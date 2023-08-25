# ELC

ELC (Endeyshent Laboratories Config) - is a staticly typed config language and static library.

## Build-it

```console
$ cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build --config Release
```

You will get `libelc.a` in the root of the project.

## How to use it

For example usage see [`test/`](./test/).

Basic example:

```c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Lexer.h"

int main(void)
{
    Lexer l = { 0 };
    char* input = "string hello = \"Hello, World\"\n";

    Hashmap* config = ELC_Lexer_init(&l, input, 0);
    assert(config != NULL);

    for (size_t i = 0; i < config->size; i++) {
        printf("Config %zu (%s, %s, %s)\n", i, config->data[i].key, config->data[i].value, TokenType_toString(config->data[i].type));
    }

    Hashmap_free(config);

    return 0;
}
```
