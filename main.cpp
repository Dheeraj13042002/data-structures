#include <iostream>
#include <vector>
using namespace std;

class Node{
public:
    int data;
    Node *next;
};

Node* new_node(int temp_data){
    Node* p = new Node;
    p->data = temp_data;
    p->next = nullptr;
    return p;
}

void push(Node** head_ref, Node* node){
    if(*head_ref == nullptr){
        *head_ref = node;
    }
    else{
        node->next = *head_ref;
        *head_ref = node;
    }
}

void display(Node** head_ref){
    Node* current = *head_ref;
    while(current->next!=nullptr){
        cout << current->data << "->";
        current = current->next;
    }
    cout << current->data;
    cout << "\n";
}

void rDisplay(Node** head_ref){
    if(*head_ref == nullptr)
        return;

    Node *current = *head_ref;
    if(current->next == nullptr)
        cout << current->data << " ";
    else{
        cout << current->data << " ";
        rDisplay(&(current->next));
    }
}

int NodeCount(Node** head_ref){
    if(*head_ref == nullptr)
        return 0;

    int res {0};
    Node* current = *head_ref;
    while(current->next!=nullptr){
        ++res;
        current = current->next;
    }
    return res+1;
}

int SumOfAll(Node** head_ref){
    if(*head_ref==nullptr){
        return 0;
    }

    int res{0};
    Node* current = *head_ref;
    while(current->next!=nullptr){
        res += current->data;
        current = current->next;
    }
    res += current->data;
    return res;
}

int FindMax(Node** head_ref){
    if(*head_ref == nullptr){
        return 0;
    }
    
    int max {0};
    Node* current = *head_ref;
    while(current->next != nullptr){
        if(current->data > max)
            max = current->data;
        current = current->next;
    }
    if(current->data > max)
        max = current->data;
    return max;
}

bool LinearSearch(Node** head_ref, int data){
    Node* current = *head_ref;
    while(current!=nullptr){
        if(current->data == data)
            return true;
        current = current->next;
    }
    return false;
}

void InsertAtLast(Node** head_ref, int data){
    Node* node = new_node(data);
    if(*head_ref == nullptr){
        *head_ref = node;
    }
    else {
        Node *current = *head_ref;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
}

void SortedInsert(Node** head_ref, int data){
    Node* node = new_node(data);
    Node* current = *head_ref;
    while(current->next!=nullptr && current->next->data<data){
        current = current->next;
    }
    node->next = current->next;
    current->next = node;
}

void DeleteNode(Node** head_ref, int key){
    if((*head_ref)->data == key){
        Node* t = *head_ref;
        *head_ref = (*head_ref) -> next;
        delete t;
        return;
    }
    Node* current = (*head_ref)->next;
    Node* temp = *head_ref;
    while(current != nullptr){
        if(current->data == key){
            temp->next = current->next;
            current->next = nullptr;
            delete current;
            return;
        }
        temp = current;
        current = current->next;
    }

}

bool SortedCheck(Node** head_ref){
    Node* current = *head_ref;
    while(current->next!=nullptr && current->data<current->next->data){
        current = current->next;
    }
    return current->next == nullptr;
}

Node* reverse(Node** head_ref){
    Node* res = nullptr;
    Node* current = *head_ref;
    while(current!=nullptr){
        Node* temp = current;
        current = current->next;
        temp->next = nullptr;
        if(res == nullptr){
            res = temp;
        }
        else{
                temp->next = res;
                res = temp;
        }
    }
    return res;
}

Node* concatenate(Node** head_ref, Node** head_ref1){
    Node* res = *head_ref;
    Node* current = *head_ref;
    while(current->next!=nullptr){
        current = current->next;
    }
    current->next = *head_ref1;
    return res;
}

Node* merge(Node** head_ref1, Node** head_ref2){
    Node* res = nullptr;
    Node* c1 = *head_ref1;
    Node* c2 = *head_ref2;
    while(c1!= nullptr && c2!= nullptr){
        if(c1->data < c2->data){
            InsertAtLast(&res, c1->data);
            c1 = c1->next;
        }
        else if (c1->data > c2->data){
            InsertAtLast(&res, c2->data);
            c2 = c2->next;
        }
        else{
            InsertAtLast(&res, c2->data);
            c1 = c1->next;
            c2 = c2->next;
        }
    }

    while(c1!=nullptr){
        InsertAtLast(&res, c1->data);
        c1 = c1->next;
    }

    while(c2!=nullptr){
        InsertAtLast(&res, c2->data);
        c2 = c2->next;
    }

    return res;
}

bool checkLoop(Node** head_ref){
    Node* fast_ptr = (*head_ref)->next;
    Node* slow_ptr = *head_ref;
    while(fast_ptr->next!=nullptr && fast_ptr->next->next!=nullptr){
        if(fast_ptr==slow_ptr)
            return true;
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
    }
    return false;
}



void Insert(Node** head_ref, int pos, int data){
    Node* node = new_node(data);
    if(*head_ref == nullptr){
        *head_ref = node;
    }
    else {
        int count{0};
        Node *current = *head_ref;
        Node *prev = nullptr;
        while (current != nullptr) {
            ++count;
            if (pos == count) {
                node->next = prev->next;
                prev->next = node;
            }
            prev = current;
            current = current->next;
        }
    }
}

void reorderList(Node* head) {
    vector<Node*> nodes;
    Node* new_head = nullptr;
    Node* slow = head;
    Node* fast = head;
    while(fast->next!=nullptr&&fast->next->next!=nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    if(fast->next!=nullptr)
        slow = slow->next;
    Node* temp = slow;
    while(slow!=nullptr){
        nodes.push_back(slow);
        slow = slow->next;
    }
    Node* curr = head;
    Node* last = nullptr;
    while(curr!=temp&&!nodes.empty()){
        if(new_head==nullptr){
            new_head = curr;
            curr = curr->next;
            new_head->next = nodes.back();
            nodes.pop_back();
            last = new_head->next;
        }else{
            last->next = curr;
            last = curr;
            curr = curr->next;
            last->next = nodes.back();
            last = last->next;
            nodes.pop_back();
        }
    }
    if(!nodes.empty()){
        last->next = nodes.back();
        nodes.pop_back();
        last->next->next = nullptr;
    }else{
        last->next = nullptr;
    }
    head = new_head;
}


int main(){
//    Node* head1 = nullptr;
//    push(&head1, new_node(2));
//    push(&head1, new_node(4));
//    push(&head1, new_node(9));
//    push(&head1, new_node(13));
//    push(&head1, new_node(16));
//    push(&head1, new_node(23));
//    push(&head1, new_node(34));
//    Node* head2 = nullptr;
//    push(&head2, new_node(3));
//    push(&head2, new_node(6));
//    push(&head2, new_node(10));
//    push(&head2, new_node(14));
//    push(&head2, new_node(19));
//    push(&head2, new_node(27));
//    push(&head2, new_node(42));
//
//    head1 = reverse(&head1);
//    head2 = reverse(&head2);
//    display(&head1);
//    display(&head2);
//
//    InsertAtLast(&head1, 39);
//    display(&head1);
//    SortedInsert(&head1, 38);
//    display(&head1);
//    DeleteNode(&head1, 34);
//    display(&head1);
//    bool flag = SortedCheck(&head1);
//    cout << boolalpha;
//    cout << flag << endl;
//    head1 = merge(&head1, &head2);
//    display(&head1);
//    bool flag1 = checkLoop(&head2);
//    cout << flag1 << endl;
//    Insert(&head2, 19, 17);
//    display(&head2);
    Node* head = nullptr;
//    push(&head, new_node(9));
//    push(&head, new_node(8));
//    push(&head, new_node(7));
//    push(&head, new_node(6));
//    push(&head, new_node(5));
//    push(&head, new_node(4));
    push(&head, new_node(3));
    push(&head, new_node(2));
    push(&head, new_node(1));
    reorderList(head);
    display(&head);

    return 0;

}