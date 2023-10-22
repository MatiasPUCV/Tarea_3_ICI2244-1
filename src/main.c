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
#if 1
    bool close = false;
    AppData* data = CreateAppData();

    while(!close)
    {
        AppTick(&close, data);
    }

    FreeAppData(data);
    End();

#else

    TreeMap* map = CreateTreeMap(lower_than_int);
    int k1 = 12;
    int v1 = 1;

    int k2 = 22;
    int v2 = 2;

    InsertTreeMap(map, &k2, &v2);
    InsertTreeMap(map, &k1, &v1);

    Pair* pair = FirstTreeMap(map);
    while (pair != NULL)
    {
        printf("%i %i\n", *(int*)(pair->key), *(int*)(pair->value));
        pair = NextTreeMap(map);
    }
    

#endif
    return 0;
}

void AppTick(bool* close, AppData* data)
{
    // Interfaz de usuario
    printf("-----------------------------------\n");
    printf(" 1) Cargar Documentos\n");
    printf(" 2) Mostrar Documentos\n");
    printf(" 3) Buscar libro\n");
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

    default:
        *close = true;
        break;
    }

}
