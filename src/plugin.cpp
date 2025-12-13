#include <cstdint>
#include <cstring>
#include <string>
#include <ts3_sdk/plugin_definitions.h>
#include <ts3_sdk/ts3_functions.h>
#include <red_ts3_info/plugin.h>
#include <red_ts3_info/info_collector.h>

struct TS3Functions ts3Functions;
static char pluginID[PLUGIN_ID_BUFSIZE];

extern "C" {
    PLUGIN_EXPORT int ts3plugin_apiVersion() { return PLUGIN_API_VERSION; }
    PLUGIN_EXPORT const char* ts3plugin_name() { return RED_TS3_PLUGIN_NAME; }
    PLUGIN_EXPORT const char* ts3plugin_version() { return RED_TS3_PLUGIN_VERSION; }
    PLUGIN_EXPORT const char* ts3plugin_author() { return "RedMeansWar"; }
    PLUGIN_EXPORT const char* ts3plugin_description() { return "Red TS3 Information Grabber Plugin"; }

    PLUGIN_EXPORT void ts3plugin_setFunctionPointers(const TS3Functions* funcs) {
        ts3Functions = *funcs;
    }

    PLUGIN_EXPORT int ts3plugin_init() {
        ts3Functions.logMessage("RTIG Plugin loaded!", LogLevel_INFO, "RTIG", 0);
        return 0;
    }

    PLUGIN_EXPORT void ts3plugin_shutdown() {}

    PLUGIN_EXPORT const char* ts3plugin_infoTitle(enum PluginItemType type, uint64) {
        switch (type) {
            case PLUGIN_SERVER:  return "RTIG Server Info";
            case PLUGIN_CHANNEL: return "RTIG Channel Info";
            case PLUGIN_CLIENT:  return "RTIG Client Info";
            default: return nullptr;
        }
    }

    PLUGIN_EXPORT const char* ts3plugin_infoDescription(enum PluginItemType type, uint64) {
        switch (type) {
            case PLUGIN_SERVER:  return "Extended server information";
            case PLUGIN_CHANNEL: return "Extended channel information";
            case PLUGIN_CLIENT:  return "Extended client information";
            default: return nullptr;
        }
    }

    PLUGIN_EXPORT void ts3plugin_infoData(uint64 serverConnectionHandlerID, uint64 id, enum PluginItemType type, char** data) {
        if (!data) return;

        std::string info;
        
        switch (type) {
            case PLUGIN_SERVER: info = red_ts3_info::InfoCollector::getServerInfo(serverConnectionHandlerID); break;
            case PLUGIN_CHANNEL: info = red_ts3_info::InfoCollector::getChannelInfo(serverConnectionHandlerID, id); break;
            case PLUGIN_CLIENT: info = red_ts3_info::InfoCollector::getClientInfo(serverConnectionHandlerID, id); break;
            default: info = "Unknown item type selected."; break;
        }

        *data = (char*)malloc(info.size() + 1);
        if (*data) {
            memcpy(*data, info.c_str(), info.size() + 1);
        }
    }
} // extern "C"
