#include <red_ts3_info/ts3_client_info.h>

using namespace std;

extern struct TS3Functions ts3Functions;

TS3ClientInfo::TS3ClientInfo(uint64 schID, anyID cID) : serverConnectionHandlerID(schID), clientID(cID) {}

std::string TS3ClientInfo::getStringVar(size_t flag) const {
    char* tmp = nullptr;
    string result;

    if (ts3Functions.getClientVariableAsString(serverConnectionHandlerID, clientID, flag, &tmp) == ERROR_ok) {
        result = tmp;
        ts3Functions.freeMemory(tmp);
    }

    return result;
}

int TS3ClientInfo::getIntVar(size_t flag) const {
    int val = 0;
    ts3Functions.getClientVariableAsInt(serverConnectionHandlerID, clientID, flag, &val);
    return val;
}

uint64 TS3ClientInfo::getChannelVar() const {
    uint64 channelID = 0;
    ts3Functions.getChannelOfClient(serverConnectionHandlerID, clientID, &channelID);
    return channelID;
}

string TS3ClientInfo::getNickname() const {
    return getStringVar(CLIENT_NICKNAME);
}

int TS3ClientInfo::getDatabaseID() const {
    return getIntVar(CLIENT_DATABASE_ID);
}

string TS3ClientInfo::getUniqueID() const {
    return getStringVar(CLIENT_UNIQUE_IDENTIFIER);
}

string TS3ClientInfo::formatInfo() const {
    ostringstream info;
    info << "[b]Nickname:[/b] [color=#ff0000]" << getNickname() << "[/color]\n";
    info << "[b]Unique ID:[/b] [color=#ff0000]" << getUniqueID() << "[/color]\n";
    info << "[b]Database ID:[/b] [color=#ff0000]" << getDatabaseID() << "[/color]\n";
    info << "[b]Current Channel ID:[/b] [color=#ff0000]" << getChannelVar() << "[/color]\n";
    return info.str();
}