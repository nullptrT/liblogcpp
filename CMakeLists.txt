project(liblogcpp)

cmake_minimum_required( VERSION 3.0 )

set( LIBLOGCPP_STABLE_VERSION 1 )
set( LIBLOGCPP_RELEASE 9 )
set( LIBLOGCPP_PATCH_VERSION 2 )
set( LIBLOGCPP_VERSION "${LIBLOGCPP_STABLE_VERSION}.${LIBLOGCPP_RELEASE}.${LIBLOGCPP_PATCH_VERSION}" )

set( LIBLOGCPP_SRC_DIR ${PROJECT_SOURCE_DIR}/src )

if( UNIX )
	add_definitions( -std=c++11 )
endif()
add_definitions(-DLOGCPP_SRC_DIR=${LIBLOGCPP_SRC_DIR})


if( LOGCPP_DESTDIR )
else()
	set( LOGCPP_DESTDIR "${CMAKE_INSTALL_PREFIX}" )
endif()

file (GLOB LIBLOGCPP_HEADERS ${LIBLOGCPP_SRC_DIR}/*.hpp )
set ( LIBLOGCPP_SOURCE ${LIBLOGCPP_SRC_DIR}/log.cpp ${LIBLOGCPP_SRC_DIR}/severity_default.cpp ${LIBLOGCPP_SRC_DIR}/severity_logger.cpp )

if( UNIX )
	set( LIBLOGCPP_SOURCE ${LIBLOGCPP_SOURCE} ${LIBLOGCPP_SRC_DIR}/color_feature.cpp )
	message("-- Compiling with support for ANSI Color codes")
    add_definitions( -DLOGCPP_AUTOCOLOR=1 )
else()
#	list(REMOVE_ITEM ${LIBLOGCPP_HEADERS} "${LIBLOGCPP_SRC_DIR}/color_feature.hpp")
endif()

if( LOGCPP_SHARED )
	add_library( logcpp SHARED ${LIBLOGCPP_SOURCE} )
	set( LOGCPP_PKGCONFIG_LIBNAME "liblogcpp.so" )
else()
	add_library( logcpp STATIC ${LIBLOGCPP_SOURCE} )
	set( LOGCPP_PKGCONFIG_LIBNAME "liblogcpp.a" )
endif()


if( BUILD_LOGCPP_TEST )
    # Instruct CMake not to run moc automatically when needed.
	set(CMAKE_AUTOMOC OFF)
	# Find the QtCore library
	find_package(Qt5Core)
	# Build the test binary
	add_executable( logcpp_test ${LIBLOGCPP_SRC_DIR}/main.cpp )
	target_link_libraries( logcpp_test logcpp ${Qt5Core_LIBRARIES} )
endif()

if( LOGCPP_HEADER_INSTALL_DIR )
else()
	set( LOGCPP_HEADER_INSTALL_DIR ${LOGCPP_DESTDIR}/include/liblogcpp )
endif()

if ( LOGCPP_LIB_INSTALL_DIR )
else()
	set ( LOGCPP_LIB_INSTALL_DIR ${LOGCPP_DESTDIR}/lib )
endif()

if( LOGCPP_INSTALL_LIBS )
	install(TARGETS logcpp DESTINATION ${LOGCPP_LIB_INSTALL_DIR} )
	install(FILES ${LIBLOGCPP_HEADERS} DESTINATION ${LOGCPP_HEADER_INSTALL_DIR} )
	install(FILES ${PROJECT_SOURCE_DIR}/lib/LibLogCPPConfig.cmake DESTINATION "${LOGCPP_LIB_INSTALL_DIR}/cmake/LibLogCPP" )
	configure_file(${PROJECT_SOURCE_DIR}/lib/liblogcpp.pc.in ${CMAKE_CURRENT_BINARY_DIR}/liblogcpp.pc @ONLY)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/liblogcpp.pc DESTINATION "${LOGCPP_LIB_INSTALL_DIR}/pkgconfig" )
endif()


if( UNIX )
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		message("-- Enabled doc_logcpp target for make")
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doc_logcpp ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating documentation with Doxygen")
	endif()
endif()
