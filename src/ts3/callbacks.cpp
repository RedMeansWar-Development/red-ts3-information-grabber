#include <cstring>
#include <red_ts3_info/info_collector.h>
#include <ts3_sdk/plugin_definitions.h>

using namespace std;

void ts3plugin_infoData(uint64 serverConnectionHandlerID, uint64 id, enum PluginItemType type, char** data) {
	if (!data) return;

	string info;

	switch (type) {
		case PLUGIN_CLIENT: info = red_ts3_info::InfoCollector::getClientInfo(serverConnectionHandlerID, id); break;
		case PLUGIN_CHANNEL: info = red_ts3_info::InfoCollector::getChannelInfo(serverConnectionHandlerID, id); break;
		case PLUGIN_SERVER: info = red_ts3_info::InfoCollector::getServerInfo(serverConnectionHandlerID); break;
		default: info = "Unknown Type"; break;
	}

	*data = strdup(info.c_str()); // ts3 will free it
}