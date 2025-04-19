#pragma once

#include "ConnectedState.hpp"
#include "UeGui/IDialMode.hpp"

namespace ue
{
    class DialState : public ConnectedState
    {
        public:
            DialState(Context& context);
            void sendCallRequest();
            void handleUnknownRecipient() override;
            void handleTimeout() override;

        private:
            IUeGui::IDialMode& iDialMode;
    };
}