#include "app.h"
#include "util.h"
#include "list.h"
#include "file.h"
#include "book.h"
#include "heap.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Crea información de la applicacion
AppData* CreateAppData()
{
    AppData* temp = Malloc(sizeof(AppData));

    temp->books       = CreateTreeMap(lower_than_string);
    temp->books_by_id = CreateTreeMap(lower_than_int);

    return temp;
}

// libera memoria de la aplicacion
void FreeAppData(AppData* data)
{
    Pair* pair = FirstTreeMap(data->books);
    while(pair != NULL)
    {
        Book* book = (Book*)(pair->value);
        FreeBook(book);
        Free(pair);

        pair = NextTreeMap(data->books);
    }

    Free(data->books);

    pair = FirstTreeMap(data->books_by_id);
    while (pair != NULL)
    {
        Free(pair);
        pair = NextTreeMap(data->books_by_id);
    }
    
    Free(data->books_by_id);
}

// carga los documentos
void AppLoadDocuments(AppData* data)
{
    // consigue el input y lo divide en plabras
    char* input = GetStrFromInput();
    List* docs = SeparateStr(input);

    // listas auxiliares
    List* files = CreateList();
    List* dirs = CreateList();

    // lee y valida los nombres de los archivo y carpetas
    while (FirstList(docs) != NULL)
    {
        char* temp = PopFront(docs);

        if (IsTxt(temp))
            PushFront(files, CreateFileFromPath(temp));

        // si no es txt o es tiene un . no puede ser una carpeta
        // aunque las carpetas si pueden iniciar con punto, como .git
        else if (strchr(temp, '.') == NULL)
            PushFront(dirs, temp);
    }

    Free(docs);

    // pasa todos los archivo encontrados en las carpetas
    // que sean .txt
    while (FirstList(dirs) != NULL)
    {
        char* temp = PopFront(dirs);
        List* dir_files = GetDirList(temp);

        while (FirstList(dir_files) != NULL)
        {
            File* file = PopFront(dir_files);
            
            if(IsTxt(file->dir))
                PushFront(files, file);

            else
                FreeFile(file);
        }

        Free(dir_files);
        Free(temp);
    }

    Free(dirs);

    int i = 0;
    printf("\n");

    while (FirstList(files) != NULL)
    {
        File* file = PopFront(files);
        
        printf("Cargando \"%s\"...\n", file->dir);
        Book* book = CreateBook(file);
        Success("¡\"%s\" cargado!\n", book->title);

        InsertTreeMap(data->books, book->title, book);
        InsertTreeMap(data->books_by_id, &book->id, book);

        FreeFile(file);
    }

    Free(files);
    Free(input);
}

// Recorre el mapa de los libros y muestra su información
void AppShowBooks(AppData* data)
{
    // Recorre el mapa y muestra los libros
    Pair* pair = FirstTreeMap(data->books);
    while(pair != NULL)
    {
        Book* book = (Book*)(pair->value);

        printf("Titulo N°%i: \"%s\"\n", book->id, book->title);
        printf("Palabras: %i | Caracterers: %i\n\n", book->word_count, book->char_count);

        pair = NextTreeMap(data->books);
    }
}

void AppSearchBook(AppData* data)
{
    char* input = GetStrFromInput();

    List* words = SeparateStr(input);
    List* books = CreateList();

    // Guarda punteros a los libros a una lista
    // Esto es para poder descartar elementos
    Pair* pair = FirstTreeMap(data->books);
    while(pair != NULL)
    {
        Book* book = (Book*)(pair->value);
        PushFront(books, book);

        pair = NextTreeMap(data->books);
    }

    // Busca cada palabra en cada libro
    while (FirstList(words) != NULL)
    {
        char* str = PopFront(words);

        // Palabra "str" en todo libro
        Book* book = FirstList(books);
        while (book != NULL)
        {
            Pair* pair = SearchMap(book->title_words, str);

            if (pair != NULL)
            {
                book = NextList(books);
            }
            else
            {
                PopCurrent(books);
                book = CurrentList(books);
            }
        }
        
        Free(str);
    }

    // Mensaje
    if (FirstList(books) != NULL)
        printf("Libros encontrados:\n");
    else
        printf("No se encontraron coinsidencias\n");

    // Muestra los libros encontrados
    while (FirstList(books) != NULL)
    {
        Book* book = PopFront(books);
        printf("%s\n", book->title);
    }
    
    Free(books);
    Free(input);
}

void AppMoreFrecuentWords(AppData* data)
{
    char* str = GetStrFromInput();
    int id = atoi(str);

    Pair* pair = SearchTreeMap(data->books_by_id, &id);
    if (pair == NULL)
    {
        Error("No exite libro con ID %i", id);
        Free(str);
        return;
    }

    Book* book = (Book*)(pair->value);

    pair = FirstTreeMap(book->top_words);
    int i = 0;
    while(pair != NULL && i != 10)
    {
        printf("%s, %i\n", pair->value, *((int*)(pair->key)));

        pair = NextTreeMap(book->top_words);
        i++;
    }

    Free(str);
}

void AppSearchByWord(AppData* data)
{
    char* str = GetStrFromInput();
    strlwr(str);

    Heap* books = CreateHeap();

    // Pone cada libro que tenga la palabra en un
    // monticulo binario. esto para que los elementos salgan ordenados
    Pair* pair = FirstTreeMap(data->books);
    while(pair != NULL)
    {
        Book* book = (Book*)(pair->value);
        
        Pair* search = SearchMap(book->words, str);
        
        if(search != NULL)
        {
            int priority = *((int*)(pair->value));
            HeapPush(books, book, priority);
        }


        pair = NextTreeMap(data->books);
    }

    // Recorre el monticulo
    Book* book2 = HeapTop(books);
    while (book2 != NULL)
    {
        printf("%s\n", book2->title);

        HeapPop(books);
        book2 = HeapTop(books);
    }

    FreeHeap(books);
    Free(str);
}