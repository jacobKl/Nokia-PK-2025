#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
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

//    gui.setAcceptCallback([this, &menu]{ showScreen(menu);});
}

void UserPort::acceptCallback(IUeGui::Callback acceptCallback) {
    gui.setAcceptCallback(acceptCallback);
}

void UserPort::rejectCallback(IUeGui::Callback rejectCallback) {
    gui.setRejectCallback(rejectCallback);
}

void UserPort::showScreen(IUeGui::IListViewMode& menu) {
    IUeGui::IListViewMode::OptionalSelection pair = menu.getCurrentItemIndex();
    logger.logInfo(pair.second);
}

int UserPort::getScreenId() {
    return screenToShow;
}

IUeGui::ISmsComposeMode &UserPort::activateComposeMode(){
    IUeGui::ISmsComposeMode &mode = gui.setSmsComposeMode();
    return mode;
}

}
