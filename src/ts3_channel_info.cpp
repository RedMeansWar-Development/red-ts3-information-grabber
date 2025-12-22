#include <red_ts3_info/ts3_channel_info.h>

using namespace std;

extern TS3Functions ts3Functions;
                
TS3ChannelInfo::TS3ChannelInfo(uint64 serverConnectionHandlerID, uint64 channelID) : schID(serverConnectionHandlerID), chID(channelID) {}

string TS3ChannelInfo::getStringVar(size_t flag) const {
    char* tmp = nullptr;
    string result;

    if (ts3Functions.getChannelVariableAsString(schID, chID, flag, &tmp) == ERROR_ok && tmp) {
        result = tmp;
        ts3Functions.freeMemory(tmp);
    }

    return result;
}

int TS3ChannelInfo::getIntVar(size_t flag) const {
    int val = 0;
    ts3Functions.getChannelVariableAsInt(schID, chID, flag, &val);
    return val;
}

uint64 TS3ChannelInfo::getUInt64Var(size_t flag) const {
    uint64 val = 0;
    ts3Functions.getChannelVariableAsUInt64(schID, chID, flag, &val);
    return val;
}

string TS3ChannelInfo::getName() const { return getStringVar(CHANNEL_NAME); }

int TS3ChannelInfo::getMaxClients() const { return getIntVar(CHANNEL_MAXCLIENTS); }
int TS3ChannelInfo::getNeededTalkPower() const { return getIntVar(CHANNEL_NEEDED_TALK_POWER); }
int TS3ChannelInfo::getChannelID() const { return getIntVar(CHANNEL_UNIQUE_IDENTIFIER); }
int TS3ChannelInfo::getChannelIconID() const { return getIntVar(CHANNEL_ICON_ID); }

bool TS3ChannelInfo::isPasswordProtected() const { return getIntVar(CHANNEL_FLAG_PASSWORD) != 0; }


uint64 TS3ChannelInfo::getParentChannelID() const {
    uint64 parentID = 0;

    ts3Functions.getParentChannelOfChannel(schID, chID, &parentID);
    return parentID;
}

bool TS3ChannelInfo::isDefaultChannel() const { return getParentChannelID() == 0; }

string TS3ChannelInfo::formatInfo() const {
    ostringstream info;

    int maxClients = getMaxClients();
    string maxClientsStr = (maxClients == -1) ? "Unlimited" : to_string(maxClients);

    info << "[b]Channel ID:[/b] [color=#00ffff]" << getChannelID() << "[/color]\n";
    info << "[b]Channel Name:[/b] [color=#00ffff]" << getName() << "[/color]\n";
    info << "[b]Max Clients:[/b] [color=#00ffff]" << maxClientsStr << "[/color]\n";
    info << "[b]Channel Parent ID:[/b] [color=#00ffff]" << getNeededTalkPower() << "[/color]\n";
    info << "[b]Talk Power Required:[/b] [color=#00ffff]" << getNeededTalkPower() << "[/color]\n";
    info << "[b]Is Default Channel:[/b] [color=#00ffff]" << isDefaultChannel() << "[/color]\n";
    info << "[b]Password Protected:[/b] [color=#00ffff]"
         << (isPasswordProtected() ? "Yes" : "No") << "[/color]\n";
    info << "[b]Channel Icon ID:[/b] [color=#00ffff]" << getChannelIconID() << "[/color]\n";

    return info.str();
}