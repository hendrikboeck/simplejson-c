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

#ifndef _SIMPLEJSONC_SIMPLEJSONCREADER_H
#define _SIMPLEJSONC_SIMPLEJSONCREADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simplejson/_internal.h"
#include "simplejson/dict.h"
#include "simplejson/list.h"
#include "simplejson/object.h"
#include "simplejson/jsonwriter.h"
#include "simplejson/str.h"

struct _SIMPLEJSONCReader {
  str_t  buf;
  size_t cur;
  size_t len;
  Dict   dict;
};
typedef struct _SIMPLEJSONCReader* JSONReader;

JSONReader jsonreader_new(strview_t json);
void       jsonreader_del(JSONReader self);

Dict jsonreader_getDict(const JSONReader self);

void    __jsonreader_forward(JSONReader self);
bool_t  __jsonreader_hitEOB(JSONReader self);
bool_t  __jsonreader_validateNextCharToken(JSONReader self, const char ctoken);
bool_t  __jsonreader_validateNextToken(JSONReader self, strview_t stoken);
str_t   __jsonreader_getNextToken(JSONReader self, bool_t isSToken);
int32_t __jsonreader_getTypeOfNextToken(JSONReader self);

Object    __jsonreader_parseObject(JSONReader self);
vptr_t    __jsonreader_parseNull(JSONReader self);
int64_t   __jsonreader_parseInt64(JSONReader self);
float64_t __jsonreader_parseFloat64(JSONReader self);
bool_t    __jsonreader_parseBool(JSONReader self);
str_t     __jsonreader_parseStr(JSONReader self);
List      __jsonreader_parseList(JSONReader self);
Dict      __jsonreader_parseDict(JSONReader self);

#ifdef __cplusplus
}
#endif

#endif  // _SIMPLEJSONC_SIMPLEJSONCREADER_H