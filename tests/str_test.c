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

#include "simplejson/str.h"

static void test_str_new(void** state) {
  (void)state;

  str_t s_01 = str_new(255);
  assert_non_null(s_01);
  str_del(s_01);
}

static void test_str_length(void** state) {
  (void)state;

  assert_int_equal(str_length("1"), 1);
  assert_int_equal(str_length(""), 0);
}

static void test_str_copy(void** state) {
  (void)state;

  strview_t sv_01 = "Hello World!";
  str_t     s_01  = str_copy(sv_01);

  assert_ptr_not_equal(sv_01, s_01);
  assert_string_equal(sv_01, s_01);

  str_del(s_01);
}

static void test_str_equal(void** state) {
  (void)state;

  assert_true(str_equal("1234", "1234"));
  assert_false(str_equal("1234", "4321"));
}

static void test_str_contains(void** state) {
  (void)state;

  const char* cp_01 = str_containsChar("abcdef", 'b');
  assert_non_null(cp_01);
  assert_int_equal(*cp_01, 'b');

  const char* cp_02 = str_containsChar("abcdef", 'g');
  assert_null(cp_02);

  char* cp_03 = str_contains("abcdef", "de");
  assert_non_null(cp_03);
  assert_int_equal(*cp_03, 'd');
  assert_int_equal(*(cp_03 + 1), 'e');

  char* cp_04 = str_contains("abcdef", "fg");
  assert_null(cp_04);
}

static void test_str_startswith(void** state) {
  (void)state;

  assert_true(str_startsWithChar("abcdef", 'a'));
  assert_false(str_startsWithChar("abcdef", 'b'));

  assert_true(str_startsWith("abcdef", "ab"));
  assert_false(str_startsWith("abcdef", "bc"));
}