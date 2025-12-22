cmake_minimum_required(VERSION 3.21)

project(rtigrmation_grabber
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ensure shared libs work on Linux/macOS
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE RTIG_HEADERS
    "include/*.h"
    "include/rtig/*.h"
    "include/ts3_sdk/*.h"
)

file(GLOB_RECURSE RTIG_SOURCES
    "src/*.cpp"
)

add_library(rtig SHARED
    ${RTIG_SOURCES}
    ${RTIG_HEADERS}
)

target_include_directories(rtig
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ts3_sdk
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ts3_sdk/teamlog
)

target_compile_definitions(rtig
    PRIVATE
        TS3_PLUGIN
)

# -------------------------------------------------
# Platform-specific output configuration
# -------------------------------------------------

if (WIN32)
    set_target_properties(rtig PROPERTIES
        OUTPUT_NAME "rtig_win64"
        SUFFIX ".dll"
    )

elseif (APPLE)
    set_target_properties(rtig PROPERTIES
        OUTPUT_NAME "rtig_macos"
        SUFFIX ".dylib"
        MACOSX_RPATH ON
    )

elseif (UNIX)
    set_target_properties(rtig PROPERTIES
        OUTPUT_NAME "rtig_linux"
        SUFFIX ".so"
    )
endif()