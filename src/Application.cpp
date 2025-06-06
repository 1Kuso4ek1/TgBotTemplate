#include "Application.hpp"

#include <print>

Application::Application()
    : bot(getenv("TOKEN")), longPoll(bot)
{
    setupCommands();
    setupCallbackQueries();
    setupKeyboards();
}

void Application::run()
{
    try
    {
        std::println("Bot name: {}", bot.getApi().getMe()->firstName);

        while(true)
            longPoll.start();
    }
    catch(TgBot::TgException& e)
    {
        std::println("Exception: {}", e.what());
    }
}

void Application::handleAny(const TgBot::Message::Ptr& message) const
{
    if(message->text.front() == '/')
        return;

    bot.getApi().sendMessage(
        message->chat->id, message->text, {}, {}, {}, "Markdown"
    );
}

void Application::handleStart(const TgBot::Message::Ptr& message) const
{
    bot.getApi().sendMessage(
        message->chat->id, "Hello World!", {}, {}, {}, "Markdown"
    );
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
            if(StringTools::startsWith(query->data, name))
                callback(query);
        }
    });
}

void Application::setupKeyboards()
{
    setupReplyKeyboards();
    setupInlineKeyboards();
}

void Application::setupReplyKeyboards() {}

void Application::setupInlineKeyboards() {}

void Application::createReplyKeyboard(
    const std::vector<std::vector<std::string>>& layout,
    const TgBot::ReplyKeyboardMarkup::Ptr& keyboard
)
{
    for(const auto& i : layout)
    {
        std::vector<TgBot::KeyboardButton::Ptr> row;
        row.reserve(i.size());

        for(const auto& j : i)
            row.push_back(std::make_shared<TgBot::KeyboardButton>(j));

        keyboard->keyboard.push_back(row);
    }
}

void Application::createInlineKeyboard(
    const std::vector<std::vector<std::string>>& layout,
    const TgBot::InlineKeyboardMarkup::Ptr& keyboard
)
{
    for(const auto& i : layout)
    {
        std::vector<TgBot::InlineKeyboardButton::Ptr> row;
        row.reserve(i.size());

        for(const auto& j : i)
            row.push_back(std::make_shared<TgBot::InlineKeyboardButton>(j, "", j));

        keyboard->inlineKeyboard.push_back(row);
    }
}
