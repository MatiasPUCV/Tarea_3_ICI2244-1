#include "app.h"
#include "util.h"
#include "list.h"
#include "file.h"
#include "book.h"

#include <string.h>


void AppLoadDocuments()
{
    char* str = GetStrFromInput();
    List* list = SeparateStr(str);

    List* files = CreateList();
    List* dirs = CreateList();

    while (FirstList(list) != NULL)
    {
        char* temp = PopFront(list);

        if (IsTxt(temp))
            PushBack(files, CreateFileFromPath(temp));

        else if (strchr(temp, '.') == NULL)
            PushBack(dirs, temp);
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
                PushBack(files, temp2);
            }
            else
                FreeFile(temp2);
        }
        
    }

    Free(dirs);

    while (FirstList(files) != NULL)
    {
        File* data = PopFront(files);
        Error("%s", data->dir);

        Book* book = CreateBook(data);

        Success("FREE TIME");
        FreeBook(book);
        FreeFile(data);
    }

    Free(files);

}