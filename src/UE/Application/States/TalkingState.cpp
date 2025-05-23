#include "TalkingState.hpp"
#include "UeGui/ICallMode.hpp"

namespace ue {
    std::string TalkingState::getName() const { return "TalkingState"; }

    TalkingState::TalkingState(Context &context) : ConnectedState(context), iCallMode(context.user.activateCallMode()) {
        logger.logInfo("[TalkingState] Talking state constructor.");

        iCallMode.clearIncomingText();
        iCallMode.clearOutgoingText();

        context.user.acceptCallback([this, &context] {
            std::string text = iCallMode.getOutgoingText();
            if (text.empty()) return;
            context.bts.sendCallTalk(context.peerPhoneNumber, text);
            iCallMode.clearOutgoingText();
            iCallMode.appendIncomingText("[Me]: " + text);
        });

        context.user.rejectCallback([this, &context] {
            logger.logInfo("[TalkingState] User hung up the call.");
            logger.logInfo("[TalkingState] Sending call dropped to peer: ", to_string(context.peerPhoneNumber));
            context.bts.sendCallDropped(context.peerPhoneNumber);
            context.user.showConnected();
            context.setState<ConnectedState>();
            iCallMode.clearIncomingText();
        });
        
    }

    void TalkingState::handleCallMessage(common::MessageId msgId, common::PhoneNumber from)
    {
    logger.logInfo("Message received: ", to_string(msgId));
    if (msgId == common::MessageId::CallDropped)
    {
        logger.logInfo("Call dropped by peer: ", to_string(from));
        context.user.showConnected();
        context.setState<ConnectedState>();
    }
    }

    void TalkingState::handleCallTalk(common::PhoneNumber from, const std::string& text)
    {
        iCallMode.appendIncomingText("[" + to_string(from) + "]: " + text);
    }
}