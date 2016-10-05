

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;


template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    if ( !v.empty() ) {
        out << '[';
        std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
        out << "\b\b]";
    }
    return out;
}

class Solution
{
public: 
    void recoverRotatedSortedArry(vector<int> &nums)
    {

    }
};

int main()
{ 
    vector<int> nums = {4,5,1,2,3};

    
    return 0;
}










