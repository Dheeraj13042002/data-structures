#include<iostream>
using namespace std;

class Queue{
private:
    int *a;
    int size;
    int top;
    int rear;
public:
    Queue(int);
    void enqueue(int);
    int dequeue();
    bool isEmpty();
    bool isFull();
    void display();
    ~Queue();
};

Queue::Queue(int s):
size{s}{
    a = new int[size];
    top = -1;
    rear = -1;
}

void Queue::enqueue(int data) {
    if(isFull())
    {
        cout << "Queue overflow" << endl;
        return;
    }
    a[++rear] = data;
}

int Queue::dequeue() {
    if(isEmpty()){
        cout << "Queue underflow" << endl;
        return -1;
    }
    int *x = &a[++top];
    int y = *x;
    *x = -1;
    return y;
}

bool Queue::isEmpty() {
    return top == rear;
}

bool Queue::isFull() {
    return rear==size-1;
}

void Queue::display() {
    if(isEmpty()){
        cout << "Queue is empty" << endl;
        return;
    }
    for(int i{top+1}; i<=rear; ++i){
        cout << a[i] << " ";
    }
    cout << endl;
}

Queue::~Queue() {
    delete [] a;
}

int main(){
    Queue q(7);
    q.enqueue(12);
    q.enqueue(10);
    q.enqueue(13);
    q.enqueue(11);
    q.enqueue(34);
    q.enqueue(22);
    q.display();
    cout << q.dequeue() << endl;
    q.dequeue();
    q.dequeue();
    q.display();
}
