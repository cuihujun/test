#include <stdlib.h>      // for itoa() call
#include <stdio.h>       // for printf() call
#include <string.h>

#include <iostream>

int main()
{
    int num = 123;
    char buf[ 5];

    // convert 123 to string [buf]
    itoa(num, buf, 10 );

    // print our string
    printf( "%s\n", buf);

    return 0;
}