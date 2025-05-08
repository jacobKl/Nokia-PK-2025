#pragma once

#include "ConnectedState.hpp"
#include "UeGui/IDialMode.hpp"
#include "Messages/IncomingMessage.hpp"


namespace ue
{
    class DialState : public ConnectedState
    {
        public:
            DialState(Context& context);
            void sendCallRequest();
            void handleCallMessage(common::MessageId msgId, common::PhoneNumber from) override;
            void handleTimeout() override;

        private:
            IUeGui::IDialMode& iDialMode;
    };
}