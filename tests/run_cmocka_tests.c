// if autoformat puts <cmocka.h>, anywhere else then at the end of all global
// includes, then put it there manually
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
// <cmocka.h> --- below this comment
#include <cmocka.h>

// UNIT-TEST-FILES
#include "_internal_test.c"
#include "dict_test.c"
#include "jsonreader_test.c"
#include "jsonwriter_test.c"
#include "list_test.c"
#include "object_test.c"
#include "str_test.c"
#include "stringbuffer_test.c"

int main(void) {
  // test simplejson/_internal.h
  printf("--------- RUNNING TESTS FOR 'simplejson/_internal.h' ---------\n");
  const struct CMUnitTest tests_internal[] = {
      cmocka_unit_test(test_internal_boolean),
      cmocka_unit_test(test_internal_memory)};
  int return_tests_internal =
      cmocka_run_group_tests(tests_internal, NULL, NULL);

  // test simplejson/dict.h
  printf("\n--------- RUNNING TESTS FOR 'simplejson/dict.h' ---------\n");
  const struct CMUnitTest tests_dict[] = {
      cmocka_unit_test(test_dictionary_new),
      cmocka_unit_test(test_dictionary_expand),
      cmocka_unit_test(test_dictionary_isSpace),
      cmocka_unit_test(test_dictionary_set_get),
      cmocka_unit_test(test_dictionary_copy),
      cmocka_unit_test(test_dictionary_length),
      cmocka_unit_test(test_dictionary_capacity),
      cmocka_unit_test(test_dictionary_data),
      cmocka_unit_test(test_dictionary_clear),
      cmocka_unit_test(test_dictionary_keys)};
  int return_tests_dict = cmocka_run_group_tests(tests_dict, NULL, NULL);

  // test simplejson/list.h
  printf("\n--------- RUNNING TESTS FOR 'simplejson/list.h' ---------\n");
  const struct CMUnitTest tests_list[] = {cmocka_unit_test(test_list_new),
                                          cmocka_unit_test(test_list_expand),
                                          cmocka_unit_test(test_list_isSpace),
                                          cmocka_unit_test(test_list_copy),
                                          cmocka_unit_test(test_list_length),
                                          cmocka_unit_test(test_list_capacity),
                                          cmocka_unit_test(test_list_data),
                                          cmocka_unit_test(test_list_at_append),
                                          cmocka_unit_test(test_list_clear),
                                          cmocka_unit_test(test_list_insert),
                                          cmocka_unit_test(test_list_remove),
                                          cmocka_unit_test(test_list_pop)};
  int return_tests_list = cmocka_run_group_tests(tests_list, NULL, NULL);

  // test simplejson/str.h
  printf("\n--------- RUNNING TESTS FOR 'simplejson/str.h' ---------\n");
  const struct CMUnitTest tests_str[] = {
      cmocka_unit_test(test_str_new), cmocka_unit_test(test_str_length),
      cmocka_unit_test(test_str_copy), cmocka_unit_test(test_str_contains),
      cmocka_unit_test(test_str_startswith)};
  int return_tests_str = cmocka_run_group_tests(tests_str, NULL, NULL);

  // test simplejson/object.h
  printf("\n--------- RUNNING TESTS FOR 'simplejson/object.h' ---------\n");
  const struct CMUnitTest tests_object[] = {cmocka_unit_test(test_object_new),
                                            cmocka_unit_test(test_object_is),
                                            cmocka_unit_test(test_object_get)};
  int return_tests_object = cmocka_run_group_tests(tests_object, NULL, NULL);

  // test simplejson/stringbuffer.h
  printf(
      "\n--------- RUNNING TESTS FOR 'simplejson/stringbuffer.h' ---------\n");
  const struct CMUnitTest tests_stringbuffer[] = {
      cmocka_unit_test(test_stringbuffer_new),
      cmocka_unit_test(test_stringbuffer_copy),
      cmocka_unit_test(test_stringbuffer_expand),
      cmocka_unit_test(test_stringbuffer_isSpace),
      cmocka_unit_test(test_stringbuffer_put_get)};
  int return_tests_stringbuffer =
      cmocka_run_group_tests(tests_stringbuffer, NULL, NULL);

  // test simplejson/jsonwriter.h
  printf("\n--------- RUNNING TESTS FOR 'simplejson/jsonwriter.h' ---------\n");
  const struct CMUnitTest tests_jsonwriter[] = {
      cmocka_unit_test(test_jsonwriter_new),
      cmocka_unit_test(test_jsonwriter_getStrView)};
  int return_tests_jsonwriter =
      cmocka_run_group_tests(tests_jsonwriter, NULL, NULL);

  // test simplejson/jsonreader.h
  printf("\n--------- RUNNING TESTS FOR 'simplejson/jsonreader.h' ---------\n");
  const struct CMUnitTest tests_jsonreader[] = {
      cmocka_unit_test(test_jsonreader_new),
      cmocka_unit_test(test_jsonreader_getDict)};
  int return_tests_jsonreader =
      cmocka_run_group_tests(tests_jsonreader, NULL, NULL);

  return return_tests_internal + return_tests_dict + return_tests_list +
         return_tests_str + return_tests_object + return_tests_stringbuffer +
         return_tests_jsonwriter + return_tests_jsonreader;
}
