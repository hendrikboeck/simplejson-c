#include "simplejson/list.h"

#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

static void test_list_new(void** state) {
  (void)state;

  List l_01 = list_new();

  assert_non_null(l_01);
  assert_non_null(l_01->data);
  assert_int_equal(l_01->cap, _LIST_INITIAL_CAP);
  assert_int_equal(l_01->len, 0);

  list_del(l_01);
}

static void test_list_expand(void** state) {
  (void)state;

  List l_01 = list_new();
  assert_int_equal(list_capacity(l_01), _LIST_INITIAL_CAP);
  _list_expand(l_01);
  assert_int_equal(list_capacity(l_01), _LIST_INITIAL_CAP * 2);

  list_del(l_01);
}

static void test_list_isSpace(void** state) {
  (void)state;

  List l_01 = list_new();
  assert_true(_list_isSpace(l_01, _LIST_INITIAL_CAP));
  assert_false(_list_isSpace(l_01, _LIST_INITIAL_CAP + 1));

  list_del(l_01);
}

static void test_list_copy(void** state) {
  (void)state;

  List l_01 = list_new();
  list_append(l_01, object_new((int64_t)1234));
  List l_02 = list_copy(l_01);

  assert_ptr_not_equal(l_01, l_02);
  assert_non_null(l_02);
  assert_int_equal(list_length(l_01), list_length(l_02));
  assert_int_equal(list_capacity(l_01), list_capacity(l_02));
  assert_ptr_not_equal(list_data(l_01), list_data(l_02));
  assert_ptr_not_equal(list_at(l_01, 0), list_at(l_02, 0));
  assert_int_equal(object_getInt64(list_at(l_01, 0)),
                   object_getInt64(list_at(l_02, 0)));

  list_del(l_01);
  list_del(l_02);
}

static void test_list_length(void** state) {
  (void)state;

  List l_01 = list_new();
  assert_int_equal(list_length(l_01), 0);

  list_append(l_01, object_new((int64_t)1234));
  assert_int_equal(list_length(l_01), 1);

  list_clear(l_01);
  assert_int_equal(list_length(l_01), 0);

  list_del(l_01);
}

static void test_list_capacity(void** state) {
  (void)state;

  List l_01 = list_new();
  assert_int_equal(list_capacity(l_01), _LIST_INITIAL_CAP);

  _list_expand(l_01);
  assert_int_equal(list_capacity(l_01), _LIST_INITIAL_CAP * 2);

  list_clear(l_01);
  assert_int_equal(list_capacity(l_01), _LIST_INITIAL_CAP * 2);

  list_del(l_01);
}

static void test_list_data(void** state) {
  (void)state;

  List l_01 = list_new();
  assert_ptr_equal(l_01->data, list_data(l_01));

  list_del(l_01);
}

static void test_list_at_append(void** state) {
  (void)state;

  List l_01 = list_new();
  Dict d_01 = dict_new();
  List l_02 = list_new();
  list_append(l_01, object_new(NULL));
  list_append(l_01, object_new((int64_t)1234));
  list_append(l_01, object_new(12.34));
  list_append(l_01, object_new((bool_t)C_TRUE));
  list_append(l_01, object_new((bool_t)C_FALSE));
  list_append(l_01, object_new(str_copy("string")));
  list_append(l_01, object_new(l_02));
  list_append(l_01, object_new(d_01));

  assert_int_equal(list_length(l_01), 8);
  assert_true(object_isNull(list_at(l_01, 0)));
  assert_true(object_isInt64(list_at(l_01, 1)));
  assert_true(object_isFloat64(list_at(l_01, 2)));
  assert_true(object_isBool(list_at(l_01, 3)));
  assert_true(object_isBool(list_at(l_01, 4)));
  assert_true(object_isStr(list_at(l_01, 5)));
  assert_true(object_isList(list_at(l_01, 6)));
  assert_true(object_isDict(list_at(l_01, 7)));

  assert_int_equal(object_getInt64(list_at(l_01, 1)), 1234);
  assert_float_equal(object_getFloat64(list_at(l_01, 2)), 12.34, 0.000001);
  assert_true(object_getBool(list_at(l_01, 3)));
  assert_false(object_getBool(list_at(l_01, 4)));
  assert_string_equal(object_getStr(list_at(l_01, 5)), "string");
  assert_ptr_equal(object_getList(list_at(l_01, 6)), l_02);
  assert_ptr_equal(object_getDict(list_at(l_01, 7)), d_01);

  list_del(l_01);
}

static void test_list_clear(void** state) {
  (void)state;

  List l_01 = list_new();
  list_append(l_01, object_new((int64_t)1));
  list_append(l_01, object_new((int64_t)2));
  list_append(l_01, object_new((int64_t)3));
  list_append(l_01, object_new((int64_t)4));
  list_append(l_01, object_new((int64_t)5));

  assert_non_null(list_at(l_01, 0));
  assert_non_null(list_at(l_01, 1));
  assert_non_null(list_at(l_01, 2));
  assert_non_null(list_at(l_01, 3));
  assert_non_null(list_at(l_01, 4));

  list_clear(l_01);

  assert_int_equal(list_length(l_01), 0);
  assert_int_equal(list_capacity(l_01), _LIST_INITIAL_CAP * 2);

  list_del(l_01);
}

static void test_list_insert(void** state) {
  (void)state;

  List l_01 = list_new();
  list_insert(l_01, list_length(l_01), object_new((int64_t)1));
  list_insert(l_01, list_length(l_01), object_new((int64_t)2));
  list_insert(l_01, list_length(l_01), object_new((int64_t)3));
  list_insert(l_01, list_length(l_01), object_new((int64_t)4));
  list_insert(l_01, list_length(l_01), object_new((int64_t)5));

  assert_int_equal(list_length(l_01), 5);
  assert_int_equal(object_getInt64(list_at(l_01, 0)), 1);
  assert_int_equal(object_getInt64(list_at(l_01, 1)), 2);
  assert_int_equal(object_getInt64(list_at(l_01, 2)), 3);
  assert_int_equal(object_getInt64(list_at(l_01, 3)), 4);
  assert_int_equal(object_getInt64(list_at(l_01, 4)), 5);

  list_insert(l_01, 0, object_new((int64_t)0));
  assert_int_equal(list_length(l_01), 6);
  assert_int_equal(object_getInt64(list_at(l_01, 0)), 0);
  assert_int_equal(object_getInt64(list_at(l_01, 1)), 1);
  assert_int_equal(object_getInt64(list_at(l_01, 2)), 2);
  assert_int_equal(object_getInt64(list_at(l_01, 3)), 3);
  assert_int_equal(object_getInt64(list_at(l_01, 4)), 4);
  assert_int_equal(object_getInt64(list_at(l_01, 5)), 5);

  list_del(l_01);
}

static void test_list_remove(void** state) {
  (void)state;

  List l_01 = list_new();
  list_append(l_01, object_new((int64_t)1));
  list_append(l_01, object_new((int64_t)2));
  list_append(l_01, object_new((int64_t)3));
  list_append(l_01, object_new((int64_t)4));
  list_append(l_01, object_new((int64_t)5));

  assert_int_equal(list_length(l_01), 5);
  assert_int_equal(object_getInt64(list_at(l_01, 0)), 1);
  assert_int_equal(object_getInt64(list_at(l_01, 1)), 2);
  assert_int_equal(object_getInt64(list_at(l_01, 2)), 3);
  assert_int_equal(object_getInt64(list_at(l_01, 3)), 4);
  assert_int_equal(object_getInt64(list_at(l_01, 4)), 5);

  list_remove(l_01, 0);
  assert_int_equal(list_length(l_01), 4);
  assert_int_equal(object_getInt64(list_at(l_01, 0)), 2);
  assert_int_equal(object_getInt64(list_at(l_01, 1)), 3);
  assert_int_equal(object_getInt64(list_at(l_01, 2)), 4);
  assert_int_equal(object_getInt64(list_at(l_01, 3)), 5);

  list_del(l_01);
}

static void test_list_pop(void** state) {
  (void)state;

  List l_01 = list_new();
  list_append(l_01, object_new((int64_t)1));
  list_append(l_01, object_new((int64_t)2));
  list_append(l_01, object_new((int64_t)3));
  list_append(l_01, object_new((int64_t)4));
  list_append(l_01, object_new((int64_t)5));

  assert_int_equal(list_length(l_01), 5);
  assert_int_equal(object_getInt64(list_at(l_01, 0)), 1);
  assert_int_equal(object_getInt64(list_at(l_01, 1)), 2);
  assert_int_equal(object_getInt64(list_at(l_01, 2)), 3);
  assert_int_equal(object_getInt64(list_at(l_01, 3)), 4);
  assert_int_equal(object_getInt64(list_at(l_01, 4)), 5);

  Object obj_01 = list_pop(l_01, 0);
  assert_non_null(obj_01);
  assert_int_equal(object_getInt64(obj_01), 1);
  assert_int_equal(list_length(l_01), 4);
  assert_int_equal(object_getInt64(list_at(l_01, 0)), 2);
  assert_int_equal(object_getInt64(list_at(l_01, 1)), 3);
  assert_int_equal(object_getInt64(list_at(l_01, 2)), 4);
  assert_int_equal(object_getInt64(list_at(l_01, 3)), 5);

  object_del(obj_01);
  list_del(l_01);
}
