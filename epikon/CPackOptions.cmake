
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Epikon RTS Game")
set(CPACK_PACKAGE_VENDOR "Claudio Bantaloukas")
set(CPACK_PACKAGE_VERSION_MAJOR "${EPIKON_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${EPIKON_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${EPIKON_MICRO_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Epikon")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Epikon")
SET(CPACK_PACKAGE_CONTACT "rockdreamer@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/gpl-3.0.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")

SET(CPACK_SOURCE_PACKAGE_FILE_NAME "epikon-${EPIKON_VERSION_NUMBER}")
SET(CPACK_PACKAGE_FILE_NAME "${CPACK_SOURCE_PACKAGE_FILE_NAME}")

SET(CPACK_PACKAGE_EXECUTABLES "epikon" "Epikon" ${CPACK_PACKAGE_EXECUTABLES})
SET(CPACK_CREATE_DESKTOP_LINKS "epikon" ${CPACK_CREATE_DESKTOP_LINKS})

if (WIN32)
    set(CPACK_GENERATOR "NSIS")
endif()

if (APPLE)
    set(CPACK_GENERATOR "NSIS")
endif()

if(CPACK_GENERATOR MATCHES "NSIS")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-win32")
#  set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/client/epikon.ico")
#  set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/src/client/epikon.ico")
  # set the package header icon for MUI
#  set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/src/client/epikon-install.bmp")
  # tell cpack to create links to the doc files
  set(CPACK_NSIS_MENU_LINKS
    "http:\\\\\\\\code.google.com\\\\p\\\\epikon" "Epikon Web Site"
    )
  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\epikon.exe")
  set(CPACK_NSIS_DISPLAY_NAME "Epikon")
  set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\code.google.com\\\\p\\\\epikon")
  set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\code.google.com\\\\p\\\\epikon")
  set(CPACK_NSIS_CONTACT "rockdreamer@gmail.com")
  set(CPACK_NSIS_DISPLAY_NAME "Epikon RTS Game")
  set(CPACK_NSIS_PACKAGE_NAME "Epikon")
endif(CPACK_GENERATOR MATCHES "NSIS")

if("${CPACK_GENERATOR}" STREQUAL "PackageMaker")
    set(CPACK_PACKAGE_DEFAULT_LOCATION "/Applications")
endif("${CPACK_GENERATOR}" STREQUAL "PackageMaker")

if(UNIX)
    set(CPACK_STRIP_FILES "bin/epikon;bin/epikonsrv")
    set(CPACK_SOURCE_STRIP_FILES "")
    set(CPACK_PACKAGE_EXECUTABLES "epikon" "Epikon" "epikonsrv" "Epikon Server")
endif(UNIX)
