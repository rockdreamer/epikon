
# ADD_DEFINITIONS( "-Wall -ansi" )
# ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

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

if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
    endif(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t-")
endif(MSVC)

add_subdirectory(server)
add_subdirectory(client)

	