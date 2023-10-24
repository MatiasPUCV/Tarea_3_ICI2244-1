#include "hashmap.h"
#include "util.h"
#include "file.h"

#include "treemap.h"
#include "book.h"
#include "app.h"

#include <stdio.h>
#include <string.h>

void AppTick(bool* close, AppData* data);

int main()
{
    bool close = false;
    AppData* data = CreateAppData();

    // Bucle prinipal
    while(!close)
        AppTick(&close, data);

    FreeAppData(data);
    End();
    
    return 0;
}

// lo que se ejecuta en cada itereacion del bucle principal
void AppTick(bool* close, AppData* data)
{
    // Interfaz de usuario
    printf("-----------------------------------\n");
    printf(" 1) Cargar Documentos\n");
    printf(" 2) Mostrar Documentos\n");
    printf(" 3) Buscar libro\n");
    printf(" 6) Buscar por palabra\n");
    printf(" 0) Cerrar Applicación\n");
    printf("-----------------------------------\n");
    
    int code = GetIntFromInput();
    printf("\n");

    switch (code)
    {
    case 1:
        Success("Cargar Documentos");
        AppLoadDocuments(data);
        break;
    
    case 2:
        Success("Mostrar Documentos");
        AppShowBooks(data);
        break;

    case 3:
        Success("Buscar libro");
        AppSearchBook(data);
        break;

    case 6:
        Success("Buscar por palabra");
        SearchByWord(data);
        break;

    default:
        *close = true;
        break;
    }

}
