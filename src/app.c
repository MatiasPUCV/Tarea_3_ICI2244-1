#include "app.h"
#include "util.h"
#include "list.h"
#include "file.h"
#include "book.h"

#include <string.h>
#include <stdio.h>

AppData* CreateAppData()
{
    AppData* temp = Malloc(sizeof(AppData));
    temp->books = CreateTreeMap(lower_than_string);

    return temp;
}

void FreeAppData(AppData* data)
{
    Pair* pair = FirstTreeMap(data->books);
    while(pair != NULL)
    {
        Book* book = (Book*)(pair->value);
        printf("%s\n", book->title);
        pair = NextTreeMap(data->books);
    }
    
}

void AppLoadDocuments(AppData* data)
{
    char* str = GetStrFromInput();
    List* list = SeparateStr(str);

    List* files = CreateList();
    List* dirs = CreateList();

    while (FirstList(list) != NULL)
    {
        char* temp = PopFront(list);

        if (IsTxt(temp))
            PushFront(files, CreateFileFromPath(temp));

        else if (strchr(temp, '.') == NULL)
            PushFront(dirs, temp);
    }

    Free(list);

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

}

void AppShowBooks(AppData* data)
{
    Pair* pair = FirstTreeMap(data->books);
    
    if (pair == NULL)
        return;

    while(pair != NULL)
    {
        Book* book = (Book*)(pair->value);
        printf("Titulo N°%i: \"%s\"\n", book->id, book->title);
        printf("Palabras: %i | Caracterers: %i\n\n", book->word_cout, book->char_count);
        pair = NextTreeMap(data->books);
    }
}