#pragma once

#include "ConnectedState.hpp"
#include "UeGui/ISmsComposeMode.hpp"

namespace ue
{

    class ComposeSmsState : public ConnectedState
    {
    public:
        ComposeSmsState(Context& context);
        void sendSms();

    private:
        IUeGui::ISmsComposeMode& iSmsComposeMode;
    };

}