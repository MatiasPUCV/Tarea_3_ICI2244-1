#include "book.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* GetTitle(const char* path);
void GetFileWordData(const char* filename, int* wcount, int* ccount, HashMap* map);
char* RemoveFromWord(char* word);
void GetTitleWord(HashMap* map, char* title);

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
    GetTitleWord(temp->title_words, temp->title);

    return temp;
}

void FreeBook(Book* book)
{
    Free(book->title);

    FreeMap(book->words, true, false);
    //FreeMap(book->title_words, true, false);

    Free(book);
}

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

    fseek(file, 34, SEEK_SET);
    while ((c = fgetc(file)) != EOF && flag)
    {
        if (c == ',' || c == '\n')
            flag = false;
        else
            count++;
    }

    char* str = Malloc(sizeof(char*) * (count + 1));

    fseek(file, 34, SEEK_SET);
    for (int i = 0; i <= count; i++)
        str[i] = fgetc(file);

    str[count] = '\0';

    fclose(file);

    return str;
}

void GetFileWordData(const char* filename, int* wcount, int* ccount, HashMap* map)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        Error("No se pudo abrir el archivo");
        return;
    }
    
    char word[500];
    
    while (fscanf(file, "%s", word) == 1)
    {
        *ccount += strlen(word);
        char* word2 = RemoveFromWord(word);

        Pair* pair = SearchMap(map, word2);
        if (IsEmptyPair(pair))
        {
            InsertMap(map, word2, (void*)1);
        }
        else
        {
            pair->value += 1;
            Free(word2);
        }

        *wcount += 1;
    }

    fclose(file);
}

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

void GetTitleWord(HashMap* map, char* title)
{
    List* list = SeparateStr(title);

    while (FirstList(list) != NULL)
    {
        char* temp = PopFront(list);
        strlwr(temp);

        InsertMap(map, temp, (void*)true);

    }

}