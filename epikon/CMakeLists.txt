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


set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Epikon RTS Game")
set(CPACK_PACKAGE_VENDOR "Claudio Bantaloukas")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/gpl-3.0.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${EPIKON_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${EPIKON_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${EPIKON_MICRO_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Epikon")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
#  SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
#  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\epikon.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Epikon")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\code.google.com\\\\p\\\\epikon")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\code.google.com\\\\p\\\\epikon")
  SET(CPACK_NSIS_CONTACT "rockdreamer@gmail.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_STRIP_FILES "bin/epikon")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "epikon" "Epikon")
INCLUDE(CPack)
