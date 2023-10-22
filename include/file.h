#ifndef FILE_H
#define FILE_H

#include "list.h"

typedef struct File
{
    char* dir;
    char* name;
    char* no_ext;
} File;

List* GetDirList(const char* directory);
void FreeFile(File* file);





#endif // FILE_H