#ifndef BOOK_H
#define BOOK_H

#include "file.h"
#include "hashmap.h"
#include "treemap.h"

typedef struct Book
{
    int id;
    char* title;

    int word_count;
    int char_count;

    HashMap* words;
    HashMap* title_words;

    TreeMap* top_words;

} Book;

Book* CreateBook(File* file);
void FreeBook(Book* book);

#endif // BOOK_H