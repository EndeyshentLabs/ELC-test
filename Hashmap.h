#ifndef ELC_HASHMAP_H_
#define ELC_HASHMAP_H_

#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} StringPair;

typedef struct {
    StringPair* data;
    size_t size;
    size_t capacity;
} Hashmap;

void Hashmap_init(Hashmap* array);
void Hashmap_push(Hashmap* array, const char* key, const char* value);

#endif // !ELC_HASHMAP_H_1