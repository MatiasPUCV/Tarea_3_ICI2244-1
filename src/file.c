#include "file.h"
#include "util.h"

#include <string.h>
#include <stdio.h>

File* FileCreate(char* dir, char* name, char* no_ext)
{
    File* file = Malloc(sizeof(File));
    file->dir    = dir;
    file->name   = name;
    file->no_ext = no_ext;
}

File* CreateFileFromPath(char* path)
{
    char* name = strrchr(path, '/');
    
    if (name != NULL)
        name++;
    else
        name = path;

    FileCreate(path, name, RemoveExtension(name));
}

#include <windows.h>

List* GetDirList(const char* directory)
{
    // Crea la str de la dirección
    char* path = Malloc(sizeof(char) * strlen(directory) + 3);
    strcpy(path, directory);
    strcat(path, "\\*");

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(path, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        Error("No se encontraron archivos en la carpeta \"%s\"", directory);
        return NULL;
    }

    List* list = CreateList();

    do
    {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        char* dir = Calloc(strlen(directory) + strlen(findFileData.cFileName) + 2, sizeof(char));
        strcat(dir, directory);
        strcat(dir, "/");
        strcat(dir, findFileData.cFileName);

        char* name = Calloc(strlen(findFileData.cFileName) + 1, sizeof(char));
        strcat(name, findFileData.cFileName);

        char* no_ext = RemoveExtension(name);

        File* file = FileCreate(dir, name, no_ext);

        PushBack(list, file);

    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    Free(path);

    return list;
}

void FreeFile(File* file)
{
    Free(file->dir);
    Free(file->name);
    Free(file->no_ext);

    Free(file);
}

