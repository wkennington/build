/*
  The main executable file for the AutoBuilder Application. This ties
  all of the application components together for the final executable.

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

/* Useful Definitions */
#define CONF_FILE "autobuild.conf"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conf.h"

int
main (int argc, char ** argv)
{
  conf_t conf;
  conf_err_t cerr;

  /* Parse the command line */

  /* Parse the configuration */
  cerr = conf_init (&conf, CONF_FILE);
  if (conf == NULL)
    {
      fprintf ("Configuration Error: %s\n", conf_error_str (cerr));
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
