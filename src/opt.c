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
#include "opt.h"

opt_err_t
opt_parse (opt_t * opt, size_t count, const char ** args)
{
  /* Initialize the Default Options */
  opt->err = NULL;
  opt->help = 0;
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
