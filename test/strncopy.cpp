#include <stdio.h>
#include <string.h>

int main(void)
{
    char longSrcStr[] = "Long_words";
    char shortDestStr[] = "Short";

#if 0
    strcpy(shortDestStr, longSrcStr);

#else
    strncpy(shortDestStr, longSrcStr, sizeof(shortDestStr)-1);
    // longSrcStr 길이가 shortDestStr 보다클경우,
    // buf에들어가는문자열이 '\0' 으로끝나지않을수있기때문입니다.
    // 따라서다음과같이써주어야합니다
    shortDestStr[sizeof(shortDestStr)-1] = '\0';
#endif
    printf("%lu\n", sizeof(shortDestStr));
    printf("%s\n", shortDestStr);
}