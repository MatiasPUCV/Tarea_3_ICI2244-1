#include "hashmap.h"
#include "util.h"
#include "file.h"


#include <stdio.h>
#include <string.h>


int main()
{
    List* list = GetDirList("books");

    while (FirstList(list) != NULL)
    {
        File* data = PopFront(list);
        Error("%s", data->dir);
        FreeFile(data);
    }

    Free(list);
    
    
    End();
    return 0;
}