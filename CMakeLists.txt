cmake_minimum_required(VERSION 3.21)

project(red_ts3_information_grabber
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ensure shared libs work on Linux/macOS
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE RED_TS3_INFO_HEADERS
    "include/*.h"
    "include/red_ts3_info/*.h"
    "include/ts3_sdk/*.h"
)

file(GLOB_RECURSE RED_TS3_INFO_SOURCES
    "src/*.cpp"
)

add_library(red_ts3_info SHARED
    ${RED_TS3_INFO_SOURCES}
    ${RED_TS3_INFO_HEADERS}
)

target_include_directories(red_ts3_info
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ts3_sdk
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ts3_sdk/teamlog
)

target_compile_definitions(red_ts3_info
    PRIVATE
        TS3_PLUGIN
)

# -------------------------------------------------
# Platform-specific output configuration
# -------------------------------------------------

if (WIN32)
    set_target_properties(red_ts3_info PROPERTIES
        OUTPUT_NAME "ts3_red_info_grabber_win64"
        SUFFIX ".dll"
    )

elseif (APPLE)
    set_target_properties(red_ts3_info PROPERTIES
        OUTPUT_NAME "ts3_red_info_grabber_macos"
        SUFFIX ".dylib"
        MACOSX_RPATH ON
    )

elseif (UNIX)
    set_target_properties(red_ts3_info PROPERTIES
        OUTPUT_NAME "ts3_red_info_grabber_linux"
        SUFFIX ".so"
    )
endif()