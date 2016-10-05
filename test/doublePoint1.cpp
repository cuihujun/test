


#include <iostream>
#include <stack>

using namespace std;


#if 1

void change(string* p)
{
    *p = "bbb";
}
int main(int argc, char* argv[])
{
    string v = "aaa";
    change(&v);
    cout << v << endl;
    
    return 0;
}


#else

void change(char** p)
{
    *p = "bbb";
}
int main(int argc, char* argv[])
{
    char *v = "aaa";
    change(&v);
    printf("%s",v);
    return 0;
}



#endif
