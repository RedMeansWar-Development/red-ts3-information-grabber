#pragma once

#if defined(_WIN32)
    #define TS3_EXPORT extern "C" __declspec(dllexport)
#elif defined(__APPLE__) || defined(__linux__)
    #define TS3_EXPORT extern "C" __attribute__((visibility("default")))
#else
    #define TS3_EXPORT extern "C"
#endif
