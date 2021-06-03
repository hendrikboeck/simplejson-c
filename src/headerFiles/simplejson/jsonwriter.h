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

#ifndef _SIMPLEJSONC_SIMPLEJSONCWRITER_H
#define _SIMPLEJSONC_SIMPLEJSONCWRITER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simplejson/_internal.h"
#include "simplejson/dict.h"
#include "simplejson/str.h"
#include "simplejson/stringbuffer.h"

#define JSON_REV_ESCAPE_CHARS "\b\f\n\r\t\\\""
#define JSON_ESCAPE_CHARS     "bfnrt\\\""

struct _SIMPLEJSONCWriter {
  Dict         data;
  StringBuffer sbuf;
};
typedef struct _SIMPLEJSONCWriter* JSONWriter;

JSONWriter jsonwriter_new(Dict data);
void       jsonwriter_del(JSONWriter self);

strview_t jsonwriter_getStrView(JSONWriter self);

void __jsonwriter_serializeObject(JSONWriter self, const Object val);
void __jsonwriter_serializeNull(JSONWriter self);
void __jsonwriter_serializeInt64(JSONWriter self, const int64_t val);
void __jsonwriter_serializeFloat64(JSONWriter self, const float64_t val);
void __jsonwriter_serializeBool(JSONWriter self, const bool_t val);
void __jsonwriter_serializeStr(JSONWriter self, strview_t val);
void __jsonwriter_serializeList(JSONWriter self, const List val);
void __jsonwriter_serializeDict(JSONWriter self, const Dict val);

#ifdef __cplusplus
}
#endif

#endif  // _SIMPLEJSONC_SIMPLEJSONCWRITER_H