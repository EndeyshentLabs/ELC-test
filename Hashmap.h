#ifndef ELC_HASHMAP_H_
#define ELC_HASHMAP_H_

#include <stdlib.h>

#include "Token.h"

typedef struct {
    char* key;
    char* value;
    TokenType type;
} ConfigElement;

typedef struct {
    ConfigElement* data;
    size_t size;
    size_t capacity;
} Hashmap;

void Hashmap_init(Hashmap* array);
void Hashmap_push(Hashmap* array, const char* key, const char* value, TokenType type);
void Hashmap_free(Hashmap* array);

#endif // ELC_HASHMAP_H_
