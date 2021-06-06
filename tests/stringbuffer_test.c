#include "simplejson/stringbuffer.h"

#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

static void test_stringbuffer_new(void** state) {
  (void)state;

  StringBuffer sbuf_01 = stringbuffer_new();

  assert_non_null(sbuf_01);
  assert_non_null(sbuf_01->buf);
  assert_int_equal(sbuf_01->len, 0);
  assert_int_equal(sbuf_01->cap, __STRINGBUFFER_INITIAL_CAP);

  sbuf_01 = stringbuffer_del(sbuf_01);
  assert_null(sbuf_01);
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
  assert_int_equal(sbuf_01->cap, __STRINGBUFFER_INITIAL_CAP);
  __stringbuffer_expand(sbuf_01);
  assert_int_equal(sbuf_01->cap, __STRINGBUFFER_INITIAL_CAP * 2);

  stringbuffer_del(sbuf_01);
}

static void test_stringbuffer_isSpace(void** state) {
  (void)state;

  StringBuffer sbuf_01 = stringbuffer_new();
  assert_true(__stringbuffer_isSpace(sbuf_01, __STRINGBUFFER_INITIAL_CAP));
  assert_false(__stringbuffer_isSpace(sbuf_01, __STRINGBUFFER_INITIAL_CAP + 1));

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
