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

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Svg REQUIRED)

set(epikon_ALL_SRCS ${epikon_SRCS} ${epikon_HDRS} ${epikon_RSRCS} ${epikon_UIS})

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
set_target_properties(epikon PROPERTIES AUTOUIC TRUE)
target_link_libraries(epikon epikonsrvlib epikonprotolib Qt5::Widgets Qt5::Network Qt5::Svg )

install(TARGETS epikon
    RUNTIME DESTINATION bin)
