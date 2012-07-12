/**
   @file util.h
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

/**
   @brief Dynamic Buffer Copy
   @details Makes an exact replica of the buffer in a newly allocated
   portion on the heap.
   @param data The target buffer to copy
   @param len The length of the target buffer
   @return The newly allocated copy of data
**/
void * memdup (const void * data, size_t len);

/**
   @brief Dynamic String Copy
   @details Makes an exact replica of the string on the heap limited
   in length by the max_value, len. The string length will limited by either
   a null terminator or the len paramter. This is not the same as
   strncpy.
   Note that this will ALWAYS null terminate the string.
   @param str Target String to Copy
   @param len Maximum Length to Copy
   @return A newly allocated copy of str
**/
char * cpstrn (const char * str, size_t len);

/**
   @brief Copies the String to the Heap
   @details Makes an exact replica of the string on the heap.
   @param str Target String to Copy
   @return A newly allocated copy of str.
**/
char * cpstr (const char * str);

/**
   @brief Copies the formatted String to the Heap
   @details Formats the stirng according to the specifications and
   places it into a chunk of heap memory.
   @param format The string formatting function.
   @return A newly allocated copy of str.
**/
char * cpstrf (const char * format, ...);
