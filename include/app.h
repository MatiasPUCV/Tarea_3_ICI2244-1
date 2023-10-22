#ifndef APP_H
#define APP_H

#include "treemap.h"

typedef struct AppData
{
    TreeMap* books;

} AppData;

AppData* CreateAppData();
void FreeAppData(AppData* data);

void AppLoadDocuments(AppData* data);
void AppShowBooks(AppData* data);
void AppSearchBook(AppData* data);

#endif