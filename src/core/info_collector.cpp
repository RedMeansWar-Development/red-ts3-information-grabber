#include <sstream>
#include <red_ts3_info/info_collector.h>
#include <ts3_sdk/ts3_functions.h>
#include <ts3_sdk/teamspeak/public_errors.h>
#include <ts3_sdk/teamspeak/public_rare_definitions.h>

using namespace std;

extern struct TS3Functions ts3Functions;

namespace red_ts3_info
{
    string InfoCollector::getServerInfo(uint64 serverConnectionHandlerID) {
        ostringstream info;
        char* tmp = nullptr;
        int value = 0;

        info << "[b][color=#ff9900]--- SERVER INFO ---[/color][/b]\n";

        if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_UNIQUE_IDENTIFIER, &tmp) == ERROR_ok)
        {
            info << "[b]Server UID:[/b] " << tmp << "[/color]\n";
            ts3Functions.freeMemory(tmp);
        }

        if (ts3Functions.getServerVariableAsInt(serverConnectionHandlerID, VIRTUALSERVER_CHANNELS_ONLINE, &value) == ERROR_ok)
            info << "[b]Total Channels:[/b] [color=#33ccff]" << value << "[/color]\n";

        if (ts3Functions.getServerVariableAsInt(serverConnectionHandlerID, VIRTUALSERVER_CLIENTS_ONLINE, &value) == ERROR_ok)
            info << "[b]Current Queries:[/b] " << value << "[/color]\n";

        return info.str();
    }

    string InfoCollector::getChannelInfo(uint64 serverConnectionHandlerID, uint64 channelID) {
        ostringstream info;
        char* tmp = nullptr;
        int maxClients = 0;
        uint64 parentID = 0;

        info << "[b][color=#33ccff]--- CHANNEL INFO ---[/color][/b]\n";

        if (ts3Functions.getChannelVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_NAME, &tmp) == ERROR_ok)
        {
            info << "[b]Channel Name:[/b] [color=#00ffff]" << tmp << "[/color]\n";
            ts3Functions.freeMemory(tmp);
        }

        if (ts3Functions.getParentChannelOfChannel(serverConnectionHandlerID, channelID, &parentID) == ERROR_ok) {
            info << "[b]Parent Channel ID:[/b] [color=#00ffff]" << parentID << "[/color]\n";
            ts3Functions.freeMemory(tmp);
        }
        
        if (ts3Functions.getChannelVariableAsInt(serverConnectionHandlerID, channelID, CHANNEL_MAXCLIENTS, &maxClients) == ERROR_ok) {
            info << "[b]Max Clients:[/b] [color=#00ffff]" << maxClients << "[/color]\n";
            ts3Functions.freeMemory(tmp);
        }
        
        anyID* clients = nullptr;
        int clientCount = 0;
        if (ts3Functions.getClientList(serverConnectionHandlerID, &clients) == ERROR_ok && clients)
        {
            for (int i = 0; clients[i]; ++i)
            {
                uint64 clientChannelID = 0;
                if (ts3Functions.getChannelOfClient(serverConnectionHandlerID, clients[i], &clientChannelID) == ERROR_ok)
                {
                    if (clientChannelID == channelID) clientCount++;
                }
            }
            ts3Functions.freeMemory(clients);
        }

        info << "[b]Clients in Channel:[/b] [color=#00ffff]" << clientCount << "[/color]\n";

        // Channel ID
        info << "[b]Channel ID:[/b] [color=#00ffff]" << channelID << "[/color]\n";

        return info.str();
    }

    string InfoCollector::getClientInfo(uint64 serverConnectionHandlerID, uint64 clientID) {
        ostringstream info;
        char* tmp = nullptr;
        int dbID = 0;

        info << "[b][color=#99ff33]--- CLIENT INFO ---[/color][/b]\n";

        // Nickname
        if (ts3Functions.getClientVariableAsString(serverConnectionHandlerID, (anyID)clientID, CLIENT_NICKNAME, &tmp) == ERROR_ok)
        {
            info << "[b]Nickname:[/b] [color=#ff0000]" << tmp << "[/color]\n";
            ts3Functions.freeMemory(tmp);
        }

        // Unique ID
        if (ts3Functions.getClientVariableAsString(serverConnectionHandlerID, (anyID)clientID, CLIENT_UNIQUE_IDENTIFIER, &tmp) == ERROR_ok)
        {
            info << "[b]Unique ID:[/b] [color=#ff0000]" << tmp << "[/color]\n";
            ts3Functions.freeMemory(tmp);
        }

        // Database ID
        if (ts3Functions.getClientVariableAsInt(serverConnectionHandlerID, (anyID)clientID, CLIENT_DATABASE_ID, &dbID) == ERROR_ok) {
            info << "[b]Database ID:[/b] [color=#ff0000]" << dbID << "[/color]\n";
            ts3Functions.freeMemory(tmp);
        }

        // Optional: current channel
        uint64 clientChannelID = 0;
        if (ts3Functions.getChannelOfClient(serverConnectionHandlerID, (anyID)clientID, &clientChannelID) == ERROR_ok) {
            info << "[b]Current Channel ID:[/b] [color=#ff0000]" << clientChannelID << "[/color]\n";
            ts3Functions.freeMemory(tmp);
        }

        return info.str();
    }
}
