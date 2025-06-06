#pragma once
#include <tgbot/Bot.h>
#include <tgbot/net/TgLongPoll.h>

#include <filesystem>
#include <unordered_map>

class Application
{
public:
    Application();

    void run();

private: // Handling messages and commands
    void handleAny(const TgBot::Message::Ptr& message) const;
    void handleStart(const TgBot::Message::Ptr& message) const;

private: // Initial bot setup
    void setupCommands();
    void setupCallbackQueries();
    void setupKeyboards();

private: // Keyboards setup
    void setupReplyKeyboards();
    void setupInlineKeyboards();

    static void createReplyKeyboard(
        const std::vector<std::vector<std::string>>& layout,
        const TgBot::ReplyKeyboardMarkup::Ptr& keyboard
    );
    static void createInlineKeyboard(
        const std::vector<std::vector<std::string>>& layout,
        const TgBot::InlineKeyboardMarkup::Ptr& keyboard
    );

private: // Class members
    TgBot::Bot bot;
    TgBot::TgLongPoll longPoll;

private: // Mapping callbacks
    std::unordered_map<std::string, TgBot::EventBroadcaster::MessageListener> commands =
    {
        { "start", [&](const auto& message) { handleStart(message); } }
    };

    std::unordered_map<std::string, TgBot::EventBroadcaster::CallbackQueryListener> callbacks{};

    std::unordered_map<std::string, TgBot::ReplyKeyboardMarkup::Ptr> replyKeyboards{};

    std::unordered_map<std::string, TgBot::InlineKeyboardMarkup::Ptr> inlineKeyboards{};
};
