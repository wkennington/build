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
#include <string.h>
#include "buffer.h"
#include "conf.h"
#include "util.h"

#define BUFF 4096
#define MALLOC_FAILED "Malloc Failed\n"
#define TOO_LARGE "Configuration File Too Large\n"

conf_err_t
conf_init (conf_t * conf, const char * filename)
{
  FILE * file;
  buffer_t buff;
  uint8_t lbuff[BUFF];
  int read;

  /* Initialize the struct */
  conf->err = NULL;
  conf->filename = cpstr (filename);
  conf->data = NULL;
  conf->data_len = 0;

  /* Attempt to open the file */
  file = fopen (filename, "r");
  if (file == NULL)
    {
      conf->err = cpstrf ("Invalid File: %s\n", filename);
      return CONF_NO_FILE;
    }

  /* Load the entire file into memory */
  if (buffer_init (&buff, BUFF, BUFF<<3) == BUFF_MALLOC_FAILED)
    {
      fclose (file);
      conf->err = cpstr (MALLOC_FAILED);
      return CONF_MALLOC_FAILED;
    }
  while ((read = fread (lbuff, sizeof (uint8_t), BUFF, file)) > 0)
    switch (buffer_add (&buff, lbuff, read))
      {
      case BUFF_MALLOC_FAILED:
        conf->err = cpstr (MALLOC_FAILED);
        buffer_destroy (&buff);
        fclose (file);
        return CONF_MALLOC_FAILED;
      case BUFF_TOO_SMALL:
        conf->err = cpstr (TOO_LARGE);
        buffer_destroy (&buff);
        fclose (file);
        return CONF_TOO_LARGE;
      }

  printf ("%s\n", buff.data);

  /* Cleanup */
  buffer_destroy (&buff);
  fclose (file);

  return CONF_OK;
}

char *
conf_get (conf_t * conf, const char * key)
{
  size_t left, right, median;
  int ret;

  /* Initialize LR */
  left = 0;
  right = conf->data_len;

  /* Binary Search over the sorted array */
  while (left < right)
    {
      median = (left+right)>>1;
      ret = strcmp (conf->data[median].key, key);
      if (ret == 0)
        return conf->data[median].val;
      else if (ret > 0)
        left = median + 1;
      else
        right = median;
    }

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
