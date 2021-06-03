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

#ifndef _SIMPLEJSONC_STRINGBUFFER_H
#define _SIMPLEJSONC_STRINGBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simplejson/_internal.h"
#include "simplejson/str.h"

#define __STRINGBUFFER_INITIAL_CAP 128

struct _StringBuffer {
  str_t  buf;
  size_t len;
  size_t cap;
};
typedef struct _StringBuffer* StringBuffer;

StringBuffer stringbuffer_new();
void         stringbuffer_del(StringBuffer self);
StringBuffer stringbuffer_copy(const StringBuffer self);

void   __stringbuffer_expand(StringBuffer self);
bool_t __stringbuffer_isSpace(StringBuffer self, const size_t size);

StringBuffer stringbuffer_clear(StringBuffer self);
StringBuffer stringbuffer_put(StringBuffer self, strview_t src);
StringBuffer stringbuffer_putChar(StringBuffer self, const char src);
strview_t    stringbuffer_get(StringBuffer self);

#ifdef __cplusplus
}
#endif

#endif  // _SIMPLEJSONC_STRINGBUFFER_H