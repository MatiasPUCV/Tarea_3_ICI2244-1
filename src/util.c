#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static size_t s_mallocCalls;
static size_t s_freeCalls;

void* Malloc(size_t size)
{
    void* ptr = malloc(size);
    if (ptr == NULL)
    {
        Error("No se pudo alocar memoria.\nCerrando programa.");
        exit(1);
    }

    s_mallocCalls++;

    return ptr;
}

void* Calloc(size_t count, size_t size)
{
    void* ptr = calloc(count, size);
    if (ptr == NULL)
    {
        Error("No se pudo alocar memoria.\nCerrando programa.");
        exit(1);
    }

    s_mallocCalls++;

    return ptr;
}

void Free(void* ptr)
{
    free(ptr);
    s_freeCalls++;
}

void Success(const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    printf("\x1b[38;2;40;150;35m");
    vfprintf(stdout, fmt, args);
    printf("\x1b[0m\n");

    va_end(args);
}

// printf() pero con "[error] " de sufijo en rojo
void Error(const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    printf("\x1b[38;2;135;10;21m[error]: ");
    vfprintf(stdout, fmt, args);
    printf("\n\x1b[0m");

    va_end(args);
}

void End()
{
    Success("¡Programa Cerrado!\nLlamadas a malloc(): %i\nLlamadas a free():   %i", s_mallocCalls, s_freeCalls);

    if (s_mallocCalls - s_freeCalls != 0)
        printf("\n\x1b[38;2;135;10;21mFaltaron \x1b[38;2;180;20;23m%i\x1b[0m\x1b[38;2;135;10;21m llamadas a free()\x1b[0m\n", s_mallocCalls - s_freeCalls);
    else
        Success("\n¡Se ha liberado toda la memoria!");
}