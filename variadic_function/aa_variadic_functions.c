#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define MIN 1

int sum(int size, ...) {
    int sum = 0;
    va_list list;
    va_start(list, size);
    for(int i = 0; i < size; i++){
        sum += va_arg(list, int);
    }
    va_end(list);
    return sum;
}

int main(){

    int elements[10] = {};

    for(int i = 0; i < 10; i++){
        int randomNumber = rand() % (MAX - MIN + 1) + MIN;
        printf("%d ", randomNumber);
        elements[i] = randomNumber;
    }

    printf("\nsum: %d\n",
     sum(10, elements[0], elements[1], elements[2], elements[3], elements[4],
     elements[5], elements[6], elements[7], elements[8], elements[9]));

}
