#include "ApplicationNotConnectedTestSuite.hpp"

namespace ue
{

void ApplicationNotConnectedTestSuite::sendAttachReqOnSibRecieve()
{
    EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
    EXPECT_CALL(timerPortMock, startTimer(500ms));
    EXPECT_CALL(userPortMock, showConnecting());

    objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationNotConnectedTestSuite, shallSendAttachReqOnSibRecieve)
{
    sendAttachReqOnSibRecieve();
}

}
