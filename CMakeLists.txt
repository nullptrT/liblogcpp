project(liblogcpp)

cmake_minimum_required( VERSION 3.0 )

set( LIBLOGCPP_STABLE_VERSION 1 )
set( LIBLOGCPP_RELEASE 6 )
set( LIBLOGCPP_DEV_VERSION 0 )
set( LIBLOGCPP_VERSION "${LIBLOGCPP_STABLE_VERSION}.${LIBLOGCPP_RELEASE}.${LIBLOGCPP_DEV_VERSION}" )

set( LIBLOGCPP_SRC_DIR ${PROJECT_SOURCE_DIR}/src )

add_definitions( -DLIBLOGCPP_VERSION=${LIBLOGCPP_VERSION} )
add_definitions( -std=c++11 )
add_definitions(-DSRC_DIR=${LIBLOGCPP_SRC_DIR})

if( DESTDIR )
else()
	set( DESTDIR "${CMAKE_INSTALL_PREFIX}" )
endif()

#set(CMAKE_BUILD_TYPE "Debug")

file (GLOB LIBLOGCPP_HEADERS ${LIBLOGCPP_SRC_DIR}/*.hpp )
file (GLOB LIBLOGCPP_SOURCE ${LIBLOGCPP_SRC_DIR}/log.cpp )


add_library( logcpp STATIC ${LIBLOGCPP_SOURCE} )


if( BUILD_LOGCPP_TEST )
	add_executable( logger_test ${LIBLOGCPP_SRC_DIR}/main.cpp )
	target_link_libraries( logger_test logcpp )
endif()

if( HEADER_INSTALL_DIR )
else()
	set( HEADER_INSTALL_DIR ${DESTDIR}/include )
endif()

if ( LIB_INSTALL_DIR )
else()
	set ( LIB_INSTALL_DIR ${DESTDIR}/lib )
endif()

if( INSTALL_LIBS )
	install(TARGETS logcpp DESTINATION ${LIB_INSTALL_DIR} )
	install(FILES ${LIBLOGCPP_HEADERS} DESTINATION ${HEADER_INSTALL_DIR} )
	install(FILES ${PROJECT_SOURCE_DIR}/lib/LibLogCPPConfig.cmake DESTINATION "${LIB_INSTALL_DIR}/cmake/LibLogCPP" )
endif()
