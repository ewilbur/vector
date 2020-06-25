#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include <stdio.h>
#include <string.h>


#ifndef DEVELOPMENT
void ** vector_front(vector *);
void ** vector_back(vector *);
void vector_incSize(vector *);
void vector_decSize(vector *);
void vector_reserve(vector *, size_t);
void vector_setDestroy(vector *, destructor);
void vector_setSize(vector *v, size_t);
void vector_setData(vector *v, void **);
void vector_setCapacity(vector *v, size_t);
#endif // DEVELOPMENT

void nothing(void *datum) {
    return;
}

void vector_init(vector *v) {
    vector_setData(v, NULL);
    vector_setSize(v, 0);
    vector_setCapacity(v, 0);
    vector_setDestroy(v, nothing);
}

void vector_free(vector *v) {
    if (v == NULL) return;
    vector_clear(v);
    free(vector_front(v));
    vector_setData(v, NULL);
    vector_setCapacity(v, 0);
}

void vector_clear(vector *v) {
    size_t i = 0;
    for (i = 0; i < vector_size(v); ++i)
        v->destroy(v->data[i]);
    vector_setSize(v, 0); 
}

void * const vector_at(const vector * const v, size_t index) {
    if (vector_size(v) <= index) return NULL;
    return v->data[index];
}

size_t vector_size(const vector * const v) {
    if (v == NULL) return 0;
    return v->size;
}

size_t vector_capacity(const vector * const v) {
    if (v == NULL) return 0;
    return v->capacity;
}

void ** vector_front(vector *v) {
    if (v == NULL) return NULL;
    return v->data;
}

void ** vector_back(vector *v) {
    if (v == NULL) return NULL;
    return v->data + vector_size(v);
}

bool vector_isEmpty(vector *v) {
    return vector_size(v) == 0;
}

void vector_pushBack(vector *v, void *datum) {
    if (vector_size(v) == vector_capacity(v))
        vector_reserve(v, (vector_size(v) + 1) * 2);
    vector_incSize(v);
    vector_setAt(v, vector_size(v) - 1, datum);
}

void vector_popBack(vector *v) {
    v->destroy(vector_at(v, vector_size(v) - 1));
    vector_decSize(v);
}

void vector_setAt(vector *v, size_t index, void * datum) {
     if (index >= vector_size(v)) return;
     v->data[index] = datum;
}

void vector_fmap(vector *v, void *(*f)(void *)) {
    void **iter = vector_front(v);
    for (iter = vector_front(v); iter < vector_back(v); ++iter)
        *iter = f(*iter);
}

void vector_fmapi(vector *v, void *(*f)(void*,size_t)) {
    void **iter = vector_front(v);
    for (iter = vector_front(v); iter < vector_back(v); ++iter)
        *iter = f(*iter, iter - vector_front(v));
}

void vector_setDestroyFree(vector *v) {
    vector_setDestroy(v, free);
}

void vector_setDestroyNothing(vector *v) {
    vector_setDestroy(v, nothing);
}

void vector_setDestroy(vector *v, destructor d) {
    if (v == NULL) return;
    v->destroy = d;
}

void vector_reserve(vector *v, size_t new_capacity) {
    if (v == NULL) return;
    if (v->capacity < new_capacity) {
        if (v->capacity == 0)
            v->data = malloc(sizeof(void *) * new_capacity);
        else
            v->data = realloc(v->data, new_capacity * sizeof(void *));
        v->capacity = new_capacity;
    }
}

void vector_incSize(vector *v) {
    if (v == NULL) return;
    ++v->size;
}

void vector_decSize(vector *v) {
    if (vector_isEmpty(v)) return;
    --v->size;
}

void vector_setData(vector *v, void **data) {
    if (v == NULL) return;
    v->data = data;
}
void vector_setCapacity(vector *v, size_t capacity) {
    if (v == NULL) return;
    v->capacity = capacity;
}

void vector_setSize(vector *v, size_t size) {
    if (v == NULL) return;
    v->size = size;
}

void vector_concat(vector * frnt, vector * bck, vector *res) {
    if (res == NULL) return;
    vector_reserve(res, vector_size(frnt) + vector_size(bck));
    if (!vector_isEmpty(frnt))
        memcpy(vector_back(res), vector_front(frnt), sizeof(void *) * vector_size(frnt));
    vector_setSize(res, vector_size(frnt));
    if (!vector_isEmpty(bck))
        memcpy(vector_back(res), vector_front(bck), sizeof(void *) * vector_size(bck));
    vector_setSize(res, vector_size(frnt) + vector_size(bck));
}

#ifdef DEVELOPMENT
void vector_print(vector *v, printer p) {
    size_t i = 0;
    printf("Begin print:\n");
    for (i = 0; i < vector_size(v); ++i)
        p(vector_at(v, i));
    printf("\nVector size: %lu\n", vector_size(v));
    printf("Vector capacity: %lu\n", vector_capacity(v));
    printf("\n");
}

void print_int(void *datum) {
    printf("%d, ", (int)datum);
}
#endif
