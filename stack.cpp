//
// Created by shourya gupta on 10/4/2020.
//

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

template <class T>
class Stack{
public:
    int size;
    int top;
    T *s;
    explicit Stack(int temp);
    void push(T x);
    T pop();
    bool isFull();
    bool isEmpty();
    T peek(int index);
    T stackTop();
    void display();
    ~Stack();
};


template <class T>
Stack<T>::Stack(int temp):
size{temp}, top{-1}{
    s = new T[size];
}


template <class T>
void Stack<T>::push(T x) {
    if(isFull()){
        cout << "Stack Overflow" << endl;
    }
    else{
        top++;
        s[top] = x;
    }
}


template <class T>
T Stack<T>::pop() {
    T x = -1;
    if(isEmpty()){
        cout << "Stack Underflow" << endl;
    }
    else{
        x = s[top];
        top--;
    }
    return x;
}


template <class T>
bool Stack<T>::isFull() {
    return top == size - 1;
}


template <class T>
bool Stack<T>::isEmpty() {
    return top == -1;
}


template <class T>
T Stack<T>::peek(int index) {
    if(top - index + 1 < 0){
        return -1;
    }

    return s[top - index + 1];
}


template <class T>
T Stack<T>::stackTop() {
    if(isEmpty())
        return -1;
    return s[top];
}


template <class T>
void Stack<T>::display() {
    if(isEmpty())
        cout << "Stack is empty." << endl;
    else{
        for(int i {top}; i >=0; --i){
            cout << s[i] << " ";
        }
        cout << "\n";
    }
}

template <class T>
Stack<T>::~Stack() {
    delete [] s;
}

bool paranthesisMatching(char exp[]){
    Stack<char> st(100);
    for(int i {0}; exp[i]!='\0'; ++i){
        if(exp[i]=='(' || exp[i]=='{' || exp[i]=='['){
            st.push(exp[i]);
        }
        else if (exp[i]==')' && st.stackTop()=='('){
            if(st.isEmpty())
                return false;
            else
                st.pop();
        }else if (exp[i]=='}' && st.stackTop()=='{'){
            if(st.isEmpty())
                return false;
            else
                st.pop();
        }else if (exp[i]==']' && st.stackTop()=='['){
            if(st.isEmpty())
                return false;
            else
                st.pop();
        }
    }
    return st.isEmpty();
}

char* infixToPostfix(char exp[]){
    Stack<char> st(100);
    int precedence[50] = {0};
    precedence[42] = 2;
    precedence[43] = 1;
    precedence[45] = 1;
    precedence[47] = 2;
    char* postfix = new char[100];
    int j {0};
    for(int i {0}; exp[i]!='\0'; ++i){
        if(exp[i]=='+'||exp[i]=='-'||exp[i]=='*'||exp[i]=='/'){
            while(true){
                if(st.isEmpty()){
                    st.push(exp[i]);
                    break;
                }
                else if(precedence[int(st.stackTop())] < precedence[int(exp[i])]){
                    st.push(exp[i]);
                    break;
                }
                else{
                    postfix[j++] = st.pop();
                }
            }
        }else{
            postfix[j++] = exp[i];
        }
    }
    while(!st.isEmpty()){
        postfix[j++] = st.pop();
    }
    postfix[j] = '\0';
    return postfix;
}

int outStackPre(char ch){
    if(ch=='+'||ch=='-')
        return 1;
    if(ch=='/'||ch=='*')
        return 3;
    if(ch=='^')
        return 6;
    if(ch=='(')
        return 7;
    if(ch==')')
        return 0;
    return -1;
}

int inStackPre(char ch){
    if(ch=='+'||ch=='-')
        return 2;
    if(ch=='/'||ch=='*')
        return 4;
    if(ch=='^')
        return 5;
    if(ch=='(')
        return 0;

    return -1;
}

bool isOperand(char ch){
    return !(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '^');
}

char* infixConverter(char exp[]){
    Stack<char> st(100);
    char* postfix = new char[strlen(exp)];
    int j{0};
    int i {0};
    while(exp[i]!='\0'){
        if(isOperand(exp[i])){
            postfix[j++] = exp[i++];
        }
        else{
            if(st.isEmpty()){
                st.push(exp[i++]);
            }
            else if(outStackPre(exp[i]) > inStackPre(st.stackTop())){
                st.push(exp[i++]);
            }
            else{
                if(outStackPre(exp[i]) < inStackPre(st.stackTop())){
                    postfix[j++] = st.pop();
                }
                else if(outStackPre(exp[i]) == inStackPre(st.stackTop())){
                    st.pop();
                    i++;
                }
            }
        }
    }
    while(!st.isEmpty()){
        postfix[j++] = st.pop();
    }
    postfix[j] = '\0';
    return postfix;
}


double convert(int left, int right, char op){
    if(op=='+'){
        return left + right;
    }
    if(op=='-'){
        return left - right;
    }
    if(op=='*'){
        return left * right;
    }
    if(op=='/'){
        return static_cast<double >(left) / static_cast<double>(right);
    }
    if(op=='^'){
        return pow(left, right);
    }
    return 0;
}


double postfixEval(char exp[]){
    Stack<double> st(100);
    for(int i {0}; exp[i]!='\0'; ++i){
        if(isOperand(exp[i])){
            st.push(exp[i] - 48);
        }
        else{
            int right = st.pop();
            int left = st.pop();
            double result = convert(left, right, exp[i]);
            st.push(result);
        }
    }
    return st.stackTop();
}

int main(){
    char exp[] = "a+b*c-d/f+g-h/i";
    char e[] = "((a+b)*c)-d^e^f";
    char* res = infixConverter(e);
    char ex[] = "((2+3)*5)-3^2^2";
    char* expostfix = infixConverter(ex);
    double result = postfixEval(expostfix);
    cout << result << endl;
//    for(int i {0}; res[i]!='\0'; ++i){
//        cout << res[i];
//    }
    cout << '\n';
    return 0;

}
