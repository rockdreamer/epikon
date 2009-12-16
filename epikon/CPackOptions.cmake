
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Epikon RTS Game")
set(CPACK_PACKAGE_VENDOR "Claudio Bantaloukas")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/gpl-3.0.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${EPIKON_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${EPIKON_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${EPIKON_MICRO_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Epikon")


if(CPACK_GENERATOR MATCHES "NSIS")
  # set the install/unistall icon used for the installer itself
  # There is a bug in NSI that does not handle full unix paths properly.
#  SET(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/client/epikon.ico")
#  SET(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/src/client/epikon.ico")
  # set the package header icon for MUI
#  SET(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/client/epikon-install.bmp")
  # tell cpack to create links to the doc files
  SET(CPACK_NSIS_MENU_LINKS
    "http://code.google.com/p/epikon" "Epikon Web Site"
    )
  # Use the icond from epikon for add-remove programs
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\epikon.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "Epikon")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\code.google.com\\\\p\\\\epikon")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\code.google.com\\\\p\\\\epikon")
  SET(CPACK_NSIS_CONTACT "rockdreamer@gmail.com")
  SET(CPACK_NSIS_DISPLAY_NAME "CMake @CMake_VERSION_MAJOR@.@CMake_VERSION_MINOR@ a cross-platform, open-source build system")
  SET(CPACK_NSIS_PACKAGE_NAME "CMake @CMake_VERSION_MAJOR@.@CMake_VERSION_MINOR@")
  SET(CPACK_NSIS_MODIFY_PATH ON)
endif(CPACK_GENERATOR MATCHES "NSIS")

if(CPACK_GENERATOR MATCHES "CygwinSource")
  # when packaging source make sure the .build directory is not included
    SET(CPACK_SOURCE_IGNORE_FILES
      "/CVS/" "/\\.build/" "/\\.svn/" "\\.swp$" "\\.#" "/#" "~$")
endif(CPACK_GENERATOR MATCHES "CygwinSource")

if("${CPACK_GENERATOR}" STREQUAL "PackageMaker")
    set(CPACK_PACKAGE_DEFAULT_LOCATION "/Applications")
endif("${CPACK_GENERATOR}" STREQUAL "PackageMaker")

  SET(CPACK_SOURCE_PACKAGE_FILE_NAME
    "epikon-$EPIKON_VERSION_NUMBER")
  IF(NOT DEFINED CPACK_SYSTEM_NAME)
      SET(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})
  ENDIF(NOT DEFINED CPACK_SYSTEM_NAME)
  IF(${CPACK_SYSTEM_NAME} MATCHES Windows)
      SET(CPACK_SYSTEM_NAME win32-${CMAKE_SYSTEM_PROCESSOR})
  ENDIF(${CPACK_SYSTEM_NAME} MATCHES Windows)
  IF(NOT DEFINED CPACK_PACKAGE_FILE_NAME)
    # if the CPACK_PACKAGE_FILE_NAME is not defined by the cache
    # default to source package - system, on cygwin system is not
    # needed
    IF(CYGWIN)
      SET(CPACK_PACKAGE_FILE_NAME "${CPACK_SOURCE_PACKAGE_FILE_NAME}")
    ELSE(CYGWIN)
      SET(CPACK_PACKAGE_FILE_NAME
        "${CPACK_SOURCE_PACKAGE_FILE_NAME}-${CPACK_SYSTEM_NAME}")
    ENDIF(CYGWIN)
  ENDIF(NOT DEFINED CPACK_PACKAGE_FILE_NAME)
  SET(CPACK_PACKAGE_CONTACT "rockdreamer@gmail.com")
  IF(UNIX)
    SET(CPACK_STRIP_FILES "bin/epikon;bin/epikonsrv")
    SET(CPACK_SOURCE_STRIP_FILES "")
    SET(CPACK_PACKAGE_EXECUTABLES "epikon" "Epikon" "epikonsrv" "Epikon Server")
  ENDIF(UNIX)

  SET(CPACK_NSIS_MODIFY_PATH ON)
