#pragma once
#include "HandlerBase.hpp"

#include "view/BotUi.hpp"

class EchoHandler final : public HandlerBase
{
public:
    explicit EchoHandler(BotUI& ui) : ui(ui) {}

    void handle(const TgBot::Message::Ptr& message) override;
    void handle(const TgBot::CallbackQuery::Ptr& query) override {}

private:
    BotUI& ui;
};
