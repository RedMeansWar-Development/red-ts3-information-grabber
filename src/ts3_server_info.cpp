#include <red_ts3_info/ts3_server_info.h>

using namespace std;
using namespace chrono;

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
int TS3ServerInfo::getServerCreatedAt() const { return getIntVar(VIRTUALSERVER_CREATED); }

string durationSince(long long seconds) {
    // Convert Unix timestamp (seconds since epoch) → time_point
    auto start = chrono::time_point<chrono::system_clock>{chrono::seconds{seconds}};
    auto end   = system_clock::now();

    // Convert to calendar days
    auto start_days = floor<days>(start);
    auto end_days   = floor<days>(end);

    year_month_day ymd_start{start_days};
    year_month_day ymd_end{end_days};

    // Calculate full calendar years
    years y = ymd_end.year() - ymd_start.year();

    if (ymd_end.month() < ymd_start.month() ||
       (ymd_end.month() == ymd_start.month() &&
        ymd_end.day()   < ymd_start.day()))
    {
        y -= years{1};
    }

    // Advance start by full years
    auto adjusted_start = sys_days{ymd_start + y};

    // Remaining duration
    auto remaining = end - adjusted_start;

    auto d = duration_cast<days>(remaining);
    remaining -= d;

    auto h = duration_cast<hours>(remaining);
    remaining -= h;

    auto m = duration_cast<minutes>(remaining);
    remaining -= m;

    auto s = duration_cast<std::chrono::seconds>(remaining);

    string result;

    if (y.count() > 0)
        result += to_string(y.count()) + " years, ";

    result +=
        to_string(d.count()) + " days, " +
        to_string(h.count()) + " hours, " +
        to_string(m.count()) + " minutes, " +
        to_string(s.count()) + " seconds";

    return result;
}

string TS3ServerInfo::formatInfo() const {
    ostringstream info;

    int maxDownloadQuota = getDownloadQuota();
    int maxUploadQuota = getUploadQuota();

    string maxDownloadQuotaStr = maxDownloadQuota == -1 ? "Unlimited" : to_string(maxDownloadQuota);
    string maxUploadQuotaStr = maxDownloadQuota == -1 ? "Unlimited" : to_string(maxUploadQuota);
    string uptimeStr = durationSince(getUptime());
    string createdAtStr = durationSince(getServerCreatedAt());

    info << "[b]Server Name:[/b] [color=#00ff00]" << getName() << "[/color]\n";
    info << "[b]Server UID:[/b] [color=#00ff00]" << getUID() << "[/color]\n";
    //info << "[b]Server IP Address:[/b] [color=#00ff00]" << getIPAddress() << "[/color]\n";
    info << "[b]Server Platform/Version:[/b] [color=#00ff00]" << getVersion() << " on " << getPlatform() << "[/color]\n";
    info << "[b]Clients Online:[/b] [color=#00ff00]" << getClientsOnline()
         << "/" << getMaxClients() << " (-" << getReservedClients() << " Reserved)[/color]\n";
    info << "[b]Channels:[/b] [color=#00ff00]" << getChannelsOnline() << "[/color]\n";
    info << "[b]Uptime (s):[/b] [color=#00ff00] " << getUptime() << " (" << uptimeStr << ")" << "[/color]\n";
    info << "[b]Created At (s):[/b] [color=#00ff00] " << getUptime() << " (" << createdAtStr << ")" << "[/color]\n";
    info << "[b]Download Quota:[/b] [color=#00ff00]" << maxDownloadQuotaStr << "[/color]\n";
    info << "[b]Upload Quota:[/b] [color=#00ff00]" << maxUploadQuotaStr << "[/color]\n";
    info << "[b]Security Level:[/b] [color=#00ff00]" << getSecurityLevel() << "[/color]\n";

    return info.str();
}