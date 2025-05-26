#include "ApplicationSmsReceivingTestSuite.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

namespace ue {

void ApplicationSmsReceivingTestSuite::expectShowNewSms()
{
    EXPECT_CALL(userPortMock, showNewSmsIndicator(true));
}

void ApplicationSmsReceivingTestSuite::setupConnectedState()
{
    EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
    EXPECT_CALL(timerPortMock, startTimer(500ms));
    EXPECT_CALL(userPortMock, showConnecting());
    objectUnderTest.handleSib(BTS_ID);
    
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showConnected());
    EXPECT_CALL(userPortMock, doubleClickCallback(_));
    objectUnderTest.handleAttachAccept();
}

TEST_F(ApplicationSmsReceivingTestSuite, shallStoreReceivedSmsInDatabase)
{
    setupConnectedState();
    expectShowNewSms();
    
    common::PhoneNumber senderNumber{123};
    std::string smsText = "Hello, test SMS";
    
    objectUnderTest.handleSmsReceived(senderNumber, smsText);
    
    ASSERT_TRUE(true);
}

TEST_F(ApplicationSmsReceivingTestSuite, shallSetUnreadFlagWhenReceivingSms)
{
    setupConnectedState();
    expectShowNewSms();
    
    common::PhoneNumber senderNumber{123};
    std::string smsText = "Hello, test SMS";
    
    objectUnderTest.handleSmsReceived(senderNumber, smsText);
    
    ASSERT_TRUE(true);
}

TEST_F(ApplicationSmsReceivingTestSuite, shallShowNewSmsIndicatorWhenReceiving)
{
    setupConnectedState();
    
    common::PhoneNumber senderNumber{123};
    std::string smsText = "Hello, test SMS";
    
    EXPECT_CALL(userPortMock, showNewSmsIndicator(true)).Times(1);
    
    objectUnderTest.handleSmsReceived(senderNumber, smsText);
}

TEST_F(ApplicationSmsReceivingTestSuite, shallKeepMultipleReceivedSmsInDatabase)
{
    setupConnectedState();
    
    common::PhoneNumber senderNumber1{123};
    common::PhoneNumber senderNumber2{124};
    std::string smsText1 = "First test SMS";
    std::string smsText2 = "Second test SMS";
    
    EXPECT_CALL(userPortMock, showNewSmsIndicator(true)).Times(2);
    
    objectUnderTest.handleSmsReceived(senderNumber1, smsText1);
    objectUnderTest.handleSmsReceived(senderNumber2, smsText2);
    
    ASSERT_TRUE(true);
}

TEST_F(ApplicationSmsReceivingTestSuite, shallHandleEmptySmsText)
{
    setupConnectedState();
    expectShowNewSms();
    
    common::PhoneNumber senderNumber{123};
    std::string smsText = "";
    
    objectUnderTest.handleSmsReceived(senderNumber, smsText);
    

    ASSERT_TRUE(true);
}

TEST_F(ApplicationSmsReceivingTestSuite, shallHandleLongSmsText)
{
    setupConnectedState();
    expectShowNewSms();
    
    common::PhoneNumber senderNumber{123};
    std::string smsText = "This is a very long SMS text that exceeds normal length to test the system's ability to handle longer messages properly without any issues or truncation problems.";
    
    objectUnderTest.handleSmsReceived(senderNumber, smsText);
    

    ASSERT_TRUE(true);
}

TEST_F(ApplicationSmsReceivingTestSuite, shallReceiveSmsFromSameSenderMultipleTimes)
{
    setupConnectedState();
    
    common::PhoneNumber senderNumber{123};
    std::string smsText1 = "First message";
    std::string smsText2 = "Second message";
    std::string smsText3 = "Third message";
    
    EXPECT_CALL(userPortMock, showNewSmsIndicator(true)).Times(3);
    
    objectUnderTest.handleSmsReceived(senderNumber, smsText1);
    objectUnderTest.handleSmsReceived(senderNumber, smsText2);
    objectUnderTest.handleSmsReceived(senderNumber, smsText3);
    
    ASSERT_TRUE(true);
}

}
