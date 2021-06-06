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

#include "simplejson/object.h"

Object __object_newNull(vptr_t data) {
  Object self = PNEW(Object);

  self->type     = NULL_OBJ_TYPE;
  self->u._null_ = NULL;

  return self;
}

Object __object_newInt64(int64_t data) {
  Object self = PNEW(Object);

  self->type    = INT64_OBJ_TYPE;
  self->u._int_ = data;

  return self;
}

Object __object_newFloat64(float64_t data) {
  Object self = PNEW(Object);

  self->type      = FLOAT64_OBJ_TYPE;
  self->u._float_ = data;

  return self;
}

Object __object_newBool(bool_t data) {
  Object self = PNEW(Object);

  self->type     = BOOL_OBJ_TYPE;
  self->u._bool_ = data;

  return self;
}

Object __object_newStr(str_t data) {
  Object self = PNEW(Object);

  self->type    = STR_OBJ_TYPE;
  self->u._str_ = data;

  return self;
}

Object __object_newList(List data) {
  Object self = PNEW(Object);

  self->type     = LIST_OBJ_TYPE;
  self->u._list_ = data;

  return self;
}

Object __object_newDict(Dict data) {
  Object self = PNEW(Object);

  self->type     = DICT_OBJ_TYPE;
  self->u._dict_ = data;

  return self;
}

void* object_del(Object self) {
  switch (self->type) {
    case STR_OBJ_TYPE:
      DEL(self->u._str_);
      break;

    case LIST_OBJ_TYPE:
      list_del(self->u._list_);
      break;

    case DICT_OBJ_TYPE:
      dict_del(self->u._dict_);
      break;

    default:
      break;
  }

  DEL(self);
  return NULL;
}

Object object_copy(Object self) {
  Object other = __copy(self, PSIZE(Object));

  switch (self->type) {
    case STR_OBJ_TYPE:
      other->u._str_ = str_copy(self->u._str_);
      break;

    case LIST_OBJ_TYPE:
      other->u._list_ = list_copy(self->u._list_);
      break;

    case DICT_OBJ_TYPE:
      other->u._dict_ = dict_copy(self->u._dict_);
      break;

    default:
      break;
  }

  return other;
}

bool_t object_isNull(Object self) {
  return (self->type == NULL_OBJ_TYPE);
}

bool_t object_isInt64(Object self) {
  return (self->type == INT64_OBJ_TYPE);
}

bool_t object_isFloat64(Object self) {
  return (self->type == FLOAT64_OBJ_TYPE);
}

bool_t object_isBool(Object self) {
  return (self->type == BOOL_OBJ_TYPE);
}

bool_t object_isStr(Object self) {
  return (self->type == STR_OBJ_TYPE);
}

bool_t object_isList(Object self) {
  return (self->type == LIST_OBJ_TYPE);
}

bool_t object_isDict(Object self) {
  return (self->type == DICT_OBJ_TYPE);
}

int64_t object_getInt64(Object self) {
  return self->u._int_;
}

float64_t object_getFloat64(Object self) {
  return self->u._float_;
}

bool_t object_getBool(Object self) {
  return self->u._bool_;
}

strview_t object_getStr(Object self) {
  return (strview_t)self->u._str_;
}

List object_getList(Object self) {
  return self->u._list_;
}

Dict object_getDict(Object self) {
  return self->u._dict_;
}