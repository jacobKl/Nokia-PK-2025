#include "TalkingState.hpp"

namespace ue {
    TalkingState::TalkingState(Context &context) : ConnectedState(context) {
        logger.logInfo("[TalkingState] Talking state constructor.");
    }
}
