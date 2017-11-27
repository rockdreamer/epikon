
set(epikon_SRCS
    player.cpp
    epikonserver.cpp 
    epikonclient.cpp
)

set(epikon_HDRS
)

set(epikon_MOC_HDRS
    player.h
    epikonserver.h
    epikonclient.h
)

find_package(Qt5Network REQUIRED)
set(epikon_ALL_SRCS ${epikon_SRCS} ${epikon_MOC_SRCS} ${epikon_HDRS} ${epikon_MOC_HDRS} )


add_library(epikonsrvlib STATIC ${epikon_ALL_SRCS})
target_link_libraries(epikonsrvlib Qt5::Network)

set_target_properties(epikonsrvlib PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")


add_executable(epikonsrv main.cpp)
set_target_properties(epikonsrv PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")
target_link_libraries(epikonsrv epikonsrvlib epikonprotolib)

install(TARGETS epikonsrv
    RUNTIME DESTINATION bin)
