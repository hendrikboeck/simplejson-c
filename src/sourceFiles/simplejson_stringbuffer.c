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

#include "simplejson/stringbuffer.h"

StringBuffer stringbuffer_new() {
  StringBuffer self = PNEW(StringBuffer);

  self->buf = str_new(__STRINGBUFFER_INITIAL_CAP);
  self->len = 0;
  self->cap = __STRINGBUFFER_INITIAL_CAP;

  return self;
}

void* stringbuffer_del(StringBuffer self) {
  str_del(self->buf);
  DEL(self);
  return NULL;
}

StringBuffer stringbuffer_copy(const StringBuffer self) {
  StringBuffer other = __copy(self, PSIZE(StringBuffer));
  other->buf         = __copy(self->buf, self->cap);
  return other;
}

void __stringbuffer_expand(StringBuffer self) {
  self->cap *= 2;
  self->buf = __moveOnto(str_new(self->cap), self->buf, self->len);
}

bool_t __stringbuffer_isSpace(StringBuffer self, const size_t size) {
  return (self->len + size <= self->cap);
}

StringBuffer stringbuffer_clear(StringBuffer self) {
}

StringBuffer stringbuffer_put(StringBuffer self, strview_t src) {
  size_t srcLen = str_length(src);

  while (!__stringbuffer_isSpace(self, srcLen)) __stringbuffer_expand(self);
  memcpy(ADDR(self->buf[self->len]), src, srcLen);
  self->len += srcLen;

  return self;
}

StringBuffer stringbuffer_putChar(StringBuffer self, char src) {
  if (!__stringbuffer_isSpace(self, 1)) __stringbuffer_expand(self);
  self->buf[self->len++] = src;

  return self;
}

strview_t stringbuffer_get(StringBuffer self) {
  if (!__stringbuffer_isSpace(self, 1)) __stringbuffer_expand(self);
  self->buf[self->len] = 0;

  return (strview_t)self->buf;
}
