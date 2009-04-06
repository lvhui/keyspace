#include "HttpConn.h"
#include "HttpServer.h"

#define MAX_MESSAGE_SIZE	4096
#define CS_CR				"\015"
#define CS_LF				"\012"
#define CS_CRLF				CS_CR CS_LF
#define MSG_FAIL			"Unable to process your request at this time"
#define MSG_NOT_FOUND		"Not found"
#define RESPONSE_FAIL		Response(500, MSG_FAIL, sizeof(MSG_FAIL) - 1)
#define RESPONSE_NOTFOUND	Response(404, MSG_NOT_FOUND, sizeof(MSG_NOT_FOUND) - 1)


HttpConn::HttpConn()
{
	server = NULL;
}


void HttpConn::Init(KeyspaceDB* kdb_, HttpServer* server_)
{
	TCPConn<>::Init();
	KeyspaceClient::Init(kdb_);
	
	server = server_;
	
	request.Init();
}


void HttpConn::OnComplete(KeyspaceOp* op, bool status)
{
	Log_Trace();
	
	numpending--;
	
	if (op->type == KeyspaceOp::GET ||
		op->type == KeyspaceOp::DIRTY_GET ||
		op->type == KeyspaceOp::INCREMENT ||
		op->type == KeyspaceOp::LIST)
	{
		if (status)
			Response(200, op->value.buffer, op->value.length);
		else
			RESPONSE_NOTFOUND;
	}
	else if (op->type == KeyspaceOp::SET ||
			 op->type == KeyspaceOp::TEST_AND_SET)
	{
		if (status)
			Response(200, "OK", strlen("OK"));
		else
			Response(200, "Failed", strlen("Failed"));
	}
	else if (op->type == KeyspaceOp::DELETE)
	{
		if (status)
			Response(200, "OK", strlen("OK"));
		else
			RESPONSE_NOTFOUND;
	}
	else
		ASSERT_FAIL();
	
	op->Free();

	if (state == DISCONNECTED && numpending == 0)
		server->DeleteConn(this);
}


void HttpConn::OnRead()
{
	Log_Trace();
	
	Parse(tcpread.data.buffer, tcpread.data.length);
	
	IOProcessor::Get()->Add(&tcpread);
}


void HttpConn::OnClose()
{
	Log_Trace();
	Close();
	request.Free();
	if (numpending == 0)
		server->DeleteConn(this);
}


int HttpConn::Parse(char* buf, int len)
{
	int pos;
	int ret;
	
	pos = request.Parse(buf, len);
	if (pos <= 0)
		return pos;
	
	if (strcmp(request.line.method, "GET") == 0)
	{
		ret = ProcessGetRequest();
		if (ret < 0)
			return -1;
		
		return pos;
	}
	
	return -1;
}

int HttpConn::ProcessGetRequest()
{
	KeyspaceOp op;
	const char* key;
	const char* value;
	const char* test;
	int keylen;
	int valuelen;
	int testlen;
	// http://localhost:8080/get/key
	// http://localhost:8080/set/key/value
	
	op.client = this;
	
	if (strncmp(request.line.uri, "/get/", strlen("/get/")) == 0)
	{
		key = request.line.uri + strlen("/get/");
		keylen = strlen(key);
		
		op.type = KeyspaceOp::GET;
		
		if (!op.key.Allocate(keylen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.key.Set((char*) key, keylen);
		
		if (!Add(op))
			RESPONSE_FAIL;
		
		return 0;
	}
	else if (strncmp(request.line.uri, "/dirtyget/", strlen("/dirtyget/")) == 0)
	{
		key = request.line.uri + strlen("/dirtyget/");
		keylen = strlen(key);
		
		op.type = KeyspaceOp::DIRTY_GET;
		
		if (!op.key.Allocate(keylen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.key.Set((char*) key, keylen);
		
		if (!Add(op))
			RESPONSE_FAIL;
		
		return 0;
	}
	else if (strncmp(request.line.uri, "/set/", strlen("/set/")) == 0)
	{
		key = request.line.uri + strlen("/set/");
		value = strchr(key, '/');
		if (!value)
			return -1;
		
		keylen = value - key;
		value++;
		valuelen = strlen(value);
		
		op.type = KeyspaceOp::SET;
		
		if (!op.key.Allocate(keylen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.key.Set((char*) key, keylen);
		
		if (!op.value.Allocate(valuelen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.value.Set((char*) value, valuelen);
		
		if (!Add(op))
			RESPONSE_FAIL;
		
		return 0;
	}
	else if (strncmp(request.line.uri, "/testandset/", strlen("testandset")) == 0)
	{
		key = request.line.uri + strlen("/testandset/");
		test = strchr(key, '/');
		if (!test)
			return -1;
		
		keylen = test - key;
		test++;
		
		value = strchr(test, '/');
		if (!value)
			return -1;
		
		testlen = value - test;
		value++;
		
		valuelen = strlen(value);
		
		op.type = KeyspaceOp::TEST_AND_SET;
		
		if (!op.key.Allocate(keylen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.key.Set((char*) key, keylen);
		
		if (!op.test.Allocate(testlen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.test.Set((char*) test, testlen);
		
		if (!op.value.Allocate(valuelen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.value.Set((char*) value, valuelen);
		
		if (!Add(op))
			RESPONSE_FAIL;
		
		return 0;
	}
	else if (strncmp(request.line.uri, "/increment/", strlen("/increment/")) == 0)
	{
		key = request.line.uri + strlen("/increment/");
		keylen = strlen(key);
		
		op.type = KeyspaceOp::INCREMENT;
		
		if (!op.key.Allocate(keylen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.key.Set((char*) key, keylen);
		
		if (!Add(op))
			RESPONSE_FAIL;
		
		return 0;
	}
	else if (strncmp(request.line.uri, "/delete/", strlen("/delete/")) == 0)
	{
		key = request.line.uri + strlen("/delete/");
		keylen = strlen(key);
		
		op.type = KeyspaceOp::DELETE;
		
		if (!op.key.Allocate(keylen))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.key.Set((char*) key, keylen);
		
		if (!Add(op))
			RESPONSE_FAIL;
		
		return 0;
	}
	else if (strncmp(request.line.uri, "/list/", strlen("/list/")) == 0)
	{
		key = request.line.uri + strlen("/list/");
		keylen = strlen(key);
		
		op.type = KeyspaceOp::LIST;
		
		// HACK +1 is to handle empty string (solution is to use DynBuffer)
		if (!op.key.Allocate(keylen + 1))
		{
			RESPONSE_FAIL;
			return 0;
		}
		op.key.Set((char*) key, keylen);
		
		if (!Add(op))
			RESPONSE_FAIL;
			
		return 0;
	}
	else if (strcmp(request.line.uri, "/latency") == 0)
	{
		Response(200, "OK", 2);
		return 0;
	}
	else
	{
		RESPONSE_NOTFOUND;
	}
	
	return -1;
}

const char* HttpConn::Status(int code)
{
	if (code == 200)
		return "OK";
	if (code == 404)
		return "Not found";
	
	return "";
}

void HttpConn::Response(int code, char* data, int len, bool close, char* header)
{	
	DynArray<MAX_MESSAGE_SIZE> httpHeader;
	int size;

	do {
		size = snprintf(httpHeader.buffer, httpHeader.size,
					"%s %d %s" CS_CRLF
					"Accept-Range: bytes" CS_CRLF
					"Content-Length: %d" CS_CRLF
					"Cache-Control: no-cache" CS_CRLF
					"%s"
					"%s"
					CS_CRLF
					, 
					request.line.version, code, Status(code),
					len,
					close ? "Connection: close" CS_CRLF : "",
					header ? header : "");

		if (size <= httpHeader.size)
			break;

		httpHeader.Reallocate(size, true);
	} while (1);
			
	Write(httpHeader.buffer, size - 1, false);
	Write(data, len);
}
