cmake_minimum_required(VERSION 2.8.12)

set(project_name MyThreadProject)

project(${project_name})

# Add your source files
set(SOURCES
    src/CThread.h
    src/CThread.cpp
    examples/main.cpp)

# Specify the include directories 
include_directories(src)

# Platform-specific settings
if(WIN32)
    # Window-specific settings
    add_definitions(-DWIN32)
else()
    add_definitions(-DLINUX)
    find_package(Threads REQUIRED)
    set(EXTRA_LIBS ${CMAKE_THREAD_LIBS_INIT})
endif()

# Create the executable
add_executable(${project_name} ${SOURCES})

# Link platform-specific libraries
target_link_libraries(${project_name} ${EXTRA_LIBS})
