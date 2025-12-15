#include <red_ts3_info/ts3_server_info.h>

using namespace std;

extern TS3Functions ts3Functions;
 
TS3ServerInfo::TS3ServerInfo(uint64 serverConnectionHandlerID) : schID(serverConnectionHandlerID) {}

string TS3ServerInfo::getStringVar(size_t flag) const {
    char* tmp = nullptr;
    string result;

    if (ts3Functions.getServerVariableAsString(schID, flag, &tmp) == ERROR_ok && tmp) {
        result = tmp;
        ts3Functions.freeMemory(tmp);
    }

    return result;
}

int TS3ServerInfo::getIntVar(size_t flag) const {
    int val = 0;
    ts3Functions.getServerVariableAsInt(schID, flag, &val);
    return val;
}

string TS3ServerInfo::getName() const { return getStringVar(VIRTUALSERVER_NAME); }
string TS3ServerInfo::getUID() const { return getStringVar(VIRTUALSERVER_UNIQUE_IDENTIFIER); }
string TS3ServerInfo::getPlatform() const { return getStringVar(VIRTUALSERVER_PLATFORM); }
string TS3ServerInfo::getVersion() const { return getStringVar(VIRTUALSERVER_VERSION); }
string TS3ServerInfo::getIPAddress() const { return getStringVar(VIRTUALSERVER_IP); }
string TS3ServerInfo::getWelcomeMessage() const { return getStringVar(VIRTUALSERVER_WELCOMEMESSAGE); }

int TS3ServerInfo::getMaxClients() const { return getIntVar(VIRTUALSERVER_MAXCLIENTS); }
int TS3ServerInfo::getClientsOnline() const { return getIntVar(VIRTUALSERVER_CLIENTS_ONLINE); }
int TS3ServerInfo::getChannelsOnline() const { return getIntVar(VIRTUALSERVER_CHANNELS_ONLINE); }
int TS3ServerInfo::getUptime() const { return getIntVar(VIRTUALSERVER_UPTIME); }
int TS3ServerInfo::getDownloadQuota() const { return getIntVar(VIRTUALSERVER_DOWNLOAD_QUOTA); }
int TS3ServerInfo::getUploadQuota() const { return getIntVar(VIRTUALSERVER_UPLOAD_QUOTA); }
int TS3ServerInfo::getSecurityLevel() const { return getIntVar(VIRTUALSERVER_NEEDED_IDENTITY_SECURITY_LEVEL); }
int TS3ServerInfo::getReservedClients() const { return getIntVar(VIRTUALSERVER_RESERVED_SLOTS); }

string TS3ServerInfo::formatInfo() const {
    ostringstream info;

    int maxDownloadQuota = getDownloadQuota();
    int maxUploadQuota = getUploadQuota();

    string maxDownloadQuotaStr = maxDownloadQuota == -1 ? "Unlimited" : to_string(maxDownloadQuota);
    string maxUploadQuotaStr = maxDownloadQuota == -1 ? "Unlimited" : to_string(maxUploadQuota);

    info << "[b]Server Name:[/b] [color=#00ff00]" << getName() << "[/color]\n";
    info << "[b]Server UID:[/b] [color=#00ff00]" << getUID() << "[/color]\n";
    //info << "[b]Server IP Address:[/b] [color=#00ff00]" << getIPAddress() << "[/color]\n";
    info << "[b]Server Platform/Version:[/b] [color=#00ff00]" << getVersion() << " on " << getPlatform() << "[/color]\n";
    info << "[b]Clients Online:[/b] [color=#00ff00]" << getClientsOnline()
         << "/" << getMaxClients() << " (-" << getReservedClients() << " Reserved)[/color]\n";
    info << "[b]Channels:[/b] [color=#00ff00]" << getChannelsOnline() << "[/color]\n";
    info << "[b]Uptime (s):[/b] [color=#00ff00]" << getUptime() << "[/color]\n";
    info << "[b]Download Quota:[/b] [color=#00ff00]" << maxDownloadQuotaStr << "[/color]\n";
    info << "[b]Upload Quota:[/b] [color=#00ff00]" << maxUploadQuotaStr << "[/color]\n";
    info << "[b]Security Level:[/b] [color=#00ff00]" << getSecurityLevel() << "[/color]\n";

    return info.str();
}