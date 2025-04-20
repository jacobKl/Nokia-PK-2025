#include "ApplicationSendingCallRequestTestSuite.hpp"
#include "States/DialState.hpp"
#include "Messages/IncomingMessage.hpp"

namespace ue {

    class MockIDialMode : public IUeGui::IDialMode {
    public:
        MOCK_METHOD(PhoneNumber, getPhoneNumber, (), (const, override));
    };

    void ApplicationSendingCallRequestTestSuite::setup()
    {
        static MockIDialMode mockDialMode;

        EXPECT_CALL(userPortMock, activateDialMode()).WillRepeatedly(ReturnRef(mockDialMode));
        EXPECT_CALL(userPortMock, showConnected()).WillRepeatedly(Return());
        EXPECT_CALL(userPortMock, doubleClickCallback(_)).WillRepeatedly(Return());
        EXPECT_CALL(userPortMock, homeCallback(_)).WillRepeatedly(Return());
        EXPECT_CALL(userPortMock, acceptCallback(_)).WillRepeatedly(Return());

        objectUnderTest.getContext().setState<DialState>();
    }

    TEST_F(ApplicationSendingCallRequestTestSuite, shallHandleBtsCallAccepted)
    {   
        setup();
        EXPECT_CALL(timerPortMock, stopTimer()).Times(1);

        objectUnderTest.handleCallMessage(common::MessageId::CallAccepted);
    }

    TEST_F(ApplicationSendingCallRequestTestSuite, shallHandleBtsUnknownRecipient)
    {
        setup();
        EXPECT_CALL(timerPortMock, stopTimer()).Times(1);
        EXPECT_CALL(userPortMock, showConnected());
        EXPECT_CALL(userPortMock, showPeerUserNotAvailable(_));

        objectUnderTest.handleCallMessage(common::MessageId::UnknownRecipient);
    }
}
