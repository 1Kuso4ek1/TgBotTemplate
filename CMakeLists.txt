cmake_minimum_required(VERSION 3.10)
project(TelegramBot)

set(CMAKE_CXX_STANDARD 23)

set(
    BOT_HEADERS

    include/core/Application.hpp
    include/view/BotUi.hpp
    include/handlers/StartHandler.hpp
    include/handlers/EchoHandler.hpp
)

set(
    BOT_SOURCES

    src/core/Application.cpp
    src/view/BotUi.cpp
    src/handlers/StartHandler.cpp
    src/handlers/EchoHandler.cpp

    src/main.cpp
)

add_subdirectory(libraries/tgbot-cpp)

add_executable(
    TelegramBot

    ${BOT_HEADERS}
    ${BOT_SOURCES}
)

target_link_libraries(TelegramBot TgBot)
target_include_directories(TelegramBot PUBLIC ${TgBot_INCLUDE_DIRECTORIES} include/ libraries/thread-pool/include)
