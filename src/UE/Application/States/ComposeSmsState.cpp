#include "ComposeSmsState.hpp"

namespace ue {

    ComposeSmsState::ComposeSmsState(Context &context) :
            BaseState(context, "ComposeSmsState"),
            iSmsComposeMode(context.user.activateComposeMode()) {
    }

}