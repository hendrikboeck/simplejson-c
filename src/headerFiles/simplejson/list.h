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

#ifndef _SIMPLEJSONC_LIST_H
#define _SIMPLEJSONC_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simplejson/object.h"

#define _LIST_INITIAL_CAP 4

struct _List {
  Object* data;
  size_t  len;
  size_t  cap;
};
typedef struct _List* List;

List list_new();
void list_del(List self);
List list_copy(const List self);

void   _list_expand(List self);
bool_t _list_isSpace(const List self, const size_t size);

size_t  list_length(const List self);
size_t  list_capacity(const List self);
Object  list_at(const List self, const size_t index);
Object* list_data(const List self);
List    list_append(List self, Object obj);
List    list_clear(List self);
List    list_extend(List self, const List other);
List    list_insert(List self, const size_t index, Object obj);
List    list_remove(List self, const size_t index);
Object  list_pop(List self, const size_t index);

#ifdef __cplusplus
}
#endif

#endif  // _SIMPLEJSONC_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

struct _List;
typedef struct _List* List;

#ifdef __cplusplus
}
#endif