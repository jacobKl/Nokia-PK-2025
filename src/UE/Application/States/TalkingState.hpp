#pragma once

#include "ConnectedState.hpp"

namespace ue
{
    class TalkingState : public ConnectedState
    {
        public:
            TalkingState(Context& context);
            void handleCallMessage(common::MessageId msgId, common::PhoneNumber from) override;
            std::string getName() const override;
        private:
            IUeGui::ICallMode& iCallMode;
    };
}
