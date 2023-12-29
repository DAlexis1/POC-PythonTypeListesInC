#include <stdio.h>
#include "testliste.h"


int main() {
    DefArray my_array = NewArray('c',10);
    IncreaseLength(&my_array,2);
    //AppendToArrayChar(&my_array,'a');
    //printf("%c",*(char*)my_array.values);
    FillArrayChar(&my_array,(char[]){'a', 'b'},2);
    InsertInArrayChar(&my_array,'c',2);
    printf("%c\n", GetCharFromArray(&my_array,1));
    char test = PopCharFromArray(&my_array,1);
    printf("%s\n",(char*)my_array.values);
    printf("%c",test);
    FreeTheArray(&my_array);
    return 0;
}
