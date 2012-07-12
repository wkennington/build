/**
   @file buffer.c
   @author William A. Kennington III <william@wkennington.com>
   @brief Limited Length Dynamically Expanding Memory Buffer
   @details Easy to use heap memory buffer which dynamically expands
   in chunks to accomodate a rapdily read data.
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
#include <string.h>
#include "buffer.h"

buffer_err_t
buffer_init (buffer_t * buff, size_t block_size, size_t max_size)
{
  /* Initialize Struct */
  buff->data = NULL;
  buff->block_size = block_size == 0 ? 4096 : block_size;
  if (max_size > 0 && max_size < buff->block_size)
    return BUFF_TOO_SMALL;
  buff->max_size = max_size;
  buff->size = buff->block_size;
  buff->len = 0;

  /* Create the first buffer segment */
  buff->data = (uint8_t*) malloc (buff->size);
  if (buff->data == NULL)
    return BUFF_MALLOC_FAILED;

  return BUFF_OK;
}

buffer_err_t
buffer_extend (buffer_t * buff)
{
  uint8_t *tmp;

  /* Try and allocate more memory */
  tmp = realloc (buff->data, buff->size + buff->block_size);
  if (tmp == NULL)
    return BUFF_MALLOC_FAILED;

  /* Fix the structure */
  buff->size += buff->block_size;
  buff->data = tmp;

  return BUFF_OK;
}

buffer_err_t
buffer_add (buffer_t * buff, void * data, size_t len)
{
  uint8_t *tmp;
  size_t new_size;

  /* Check free space */
  if (buff->max_size > 0 && buff->len + len > buff->max_size)
    return BUFF_TOO_SMALL;
  if (buff->len + len > buff->size)
    {
      /* Calculate the new size of the buffer */
      new_size = (len + buff->len)/buff->block_size;
      new_size *= buff->block_size;
      if (buff->len + len > new_size)
        new_size += buff->block_size;
      if (new_size > buff->max_size)
        new_size = buff->max_size;

      /* Allocate Memory */
      tmp = (uint8_t*) realloc (buff->data, new_size);
      if (tmp == NULL)
        return BUFF_MALLOC_FAILED;

      /* Fix the Structure */
      buff->data = tmp;
      buff->size = new_size;
    }

  /* Copy the memory */
  memcpy (buff->data + buff->len, data, len);
  buff->len += len;

  return BUFF_UNKNOWN;
}

buffer_err_t
buffer_destroy (buffer_t * buff)
{
  if (buff->data != NULL)
    free (buff->data);
  return BUFF_OK;
}
