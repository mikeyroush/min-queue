#include "MinQueue.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

int main () {
    // Construct a queue
    cout << "Create a new queue" << endl;
    MinQueue<int> q;
    cout << "isEmpty: " << q.isEmpty() << endl;
    cout << "queue: "; q.print();
    
    // Enqueue 10 nodes
    cout << "Enqueue 10 nodes with values 10,20...100" << endl;
    for (int i = 10; i <= 100; i+=10){
        q.enqueue(i);
    }
    cout << "queue: "; q.print();
    
    // Dequeue 1st node
    cout << "Dequeue 1st node" << endl;
    cout << "dequeued value: " << q.dequeue() << endl;
    cout << "queue: "; q.print();
    
    // Enqueue a new node of value 1 and return min
    cout << "Enque a value of 1 and return min value and size of queue" << endl;
    q.enqueue(1);
    cout << "queue: "; q.print();
    cout << "min: " << q.min() << endl;
    cout << "size: " << q.size() << endl << endl;
}
