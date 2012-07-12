/**
   @file util.c
   @author William A. Kennington III <william@wkennington.com>
   @brief Useful Functions
   @details A miscellaneous group of functions useful throughout the autobuilder
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
#include <stdarg.h>
#include <string.h>

void *
memdup (const void * data, size_t len)
{
  void * ret = NULL;

  /* Allocate memory for new buffer */
  ret = malloc (len * sizeof (char));
  if (ret == NULL)
    return ret;

  /* Copy the buffer contents */
  memcpy (ret, data, len);

  return ret;
}

char *
cpstrn (const char * str, size_t len)
{
  char * ret;

  /* Get the maximum length */
  len = strnlen (str, len);

  /* Allocates a new buffer for the string */
  ret = (char*) malloc ((len+1)*sizeof (char));
  if (ret == NULL)
    return ret;

  /* Setup the return string */
  memcpy (ret, str, len*sizeof(char));
  ret[len] = 0;

  return ret;
}

char *
cpstr (const char * str)
{
  return (char*) memdup (str, (strlen (str)+1) * sizeof (char));
}

char *
cpstrf (const char * format, ...)
{
  va_list args;
  char * ret;
  int ret_len;

  /* Setup the Variable Argument List */
  va_start (args, format);

  /* Get the length of the string */
  ret_len = vsnprintf (NULL, 0, format, args) + 1;

  /* Reset the args list */
  va_end (args);
  va_start (args, format);

  /* Generate the string */
  ret = (char*) malloc (ret_len * sizeof (char));
  if (ret == NULL)
    return NULL;
  vsnprintf (ret, ret_len, format, args);

  /* Cleanup the arguments list */
  va_end (args);

  return ret;
}
