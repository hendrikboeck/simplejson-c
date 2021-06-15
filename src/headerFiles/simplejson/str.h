/******************************************************************************/
/* simplejson-c                                                               */
/* Copyright (C) 2021  Hendrik Boeck <hendrikboeck.dev@protonmail.com>        */
/*                                                                            */
/* This program is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation, either version 3 of the License, or          */
/* (at your option) any later version.                                        */
/*                                                                            */
/* This program is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              */
/* GNU General Public License for more details.                               */
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>.      */
/******************************************************************************/

#ifndef _SIMPLEJSONC_STR_H
#define _SIMPLEJSONC_STR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simplejson/_internal.h"

#define STR_NUMBERS     "0123456789"
#define STR_ASCII_LOWER "abcdefghijklmnopqrstuvwxyz"
#define STR_ASCII_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

str_t str_new(size_t cap);
void  str_del(str_t self);
str_t str_copy(strview_t self);

size_t      str_length(strview_t self);
bool_t      str_equal(strview_t self, strview_t other);
const char* str_containsChar(strview_t self, const char part);
char*       str_contains(strview_t self, strview_t part);
bool_t      str_startsWithChar(strview_t self, const char part);
bool_t      str_startsWith(strview_t self, strview_t part);

#ifdef __cplusplus
}
#endif

#endif  // _SIMPLEJSONC_STR_H