//
// Created by benm on 9/4/18.
//

#ifndef EX2_BOOK_H
#define EX2_BOOK_H


#include "Unit.h"

class Book: public Unit
{
protected:
    int _publicationYear, _size;
    string _author;
};


#endif //EX2_BOOK_H
