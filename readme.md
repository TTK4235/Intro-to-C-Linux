
Preface
=======

This text is intended to be a resource to prepare you for working on the elevator project. It covers a lot of ground, and is not intended to be completed in only four hours. The entire exercise is voluntary, so feel free to skip ahead, or come back to this text after you have started with the actual project work.

###Contents:

- [Intro to C and Linux](#intro-to-c-and-linux)
  - [Part 1: Your terminal and you](#part-1-your-terminal-and-you)
    - [Opening a terminal window](#opening-a-terminal-window)
  - [Part 2: Ready, set, C](#part-2-ready-set-c)
    - [Compilers for C](#compilers-for-c)
    - [Running programs](#running-programs)
    - [Stopping programs](#stopping-programs)
  - [Part 3: C syntax and some simple programs](#part-3-c-syntax-and-some-simple-programs)
    - [0: Hello world](#0-hello-world)
    - [1: The `main` function](#1-the-main-function)
    - [2: Primitive (built-in) types](#2-primitive-built-in-types)
    - [3: `printf`](#3-printf)
    - [4: Operators](#4-operators)
    - [5: Functions](#5-functions)
    - [6: Loops](#6-loops)
    - [7: If, modulo and `printf` formatting](#7-if-modulo-and-printf-formatting)
    - [8: User-defined types](#8-user-defined-types)
      - [Structs](#structs)
        - [Typedef](#typedef)
      - [Enumerations](#enumerations)
        - [The `switch` statement](#the-switch-statement)
      - [A card trick](#a-card-trick)
    - [9: Pointer basics](#9-pointer-basics)
      - [Alternative dereference syntax for structs](#alternative-dereference-syntax-for-structs)
    - [10: Fixed-size arrays and basic pointer arithmetic](#10-fixed-size-arrays-and-basic-pointer-arithmetic)
      - [Memory layout of arrays](#memory-layout-of-arrays)
      - [A note about strings](#a-note-about-strings)
- [Modules and Makefiles](#modules-and-makefiles)
    - [A timer module](#a-timer-module)
      - [Header (.h) files and implementation (.c) files](#header-h-files-and-implementation-c-files)
    - [Makefiles](#makefiles)
- [Goodbye World (Advanced/For fun)](#goodbye-world-advancedfor-fun)
    - [1: The standard "hello world" program](#1-the-standard-hello-world-program)
    - [2: Without #include](#2-without-#include)
    - [3: With no return value](#3-with-no-return-value)
    - [4: The smallest C program?](#4-the-smallest-c-program)
    - [5: Definitely the smallest C program.](#5-definitely-the-smallest-c-program)
- [Appendix](#appendix)
    - [Macros](#macros)
    - [The `null` pointer](#the-null-pointer)
    - [Pointer casting](#pointer-casting)
    - [Function pointers](#function-pointers)
    - [Higher-order functions](#higher-order-functions)
      - [Example: `qsort`](#example-qsort)
    - [Floating-point is hard](#floating-point-is-hard)
    - [`clang-format`](#clang-format)

Intro to C and Linux
====================

Part 1: Your terminal and you
-----------------------------

### Opening a terminal window

There are several ways to open a new terminal window:
 - From the menu in the top-left corner (start typing "terminal")
 - The terminal icon on the left sidebar
 - By pressing `Ctrl + Alt + T`

From the terminal we can much more than with the graphical interface, but we will start with some basic and familiar functions. First, we should make a new folder that we will use as our "workbench" of sorts.

 - [ ] To make this folder on the desktop, we must first change directory in the terminal. Do this by typing `cd Desktop` ("cd" means "change directory"). Use the Tab key to autocomplete the directory name.
 - [ ] Make a new directory using `mkdir directoryName`. Give this some appropriate name.

We can create new files using `touch fileName`, and edit them using - for example - `nano` or `vi`. There are of course other non-terminal text editors, and these may be more (or less) comfortable to work with. Create a file.

 - [ ] We can list the files in the current directory by using `ls` ("ls" means "list").
   - If you call `ls -a`, you will see two extra entries: `.` and `..`. These are the "names" of the current directory and the parent directory, respectively. You can `cd` a level "up" by calling `cd ..`.
 - [ ] We can move a file using `mv moveThisFile toHere`. Move the file you created one level up, by calling `mv fileYouCreated ../fileName`, or the shorter version `mv fileYouCreated ../` if you want to keep the same fileName.
   - Call `ls ..` to check that the file is moved.
 - Similarly to `mv`, we also have `cp` for copying.
 - [ ] We can remove files using `rm`. Remove the file you created, moved (and any copies you created if you also copied it).

`mv`, `cp` and `rm` all have their own set of options. You can see what these are by calling eg `rm --help`. For `cp` and `rm`, we see that we need to use the option `-r` or `--recursive` to copy or remove folders.

If we want to select multiple files that match a certain pattern, we can use the wildcard `*`. For example, if we want to remove all files that end in `.txt`, we can call rm `*.txt`.
    
    
In the terminal, Ctrl-C and Ctrl-V do not perform copy/paste, and you can find a brief history as to why [here](http://superuser.com/a/421468). Instead, use `Ctrl + Shift + [C/V/X]`



Part 2: Ready, set, C
---------------------

Before we create our first program in C, we must first look into exactly how we create it, how we run it, and finally - if it doesn't do this on its own - how we make it stop.

###Compilers for C

To create an executable program from C-code, we must compile it. There are several C-compilers out there, and by far the most common is the Gnu Compiler Collection, [gcc](https://gcc.gnu.org/). [Clang](http://clang.llvm.org/) is a newer compiler, which means it has learned several lessons from gcc. One of the most noticeable improvements are the significantly superior warnings and error messages.

Compilers are complicated beasts, and have a [huge number of options](https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html). Here's a summary of the ones we will need:
 - `-o executableName`: By default, the name of the executable is `a.out`. `-o` gives it a different name.
 - `-E`: This outputs the source code after preprocessing, and does not perform compilation or linking.
 - `-c`: The compiler produces an object-file (.o) for each c-file, instead of a single executable.
   - This is used to prevent compiling all of the code over and over, when only a few files have been changed.
   - To create an executable from object files, use gcc or clang again, or call the linker directly using `ld`.
 - `-Wall`: There are lots of `-Wxx` options for controlling warnings. `-Wall` enables all of them.
   - In general, do not ignore compiler warnings because they're "just warnings"!
 - `-g`: Produces debugging information that will be useful if (also known as "when") your programs crash.
 - `-fsanitize=address`: This option will crash your program the moment Something Bad happens with the memory the program is using, and print out a large amount of information about exactly what went wrong and - when used in combination with `-g` - where it happened.

We invoke the compiler using `compiler -options filename.c`, eg `gcc -Wall hello_world.c`.
 
 
###Running programs

To tell the terminal that we want to run a program, we must prefix the name of the executable with `./`, eg `./totallyRadProgram`. You can find an explanation of why [here](http://askubuntu.com/a/320657).

###Stopping programs

As you may recall if you read the explanation for why copy/paste is done with Ctrl-Shift-C/V, Ctrl-C is used to cancel the current program.



    
Part 3: C syntax and some simple programs
-----------------------------------------

Now that we know how the basics of using the terminal and invoking compilers, we can finally get started with some code.

This is not a test, and it is not a competition. The goal is to learn the basics of the C language and toolchain so that you can start making useful programs on your own. If you are stuck, you should ask for help. Remember that your fellow students and the internet are also valuable resources!

###0: Hello world
 - [ ] Copy or type the standard "[hello world](/hello_world.c)" program. Compile it and run it, and verify that it works as expected.

###1: The `main` function

A function is declared as follows:
```C
return_type function_name(argument_type argument_name){
    // function body
}
```
Note that C use braces (`{``}`) to signify the start and end of a scope, unlike - say - Python, which uses colon (`:`) and significant whitespace (indentation). The indentation in C does not matter, but it definitely helps in keeping code more readable.

 - The `main` function is where execution starts.
   - `main` must return an `int` (integer). Returning `0` is commonly used to signify that the program has run successfully.
   - `main` can take either no arguments (here signified by `void`), or two arguments: `int main(int argc, char** argv)`. The latter two-argument version is used when the program should take arguments from the command line.
 - `printf` is used to "print formatted" to the standard output (here the terminal). We will come back to the "formatted" part of printing later.
   - The `\n` at the end of the string is used to print a newline. Try removing it to see what happens.
   - `printf` is a function, so we need to give the compiler some information about what this function looks like. We find this information in `stdio.h`, which is why we use `#include <stdio.h>`.

   
###2: Primitive (built-in) types

C is a statically typed language, which means that all variables must be assigned a type, and this type cannot change. The built-in types are:
 - `int`: Standard signed integer, usually 32 bit.
   - `short`, `long`: short (usually 16 bit) and long (usually 64 bit) integers
 - `char`: A single character (used for strings), 8 bit
 - `float` and `double`: 32 bit and 64 bit floating-point numbers
 - `void`: "Untyped", usually used in conjunction with pointers (memory locations) and typecasting (telling the compiler to reinterpret one type as another)
 
Notice the lack of booleans and strings.
 - `int` is usually used as a substitute for booleans.
 - `char *` ("pointer to char" (think "memory location of char")) is used for strings. We will come back to how this works later.

    
###3: `printf`

`printf` takes one or more arguments, and the first argument is always a string (or rather, a `char *`). In this string we can embed several *conversion specifiers* that will be replaced by the additional arguments. A conversion specifier starts with the character `%`:
```C
printf("An integer: %d, a string: %s\n", 5, "hello!");
```

You can find full documentation of printf by typing `man fprintf` in the terminal. However, going [here](http://www.cplusplus.com/reference/cstdio/printf/) provides a more concise overview with better examples.

 - [ ] Declare and initialize variables for each of the types `int`, `char`, `float` and `char *`, then print them.
   - You can either declare and initialize in two statements (`type variable_name; variable_name = ...;`), or in a single statement (`type variable_name = ...;`)
 - [ ] Try removing the initialization (where you assign a value to the variable), and print the values now.

###4: Operators

C uses these symbols for binary (two-argument) arithmetic operators:
 - `*` (multiply), `/` (divide), `%` (modulo)
 - `+` (add), `-` (subtract)

Since C does not have booleans, a value of `0` means false, and any other value means true.
C uses these symbols for logical operators:
 - `&&` (and), `||` (or), `!` (not)
 - `<` (less than), `>` (greater than)
 
 - [ ] Find the rules for operator precedence for the above operators
 
C also has the unary (one-argument) increment and decrement operators:
 - `value++` and `++value` increase `value` by `1`
 - Similarly for `value--` and `--value`
 
 - [ ] Try the post- and pre-increment operators to see how they behave differently (eg `printf("%d\n", x++);`)
 
The binary arithmetic operators can also be combined with assignment (`=`). This way, we can re-write `value = value + 2` as `value += 2`, to avoid duplication of the variable name.
 - `+=  -=  *=  /=  %=`
 
There are also bitwise operators (`~  &  |  ^  <<  >>`) for working with single bits. We will not be needing them for now.

    
###5: Functions

- [ ] Create a function that takes an integer and returns its square.
  - The function must be declared "before" it is used, in other words above the point where it is called.
  - In case you were wondering: C does not allow you to declare a function inside another function.
  
Functions cannot be forward referenced. To call a function not yet encountered in the source file, it is necessary to insert a function declaration preceding the call. A function declaration looks similar to a function definition, but without the function body, eg: `return_type function_name(arg1_type, arg2_type);`. Giving names to the arguments is optional in a function definition.

```C
// Incorrect (compile with `-Wall`):
int main(void){
    foo(17);
}
void foo(int i){
    // ...
}

// Correct: 
void foo(int i); // Giving the parameter a name (here `i`) is optional
int main(void){
    foo(17);
}
void foo(int i){
    // ...
}
```
    
 - [ ] Move the square-function below the main function
   - Verify that you get a warning about an "implicit declaration"
   - Create a function declaration above the main function
   

###6: Loops

C has several loop statements:
 - `for(initialize; test; increment){}`: Runs `initialize`, then runs `test` *before* and `increment` *after* the loop body.
   - eg `for(int i = 0; i < 10; i++){}` will give `i` the values 0 to 9
     - (This is equivalent to `for i in range(0, 10):` in Python)
 - `while(condition){}`: Runs the loop body while `condition` is true.
   - Equivalent to `for(; condition; ){}`
   - `while(1){}` will run forever.
 - `do {} while(condition)`: Similar to `while`, but checks the condition *after* it has run through the loop.

 - [ ] Use a loop to create a function that returns the n-th Fibonacci number.
   - The function should take `int n` as its only parameter, and return an `int`.
   - Do not spend time reinventing the wheel. Search [Rosetta Code](http://rosettacode.org) for inspiration.
    
###7: If, modulo and `printf` formatting

An if-statement in C looks like this:
```C
if(condition){
    //...
} else if(other condition){
    //...
} else {
    //...
}
```
`else if` and `else` are optional. Any number of `else if`s can be added.

 - [ ] Create a function that prints the [Hailstone sequence](http://en.wikipedia.org/wiki/Collatz_conjecture) for positive numbers. The numbers should be printed on a single line, in columns 4 wide, left justify.
   - Example output for `3`: <pre><code>3   10  5   16  8   4   2   </code></pre>
     - Use `printf` format specifiers to achieve this.
   - Use modulo (`%`) to check if a value is even or odd.

###8: User-defined types

####Structs

We can create composite types (a type composed of primitive types (and other composite types)) by using the `struct` keyword:
```C
struct Type {
    int     firstMember;
    float   secondMember;
};
```

To create an instance of `Type`, we write:
```C
struct Type someInstanceOfType;
// And to assign values to struct members:
someInstanceOfType.firstMember = 5;
```

We can also assign the members all at once:
```C
struct Type instanceOne = {5, 3.4};
// Assigning with a "designated initializer":
struct Type instanceTwo = {.secondMember = 7.2, .firstMember = 6};
```

Note that we need to write `struct Type`, and not just `Type`! To avoid this, we can use `typedef` keyword:

#####Typedef
The only thing `typedef` does is give a new name to a type. This is also useful for giving the compiler some additional help, so that you don't accidentally write `birthday = currentSpeed + numGiraffes`. See [typedef](http://en.wikipedia.org/wiki/Typedef) on Wikipedia.

With typedef, we can shorten declarations of complex types:
```C
typedef  struct Foo  Bar;
// These are now equivalent:
struct Foo  instance;
Bar         instance;

// makes `struct tag_type` and `Type` equivalent
typedef struct tag_type  Type;
struct tag_type {
    int     firstMember;
    float   secondMember;
};

// This typedef's an anonymous (un-named) struct as `Type`
typedef struct {
    int     firstMember;
    float   secondMember;
} Type;


// And an instance is declared as:
Type instance;
```

####Enumerations
An enumeration is a set of named values, but it is not a new type. The named values are integers, and their values start at 0 (unless something else is assigned), and each new value is 1 larger than the previous:
```C
enum Weekday {
    monday, tuesday, wednesday = 11, thursday, friday
}
// monday will have the value 0, friday has the value 13
```
Note that we can accidentally write `enum Weekday w = 972;` without the compiler warning us!

To avoid writing `enum Weekday` instead of just `Weekday`, we can use the same typedef trick as before.

#####The `switch` statement
Since enums are just a collection of integer constants, printing enums would just print this constant, and not the name. we will create a function that prints the name of each constant by using the `switch` statement.

The switch statement is very similar to a set of if-else-statements, but with one major difference: You can only switch on a single value (unlike a chain of if-statements, which can contain anything). This means that a switch-statement can often more clearly express the intent of the code.
```C
switch(value){
case 1:
    printf("The value is 1\n");
    break;
case 2:
    printf("The value is 2\n");
    // No `break` here: case 2 will "fallthrough" to the next case.
    //  (this is a common source of bugs)
case 3:
    printf("The value is 2 or 3\n");
    break;
default:
    printf("The value is something else\n");
}
```

####A card trick

 - [ ] Create an enum that signifies the suit of the card (club, spade, heart, diamond)
 - [ ] Write a function that returns a string (`char *`) that gives a readable name of the card suit enum.
   - Use a switch-statement, with a case for each member in the enum.
   - Note: If you have a return statement inside a case, any code after it (such as a `break` label) will be unreachable.
 
 - [ ] Write a function that performs a magic card trick:   
   - Create a struct that has two members: the first is the suit, and the second is the value
   - Create a function that takes a card, and returns a new card!
   
 - [ ] Create a function that does not return a new card, but instead modifies the original card.
   - Hm, why doesn't it work?
   
When we pass a parameter to a function, the value is copied (commonly called "pass-by-value"). So when we pass a struct to a function and modify it, we just modify the copy! To modify the original ("un-copied") value, we need to pass the memory location of the original ("pass-by-reference").



###9: Pointer basics

To get the address (memory location) of a variable, we use the `&` operator:
```C
int i = 5;
printf("Address of i: %p\n", &i);
```

A pointer (to a a variable of a type) is a variable that can store an address. A pointer is not a type, but a *type constructor*: it must be applied to a proper type to form a proper type of its own.
(Similarly, you cannot have a "list of nothings", but you can have a "list of penguins". A "list" on its own is not a type.)
```C
// (continued from above)
// A "pointer to int", called `addr`
int * addr = &i;
// A "pointer to nothing" does not compile, and makes no sense anyway!
* wut = &i;
```

Here's the confusing part: The `*` symbol is not just used for declaring pointers, but also for dereferencing a pointer (ie accessing the value stored at that address):
```C
// (continued from above)
// Should print 5
printf("Value stored at memory location %p: %d\n", addr, *addr);

int j = *addr;
printf("Value of j: %d\n", j);  // (Also 5)
```

With pointers, we can pass memory locations as parameters to functions:
```C
// Takes the address of an integer as a parameter
void func(int * j){
    // Writes the value 7 at the memory location pointed to by j
    *j = 7;
}
int main(void){
    int i = 6;
    func(&i);   // Passes the address of i, not i itself
    printf("Value of i: %d\n", i);  // should print 7
}
```

 - [ ] Now we can create a function that performs a magic card trick by modifying the original card (passing the card "by reference").
   - Make sure you dereference the right thing!
     - `*foo.bar` means `*(foo.bar)`, not `(*foo).bar`!
     - We need to dereference the struct, not the members.

####Alternative dereference syntax for structs
Writing `(*card).value = ...` is rather tedious. There exists an alternative syntax for accessing members of dereferenced structs: `card->value`
 - [ ] Rewrite the pass-by-reference card trick with the more readable `->` syntax.
 
 

    
###10: Fixed-size arrays and basic pointer arithmetic
C does not have any dynamically sized arrays (arrays that change the length of at runtime)! Any programming language that has dynamic arrays is hiding a lot of bookkeeping behind the scenes. To create our own dynamic arrays, we'll have to either create our own, or find some code someone else has written. So for now, we will only look at fixed-size arrays.

In C, it is said that "declaration reflects use". As we saw with pointers, they were used as `*p = val;`, so therefore they are declared  as `int *p;` (if we remove one of the spaces). Similarly with arrays: They are used as `arr[3] = 5;`, so they are declared as `int arr[8];`.

```C
// Declares an array of 8 integers
//  Note that the array is currently uninitialized! It will contain junk
int arr1[8]; 

// Arrays are 0-indexed
printf("The first element: arr1[%d]: %d (should be junk)\n", 0, arr[0]);

// Declares an array of 6 integers, where the first 3 elements are 4, 2 and 7
//  The remaining elements will be set to 0
int arr2[6] = {4, 2, 7};
printf("arr2[%d]: %d (should be 4)\n", 0, arr[0]);
printf("arr2[%d]: %d (should be 7)\n", 2, arr[2]);
printf("arr2[%d]: %d (should be 0)\n", 3, arr[3]);

// We can therefore initialize an entire array to 0 by writing
int arr3[8] = {0};

// The compiler can deduce the length of the array if we initialize it
//  But it is not dynamically sized! The compiler just fills in the missing `5` in the square brackets
int arr4[] = {6, 5, 2, 3, 0};
```

####Memory layout of arrays
Arrays are just a contiguous block of memory. If we were to access an array "out-of-bounds" (either negative indexes, or indexes larger than the length of the array), then we would just access whatever happened to be there. Probably. This is what is known as "undefined behaviour", a world where [literally anything](http://c-faq.com/ansi/undef.html) is allowed to happen.

```C
int main(){
    int j = 44;
    int i = 3;
    int arr[2] = {10, 20};
    printf("arr[i]: %d (probably 44)\n", arr[i]);
    // (Note that the memory order is reversed)
}
```

If we were to write a function that can work on arrays of any length, then that function needs to know how long the array is. One way of solving this would be to store the length of the array as part of the type (as if creating a struct behind the scenes), but the C philosophy does not approve of this kind of overhead. In fact, the C philosophy approves *so little* of any kind of overhead, it doesn't even send the array to the function! It just sends a pointer to the first element of the array!

```C
// These two are literally completely equivalent!
void foo(int arr[]){
    // ...
}
void foo(int * arr){
    //...
}


int arr[8] = {0};
// When calling `foo`, these are also equivalent!
foo(arr);       // The array decays to a pointer automatically
foo(&arr[0]);   // We pass the address of the first element in the array

```


All this means that if we want a function that takes arrays as parameters, we must send the location of the first element of the array (an array "decays" into a pointer all by itself when we pass it to a function), as well as the length of the array.

 - [ ] Write a function that prints an integer array
   - It must take two parameters: `int arr[]` (or `int *arr`), and the length of the array
   - Use a loop to iterate over the array, by using a variable for the index
 - [ ] Try passing the wrong length to the array (especially lengths too long)
   - Try compiling with `-g -fsanitize=address`, and try again. Does it tell you what and where the problem is?
     - Using AddressSanitizer is very useful for catching these kinds of subtle bugs!

   
Since arrays decay to pointers when passed to a function, this must mean that the array indexing syntax `arr[index]` is actually working with pointers! In fact, `arr[index]` and `*(arr+index)` are completely equivalent!

 - [ ] Write a function that finds the sum of the elements in an array of function
   - But do not use the `[]` syntax! Use raw pointers instead
   - You can also increment and decrement pointers with `ptr++` and `ptr--` to advance forward or backward in the array
   
    
####A note about strings

When we write the string literal `"abc"`, this actually places the values `{97, 98, 99, 0}` in read-only memory (`97` is the ascii value for `a`). The string literal does not have a length, but it is terminated with a single `0`. This way we can refer to it with a single pointer (the memory location of the first character), and the string ends when we encounter the first `0`.
    

Modules and Makefiles
=====================

So far, we have only used one source file at a time. As a project grows in size, it becomes increasingly important to split it into self-contained modules, as it is impossible to keep everything in your head at once. A good module should offer a consistent *abstraction*: We should be able to grasp how it works just by looking at the "outside" of the module, and without knowing anything about how it works on the "inside" (Eg: we understand what `printf` does without knowing how it does it). One way of forming a module is by creating a new file.

###A timer module

The module we will be making here is a simple timer, that you can hopefully use in the elevator project. (You are of course free to implement this in whatever way you want, but here are some ideas to get you started)

The timer must be able to:
 - Be started, with some duration
 - Be stopped (or reset)
 - Signal when the duration has passed
 

The function [`gettimeofday`](http://linux.die.net/man/2/gettimeofday) is found in `sys/time.h`. It modifies a `timeval` struct, such that it contains the number of seconds and microseconds since the 1st of January 1970. To convert the timeval struct into a double (so that we can more easily do addition and subtraction), we can use the following function:

```C
double get_wall_time(void){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
```
(Note that we lose some precision by converting to double, but for our usage it's fine)

The timer module must also have some internal variables, such as the start time, duration, and/or end time, and possibly whether the timer is active or not (which of these do you need?). These internal variables should not be accessible from the outside: They should only be modified by the functions in the interface (start/stop/reset/peek/hasTimedOut/etc). To achieve this, we will put the timer code in its own file.

####Header (.h) files and implementation (.c) files

There is no functional difference between header files and implementation files, but the convention is that the definitions (the actual code) goes in the .c file, while the declarations go in the .h file. Any code that needs to call functions from another file would then only include the .h file.

To compile multiple files at the same time, we can either pass all the files together (eg `clang -Wall file1.c file2.c`), or use a makefile (see below).

 - [ ] Create the timer module, with a .h and a .c file with the same name (eg timer.h and timer.c)
   - Only put the function declarations in the header file
   - Put the function definitions (implementations) and local variables in the .c file
 - [ ] Test the module from the file that has your `main()` function
   - Include the .h file, not the .c file
   - To check that the duration is correct, call the program with `time ./program` from the command line, and look at the `real` time used


###Makefiles

Compile times will grow with the number of lines of code. If we can compile the files individually (and then link them together), we only need to compile the one we made changes to, thus saving on compile time. Also, back in 1972 there often wasn't enough memory installed in the system to compile everything at the same time anyway!

The program `make` lets us automate this process, by looking at the timestamps of the dependencies: The executable file depends on the source code, so if the source code is newer than the executable, it must be rebuilt. We will separate the dependencies into two phases:

 - The executable depends on the object (.o) files
   - It is created by linking together the object files
 - The object files depend on the corresponding .c files
   - They are created by compiling the .c files with `-c`

A makefile is based on rules, which are used to decide what happens when the target timestamp is older than the dependency. Rules are structured like this:
   
```Makefile
# The basic rule:
target: dependency1 dependency2
	command1
	command2
# Note: The indentation above must use a single tab, not spaces!
    
# Example:
timer.o: timer.c
	clang -c timer.c
    
# When using the same rule for several targets
targets: target-pattern: dependency-pattern
	command
```

 - Creating variables:
   - `SOURCES = main.c timer.c`
   - `EXECUTABLE = someProgramName`
 - Accessing variables:
   - `$(TARGET)`
 - Substituting:
   - `OBJECTS = $(SOURCES:.c=.o)` (sets `OBJECTS` to `main.o timer.o`)
 - Pattern matching:
   - `$(OBJECTS): %.o: %.c`
 - Automatic variables:
   - `$@`: The target of the rule
   - `$^`: All the dependencies
   - `$<`: Only the first dependency
   
With these, we can now create a simple makefile.

 - [ ] Create a file called `makefile` (or `Makefile`). (It has no file extension)
 - [ ] Create all the variables we need:
   - The name of the executable (just pick something)
   - The list of all the source files
   - The list of all the corresponding object files (use substitution!)
   - The list of all the compiler flags (eg `-Wall`, `-g`, etc)
   - The name of compiler to use (`clang` or `gcc`)
 - [ ] Create a rule for compiling object files
   - Use pattern matching, since the rule for all the object files are the same
   - Use the automatic variable `$<` to reference the name of the dependency (ie the .c file)
   - Remember to use the extra flag `-c`
   - Remember also to include the list of compiler flags
 - [ ] Create a rule for linking the executable
   - You can use the compiler to link object files (ie `clang obj1.o obj2.o`)
   - Use the automatic variable `$^` to get the list of the dependencies (the object files)
   - Use the automatic variable `$@` to get the name of the target (the executable name)
     - Use the flag `-o` to set the name of the output executable
   - Makefiles are read from the top down, so put this rule *above* the rule for creating the object files
 - [ ] Invoke the makefile by calling `make` from the command line
    
    
Goodbye World (Advanced/For fun)
================================

We will be doing something rather unconventional here: By looking at each little piece in the standard "hello world" program in detail, and then removing that piece, we will break down (in more ways than one) a C program and the toolchain used for building an executable.

###1: The standard "hello world" program

 - [ ] Start with the standard "hello world" program, as before
   
###2: Without #include

Let us now see what happens when we remove `#include <stdio.h>`:
 - [ ] Remove the #include, and compile both with gcc and clang
   - You will surely see a difference in the quality of the compiler output!
 - [ ] Since the compiler gave us "just a warning", we can still run the program. Try running it.

All lines that start with `#` are so-called "preprocessor directives". The preprocessor performs text manipulation before the compiler does its work, and has no understanding of what constitutes valid C-code. The `#include`-directive tells the preprocessor to scan the specified file before continuing with the rest of the file; it is essentially a copy/paste operation. Other directives include `#define a b`, which replaces any instance of `a` with `b`. This may be useful for defining constants, eg `#define NUM_FLOORS 4`.

To see what our source code looks like after the preprocessor has done its work, we use the compiler option `-E`.
 - [ ] Put the #include-directive back, and invoke the compiler with `-E`.
   - Yikes! That's a lot of stuff. `-E` is mostly useful when you need to see what your preprocessor directives output. [Some people](http://jhnet.co.uk/articles/cpp_magic) do truly ~~awful~~ magical things with the preprocessor, and `-E` is an invaluable tool for creating ~~such abominations~~ rainbows and sunshine.
 

Back to what happens when we remove the #include-directive: The problem is that the compiler has no way of knowing what the function `printf` looks like. We can help the compiler out by providing this definition ourselves.
 - [ ] Provide a definition of `printf`
   - The output from clang is helpful enough to give us the return type and argument types. `...` is also a valid argument: It means that the function takes any number of *additional* arguments, and that their types are unknown.
        
So why did the program compile and run even if the compiler didn't know what `printf` looks like? As it turns out, in C the "default" type of a function (one that is not defined) is `int function()`: A function that takes any number of arguments and returns an integer. Since `printf` happens to be such a function, this technically "works fine".


###3: With no return value

C is an old language, and so there exists several standards: c89, c99, and the most recent: c11. In c89, the return statement at the end of `main` was mandatory, but this was lifted in c99, where a program returns 0 unless specified otherwise.

 - [ ] We can get the return value of the program that last ran by typing `echo $?` in the terminal. Change the return value of the program, run it, and verify that you get the correct value from `echo $?`.
 - [ ] Remove the `return` statement, and ~~go back in time to 1989~~ compile with the option `-std=c89` using gcc (clang has poor support for old versions of C). Run the program and check the return value. What do you get?
   - Do you see any place in the code that corresponds to the return value of the program?
   - Hint (Spoilers): Try modifying the printed message to something else, like "Penguins!".


###4: The smallest C program?

Let's keep removing things! The first to go is `printf`.

Remember the "default" function type? This also goes for `main`: It takes an unknown number of arguments, and returns an integer. This means we can remove the `void` argument, and also the return type.
 - [ ] Compile this "program" (there's no code inside `main` any more...) and run it. Wasn't that exciting?

###5: Definitely the smallest C program.

You would think a program couldn't get smaller and more useless than this, but it can.

 - [ ] Delete everything in the entire file, and try compiling it.

The error message tells us that there is a problem in function `_start`: An undefined reference to `main`. The problem is that the automatically generated `_start` function tries to call `main`, but the compiler hasn't given the linker a function with that name. As it turns out, `main` isn't really where execution starts! In fact there are several functions that are called before `main` (and we can even define our own), but `_start` is king of all functions.

So to create an executable without `main`, we need to prevent *the C compiler* from creating a standard `_start` function. To do this, we will compile and link in two separate phases.

 - [ ] First, we must generate a file to give to the linker. Since the linker works with object files, we will compile our empty file with the compiler option `-c`.
 - [ ] Invoke the linker with `ld`, and pass the object file. You can give a name to the executable using `-o` as before.
 - [ ] Run the worlds shortest C program!
 
As an added bonus, this is also the shortest program that produces its own source code as its output...

The words "Segmentation Fault" means that the operating system prevented you from accessing memory that your program doesn't own. In this case, the value of `_start` was not defined, so `ld` gave it a default value, one that happened to be outside the valid memory region of the program. Without an operating system, this program would have interpreted whatever happened to lie in this memory as valid machine code, and all hell would break loose.


Appendix
========

###Macros
Todo

###The `null` pointer
Todo
 - if(ptr)
 
###Pointer casting
Todo
 - reinterpret cast: `*(T*)&v`

###Function pointers
Todo
 - function types
 

###Higher-order functions
Todo
####Example: `qsort`

###Floating-point is hard
Todo
 - digital representation of analog concept -> reduced presicion
 - `recurrence!("108-(815-1500/a[n-2])/a[n-1]")(4.0, 4.25)`
 - foldl1 (+) (replicate 10 0.1)  !=  0.1 * 10
 
###`clang-format`
Todo
Upload suggested `.clang-format` file
 
 