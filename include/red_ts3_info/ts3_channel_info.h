#pragma once
#pragma once

#include <string>
#include <sstream>

#include <teamspeak/public_definitions.h>
#include <teamspeak/public_errors.h>
#include <teamspeak/public_errors_rare.h>
#include <teamspeak/public_rare_definitions.h>
#include <ts3_functions.h>
 
class TS3ChannelInfo {
    public:
        TS3ChannelInfo(uint64 serverConnectionHandlerID, uint64 channelID);

        std::string getName() const;
        int         getMaxClients() const;
        int         getNeededTalkPower() const;
        bool        isPasswordProtected() const;
        int         getChannelID() const;
        int         getChannelIconID() const;
        uint64      getParentChannelID() const;
        bool        isDefaultChannel() const;
        std::string formatInfo() const;

    private:
        uint64 schID;
        uint64 chID;
        
        std::string getStringVar(size_t flag) const;
        int         getIntVar(size_t flag) const;
        uint64      getUInt64Var(size_t flag) const;
};