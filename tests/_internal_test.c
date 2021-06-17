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

#include "simplejson/_internal.h"

static void test_internal_boolean(void** state) {
  (void)state;

  assert_true(C_TRUE);
  assert_false(C_FALSE);
}

static void test_internal_memory(void** state) {
  (void)state;

  int32_t* d     = NEW(int32_t);
  *d             = 1234;
  int32_t* dCopy = (int32_t*)memory_copy(d, sizeof(int32_t));

  assert_non_null(d);
  assert_non_null(dCopy);
  assert_ptr_not_equal(d, dCopy);
  assert_int_equal(*d, *dCopy);
  assert_int_equal(*d, 1234);

  int32_t* dMove = (int32_t*)memory_move(d, sizeof(int32_t));

  assert_non_null(dMove);
  assert_int_equal(*dMove, 1234);

  int32_t* dMoveOnto =
      (int32_t*)memory_moveOnto(NEW(int32_t), dMove, sizeof(int32_t));

  assert_non_null(dMoveOnto != NULL);
  assert_int_equal(*dMoveOnto, 1234);

  DEL(dCopy);
  DEL(dMoveOnto);
}