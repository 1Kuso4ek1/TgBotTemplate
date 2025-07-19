#include "view/BotUi.hpp"

#include "core/Constants.hpp"

void BotUI::sendStartMessage(const int64_t chatId) const
{
    bot.getApi().sendMessage(chatId, Strings::helloWorld, {}, {}, {}, "Markdown");
}

void BotUI::sendMarkdownMessage(const int64_t chatId, const std::string& message) const
{
    bot.getApi().sendMessage(chatId, message, {}, {}, {}, "Markdown");
}

void BotUI::setupReplyKeyboards() {}

void BotUI::setupInlineKeyboards() {}

void BotUI::createReplyKeyboard(
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

void BotUI::createInlineKeyboard(
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
