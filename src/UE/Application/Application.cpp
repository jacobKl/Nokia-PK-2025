#include "Application.hpp"
#include "Sms/Sms.hpp"
#include "States/ViewSmsListState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer)
    : context{iLogger, bts, user, timer},
      logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.phoneNumber = phoneNumber;
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

std::string Application::getStateName()
{
    return dynamic_cast<BaseState*>(context.state.get())->getName();
}

void Application::handleTimeout()
{
    context.state->handleTimeout();
}

void Application::handleSib(common::BtsId btsId)
{
    context.state->handleSib(btsId);
}

void Application::handleAttachAccept()
{
    context.state->handleAttachAccept();
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
}

void Application::handleDisconnect() 
{
    context.state->handleDisconnect();
}

void Application::handleCallMessage(common::MessageId msgId, common::PhoneNumber from)
{
    context.state->handleCallMessage(msgId, from);
}

void Application::handleCallReceive(common::MessageId msgId, common::PhoneNumber from)
{
    context.state->handleCallReceive(msgId, from);
}

void Application::handleCallTalk(common::PhoneNumber from, const std::string& text)
{
    context.state->handleCallTalk(from, text);
}

void Application::handleSmsReceived(common::PhoneNumber from, const std::string& text)
{

    Sms newSms = Sms(text, from, context.phoneNumber, std::chrono::system_clock::now());
    context.messages.push_back(newSms);
    context.hasUnreadMessages = true;

    context.state->handleSmsReceived(from, text);

    if (dynamic_cast<ViewSmsListState*>(context.state.get()) == nullptr) {
        context.user.showNewSmsIndicator(true);
    }

}

Context& Application::getContext() {
    return context;
}

}
