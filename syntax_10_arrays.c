#include <stdio.h>
#include <stdlib.h>


void printArray(int arr[], int sz);
int sum(int* arr, int sz);
int compareInt(const void* first, const void* second);


int main(){

    // In C, "declaration reflects use"
    //  Since arrays are used like this: value = arrayName[index];
    //  Then arrays are declared like this: type arrayName[size];

    // Arrays need to have a size known at compile-time
    int arr1[3];
    
    // The compiler can also deduce the array size from the initializer list:
    int arr2[] = {1, 5, 3, 0, 7, 3};
    
    // But we cannot access the size of the array when we pass it to a 
    //   function that takes arrays of any size (passing arrays to functions
    //   implicitly passes a pointer to the first element)
    // So we need to also pass the size of the array wherever we use it
    // If the size is wrong, Bad Things can happen
    //  Try giving printArray a size that is too large!
    //    Also, compile with -fsanitize=address
    printArray(arr2, 3);
    
    // If the size of the array is known at compile-time, we can get the size 
    //   of the array (in bytes) using sizeof(), as long as we are in the same 
    //   scope the array was declared in. sizeof() only works at compile-time.
    // sizeof(arr2) gives the total memory usage of the array
    // sizeof(arr2[0]) gives the memory usage of a single element
    printArray(arr2, sizeof(arr2)/sizeof(arr2[0]));
    
    // To make this easier, we define this function-like macro:
    //  (Macros perform text-substitution before the source is compiled)
    #define len(arr) (sizeof(arr)/sizeof(arr[0]))
    
    // If we do not assign any content to the array, it is filled with junk:
    printArray(arr1, len(arr1));
    
    
    
    printf("Sum: %d\n", sum(arr2, len(arr2)));
    
    qsort(arr2, len(arr2), sizeof(arr2[0]), &compareInt);
    
    printArray(arr2, len(arr2));
}



void printArray(int arr[], int sz){
    printf("{%d", arr[0]);
    for(int i = 1; i < sz; i++){
        printf(", %d", arr[i]);
    }
    printf("}\n");
}


int sum(int* arr, int sz){
    int sum = 0;
    int* element = arr;
    for(int i = 0; i < sz; i++){
        sum += *element;
        element++;      // move the pointer to the next element in the array
        
        // Alternative 1:
        //  sum += *arr++;
        
        // Alternative 2:
        //  sum += *(arr + i);
    }
    return sum;
}



int compareInt(const void* first, const void* second){
    // The compare function needs to be completely generic, which means it 
    //  uses pointers to "untyped" data (void*)
    // The function also needs to promise to not change the pointer itself
    //  (The address/memory location of the data), hence the usage of const
    
    // To convert back to int, we must
    //  1) Convert the pointer-to-untyped-data into a pointer-to-int, then
    //  2) Get the data by dereferencing the pointer
    int a = *(int*)first;
    int b = *(int*)second;
    
    if(a > b){
        return 1;
    } else if(a < b){
        return -1;
    } else {
        return 0;
    }
    
    // (Alternative using the Ternary operator / "inline if" / "if-expression")
    // return (a < b)  ?  -1  :  (a > b);
}















