#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static size_t s_mallocCalls;
static size_t s_freeCalls;

// malloc() pero con cosas para debugging 
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

// calloc() pero con cosas para debugging 
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

// Free pero con cosas para debugging 
void Free(void* ptr)
{
    if (ptr == NULL)
        return;

    free(ptr);
    s_freeCalls++;
}

// printf en verde
void Success(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    printf("\x1b[38;2;40;150;35m");
    vfprintf(stdout, fmt, args);
    printf("\x1b[0m\n");

    va_end(args);
}

// printf() pero con "[error]: " de sufijo en rojo
void Error(const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    printf("\x1b[38;2;135;10;21m[error]: ");
    vfprintf(stdout, fmt, args);
    printf("\n\x1b[0m");

    va_end(args);
}

// Consigue un str de input
// (admite espacios)
char* GetStrFromInput()
{
    // Consigue el numero de opción insertada
    char* str = Malloc(sizeof(char) * 100);
    if (scanf("%[^\n]", str) != 1)
    {
        Free(str);
        return NULL;
    }

    // Limpia el buffer de entrada
    int c; while ((c = getchar()) != '\n' && c != EOF);

    return str;
}

// Consigue un int del input esto
// transformando el primer caracter de una str en int
int GetIntFromInput()
{
    char* str = GetStrFromInput();
    int code = str[0] - 48;

    Free(str);

    return code;
}

// Serapara por espacios una str
// y devuelve una lista con las separaciones
List* SeparateStr(char *str)
{
    char *copia = strdup(str);

    if (copia == NULL) 
        return NULL;

    List* list = CreateList();

    char* token = strtok(copia, " ");

    while (token != NULL)
    {
        PushBack(list, token);
        Error("%s", token);
        token = strtok(NULL, " ");
    }

    return list;
}

char* RemoveExtension(const char* str)
{
    int len = strlen(str);

    int pos;
    for (pos = 0; pos < len; pos++)
    {
        char c = str[len - pos - 1];
        if (c == '.')
            break;
    }

    char* result = Calloc(pos + 1, sizeof(char));
    for (int i = 0; i < pos; i++)
        result[i] = str[i];

    return result;
}

// revisa si una str termina en .txt
bool IsTxt(const char *str)
{
    int len = strlen(str);
    if (len < 4)
        return false;
    
    const char *final = str + len - 4;
    
    if (strcmp(final, ".txt") == 0)
        return true;
    
    return false;
}

// Debugging
void End()
{
    Success("¡Programa Cerrado!\nLlamadas a malloc(): %i\nLlamadas a free():   %i", s_mallocCalls, s_freeCalls);

    if (s_mallocCalls - s_freeCalls != 0)
        printf("\n\x1b[38;2;135;10;21mFaltaron \x1b[38;2;180;20;23m%i\x1b[0m\x1b[38;2;135;10;21m llamadas a free()\x1b[0m\n", s_mallocCalls - s_freeCalls);
    else
        Success("\n¡Se ha liberado toda la memoria!");
}