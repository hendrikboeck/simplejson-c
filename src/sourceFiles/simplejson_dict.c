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

#include "simplejson/dict.h"

Dict dict_new() {
  Dict self = PNEW(Dict);

  self->data = NEW_ARR(DictTuple, __DICT_INITIAL_CAP);
  self->len  = 0;
  self->cap  = __DICT_INITIAL_CAP;

  return self;
}

void dict_del(Dict self) {
  dict_clear(self);
  DEL(self->data);
  DEL(self);
}

Dict dict_copy(const Dict self) {
  Dict other = __copy(self, PSIZE(Dict));

  for (size_t i = 0; i < self->len; i++)
    other->data[i] = (DictTuple){.key   = str_copy(self->data[i].key),
                                 .value = object_copy(self->data[i].value)};

  return other;
}

void __dict_expand(Dict self) {
  self->cap *= 2;
  self->data = __moveOnto(NEW_ARR(DictTuple, self->cap), self->data,
                          self->len * sizeof(DictTuple));
}

bool_t __dict_isSpace(const Dict self, const size_t size) {
  return (self->len + size <= self->cap);
}

size_t dict_len(const Dict self) {
  return self->len;
}

size_t dict_cap(const Dict self) {
  return self->cap;
}

DictTuple* dict_data(const Dict self) {
  return self->data;
}

Dict dict_clear(Dict self) {
  for (size_t i = 0; i < self->len; i++) {
    DEL(self->data[i].key);
    object_del(self->data[i].value);
  }

  return self;
}

Dict dict_set(Dict self, strview_t key, Object value) {
  DictTuple* itr = dict_getTuple(self, key);

  if (itr) {
    object_del(itr->value);
    itr->value = value;
  } else {
    if (!__dict_isSpace(self, 1)) __dict_expand(self);
    self->data[self->len++] = (DictTuple){.key = key, .value = value};
  }
}

Object dict_get(Dict self, strview_t key) {
  DictTuple* itr = dict_getTuple(self, key);

  if (itr)
    return itr->value;
  else
    return NULL;
}

DictTuple* dict_getTuple(Dict self, strview_t key) {
  for (size_t i = 0; i < self->len; i++)
    if (strcmp(self->data[i].key, key) == 0) return ADDR(self->data[i]);

  return NULL;
}

strview_t* dict_keys(const Dict self) {
  str_t* keys = NEW_ARR(str_t, self->len);

  for (size_t i = 0; i < self->len; i++) keys[i] = self->data[i].key;

  return (strview_t*)keys;
}

Object dict_setDefault(Dict self, strview_t key, Object def) {
  DictTuple* itr = dict_getTuple(self, key);

  if (!itr) {
    dict_set(self, key, def);
    return def;
  } else {
    object_del(def);
    return itr->value;
  }
}