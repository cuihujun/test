#include <string>
#include <cstring>
#include <iostream>


using namespace std;

int main(void )
{
    std::string str = "asdfasdaf";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    
    
    cout<< cstr <<endl;
    delete [] cstr;
}