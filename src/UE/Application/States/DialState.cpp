#include "DialState.hpp"
#include "TalkingState.hpp"

using namespace std::chrono_literals;

namespace ue {

    std::string DialState::getName() const { return "DialState"; }

    DialState::DialState(Context &context) : ConnectedState(context), iDialMode(context.user.activateDialMode())
    {
        context.user.homeCallback([this]{ this->context.user.showConnected(); });
        context.user.acceptCallback([this]{ sendCallRequest(); });
    }

    void DialState::sendCallRequest() {
        logger.logDebug("[DialState] Sending call request to: ", iDialMode.getPhoneNumber());

        context.bts.sendCallRequest(iDialMode.getPhoneNumber());
        context.timer.startTimer(1000ms);
    }

    void DialState::handleCallMessage(common::MessageId msgId, common::PhoneNumber from) {
        switch (msgId) {
            case common::MessageId::CallAccepted:
                context.timer.stopTimer();
                context.setState<TalkingState>();
            break;
            case common::MessageId::UnknownRecipient:
                context.timer.stopTimer();
                context.setState<ConnectedState>();
                context.user.showPeerUserNotAvailable(iDialMode.getPhoneNumber());
            break;
            case common::MessageId::CallDropped:
                context.timer.stopTimer();
                context.setState<ConnectedState>();
                context.user.showCallDropped();
            break;
        }
    }

    void DialState::handleTimeout() {
        context.timer.stopTimer();
        context.setState<ConnectedState>();
        context.user.showCallTimeout();
    }

    void DialState::handleReject(common::PhoneNumber from) {
        context.timer.stopTimer();
        context.bts.sendCallDropped(from);
        context.setState<ConnectedState>();
    }
}