#ifndef LISTES_TESTLISTE_H
#define LISTES_TESTLISTE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct defarray {
    char type;  //will take char (c), int (i) or bool (b)
    unsigned int phys_size;
    unsigned int real_size;
    void* values ;
}DefArray;

struct Test {

};


DefArray NewArray(char type,unsigned int length);
void IncreaseLength(DefArray* Array,int increase);

void AppendToArrayPrivate(DefArray*,void*);
void AppendToArrayInt(DefArray*,int);
void AppendToArrayChar(DefArray*,char);
void AppendToArrayFloat(DefArray*,float);

void FillArray(DefArray* Array, void **value,int);
void FillArrayChar(DefArray*,char[],int);
void FillArrayInt(DefArray*,int[],int);
void FillArrayFloat(DefArray*,float[],int);

void InsertInArray(DefArray*,void*, int);
void InsertInArrayChar(DefArray*,char, int);
void InsertInArrayInt(DefArray*,int, int);
void InsertInArrayFloat(DefArray*,float, int);


#endif //LISTES_TESTLISTE_H
