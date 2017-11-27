
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

find_package(Qt5Network REQUIRED)
set(epikon_ALL_SRCS ${epikon_SRCS} ${epikon_MOC_SRCS} ${epikon_HDRS} ${epikon_MOC_HDRS} )

add_library(epikonprotolib STATIC ${epikon_ALL_SRCS})
target_link_libraries(epikonprotolib Qt5::Network)

set_target_properties(epikonprotolib PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")

