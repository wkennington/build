/**
   @file buffer.h
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

#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdint.h>

/**
   @brief Buffer Error Codes
**/
typedef enum _buffer_err_t
  {
    BUFF_OK = 0, /**< Success */
    BUFF_MALLOC_FAILED, /**< Allocating Memory Failed */
    BUFF_TOO_SMALL, /**< Not enough room to allocate more blocks */
    BUFF_UNKNOWN /**< Unknown Error */
  } buffer_err_t;

/**
   @brief Buffer Structure
**/
typedef struct _buffer_t
{
  uint8_t * data; /**< Data Segment */
  size_t block_size, /**< Size of each allocated block */
    max_size, /**< Maximum size of the memory buffer */
    size, /**< Current Size of the memory buffer */
    len; /**< Length of the data segment */
} buffer_t;

/**
   @brief Creates a New Buffer
   @details Creates a new buffer with a maximum size of maxsize.
   @param buff The buffer structure to be initialized
   @param block_size The size of each extended allocated block. Set
   this to 0 for the default allocation scheme.
   @param max_size The maximum size of the buffer. Set this to 0 for
   unlimited bytes.
   @return An error code corresponding to any errors which my have occurred
**/
buffer_err_t buffer_init (buffer_t * buff, size_t block_size, size_t max_size);

/**
   @brief Extends the Buffer
   @details Allocates new memory for the end of the buffer if it makes
   sense
   @param buff The buffer structure to extend
   @return An error code
 **/
buffer_err_t buffer_extend (buffer_t * buff);

/**
   @brief Copies data onto the end of the buffer
   @details Handles allocations and copying of the data into the
   buffer's data segment.
   @param buffer The buffer to copy data into
   @param data The data segment to copy
   @param len The length of the data segment
   @return An error code
**/
buffer_err_t buffer_add (buffer_t * buff, void * data, size_t len);

/**
   @brief Destroys the Buffer
   @details Destroys the buffer and frees its contents from heap
   memory.
   @param buff The buffer struct to be destroyed
   @return An error code corresponding to free errors
**/
buffer_err_t buffer_destroy (buffer_t * buff);

#endif
