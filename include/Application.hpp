#pragma once
#include <tgbot/Bot.h>
#include <tgbot/net/TgLongPoll.h>

#include <filesystem>
#include <unordered_map>

class Application
{
public:
    Application();

    void setupCommands();
    void setupCallbackQueries();
    void setupKeyboards();
    void loadData();

    void run() const;

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

private: // Handling messages and commands
    void handleAny(const TgBot::Message::Ptr& message) const;
    void handleStart(const TgBot::Message::Ptr& message) const;
    void handlePic(const TgBot::Message::Ptr& message) const;

private:
    void handleNextPicture(const TgBot::CallbackQuery::Ptr& query) const;

private: // Class members
    TgBot::Bot bot;
    TgBot::TgLongPoll longPoll;

    std::filesystem::path dataPath;

    const std::string picName = "ptitsa.png";
    const std::string picMime = "image/png";

    TgBot::InputFile::Ptr picInputFile;

private: // Mapping callbacks
    std::unordered_map<std::string, TgBot::EventBroadcaster::MessageListener> commands =
    {
        { "start", [&](const auto& message) { handleStart(message); } },
        { "pic", [&](const auto& message) { handlePic(message); } }
    };

    std::unordered_map<std::string, TgBot::EventBroadcaster::CallbackQueryListener> callbacks =
    {
        { "Next picture", [&](const auto& query) { handleNextPicture(query); } }
    };

    std::unordered_map<std::string, TgBot::ReplyKeyboardMarkup::Ptr> replyKeyboards =
    {
        { "menu", std::make_shared<TgBot::ReplyKeyboardMarkup>() }
    };

    std::unordered_map<std::string, TgBot::InlineKeyboardMarkup::Ptr> inlineKeyboards =
    {
        { "pic", std::make_shared<TgBot::InlineKeyboardMarkup>() }
    };
};
