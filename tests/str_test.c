#include "simplejson/str.h"

#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

static void test_str_new(void** state) {
  (void)state;

  str_t s_01 = str_new(255);
  assert_non_null(s_01);
  s_01 = str_del(s_01);
  assert_null(s_01);
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