#include <iostream>
using namespace std;

class Node{
public:
    Node() : value(0), next(NULL) {}
    Node( int theValue, Node *theNext ) : value(theValue), next(theNext){}
    int value;
    Node *next;
};

class LinkedList{
public:
    LinkedList( );
    ~LinkedList( );
    void push_front( int value );
    void push_back( int value );
    void delete_front( );
    void show_element( );

    void BubbleSortVer1( );
    void BubbleSortVer2( );
private:
    Node* head;

    Node* swap( Node*, Node* );
};

LinkedList::LinkedList( ) : head(NULL){

}
LinkedList::~LinkedList( ){
    if( head )
        delete_front( );
}

void LinkedList::push_front( int value ){
    Node *newNode = new Node(value, head);
    head = newNode;
}

void LinkedList::push_back( int value ){
    if( !head )
        push_front( value );
    else{
        Node *current = head;
        while( current->next != NULL )
            current = current->next;
        Node *newNode = new Node(value, NULL);
        current->next = newNode;
    }
}

void LinkedList::delete_front( ){
    if( !head )
        return;
    Node *deleteNode = head;
    head = head->next;
    delete deleteNode;
}

void LinkedList::show_element( ){
    Node *current = head;
    while( current ){
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}

void LinkedList::BubbleSortVer1( ){
    if( !head ) return;
    bool change = true;
    while( change ){ //round
        Node *prev = NULL;
        Node *current = head;
        change = false;
        while( current->next != NULL ){
            if( current->value > current->next->value ){
                current = swap(current, current->next);
                change = true;
                if( prev != NULL )
                    // swap is unrelated to head, update prev' s next link
                    prev->next = current;
                else
                    // swap is related to head, change head pointer
                    head = current;
            }
            prev = current;
            current = current->next;
        }
        show_element( );
    }
}

void LinkedList::BubbleSortVer2( ){
    if( !head ) return;
    bool change = true;
    Node *prevHead = new Node(0, head);
    while( change ){
        change = false;
        Node *prev = prevHead;
        Node *current = prev->next;
        while( current->next != NULL ){
            if( current->value > current->next->value ){
                prev->next = current = swap(current, current->next);
                change = true;
            }
            prev = current;
            current = current->next;
        }
    }
    head = prevHead->next;
    delete prevHead;
}

Node* LinkedList::swap( Node* p, Node* q){
    Node *temp = q->next;
    q->next = p;
    p->next = temp;
    return q;
}
int main( ){
    LinkedList list;
    list.push_back( 4 );
    list.push_back( 7 );
    list.push_back( 5 );
    list.push_back( 1 );
    list.push_back( 3 );
    list.push_back( 2 );
    list.push_front( 6 );
    list.push_front( 0 );
    list.show_element( );

    list.delete_front( );
    list.show_element( );

    cout << "sorting list1: \n";
    list.BubbleSortVer2( );
    cout << "After sort: ";
    list.show_element( );

    LinkedList list2;
    list2.push_back( 1 );
    list2.push_back( 2 );
    list2.push_back( 3 );
    list2.push_back( 4 );
    list2.push_back( 5 );
    list2.push_back( 7 );
    list2.push_back( 6 );

    cout << "\nsorting list2: \n";
    list2.BubbleSortVer2( );
    cout << "After sort: ";
    list2.show_element( );
    return 0;
}