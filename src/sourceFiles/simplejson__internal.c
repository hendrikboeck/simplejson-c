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

#include "simplejson/_internal.h"

void* __copy(const void* src, const size_t size) {
  void* blk = NEW_BLK(size);
  memcpy(blk, src, size);
  return blk;
}

void* __move(void* src, const size_t size) {
  void* blk = __copy(src, size);
  DEL(blk);
  return blk;
}

void* __moveOnto(void* dest, void* src, const size_t size) {
  memcpy(dest, src, size);
  DEL(src);
  return dest;
}

void __error(strview_t msg) {
  fprintf(stderr, "ERROR: %s\n", msg);
}

void __errorExit(const int32_t code, strview_t msg) {
  __error(msg);
  exit(code);
}

void __fatalError(strview_t filename, int32_t linenumber, strview_t format,
                  ...) {
  fprintf(stderr, "Thrown FATAL_ERROR in file %s in line %d: ", filename,
          linenumber);
  va_list argp;
  va_start(argp, format);
  vfprintf(stderr, format, argp);
  va_end(argp);
  fprintf(stderr, "\n");
  raise(SIGNAL_FATAL_ERROR);
}