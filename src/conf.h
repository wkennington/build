/*
  A configuration parser and manager, a file based serializing key ->
  value map.

  Copyright (C) 2012 William Kennington

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

/**
 * IMPORTANT NOTES:
 * Editing support is currently unavailable
 **/

typedef enum _conf_err_t
  {
    CONF_OK = 0,
    CONF_UNKNOWN
  } conf_err_t;

typedef struct _conf_t
{
  const char * filename;
} conf_t;

/* Initializes the configuration struct to the given filename */
conf_err_t conf_init (conf_t * conf, const char * filename);

/* Gets the value of a key -> value pair */
const char * conf_get (conf_t * conf, const char * key);

/* Destroys the configuration struct freeing self allocated heap memory*/
conf_err_t conf_destroy (conf_t * conf);

/* Gets the meaning of an error value */
const char * conf_error_string (conf_err_t err);
