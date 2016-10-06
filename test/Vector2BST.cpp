
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class TreeNode {
public:
   int val;
   TreeNode *left, *right;
   TreeNode(int val) 
   {
        this->val = val;
        this->left = this->right = NULL;
    }
};

class Solution {
public:
    void binaryTreePaths(TreeNode* root, vector<string>&res, string str);
    vector<string> binaryTreePaths(TreeNode* root);

    TreeNode *sortedArrayToBST(vector<int> &A) 
    {
        // write your code here
        if (A.size() == 0)
            return NULL;
        int len = A.size();
        return buildTree(A, 0, len-1);
    }
    
    TreeNode *buildTree(vector<int> &A, int start, int end) 
    {
        if (start > end) return NULL;
        int mid = start + (end - start)/2;

        TreeNode *root = new TreeNode(A[mid]);
        root->left = buildTree(A, start, mid-1);
        root->right = buildTree(A, mid+1, end);
        return root;
    }
};

void Solution::binaryTreePaths(TreeNode* root, vector<string>&res, string str) //Private Function
{
    if(!root)
        return;
    
    str.append(to_string(root->val));
    str.push_back('-');
    str.push_back('>');
    
    if(!root->left && !root->right)
    {
        str.pop_back();
        str.pop_back();
        res.push_back(std::move(str));
    }
    
    binaryTreePaths(root->left, res, str+"L");
    binaryTreePaths(root->right, res, str+"R");
}

vector<string> Solution::binaryTreePaths(TreeNode* root) //Public Function
{
    vector<string> result;
    
    if(!root)
        return result;
    
    binaryTreePaths(root, result, ""); //Trigger the function here
    return result;
}

int main()
{

    Solution solution;
    vector<int> nums = {1,2,3,4,5,6,7};

    TreeNode* root = solution.buildTree(nums, 0, nums.size()-1);
    
    vector<string> paths = solution.binaryTreePaths(root);

    for(auto path:paths)
    {
        cout << path << " " <<endl;
    }

    return 0;
}



