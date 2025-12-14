#include <red_ts3_info/common.h>
#include <red_ts3_info/plugin.h>
#include <red_ts3_info/ts3_client_info.h>
#include <red_ts3_info/ts3_server_info.h>
#include <red_ts3_info/ts3_channel_info.h>

using namespace std;

struct TS3Functions ts3Functions;
static char* pluginID = NULL;

#ifdef _WIN32
static int wcharToUtf8(const wchar_t* str, char** result)
{
    int outlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, 0, 0);
    *result = (char*)malloc(outlen);
    if (WideCharToMultiByte(CP_UTF8, 0, str, -1, *result, outlen, 0, 0) == 0) {
        *result = NULL;
        return -1;
    }
    return 0;
}
#endif // _WIN32

const char* ts3plugin_name() { return RED_TS3_PLUGIN_NAME; }
const char* ts3plugin_version() { return RED_TS3_PLUGIN_VERSION; }
int         ts3plugin_apiVersion() { return PLUGIN_API_VERSION; }
const char* ts3plugin_author() { return "RedMeansWar"; }
const char* ts3plugin_description() { return "A TeamSpeak 3 plugin that gives information about channels, server, and client"; }
void        ts3plugin_setFunctionPointers(const struct TS3Functions funcs) { ts3Functions = funcs; }

int ts3plugin_init() {
    printf("RTIG: Started\n");
    return 0;
}

void ts3plugin_shutdown() {
    printf("RTIG: Shutting down\n");

    if (pluginID) {
        free(pluginID);
        pluginID = NULL;
    }
}

string getServerInfo(uint64 serverConnectionHandlerID) {
    ostringstream info;
    
    info << "[b][color=#ff9900]--- SERVER INFO ---[/color][/b]\n";

    TS3ServerInfo server(serverConnectionHandlerID);
    info << server.formatInfo();

    return info.str();
}

string getClientInfo(uint64 serverConnectionHandlerID, uint64 clientID) {
    ostringstream info;

    info << "[b][color=#99ff33]--- CLIENT INFO ---[/color][/b]\n";
    
    TS3ClientInfo client(serverConnectionHandlerID, static_cast<anyID>(clientID));
    info << client.formatInfo();

    return info.str();
}

string getChannelInfo(uint64 serverConnectionHandlerID, uint64 channelID) {
    ostringstream info;

    info << "[b][color=#33ccff]--- CHANNEL INFO ---[/color][/b]\n";

    TS3ChannelInfo channel(serverConnectionHandlerID, static_cast<anyID>(channelID));
    info << channel.formatInfo();
    
    return info.str();
}

// text display
const char* ts3plugin_infoTitle() { return RED_TS3_PLUGIN_NAME; }
void        ts3plugin_freeMemory(void* data) { free(data); }

void ts3plugin_infoData(uint64 serverConnectionHandlerID, uint64 id, enum PluginItemType type, char** data) {
    string info;

    switch (type) {
        case PLUGIN_SERVER: info = getServerInfo(serverConnectionHandlerID); break;
        case PLUGIN_CLIENT: info = getClientInfo(serverConnectionHandlerID, id); break;
        case PLUGIN_CHANNEL: info = getChannelInfo(serverConnectionHandlerID, id); break;
        default: 
            printf("Invalid item type: %d\n", type);
            *data = nullptr;
            return;
    }

    *data = (char*)malloc((info.size() + 1) * sizeof(char)); // +1 for null terminator
    if(*data)
        strcpy(*data, info.c_str());
}