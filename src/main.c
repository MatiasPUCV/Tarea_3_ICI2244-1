#include "hashmap.h"
#include "util.h"
#include "file.h"

#include "treemap.h"
#include "book.h"
#include "app.h"

#include <stdio.h>
#include <string.h>

void ReadBooksFromDir(const char* path)
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

void AppTick(bool* close);

int main()
{
    bool close = false;
    while(!close)
    {
        AppTick(&close);
    }

    End();
    return 0;
}

void AppTick(bool* close)
{
    // Interfaz de usuario
    printf("-----------------------------------\n");
    printf(" 1) Cargar Documentos\n");
    printf(" 0) Cerrar Applicación\n");
    printf("-----------------------------------\n");
    
    int code = GetIntFromInput();
    Success("%i", code);

    switch (code)
    {
    case 1:
        Success("Cargar Documentos");
        AppLoadDocuments();
        break;

    default:
        *close = true;
        break;
    }

}
