<p align="center"><img height=64px src=".github/markdown/simplejson.png"></p>
<h1 align="center">simplejson-c</h1>

- [1. Abstract](#1-abstract)
- [2. Use simplejson-c into project](#2-use-simplejson-c-into-project)
- [3. Examples](#3-examples)
  - [3.1. Read JSON](#31-read-json)
  - [3.2. Write JSON](#32-write-json)

# 1. Abstract

The **simplejson-c** is a library that is built for eas of use, not for performance. It uses a structure similar to python. You generate JSON from a python-like dictionary and vice versa.

The dictionaries only store references to pointers and delete them on destruct. Therefore pointer-based values have to be copied. You can use the integrated `memory_*`-functions for like `memory_copy` or `str_copy`, with which you can copy values from the stack to the heap in one command.

The integrated `str.h` adds functions like `str_equal` or `str_contains`, which can also be used outside of the **simplejson-c** library.

The **simplejson-c** library features a very basic form of exceptions. The exceptions are just simple signals, that are raised, if an error occurred. You can handle those exceptions, by handling the signal `SIGNAL_FATAL_ERROR`.

# 2. Use simplejson-c into project

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED 99)
set(CMAKE_BUILD_TYPE_INIT "Release")

include(FetchContent)
FetchContent_Declare(
  simplejsonlib
  GIT_REPOSITORY https://github.com/hendrikboeck/simplejson-c.git
  GIT_TAG        develop
)
FetchContent_MakeAvailable(simplejsonlib)

include_directories(
  ${PROJECT_BINARY_DIR}/_deps/simplejsonlib-src/src/headerFiles
  ...
)

add_dependencies(<targetname> simplejson)
target_link_libraries(<targetname> simplejson)
```

# 3. Examples

## 3.1. Read JSON

```c
#include <stdio.h>
#include "simplejson/jsonreader.h"

strview_t  json   = "{\"key\": \"value\"}";
JSONReader reader = jsonreader_new(json);
Dict       dict   = jsonreader_getDict(reader);  // just reference

for(size_t i = 0; i < dict_length(dict); i++) {
  DictTuple tpl = dict_data(dict)[i];
  printf("key: '%s', value: '%s'\n", tpl.key, object_getStr(tpl.value));
}

jsonreader_del(reader);
```

## 3.2. Write JSON

```c
#include <stdio.h>
#include "simplejson/jsonwriter.h"

Dict dict = dict_new();
dict_set(str_copy("key"), object_new(str_copy("value")));
dict_set(str_copy("keyInt"), object_new((int64_t)1234));

JSONWriter writer = jsonwriter_new(dict);
printf("OUT: %s\n", jsonwriter_getStrView(writer));
// OUT: {"key":"value","keyInt":1234}

jsonwriter_del(writer);
dict_del(dict);
```
