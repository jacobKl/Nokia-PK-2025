#include "ApplicationTalkingCallTestSuite.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;

namespace ue {

// User closes UE while having Call (Talking) -> send Call Dropped
TEST_F(ApplicationTalkingCallTestSuite, shallSendCallDroppedWhenUserCloses)
{
    ASSERT_TRUE(closeGuard) << "TalkingState did not install a close-guard callback";
    EXPECT_CALL(btsPortMock, sendCallDropped(peerNumber));
    closeGuard();
}

// UE connection to BTS was dropped while having Call (Talking) -> go to NotConnected
TEST_F(ApplicationTalkingCallTestSuite, shallGoToNotConnectedOnBtsDisconnect)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnect();
    EXPECT_EQ("NotConnectedState", objectUnderTest.getStateName());
}

// UE receives SMS, while having Call (Talking) -> store it, remain in Talking
TEST_F(ApplicationTalkingCallTestSuite, shallStoreReceivedSmsButStayInTalking)
{
    const common::PhoneNumber from{7};
    const std::string         txt{"Background SMS"};
    auto& ctx = objectUnderTest.getContext();
    ssize_t before = ctx.messages.size();

    EXPECT_CALL(userPortMock, showNewSmsIndicator(true));
    objectUnderTest.handleSmsReceived(from, txt);

    ASSERT_EQ(before + 1, ctx.messages.size());
    EXPECT_EQ(txt, ctx.messages.back().getText());
    EXPECT_EQ("TalkingState", objectUnderTest.getStateName());
}

// UE receives Call Request, while having Call (Talking)
// a) from other UE → drop it
TEST_F(ApplicationTalkingCallTestSuite, shallDropIncomingCallRequestFromOther)
{
    const common::PhoneNumber other{13};
    EXPECT_CALL(btsPortMock, sendCallDropped(other));
    objectUnderTest.handleCallMessage(common::MessageId::CallRequest, other);
}

// b) from same peer -> ignore
TEST_F(ApplicationTalkingCallTestSuite, shallIgnoreCallRequestFromSamePeer)
{
    EXPECT_CALL(btsPortMock, sendCallDropped(_)).Times(0);
    objectUnderTest.handleCallMessage(common::MessageId::CallRequest, peerNumber);
}

} // namespace ue
