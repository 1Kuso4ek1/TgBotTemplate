cmake_minimum_required(VERSION 3.10)
project(TelegramBot)

set(CMAKE_CXX_STANDARD 23)

add_executable(TelegramBot main.cpp
    src/core/Application.cpp
    include/core/Application.hpp
    src/view/BotUi.cpp
    include/view/BotUi.hpp
    src/handlers/StartHandler.cpp
    include/handlers/StartHandler.hpp
    src/handlers/EchoHandler.cpp
    include/handlers/EchoHandler.hpp)

target_link_libraries(TelegramBot TgBot)
target_include_directories(TelegramBot PUBLIC ${TgBot_INCLUDE_DIRECTORIES} include/)

add_subdirectory(libraries/tgbot-cpp)
