

#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <stack>
#include <sstream>
#include <iomanip>
#include <list>

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


class TreeNode
{
public:
    int val;
    TreeNode *left, *right;
    
    TreeNode(int val)
    {
        this->val = val;
        this->left = NULL;
        this->right =  NULL;
    }
};

// this struct is for zigzagLevelOrderTraversal()
struct Node
{
    TreeNode *node;
    int level;
    Node(){}
    Node(TreeNode *n, int l):node(n), level(l){}
};

// this class is for BST Validate
class ResultType
{
public:
    bool isBST;
    TreeNode *maxNode, *minNode;
    ResultType() {
        this->isBST = true;
        this->maxNode = NULL;
        this->minNode = NULL;
    }
};

class Solution
{
public:
    
    TreeNode *lastNode = NULL;
    
    vector<int> preorderTraversal(TreeNode *root);
    vector<int> inorderTraversal(TreeNode *root);
    
    vector<int> postorderTraversal(TreeNode *root);
    vector<string> binaryTreePaths(TreeNode* root);
    
    
    vector<vector<int>> levelOrderTraversal(TreeNode *root);
    vector<vector<int>> levelOrderBottomTraversal(TreeNode *root);
    vector<vector<int>> zigzagLevelOrderTraversal(TreeNode *root);
    
    void flattenBinaryTreeToLinkedList(TreeNode *root);
    /**
     * @param root: The root of binary tree.
     * @return: True if the binary tree is BST, or false
     */
    bool isValidBST(TreeNode *root);
    bool isIdentical(TreeNode* a, TreeNode* b);
    int maxDepth(TreeNode* node);
    
    vector<int> binaryTreePathsSum(TreeNode* root);
    int leftLeavesSum(TreeNode *root);
    int rightLeavesSum(TreeNode *root);
    int totalleaveSum(TreeNode* root);
    vector<int> levelSums(TreeNode *root);
    
    string serialize(TreeNode *root);
    TreeNode* deserialize(string data);
    
    TreeNode* insertNode(TreeNode* node, int val);
    TreeNode* deleteNode(TreeNode* root, int val);
    TreeNode* searchBST(TreeNode* root, int val);
    
    TreeNode* insertNode(TreeNode* root, TreeNode* node);
    TreeNode* deleteNode(TreeNode* root, TreeNode* node);
    
    void displayBinaryTree(TreeNode* root);
    
    void invertBinaryTree(TreeNode *node);
private:
    vector<int> preorder;
    vector<int> inorder;
    void preorderTraverse(TreeNode *root);
    void inorderTraverse(TreeNode *root);
    
    void binaryTreePaths(TreeNode* root, vector<string>&v,string s);
    void binaryTreePathsSum(TreeNode* root, vector<int> &res, vector<int> values);
    
    ResultType checkBST(TreeNode* root);
    bool isLeaf(TreeNode* node);
    TreeNode* minValueNode(TreeNode* node);
    
    vector<string> split(const string &str, string delim);
};

#pragma mark - Check BST
/*
 1)
 
 1
 2              3
 4       5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 cout << solution.isValidBST(root) << endl;
 
 OUTPUT:
 0
 
 2)
 50
 /     \
 30      70
 /  \    /  \
 20   40  60   80
 
 Solution solution;
 string str = "{50,30,70,20,40,60,80}";
 TreeNode* root = solution.deserialize(str);
 cout << solution.isValidBST(root) << endl;
 
 OUTPUT:
 1
 */
ResultType Solution::checkBST(TreeNode *root) //Private function
{
    ResultType result;
    if (root == NULL)
    {
        return result;
    }
    
    ResultType left = checkBST(root->left);
    ResultType right = checkBST(root->right);
    
    if (!left.isBST || !right.isBST)
    {
        result.isBST = false;
        return result;
    }
    
    if (left.maxNode != NULL && left.maxNode->val >= root->val) {
        result.isBST = false;
        return result;
    }
    
    if (right.minNode != NULL && right.minNode->val <= root->val) {
        result.isBST = false;
        return result;
    }
    
    result.isBST = true;
    result.minNode = left.minNode == NULL ? root : left.minNode;
    result.maxNode = right.maxNode == NULL ? root : right.maxNode;
    return result;
}


bool Solution::isValidBST(TreeNode *root) // Public function
{
    ResultType result = checkBST(root);
    return result.isBST;
}

/*
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 
 string str="{1,2,3,4,5,6,7}";
 TreeNode* newRoot = solution.deserialize(str);
 
 cout << solution.isIdentical(root, newRoot) << endl;;
 
 OUTPUT:
 1
 */
bool Solution::isIdentical(TreeNode* a, TreeNode* b)
{
    if(!a && !b)
        return true;
    else if(!a && b)
        return false;
    else if(a && !b)
        return false;
    else {
        if(a->val != b->val)
            return false;
        else
            return isIdentical(a->left, b->left) && isIdentical(a->right, b->right);
    }
}

int Solution::maxDepth(TreeNode* node)
{
    if (!node) return 0;
    return 1 + std::max(maxDepth(node->left), maxDepth(node->right));
}

#pragma mark - In-Order Traversal
/********************************************************
 In-Order Traversal
 
 1
 2              3
 4      5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 cout << solution.inorderTraversal(root) << endl;
 
 OUTPUT:
 [4 2 5 1 6 3 7 ]
 */
void Solution::inorderTraverse(TreeNode *root) //Private
{
    if (root == NULL)
    {
        return;
    }
    // NOTE: 1. Left -> 2. Root -> 3. Right
    inorderTraverse(root->left);
    inorder.push_back(root->val);
    inorderTraverse(root->right);
}

vector<int> Solution::inorderTraversal(TreeNode *root) //Public
{
    inorder.clear();
    inorderTraverse(root);
    return inorder;
}

#pragma mark - Pre-Order Traversal
/********************************************************
 Pre-Order Traversal
 1
 2              3
 4      5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 cout << solution.preorderTraversal(root) << endl;
 
 OUTPUT: [1 2 4 5 3 6 7]
 */
void Solution::preorderTraverse(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    
    // NOTE: 1. Root -> 2. Left -> 3. Right
    preorder.push_back(root->val);
    preorderTraverse(root->left);
    preorderTraverse(root->right);
}

vector<int> Solution::preorderTraversal(TreeNode *root)
{
    preorder.clear();
    preorderTraverse(root);
    return preorder;
}

#pragma mark - Post-Order Traversal
/********************************************************
 Post-Order Traversal
 
 1
 2              3
 4       5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 cout << solution.preorderTraversal(root) << endl;
 
 OUTPUT: [4 5 2 6 7 3 1 ]
 */
vector<int> Solution::postorderTraversal(TreeNode *root)
{
    vector<int> result;
    stack<TreeNode *> nodeStack;
    
    TreeNode *current = root, *lastVisited = NULL;
    while (current != NULL || !nodeStack.empty())
    {
        while (current != NULL)
        {
            nodeStack.push(current);
            current = current->left;
        }
        current = nodeStack.top();
        if (current->right == NULL || current->right == lastVisited)
        {
            nodeStack.pop();
            result.push_back(current->val);
            lastVisited = current;
            current = NULL;
        }
        else
        {
            current = current->right;
        }
    }
    return result;
}

#pragma mark - Level-Order Traversal
/********************************************************
 Level-Order Traversal
 
 1
 2              3
 4       5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 vector<vector<int>> levelOrderTraversal = solution.levelOrderTraversal(root);
 for(auto list : levelOrderTraversal)
 {
 cout<<list<<endl;
 }
 
 OUTPUT:
 [1 ]
 [2 3 ]
 [4 5 6 7 ]
 
 */

vector<vector<int>> Solution::levelOrderTraversal(TreeNode *root)
{
    vector<vector<int>> result;
    result.clear();
    
    if (root == NULL) {
        return result;
    }
    
    queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty())
    {
        unsigned long int size = queue.size();
        vector<int> level;
        
        for (int i = 0; i < size; i++)
        {
            TreeNode *head = queue.front();
            queue.pop();
            level.push_back(head->val);
            if (head->left != NULL)
            {
                queue.push(head->left);
            }
            if (head->right != NULL)
            {
                queue.push(head->right);
            }
        }
        result.push_back(level);
    }
    return result;
}

#pragma mark - Level-Order-Bottom Traversal
/********************************************************
 Level-Order-Bottom Traversal
 
 1
 2              3
 4       5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 vector<vector<int>> levelOrderBottomTraversal = solution.levelOrderBottomTraversal(root);
 for(auto list : levelOrderBottomTraversal)
 {
 cout<<list<<endl;
 }
 
 OUTPUT:
 [4 5 6 7 ]
 [2 3 ]
 [1 ]
 */
vector<vector<int>> Solution::levelOrderBottomTraversal(TreeNode *root)
{
    
    vector<vector<int> > result;
    result.clear();
    if(root == NULL)
        return result;
    
    queue<TreeNode*> queue;
    queue.push(root);
    queue.push(NULL);
    vector<int> tmp;
    while(!queue.empty())
    {
        //travesal current level
        TreeNode* p = queue.front();
        queue.pop();
        if(p!=NULL)
        {
            tmp.push_back(p->val);
            if(p->left)
                queue.push(p->left);
            if(p->right)
                queue.push(p->right);
        }else
        {
            if(!tmp.empty())
            {
                queue.push(NULL);
                result.push_back(tmp);
                tmp.clear();
            }
        }
    }
    reverse(result.begin(),result.end());
    return result;
}

#pragma mark - ZigZag Level Order Traversal
/********************************************************
 ZigZag Level Order Traversal
 
 1
 2              3
 4       5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 vector<vector<int>> zigzagLevelOrderTraversal = solution.zigzagLevelOrderTraversal(root);
 
 vector<int> res = {};
 for(auto list : zigzagLevelOrderTraversal)
 {
 res.insert(res.end(), list.begin(), list.end());
 }
 cout << res << endl;
 
 OUTPUT:
 [1 ]
 [3 2 ]
 [4 5 6 7 ]
 */

vector<vector<int>> Solution::zigzagLevelOrderTraversal(TreeNode *root)
{
    vector<vector<int> > ret;
    ret.clear();
    if (root == NULL)
        return ret;
    
    queue<Node> nodeQueue;
    nodeQueue.push(Node(root, 0));
    int curLevel = -1;
    vector<int> values;
    
    while(!nodeQueue.empty())
    {
        Node node = nodeQueue.front();
        
        if (node.node->left)
            nodeQueue.push(Node(node.node->left, node.level + 1));
        if (node.node->right)
            nodeQueue.push(Node(node.node->right, node.level + 1));
        
        if (curLevel != node.level)
        {
            if (curLevel != -1)
            {
                if (curLevel % 2 == 1)
                    reverse(values.begin(), values.end());
                
                ret.push_back(values);
            }
            values.clear();
            curLevel = node.level;
        }
        values.push_back(node.node->val);
        nodeQueue.pop();
    }
    if (curLevel % 2 == 1)
        reverse(values.begin(), values.end());
    ret.push_back(values);
    return ret;
}

#pragma mark - Flatten Binary Tree to Linked List
/********************************************************
 Flatten Binary Tree to Linked List
 
 1
 2              3
 4       5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 solution.flattenBinaryTreeToLinkedList(root);
 
 1
 2
 4
 5
 3
 6
 7
 
 vector<string> binaryTreePaths = solution.binaryTreePaths(root);
 for(auto list : binaryTreePaths)
 {
 cout<<list<<endl;
 }
 OUTPUT:
 1->R2->R4->R5->R3->R6->R7
 
 */
void Solution::flattenBinaryTreeToLinkedList(TreeNode *root)
{
    if (root == NULL) return;
    while (root)
    {
        if (root->left)
        {
            TreeNode *pre = root->left;
            while (pre->right)
                pre = pre->right;
            pre->right = root->right;
            root->right = root->left;
            root->left = NULL;
        }
        root = root->right;
    }
}

#pragma mark - Binary Tree Paths
/********************************************************
 Binary Tree Paths
 1
 2              3
 4       5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 vector<string> binaryTreePaths = solution.binaryTreePaths(root);
 for(auto list : binaryTreePaths)
 {
 cout<<list<<endl;
 }
 
 OUTPUT:
 1->L2->L4
 1->L2->R5
 1->R3->L6
 1->R3->R7
 */
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

#pragma mark - Binary Tree Sums
/********************************************************
 Binary Tree Paths Sum
 1
 2              3
 4       5      6         7
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 vector<int> sums = solution.binaryTreePathsSum(root);
 for(auto sum : sums)
 {
 cout<<sum<<endl;
 }
 
 OUTPUT:
 7
 8
 10
 11
 
 */

void Solution::binaryTreePathsSum(TreeNode* root, vector<int> &res, vector<int> values) //Private Function
{
    if(!root)
        return;
    
    values.push_back(root->val);
    
    if(!root->left && !root->right)
    {
        int sum=0;
        for(auto value: values)
        {
            sum+=value;
        }
        res.push_back(sum);
    }
    
    binaryTreePathsSum(root->left, res, values);
    binaryTreePathsSum(root->right, res, values);
}

vector<int> Solution::binaryTreePathsSum(TreeNode* root) //Public Function
{
    vector<int> result;
    
    if(!root)
        return result;
    
    binaryTreePathsSum(root, result, {}); //Trigger the function here
    return result;
}



bool Solution::isLeaf(TreeNode *node)  //Private Function
{
    if (node == NULL)
        return false;
    if (node->left == NULL && node->right == NULL)
        return true;
    return false;
}
/*
 1
 2              3
 4       5      6         7
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 int leftSum = leftLeavesSum(root);
 cout << leftSum << endl; // OUTPUT: 10
 
 int rightSum = leftLeavesSum(root);
 cout << rightSum << endl; // OUTPUT 12
 
 cout << solution.totalleaveSum(root) <<endl;  // OUTPUT 22
 */

int Solution::leftLeavesSum(TreeNode *root)
{
    // Initialize result
    int res = 0;
    
    // Update result if root is not NULL
    if (root != NULL)
    {
        // If left of root is NULL, then add key of
        // left child
        if (isLeaf(root->left))
            res += root->left->val;
        else // Else recur for left child of root
            res += leftLeavesSum(root->left);
        
        // Recur for right child of root and update res
        res += leftLeavesSum(root->right);
    }
    return res;
}
int Solution::rightLeavesSum(TreeNode *root)
{
    int res = 0;
    
    if (root != NULL)
    {
        if (isLeaf(root->right))
            res += root->right->val;
        else
            res += rightLeavesSum(root->right);
        
        res += rightLeavesSum(root->left);
    }
    return res;
}


int Solution::totalleaveSum(TreeNode* root)
{
    int sum = 0;
    
    if(root == NULL)
        return sum;
    
    if (isLeaf(root))
    {
        sum += root->val;
    }
    sum += totalleaveSum(root->left);
    sum += totalleaveSum(root->right);
    return sum;
}

vector<int> Solution::levelSums(TreeNode *root)
{
    vector<int> result;
    int sum;
    
    vector<vector <int>> nodes=levelOrderTraversal(root);
    
    for(auto node: nodes)
    {
        sum = 0;
        for(auto value: node)
        {
            sum+=value;
        }
        result.push_back({sum});
    }
    
    return result;
}

#pragma mark - Serialalize/Deserialize

/*
 
 TreeNode* root = new TreeNode(1);
 root->left = new TreeNode(2);
 root->right = new TreeNode(3);
 root->left->left = new TreeNode(4);
 root->left->right = new TreeNode(5);
 root->right->left = new TreeNode(6);
 root->right->right = new TreeNode(7);
 
 Solution solution;
 cout << solution.serialize(root) << endl;
 
 OUTPUT:
 {1,2,3,4,5,6,7}
 */
vector<string> Solution::split(const string &str, string delim)
{
    vector<string> results;
    unsigned long lastIndex = 0, index;
    while ((index = str.find(delim, lastIndex)) != string::npos)
    {
        results.push_back(str.substr(lastIndex, index - lastIndex));
        lastIndex = index + delim.length();
    }
    
    if (lastIndex != str.length())
    {
        results.push_back(str.substr(lastIndex, str.length() - lastIndex));
    }
    return results;
}

string Solution::serialize(TreeNode *root)
{
    vector<TreeNode *> nodes;
    nodes.push_back(root);
    
    for (int i = 0; i < nodes.size(); i++)
    {
        TreeNode *node = nodes[i];
        if (node == NULL)
        {
            continue;
        }
        nodes.push_back(node->left);
        nodes.push_back(node->right);
    }
    
    while (nodes.size() > 0 && nodes[nodes.size() - 1] == NULL)
    {
        nodes.pop_back();
    }
    
    if (nodes.size() == 0)
    {
        return "{}";
    }
    
    stringstream ss;
    ss << "{" << nodes[0]->val;
    for (int i = 1; i < nodes.size(); i++)
    {
        if (nodes[i] == NULL)
        {
            ss << ",#";
        } else {
            ss << "," << nodes[i]->val;
        }
    }
    ss << "}";
    
    return ss.str();
}

/*
 
 Solution solution;
 string str = "{1,2,3,4,5,6,7}";
 TreeNode* newRoot = solution.deserialize(str);
 
 vector<string> binaryTreePaths = solution.binaryTreePaths(newRoot);
 for(auto list : binaryTreePaths)
 {
 cout<<list<<endl;
 }
 
 OUTPUT:
 1->L2->L4
 1->L2->R5
 1->R3->L6
 1->R3->R7
 */

TreeNode* Solution::deserialize(string data)
{
    if (data == "{}")
    {
        return NULL;
    }
    
    vector<string> vals = split(data.substr(1, data.size() - 2), ",");
    TreeNode *root = new TreeNode(atoi(vals[0].c_str()));
    queue<TreeNode *> queue;
    queue.push(root);
    
    bool isLeftChild= true;
    for (int i = 1; i < vals.size(); i++)
    {
        if (vals[i] != "#")
        {
            TreeNode *node = new TreeNode(atoi(vals[i].c_str()));
            if (isLeftChild)
            {
                queue.front()->left = node;
            }
            else
            {
                queue.front()->right = node;
            }
            queue.push(node);
        }
        if (!isLeftChild)
        {
            queue.pop();
        }
        
        isLeftChild = !isLeftChild;
    }
    return root;
}

#pragma mark - Search/Insert/Delete BST


/*
 50                            50
 /     \         delete(20)      /   \
 30      70       --------->    30     70
 /  \    /  \                     \    /  \
 20   40  60   80                   40  60   80
 

 Solution solution;
 string str = "{50,30,70,20,40,60,80}";
 TreeNode* root = solution.deserialize(str);

 cout << solution.isValidBST(root) << endl;
 cout << solution.serialize(root) << endl;

 solution.deleteNode(root, 20);
 cout << solution.serialize(root) << endl;
 solution.deleteNode(root, 30);
 cout << solution.serialize(root) << endl;

 //solution.insert(root, 20);
 TreeNode* node = new TreeNode(20);

 solution.insertNode(root, node);
 cout << solution.serialize(root) << endl;
 solution.deleteNode(root, node);
 cout << solution.serialize(root) << endl;

 OUTPUT:
 1
 {50,30,70,20,40,60,80}
 {50,30,70,#,40,60,80}
 {50,40,70,#,#,60,80}
 {50,40,70,20,#,60,80}
 {50,40,70,#,#,60,80}
 */
TreeNode* Solution::minValueNode(TreeNode* node)
{
    TreeNode* current = node;
    
    // loop down to find the leftmost leaf
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

TreeNode* Solution::searchBST(TreeNode* root, int val)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->val == val)
        return root;
    
    // Key is greater than root's key
    if (root->val < val)
        return searchBST(root->right, val);
    
    // Key is smaller than root's key
    return searchBST(root->left, val);
}

TreeNode* Solution::insertNode(TreeNode* root, int val)
{
    // If the tree is empty, return a new node
    if (root == NULL) return new TreeNode(val);
    
    // Otherwise, recur down the tree
    if (val < root->val)
        root->left  = insertNode(root->left, val);
    else
        root->right = insertNode(root->right, val);
    return root;
}

TreeNode* Solution::insertNode(TreeNode* root, TreeNode* node)
{
    
    if (root == NULL)
    {
        root = node;
        return root;
    }
    
    if (node->val < root->val)
        root->left  = insertNode(root->left, node);
    else
        root->right = insertNode(root->right, node);
    
    return root;
}

TreeNode* Solution::deleteNode(TreeNode* root, int val)
{
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (val < root->val)
        root->left = deleteNode(root->left, val);
    
    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if (val > root->val)
        root->right = deleteNode(root->right, val);
    
    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            delete root;
            return temp;
        }
        
        // node with two children: Get the inorder successor (smallest in the right subtree)
        TreeNode* temp = minValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        root->val = temp->val;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->val);
    }
    return root;
}

TreeNode* Solution::deleteNode(TreeNode* root, TreeNode* node)
{
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (node->val < root->val)
        root->left = deleteNode(root->left, node->val);
    
    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if (node->val > root->val)
        root->right = deleteNode(root->right, node->val);
    
    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            delete root;
            return temp;
        }
        
        // node with two children: Get the inorder successor (smallest in the right subtree)
        TreeNode* temp = minValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        root->val = temp->val;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->val);
    }
    return root;
}

/* displayBinaryTree
 
        50
     /     \
    30      70
   /  \    /  \
 20   40  60   80
 
 Solution solution;
 string str = "{50,30,70,20,40,60,80}";
 TreeNode* root = solution.deserialize(str);
 
 solution.displayBinaryTree(root, 0);(root, 0);
 
 */



void displayTree(TreeNode* root, int indent)
{
    if (root != nullptr)
    {
        displayTree(root->right, indent + 4);
        for(int i = 0; i < indent; i++ )
            cout <<' ';
        cout << root->val << endl;
        displayTree(root->left, indent + 4);
    }
}

void Solution::displayBinaryTree(TreeNode* root)
{
#if 1
    if (root != nullptr)
    {
        int indent = 0;
        displayTree(root->right, indent);
    }
#else

    struct NodeDepth
    {
        TreeNode* node;
        int level;
        NodeDepth(TreeNode* _n, int _lvl) : node(_n), level(_lvl) {}
    };
    
    int depth = maxDepth(root);
    
    char buf[1024];
    int last_level = 0;
    int offset = (1 << depth) - 1;
    
    // using a queue means we perform a breadth first iteration through the tree
    std::list<NodeDepth> nodeQueue;
    
    nodeQueue.push_back(NodeDepth(root, last_level));
    while (nodeQueue.size())
    {
        const NodeDepth& nodeDepth = *nodeQueue.begin();
        
        // moving to a new level in the tree, output a new line and calculate new offset
        if (last_level != nodeDepth.level)
        {
            std::cout << "\n";
            
            last_level = nodeDepth.level;
            offset = (1 << (depth - nodeDepth.level)) - 1;
        }
        
        // output <offset><data><offset>
        if (nodeDepth.node)
            snprintf(buf,sizeof(buf)-1, " %*s%d%*s", offset, " ", nodeDepth.node->val, offset, " ");
        else
            snprintf(buf, sizeof(buf)-1, " %*s",  offset << 1, " ");
        std::cout << buf;
        
        if (nodeDepth.node)
        {
            nodeQueue.push_back(NodeDepth(nodeDepth.node->left, last_level + 1));
            nodeQueue.push_back(NodeDepth(nodeDepth.node->right, last_level + 1));
        }
        
        nodeQueue.pop_front();
    }
    std::cout << "\n";

#endif
}

/*
 Solution solution;
 string str = "{50,30,70,20,40,60,80}";
 TreeNode* root = solution.deserialize(str);
 
 solution.displayBinaryTree(root);
 solution.invertBinaryTree(root);
 solution.displayBinaryTree(root);
 */
void Solution::invertBinaryTree(TreeNode *node)
{
    TreeNode* left = node->left;
    TreeNode* right = node->right;
    
    node->left = right;
    node->right = left;
    if (left!=NULL) invertBinaryTree(left);
    if (right!=NULL) invertBinaryTree(right);
}

#pragma mark - Others
/* This function counts the number of nodes in a binary tree */
int countNodes(TreeNode* root)
{
    if (root == NULL)
        return (0);
    return (1 + countNodes(root->left) + countNodes(root->right));
}

/* This function checks if the binary tree is complete or not */
bool isComplete (TreeNode* root, unsigned int index, unsigned int number_nodes)
{
    // An empty tree is complete
    if (root == NULL)
        return (true);
    
    // If index assigned to current node is more than
    // number of nodes in tree, then tree is not complete
    if (index >= number_nodes)
        return (false);
    
    // Recur for left and right subtrees
    return (isComplete(root->left, 2*index + 1, number_nodes) && isComplete(root->right, 2*index + 2, number_nodes));
}

int depth(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int left = depth(root->left);
    int right = depth(root->right);
    if (left == -1 || right == -1 || abs(left - right) > 1)
    {
        return -1;
    }
    return max(left, right) + 1;
}

bool isBalanced(TreeNode *root)
{
    return depth(root) != -1;
}

#pragma mark - Main Function
int main()
{


    Solution solution;
    
    string str = "{50,30,70,20,40,60,80}";
    TreeNode* root = solution.deserialize(str);
    
    vector<int> nums = {23,41,51,60,73,31,94,55,66,2,4,3,90};
    sort(nums.begin(), nums.end());
    
    for(auto num : nums)
    {
        solution.insertNode(root, num);
    }
    cout << solution.binaryTreePaths(root) << endl;
    
    solution.displayBinaryTree(root);
    
    
//    Solution solution;
//    string str = "{50,30,70,20,40,60,80}";
//    TreeNode* root = solution.deserialize(str);
// 
//    solution.displayBinaryTree(root);
//    solution.invertBinaryTree(root);
//    solution.displayBinaryTree(root);
    
    
    
    
    return 0;
}















