#pragma once

#include <cstdint>

#ifndef PLUGIN_H
#define PLUGIN_H

// -------------------------------------------------
// Plugin metadata
// -------------------------------------------------

#define RED_TS3_PLUGIN_NAME     "RTIG"
#define RED_TS3_PLUGIN_VERSION  "1.0.1"

// TeamSpeak plugin API version
#define PLUGIN_API_VERSION 26

// -------------------------------------------------
// Export / linkage macro
// -------------------------------------------------

#if defined(_WIN32)
    #define TS3_EXPORT extern "C" __declspec(dllexport)
#else
    #define TS3_EXPORT extern "C" __attribute__((visibility("default")))
#endif

// -------------------------------------------------
// Required TeamSpeak plugin functions
// -------------------------------------------------

TS3_EXPORT const char* ts3plugin_name();
TS3_EXPORT const char* ts3plugin_version();
TS3_EXPORT int         ts3plugin_apiVersion();
TS3_EXPORT const char* ts3plugin_author();
TS3_EXPORT const char* ts3plugin_description();
TS3_EXPORT void        ts3plugin_setFunctionPointers(const struct TS3Functions funcs);
TS3_EXPORT int         ts3plugin_init();
TS3_EXPORT void        ts3plugin_shutdown();

// -------------------------------------------------
// Optional info display
// -------------------------------------------------

TS3_EXPORT void        ts3plugin_infoData(
    uint64_t serverConnectionHandlerID,
    uint64_t id,
    enum PluginItemType type,
    char** data
);

TS3_EXPORT const char* ts3plugin_infoTitle();
TS3_EXPORT void        ts3plugin_freeMemory(void* data);

#endif // PLUGIN_H
