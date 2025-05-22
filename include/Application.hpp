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
    void loadData();

    void run() const;

private:
    void handleStart(const TgBot::Message::Ptr& message) const;
    void handlePic(const TgBot::Message::Ptr& message) const;

private:
    TgBot::Bot bot;
    TgBot::TgLongPoll longPoll;

    std::filesystem::path dataPath;

    const std::string picName = "ptitsa.png";
    const std::string picMime = "image/png";

    TgBot::InputFile::Ptr picInputFile;

private:
    std::unordered_map<std::string, TgBot::EventBroadcaster::MessageListener> commands =
    {
        { "start", [&](const auto& message) { handleStart(message); } },
        { "pic", [&](const auto& message) { handlePic(message); } }
    };
};
