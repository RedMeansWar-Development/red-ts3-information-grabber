#include <red_ts3_info/ts3_connection_info.h>

using namespace std;

extern struct TS3Functions ts3Functions;

TS3ConnectionInfo::TS3ConnectionInfo(uint64 schID) : serverConnectionHandlerID(schID) {}

string TS3ConnectionInfo::getStringVar(size_t flag) const {
    char* tmp = nullptr;
    string result;

    if (ts3Functions.getConnectionVariableAsString(serverConnectionHandlerID, clientID, flag, &tmp) == ERROR_ok) {
        result = tmp;
        ts3Functions.freeMemory(tmp);
    }

    return result;
}

string TS3ConnectionInfo::getClientConnectionIP() const { return getStringVar(CONNECTION_CLIENT_IP); }

string TS3ConnectionInfo::formatInfo() const {
    ostringstream info;
    info << "[b]Nickname:[/b] [color=##00b3ff]" << getClientConnectionIP() << "[/color]\n";
    return info.str();
}