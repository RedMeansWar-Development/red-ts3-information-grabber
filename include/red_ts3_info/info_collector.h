#pragma once
#include <string>
#include <ts3_sdk/teamspeak/public_definitions.h>

using uint64 = uint64_t;

namespace red_ts3_info
{
    class InfoCollector
    {
    public:
        static std::string getClientInfo(uint64 serverConnectionHandlerID, uint64 clientID);
        static std::string getChannelInfo(uint64 serverConnectionHandlerID, uint64 channelID);
        static std::string getServerInfo(uint64 serverConnectionHandlerID);
    };
}
