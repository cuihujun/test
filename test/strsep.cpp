#include <string.h>
#include <stdio.h>

int main(void )
{
    const char string[] = "words separated by spaces -- and, punctuation!" ;
    const char delimiters[] = " .,;:!-" ;
    char *running;
    char *token;

    running = strdup(string);
    token = strsep(&running, delimiters);    /* token => "words" */
    printf("%s\n", token);
    token = strsep(&running, delimiters);    /* token => "separated" */
    token = strsep(&running, delimiters);    /* token => "by" */
    token = strsep(&running, delimiters);    /* token => "spaces" */
    token = strsep(&running, delimiters);    /* token => "" */
    token = strsep(&running, delimiters);    /* token => "" */
    token = strsep(&running, delimiters);    /* token => "" */
    token = strsep(&running, delimiters);    /* token => "and" */
    token = strsep(&running, delimiters);    /* token => "" */
    token = strsep(&running, delimiters);    /* token => "punctuation" */
    token = strsep(&running, delimiters);    /* token => "" */
    token = strsep(&running, delimiters);    /* token => NULL */
    return 0;
}