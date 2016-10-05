#include <stdio.h>

typedef int (*CallbackType)(float);

void DoWork(CallbackType callback)
{
    printf("DoWork\n");
    float variable = 0.0f;
    int result = callback(variable);
    printf("DoWork result = %d\n", result);
}

int SomeCallback(float variable)
{
    printf("SomeCallback =>%f\n",variable);
    int result = 10;
    return result;
}

int main(int argc, char ** argv)
{
    DoWork(&SomeCallback);
    printf("%d\n", (SomeCallback == &SomeCallback)); // => 1
    return 0;
}