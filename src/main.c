#include "hashmap.h"
#include "util.h"
#include "file.h"

#include "treemap.h"
#include "book.h"

#include <stdio.h>
#include <string.h>

void ReadBooksFromDir(const char* path)
{
    for (int i = 0; i < 1; i++)
    {
        File* data;
        List* list = GetDirList(path);

        while (FirstList(list) != NULL)
        {
            data = PopFront(list);
            Error("%s", data->dir);

            Book* book = CreateBook(data);

            Success("FREE TIME");
            FreeBook(book);
            FreeFile(data);
        }

        Free(list);
    }
}

int main()
{

   ReadBooksFromDir("books");

    End();
    return 0;
}

void AppTick()
{
    
}