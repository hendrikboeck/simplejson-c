# simplejson-c

simplejson-c is a simple library, that converts json into a pythonlike dictionary and can convert this dictionary to json.

## Use into project

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED 99)
set(CMAKE_BUILD_TYPE_INIT "Release")

include(ExternalProject)
ExternalProject_Add(
  simplejson

  GIT_REPOSITORY    https://github.com/hendrikboeck/simplejson-c.git
  GIT_TAG           stable

  INSTALL_COMMAND   ""

  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)
ExternalProject_Get_Property(simplejson install_dir)
find_library(simplejson ${install_dir})

include_directories(
  ${install_dir}/src/simplejson/src/headerFiles
  ...
)
add_dependencies(<targetname> simplejson)
target_link_libraries(<targetname> libsimplejson)
```

## Examples

### Read JSON

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

### Write JSON

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
