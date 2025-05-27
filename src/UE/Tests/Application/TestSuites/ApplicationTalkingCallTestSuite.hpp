#ifndef APPLICATION_TALKING_CALL_TEST_SUITE_HPP
#define APPLICATION_TALKING_CALL_TEST_SUITE_HPP

#include "ApplicationNotConnectedTestSuite.hpp"
#include "States/TalkingState.hpp"

#include <gmock/gmock.h>
#include <functional>

namespace ue {

    class ApplicationTalkingCallTestSuite : public ApplicationNotConnectedTestSuite
    {
    protected:
        ApplicationTalkingCallTestSuite()
        {
            using namespace ::testing;

            EXPECT_CALL(userPortMock, showConnected()).Times(AtLeast(1));
            EXPECT_CALL(userPortMock, doubleClickCallback(_)).Times(AnyNumber());
            EXPECT_CALL(userPortMock, rejectCallback(_)).Times(AnyNumber());
            EXPECT_CALL(userPortMock, acceptCallback(_)).Times(AnyNumber());
            EXPECT_CALL(userPortMock, smsSelectedCallback(_)).Times(AnyNumber());
            EXPECT_CALL(userPortMock, showNewSmsIndicator(_)).Times(AnyNumber());

            sendAttachReqOnSibRecieve();
            EXPECT_CALL(timerPortMock, stopTimer());
            EXPECT_CALL(userPortMock, showConnected());
            objectUnderTest.handleAttachAccept();

            peerNumber = common::PhoneNumber{42};
            objectUnderTest.getContext().peerPhoneNumber = peerNumber;

            EXPECT_CALL(userPortMock, setCloseGuard(_))
                .WillOnce(SaveArg<0>(&closeGuard));

            objectUnderTest.getContext().setState<TalkingState>();
        }

        std::function<bool()> closeGuard;
        common::PhoneNumber   peerNumber;
    };

} // namespace ue

#endif // APPLICATION_TALKING_CALL_TEST_SUITE_HPP
