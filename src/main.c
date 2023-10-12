#include "hashmap.h"
#include "util.h"

#include <stdio.h>

int main()
{

    HashMap* map = CreateMap();

    int x = 45;
    const char* str = "LOL";
    InsertMap(map, str, &x);

    Pair* pair = NextMap(map);
    if (pair == NULL)
    {
        Error("AAAAAAAAAAAAAAAAAAAAAAAA");
    }

    printf("%i", *(int*)(pair->value));
    

    End();
    return 0;
}