/**
   @file conf.h
   @author William A. Kennington III <william@wkennington.com>
   @brief A configuration parser and manager, binding keys to values
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

typedef enum _conf_err_t
  {
    CONF_OK = 0,
    CONF_UNKNOWN
  } conf_err_t;

typedef struct _conf_t
{
  const char * filename;
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
const char * conf_get (conf_t * conf, const char * key);

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
const char * conf_error_string (conf_err_t err);
