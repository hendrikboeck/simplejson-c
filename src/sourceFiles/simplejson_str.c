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

#include "simplejson/str.h"

str_t str_new(size_t cap) {
  return (str_t)NEW_BLK(cap);
}

void str_del(str_t self) {
  DEL(self);
}

str_t str_copy(strview_t self) {
  return strcpy(str_new(str_length(self) + 1), self);
}

size_t str_length(strview_t self) {
  return strlen(self);
}

bool_t str_compare(strview_t self, strview_t other) {
  return (bool_t)(strcmp(self, other) == 0);
}

char* str_containsChar(strview_t self, const char part) {
  for (size_t i = 0; i < str_length(self); i++)
    if (self[i] == part) return ADDR(self[i]);
  return NULL;
}

char* str_contains(strview_t self, strview_t part) {
  return strstr(self, part);
}

bool_t str_startsWithChar(strview_t self, const char part) {
  return (bool_t)(self[0] == part);
}

bool_t str_startsWith(strview_t self, strview_t part) {
  (bool_t)(strncmp(self, part, strlen(part)) == 0);
}
