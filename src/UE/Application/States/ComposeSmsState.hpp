#pragma once

#include "BaseState.hpp"
#include "UeGui/ISmsComposeMode.hpp"

namespace ue
{

    class ComposeSmsState : public BaseState
    {
    public:
        ComposeSmsState(Context& context);

    private:
        IUeGui::ISmsComposeMode& iSmsComposeMode;
    };

}