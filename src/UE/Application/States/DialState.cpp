#include "DialState.hpp"

using namespace std::chrono_literals;

namespace ue {

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

    void DialState::handleCallMessage(common::MessageId msgId) {

        switch (msgId) {
            case common::MessageId::CallRequest:
                printf("handling call request. \n");
            break;
            case common::MessageId::UnknownRecipient:
                context.timer.stopTimer();
                context.setState<ConnectedState>();
                context.user.showPeerUserNotAvailable(iDialMode.getPhoneNumber());
            break;
        }
    }

    void DialState::handleTimeout() {
        printf("[DialState] handle timeout.\n");
    }
}