#pragma once

#include <IUeGui.hpp>

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showPeerUserNotAvailable(common::PhoneNumber number) = 0;
    virtual void showCallRequest(common::PhoneNumber) = 0;
    virtual void showCallDropped() = 0;
    virtual void showCallTimeout() = 0;

    virtual void acceptCallback(IUeGui::Callback acceptCallback) = 0;
    virtual void rejectCallback(IUeGui::Callback rejectCallback) = 0;
    virtual void doubleClickCallback(IUeGui::Callback doubleClickCallback) = 0;
    virtual void homeCallback(IUeGui::Callback homeCallback) = 0;
    virtual int getScreenId() = 0;

    virtual IUeGui::ISmsComposeMode &activateComposeMode() = 0;
    virtual IUeGui::IDialMode &activateDialMode() = 0;

    virtual void showSmsListView(const std::vector<std::string>& smsInfoItems) = 0;
    virtual void showEmptySmsListView() = 0;
    virtual void showSmsView(const std::string& text) = 0;
    virtual void smsSelectedCallback(std::function<void(size_t)> callback) = 0;
    virtual void showNewSmsIndicator(bool hasNew) = 0;
};

}
