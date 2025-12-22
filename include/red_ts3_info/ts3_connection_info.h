#pragma once 

#include <string>
#include <sstream>

#include <teamspeak/public_definitions.h>
#include <teamspeak/public_errors.h>
#include <teamspeak/public_errors_rare.h>
#include <teamspeak/public_rare_definitions.h>
#include <ts3_functions.h>

class TS3ConnectionInfo {
    public:
        TS3ConnectionInfo(uint64 serverConnectionHandlerID);

        std::string getClientConnectionIP() const;
        std::string formatInfo() const;

    private:
        uint64 serverConnectionHandlerID;
        anyID clientID;

        std::string getStringVar(size_t flag) const;
};