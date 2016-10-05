

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
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

class LinkedListNode
{
public:
    int val;
    LinkedListNode *next;
    LinkedListNode(int node_value)
    {
        this->val = node_value;
        this->next = NULL;
    }
};

class SinglyLinkedList
{
public:

    SinglyLinkedList( );
    ~SinglyLinkedList( );
    
    LinkedListNode* getHead(){return head;}
    void setHead(LinkedListNode* node){head = node;}
    LinkedListNode* getTail(){return tail;}
    void insertHead(LinkedListNode* newNode);
    void insertTail(LinkedListNode* newNode);
    void insertAfter(LinkedListNode *preNode, LinkedListNode* newNode);
    
    void removeHead();
    void removeTail();
    void removeAfter(LinkedListNode *preNode);
    void removeNode(LinkedListNode *node);
    void removeNodesEqualto(int x);
    
    bool checkHeadValueEqualTo(int val);
    LinkedListNode* searchNodeByVal_ReturnCurrNode(int val);
    LinkedListNode* searchNodeByVal_ReturnPreNode(int val);
    vector<LinkedListNode*> searchNodesByVal_ReturnVecPreNodes(int x);
    LinkedListNode* searchNode_ReturnPreNode(LinkedListNode* node);
    LinkedListNode* reverseKGroup(LinkedListNode *head, int k);
    
    // NOTE: Print the Node;
    void printList();

private:
    LinkedListNode* reverse(LinkedListNode *p1, LinkedListNode *p2);
    
    LinkedListNode* head;
    LinkedListNode* tail;
};


#pragma mark - CONSTRUCTOR & DESTRUCTOR
SinglyLinkedList::SinglyLinkedList( ) : head(NULL){}
SinglyLinkedList::~SinglyLinkedList( ) {}

#pragma mark - INSERT NODE FUNCTIONS
void SinglyLinkedList::insertHead(LinkedListNode* newNode)
{
    // NOTE: Check input value
    if (newNode == NULL)
    {
        return;
    }
    else
    {
        if (head == NULL)
        {
            // NOTE: If the head is NULL, it become the head
            newNode->next = NULL;
            head = newNode;
            tail = newNode;
        }
        else
        {
            // NOTE: Insert it to head
            newNode->next = head;
            head = newNode;
        }
    }
}

void SinglyLinkedList::insertTail(LinkedListNode *newNode)
{
    // NOTE: Check input value
    if (newNode == NULL)
    {
        return;
    }
    else
    {
        newNode->next = NULL;
        if (head == NULL)
        {
            // NOTE: If the head is NULL, it become the head
            head = newNode;
            tail = newNode;
        }
        else
        {
            // NOTE: Insert it after tail
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void SinglyLinkedList::insertAfter(LinkedListNode *preNode, LinkedListNode *newNode)
{
    if (newNode == NULL)
    {
        return;
    }
    else
    {
        if (preNode == NULL)
        {
            insertHead(newNode);
        }
        else if (preNode == tail)
        {
            insertTail(newNode);
        }
        else
        {
            // NOTE: Insert newNode after preNode
            LinkedListNode *next = preNode->next;
            preNode->next = newNode;
            newNode->next = next;
        }
    }
}

#pragma mark - REMOVE NODE FUNCTIONS
void SinglyLinkedList::removeHead()
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        LinkedListNode* removedNode;
        removedNode = head;
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->next;
        }
        delete removedNode;
        removedNode = NULL;
    }
}
void SinglyLinkedList::removeTail()
{
    if (tail == NULL)
    {
        return;
    }
    else
    {
        LinkedListNode *removedNode;
        removedNode = tail;
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            LinkedListNode *previousToTail = head;
            while (previousToTail->next != tail)
            {
                previousToTail = previousToTail->next;
            }
            tail = previousToTail;
            tail->next = NULL;
        }
        delete removedNode;
        removedNode = NULL;
    }
}

void SinglyLinkedList::removeNode(LinkedListNode *currNode)
{
#if 0
    if (currNode == NULL)
        return;
    
    if(currNode == head)
    {
        removeHead();
    }
    else if(currNode == tail)
    {
        removeTail();
    }
    else
    {
        // NOTE: Re-Search the list to get the preNode
        LinkedListNode* preNode = searchNode_ReturnPreNode(currNode);
        removeAfter(preNode);
    }
    return;
#else
    
    if (currNode == NULL)
        return;
    
    if(currNode == head)
    {
        removeHead();
    }
    else if(currNode == tail)
    {
        removeTail();
    }
    else
    {
        // copy NEXT NODE values to CURRENT NODE and delete NEXT NODE
        LinkedListNode* next = currNode->next;
        currNode->val = next->val;
        currNode->next = next->next;
        
        delete next;
        next = NULL;
        return;
    }
#endif
}

void SinglyLinkedList::removeAfter(LinkedListNode *preNode)
{
    if (preNode == NULL)
    {
        return;
    }
    else if (preNode == tail)
    {
        return;
    }
    else if (preNode->next == tail)
    {
        LinkedListNode *removedNode = preNode->next;
        tail = preNode;
        tail->next = NULL;
        delete removedNode;
        removedNode = NULL;
    }
    else
    {
        if(preNode->next)
        {
            LinkedListNode *removedNode = preNode->next;
            preNode->next = removedNode->next;
            delete removedNode;
            removedNode = NULL;
        }
        else
        {
            cerr << "[Error][removeAfter] preNode->next is NULL" << endl;
        }
    }
}

/*
 SinglyLinkedList* list = new SinglyLinkedList();
 
 vector<int> item = {1,4,3,4,4,3,6,7,4,4};
 
 int _list_item;
 int _list_i;
 
 for(_list_i=0; _list_i<item.size(); _list_i++)
 {
 _list_item = item[_list_i];
 LinkedListNode* newNode = new LinkedListNode(_list_item);
 list->insertTail(newNode);
 }
 
 list->printList(); // OUTPUT: 1 4 3 4 4 3 6 7 4 4
 
 list->removeNodesEqualto(4);
 
 list->printList(); // OUTPUT: 1 3 3 6 7 

 */
void SinglyLinkedList::removeNodesEqualto(int x)
{
    LinkedListNode* temp = head;
    
    if(head->val == x)
    {
        removeHead();
    }
    
    while(temp!=NULL)
    {
        if(temp->val == x) // x 같은 숫자 연속으로 있을때 보안하기위함
            removeNode(temp);
        if(temp->next && temp->next->val == x)
            removeAfter(temp);
        temp = temp->next;
    }
    
}

#pragma mark - K-Group Reverse NODE FUNCTIONS

/*
 
 SinglyLinkedList* list = new SinglyLinkedList();
 
 vector<int> item = {1,2,3,4,5,6,7,8,9};
 
 int _list_item;
 int _list_i;
 
 for(_list_i=0; _list_i<item.size(); _list_i++)
 {
 _list_item = item[_list_i];
 LinkedListNode* newNode = new LinkedListNode(_list_item);
 list->insertTail(newNode);
 }
 
 list->printList();  // OUTPUT: 1 2 3 4 5 6 7 8 9
 LinkedListNode* head = list->reverseKGroup(list->getHead(), 3);
 list->printList();  // OUTPUT: 3 2 1 6 5 4 9 8 7

 */
LinkedListNode* SinglyLinkedList::reverse(LinkedListNode *p1, LinkedListNode *p2)
{
    LinkedListNode *p1next = p1->next;
    LinkedListNode *p2next = p2->next;
    LinkedListNode *prev = p2next;
    LinkedListNode *p = p1next;
    
    while (p != p2next)
    {
        LinkedListNode *temp = p ->next;
        p->next = prev;
        prev = p;
        p = temp;
    }
    p1->next = p2;
    return p1next;
}

LinkedListNode* SinglyLinkedList::reverseKGroup(LinkedListNode* head, int k)
{
    if (k == 1)
    {
        return head;
    }
    
    LinkedListNode *dummy = new LinkedListNode(0);
    dummy->next = head;
    
    LinkedListNode *p1 = dummy, *p2 = dummy;
    
    for (int i = 0; i < k; i++)
    {
        if (p2 == NULL)
        {
            break;
        }
        p2 = p2->next;
    }
    if (p2 == NULL)
    {
        return head;
    }
    
    while (p2 != NULL)
    {
        p2 = reverse(p1, p2);
        for (int i = 0; i < k; i++)
        {
            if (p2 == NULL)
            {
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    setHead(dummy->next);
    
    return dummy->next;
}

#pragma mark - SEARCH NODE FUNCTIONS

bool SinglyLinkedList::checkHeadValueEqualTo(int val)
{
    if(head->val == val)
        return true;
    else
        return false;
}

LinkedListNode* SinglyLinkedList::searchNode_ReturnPreNode(LinkedListNode* currNode)
{
    LinkedListNode* temp = head;
    
    if(currNode == head)
    {
        cerr << "[searchNode_ReturnPreNode] check head of node first" << endl;
        return NULL;
    }
    
    while(temp!=NULL&&temp->next!=NULL)
    {
        if(temp->next==currNode)
            return temp;
        
        temp = temp->next;
    }
    return NULL;
}

LinkedListNode* SinglyLinkedList::searchNodeByVal_ReturnCurrNode(int val)
{
    LinkedListNode* temp = head;
    while(temp!=NULL)
    {
        if(temp->val==val)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

LinkedListNode* SinglyLinkedList::searchNodeByVal_ReturnPreNode(int val)
{
    LinkedListNode* temp = head;
    if(checkHeadValueEqualTo(val))
    {
        cerr << "[searchNodeByVal_ReturnPreNode] check head of node first" << endl;
        return NULL;
    }
    
    while(temp!=NULL)
    {
        // NOTE: Check value here
        if(temp->next && temp->next->val==val)
            return temp;
        
        temp = temp->next;
    }
    return NULL;
}

/*
 SinglyLinkedList* list = new SinglyLinkedList();
 
 vector<int> item = {1,4,3,4,3,6,7,4,4};
 
 int _list_item;
 int _list_i;
 
 for(_list_i=0; _list_i<item.size(); _list_i++)
 {
    _list_item = item[_list_i];
    LinkedListNode* newNode = new LinkedListNode(_list_item);
    list->insertTail(newNode);
 }
 
 list->printList();
 vector<LinkedListNode*> preNodes = list->searchNodesByVal_ReturnVecPreNodes(4);
 */
vector<LinkedListNode*> SinglyLinkedList::searchNodesByVal_ReturnVecPreNodes(int x)
{
    vector<LinkedListNode*> res = {};
    LinkedListNode* temp = head;
    
    if(temp->val == x)
    {
        cout << "[searchEqualX_ReturnPreNode] the value is at the Head of list" << endl;
        return {};
    }
    
    while(temp!=NULL)
    {
        if(temp->next && temp->next->val == x)
            res.push_back(temp);
        temp = temp->next;
    }
    return res;
}

#pragma mark - PRINT NODE FUNCTIONS
void SinglyLinkedList::printList()
{
    LinkedListNode* temp=head;
    
    cout <<"PRINT OUT THE NODE VALUES"<<endl;
    while(temp!=NULL)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout <<endl;
}

#pragma mark - MAIN FUNCTION
int main()
{
    
    SinglyLinkedList* list = new SinglyLinkedList();
    
    vector<int> item = {1,4,3,4,4,3,6,7,4,4};
    
    int _list_item;
    int _list_i;
    
    for(_list_i=0; _list_i<item.size(); _list_i++)
    {
        _list_item = item[_list_i];
        LinkedListNode* newNode = new LinkedListNode(_list_item);
        list->insertTail(newNode);
    }
    
    list->printList();
    
    list->removeNodesEqualto(4);

    list->printList();
    
    return 0 ;
}























