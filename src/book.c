#include "book.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* GetTitle(const char* path);
char* RemoveFromWord(char* word);

void GetTitleWords(HashMap* map, char* title);
void GetFileWordData(const char* filename, int* wcount, int* ccount, HashMap* map);

// Crea un libro
Book* CreateBook(File* file)
{
    Book* temp = Malloc(sizeof(Book));

    temp->id = atoi(file->no_ext);
    temp->title = GetTitle(file->dir);
    
    temp->word_cout = 0;
    temp->char_count = 0;

    temp->words = CreateMap();
    temp->title_words = CreateMap();


    GetFileWordData(file->dir, &temp->word_cout, &temp->char_count, temp->words);
    GetTitleWords(temp->title_words, temp->title);

    return temp;
}

// Libera memoria de un libro
void FreeBook(Book* book)
{
    Free(book->title);
    FreeMap(book->words, true, true);
    
    Free(book);
}

// Consigue el titulo del libro
char* GetTitle(const char* path)
{
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        Error("No se pudo abrir el archivo");
        return NULL;
    }
    
    char c;
    bool flag = true;
    int count = 0;

    // Va a donde empieza el titulo y se detiene
    // hasta encotrar un , esto es para obtener
    // el tamaño de titulo
    fseek(file, 34, SEEK_SET);
    while ((c = fgetc(file)) != EOF && flag)
    {
        if (c == ',' || c == '\n')
            flag = false;
        else
            count++;
    }

    char* str = Malloc(sizeof(char*) * (count + 1));

    // pasa el titulo a "str"
    fseek(file, 34, SEEK_SET);

    for (int i = 0; i <= count; i++)
        str[i] = fgetc(file);

    str[count] = '\0';

    fclose(file);

    return str;
}

// Conigue las palabras, su cantidad y el numero de caracteres
void GetFileWordData(const char* filename, int* wcount, int* ccount, HashMap* map)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        Error("No se pudo abrir el archivo");
        return;
    }
    
    char word[100];
    
    // lee el archivo palabra a palabra
    while (fscanf(file, "%s", word) == 1)
    {
        // Cuenta de caracteres
        *ccount += strlen(word);

        char* word2 = RemoveFromWord(word);

        // inserta la palabra en el mapa y en el caso de ya existir
        // añade 1 a su contador
        Pair* pair = SearchMap(map, word2);
        if (IsEmptyPair(pair))
        {
            int* count = Malloc(sizeof(int));
            *count = 1;

            InsertMap(map, word2, count);
        }
        else
        {
            *((int*)(pair->value)) += 1;
            Free(word2);
        }

        // Cuenta de palabras
        *wcount += 1;
    }

    fclose(file);
}

// remueve los caracteres que estan "blacklist" de "word"
char* RemoveFromWord(char* word)
{
    char blacklist[] = ".,:;(){}[]¿?¡!";

    int len = strlen(word);
    int index = 0;

    char* word2 = Calloc(len + 1, sizeof(char*));
    for (int i = 0; i < len; i++)
    {
        if (strchr(blacklist, word[i]) == NULL)
        {
            word2[index] = word[i];
            index++;
        }
    }

    word2[index + 1] = '\0';
    strlwr(word2);

    return word2;
}

// Fragmenta el titulo del libro y lo guarda en un HashMap
void GetTitleWords(HashMap* map, char* title)
{
    List* list = SeparateStr(title);

    while (FirstList(list) != NULL)
    {
        char* temp = PopFront(list);
        strlwr(temp);

        InsertMap(map, temp, (void*)true);
    }

    Free(list);
}