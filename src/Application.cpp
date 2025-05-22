#include "Application.hpp"

#include <print>

Application::Application()
    : bot(getenv("TOKEN")), longPoll(bot), dataPath("../data")
{}

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

void Application::setupReplyKeyboards()
{
    createReplyKeyboard({ { "/start", "/pic" } }, replyKeyboards["menu"]);
}

void Application::setupInlineKeyboards()
{
    createInlineKeyboard({ { "Next picture" } }, inlineKeyboards["pic"]);
}

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

void Application::handleAny(const TgBot::Message::Ptr& message) const
{
    if(message->text.front() == '/')
        return;

    bot.getApi().sendMessage(
        message->chat->id, message->text, {}, {},
        replyKeyboards.at("menu"), "Markdown"
    );
}

void Application::handleStart(const TgBot::Message::Ptr& message) const
{
    bot.getApi().sendMessage(
        message->chat->id, "Hello World!", {}, {},
        replyKeyboards.at("menu"), "Markdown"
    );
}

void Application::handlePic(const TgBot::Message::Ptr& message) const
{
    bot.getApi().sendPhoto(
        message->chat->id, picInputFile, "Here's your picture!", {},
        inlineKeyboards.at("pic"), "Markdown"
    );
}

void Application::handleNextPicture(const TgBot::CallbackQuery::Ptr& query) const
{
    bot.getApi().sendPhoto(
        query->message->chat->id, picInputFile, "Here's another picture!", {},
        inlineKeyboards.at("pic"), "Markdown"
    );
}
