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

#include "simplejson/stringbuffer.h"

static void test_stringbuffer_new(void** state) {
  (void)state;

  StringBuffer sbuf_01 = stringbuffer_new();

  assert_non_null(sbuf_01);
  assert_non_null(sbuf_01->buf);
  assert_int_equal(sbuf_01->len, 0);
  assert_int_equal(sbuf_01->cap, _STRINGBUFFER_INITIAL_CAP);

  stringbuffer_del(sbuf_01);
}

static void test_stringbuffer_copy(void** state) {
  (void)state;

  StringBuffer sbuf_01 = stringbuffer_new();
  stringbuffer_put(sbuf_01, "Hello World!");
  StringBuffer sbuf_02 = stringbuffer_copy(sbuf_01);

  assert_non_null(sbuf_02);
  assert_ptr_not_equal(sbuf_01, sbuf_02);
  assert_ptr_not_equal(sbuf_01->buf, sbuf_02->buf);
  assert_int_equal(sbuf_01->len, sbuf_02->len);
  assert_int_equal(sbuf_01->cap, sbuf_02->cap);
  assert_string_equal(stringbuffer_get(sbuf_01), stringbuffer_get(sbuf_02));

  stringbuffer_del(sbuf_01);
  stringbuffer_del(sbuf_02);
}

static void test_stringbuffer_expand(void** state) {
  (void)state;

  StringBuffer sbuf_01 = stringbuffer_new();
  assert_int_equal(sbuf_01->cap, _STRINGBUFFER_INITIAL_CAP);
  _stringbuffer_expand(sbuf_01);
  assert_int_equal(sbuf_01->cap, _STRINGBUFFER_INITIAL_CAP * 2);

  stringbuffer_del(sbuf_01);
}

static void test_stringbuffer_isSpace(void** state) {
  (void)state;

  StringBuffer sbuf_01 = stringbuffer_new();
  assert_true(_stringbuffer_isSpace(sbuf_01, _STRINGBUFFER_INITIAL_CAP));
  assert_false(_stringbuffer_isSpace(sbuf_01, _STRINGBUFFER_INITIAL_CAP + 1));

  stringbuffer_del(sbuf_01);
}

static void test_stringbuffer_clear(void** state) {
  (void)state;

  StringBuffer sbuf_01 = stringbuffer_new();
  stringbuffer_put(sbuf_01, "Hello World!");
  assert_int_not_equal(sbuf_01->len, 0);
  stringbuffer_clear(sbuf_01);
  assert_int_equal(sbuf_01->len, 0);

  stringbuffer_del(sbuf_01);
}

static void test_stringbuffer_put_get(void** state) {
  (void)state;

  StringBuffer sbuf_01 = stringbuffer_new();
  stringbuffer_put(sbuf_01, "Hello World!");
  assert_string_equal(stringbuffer_get(sbuf_01), "Hello World!");

  stringbuffer_putChar(sbuf_01, '?');
  assert_string_equal(stringbuffer_get(sbuf_01), "Hello World!?");

  stringbuffer_del(sbuf_01);
}
