/**
   @file conf.c
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

#include <stdlib.h>
#include "conf.h"

conf_err_t
conf_init (conf_t * conf, const char * filename)
{
  return CONF_UNKNOWN;
}

const char *
conf_get (conf_t * conf, const char * key)
{
  return NULL;
}

conf_err_t
conf_destroy (conf_t * conf)
{
  return CONF_UNKNOWN;
}

const char * conf_get_err (conf_t * conf)
{
  return conf->err;
}

const char *
conf_err_str (conf_err_t err)
{
  switch (err)
    {
    case CONF_OK:
      return "Success";
    case CONF_UNKNOWN:
      return "Unknown Cause of Error";
    }

  return "Undefined Error Code";
}
