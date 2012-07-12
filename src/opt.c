/**
   @file opt.c
   @author William A. Kennington III <william@wkennington.com>
   @brief Option Parser
   @details An option parser specifically tailored for use in the
   autobuilder application.
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
#include <getopt.h>
#include <unistd.h>
#include "opt.h"
#include "util.h"

#define DEFAULT_CONFIG "autobuild.conf"

#define OPTS "-c:hW:"
const static struct option LONG_OPTS [] = {
  {"config", 1, NULL, 0},
  {"help", 0, NULL, 0},
  {0, 0, 0, 0}
};

opt_err_t
opt_init (opt_t * opt, size_t count, char ** args)
{
  int ret, idx;

  /* Initialize the Default Options */
  opt->err = NULL;
  opt->help = 0;
  opt->conf = cpstr (DEFAULT_CONFIG);

  /* Prevent getopt from printing to stderr */
  opterr = 0;

  /* Iterate over every option matching them into the struct */
  while ((ret = getopt_long (count, args, OPTS, LONG_OPTS, &idx)) != -1)
    {
      /* Non-standard option */
      if (ret == 1)
        continue;

      /* Short option */
      else if (ret != 0)
        switch (ret)
          {
          case 'c':
            opt->conf = cpstr (optarg);
          case 'h':
            opt->help = 1;
          }

      /* Long Options */
      else
        switch (idx)
          {
          case 0:
            opt->conf = cpstr (optarg);
          case 1:
            opt->help = 1;
          }

    }

  return OPT_OK;
}

opt_err_t
opt_destroy (opt_t * opt)
{
  if (opt->err != NULL)
    free ((void*)opt->err);
  if (opt->conf != NULL)
    free ((void*)opt->conf);
  return OPT_OK;
}

const char *
opt_get_err (opt_t * opt)
{
  return opt->err;
}

const char *
opt_err_str (opt_err_t err)
{
  switch (err)
    {
    case OPT_OK:
      return "Success";
    case OPT_UNKNOWN:
      return "Unknown Cause of Error";
    }
  return "Unknown Error Code";
}
