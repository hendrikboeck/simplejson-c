# simplejson-c

simplejson-c is a simple library, that converts json into a pythonlike dictionary and can convert this dictionary to json.

# Examples

## Read JSON

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

## Write JSON

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
