#include <iostream>
using namespace std;

class Node{
public:
    int data;
    int priority;
    Node* next;
};

Node* new_node(int temp_data, int temp_pri){
    Node* temp = new Node;
    temp->data = temp_data;
    temp->priority = temp_pri;
    temp->next = nullptr;
    return temp;
}

void push(Node** head_ref, int d, int p){
    Node* temp = new_node(d, p);
    if(temp==nullptr){
        cout << "Queue is full." << endl;
        return;
    }
    if(*head_ref==nullptr){
        *head_ref = temp;
        return;
    }
    Node* current = *head_ref;
    Node* prev = current;
    while(current!=nullptr && current->priority<=temp->priority){
        prev = current;
        current = current->next;
    }
    temp->next = current;
    prev->next = temp;
}

void pop(Node** head_ref){
    if(*head_ref==nullptr){
        cout << "queue is empty" << endl;
        return;
    }
    Node* temp = *head_ref;
    *head_ref = (*head_ref)->next;
    delete temp;
}

void display(Node** head_ref){
    if(*head_ref==nullptr)
        return;
    Node* current = *head_ref;
    while(current!=nullptr){
        cout << "priority: " << current->priority << " " << "data: " << current->data << endl;
        current = current->next;
    }
}

int main(){
    Node* queue = nullptr;
    push(&queue, 23, 1);
    push(&queue, 11, 1);
    push(&queue, 12, 1);
    push(&queue, 34, 2);
    push(&queue, 5, 2);
    push(&queue, 65, 2);
    push(&queue, 22, 3);
    push(&queue, 13, 1);
    push(&queue, 66, 2);
    push(&queue, 72, 2);
    push(&queue, 18, 3);
    push(&queue, 27, 3);

    display(&queue);
    cout << "===========================" << endl;
    pop(&queue);
    pop(&queue);
    display(&queue);
    return 0;
}