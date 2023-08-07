cmake_minimum_required(VERSION 3.12)

project(BITest)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the BITFramework library
file(GLOB_RECURSE BITFRAMEWORK_SOURCES
    BITFramework/src/*.cpp BITFramework/src/*.h
)

add_library(BITFramework STATIC ${BITFRAMEWORK_SOURCES})
target_include_directories(BITFramework PUBLIC BITFramework/src/)

# Precompiled header settings
target_precompile_headers(BITFramework PUBLIC BITFramework/src/bitpch.h)

# Add the BITGame executable
file(GLOB_RECURSE BITGAME_SOURCES
    BITGame/src/*.cpp BITGame/src/*.h
)

add_executable(BITGame ${BITGAME_SOURCES})
target_link_libraries(BITGame PRIVATE BITFramework)
target_include_directories(BITGame PUBLIC BITGame/src/)

# Optionally, set the output directories for built files
set_target_properties(BITFramework PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

set_target_properties(BITGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Set BITGame as the startup project for Visual Studio
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BITGame)
endif()