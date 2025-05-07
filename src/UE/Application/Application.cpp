#include "Application.hpp"
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
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
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

Context& Application::getContext() {
    return context;
}

}
