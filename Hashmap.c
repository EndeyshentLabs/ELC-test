#include "Hashmap.h"

#include <assert.h>
#include <string.h>

#define HASHMAP_CAP 32

void Hashmap_init(Hashmap* array)
{
    array->data = malloc(HASHMAP_CAP * sizeof(ConfigElement));
    array->size = 0;
    array->capacity = HASHMAP_CAP;
}

void Hashmap_push(Hashmap* array, const char* key, const char* value, TokenType type)
{
    if (array->size >= array->capacity) {
        array->capacity *= 2; // Double the capacity when full
        array->data = realloc(array->data, array->capacity * sizeof(ConfigElement));
        assert(array->data != NULL && "BUY MORE RAM lol");
    }

    ConfigElement* pair = &(array->data[array->size]);
    pair->key = strdup(key);
    pair->value = strdup(value);
    pair->type = type;
    array->size++;
}

void Hashmap_free(Hashmap* array)
{
    for (size_t i = 0; i < array->size; i++) {
        free(array->data[i].key);
        free(array->data[i].value);
    }
    free(array->data);
}
