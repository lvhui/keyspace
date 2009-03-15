#ifndef TRANSPORT_UDP_WRITER_H
#define TRANSPORT_UDP_WRITER_H

#include "System/IO/Socket.h"
#include "TransportWriter.h"

class TransportUDPWriter : public TransportWriter
{
public:
	TransportUDPWriter();
	~TransportUDPWriter();
	
	// TransportWriter interface
	virtual void	Init(IOProcessor* ioproc_, Scheduler* scheduler_, Endpoint &endpoint_);
	virtual	void	Write(ByteString &bs);

private:
	IOProcessor*	ioproc;
	Endpoint		endpoint;
	Socket			socket;
};

#endif