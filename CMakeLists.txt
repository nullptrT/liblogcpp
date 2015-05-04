project(liblogcpp)

cmake_minimum_required( VERSION 2.8 )

set( LIBLOGCPP_STABLE_VERSION 0 )
set( LIBLOGCPP_DEV_VERSION 0 )
set( LIBLOGCPP_RELEASE 1a )
set( LIBLOGCPP_VERSION "${LIBLOGCPP_STABLE_VERSION}.${LIBLOGCPP_DEV_VERSION}.${LIBLOGCPP_RELEASE}" )

set( LIBLOGCPP_SRC_DIR "${PROJECT_SOURCE_DIR}/src" )

add_definitions( -DVERSION="${LIBLOGCPP_VERSION}" )
add_definitions( -std=c++11 )
add_definitions(-DSRC_DIR="${LIBLOGCPP_SRC_DIR}")

if( DESTDIR )
else()
    set( DESTDIR "${PROJECT_BINARY_DIR}" )
endif()

#set(CMAKE_BUILD_TYPE "Debug")

file (GLOB LIBLOGCPP_HEADERS "${LIBLOGCPP_SRC_DIR}/*.hpp" )


if( HEADER_INSTALL_DIR )
else()
    set( HEADER_INSTALL_DIR "${DESTDIR}/include" )
endif()


install(FILES "${LIBLOGCPP_HEADERS}" DESTINATION "${HEADER_INSTALL_DIR}" )
