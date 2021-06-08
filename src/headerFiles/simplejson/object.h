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

#ifndef _SIMPLEJSONC_OBJECT_H
#define _SIMPLEJSONC_OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simplejson/_internal.h"
#include "simplejson/dict.h"
#include "simplejson/list.h"
#include "simplejson/str.h"

#define NULL_OBJ_TYPE    0
#define INT64_OBJ_TYPE   1
#define FLOAT64_OBJ_TYPE 2
#define BOOL_OBJ_TYPE    3
#define STR_OBJ_TYPE     4
#define LIST_OBJ_TYPE    5
#define DICT_OBJ_TYPE    6

union _ObjectTypes {
  vptr_t    _null_;
  int64_t   _int_;
  float64_t _float_;
  bool_t    _bool_;
  str_t     _str_;
  List      _list_;
  Dict      _dict_;
};
typedef union _ObjectTypes ObjectTypes;

struct _Object {
  int32_t     type;
  ObjectTypes u;
};
typedef struct _Object* Object;

// DEPRECATED
#define OBJ_TYPE(X)                      \
  _Generic((X), vptr_t                   \
           : NULL_OBJ_TYPE, int64_t      \
           : INT64_OBJ_TYPE, float64_t   \
           : FLOAT64_OBJ_TYPE, float32_t \
           : FLOAT64_OBJ_TYPE, bool_t    \
           : BOOL_OBJ_TYPE, str_t        \
           : STR_OBJ_TYPE, List          \
           : LIST_OBJ_TYPE, Dict         \
           : DICT_OBJ_TYPE)

#define object_new(obj)                     \
  _Generic((obj), vptr_t                    \
           : __object_newNull, int64_t      \
           : __object_newInt64, float64_t   \
           : __object_newFloat64, float32_t \
           : __object_newFloat64, bool_t    \
           : __object_newBool, str_t        \
           : __object_newStr, List          \
           : __object_newList, Dict         \
           : __object_newDict)(obj)

Object __object_newNull(vptr_t data);
Object __object_newInt64(int64_t data);
Object __object_newFloat64(float64_t data);
Object __object_newBool(bool_t data);
Object __object_newStr(str_t data);
Object __object_newList(List data);
Object __object_newDict(Dict data);
void*  object_del(Object self);
Object object_copy(const Object self);

bool_t object_isNull(Object self);
bool_t object_isInt64(Object self);
bool_t object_isFloat64(Object self);
bool_t object_isBool(Object self);
bool_t object_isStr(Object self);
bool_t object_isList(Object self);
bool_t object_isDict(Object self);

int64_t   object_getInt64(Object self);
float64_t object_getFloat64(Object self);
bool_t    object_getBool(Object self);
strview_t object_getStr(Object self);
List      object_getList(Object self);
Dict      object_getDict(Object self);

#ifdef __cplusplus
}
#endif

#endif  // _SIMPLEJSONC_OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

struct _Object;
typedef struct _Object* Object;

#ifdef __cplusplus
}
#endif