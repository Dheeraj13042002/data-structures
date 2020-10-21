#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node* next;
    Node* prev;
    Node(){next = nullptr; prev = nullptr;}
};

Node* new_node(int data){
    Node* node = new Node;
    node->data = data;
    return node;
}

//Node* partition(Node* head, Node* start, Node* end){
//    Node* index = head;
//    Node* current = start;
//    while(current!=end->next){
//        if(current->data<end->data && current!=head){
//            if(index==head){
//                index->next = current->next;
//                current->next->prev = index;
//                current->next = index;
//                current->prev = nullptr;
//                head = current;
//            }
//        }
//    }
//}


void swap ( int* a, int* b ) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}


Node* partition(Node *start, Node *end)
{
    int pivot = end->data;
    Node *i = start->prev;

    for (Node *j = start; j != end; j = j->next)
    {
        if (j->data <= pivot)
        {
            i = (i == nullptr)? start : i->next;
            swap(&(i->data), &(j->data));
        }
    }

    i = (i == nullptr)? start : i->next;
    swap(&(i->data), &(end->data));
    return i;
}

void quickSort(Node* low, Node *high)
{
    if (high != nullptr && low != high && low != high->next)
    {
        Node *p = partition(low, high);
        quickSort(low, p->prev);
        quickSort(p->next, high);
    }

}


void display(Node *curr)
{
    while (curr!=nullptr)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}


void push(Node** head_ref, int new_data)
{
    Node* new_node = new Node;  
    new_node->data = new_data;
    new_node->prev = nullptr;
    new_node->next = (*head_ref);
    if ((*head_ref) != nullptr) 
        (*head_ref)->prev = new_node;
    (*head_ref) = new_node;
}


int main()
{
    Node *head = nullptr;
    push(&head, 7);
    push(&head, 25);
    push(&head, 6);
    push(&head, 4);
    push(&head, 25);
    cout << "Linked List before sorting \n";
    display(head);
    Node* last = head;
    while(last->next!=nullptr)
        last = last->next;
    quickSort(head, last);
    cout << "Linked List after sorting \n";
    display(head);
    return 0;
}