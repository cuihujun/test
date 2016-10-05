


#include <stdio.h>
#include <stdlib.h>


int c ;
void PrintHelloWorld()
{
    printf("Hello World\n");
}

int* Add(int* a , int* b)
{
    c = (*a)+(*b);
    return &c;
}

int main(int argc, const char * argv[])
{
    int a=2, b=4;
    int* prt = Add(&a, &b);
    PrintHelloWorld();
    printf("Sum = %d\n", *prt);

    return 0;
}










