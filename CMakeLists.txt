project(Epikon)
cmake_minimum_required(VERSION 3.2.0)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

SET( EPIKON_MAJOR_VERSION 0 )
SET( EPIKON_MINOR_VERSION 1 )
SET( EPIKON_MICRO_VERSION 0 )
SET( EPIKON_BUILD_VERSION 0 )

set ( EPIKON_VERSION_STRING "${EPIKON_MAJOR_VERSION}.${EPIKON_MINOR_VERSION}.${EPIKON_MICRO_VERSION}")
set ( EPIKON_VERSION_NUMBER ${EPIKON_MAJOR_VERSION}.${EPIKON_MINOR_VERSION}.${EPIKON_MICRO_VERSION})

include(GetGitRevisionDescription)
git_describe(EPIKON_GIT_TAG --tags --dirty=-d)
if (EPIKON_GIT_TAG)
    set(EPIKON_VERSION_STRING "${EPIKON_VERSION_STRING} Build ${EPIKON_GIT_TAG}")
    set(EPIKON_VERSION_NUMBER ${EPIKON_VERSION_NUMBER}.${EPIKON_GIT_TAG})
    set(EPIKON_BUILD_VERSION ${EPIKON_GIT_TAG})
endif()
message ("Building epikon v${EPIKON_VERSION_STRING}")

ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
    endif(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t-")
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/epikondefs.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/epikondefs.h"
    IMMEDIATE
    @ONLY)

set(CMAKE_AUTOMOC ON)

add_subdirectory(protocol)
add_subdirectory(server)
add_subdirectory(client)
include(InstallRequiredSystemLibraries)

include(${PROJECT_SOURCE_DIR}/CPackOptions.cmake)
include(CPack)
