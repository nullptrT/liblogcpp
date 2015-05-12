project(liblogcpp)

cmake_minimum_required( VERSION 2.8 )

set( LIBLOGCPP_STABLE_VERSION 1 )
set( LIBLOGCPP_RELEASE 3 )
set( LIBLOGCPP_DEV_VERSION 9 )
set( LIBLOGCPP_VERSION "${LIBLOGCPP_STABLE_VERSION}.${LIBLOGCPP_RELEASE}.${LIBLOGCPP_DEV_VERSION}" )

set( LIBLOGCPP_SRC_DIR "${PROJECT_SOURCE_DIR}/src" )

add_definitions( -DVERSION="${LIBLOGCPP_VERSION}" )
add_definitions( -std=c++11 )
add_definitions(-DSRC_DIR="${LIBLOGCPP_SRC_DIR}")

if( DESTDIR )
else()
	set( DESTDIR "${PROJECT_BINARY_DIR}" )
endif()

set(CMAKE_BUILD_TYPE "Debug")

file (GLOB LIBLOGCPP_HEADERS "${LIBLOGCPP_SRC_DIR}/*.hpp" )
file (GLOB LIBLOGCPP_SOURCE "${LIBLOGCPP_SRC_DIR}/log.cpp" )

add_library( logcpp STATIC "${LIBLOGCPP_SOURCE}" )

add_executable( logger_test "${LIBLOGCPP_SRC_DIR}/main.cpp" )
target_link_libraries( logger_test logcpp )


if( HEADER_INSTALL_DIR )
else()
	set( HEADER_INSTALL_DIR "${DESTDIR}/include" )
endif()

if ( LIB_INSTALL_DIR )
else()
	set ( LIB_INSTALL_DIR ${DESTDIR}/lib )
endif()


install(FILES "${LIBLOGCPP_HEADERS}" DESTINATION "${HEADER_INSTALL_DIR}" )
