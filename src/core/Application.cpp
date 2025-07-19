#include "core/Application.hpp"
#include "core/Constants.hpp"

#include "handlers/EchoHandler.hpp"
#include "handlers/StartHandler.hpp"

#include <print>

Application::Application()
    : bot(Env::token, httpClient),
      longPoll(bot, 1, 30),
      ui(bot)
{
    startHandler = std::make_unique<StartHandler>(ui);
    echoHandler = std::make_unique<EchoHandler>(ui);

    setupCommands();
    setupCallbackQueries();
}

void Application::run()
{
    while(true)
    {
        try
        {
            std::println("Bot name: {}", bot.getApi().getMe()->firstName);

            while(true)
                longPoll.start();
        }
        catch(const std::exception& e)
        {
            std::println("'Application::run': {}", e.what());
        }
    }
}

void Application::handleAny(const TgBot::Message::Ptr& message) const
{
    if(message->text.front() == '/')
        return;

    echoHandler->handle(message);
}

void Application::setupCommands()
{
    bot.getEvents().onAnyMessage([&](const auto& message) { handleAny(message); });

    for(const auto& [command, func] : commands)
        bot.getEvents().onCommand(command, func);
}

void Application::setupCallbackQueries()
{
    bot.getEvents().onCallbackQuery([&](const auto& query)
    {
        for(const auto& [name, callback] : callbacks)
        {
            if(query->data.starts_with(name))
                callback(query);
        }
    });
}
