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

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
// <cmocka.h> --- below this comment
#include <cmocka.h>

#include "simplejson/jsonreader.h"

static void test_jsonreader_new(void** state) {
  (void)state;

  JSONReader r_01 = jsonreader_new("{}");

  assert_non_null(r_01);
  assert_non_null(r_01->buf);
  assert_non_null(r_01->dict);
  assert_int_equal(r_01->len, str_length("{}"));

  jsonreader_del(r_01);
}

static void test_jsonreader_getDict(void** state) {
  (void)state;

  strview_t json_01 =
      "{\"key_null\":null,\"key_int64\":1234,\"key_float64\":12.340000,\"key_"
      "bool_t\":true,\"key_bool_f\":false,\"key_str\":\"string\",\"key_list_"
      "int\":[1,2,3,4],\"key_list_empty\":[],\"key_dict\":{}}";
  JSONReader r_01 = jsonreader_new(json_01);
  Dict       d_01 = jsonreader_getDict(r_01);

  assert_true(object_isNull(dict_get(d_01, "key_null")));
  assert_true(object_isInt64(dict_get(d_01, "key_int64")));
  assert_true(object_isFloat64(dict_get(d_01, "key_float64")));
  assert_true(object_isBool(dict_get(d_01, "key_bool_t")));
  assert_true(object_isBool(dict_get(d_01, "key_bool_f")));
  assert_true(object_isStr(dict_get(d_01, "key_str")));
  assert_true(object_isList(dict_get(d_01, "key_list_int")));
  assert_true(object_isList(dict_get(d_01, "key_list_empty")));
  assert_true(object_isDict(dict_get(d_01, "key_dict")));

  assert_int_equal(object_getInt64(dict_get(d_01, "key_int64")), 1234);
  assert_float_equal(object_getFloat64(dict_get(d_01, "key_float64")), 12.34,
                     0.000001);
  assert_true(object_getBool(dict_get(d_01, "key_bool_t")));
  assert_false(object_getBool(dict_get(d_01, "key_bool_f")));
  assert_string_equal(object_getStr(dict_get(d_01, "key_str")), "string");
  assert_non_null(object_getList(dict_get(d_01, "key_list_int")));
  assert_non_null(object_getList(dict_get(d_01, "key_list_empty")));
  assert_non_null(object_getDict(dict_get(d_01, "key_dict")));

  jsonreader_del(r_01);
}
