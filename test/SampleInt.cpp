/*

Sample Challenge 
This is a simple challenge to get things started. Given a sorted array () and a number (), can you print the index location of  in the array?

The next section describes the input format. You can often skip it, if you are using included methods.

Input Format 
There will be three lines of input:

V - the value that has to be searched.
n - the size of the array.
ar -  numbers that make up the array.
Output Format 
Output the index of  in the array.

The next section describes the constraints and ranges of the input. You should check this section to know the range of the input.

Constraints
1<=n<=100
-1000<=V<=1000 (V is in ar)
It is guaranteed that  will occur in  exactly once.
This "sample" shows the first input test case. It is often useful to go through the sample to understand a challenge.

Sample Input

4
6
1 4 5 7 9 12
Sample Output

1
Explanation 
V=4 . The value 4 is the 2nd element in the array, but its index is 1 since array indices start from 0, so the answer is .

*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() 
{
	int searchNum;
    cin >> searchNum;

    int size;
    cin >> size;

    vector<int> numbers(size);
    int index = 0;
    while (std::cin && index != size) 
    {
        std::cin >> numbers[index++];
    }
    
    vector<int>::iterator res = find(numbers.begin(), numbers.end(), searchNum);

    cout << std::distance(numbers.begin(), res) <<endl;
}





