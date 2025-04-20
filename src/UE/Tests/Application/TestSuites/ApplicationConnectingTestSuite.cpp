#include "ApplicationConnectingTestSuite.hpp"

namespace ue
{
    TEST_F(ApplicationConnectingTestSuite, shallConnectOnAttachAccept)
    {
        EXPECT_CALL(timerPortMock, stopTimer());
        EXPECT_CALL(userPortMock, showConnected());
        EXPECT_CALL(userPortMock, doubleClickCallback(_));

        objectUnderTest.handleAttachAccept();
    }

    TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnAttachReject)
    {
        EXPECT_CALL(timerPortMock, stopTimer());
        EXPECT_CALL(userPortMock, showNotConnected());

        objectUnderTest.handleAttachReject();
    }

    TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnTimeout)
    {
        EXPECT_CALL(userPortMock, showNotConnected());

        objectUnderTest.handleTimeout();
    }
}
