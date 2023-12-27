#include "testliste.h"

// -------------------------------------------------------------------------------
//                            Defining Array

DefArray NewArray(char type,unsigned int length) {
    void *result;
    if (type=='c'){result = malloc(sizeof(char)*length);}
    else if (type=='i'){result = malloc(sizeof(int)*length);}
    else if (type=='f'){result = malloc(sizeof(float)*length);}
    else {
        printf("Bad flag");
        exit(1);
    }

    DefArray return_array = {type,length,0,result};
    return return_array;
}

// -------------------------------------------------------------------------------
//                             Increasing length of array

void IncreaseLength(DefArray* Array,int increase){
    void* Buffer;
    switch (Array->type) {
        case 'i' : Buffer = realloc(Array->values,Array->phys_size+increase*sizeof(int)); break;
        case 'c' : Buffer = realloc(Array->values,Array->phys_size+increase*sizeof(char)); break;
        case 'f' : Buffer = realloc(Array->values,Array->phys_size+increase*sizeof(float)); break;
    }
    Array->phys_size+=increase;
    if (Buffer==NULL){
        //Handle memory leak some way
    } else {
        Array->values = Buffer;
    }
}

// ------------------------------------------------------------------------------------------
//                                    Appending to Array functions


void AppendToArrayPrivate(DefArray* Array,void* value){
    if (Array->real_size+1>Array->phys_size){
        IncreaseLength(Array,1);
    }
    switch (Array->type) {
        case 'i' : ((int *)Array->values)[Array->real_size] = *(int*)value; break;
        case 'c' : ((char *)Array->values)[Array->real_size] = *(char*)value; break;
        case 'f' : ((float *)Array->values)[Array->real_size] = *(float*)value; break;
    }
    Array->real_size++;
}

void AppendToArrayInt(DefArray* Array,int value){
    AppendToArrayPrivate(Array,&value);
}
void AppendToArrayChar(DefArray* Array,char value){
    AppendToArrayPrivate(Array,&value);
}
void AppendToArrayFloat(DefArray* Array,float value){
    AppendToArrayPrivate(Array,&value);
}

// --------------------------------------------------------------------------------------
//                                  Filling Array functions

void FillArray(DefArray* Array, void **value,int len_value){
    switch(Array->type){
        case 'i' : {
            for (int i = 0; i<len_value; i++){
                AppendToArrayInt(Array,((int*)value)[i]);
            }
            break;
        }
        case 'c' : {
            for (int i = 0; i<len_value; i++){
                AppendToArrayChar(Array,((char*)value)[i]);
            }
            break;
        }
        case 'f' : {
            for (int i = 0; i<len_value; i++){
                AppendToArrayFloat(Array,((float*)value)[i]);
            }
            break;
        }
    }
}

void FillArrayChar(DefArray* Array,char* char_list, int len_value){
    FillArray(Array, (void **)char_list, len_value);
}
void FillArrayInt(DefArray* Array,int* int_list,int len_value){
    FillArray(Array, (void **) int_list, len_value);
}
void FillArrayFloat(DefArray* Array,float* float_list,int len_value){
    FillArray(Array, (void **) float_list, len_value);
}

// ------------------------------------------------------------------------------
//                          Insert an element

void InsertInArray(DefArray* Array,void* value, int index){
    if (Array->real_size+1>Array->phys_size){
        IncreaseLength(Array,1);
    }
    switch (Array->type) {
        case 'i': {
            int temp;
            int RealValue = *(int*)value;
            for (int i = index; i <= Array->real_size; i++) {
                temp = ((int*)Array->values)[i];
                ((int*)Array->values)[i]=RealValue;
                RealValue = temp;
            }
            break;
        }
        case 'c': {
            char temp;
            char RealValue = *(char*)value;
            for (int i = index; i <= Array->real_size; i++) {
                temp = ((char*)Array->values)[i];
                ((char*)Array->values)[i]=RealValue;
                RealValue = temp;
            }
            break;
        }
        case 'f': {
            float temp;
            float RealValue = *(float*)value;
            for (int i = index; i <= Array->real_size; i++) {
                temp = ((float*)Array->values)[i];
                ((float*)Array->values)[i]=RealValue;
                RealValue = temp;
            }
            break;
        }
    }
}

void InsertInArrayChar(DefArray* Array,char value, int index){
    InsertInArray(Array,&value,index);
}
void InsertInArrayInt(DefArray* Array,int value, int index){
    InsertInArray(Array,&value,index);
}
void InsertInArrayFloat(DefArray* Array,float value, int index){
    InsertInArray(Array,&value,index);
}


