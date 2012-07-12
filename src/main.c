/**
   @file main.c
   @author William A. Kennington III <william@wkennington.com>
   @brief The main executable file for the AutoBuilder
   Application. This ties all of the application components together
   for the final executable.
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

/* Useful Definitions */
#define HELP_TXT "Usage: autobuild [--help]"
#define SHORT_HELP "Try 'autobuild --help' for more information."

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conf.h"
#include "opt.h"

/**
   @brief AutoBuilder Entry Point
   @param argc Number of arguments passed through argv
   @param argv String representation of arguments passed to the
   application
   @return EXIT_SUCCESS on success or a non-zero integer on failure.
**/
int
main (int argc, char ** argv)
{
  conf_t conf;
  conf_err_t cerr;
  opt_t opt;
  opt_err_t oerr;
  char * db_db;

  /* Parse the command line */
  oerr = opt_init(&opt, argc, argv, 1);
  if (oerr != OPT_OK)
    {
      fprintf (stderr, "%s\n", SHORT_HELP);
      opt_destroy (&opt);
      return EXIT_FAILURE;
    }
  if (opt.help)
    {
      fprintf (stderr, "%s\n", HELP_TXT);
      return EXIT_SUCCESS;
    }

  /* Parse the configuration */
  cerr = conf_init (&conf, opt.conf);
  if (cerr != CONF_OK)
    {
      fprintf (stderr, "Configuration Error: %s", conf_get_err (&conf));
      conf_destroy (&conf);
      opt_destroy (&opt);
      return EXIT_FAILURE;
    }

  /* Read DB_DB */
  db_db = conf_get (&conf, "DB_DB");
  if (db_db == NULL)
    {
      fprintf (stderr, "Configuration Error: Couldn't get key DB_DB\n");
      conf_destroy (&conf);
      opt_destroy (&opt);
      return EXIT_FAILURE;
    }

  /* Cleanup */
  conf_destroy (&conf);
  opt_destroy (&opt);

  return EXIT_SUCCESS;
}
