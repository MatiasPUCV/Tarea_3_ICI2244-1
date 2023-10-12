#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

static size_t s_mallocCalls;
static size_t s_freeCalls;

// es malloc() y adicionalmente busca errores y cuenta las llamadas a malloc
void* Malloc(size_t size);
void* Calloc(size_t count, size_t size);
void Free(void* ptr);

void Success(const char* fmt, ...);
void Error(const char* fmt, ...);

void End();

#endif