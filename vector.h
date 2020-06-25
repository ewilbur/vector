#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdbool.h>
#include <stdlib.h>
// #include "generics/printer.h"

#define DEVELOPMENT
#define ALLOW_UNTESTED

typedef void (*destructor)(void *);
void nothing(void *);

typedef struct vector {
    void **data;
    size_t size;
    size_t capacity;
    destructor destroy;
} vector;

/* | Initialize a vector with default vaules. You must initialize all vectors
 * before using them. Failing to do this will result in undefined behavior
 */
void vector_init(vector *);
/* | Free the memory of a vector when it is no longer needed. You need not free
 * a vector when you are done using it, however, the memory will not be freed
 * and will result in memory leaks.
 */
void vector_free(vector *);
/* | Clear the contents of the vector by using the destructor on the data and
 * setting the size of the vector to zero
 */
void vector_clear(vector *);

/* | Query the vector for the data stored at index. If the index
 * does not exist, or the vector is NULL, NULL is returned
 */
void * const vector_at(const vector * const, size_t);
size_t vector_size(const vector * const);
size_t vector_capacity(const vector * const);

bool vector_isEmpty(vector *);

void vector_pushBack(vector *, void *);
void vector_popBack(vector *);

void vector_setAt(vector *, size_t, void *);
void vector_fmap(vector *, void *(*f)(void *));
void vector_fmapi(vector *, void *(*f)(void *, size_t));
void vector_setDestroyFree(vector *v);
void vector_setDestroyNothing(vector *v);
void vector_concat(vector * , vector * , vector *);

#ifdef DEVELOPMENT
typedef void (*printer)(void *);
void vector_print(vector *, printer);

void print_int(void *);
#endif // DEVELOPMENT

#ifdef DEVELOPMENT
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

#endif
