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

#ifndef _SIMPLEJSONC__INTERNAL_H
#define _SIMPLEJSONC__INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                                TYPES                                       */
/******************************************************************************/

#include <stdint.h>
#include <stdlib.h>

typedef float  float32_t;
typedef double float64_t;

typedef enum { false, true } bool_t;

typedef void*       vptr_t;
typedef int8_t      byte_t;
typedef char*       str_t;
typedef const str_t strview_t;

/******************************************************************************/
/*                                MEMORY                                      */
/******************************************************************************/

#include <stdlib.h>
#include <string.h>

#define ADDR(obj)        (&(obj))
#define NEW_BLK(size)    malloc(size)
#define PSIZE(type)      (sizeof(*((type)NULL)))
#define PNEW(type)       ((type)NEW_BLK(PSIZE(type)))
#define NEW(type)        ((type*)NEW_BLK(sizeof(type)))
#define NEW_ARR(type, n) ((type*)NEW_BLK(sizeof(type) * n))
#define DEL(ptr)         free(ptr)

void* __copy(const void* src, const size_t size);
void* __move(void* src, const size_t size);
void* __moveOnto(void* dest, void* src, const size_t size);

/******************************************************************************/
/*                                SYSTEM                                      */
/******************************************************************************/

#include <signal.h>
#include <stdarg.h>
#include <stdio.h>

void __error(strview_t msg);
void __errorExit(const int32_t code, strview_t msg);

#define SIGNAL_FATAL_ERROR SIGUSR1

#define FATAL_ERROR(fmt, ...) \
  __fatalError(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
void __fatalError(strview_t filename, int32_t linenumber, strview_t format,
                  ...);

#ifdef __cplusplus
}
#endif

#endif  // _SIMPLEJSONC__INTERNAL_H