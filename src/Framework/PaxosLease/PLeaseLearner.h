#ifndef PLEASELEARNER_H
#define PLEASELEARNER_H

#include "System/Common.h"
#include "System/Events/Scheduler.h"
#include "Framework/Transport/TransportWriter.h"
#include "Framework/Paxos/PaxosConfig.h"
#include "PLeaseMsg.h"
#include "PLeaseState.h"

class PLeaseLearner
{
public:
							PLeaseLearner();
	
	bool					Init(Scheduler* scheduler_, PaxosConfig* config_);

	void					ProcessMsg(PLeaseMsg &msg);
	
	void					OnLeaseTimeout();
	
	bool					IsLeaseOwner();
	bool					LeaseKnown();
	unsigned				LeaseOwner();
	ulong64					LeaseEpoch();
	
	void					SetOnLearnLease(Callable* onLearnLeaseCallback_);
	void					SetOnLeaseTimeout(Callable* onLeaseTimeoutCallback_);

private:
	virtual void			OnLearnChosen();

	Scheduler*				scheduler;
	
	MFunc<PLeaseLearner>	onLeaseTimeout;
	Timer					leaseTimeout;
	
	PLeaseMsg				msg;
	
	PaxosConfig*			config;
	
	PLeaseLearnerState		state;
	
	Callable*				onLearnLeaseCallback;
	Callable*				onLeaseTimeoutCallback;
};

#endif
