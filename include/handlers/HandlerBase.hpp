#pragma once
#include <tgbot/types/CallbackQuery.h>
#include <tgbot/types/Message.h>

class HandlerBase
{
public:
    virtual ~HandlerBase() = default;

    virtual void handle(const TgBot::Message::Ptr& message) = 0;
    virtual void handle(const TgBot::CallbackQuery::Ptr& query) = 0;
};
