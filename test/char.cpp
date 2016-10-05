#include <stdio.h>
#include <string.h>

int main()
{
    char t_char[ 20]= "";
    char* s_char = "hello";
    char* d_char;
    strncpy(t_char, s_char, sizeof(t_char));
    printf( "the t_char is => %s\n", t_char);
    d_char = s_char;
    printf( "the d_char is => %s\n", d_char);
    return 1;
}