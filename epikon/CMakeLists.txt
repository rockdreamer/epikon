project(Epikon)

cmake_minimum_required(VERSION 2.8.0)

SET( EPIKON_MAJOR_VERSION 0 )
SET( EPIKON_MINOR_VERSION 1 )
SET( EPIKON_MICRO_VERSION 0 )
SET( EPIKON_BUILD_VERSION 0 )

set ( EPIKON_VERSION_STRING "${EPIKON_MAJOR_VERSION}.${EPIKON_MINOR_VERSION}.${EPIKON_MICRO_VERSION}")
set ( EPIKON_VERSION_NUMBER ${EPIKON_MAJOR_VERSION}.${EPIKON_MINOR_VERSION}.${EPIKON_MICRO_VERSION})

if (EXISTS ${PROJECT_SOURCE_DIR}/.svn)
    find_package(Subversion)
    if (Subversion_FOUND)
        SUBVERSION_WC_INFO(${PROJECT_SOURCE_DIR} Epikon)
        set(EPIKON_VERSION_STRING "${EPIKON_VERSION_STRING} Build ${Epikon_WC_REVISION}")
        set(EPIKON_VERSION_NUMBER ${EPIKON_VERSION_NUMBER}.${Epikon_WC_REVISION})
        set(EPIKON_BUILD_VERSION ${Epikon_WC_REVISION})
    endif (Subversion_FOUND)
endif (EXISTS ${PROJECT_SOURCE_DIR}/.svn)
message ("Building epikon v${EPIKON_VERSION_STRING}")

include(InstallRequiredSystemLibraries)

add_subdirectory(src)

include(${PROJECT_SOURCE_DIR}/CPackOptions.cmake)
include(CPack)
