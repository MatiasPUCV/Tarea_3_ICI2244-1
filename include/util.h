#ifndef UTIL_H
#define UTIL_H

#include "list.h"

#include <stddef.h>
#include <stdbool.h>

// es malloc() y adicionalmente busca errores y cuenta las llamadas a malloc
void* Malloc(size_t size);
void* Calloc(size_t count, size_t size);

// ejecuta free() y cuenta la veces que se ha ejecutado
void Free(void* ptr);

// printf en verde
void Success(const char* fmt, ...);

// printf() pero con "[error]: " de sufijo en rojo
void Error(const char* fmt, ...);

char* GetStrFromInput();
int GetIntFromInput();

List* SeparateStr(char* str);
bool IsTxt(const char *str);
char* RemoveExtension(const char* str);

#endif