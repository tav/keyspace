#include "PaxosLearner.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "System/Log.h"
#include "System/Events/EventLoop.h"
#include "Framework/ReplicatedLog/ReplicatedConfig.h"
#include "PaxosConsts.h"

PaxosLearner::PaxosLearner()
{
}

void PaxosLearner::Init(Writers writers_)
{
	writers = writers_;
	lastRequestChosenTime = 0;
	lastRequestChosenPaxosID = 0;
	state.Init();
}

bool PaxosLearner::RequestChosen(unsigned nodeID)
{
	Log_Trace();
	
	if (lastRequestChosenPaxosID == paxosID &&
	EventLoop::Now() - lastRequestChosenTime < REQUEST_CHOSEN_TIMEOUT)
		return true;
	
	lastRequestChosenPaxosID = paxosID;
	lastRequestChosenTime = EventLoop::Now();
	
	msg.RequestChosen(paxosID, RCONF->GetNodeID());
	
	msg.Write(wdata);

	writers[nodeID]->Write(wdata);
	
	return true;
}

bool PaxosLearner::SendChosen(unsigned nodeID,
							  uint64_t paxosID,
							  ByteString& value)
{
	Log_Trace();
	
	msg.LearnValue(paxosID, RCONF->GetNodeID(), value);
	
	msg.Write(wdata);

	writers[nodeID]->Write(wdata);
	
	return true;
}

bool PaxosLearner::SendStartCatchup(unsigned nodeID,
									uint64_t paxosID)
{
	Log_Trace();
	
	msg.StartCatchup(paxosID, RCONF->GetNodeID());
	
	msg.Write(wdata);

	writers[nodeID]->Write(wdata);
	
	return true;
}

void PaxosLearner::OnLearnChosen(PaxosMsg& msg_)
{
	Log_Trace();

	msg = msg_;

	state.learned = true;
	state.value.Set(msg.value);

	Log_Trace("+++ Consensus for paxosID = %" PRIu64 " is %.*s +++", paxosID,
		state.value.length, state.value.buffer);
}

void PaxosLearner::OnRequestChosen(PaxosMsg& msg_)
{
	Log_Trace();

	msg = msg_;

	if (state.learned)
		SendChosen(msg.nodeID, paxosID, state.value);
}

bool PaxosLearner::Learned()
{
	return state.learned;	
}

ByteString PaxosLearner::Value()
{
	return state.value;
}
