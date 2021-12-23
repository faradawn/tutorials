#include <stdio.h>

typedef struct A{
    int x;
    char* argv[0];
}A;

int main(){
    char* argv[4]={"echo", "-e", "yay", NULL};
    A arr[2];
    A a1;
    a1.x=10;
    a1.argv[3]=argv[0];
    printf("size %ld\n", sizeof(arr));
    puts(a1.argv[3]);


}