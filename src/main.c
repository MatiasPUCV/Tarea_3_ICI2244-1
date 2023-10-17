#include "hashmap.h"
#include "util.h"
#include "file.h"


#include <stdio.h>
#include <string.h>

void GetFile(const char* filename);

int main()
{
#if 0
    List* list = GetDirList("books");

    File* data;
    while (FirstList(list) != NULL)
    {
        data = PopFront(list);
        Error("%s", data->dir);
        FreeFile(data);
    }

    Free(list);
#endif

    GetFile("books/103.txt");
    
    End();
    return 0;
}

void GetFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        Error("No se pudo abrir el archivo");
        return;
    }

    char backlist[] = ".,:;(){}[]";
    char word[500];
    
    while (fscanf(file, "%s", word) == 1)
    {
        int len = strlen(word);
        int index = 0;

        char* word2 = Calloc(len + 1, sizeof(char*));

        for (int i = 0; i < len; i++)
        {
            if (strchr(backlist, word[i]) == NULL)
            {
                word2[index] = word[i];
                index++;
            }
        }
        word2[index + 1] = '\0';
        //printf("%s\n", strlwr(word2));


        Free(word2);

    }


    fclose(file);
}


