#ifndef APPLICATION_VIEWING_SMS_TEST_SUITE_HPP
#define APPLICATION_VIEWING_SMS_TEST_SUITE_HPP

#include "ApplicationNotConnectedTestSuite.hpp"
#include "Context.hpp"

namespace ue
{
   class ApplicationViewingSmsTestSuite : public ApplicationNotConnectedTestSuite
   {
   protected:
      ApplicationViewingSmsTestSuite()
      {
         using ::testing::_;
         using ::testing::AnyNumber;
         using ::testing::AtLeast;

         EXPECT_CALL(userPortMock, showConnected()).Times(AnyNumber());
         EXPECT_CALL(userPortMock, doubleClickCallback(_)).Times(AnyNumber());
         EXPECT_CALL(userPortMock, rejectCallback(_)).Times(AnyNumber());
         EXPECT_CALL(userPortMock, smsSelectedCallback(_)).Times(AnyNumber());
         EXPECT_CALL(userPortMock, showNewSmsIndicator(_)).Times(AnyNumber());

         sendAttachReqOnSibRecieve();

         EXPECT_CALL(timerPortMock, stopTimer()).Times(AnyNumber());
         EXPECT_CALL(userPortMock, showConnected()).Times(AtLeast(1));
         objectUnderTest.handleAttachAccept();
      }

      Context& context() { return objectUnderTest.getContext(); }
   };
}   // namespace ue
#endif
