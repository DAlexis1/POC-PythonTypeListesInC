#ifndef LISTES_TESTLISTE_H
#define LISTES_TESTLISTE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @struct DefArray type for dynamic array
 * @field .type :
 * Member type contains a char either 'c', 'i' or 'f' for char, int or float the only type currently implemented
 * @field .phys_size :
 * Member phys_size contains an uint for the physical size of the array which is the size actually allocated
 * @field .virt_size :
 * Member virt_size contains an uint for the virtual size of the array which is the size used
 * @field .values :
 * Member values contains a void pointer for the content of the array
 */
typedef struct defarray {
    char type;
    unsigned int phys_size;
    unsigned int virt_size;
    void* values;
}DefArray;


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

char GetCharFromArray(DefArray* Array, int index);
int GetIntFromArray(DefArray* Array, int index);
float GetFloatFromArray(DefArray* Array, int index);

void RemoveFromArrayByIndex(DefArray* Array, int index);

char PopCharFromArray(DefArray* Array,int index);
int PopIntFromArray(DefArray* Array,int index);
float PopFloatFromArray(DefArray* Array,int index);

void FreeTheArray(DefArray* Array);

#endif //LISTES_TESTLISTE_H
