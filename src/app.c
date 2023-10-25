#include "app.h"
#include "util.h"
#include "list.h"
#include "file.h"
#include "book.h"
#include "heap.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Crea información de la applicacion
AppData* CreateAppData()
{
    AppData* temp = Malloc(sizeof(AppData));

    temp->books       = CreateTreeMap(lower_than_string);
    temp->books_by_id = CreateTreeMap(lower_than_int);
    temp->docs_count  = 0;

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
        
        data->docs_count++;

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

    while (FirstList(words) != NULL)
    {
        char* word = PopFront(words);

        Book* book = FirstList(books);
        while (book != NULL)
        {
            if (strstr(book->title, word) != NULL)
            {
                book = NextList(books);
            }
            else
            {
                PopCurrent(books);
                book = CurrentList(books);
            }
        }
        
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

void AppMoreFrequentWords(AppData* data)
{
    char* str = GetStrFromInput();
    int id = atoi(str);

    Pair* pair = SearchTreeMap(data->books_by_id, &id);
    if (pair == NULL)
    {
        Error("No existe libro con ID %i", id);
        Free(str);
        return;
    }

    Book* book = (Book*)(pair->value);

    Heap* words = CreateHeap();

    pair = FirstMap(book->words);
    Pair* temp = pair;

    do
    {
        int priority = *((int*)(pair->value));
        HeapPush(words, pair, priority);

        pair = NextMap(book->words);
    }
    while (pair != NULL && pair != temp);
    
    // Recorre el monticulo 10 veces
    int i = 0;
    Pair* word = HeapTop(words);
    while (word != NULL && i != 10)
    {
        int value = *((int*)word->value);

        // Calcula la frecuencia
        double frequency =  (double)value / (double)book->word_count;

        printf("%s | Frecuencia:  %lf\n", word->key, frequency);

        HeapPop(words);
        word = HeapTop(words);
        i++;
    }

    // Libera memoria
    while (HeapTop(words) != NULL)
        HeapPop(words);
    
    FreeHeap(words);
    Free(str);
}

void AppMoreRelevantWord(AppData* data)
{
    char* str = GetStrFromInput();

    // Busca el libro, si no lo encuentra salta un error
    Pair* pair = SearchTreeMap(data->books, str);
    if (IsEmptyPair(pair))
    {
        Error("El libro \"%s\" no existe", str);
        return;
    }

    Book* book = (Book*)(pair->value);
    Heap* words = CreateHeap();

    // Recorre el mapa de palabras
    pair = FirstMap(book->words);
    Pair* temp = pair;
    do
    {
        char* word = ((char*)(pair->key));
        int word_in_docs = 0;

        // Busca cada palabra en cada libro
        Pair* pair2 = FirstTreeMap(data->books);
        while(pair2 != NULL)
        {
            Book* book2 = (Book*)(pair2->value);

            if (SearchMap(book2->words, word) != NULL)
                word_in_docs++; // Aumenta la cuenta

            pair2 = NextTreeMap(data->books);
        }

        // value es el numero de veces que aparece en un libro
        int value = *((int*)(pair->value));

        // Calcula la relevacia. Se guarda en el Heap para poder llevarlo junto
        // con la palabra en un par, dentro del monticulo
        double* revelancy = Malloc(sizeof(double));
        *revelancy = (((double)value / (double)book->word_count) * log10((double)data->docs_count / (double)word_in_docs));

        // Saca la prioridad, que es meramente es la relevacia convertida en int
        unsigned int priority = (unsigned int)((double)(*revelancy * 100000000));

        Pair* heap_data = CreatePair(word, revelancy);
        HeapPush(words, heap_data, priority);


        pair = NextMap(book->words);
    }
    while (pair != NULL && pair != temp);

    // Recorre el monticulo 10 veces
    int i = 0;
    Pair* haep_pair = HeapTop(words);
    while (haep_pair != NULL && i != 10)
    {
        double* revelancy = ((double*)haep_pair->value);

        printf("%s | Relevancia:  %lf\n", haep_pair->key, *revelancy);

        Free(revelancy);

        HeapPop(words);
        haep_pair = HeapTop(words);
        i++;
    }

    // Libera memoria
    while (HeapTop(words) != NULL)
    {
        Pair* temp = HeapTop(words);

        Free(temp->value);
        Free(temp);

        HeapPop(words);
    }

    FreeHeap(words);
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