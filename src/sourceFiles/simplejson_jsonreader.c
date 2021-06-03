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

#include "simplejson/jsonreader.h"

JSONReader jsonreader_new(strview_t json) {
  JSONReader self = PNEW(JSONReader);

  self->buf  = str_copy(json);
  self->cur  = 0;
  self->len  = str_length(self->buf);
  self->dict = __jsonreader_parseDict(self);

  return self;
}

void jsonreader_del(JSONReader self) {
  str_del(self->buf);
  dict_del(self->dict);
  DEL(self);
}

Dict jsonreader_getDict(const JSONReader self) {
  return self->dict;
}

void __jsonreader_forward(JSONReader self) {
  for (; !__jsonreader_hitEOB(self); self->cur++) {
    if (self->buf[self->cur] != ' ' && self->buf[self->cur] != '\n') break;
  }
  if (__jsonreader_hitEOB(self)) FATAL_ERROR("hit EOB while forwarding");
}

bool_t __jsonreader_hitEOB(JSONReader self) {
  return (self->cur >= self->len);
}

bool_t __jsonreader_validateNextCharToken(JSONReader self, const char ctoken) {
  __jsonreader_forward(self);

  if (self->buf[self->cur] == ctoken) {
    self->cur++;
    return true;
  } else {
    return false;
  }
}

bool_t __jsonreader_validateNextToken(JSONReader self, strview_t stoken) {
  __jsonreader_forward(self);

  size_t stokenLength = str_length(stoken);
  if (strncmp(ADDR(self->buf[self->cur]), stoken, stokenLength) == 0) {
    self->cur += stokenLength;
    return true;
  } else {
    return false;
  }
}

str_t __jsonreader_getNextToken(JSONReader self, bool_t isSToken) {
  __jsonreader_forward(self);

  str_t        revEsc         = JSON_REV_ESCAPE_CHARS;
  str_t        esc            = JSON_ESCAPE_CHARS;
  str_t        tokenDelimiter = ",]}";
  StringBuffer sbuf           = stringbuffer_new();

  if (isSToken) {
    if (!__jsonreader_validateNextCharToken(self, '\"'))
      FATAL_ERROR("expected '\"', but found '%c' at \"%s\"",
                  self->buf[self->cur], ADDR(self->buf[self->cur]));

    for (; !__jsonreader_hitEOB(self); self->cur++) {
      char curChar = self->buf[self->cur];
      if (curChar == '\"')
        break;
      else if (curChar == '\\') {
        char* pEscChar = str_containsChar(esc, self->buf[++self->cur]);
        stringbuffer_putChar(sbuf, revEsc[pEscChar - esc]);
      } else
        stringbuffer_putChar(sbuf, curChar);
    }
  } else {
    for (; !__jsonreader_hitEOB(self); self->cur++) {
      char curChar = self->buf[self->cur];
      if (str_containsChar(tokenDelimiter, curChar))
        break;
      else if (curChar == ' ')
        continue;
      else
        stringbuffer_putChar(sbuf, curChar);
    }
  }

  str_t result = str_copy(stringbuffer_get(sbuf));
  stringbuffer_del(sbuf);
  return result;
}

bool_t __jsonreader_nextTokenContainsChar(JSONReader self, const char c) {
  bool_t foundC         = false;
  str_t  tokenDelimiter = ",]}";
  for (size_t i = self->cur + 1; i < self->len; i++) {
    char curChar = self->buf[i];
    if (curChar == ' ') {
      continue;
    } else if (curChar == '.') {
      foundC = true;
      break;
    } else if (str_containsChar(tokenDelimiter, self->buf[i])) {
      break;
    }
  }
  return foundC;
}

int32_t __jsonreader_getTypeOfNextToken(JSONReader self) {
  __jsonreader_forward(self);

  char nextChar = self->buf[self->cur];
  // str
  if (nextChar == '\"') {
    return STR_OBJ_TYPE;
  }
  // int or float
  else if (str_containsChar("-0123456789", nextChar) != NULL) {
    if (__jsonreader_nextTokenContainsChar(self, '.'))
      return FLOAT64_OBJ_TYPE;
    else
      return INT64_OBJ_TYPE;
  }
  // null
  else if (nextChar == 'n') {
    return NULL_OBJ_TYPE;
  }
  // bool
  else if (str_containsChar("tf", nextChar) != NULL) {
    return BOOL_OBJ_TYPE;
  }
  // list
  else if (nextChar == '[') {
    return LIST_OBJ_TYPE;
  }
  // dict
  else if (nextChar == '{') {
    return DICT_OBJ_TYPE;
  }

  FATAL_ERROR("type of next token is undefined");
}

Object __jsonreader_parseObject(JSONReader self) {
  switch (__jsonreader_getTypeOfNextToken(self)) {
    case NULL_OBJ_TYPE: ;
      vptr_t _null_ = __jsonreader_parseNull(self);
      return object_new(_null_);

    case INT64_OBJ_TYPE: ;
      int64_t _int_ = __jsonreader_parseInt64(self);
      return object_new(_int_);

    case FLOAT64_OBJ_TYPE: ;
      float64_t _float_ = __jsonreader_parseFloat64(self);
      return object_new(_float_);

    case BOOL_OBJ_TYPE: ;
      bool_t _bool_ = __jsonreader_parseBool(self);
      return object_new(_bool_);

    case STR_OBJ_TYPE: ;
      str_t _str_ = __jsonreader_parseStr(self);
      return object_new(_str_);

    case LIST_OBJ_TYPE: ;
      List _list_ = __jsonreader_parseList(self);
      return object_new(_list_);

    case DICT_OBJ_TYPE: ;
      Dict _dict_ = __jsonreader_parseDict(self);
      return object_new(_dict_);

    default:
      FATAL_ERROR("unkown object type");
  }
}

vptr_t __jsonreader_parseNull(JSONReader self) {
  if (__jsonreader_validateNextToken(self, "null")) {
    return NULL;
  } else {
    FATAL_ERROR("'null' could not be verified as a token found \"%s\"",
                ADDR(self->buf[self->cur]));
  }
}

int64_t __jsonreader_parseInt64(JSONReader self) {
  str_t   nextToken = __jsonreader_getNextToken(self, false);
  int64_t result    = atol(nextToken);
  str_del(nextToken);
  return result;
}

float64_t __jsonreader_parseFloat64(JSONReader self) {
  str_t     nextToken = __jsonreader_getNextToken(self, false);
  float64_t result    = atof(nextToken);
  str_del(nextToken);
  return result;
}

bool_t __jsonreader_parseBool(JSONReader self) {
  if (__jsonreader_validateNextToken(self, "true")) {
    return true;
  } else if (__jsonreader_validateNextToken(self, "false")) {
    return false;
  } else {
    FATAL_ERROR("expected bool, but found \"%s\"",
                __jsonreader_getNextToken(self, false));
  }
}

str_t __jsonreader_parseStr(JSONReader self) {
  str_t result = __jsonreader_getNextToken(self, true);
  self->cur++;
  return result;
}

List __jsonreader_parseList(JSONReader self) {
  List list = list_new();

  if (!__jsonreader_validateNextCharToken(self, '['))
    FATAL_ERROR("expected '[', but found '%c' at \"%s\"", self->buf[self->cur],
                ADDR(self->buf[self->cur]));
  if (__jsonreader_validateNextCharToken(self, ']')) return list;

  do {
    Object val = __jsonreader_parseObject(self);
    list_append(list, val);
  } while (__jsonreader_validateNextCharToken(self, ','));

  if (!__jsonreader_validateNextCharToken(self, ']'))
    FATAL_ERROR("expected ']', but found '%c' at \"%s\"", self->buf[self->cur],
                ADDR(self->buf[self->cur]));

  return list;
}

Dict __jsonreader_parseDict(JSONReader self) {
  Dict dict = dict_new();

  if (!__jsonreader_validateNextCharToken(self, '{'))
    FATAL_ERROR("expected '{', but found '%c' at \"%s\"", self->buf[self->cur],
                ADDR(self->buf[self->cur]));
  if (__jsonreader_validateNextCharToken(self, '}')) return dict;

  do {
    str_t key = __jsonreader_parseStr(self);
    __jsonreader_validateNextCharToken(self, ':');
    Object val = __jsonreader_parseObject(self);
    dict_set(dict, key, val);
  } while (__jsonreader_validateNextCharToken(self, ','));

  if (!__jsonreader_validateNextCharToken(self, '}'))
    FATAL_ERROR("expected '}', but found '%c' at \"%s\"", self->buf[self->cur],
                ADDR(self->buf[self->cur]));

  return dict;
}
