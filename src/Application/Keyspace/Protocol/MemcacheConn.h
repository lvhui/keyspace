#ifndef MEMCACHE_CONN_H
#define MEMCACHE_CONN_H

#include "System/Containers/List.h"
#include "System/Events/Callable.h"
#include "System/IO/Socket.h"
#include "System/IO/IOOperation.h"
#include "System/IO/IOProcessor.h"

#include "../Database/KeyspaceDB.h"
#include "../Database/KeyspaceClient.h"

class MemcacheServer;

class MemcacheConn : public TCPConn<>, public KeyspaceClient
{
public:		
	void			Init(MemcacheServer* server_, KeyspaceDB* kdb_);

	// TCPConn interface
	virtual void	OnRead();
	virtual void	OnClose();
	
	// KeyspaceClient interface
	virtual void	OnComplete(KeyspaceOp* op, bool status);
	
private:
	class Token
	{
	public:
		const char*	value;
		int			len;
	};

	MemcacheServer*	server;
	KeyspaceDB*		kdb;
	const char*		newline;
	int				numpending;

	int				Tokenize(const char* data, int size, Token* tokens, int maxtokens);
	const char*		Process(const char* data, int size);
	const char*		ProcessGetCommand(const char* data, int size, Token* tokens, int numtoken);
	const char*		ProcessSetCommand(const char* data, int size, Token* tokens, int numtoken);
};

#endif
