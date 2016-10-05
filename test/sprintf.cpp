#include <iostream>

int main(int argc, const char * argv[])
{
    //复制的目标字符串
    char szTarget[20];

    //复制的源字符串，假设szSource50个字节都不为0
    char szSource[51]="12345678901234567890123456789012345678901234567890";

    //以&szTarget[0]为起始地址，把szSource里面的所有内容(50个字节)copy进去
    //sprintf(szTarget , "%s" , szSource);
    //printf("%s\n", szTarget);

    //以&szTarget[0]为起始地址，把szSource的前19个字节copy进去，将szTarget[20]赋值为0;
    snprintf(szTarget , sizeof(szTarget) , "%s" , szSource);
    printf("%s\n", szTarget);

    //以&szTarget[0]为起始地址，把szSource的前20个字节copy进去。
    strncpy(szTarget , szSource , sizeof(szTarget));
    printf("%s\n", szTarget);

    return 0;
}