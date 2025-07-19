#pragma once
#include <tgbot/Bot.h>
#include <tgbot/net/TgLongPoll.h>

#include "NoRetryHttpClient.hpp"

#include "handlers/HandlerBase.hpp"

#include "view/BotUi.hpp"

#include <filesystem>
#include <unordered_map>

class Application
{
public:
    Application();

    void run();

private: // Handling messages and commands
    void handleAny(const TgBot::Message::Ptr& message) const;

private: // Initial bot setup
    void setupCommands();
    void setupCallbackQueries();

private: // Class members
    NoRetryHttpClient httpClient;

    TgBot::Bot bot;
    TgBot::TgLongPoll longPoll;

    BotUI ui;

    std::unique_ptr<HandlerBase> startHandler, echoHandler;

private: // Mapping callbacks
    std::unordered_map<std::string, TgBot::EventBroadcaster::MessageListener> commands =
    {
        { "start", [&](const auto& message) { startHandler->handle(message); } }
    };

    std::unordered_map<std::string, TgBot::EventBroadcaster::CallbackQueryListener> callbacks{};
};
