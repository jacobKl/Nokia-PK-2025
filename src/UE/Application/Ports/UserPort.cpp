#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();

    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    menu.addSelectionListItem("Make a call", "");

    gui.setAcceptCallback([this, &menu]{ selectScreen(menu);});
}

void UserPort::showPeerUserNotAvailable(common::PhoneNumber number) {
    gui.showPeerUserNotAvailable(number);

    const auto handler = [&] {
        gui.setListViewMode();
    };

    gui.setAcceptCallback(handler);
    gui.setRejectCallback(handler);
    gui.setHomeCallback(handler);
}

void UserPort::acceptCallback(IUeGui::Callback acceptCallback) {
    gui.setAcceptCallback(acceptCallback);
}

void UserPort::rejectCallback(IUeGui::Callback rejectCallback) {
    gui.setRejectCallback(rejectCallback);
}

void UserPort::doubleClickCallback(IUeGui::Callback doubleClickCallback) {
    gui.setDoubleClickCallback(doubleClickCallback);
}

void UserPort::homeCallback(IUeGui::Callback homeCallback) {
    gui.setHomeCallback(homeCallback);
}

void UserPort::selectScreen(IUeGui::IListViewMode& menu) {
    IUeGui::IListViewMode::OptionalSelection pair = menu.getCurrentItemIndex();

    if (pair.first) {
        screenToShow = pair.second;
    } else {
        screenToShow = NO_SCREEN;
    }
}

int UserPort::getScreenId() {
    return screenToShow;
}

IUeGui::ISmsComposeMode &UserPort::activateComposeMode(){
    IUeGui::ISmsComposeMode &mode = gui.setSmsComposeMode();

    return mode;
}

IUeGui::IDialMode &UserPort::activateDialMode() {
    IUeGui::IDialMode &mode = gui.setDialMode();

    return mode;
}



}
