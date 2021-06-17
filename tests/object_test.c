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

#include "simplejson/object.h"

static void test_object_new(void** state) {
  (void)state;

  Object obj_01 = object_new(NULL);
  Object obj_02 = object_new((int64_t)1234);
  Object obj_03 = object_new(12.34);
  Object obj_04 = object_new((bool_t)C_TRUE);
  Object obj_05 = object_new(str_copy("Hello"));
  Object obj_06 = object_new(list_new());
  Object obj_07 = object_new(dict_new());

  assert_non_null(obj_01);
  assert_non_null(obj_02);
  assert_non_null(obj_03);
  assert_non_null(obj_04);
  assert_non_null(obj_05);
  assert_non_null(obj_06);
  assert_non_null(obj_07);

  object_del(obj_01);
  object_del(obj_02);
  object_del(obj_03);
  object_del(obj_04);
  object_del(obj_05);
  object_del(obj_06);
  object_del(obj_07);
}

static void test_object_is(void** state) {
  (void)state;

  Object obj_01 = object_new(NULL);
  Object obj_02 = object_new((int64_t)1234);
  Object obj_03 = object_new(12.34);
  Object obj_04 = object_new((bool_t)C_TRUE);
  Object obj_05 = object_new(str_copy("Hello"));
  Object obj_06 = object_new(list_new());
  Object obj_07 = object_new(dict_new());

  assert_true(object_isNull(obj_01));
  assert_true(object_isInt64(obj_02));
  assert_true(object_isFloat64(obj_03));
  assert_true(object_isBool(obj_04));
  assert_true(object_isStr(obj_05));
  assert_true(object_isList(obj_06));
  assert_true(object_isDict(obj_07));

  assert_false(object_isNull(obj_07));
  assert_false(object_isInt64(obj_01));
  assert_false(object_isFloat64(obj_02));
  assert_false(object_isBool(obj_03));
  assert_false(object_isStr(obj_04));
  assert_false(object_isList(obj_05));
  assert_false(object_isDict(obj_06));

  object_del(obj_01);
  object_del(obj_03);
  object_del(obj_04);
  object_del(obj_05);
  object_del(obj_06);
  object_del(obj_07);
}

static void test_object_get(void** state) {
  (void)state;

  Object obj_02 = object_new((int64_t)1234);
  Object obj_03 = object_new(12.34);
  Object obj_04 = object_new((bool_t)C_TRUE);
  Object obj_05 = object_new(str_copy("Hello"));
  List   l_01   = list_new();
  Object obj_06 = object_new(l_01);
  Dict   d_01   = dict_new();
  Object obj_07 = object_new(d_01);

  assert_int_equal(object_getInt64(obj_02), 1234);
  assert_float_equal(object_getFloat64(obj_03), 12.34, 0.000001);
  assert_true(object_getBool(obj_04));
  assert_string_equal(object_getStr(obj_05), "Hello");
  assert_ptr_equal(object_getList(obj_06), l_01);
  assert_ptr_equal(object_getDict(obj_07), d_01);

  object_del(obj_02);
  object_del(obj_03);
  object_del(obj_04);
  object_del(obj_05);
  object_del(obj_06);
  object_del(obj_07);
}