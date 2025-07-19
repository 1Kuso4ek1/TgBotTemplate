#pragma once
#include <tgbot/Bot.h>

class BotUI
{
public:
    explicit BotUI(TgBot::Bot& bot) : bot(bot) {}

    void sendStartMessage(int64_t chatId) const;
    void sendMarkdownMessage(int64_t chatId, const std::string& message) const;

private:
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

private:
    TgBot::Bot& bot;

private:
    std::unordered_map<std::string, TgBot::ReplyKeyboardMarkup::Ptr> replyKeyboards{};
    std::unordered_map<std::string, TgBot::InlineKeyboardMarkup::Ptr> inlineKeyboards{};
};
