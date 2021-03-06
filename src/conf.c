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

inline static char * 
trim_str (char * str, size_t len)
{
  /* Trim the spaces from the front */
  while (str[0] == ' ' || str[0] == '\t' || str[0] == '\r' || str[0] == '\n')
    str++;

  /* Work backward to place the end of string */
  len--;
  while (str[len] == ' ' || str[len] == '\t' || str[len] == '\r' || str[len] == '\n')
    len--;
  str[len+1] = '\0';

  return str;
}

inline static char *
cleanup_str (char * str, int key)
{
  /* Start by trimming the str */
  str = trim_str (str, strlen (str));

  return str;
}

conf_err_t
conf_init (conf_t * conf, const char * filename)
{
  FILE * file;
  buffer_t buff;
  uint8_t lbuff[BUFF];
  int read;
  size_t line_ct, i, st, eq;
  char *tmp_key, *tmp_val;

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

  /* Close File Handle */
  fclose (file);

  /* Parse each line looking for errors */
  line_ct = 0;
  st = 0;
  eq = 0;
  for (i = 0; i < buff.len; i++)
    switch (buff.data[i])
      {
      case '=':
        eq = i;
        break;
      case '\n':
        line_ct++;

        /* Break down the line into a string */
        tmp_key = buff.data + st;
        buff.data[i] = '\0';
        tmp_key = trim_str (tmp_key, i-st+1);

        /* Empty or comment line */
        if (strlen (tmp_key) == 0 || tmp_key[0] == '#')
          break;

        /* Validate Line */
        if (eq <= st)
          {
            conf->err = cpstrf ("Parse Error: Invalid Line #%d\n", line_ct);
            buffer_destroy (&buff);
            return CONF_PARSE_ERR;
          }

        /* Trim value and key strings */
        buff.data[eq] = '\0';
        tmp_val = buff.data + eq + 1;
        tmp_key = cleanup_str (tmp_key, 1);
        if (tmp_key == NULL)
          {
            conf->err = cpstrf ("Key Error on Line #%d\n", line_ct);
            return CONF_PARSE_ERR;
          }
        tmp_val = cleanup_str (tmp_val, 0);
        if (tmp_val == NULL)
          {
            conf->err = cpstrf ("Value Error on Line #%d\n", line_ct);
            return CONF_PARSE_ERR;
          }

        /* Store the values */
        printf ("Key: %s\nValue: %s\n", tmp_key, tmp_val);

        st = i+1;
        break;
      }

  /* Cleanup */
  buffer_destroy (&buff);

  /* Sort the array */

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
