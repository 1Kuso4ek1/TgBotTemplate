#include "handlers/StartHandler.hpp"

#include <print>

void StartHandler::handle(const TgBot::Message::Ptr& message)
{
    try
    {
        ui.sendStartMessage(message->chat->id);
    }
    catch(const std::exception& e)
    {
        std::println("'StartHandler::handle': {}", e.what());
    }
}
