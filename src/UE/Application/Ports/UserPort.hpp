#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include "../Enums/ScreenType.hpp"



namespace ue
{

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showPeerUserNotAvailable(common::PhoneNumber number) override;
    void showCallRequest(common::PhoneNumber) override;
    void showCallDropped() override;
    void showCallTimeout() override;


    virtual void acceptCallback(IUeGui::Callback acceptCallback) override;
    virtual void rejectCallback(IUeGui::Callback rejectCallback) override;
    virtual void doubleClickCallback(IUeGui::Callback doubleClickCallback) override;
    virtual void homeCallback(IUeGui::Callback homeCallback) override;
    virtual int getScreenId() override;

    virtual IUeGui::ISmsComposeMode &activateComposeMode() override;
    virtual IUeGui::IDialMode &activateDialMode() override;

    void showSmsListView(const std::vector<std::string>& smsInfoItems) override;
    void showEmptySmsListView() override;
    void showSmsView(const std::string& text) override;
    void smsSelectedCallback(std::function<void(size_t)> callback) override;

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    IUeGui::Callback callback;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    int screenToShow = NO_SCREEN;


    void selectScreen(IUeGui::IListViewMode& menu);
};

}
