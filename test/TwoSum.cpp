

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public: 
	vector<int> TwoSum(vector<int>& nums, int sum)
	{
		vector<int> result;
		unordered_map<int,int> umap;

		for(int i=0; i<nums.size();i++)
		{
			if(umap.find(sum-nums[i])!=umap.end())
			{
				result.push_back(umap[sum-nums[i]]);
				result.push_back(i);
				return result;
			}
			umap[nums[i]]=i;
		}
		result = {-1,-1};
		return result;

	}


};

int main()
{
	Solution s;
	vector<int> input = {2,3,4,6,3,9};
	int sum =11;
	vector<int> res;

	res = s.TwoSum(input, sum);

	cout << res[0] << endl;
	cout << res[1] << endl;

	return 0;
}



