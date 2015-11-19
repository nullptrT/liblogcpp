/*
 * Summary: compile-time version informations
 * Description: compile-time version informations for LibLogC++
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Daniel Veillard
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * LIBLOGCPP_DOTTED_VERSION:
 *
 * the version string like "1.2.3"
 */
#define LIBLOGCPP_DOTTED_VERSION "1.5.3"

/**
 * LIBLOGCPP_VERSION:
 *
 * the version number: 1.2.3 value is 10203
 */
#define LIBLOGCPP_VERSION 10503

/**
 * LIBLOGCPP_VERSION_STRING:
 *
 * the version number string, 1.2.3 value is "10203"
 */
#define LIBLOGCPP_VERSION_STRING "10503"

/**
 * LIBLOGCPP_VERSION_EXTRA:
 *
 * extra version information
 */
#define LIBLOGCPP_VERSION_EXTRA ""


#ifdef __cplusplus
}
#endif /* __cplusplus */



