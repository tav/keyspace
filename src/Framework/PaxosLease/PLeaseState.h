#ifndef PLEASESTATE_H
#define PLEASESTATE_H

#include "System/Platform.h"
#include "System/Buffer.h"

class PLeaseProposerState
{
public:			
	bool Active()
	{
		return (preparing || proposing);
	}
	
	void Init()
	{
		preparing =	false;
		proposing =	false;
		proposalID = 0;
		highestReceivedProposalID =	0;
		duration = 0;
		expireTime = 0;
	}
	
public:
	bool		preparing;
	bool		proposing;
	uint64_t	proposalID;
	uint64_t	highestReceivedProposalID;
	unsigned	leaseOwner;
	unsigned	duration;
	uint64_t	expireTime;

};

class PLeaseAcceptorState
{
public:
	void Init()
	{
		promisedProposalID = 0;

		accepted = false;
		acceptedProposalID = 0;
		acceptedLeaseOwner = 0;
		acceptedDuration = 0;
		acceptedExpireTime = 0;
	}

	void OnLeaseTimeout()
	{
		accepted = false;
		acceptedProposalID = 0;
		acceptedLeaseOwner = 0;
		acceptedDuration   = 0;
		acceptedExpireTime = 0;
	}
public:
	uint64_t	promisedProposalID;
	bool		accepted;
	uint64_t	acceptedProposalID;
	unsigned	acceptedLeaseOwner;
	unsigned	acceptedDuration;
	uint64_t	acceptedExpireTime;
};

class PLeaseLearnerState
{
public:	
	void Init()
	{
		learned = 0;
		leaseOwner = 0;
		expireTime = 0;
		leaseEpoch = 0;
	}
	
	void OnLeaseTimeout()
	{
		learned = 0;
		leaseOwner = 0;
		expireTime = 0;
		leaseEpoch++;
	}
	
public:
	bool		learned;
	unsigned	leaseOwner;
	uint64_t	expireTime;
	uint64_t	leaseEpoch;
};

#endif
