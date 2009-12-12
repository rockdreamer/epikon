project(Epikon)

cmake_minimum_required(VERSION 2.8.0)

SET( EPIKON_MAJOR_VERSION 0 )
SET( EPIKON_MINOR_VERSION 1 )
SET( EPIKON_MICRO_VERSION 0 )
SET( EPIKON_BUILD_VERSION 0 )

set(epikon_SRCS
    epikonmainwindow.cpp 
    epikongame.cpp 
    epikonplayer.cpp 
    epikonplanet.cpp 
    epikongamescene.cpp 
    epikonplanetitem.cpp 
    epikonattack.cpp 
    epikonshipitem.cpp 
    epikonserver.cpp 
    epikonconnectionmanager.cpp 
    epikonclient.cpp
    main.cpp
)

set(epikon_HDRS
    epikonplanetitem.h
    epikonconnectionmanager.h
)

set(epikon_MOC_HDRS
    epikonmainwindow.h
    epikongame.h 
    epikonplayer.h 
    epikonplanet.h 
    epikongamescene.h 
    epikonattack.h 
    epikonshipitem.h 
    epikonserver.h 
    epikonclient.h
)

set(epikon_UIS
    epikonmainwindow.ui
)

set(epikon_RSRCS
    resources.qrc
)

# ADD_DEFINITIONS( "-Wall -ansi" )
# ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

set(BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)
if(WIN32)
    set ( LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin )
    set ( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin )
    set ( LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)
else()
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(LIB_SUFFIX "")
    else(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(LIB_SUFFIX 64)
    endif(CMAKE_SIZEOF_VOID_P EQUAL 4)

    set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})
    set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib${LIB_SUFFIX})
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
endif()

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
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt4 4.6.0 COMPONENTS QtCore QtGui QtNetwork QtSvg Phonon REQUIRED)
set(QT_USE_QTMAIN 1)
include(${QT_USE_FILE})

QT4_WRAP_CPP(epikon_MOC_SRCS ${epikon_MOC_HDRS})
QT4_WRAP_UI(epikon_UIS_H ${epikon_UIS})
QT4_ADD_RESOURCES(epikon_RSRCS_SRC ${epikon_RSRCS})
set(epikon_ALL_SRCS ${epikon_SRCS} ${epikon_RSRCS_SRC} ${epikon_MOC_SRCS} ${epikon_HDRS} ${epikon_MOC_HDRS} ${epikon_UIS_H})

if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
    endif(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t-")
endif(MSVC)

if(UNIX)
    message("Building unix-like executable")
    add_executable(epikon ${epikon_ALL_SRCS})
elseif(APPLE)
    message("Building MacOSX Bundle")
    add_executable(epikon MACOSX_BUNDLE ${epikon_ALL_SRCS})
elseif(WIN32)
    message("Building win32 executable")
    add_executable(epikon WIN32 ${epikon_ALL_SRCS})
endif()

set_target_properties(epikon PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")
message("linking against ${QT_LIBRARIES} ")
target_link_libraries(epikon ${QT_LIBRARIES} )


install(TARGETS epikon
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} )

include(InstallRequiredSystemLibraries)
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
SET(CPACK_PACKAGE_EXECUTABLES "epikon" "epikon")
INCLUDE(CPack)
