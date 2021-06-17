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
  const struct CMUnitTest tests_list[] = {
      cmocka_unit_test(test_internal_boolean),
      cmocka_unit_test(test_internal_memory),
      cmocka_unit_test(test_dictionary_new),
      cmocka_unit_test(test_dictionary_expand),
      cmocka_unit_test(test_dictionary_isSpace),
      cmocka_unit_test(test_dictionary_set_get),
      cmocka_unit_test(test_dictionary_copy),
      cmocka_unit_test(test_dictionary_length),
      cmocka_unit_test(test_dictionary_capacity),
      cmocka_unit_test(test_dictionary_data),
      cmocka_unit_test(test_dictionary_clear),
      cmocka_unit_test(test_dictionary_keys),
      cmocka_unit_test(test_list_new),
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
      cmocka_unit_test(test_list_pop),
      cmocka_unit_test(test_str_new),
      cmocka_unit_test(test_str_length),
      cmocka_unit_test(test_str_copy),
      cmocka_unit_test(test_str_contains),
      cmocka_unit_test(test_str_startswith),
      cmocka_unit_test(test_object_new),
      cmocka_unit_test(test_object_is),
      cmocka_unit_test(test_object_get),
      cmocka_unit_test(test_stringbuffer_new),
      cmocka_unit_test(test_stringbuffer_copy),
      cmocka_unit_test(test_stringbuffer_expand),
      cmocka_unit_test(test_stringbuffer_isSpace),
      cmocka_unit_test(test_stringbuffer_put_get),
      cmocka_unit_test(test_jsonwriter_new),
      cmocka_unit_test(test_jsonwriter_getStrView),
      cmocka_unit_test(test_jsonreader_new),
      cmocka_unit_test(test_jsonreader_getDict)};

  return cmocka_run_group_tests(tests_list, NULL, NULL);
}
