/**
   @file opt.h
   @author William A. Kennington III <william@wkennington.com>
   @brief Option Parser
   @details An option parser specifically tailored for use in the
   autobuilder application.
**/
/*
  Copyright (C) 2012 William A. Kennington III

  This file is part of AutoBuilder.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _OPT_H_
#define _OPT_H_

#include <stdint.h>

/**
   @brief Option Values
   @details Contains specific values which account for flags enabled
   in the command line.
**/
typedef struct _opt_t
{
  const char * err; /**< Last Error String */
  uint8_t help; /**< Help Selected Flag */
  const char * conf; /**< Path to the configuration file */
} opt_t;

/**
   @brief Option Error Codes
**/
typedef enum _opt_err_tn
  {
    OPT_OK = 0, /**< Success */
    OPT_INVALID, /**< Invalid Argument */
    OPT_UNKNOWN /**< An Unknown Error */
  } opt_err_t;

/**
   @brief Parses Command Line Options'
   @param opt A pointer to an option structure
   @param count The number of strings in the array args
   @param args The array of strings to be parsed
   @param err 0 to disable automatic error printing or 1 to enable printing.
   @return OPT_OK(0) on success or an error code on failure.
   @details Takes an option struct and populates it with data from the
   command line arguments passed by args.
**/
opt_err_t opt_init (opt_t * opt, size_t count, char ** args, int err);

/**
   @brief Destroys the OPT Struct
   @details Frees any allocated memory in the opt struct and prepares
   it for deletion. You must call this to prevent memory leaks.
   @param opt The option structure to free
   @return OPT_OK(0) on success or an error code on failure
**/
opt_err_t opt_destroy (opt_t * opt);

/**
   @brief Get Detailed Error Message
   @details Generates a string with a detailed error message
   describing the most recent error event
   @param opt The option structure which had an error
   @return Error String or NULL if no error
**/
const char * opt_get_err (opt_t * opt);

/**
   @brief Generates a string describing the error code
   @param err The error code to be described.
   @return The string representing the error code.
*/
const char * opt_err_str (opt_err_t err);

#endif
