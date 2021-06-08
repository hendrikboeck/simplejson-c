#include "simplejson/jsonwriter.h"

#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

static void test_jsonwriter_new(void** state) {
  (void)state;

  Dict       d_01 = dict_new();
  JSONWriter w_01 = jsonwriter_new(d_01);
  assert_non_null(w_01->data);
  assert_non_null(w_01->sbuf);
  assert_ptr_equal(w_01->data, d_01);

  dict_del(d_01);
  w_01 = jsonwriter_del(w_01);
  assert_null(w_01);
}

static void test_jsonwriter_getStrView(void** state) {
  (void)state;

  Dict d_01 = dict_new();
  Dict d_02 = dict_new();
  List l_01 = list_new();
  list_append(l_01, object_new((int64_t)1));
  list_append(l_01, object_new((int64_t)2));
  list_append(l_01, object_new((int64_t)3));
  list_append(l_01, object_new((int64_t)4));
  List l_02 = list_new();
  dict_set(d_01, str_copy("key_null"), object_new(NULL));
  dict_set(d_01, str_copy("key_int64"), object_new((int64_t)1234));
  dict_set(d_01, str_copy("key_float64"), object_new(12.34));
  dict_set(d_01, str_copy("key_bool_t"), object_new((bool_t)C_TRUE));
  dict_set(d_01, str_copy("key_bool_f"), object_new((bool_t)C_FALSE));
  dict_set(d_01, str_copy("key_str"), object_new(str_copy("string")));
  dict_set(d_01, str_copy("key_list_int"), object_new(l_01));
  dict_set(d_01, str_copy("key_list_empty"), object_new(l_02));
  dict_set(d_01, str_copy("key_dict"), object_new(d_02));

  JSONWriter w_01 = jsonwriter_new(d_01);
  assert_string_equal(
      jsonwriter_getStrView(w_01),
      "{\"key_null\":null,\"key_int64\":1234,\"key_float64\":12.340000,\"key_"
      "bool_t\":true,\"key_bool_f\":false,\"key_str\":\"string\",\"key_list_"
      "int\":[1,2,3,4],\"key_list_empty\":[],\"key_dict\":{}}");

  dict_del(d_01);
  jsonwriter_del(w_01);
}
