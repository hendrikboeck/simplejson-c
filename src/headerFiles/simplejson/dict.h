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

#ifndef _SIMPLEJSONC_DICT_H
#define _SIMPLEJSONC_DICT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simplejson/object.h"
#include "simplejson/str.h"

#define _dict_INITIAL_CAP 4

struct _DictTuple {
  str_t  key;
  Object value;
};
typedef struct _DictTuple DictTuple;

struct _Dict {
  DictTuple* data;
  size_t     len;
  size_t     cap;
};
typedef struct _Dict* Dict;

Dict dict_new();
void dict_del(Dict self);
Dict dict_copy(const Dict self);

void   _dict_expand(Dict self);
bool_t _dict_isSpace(const Dict self, const size_t size);

size_t     dict_length(const Dict self);
size_t     dict_capacity(const Dict self);
DictTuple* dict_data(const Dict self);
Dict       dict_clear(Dict self);
Dict       dict_set(Dict self, str_t key, Object value);
Object     dict_get(const Dict self, strview_t key);
DictTuple* dict_getTuple(const Dict self, strview_t key);
strview_t* dict_keys(const Dict self);
Object     dict_setDefault(Dict self, strview_t key, Object def);

#ifdef __cplusplus
}
#endif

#endif  // _SIMPLEJSONC_DICT_H

#ifdef __cplusplus
extern "C" {
#endif

struct _Dict;
typedef struct _Dict* Dict;

#ifdef __cplusplus
}
#endif