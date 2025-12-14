#pragma once

#include <cstdint>

#ifndef PLUGIN_H
#define PLUGIN_H

// plugin variables
#define RED_TS3_PLUGIN_NAME		"RTIG"
#define RED_TS3_PLUGIN_VERSION  "1.0.0"

// plugin version
#define PLUGIN_API_VERSION 26

// buffer sizes
#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
#define PLUGINS_EXPORTDLL __declspec(dllexport)
#else
#define PLUGINS_EXPORTDLL __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif
	// required functions
	PLUGINS_EXPORTDLL const char* ts3plugin_name();
	PLUGINS_EXPORTDLL const char* ts3plugin_version();
	PLUGINS_EXPORTDLL int         ts3plugin_apiVersion();
	PLUGINS_EXPORTDLL const char* ts3plugin_author();
	PLUGINS_EXPORTDLL const char* ts3plugin_description();
	PLUGINS_EXPORTDLL void        ts3plugin_setFunctionPointers(const struct TS3Functions funcs);
	PLUGINS_EXPORTDLL int         ts3plugin_init();
	PLUGINS_EXPORTDLL void        ts3plugin_shutdown();

	// optionals
	PLUGINS_EXPORTDLL void		  ts3plugin_infoData(uint64_t serverConnectionHandlerID, uint64_t id, enum PluginItemType type, char** data);
	PLUGINS_EXPORTDLL const char* ts3plugin_infoTitle(); // static title shown in the left column in the info frame
	PLUGINS_EXPORTDLL void		  ts3plugin_freeMemory(void* data);

#ifdef __cplusplus
}
#endif

#endif