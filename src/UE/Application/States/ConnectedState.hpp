#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    virtual void changeScreen();
    void handleCallMessage(common::MessageId msgId, common::PhoneNumber from) override;
    std::string getName() const override;
};

}
