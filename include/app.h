#ifndef APP_H
#define APP_H

#include "treemap.h"

typedef struct AppData
{
    TreeMap* books;

} AppData;

void AppLoadDocuments();

#endif