# Copyright (C) 2012 William Kennington
#
# This file is part of AutoBuilder.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

ACLOCAL_AMFLAGS = -I ../m4
bin_PROGRAMS = autobuild
AM_CFLAGS = $(LIBDEPS_CFLAGS) $(POSTGRESQL_CFLAGS)
autobuild_SOURCES = buffer.c conf.c main.c opt.c util.c
autobuild_LDADD = -lpthread $(LIBDEPS_LIBS) $(POSTGRESQL_LIBS)
