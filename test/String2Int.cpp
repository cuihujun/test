#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <stdlib.h>  
#include <string> 

using namespace std;

void split(const std::string &s, char delim, std::vector<string> &elems)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

vector<int> parseInts(string str) 
{
   char* cpStr = strdup(str.c_str());
   char* token;
   vector<string> sRes;
   vector<int> nums;
   
   sRes = split(cpStr, ',');
   

   // STRING TO INT >>>>>>>>>>
   for(auto snum: sRes)
   {
        nums.push_back(stoi(snum));   
   }
   return nums;
}

int main() 
{
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) 
    {
        cout << integers[i] << "\n";
    }
    
    return 0;
}