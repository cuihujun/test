

#include <iostream>
#include <vector>
using namespace std;


class ListNode
{
    
public:
    int val;
    ListNode* next;
    ListNode(int value)
    {
        val = value;
        next = NULL;
        
    }
    ~ListNode(){}
};

class Solution
{
public:
    
    void insertNode(ListNode*& node, int val)
    {
        if(node == NULL)
        {
            node = new ListNode(val);
        }
        else
        {
            insertNode(node->next, val);
        }
    }
    
    void deleteNode(ListNode*& node, int val)
    {
        if(node == NULL)
        {
            return;
        }
        if(node->val == val)
        {
            ListNode* temp = node;
            node = node->next;
            delete temp;
            temp = NULL;
        }
        else
        {
            ListNode* curr = node;
            while(curr!=NULL)
            {
                if(curr->next&&curr->next->val == val)
                {
                    ListNode* temp = curr->next;
                    curr->next = temp->next;
                    delete temp;
                    temp = NULL;
                    break;
                }
                else
                {
                    curr = curr->next;
                }
            }
        }
        

    }
    
    ListNode* mergeSortedList(ListNode* list1, ListNode* list2)
    {
        ListNode* dummy = new ListNode(0);
        dummy->next = NULL;
        ListNode* res = dummy;
        
        while(list1!=NULL && list2!=NULL)
        {
            if(list1->val < list2->val)
            {
                ListNode* temp = list1;
                dummy->next = new ListNode(list1->val);
                list1 = list1->next;
                delete temp;
                temp = NULL;
            }
            else
            {
                ListNode* temp = list2;
                dummy->next = new ListNode(list2->val);;
                list2 = list2->next;
                delete temp;
                temp = NULL;
            }
            dummy=dummy->next;
        }
        
        if(list1 == NULL)
            dummy->next = list2;
        else
            dummy->next = list1;
        
        ListNode* nodeDelte = res;
        
        res = res->next;
        delete nodeDelte;
        nodeDelte = NULL;
        return res;
        
    }
};


int main()
{
//    ListNode* node3 = new ListNode(3);
//    ListNode* node6 = new ListNode(6);
//    ListNode* node8 = new ListNode(8);
//    ListNode* node10 = new ListNode(10);
//    
//    node3->next = node6;
//    node6->next = node8;
//    node8->next = node10;
//    node10->next = NULL;
//    
//    ListNode* node4 = new ListNode(4);
//    ListNode* node5 = new ListNode(5);
//    ListNode* node7 = new ListNode(7);
//    ListNode* node11 = new ListNode(11);
//    
//    node4->next = node5;
//    node5->next = node7;
//    node7->next = node11;
//    node11->next = NULL;
//    
//    Solution s;
//    s.mergeSortedList(node3, node4);

    
    Solution s;
    
    ListNode* node= NULL;
    s.insertNode(node, 1);
    s.insertNode(node, 2);
    s.insertNode(node, 3);
    s.insertNode(node, 4);
    s.insertNode(node, 5);
    s.insertNode(node, 6);
    s.insertNode(node, 7);
    s.insertNode(node, 8);
    s.insertNode(node, 9);
    s.insertNode(node, 10);
    s.insertNode(node, 11);
    s.insertNode(node, 12);
    s.insertNode(node, 13);
    
    
    cout << node->val << endl;
    
    s.deleteNode(node, 1);
    s.deleteNode(node, 2);
    s.deleteNode(node, 3);
    
    s.deleteNode(node, 8);
    s.deleteNode(node,13);
    cout << node->val << endl;
    return 0;
}




































