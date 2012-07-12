/**
   @file conf.h
   @author William A. Kennington III <william@wkennington.com>
   @brief Configuration Parser
   @details A configuration parser and manager, binding keys to values
   read from the input file.
   @warning Editing support is currently unavailable.
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

#ifndef _CONF_H
#define _CONF_H

/**
   @brief Configuration Error Codes
**/
typedef enum _conf_err_t
  {
    CONF_OK = 0, /**< Success */
    CONF_NO_FILE, /**< File does not exist */
    CONF_UNKNOWN /**< Unknown Cause of Error */
  } conf_err_t;

/**
   @brief Key value pair string
**/
struct _conf_kv_t
{
  char * key;
  char * val;
};

/**
   @brief Configuration Data Struct
**/
typedef struct _conf_t
{
  char * err; /**< Last Error String */
  char * filename; /**< The path of the configuration file. */
  struct _conf_kv_t * data; /**< The data struct for kv pairs.*/
  size_t data_len;
} conf_t;

/**
   @brief Initializes the configuration struct to the given filename.
   @param conf The configuration struct to be initialized with data.
   @param filename The name of the file where the configuration is
   stored.
   @return CONF_OK(0) on success or a positive error code.
*/
conf_err_t conf_init (conf_t * conf, const char * filename);

/**
   @brief Gets the value of a key -> value pair
   @param conf The configuration struct.
   @param key The key of the associated key -> value pair.
   @return NULL on failure or the value of the assoicated key.
**/
char * conf_get (conf_t * conf, const char * key);

/**
   @brief Get Detailed Error Message
   @details Generates a string with a detailed error message
   describing the most recent error event
   @param conf The configuration structure which had an error
   @return Error String or NULL if no error
**/
const char * conf_get_err (conf_t * conf);

/**
   @brief Destroys the configuration struct freeing self allocated
   heap memory
   @param conf The configuration struct.
   @return CONF_OK(0) on success or a  positive error code.
**/
conf_err_t conf_destroy (conf_t * conf);

/**
   @brief Generates a string describing the error code
   @param err The error code to be described.
   @return The string representing the error code.
*/
const char * conf_err_str (conf_err_t err);

#endif
