#include "testliste.h"

// -------------------------------------------------------------------------------
//                            Defining Array

/**
 * @Description Create a new dynamic array of type DefArray by allocating in the heap an array of the type indicated at the start and of the length asked.
 * @warning Remind to use the function FreeTheArray at the end of your program on every array created
 * @param type The type of the array to create
 * @param length The length of the array to create. Put 1 if you only need to do basic things and any other things if for any reason you need to be able to insert value anywhere from the start
 * @return The Array just created
 */

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

/**
 * @Description Reallocate the memory of the array to increase the length.
 * @param Array A pointer to the array
 * @param increase Integer for how much we should increase the length of the array
 */

void IncreaseLength(DefArray* Array,int increase){
    void* Buffer;
    switch (Array->type) {
        case 'i' : Buffer = realloc(Array->values,Array->phys_size+increase*sizeof(int)); break;
        case 'c' : Buffer = realloc(Array->values,Array->phys_size+increase*sizeof(char)); break;
        case 'f' : Buffer = realloc(Array->values,Array->phys_size+increase*sizeof(float)); break;
    }
    Array->phys_size+=increase;
    if (Buffer==NULL){
        fprintf(stderr,"Not enough memory");
        free(Array->values);
        exit(0);
    } else {
        Array->values = Buffer;
    }
}

// ------------------------------------------------------------------------------------------
//                                    Appending to Array functions

/**
 * @brief Use the Derivative to append value as it won't require you to deal with any void pointer
 * @Description Add a value at the end of the list + a trailing 0x00 to ensure we don't get memory leak
 * @Derivative AppendToArrayInt,
 * @Derivative AppendToArrayChar,
 * @Derivative AppendToArrayFloat
 * @param Array A pointer to the array to which we need to append a value
 * @param value A void pointer to the value we want to append
 */
void AppendToArrayPrivate(DefArray* Array,void* value){
    for (int i=0;i<2;i++) {    // the loop is to ensure we can also put a trailing 0x00 character at the end of the array, for printing in the case of char for example and avoid leaking memory
        if (Array->virt_size + 1 > Array->phys_size) {
            IncreaseLength(Array, 1);
        }
    }

    switch (Array->type) {
        case 'i' : {
            ((int *)Array->values)[Array->virt_size] = *(int*)value;
            ((int *)Array->values)[Array->virt_size + 1] = 0x00;
            break;
        }
        case 'c' : {
            ((char *)Array->values)[Array->virt_size] = *(char*)value;
            ((char *)Array->values)[Array->virt_size + 1] = 0x00;
            break;
        }
        case 'f' : {
            ((float *)Array->values)[Array->virt_size] = *(float*)value;
            ((float *)Array->values)[Array->virt_size + 1] = 0x00;
            break;
        }
    }
    Array->virt_size++;
}

/**
 * @Description Append to an integer array using the AppendToArrayPrivate function
 * @param Array Pointer to the array to which we want to append a value
 * @param value The integer value to append
 */
void AppendToArrayInt(DefArray* Array,int value){
    AppendToArrayPrivate(Array,&value);
}

/**
 * @Description Append to a char array using the AppendToArrayPrivate function
 * @param Array Pointer to the array to which we want to append a value
 * @param value The char value to append
 */
void AppendToArrayChar(DefArray* Array,char value){
    AppendToArrayPrivate(Array,&value);
}

/**
 * @Description Append to a float array using the AppendToArrayPrivate function
 * @param Array Pointer to the array to which we want to append a value
 * @param value The float value to append
 */
void AppendToArrayFloat(DefArray* Array,float value){
    AppendToArrayPrivate(Array,&value);
}

// --------------------------------------------------------------------------------------
//                                  Filling Array functions

/**
 * @brief To avoid dealing with void pointer, use the Derivative to fill the array
 * @Description Add the content of a static array to the end of the dynamic array passed in parameter
 * @Derivative FillArrayChar,
 * @Derivative FillArrayInt,
 * @Derivative FillArrayFloat
 * @param Array Pointer to the array to which we want to add the content of the list
 * @param value The static array that will be appended to the end of the dynamic array
 * @param len_value The len of the static array.
 */
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

/**
 * @Description Fill a dynamic char array from a static char array
 * @param Array Pointer to the array to which we want to add the content of the list
 * @param value The static char array that will be appended to the end of the dynamic array
 * @param len_value The len of the static array.
 */
void FillArrayChar(DefArray* Array,char* char_list, int len_value){
    FillArray(Array, (void **)char_list, len_value);
}

/**
 * @Description Fill a dynamic integer array from a static integer array
 * @param Array Pointer to the array to which we want to add the content of the list
 * @param value The static integer array that will be appended to the end of the dynamic array
 * @param len_value The len of the static array.
 */
void FillArrayInt(DefArray* Array,int* int_list,int len_value){
    FillArray(Array, (void **) int_list, len_value);
}

/**
 * @Description Fill a dynamic float array from a static float array
 * @param Array Pointer to the array to which we want to add the content of the list
 * @param value The static float array that will be appended to the end of the dynamic array
 * @param len_value The len of the static array.
 */
void FillArrayFloat(DefArray* Array,float* float_list,int len_value){
    FillArray(Array, (void **) float_list, len_value);
}

// ------------------------------------------------------------------------------
//                          Insert an element

/**
 * @brief don't use these function unless you want to deal with void pointer
 * @Description Insert an element at a certain index and shift the next elements to the right (increase the physical size if needed)
 * @Derivative InsertInArrayChar,
 * @Derivative InsertInArrayInt,
 * @Derivative InsertInArrayFloat
 * @param Array A pointer to the array in which we want to insert a value
 * @param value A void pointer for the value to insert
 * @param index The place to insert the value
 */
void InsertInArray(DefArray* Array,void* value, int index){
    if (Array->virt_size + 1 > Array->phys_size){
        IncreaseLength(Array,1);
    }
    switch (Array->type) {
        case 'i': {
            int temp;
            int RealValue = *(int*)value;
            for (int i = index; i <= Array->virt_size; i++) {
                temp = ((int*)Array->values)[i];
                ((int*)Array->values)[i]=RealValue;
                RealValue = temp;
            }
            break;
        }
        case 'c': {
            char temp;
            char RealValue = *(char*)value;
            for (int i = index; i <= Array->virt_size; i++) {
                temp = ((char*)Array->values)[i];
                ((char*)Array->values)[i]=RealValue;
                RealValue = temp;
            }
            break;
        }
        case 'f': {
            float temp;
            float RealValue = *(float*)value;
            for (int i = index; i <= Array->virt_size; i++) {
                temp = ((float*)Array->values)[i];
                ((float*)Array->values)[i]=RealValue;
                RealValue = temp;
            }
            break;
        }
    }
}

/**
 * Insert a char in the Array using the InsertInArray function
 * @param Array a pointer to the array in which we want to insert an element
 * @param value the char we want to insert
 * @param index an integer for the index at which we want to insert the value
 */
void InsertInArrayChar(DefArray* Array,char value, int index){
    InsertInArray(Array,&value,index);
}

/**
 * Insert an integer in the Array using the InsertInArray function
 * @param Array a pointer to the array in which we want to insert an element
 * @param value the integer we want to insert
 * @param index an integer for the index at which we want to insert the value
 */
void InsertInArrayInt(DefArray* Array,int value, int index){
    InsertInArray(Array,&value,index);
}

/**
 * Insert a float in the Array using the InsertInArray function
 * @param Array a pointer to the array in which we want to insert an element
 * @param value the float we want to insert
 * @param index an integer for the index at which we want to insert the value
 */
void InsertInArrayFloat(DefArray* Array,float value, int index){
    InsertInArray(Array,&value,index);
}

//---------------------------------------------------------------------------------------
//                             Get an element from its Index

/**
 * @Description Getter for dynamic char array
 * @param Array A pointer to the array
 * @param index the index of the element we want to get
 * @return the element we want to get
 */
char GetCharFromArray(DefArray* Array, int index){
    return ((char*)Array->values)[index];
}

/**
 * @Description Getter for dynamic int array
 * @param Array A pointer to the array
 * @param index the index of the element we want to get
 * @return the element we want to get
 */
int GetIntFromArray(DefArray* Array, int index){
    return ((int*)Array->values)[index];
}

/**
 * @Description Getter for dynamic float array
 * @param Array A pointer to the array
 * @param index the index of the element we want to get
 * @return the element we want to get
 */
float GetFloatFromArray(DefArray* Array, int index){
    return ((float*)Array->values)[index];
}

//---------------------------------------------------------------------------------------
//                                  Remove an element
/**
 * @Description Remove the element of the array at the index asked and move everything one time left to rearrange it to delete the space
 * @param Array A pointer to the array from which we need to delete one element
 * @param index The index of the element to delete
 */
void RemoveFromArrayByIndex(DefArray* Array, int index){
    switch (Array->type) {
        case 'i':{
            for (int i = index; i < Array->virt_size; i++){
                ((int*)Array->values)[i]=((int*)Array->values)[i+1];
            }
            ((int*)Array->values)[Array->virt_size]=0x00;
            Array->virt_size--;
            break;
        }
        case 'c':{
            for (int i = index; i < Array->virt_size; i++){
                ((char*)Array->values)[i]=((char*)Array->values)[i+1];
            }
            ((char*)Array->values)[Array->virt_size]=0x00;
            Array->virt_size--;
            break;
        }
        case 'f':{
            for (int i = index; i < Array->virt_size; i++){
                ((float*)Array->values)[i]=((float*)Array->values)[i+1];
            }
            ((float*)Array->values)[Array->virt_size]=0x00;
            Array->virt_size--;
            break;
        }
    }
}

// --------------------------------------------------------------------------------------------
//                                 pop out an element from the array

/**
 * @Description Remove an element and return it using functions GetCharFromArray and RemoveFromArrayByIndex
 * @param Array A pointer to the array from which we'll pop an element
 * @param index The index of the element to be popped
 * @return the char previously popped.
 */
char PopCharFromArray(DefArray* Array,int index){
    char CharPopped = GetCharFromArray(Array,index);
    RemoveFromArrayByIndex(Array,index);
    return CharPopped;
}

/**
 * @Description Remove an element and return it using functions GetIntFromArray and RemoveFromArrayByIndex
 * @param Array A pointer to the array from which we'll pop an element
 * @param index The index of the element to be popped
 * @return the int previously popped.
 */
int PopIntFromArray(DefArray* Array,int index){
    int IntPopped = GetIntFromArray(Array,index);
    RemoveFromArrayByIndex(Array,index);
    return IntPopped;
}

/**
 * @Description Remove an element and return it using functions GetFloatFromArray and RemoveFromArrayByIndex
 * @param Array A pointer to the array from which we'll pop an element
 * @param index The index of the element to be popped
 * @return the float previously popped.
 */
float PopFloatFromArray(DefArray* Array,int index){
    float FloatPopped = GetFloatFromArray(Array,index);
    RemoveFromArrayByIndex(Array,index);
    return FloatPopped;
}

// --------------------------------------------------------------------------------------------
//                                  free the content of the array
/**
 * @Description Liberate the memory used for the array value
 * @param Array The Array we need to free memory from
 */
void FreeTheArray(DefArray* Array){
    free(Array->values);
}