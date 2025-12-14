#pragma once

#include <string>
#include <sstream>

#include <teamspeak/public_definitions.h>
#include <teamspeak/public_errors.h>
#include <teamspeak/public_errors_rare.h>
#include <teamspeak/public_rare_definitions.h>
#include <ts3_functions.h>


class TS3ServerInfo {
    public:
        explicit TS3ServerInfo(uint64 serverConnectionHandlerID);

        std::string getName() const;
        std::string getUID() const;
        std::string getPlatformVersion() const;
        int         getMaxClients() const;
        int         getClientsOnline() const;
        int         getChannelsOnline() const;
        int         getUptime() const;
        int         getDownloadQuota() const;
        int         getUploadQuota() const;
        int         getSecurityLevel() const;

        std::string formatInfo() const;
    
    private:
        uint64 schID;

        std::string getStringVar(size_t flag) const;
        int         getIntVar(size_t flag) const;
};