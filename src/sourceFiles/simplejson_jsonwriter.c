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

#include "simplejson/jsonwriter.h"

JSONWriter jsonwriter_new(Dict data) {
  JSONWriter self = PNEW(JSONWriter);

  self->data = data;
  self->sbuf = stringbuffer_new();

  __jsonwriter_serializeDict(self, self->data);

  return self;
}

void* jsonwriter_del(JSONWriter self) {
  stringbuffer_del(self->sbuf);
  DEL(self);
  return NULL;
}

strview_t jsonwriter_getStrView(JSONWriter self) {
  return stringbuffer_get(self->sbuf);
}

void __jsonwriter_serializeObject(JSONWriter self, const Object val) {
  switch (val->type) {
    case NULL_OBJ_TYPE:
      __jsonwriter_serializeNull(self);
      break;

    case INT64_OBJ_TYPE:
      __jsonwriter_serializeInt64(self, object_getInt64(val));
      break;

    case FLOAT64_OBJ_TYPE:
      __jsonwriter_serializeFloat64(self, object_getFloat64(val));
      break;

    case BOOL_OBJ_TYPE:
      __jsonwriter_serializeBool(self, object_getBool(val));
      break;

    case STR_OBJ_TYPE:
      __jsonwriter_serializeStr(self, object_getStr(val));
      break;

    case LIST_OBJ_TYPE:
      __jsonwriter_serializeList(self, object_getList(val));
      break;

    case DICT_OBJ_TYPE:
      __jsonwriter_serializeDict(self, object_getDict(val));
      break;

    default:
      __errorExit(EXIT_FAILURE, "JSONWriter: unkown type to serialize");
      break;
  }
}

void __jsonwriter_serializeNull(JSONWriter self) {
  stringbuffer_put(self->sbuf, "null");
}

void __jsonwriter_serializeInt64(JSONWriter self, const int64_t val) {
  size_t valLength = snprintf(NULL, 0, "%ld", val);
  str_t  valString = str_new(valLength + 1);
  sprintf(valString, "%ld", val);
  stringbuffer_put(self->sbuf, valString);
  str_del(valString);
}

void __jsonwriter_serializeFloat64(JSONWriter self, const float64_t val) {
  size_t valLength = snprintf(NULL, 0, "%lf", val);
  str_t  valString = str_new(valLength + 1);
  sprintf(valString, "%lf", val);
  stringbuffer_put(self->sbuf, valString);
  str_del(valString);
}

void __jsonwriter_serializeBool(JSONWriter self, const bool_t val) {
  if (val)
    stringbuffer_put(self->sbuf, "true");
  else
    stringbuffer_put(self->sbuf, "false");
}

void __jsonwriter_serializeStr(JSONWriter self, strview_t val) {
  stringbuffer_putChar(self->sbuf, '\"');

  str_t revEsc = JSON_REV_ESCAPE_CHARS;
  str_t esc    = JSON_ESCAPE_CHARS;

  for (size_t i = 0; i < strlen(val); i++) {
    char* inSpecials = str_containsChar(revEsc, val[i]);
    if (inSpecials == NULL) {
      stringbuffer_putChar(self->sbuf, val[i]);
    } else {
      stringbuffer_putChar(self->sbuf, '\\');
      stringbuffer_putChar(self->sbuf, esc[inSpecials - revEsc]);
    }
  }

  stringbuffer_putChar(self->sbuf, '\"');
}

void __jsonwriter_serializeList(JSONWriter self, const List val) {
  stringbuffer_putChar(self->sbuf, '[');
  for (size_t i = 0; i < val->len; i++) {
    __jsonwriter_serializeObject(self, list_at(val, i));
    if (i < val->len - 1) stringbuffer_putChar(self->sbuf, ',');
  }
  stringbuffer_putChar(self->sbuf, ']');
}

void __jsonwriter_serializeDict(JSONWriter self, const Dict val) {
  stringbuffer_putChar(self->sbuf, '{');
  for (size_t i = 0; i < val->len; i++) {
    __jsonwriter_serializeStr(self, dict_data(val)[i].key);
    stringbuffer_putChar(self->sbuf, ':');
    __jsonwriter_serializeObject(self, dict_data(val)[i].value);
    if (i < val->len - 1) stringbuffer_putChar(self->sbuf, ',');
  }
  stringbuffer_putChar(self->sbuf, '}');
}
