project(liblogcpp)

cmake_minimum_required( VERSION 3.0 )

set( LIBLOGCPP_STABLE_VERSION 1 )
set( LIBLOGCPP_RELEASE 6 )
set( LIBLOGCPP_DEV_VERSION 3 )
set( LIBLOGCPP_VERSION "${LIBLOGCPP_STABLE_VERSION}.${LIBLOGCPP_RELEASE}.${LIBLOGCPP_DEV_VERSION}" )

set( LIBLOGCPP_SRC_DIR ${PROJECT_SOURCE_DIR}/src )

add_definitions( -std=c++11 )
add_definitions(-DSRC_DIR=${LIBLOGCPP_SRC_DIR})

if( ENABLE_QT_SUPPORT )
	add_definitions( -DENABLE_QT_SUPPORT=1 )
	# Instruct CMake to run moc automatically when needed.
	set(CMAKE_AUTOMOC ON)
	# Find the QtCore library
	find_package(Qt5Core)
	message("-- Compiling with support for QString")
endif()

if( DESTDIR )
else()
	set( DESTDIR "${CMAKE_INSTALL_PREFIX}" )
endif()

file (GLOB LIBLOGCPP_HEADERS ${LIBLOGCPP_SRC_DIR}/*.hpp )
file (GLOB LIBLOGCPP_SOURCE ${LIBLOGCPP_SRC_DIR}/log.cpp )

if( UNIX )
	set( LIBLOGCPP_SOURCE ${LIBLOGCPP_SOURCE} ${LIBLOGCPP_SRC_DIR}/color_feature.cpp )
	message("-- Compiling with support for ANSI Color codes")
endif()

add_library( logcpp STATIC ${LIBLOGCPP_SOURCE} )
if( ENABLE_QT_SUPPORT )
	target_link_libraries( logcpp ${Qt5Core_LIBRARIES} )
endif()

if( BUILD_LOGCPP_TEST )
	add_executable( logger_test ${LIBLOGCPP_SRC_DIR}/main.cpp )
	target_link_libraries( logger_test logcpp )
endif()

if( HEADER_INSTALL_DIR )
else()
	set( HEADER_INSTALL_DIR ${DESTDIR}/include/liblogcpp )
endif()

if ( LIB_INSTALL_DIR )
else()
	set ( LIB_INSTALL_DIR ${DESTDIR}/lib )
endif()

if( INSTALL_LIBS )
	install(TARGETS logcpp DESTINATION ${LIB_INSTALL_DIR} )
	install(FILES ${LIBLOGCPP_HEADERS} DESTINATION ${HEADER_INSTALL_DIR} )
	install(FILES ${PROJECT_SOURCE_DIR}/lib/LibLogCPPConfig.cmake DESTINATION "${LIB_INSTALL_DIR}/cmake/LibLogCPP" )
	install(FILES ${PROJECT_SOURCE_DIR}/lib/liblogcpp.pc DESTINATION "${LIB_INSTALL_DIR}/pkgconfig" )
endif()


find_package(Doxygen)
if(DOXYGEN_FOUND)
	if(ENABLE_DOC)
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating documentation with Doxygen")
	endif()
endif()

