#pragma once

#include <string>
#include <sstream>

#include <teamspeak/public_definitions.h>
#include <teamspeak/public_errors.h>
#include <teamspeak/public_errors_rare.h>
#include <teamspeak/public_rare_definitions.h>
#include <ts3_functions.h>

class TS3ClientInfo {
    public: 
        TS3ClientInfo(uint64 serverConnectionHandlerID, anyID clientID);

        std::string getNickname() const;
        std::string getUniqueID() const;
        int         getDatabaseID() const;
        bool        isDefaultChannel() const;
        int         getCurrentChannelID() const;
        std::string formatInfo() const;

    private:
        uint64 serverConnectionHandlerID;
        anyID clientID;

        std::string getStringVar(size_t flag) const;
        int         getIntVar(size_t flag) const;
        uint64      getChannelVar() const;
};
