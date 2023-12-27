#include <stdio.h>
#include "testliste.h"


int main() {
    DefArray my_array = NewArray('c',10);
    IncreaseLength(&my_array,2);
    //AppendToArrayChar(&my_array,'a');
    //printf("%c",*(char*)my_array.values);
    FillArrayChar(&my_array,(char[]){'a', 'b'},2);
    InsertInArrayChar(&my_array,'c',1);
    printf("%s",(char*)my_array.values);
    free(my_array.values);

    return 0;

}
