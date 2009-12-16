
set(epikon_SRCS
    epikonmainwindow.cpp 
    epikongame.cpp 
    epikonnetworkgame.cpp
    epikonplayer.cpp
    epikonplanet.cpp 
    epikongamescene.cpp 
    epikonplanetitem.cpp 
    epikonattack.cpp 
    epikonshipitem.cpp 
    epikonconnection.cpp
    main.cpp
)

set(epikon_HDRS
    epikonplanetitem.h
)

set(epikon_MOC_HDRS
    epikonconnection.h
    epikonmainwindow.h
    epikongame.h 
    epikonnetworkgame.h
    epikonplayer.h
    epikonplanet.h 
    epikongamescene.h 
    epikonattack.h 
    epikonshipitem.h 
)

set(epikon_UIS
    epikonmainwindow.ui
)

set(epikon_RSRCS
    resources.qrc
)


find_package(Qt4 4.6.0 COMPONENTS QtCore QtGui QtNetwork QtSvg Phonon REQUIRED)
set(QT_USE_QTMAIN 1)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

QT4_WRAP_CPP(epikon_MOC_SRCS ${epikon_MOC_HDRS})
QT4_WRAP_UI(epikon_UIS_H ${epikon_UIS})
QT4_ADD_RESOURCES(epikon_RSRCS_SRC ${epikon_RSRCS})
set(epikon_ALL_SRCS ${epikon_SRCS} ${epikon_RSRCS_SRC} ${epikon_MOC_SRCS} ${epikon_HDRS} ${epikon_MOC_HDRS} ${epikon_UIS_H})

if(UNIX)
    add_executable(epikon ${epikon_ALL_SRCS})
elseif(APPLE)
    add_executable(epikon MACOSX_BUNDLE ${epikon_ALL_SRCS})
elseif(WIN32)
    add_executable(epikon WIN32 ${epikon_ALL_SRCS})
endif()

set_target_properties(epikon PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")
target_link_libraries(epikon epikonsrvlib epikonprotolib ${QT_LIBRARIES} )

install(TARGETS epikon
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} )

