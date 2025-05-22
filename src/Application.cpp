#include "Application.hpp"

#include <print>

Application::Application()
    : bot(getenv("TOKEN")), longPoll(bot), dataPath("../data")
{}

void Application::setupCommands()
{
    for(const auto& [command, func] : commands)
        bot.getEvents().onCommand(command, func);
}

void Application::loadData()
{
    try
    {
        picInputFile = TgBot::InputFile::fromFile(dataPath / picName, picMime);
    }
    catch(const std::exception& e)
    {
        std::println("Error loading data from \"{}\": {}", (dataPath / picName).string(), e.what());
    }
}

void Application::run() const
{
    try
    {
        std::println("Bot name: {}", bot.getApi().getMe()->firstName);
        TgBot::TgLongPoll longPoll(bot);

        while(true)
            longPoll.start();
    }
    catch(TgBot::TgException& e)
    {
        std::println("Exception: {}", e.what());
    }
}

void Application::handleStart(const TgBot::Message::Ptr& message) const
{
    bot.getApi().sendMessage(message->chat->id, "Hello World!");
}

void Application::handlePic(const TgBot::Message::Ptr& message) const
{
    bot.getApi().sendPhoto(message->chat->id, picInputFile, "Here's your picture!");
}
