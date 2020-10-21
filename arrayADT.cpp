//
// Created by shourya gupta on 6/23/2020.
//

#include <iostream>

using namespace std;

class Array{
private:
    int size;
    int length;
    void changeSize(int);
public:
    int* p;
    Array(int s = 0);
    Array(const Array &);
    ~Array();
    int search(int);
    void insert(int, int);
    void append(int);
    void remove();
    void delete_item(int);
    int get(int);
    void set(int, int);
    void display();
    void sort_array();
    int get_size();
};

Array::Array(int s)
: size{s} {
    p = new int[s];
    length = 0;
}

Array::Array(const Array &source) {
    this->size = source.size;
    this->p = new int[size];
    this->length = source.length;
    for (int i {0}; i < source.size; ++i)
    {
        this->p[i] = source.p[i];
    }
}

Array::~Array() {
    delete [] p;
}

void Array::changeSize(int s) {
    if (s < size)
    {
        int *q = new int[s];
        for (int i {0}; i<s; ++i)
        {
            q[i] = p[i];
        }
        size = s;
        delete [] p;
        p = q;
        q = nullptr;
    }
    else {
        int *q = new int[s];
        for (int i {0}; i<size; ++i)
        {
            q[i] = p[i];
        }
        size = s;
        delete [] p;
        p = q;
        q = nullptr;
    }
}

int Array::search(int key) {
    for (int i {0}; i<size; ++i)
    {
        if (p[i] == key)
            return i;
    }
    return 0;
}

void Array::insert(int key, int index) {
    if (index > size - 1 || index < 0){
        cout << index << " does not exist in the array." << endl;
    }
    else {
        changeSize(size + 1);
        for (int i {size - 1}; i > index; --i)
        {
            p[i] = p[i - 1];
        }
        p[index] = key;
    }
}

void Array::append(int key) {
    changeSize(size + 1);
    p[size - 1] = key;
}

void Array::delete_item(int index) {
    if (index > size - 1 || index < 0){
        cout << index << " does not exist in the array." << endl;
    }
    else{
        for (int i {index}; i<size - 1; ++i)
        {
            p[i] = p[i + 1];
        }
        changeSize(size - 1);
    }
}

int Array::get(int index) {
    return p[index];
}

void Array::set(int key, int index) {
    p[index] = key;
}

void Array::display() {
    for (int i {0}; i<size; ++i)
    {
        if (i != size - 1)
        {
            cout << p[i] << ", ";
        } else cout << p[i];
    }
    cout << "\n";
}

void Array::sort_array() {
    for ( int i {0}; i<size; ++i)
    {
        for (int j {i}; j<size; ++j)
        {
            if (p[j] > p[i])
            {
                int temp = p[j];
                p[j] = p[i];
                p[i] = temp;
            }
        }
    }
}

void Array::remove() {
    changeSize(size - 1);
}

int Array::get_size() {
    return size;
}

int main(){
    Array arr(5);
    arr.p[0] = 1;
    arr.p[1] = 2;
    arr.p[2] = 3;
    arr.p[3] = 4;
    arr.p[4] = 5;
    arr.display();
    arr.append(10);
    arr.display();
    int pos = arr.search(4);
    cout << pos << endl;
    arr.delete_item(4);
    arr.display();
    arr.insert(15, 3);
    arr.display();
}
