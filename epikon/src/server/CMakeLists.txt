
set(epikon_SRCS
    epikonserver.cpp 
    epikonconnectionmanager.cpp 
    epikonclient.cpp
    epikonprotocolcommand.cpp
)

set(epikon_HDRS
    epikonconnectionmanager.h
    epikonprotocolcommand.h
)

set(epikon_MOC_HDRS
    epikonserver.h 
    epikonclient.h
)


find_package(Qt4 4.6.0 COMPONENTS QtCore QtNetwork REQUIRED)
include(${QT_USE_FILE})

QT4_WRAP_CPP(epikon_MOC_SRCS ${epikon_MOC_HDRS})
set(epikon_ALL_SRCS ${epikon_SRCS} ${epikon_MOC_SRCS} ${epikon_HDRS} ${epikon_MOC_HDRS} )


add_library(epikonsrvlib STATIC ${epikon_ALL_SRCS})
set_target_properties(epikonsrvlib PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")


add_executable(epikonsrv main.cpp)
set_target_properties(epikonsrv PROPERTIES LINK_FLAGS "${ALL_LINKFLAGS}")
target_link_libraries(epikonsrv epikonsrvlib ${QT_LIBRARIES} )

install(TARGETS epikonsrv
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} )
