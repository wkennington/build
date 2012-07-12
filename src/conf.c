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
#include <stdio.h>
#include "conf.h"
#include "util.h"

conf_err_t
conf_init (conf_t * conf, const char * filename)
{
  FILE * file;

  /* Initialize the struct */
  conf->err = NULL;
  conf->filename = cpstr (filename);
  conf->data = NULL;

  /* Attempt to open the file */
  file = fopen (filename, "r");
  if (file == NULL)
    {
      conf->err = cpstrf ("Invalid File: %s\n", filename);
      return CONF_NO_FILE;
    }

  return CONF_OK;
}

char *
conf_get (conf_t * conf, const char * key)
{
  return NULL;
}

conf_err_t
conf_destroy (conf_t * conf)
{
  size_t i;

  /* Free Data Members */
  if (conf->err != NULL)
    free ((void*)conf->err);
  if (conf->filename != NULL)
    free ((void*)conf->filename);
  if (conf->data != NULL)
    {
      for (i = 0; i < conf->data_len; i++)
        {
          free (conf->data[i].key);
          free (conf->data[i].val);
        }
      free ((void*)conf->data);
    }

  return CONF_OK;
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
