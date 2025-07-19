#pragma once
#include <tgbot/net/BoostHttpOnlySslClient.h>

class NoRetryHttpClient final : public TgBot::BoostHttpOnlySslClient
{
public:
    int getRequestMaxRetries() const override { return 0; }
    int getRequestBackoff() const override { return 0; }
};
