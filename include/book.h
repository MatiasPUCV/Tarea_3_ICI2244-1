#ifndef BOOK_H
#define BOOK_H

#include "file.h"
#include "hashmap.h"

typedef struct Book
{
    int id;
    char* title;

    int word_count;
    int char_count;

    HashMap* words;

} Book;

Book* CreateBook(File* file);
void FreeBook(Book* book);

#endif // BOOK_H