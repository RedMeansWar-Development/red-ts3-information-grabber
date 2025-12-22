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
    auto start = chrono::time_point<chrono::system_clock>{chrono::seconds{seconds}};
    auto end   = chrono::system_clock::now();

    auto start_days = chrono::floor<chrono::days>(start);
    auto end_days   = chrono::floor<chrono::days>(end);

    chrono::year_month_day ymd_start{start_days};
    chrono::year_month_day ymd_end{end_days};

    // Calculate full years
    chrono::years y = ymd_end.year() - ymd_start.year();
    if (ymd_end.month() < ymd_start.month() || 
        (ymd_end.month() == ymd_start.month() && ymd_end.day() < ymd_start.day())) {
        y -= chrono::years{1};
    }

    // Calculate months after full years
    auto adjusted_start = chrono::sys_days{ymd_start + y};
    chrono::year_month_day ymd_adjusted{adjusted_start};

    chrono::months m = ymd_end.month() - ymd_adjusted.month();
    if (ymd_end.day() < ymd_adjusted.day()) {
        m -= chrono::months{1};
    }
    if (m.count() < 0) {
        m += chrono::months{12};
    }

    // Remaining days
    auto adjusted_start2 = chrono::sys_days{ymd_adjusted + m};
    auto remaining = end_days - adjusted_start2;
    auto d = remaining.count();

    // Remaining time (hours, minutes, seconds)
    auto leftover_seconds = chrono::duration_cast<chrono::seconds>(end - (adjusted_start2 + chrono::days{d}));
    auto h = chrono::duration_cast<chrono::hours>(leftover_seconds);
    leftover_seconds -= h;
    auto min = chrono::duration_cast<chrono::minutes>(leftover_seconds);
    leftover_seconds -= min;
    auto s = leftover_seconds;

    // Build string
    ostringstream result;
    if (y.count() > 0) result << y.count() << " years, ";
    if (m.count() > 0) result << m.count() << " months, ";
    if (d > 0) result << d << " days, ";
    result << h.count() << " hours, " << min.count() << " minutes, " << s.count() << " seconds";

    return result.str();
}

string formatDuration(long long seconds) {
    auto d = seconds / (24 * 3600);
    seconds %= (24 * 3600);
    
    auto h = seconds / 3600;
    seconds %= 3600;
    
    auto m = seconds / 60;
    auto s = seconds % 60;
    
    string result;
    
    if (d > 0)
        result += to_string(d) + " days, ";
    
    result += to_string(h) + " hours, " +
              to_string(m) + " minutes, " +
              to_string(s) + " seconds";
    
    return result;
}

string TS3ServerInfo::formatInfo() const {
    ostringstream info;

    int maxDownloadQuota = getDownloadQuota();
    int maxUploadQuota = getUploadQuota();

    string maxDownloadQuotaStr = maxDownloadQuota == -1 ? "Unlimited" : to_string(maxDownloadQuota);
    string maxUploadQuotaStr = maxUploadQuota == -1 ? "Unlimited" : to_string(maxUploadQuota);  // Fixed: was checking maxDownloadQuota
    string uptimeStr = formatDuration(getUptime());  // Fixed: use formatDuration instead
    string createdAtStr = durationSince(getServerCreatedAt());  // This one is correct as-is

    info << "[b]Server Name:[/b] [color=#00ff00]" << getName() << "[/color]\n";
    info << "[b]Server UID:[/b] [color=#00ff00]" << getUID() << "[/color]\n";
    info << "[b]Server Platform/Version:[/b] [color=#00ff00]" << getVersion() << " on " << getPlatform() << "[/color]\n";
    info << "[b]Clients Online:[/b] [color=#00ff00]" << getClientsOnline()
         << "/" << getMaxClients() << " (-" << getReservedClients() << " Reserved)[/color]\n";
    info << "[b]Channels:[/b] [color=#00ff00]" << getChannelsOnline() << "[/color]\n";
    info << "[b]Uptime (s):[/b] [color=#00ff00]" << getUptime() << " (" << uptimeStr << ")" << "[/color]\n";
    info << "[b]Server Age:[/b] [color=#00ff00]" << durationSince(getServerCreatedAt()) << "[/color]\n"; // Fixed: was calling getUptime()
    info << "[b]Download Quota:[/b] [color=#00ff00]" << maxDownloadQuotaStr << "[/color]\n";
    info << "[b]Upload Quota:[/b] [color=#00ff00]" << maxUploadQuotaStr << "[/color]\n";
    info << "[b]Security Level:[/b] [color=#00ff00]" << getSecurityLevel() << "[/color]\n";

    return info.str();
}