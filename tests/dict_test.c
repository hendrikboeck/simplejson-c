#include "simplejson/dict.h"

#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

static void test_dictionary_new(void** state) {
  (void)state;

  Dict d_01 = dict_new();

  assert_non_null(d_01);
  assert_non_null(d_01->data);
  assert_int_equal(d_01->cap, __DICT_INITIAL_CAP);
  assert_int_equal(d_01->len, 0);

  d_01 = dict_del(d_01);
  assert_null(d_01);
}

static void test_dictionary_expand(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  __dict_expand(d_01);

  assert_int_equal(d_01->cap, __DICT_INITIAL_CAP * 2);

  dict_del(d_01);
}

static void test_dictionary_isSpace(void** state) {
  (void)state;

  Dict d_01 = dict_new();

  assert_true(__dict_isSpace(d_01, __DICT_INITIAL_CAP));
  assert_false(__dict_isSpace(d_01, __DICT_INITIAL_CAP + 1));

  dict_del(d_01);
}

static void test_dictionary_set_get(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  Dict d_02 = dict_new();
  List l_01 = list_new();
  dict_set(d_01, str_copy("key_null"), object_new(NULL));
  dict_set(d_01, str_copy("key_int64"), object_new((int64_t)1234));
  dict_set(d_01, str_copy("key_float64"), object_new(12.34));
  dict_set(d_01, str_copy("key_bool_t"), object_new((bool_t)C_TRUE));
  dict_set(d_01, str_copy("key_bool_f"), object_new((bool_t)C_FALSE));
  dict_set(d_01, str_copy("key_str"), object_new(str_copy("string")));
  dict_set(d_01, str_copy("key_list"), object_new(l_01));
  dict_set(d_01, str_copy("key_dict"), object_new(d_02));

  assert_true(object_isNull(dict_get(d_01, "key_null")));
  assert_true(object_isInt64(dict_get(d_01, "key_int64")));
  assert_true(object_isFloat64(dict_get(d_01, "key_float64")));
  assert_true(object_isBool(dict_get(d_01, "key_bool_t")));
  assert_true(object_isBool(dict_get(d_01, "key_bool_f")));
  assert_true(object_isStr(dict_get(d_01, "key_str")));
  assert_true(object_isList(dict_get(d_01, "key_list")));
  assert_true(object_isDict(dict_get(d_01, "key_dict")));

  assert_int_equal(object_getInt64(dict_get(d_01, "key_int64")), 1234);
  assert_float_equal(object_getFloat64(dict_get(d_01, "key_float64")), 12.34,
                     0.000001);
  assert_true(object_getBool(dict_get(d_01, "key_bool_t")));
  assert_false(object_getBool(dict_get(d_01, "key_bool_f")));
  assert_string_equal(object_getStr(dict_get(d_01, "key_str")), "string");
  assert_ptr_equal(object_getList(dict_get(d_01, "key_list")), l_01);
  assert_ptr_equal(object_getDict(dict_get(d_01, "key_dict")), d_02);

  DictTuple* tpl_01 = dict_getTuple(d_01, "key_int64");
  DictTuple* tpl_02 = dict_getTuple(d_01, "key_int64_02");
  assert_non_null(tpl_01);
  assert_string_equal(tpl_01->key, "key_int64");
  assert_int_equal(object_getInt64(tpl_01->value), 1234);

  size_t d_01_length_before = dict_length(d_01);
  dict_set(d_01, str_copy("key_int64"), object_new((int64_t)5678));
  Object obj_01 = dict_get(d_01, "key_int64");
  assert_non_null(obj_01);
  assert_true(object_isInt64(obj_01));
  assert_int_equal(object_getInt64(obj_01), 5678);
  assert_int_equal(d_01_length_before, dict_length(d_01));

  Object obj_02 = dict_setDefault(d_01, "key_int64", object_new((int64_t)1111));
  Object obj_03 = dict_get(d_01, "key_int64_02");
  Object obj_04 =
      dict_setDefault(d_01, "key_int64_02", object_new((int64_t)1111));
  assert_non_null(obj_02);
  assert_int_equal(object_getInt64(obj_02), 5678);
  assert_null(obj_03);
  assert_non_null(obj_04);
  assert_int_equal(object_getInt64(obj_04), 1111);

  dict_del(d_01);
}

static void test_dictionary_copy(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  dict_set(d_01, str_copy("key"), object_new((int64_t)1234));
  Dict d_02 = dict_copy(d_01);

  assert_ptr_not_equal(d_01, d_02);
  assert_non_null(d_02);
  assert_int_equal(dict_length(d_01), dict_length(d_02));
  assert_int_equal(dict_capacity(d_01), dict_capacity(d_02));
  assert_ptr_not_equal(dict_data(d_01), dict_data(d_02));
  assert_ptr_not_equal(dict_get(d_01, "key"), dict_get(d_02, "key"));
  assert_int_equal(object_getInt64(dict_get(d_01, "key")),
                   object_getInt64(dict_get(d_02, "key")));

  dict_del(d_02);
  dict_del(d_01);
}

static void test_dictionary_length(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  assert_int_equal(dict_length(d_01), 0);

  dict_set(d_01, str_copy("key_int64"), object_new((int64_t)1234));
  assert_int_equal(dict_length(d_01), 1);

  dict_clear(d_01);
  assert_int_equal(dict_length(d_01), 0);

  dict_del(d_01);
}

static void test_dictionary_capacity(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  assert_int_equal(dict_capacity(d_01), __DICT_INITIAL_CAP);
  __dict_expand(d_01);
  assert_int_equal(dict_capacity(d_01), __DICT_INITIAL_CAP * 2);
  dict_clear(d_01);
  assert_int_equal(dict_capacity(d_01), __DICT_INITIAL_CAP * 2);

  dict_del(d_01);
}

static void test_dictionary_data(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  assert_ptr_equal(d_01->data, dict_data(d_01));

  dict_del(d_01);
}

static void test_dictionary_clear(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  dict_set(d_01, str_copy("key_01"), object_new((int64_t)1));
  dict_set(d_01, str_copy("key_02"), object_new((int64_t)2));
  dict_set(d_01, str_copy("key_03"), object_new((int64_t)3));
  dict_set(d_01, str_copy("key_04"), object_new((int64_t)4));
  dict_set(d_01, str_copy("key_05"), object_new((int64_t)5));

  assert_non_null(dict_data(d_01)[0].key);
  assert_non_null(dict_data(d_01)[0].value);
  assert_non_null(dict_data(d_01)[4].key);
  assert_non_null(dict_data(d_01)[4].value);

  dict_clear(d_01);

  assert_null(dict_data(d_01)[0].key);
  assert_null(dict_data(d_01)[0].value);
  assert_null(dict_data(d_01)[4].key);
  assert_null(dict_data(d_01)[4].value);
  assert_int_equal(dict_length(d_01), 0);
  assert_int_equal(dict_capacity(d_01), __DICT_INITIAL_CAP * 2);

  dict_del(d_01);
}

static void test_dictionary_keys(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  dict_set(d_01, str_copy("key_01"), object_new((int64_t)1));
  dict_set(d_01, str_copy("key_02"), object_new((int64_t)2));
  dict_set(d_01, str_copy("key_03"), object_new((int64_t)3));
  dict_set(d_01, str_copy("key_04"), object_new((int64_t)4));
  dict_set(d_01, str_copy("key_05"), object_new((int64_t)5));

  strview_t* d_01_keys = dict_keys(d_01);
  assert_ptr_equal(d_01_keys[0], dict_data(d_01)[0].key);
  assert_ptr_equal(d_01_keys[1], dict_data(d_01)[1].key);
  assert_ptr_equal(d_01_keys[2], dict_data(d_01)[2].key);
  assert_ptr_equal(d_01_keys[3], dict_data(d_01)[3].key);
  assert_ptr_equal(d_01_keys[4], dict_data(d_01)[4].key);
  DEL(d_01_keys);

  dict_del(d_01);
}
