#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include "Endpoint.h"

#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM

class Socket
{
public:
	int		fd;
	int		type;
	bool	listening;
	
	Socket() { fd = -1; listening = false; }
	
	bool Create(int type);

	bool SetNonblocking();

	bool Bind(int port);
	bool Listen(int port, int backlog = 1024);
	bool Accept(Socket* newSocket);
	bool Connect(Endpoint &endpoint);

	bool GetEndpoint(Endpoint &endpoint);
	
	void Close();	
};

#endif
