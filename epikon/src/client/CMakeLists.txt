
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
    main.cpp
)

set(epikon_HDRS
    epikonplanetitem.h
)

set(epikon_MOC_HDRS
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
    serverdialog.ui
    connectiondialog.ui
)

set(epikon_RSRCS
    resources.qrc
)


find_package(Qt4 4.6.0 COMPONENTS QtCore QtGui QtNetwork QtSvg REQUIRED)

set(QT_USE_QTMAIN 1)
set(QT_USE_QTDBUS FALSE)

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
    install(FILES
        ${QT_BINARY_DIR}/QtCore4.dll
        ${QT_BINARY_DIR}/QtGui4.dll
        ${QT_BINARY_DIR}/QtSvg4.dll
        ${QT_BINARY_DIR}/QtNetwork4.dll
        DESTINATION bin)
endif()

set_target_properties(epikon PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")
target_link_libraries(epikon epikonsrvlib epikonprotolib ${QT_LIBRARIES} )

install(TARGETS epikon
    RUNTIME DESTINATION bin)

