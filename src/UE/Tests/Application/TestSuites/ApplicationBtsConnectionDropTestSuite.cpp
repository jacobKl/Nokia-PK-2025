
#include "ApplicationBtsConnectionDropTestSuite.hpp"

namespace ue
{
    TEST_F(ApplicationBtsConnectionDropTestSuite, shallHandleBtsConnectionDrop)
    {
        EXPECT_CALL(userPortMock, showNotConnected());

        objectUnderTest.handleDisconnect();
    }
}

