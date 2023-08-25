#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Lexer.h"

int main(void)
{
    char* input = "float? pi = 3.1415926535898\n"
                  "int? a = nil\n"
                  "string str = \"Hello, World!\"\n"
                  "char chr = 's'";
    Lexer l = { 0 };
    Hashmap* config = ELC_Lexer_init(&l, input, 0);
    assert(config != NULL);

    for (size_t i = 0; i < config->size; i++) {
        printf("Config %zu (%s, %s, %s)\n", i, config->data[i].key, config->data[i].value, TokenType_toString(config->data[i].type));
    }

    Hashmap_free(config);

    return 0;
}
