#include <stdlib.h>      // for itoa() call
#include <stdio.h>       // for printf() call
#include <string.h>

#include <iostream>

using namespace std;

int main()
{
    int num = 123;
    char buf[ 5];

    // convert 123 to string [buf]
    

    // Method 1
    //itoa(num, buf, 10 );

    // Method 2
    sprintf(buf, "%d", num);

    // print our string
    printf( "%s\n", buf);

    return 0;
}