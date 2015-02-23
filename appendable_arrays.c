
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
Creating an array we can append to is not easy!
All blocks of memory have a fixed size, and we should not access anything
  outside these bounds. Doing so may crash the program (if we're lucky), or
  cause impossibly difficult-to-find bugs. This means we cannot trivially extend
  the memory an array uses!
To get enough space for additional elements, we must first ask for a new block
  of memory that has extra capacity (allocate), copy all the elements into the
  new block, then free (deallocate) the old block (so that it can be reused at a
  later point).
To know how large the current block is and how much of it is currently in use,
  we need variables for capacity and length.
*/
typedef struct Array Array;
struct Array {
    int*    data;
    int     capacity;
    int     length;
};


/*
To create a new array, we first allocate space for the "bookkeeping" variables
  (here: the "Array" struct), then we must allocate space for the data.
*/
Array* newArray(int capacity){
    Array* a    = malloc(sizeof(Array));

    a->data     = malloc(sizeof(int) * capacity);
    a->capacity = capacity;
    a->length   = 0;

    return a;
}

/*
When we wrap the unprotected memory block (here: Array.data) in our own struct,
  we lose some and we gain some:
We lose the ability to use the normal array-indexing syntaxs (eg "a[3] = 7;"),
  and instead must use a function call.
We gain the ability to do bounds-checking on the indexes at runtime (though at
  the cost of some performance).
*/
void set(Array* a, int idx, int value){
    assert(idx < a->length && "Range error: Attempted to access an element beyond the end of the array");
    assert(idx >= 0 && "Range error: Attepted to access an element beyond the start of the array");
    a->data[idx] = value;
}


int get(Array* a, int idx){
    assert(idx < a->length && "Range error: Attempted to access an element beyond the end of the array");
    assert(idx >= 0 && "Range error: Attepted to access an element beyond the start of the array");
    return a->data[idx];
}

/*
When we append to the array, there are two scenarios:
1) There is sufficient capacity in the current block of memory
    In this case, we just assign the value to the last position, then bump the length
2) There is insufficient space, ie the length is equal to the capacity
    In this case, we must copy the data into a new block before we can assign the value
        We allocate a new block of memory, with twice the capacity
        We copy the data into the new block
        We free the old block, so that it can be used later
        We modify the pointer to the data block to correctly point to the new block
*/
void append(Array* a, int value){
    if(a->length == a->capacity){

        int* newData = malloc(sizeof(int) * a->capacity * 2);
        memcpy(newData, a->data, sizeof(int) * a->length);
        free(a->data);
        a->data = newData;

        a->capacity *= 2;
    }

    a->data[a->length] = value;
    a->length++;
}
/*
How do we then prepend (add to the front) to arrays? The answer is that we don't.
In Python, using list.insert(0, v) is anywhere between 20 to 80 times slower
  than list.append(v), simply because of all the re-allocating and copying!
http://stackoverflow.com/questions/7776938/python-insert-vs-append
*/


/*
When removing elements from the back of the array, it is "enough" to just
  decrease the length by one.
But what if we allocate space for a million elements, then remove all but one of
  them? This will waste a lot of memory!
*/
void popBack(Array* a){
    a->length--;
    // TODO: shrink size.
}

/*
When removing elements from the front of the array, we could do something similar.
Instead of just having "length", the array has two indexes: the index of the
  first element, and the index of the last.
The length must now become a function that returns "backIdx - frontIdx".
We must also here remember to shrink the array, otherwise calling append and 
  popFront repeatedly will use more and more memory!
*/
void popFront(Array* a){
/*
    assert(a->frontIdx < a->backIdx && "Range error: Attepted to remove the front of an empty array");
    a->frontIdx++;
*/
}


void printArray(Array* a){
    printf("Array:{");
    if(a->length != 0){
        printf("%d", get(a, 0));
    }
    for(int i = 1; i < a->length; i++){
        printf(", %d", get(a, i));
    }
    printf("}\n");
}

void printArrayInfo(Array* a){
    printf(
        "ArrayInfo:{length = %d, capacity = %d, data = %p}\n",
        a->length, a->capacity, a->data
    );
}




int main(void){
    Array* a = newArray(2);
    printArray(a);  printArrayInfo(a);  printf("\n");

    append(a, 10);
    printArray(a);  printArrayInfo(a);  printf("\n");

    append(a, 20);
    printArray(a);  printArrayInfo(a);  printf("\n");

    append(a, 30);
    printArray(a);  printArrayInfo(a);  printf("\n");

    set(a, 1, 15);
    printArray(a);  printArrayInfo(a);  printf("\n");

    popBack(a);
    printArray(a);  printArrayInfo(a);  printf("\n");

    return 0;
}

