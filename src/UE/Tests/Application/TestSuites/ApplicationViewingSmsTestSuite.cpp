#include "ApplicationViewingSmsTestSuite.hpp"

#include "States/ViewSmsListState.hpp"
#include "States/ViewSmsState.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::DoDefault;
using ::testing::SaveArg;

namespace ue
{
// ──────────────────────────────────────────────────────────────────────────────
// 1. Brak SMS-ów  ->  widok pustej listy
// ──────────────────────────────────────────────────────────────────────────────
TEST_F(ApplicationViewingSmsTestSuite, shallShowEmptySmsListWhenNoMessages)
{
    std::function<void(size_t)> selectCb;
    std::function<void()>       closeCb;

    EXPECT_CALL(userPortMock, showNewSmsIndicator(false));
    EXPECT_CALL(userPortMock, showEmptySmsListView());
    EXPECT_CALL(userPortMock, smsSelectedCallback(_))
        .WillOnce(SaveArg<0>(&selectCb))
        .WillRepeatedly(DoDefault());
    EXPECT_CALL(userPortMock, rejectCallback(_))
        .WillOnce(SaveArg<0>(&closeCb))
        .WillRepeatedly(DoDefault());

    context().setState<ViewSmsListState>();
    ASSERT_NE(nullptr,
              dynamic_cast<ViewSmsListState*>(context().getState()));
}

// ──────────────────────────────────────────────────────────────────────────────
// 2. Jeden SMS w bazie  ->  widok listy
// ──────────────────────────────────────────────────────────────────────────────
TEST_F(ApplicationViewingSmsTestSuite, shallShowSmsListWhenMessagesExist)
{
    const common::PhoneNumber from{123};
    context().messages.emplace_back("Hello", from, context().phoneNumber);

    std::function<void(size_t)> selectCb;
    EXPECT_CALL(userPortMock, showNewSmsIndicator(false));
    EXPECT_CALL(userPortMock, showSmsListView(_));
    EXPECT_CALL(userPortMock, smsSelectedCallback(_))
        .WillOnce(SaveArg<0>(&selectCb))
        .WillRepeatedly(DoDefault());

    context().setState<ViewSmsListState>();
    ASSERT_NE(nullptr,
              dynamic_cast<ViewSmsListState*>(context().getState()));
}

// ──────────────────────────────────────────────────────────────────────────────
// 3. Wybór SMS-a  ->  widok pojedynczej wiadomości  +  oznaczenie przeczytania
// ──────────────────────────────────────────────────────────────────────────────
TEST_F(ApplicationViewingSmsTestSuite, shallShowSelectedSmsAndMarkRead)
{
    const common::PhoneNumber from{123};
    const std::string         text{"Hi!"};
    context().messages.emplace_back(text, from, context().phoneNumber);

    std::function<void(size_t)> selectCb;
    std::function<void()>       closeViewCb;

    EXPECT_CALL(userPortMock, showNewSmsIndicator(false));
    EXPECT_CALL(userPortMock, showSmsListView(_));
    EXPECT_CALL(userPortMock, smsSelectedCallback(_))
        .WillOnce(SaveArg<0>(&selectCb))
        .WillRepeatedly(DoDefault());
    EXPECT_CALL(userPortMock, rejectCallback(_))
        .WillOnce(SaveArg<0>(&closeViewCb))
        .WillRepeatedly(DoDefault());

    context().setState<ViewSmsListState>();
    ASSERT_TRUE(selectCb);

    EXPECT_CALL(userPortMock, showSmsView(text));
    EXPECT_CALL(userPortMock, rejectCallback(_))
        .WillOnce(SaveArg<0>(&closeViewCb))
        .WillRepeatedly(DoDefault());

    selectCb(0);
    ASSERT_NE(nullptr,
              dynamic_cast<ViewSmsState*>(context().getState()));
    EXPECT_TRUE(context().messages[0].hasBeenRead());
}

// ──────────────────────────────────────────────────────────────────────────────
// 4. Zamknięcie widoku SMS  ->  powrót do listy
// ──────────────────────────────────────────────────────────────────────────────
TEST_F(ApplicationViewingSmsTestSuite, shallReturnToListAfterClosingSmsView)
{
    const common::PhoneNumber from{123};
    const std::string         text{"Test"};
    context().messages.emplace_back(text, from, context().phoneNumber);

    std::function<void(size_t)> selectCb;
    std::function<void()>       closeViewCb;

    EXPECT_CALL(userPortMock, showNewSmsIndicator(false));
    EXPECT_CALL(userPortMock, showSmsListView(_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(userPortMock, smsSelectedCallback(_))
        .WillOnce(SaveArg<0>(&selectCb))
        .WillRepeatedly(DoDefault());
    EXPECT_CALL(userPortMock, rejectCallback(_))
        .WillOnce(SaveArg<0>(&closeViewCb))
        .WillRepeatedly(DoDefault());

    context().setState<ViewSmsListState>();
    ASSERT_TRUE(selectCb);

    EXPECT_CALL(userPortMock, showSmsView(text));
    EXPECT_CALL(userPortMock, rejectCallback(_))
        .WillOnce(SaveArg<0>(&closeViewCb))
        .WillRepeatedly(DoDefault());

    selectCb(0);
    ASSERT_TRUE(closeViewCb);

    EXPECT_CALL(userPortMock, showSmsListView(_));
    closeViewCb();
    ASSERT_NE(nullptr,
              dynamic_cast<ViewSmsListState*>(context().getState()));
}

// ──────────────────────────────────────────────────────────────────────────────
// 5. Zamknięcie listy  ->  powrót do Connected
// ──────────────────────────────────────────────────────────────────────────────
TEST_F(ApplicationViewingSmsTestSuite, shallReturnToConnectedAfterClosingList)
{
    std::function<void()> closeCb;

    EXPECT_CALL(userPortMock, showNewSmsIndicator(false));
    EXPECT_CALL(userPortMock, showEmptySmsListView());
    EXPECT_CALL(userPortMock, rejectCallback(_))
        .WillOnce(SaveArg<0>(&closeCb))
        .WillRepeatedly(DoDefault());

    context().setState<ViewSmsListState>();
    ASSERT_TRUE(closeCb);

    EXPECT_CALL(userPortMock, showConnected()).Times(::testing::AtLeast(1));
    closeCb();
}
}   // namespace ue
