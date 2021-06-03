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

#include "simplejson/list.h"

List list_new() {
  List self = PNEW(List);

  self->data = NEW_ARR(Object, __LIST_INITIAL_CAP);
  self->len  = 0;
  self->cap  = __LIST_INITIAL_CAP;

  return self;
}

void list_del(List self) {
  list_clear(self);
  DEL(self->data);
  DEL(self);
}

List list_copy(const List self) {
  List other = PNEW(List);

  other->cap  = self->cap;
  other->len  = self->len;
  other->data = NEW_ARR(Object, other->cap);

  for (size_t i = 0; i < self->len; i++)
    other->data[i] = object_copy(self->data[i]);

  return other;
}

void __list_expand(List self) {
  self->cap *= 2;
  self->data = __moveOnto(NEW_ARR(Object, self->cap), self->data,
                          self->len * sizeof(Object));
}

bool_t __list_isSpace(const List self, const size_t size) {
  return (self->len + size <= self->cap);
}

size_t list_len(List self) {
  return self->len;
}

size_t list_cap(const List self) {
  return self->cap;
}

Object list_at(const List self, const size_t index) {
  return self->data[index];
}

Object* list_data(const List self) {
  return self->data;
}

List list_append(List self, Object obj) {
  return list_insert(self, self->len, obj);
}

List list_clear(List self) {
  for (size_t i = 0; i < self->len; i++) object_del(self->data[i]);
  self->len = 0;
}

List list_extend(List self, const List other) {
  while (!__list_isSpace(self, other->len)) __list_expand(self);

  for (size_t i = 0; i < other->len; i++)
    self->data[self->len + i] = object_copy(other->data[i]);
  self->len += other->len;

  return self;
}

List list_insert(List self, const size_t index, Object obj) {
  if (!__list_isSpace(self, 1)) __list_expand(self);

  for (size_t i = self->len; i > index; i--) self->data[i] = self->data[i - 1];
  self->data[index] = obj;
  self->len++;

  return self;
}

List list_remove(List self, const size_t index) {
  object_del(self->data[index]);
  for (size_t i = index; i < self->len - 1; i++)
    self->data[i] = self->data[i + 1];
  self->len--;
  return self;
}

Object list_pop(List self, const size_t index) {
  Object obj = object_copy(self->data[index]);
  list_remove(self, index);
  return obj;
}
