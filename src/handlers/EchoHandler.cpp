#include "handlers/EchoHandler.hpp"

#include <print>

void EchoHandler::handle(const TgBot::Message::Ptr& message)
{
    try
    {
        ui.sendMarkdownMessage(message->chat->id, message->text);
    }
    catch(const std::exception& e)
    {
        std::println("'EchoHandler::handle': {}", e.what());
    }
}
