#pragma once

#include "ConnectedState.hpp"

namespace ue
{
    class TalkingState : public ConnectedState
    {
        public:
            TalkingState(Context& context);
    };
}
