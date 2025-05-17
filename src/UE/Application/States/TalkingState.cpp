#include "TalkingState.hpp"

namespace ue {
    std::string TalkingState::getName() const { return "TalkingState"; }

    TalkingState::TalkingState(Context &context) : ConnectedState(context) {
        logger.logInfo("[TalkingState] Talking state constructor.");

        context.user.rejectCallback([this, &context] {
            logger.logInfo("[TalkingState] User hung up the call.");
            context.bts.sendCallDropped(context.peerPhoneNumber);
            context.user.showConnected();
            context.setState<ConnectedState>();
        });
        
    }

    void TalkingState::handleCallMessage(common::MessageId msgId, common::PhoneNumber from)
    {
    if (msgId == common::MessageId::CallDropped)
    {
        logger.logInfo("Call dropped by peer: ", to_string(from));
        context.user.showConnected();
        context.setState<ConnectedState>();
    }
    }
}