#include <cstdlib>
#include <stdexcept>
#include <iostream>
using namespace std;
template<typename T>
class DoublyLinkedList; // class declaration

///////////////////////////////////////////////////
//Declarations
///////////////////////////////////////////////////
// list node
template<typename T>
struct DListNode {
    T obj;
    DListNode *prev, *next;
    DListNode(T e=T(), DListNode *p = NULL, DListNode *n = NULL)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list
template<typename T>
class DoublyLinkedList {
private:
    DListNode<T> header, trailer;
public:
    DoublyLinkedList() : header(), trailer() // constructor
    { header.next = &trailer; trailer.prev = &header; }
    DoublyLinkedList(const DoublyLinkedList& dll); // copy constructor
    ~DoublyLinkedList(); // destructor
    DoublyLinkedList& operator=(const DoublyLinkedList& dll); // assignment operator
    // return the pointer to the first node
    DListNode<T> *getFirst() const { return header.next; }
    // return the pointer to the trailer
    const DListNode<T> *getAfterLast() const { return &trailer; }
    // return if the list is empty
    bool isEmpty() const { return header.next == &trailer; }
    T first() const; // return the first object
    T last() const; // return the last object
    void insertFirst(T newobj); // insert to the first of the list
    T removeFirst(); // remove the first node
    void insertLast(T newobj); // insert to the last of the list
    T removeLast(); // remove the last node
    void insertAfter(DListNode<T> &p, T newobj);
    void insertBefore(DListNode<T> &p, T newobj);
    T removeAfter(DListNode<T> &p);
    T removeBefore(DListNode<T> &p);
    T min();
};

// output operator
template<typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);
// return the list length
template<typename T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll);

// queue
template<typename T>
class MinQueue{
private:
    int length = 0;
    DoublyLinkedList<T> dll;
public:
    void enqueue(T newobj);
    T dequeue();
    int size();
    bool isEmpty();
    T min();
    void print();
};

///////////////////////////////////////////////////
//Definitions
///////////////////////////////////////////////////

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
    explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

///////////////////////////////////////////////////
//Queue
///////////////////////////////////////////////////
template<typename T>
void MinQueue<T>::enqueue(T newobj){
    dll.insertLast(newobj);
    length++;
}

template<typename T>
T MinQueue<T>::dequeue(){
    length--;
    return dll.removeFirst();
}

template<typename T>
int MinQueue<T>::size(){
    return length;
}

template<typename T>
bool MinQueue<T>::isEmpty(){
    return dll.isEmpty();
}

template<typename T>
T MinQueue<T>::min(){
    return dll.min();
}

template<typename T>
void MinQueue<T>::print(){
    cout << dll << endl << endl;
}

///////////////////////////////////////////////////
//DoublyLinkedList
///////////////////////////////////////////////////
// copy constructor
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
    // Initialize the list
    header.next = &trailer; trailer.prev = &header;
    DListNode<T> *curr = dll.header.next;
    while (curr != &dll.trailer){
        insertLast(curr->obj);
        curr = curr->next;
    }
}

// assignment operator
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
    if (!isEmpty()){this->~DoublyLinkedList();}
    new(this) DoublyLinkedList(dll);
    return *this;
}

// insert the new object as the first one
template<typename T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{
    DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

// insert the new object as the last one
template<typename T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
    DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

// remove the first object from the list
template<typename T>
T DoublyLinkedList<T>::removeFirst()
{
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    DListNode<T> *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    T obj = node->obj;
    delete node;
    return obj;
}

// remove the last object from the list
template<typename T>
T DoublyLinkedList<T>::removeLast()
{
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    DListNode<T> *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    T obj = node->obj;
    delete node;
    return obj;
}

// destructor
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    DListNode<T> *prev_node, *node = header.next;
    while (node != &trailer) {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
}

// return the first object
template<typename T>
T DoublyLinkedList<T>::first() const
{
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    return header.next->obj;
}

// return the last object
template<typename T>
T DoublyLinkedList<T>::last() const
{
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    return trailer.prev->obj;
}

// insert the new object after the node p
template<typename T>
void DoublyLinkedList<T>::insertAfter(DListNode<T> &p, T newobj)
{
    DListNode<T> *curr = header.next;
    while (curr->obj != p.obj && curr != &trailer){
        curr = curr->next;
    }
    if (curr == &trailer)
        throw EmptyDLinkedListException("Could Not Find Node");
    DListNode<T> *temp = curr->next;
    DListNode<T> *newNode = new DListNode<T>(newobj, curr, temp);
    curr->next = newNode;
    temp->prev = newNode;
}

// insert the new object before the node p
template<typename T>
void DoublyLinkedList<T>::insertBefore(DListNode<T> &p, T newobj)
{
    DListNode<T> *curr = header.next;
    while (curr->obj != p.obj && curr != &trailer) {
        curr = curr->next;
    }
    if (curr == &trailer)
        throw EmptyDLinkedListException("Could Not Find Node");
    DListNode<T> *temp = curr->prev;
    DListNode<T> *newNode = new DListNode<T>(newobj, temp, curr);
    curr->prev = newNode;
    temp->next = newNode;
}

// remove the node after the node p
template<typename T>
T DoublyLinkedList<T>::removeAfter(DListNode<T> &p)
{
    DListNode<T> *curr = header.next;
    while (curr->obj != p.obj && curr != &trailer) {
        curr = curr->next;
    }
    if (curr == &trailer)
        throw EmptyDLinkedListException("Could Not Find Node");
    DListNode<T> *temp = curr->next;
    curr->next = temp->next;
    temp->next->prev = curr;
    T obj = temp->obj;
    delete temp;
    return obj;
}

// remove the node before the node p
template<typename T>
T DoublyLinkedList<T>::removeBefore(DListNode<T> &p)
{
    DListNode<T> *curr = header.next;
    while (curr->obj != p.obj && curr != &trailer) {
        curr = curr->next;
    }
    if (curr == &trailer)
        throw EmptyDLinkedListException("Could Not Find Node");
    DListNode<T> *temp = curr->prev;
    curr->prev = temp->prev;
    temp->prev->next = curr;
    T obj = temp->obj;
    delete temp;
    return obj;
}

template<typename T>
T DoublyLinkedList<T>::min(){
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    DListNode<T> *curr = header.next;
    T min = curr->obj;
    while (curr != trailer.prev){
        curr = curr->next;
        if (curr->obj < min)
            min = curr->obj;
    }
    return min;
}

// return the list length
template<typename T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll)
{
    DListNode<T> *current = dll.getFirst();
    int count = 0;
    while (current != dll.getAfterLast()){
        count++;
        current = current->next;
    }
    return count;
}

// output operator
template<typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
    DListNode<T> *curr = dll.getFirst();
    while (curr != dll.getAfterLast()){
        out << curr->obj << " ";
        curr = curr->next;
    }
    return out;
}

