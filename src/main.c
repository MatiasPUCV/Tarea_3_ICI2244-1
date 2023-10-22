#include "hashmap.h"
#include "util.h"
#include "file.h"

#include "treemap.h"
#include "book.h"

#include <stdio.h>
#include <string.h>

int main()
{
    File* data;
    List* list = GetDirList("books");

    while (FirstList(list) != NULL)
    {
        data = PopFront(list);
        Error("%s", data->dir);
        
        Book* book = CreateBook(data);

        FreeFile(data);
        FreeBook(book);
    }

    Free(list);
    End();
    return 0;
}

