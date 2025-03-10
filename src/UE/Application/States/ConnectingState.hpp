#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectingState : public BaseState
{
public:
    ConnectingState(Context& context);

    // IBtsEventsHandler interface
public:
    void handleAttachAccept() override;
};

}
