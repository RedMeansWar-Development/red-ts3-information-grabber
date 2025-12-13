#pragma once

#define RED_TS3_PLUGIN_NAME        "RTIG"
#define RED_TS3_PLUGIN_VERSION     "1.0.0"

// TS3 API Version
#define PLUGIN_API_VERSION 26

// Buffer Sizes
#define PLUGIN_ID_BUFSIZE 512
#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

#ifdef _WIN32
    #define PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
    #define PLUGIN_EXPORT extern "C"
#endif
