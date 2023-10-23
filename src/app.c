#include "app.h"
#include "util.h"
#include "list.h"
#include "file.h"
#include "book.h"

#include <string.h>
#include <stdio.h>

// Crea información de la applicacion
AppData* CreateAppData()
{
    AppData* temp = Malloc(sizeof(AppData));
    temp->books = CreateTreeMap(lower_than_string);

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
    
}

// carga los documentos
void AppLoadDocuments(AppData* data)
{
    // consigue el input y lo divide en plabras
    char* str = GetStrFromInput();
    List* list = SeparateStr(str);

    // listas auxiliares
    List* files = CreateList();
    List* dirs = CreateList();

    // lee y valida los nombres de los archivo y carpetas
    while (FirstList(list) != NULL)
    {
        char* temp = PopFront(list);

        if (IsTxt(temp))
            PushFront(files, CreateFileFromPath(temp));

        else if (strchr(temp, '.') == NULL)
            PushFront(dirs, temp);
    }

    Free(list);

    // pasa todos los archivo encontrados de las carpetas
    // que sean .txt
    while (FirstList(dirs) != NULL)
    {
        char* temp = PopFront(dirs);
        List* dir_files = GetDirList(temp);

        while (FirstList(dir_files) != NULL)
        {
            File* temp2 = PopFront(dir_files);
            
            if(IsTxt(temp2->dir))
            {
                PushFront(files, temp2);
            }
            else
                FreeFile(temp2);
        }
        
    }

    Free(dirs);

    int i = 0;
    while (FirstList(files) != NULL)
    {
        File* file = PopFront(files);
        
        printf("Cargando \"%s\"...\n", file->dir);
        Book* book = CreateBook(file);
        Success("¡\"%s\" cargado!\n", book->title);

        InsertTreeMap(data->books, book->title, book);

        FreeFile(file);
    }

    Free(files);
    Free(str);
}

// Recorrer el mapa de los libros y muestra su informacion
void AppShowBooks(AppData* data)
{
    Pair* pair = FirstTreeMap(data->books);
    while(pair != NULL)
    {
        Book* book = (Book*)(pair->value);

        printf("Titulo N°%i: \"%s\"\n", book->id, book->title);
        printf("Palabras: %i | Caracterers: %i\n\n", book->word_cout, book->char_count);

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

        Book* book = FirstList(books);
        while (book != NULL)
        {

            Pair* pair = SearchMap(book->title_words, str);

            // descarta un libro
            if(pair == NULL)
                PopCurrent(books);


            book = NextList(books);
        }
        
        Free(str);
    }
    
    // Mensaje
    if (FirstList(books) != NULL)
        printf("Libros encontrados:\n");
    else
        printf("No se encontraron coinsidencias\n");

    // Muestra libros encontrados
    while (FirstList(books) != NULL)
    {
        Book* book = PopFront(books);
        printf("%s\n", book->title);
    }
    
    Free(input);
}