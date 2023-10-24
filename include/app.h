#ifndef APP_H
#define APP_H

#include "treemap.h"

typedef struct AppData
{
    TreeMap* books;
    TreeMap* books_by_id;

} AppData;

AppData* CreateAppData();
void FreeAppData(AppData* data);

void AppLoadDocuments(AppData* data);
void AppShowBooks(AppData* data);
void AppSearchBook(AppData* data);
void AppMoreFrequentWords(AppData* data);

void AppSearchByWord(AppData* data);

#endif