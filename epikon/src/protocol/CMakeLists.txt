
set(epikon_SRCS
    command.cpp
    protocol.cpp
)

set(epikon_HDRS
    command.h
)

set(epikon_MOC_HDRS
       protocol.h
)


find_package(Qt4 4.6.0 COMPONENTS QtCore QtNetwork REQUIRED)
set(QT_USE_QTDBUS FALSE)
include(${QT_USE_FILE})

QT4_WRAP_CPP(epikon_MOC_SRCS ${epikon_MOC_HDRS})
set(epikon_ALL_SRCS ${epikon_SRCS} ${epikon_MOC_SRCS} ${epikon_HDRS} ${epikon_MOC_HDRS} )


add_library(epikonprotolib STATIC ${epikon_ALL_SRCS})
set_target_properties(epikonprotolib PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")

