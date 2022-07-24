# Math and Array

## Bits
count number of set bits in a number
```
int a = __builtin_popcount(10)
```

## C++ What is (const &arr)
- stack overflow: https://stackoverflow.com/questions/26647152/are-vectors-passed-to-functions-by-value-or-by-reference-in-c


## How can arrays be used?
1 - string and array of strings
```c
char cmu[]="carnegie";
char uch[]="chicago";
char argv[2]={cmu, uch};
```

2 - what can functions return?
- int? yes
- struct? yes
- string? no
- array? no

3 - How to declare an array of structs?
```c
// variable sized struct
typedef struct A{
    int x;
    char* argv[];
}A; // size 8 (align to 8, altough argv = 0 size)
A arr[2]; // size 2 * 8 = 16

// fixed sized struct
typedef struct A{
    int x;
    char* argv[2];
}A; // size 24 (align to 8)
A arr[2]; // size 2 * 24 = 48
```

