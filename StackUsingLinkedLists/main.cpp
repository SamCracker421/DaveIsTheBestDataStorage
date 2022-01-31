#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

//Class Declarations

template <typename T>
class Node{
public:
    Node* next;
    T value;
};

template <typename T>
class Stack {
private:
    int length;
    Node<T> head;
public:
    Stack();
    void push(T val);
    T pop();
    T top();
    int size();
    bool isEmpty();
};

//Method Declaration

template <typename T>
Stack<T>::Stack(){
    length=0;
    head.next=nullptr;
};

template <typename T>
T Stack<T>::pop(){
    length-=1;
    T cheese= head.next->value;
    head.next=head.next->next;
    delete head.next;
    return cheese;
};

template <typename T>
T Stack<T>::top(){
    return head.next->value;
};

template <typename T>
void Stack<T>::push(T val){\
    length+=1;
    Node<T>* newnode=new Node<T>;
    newnode->value=val;
    newnode->next=head.next;
    head.next=newnode;
}
template <typename T>
int Stack<T>::size(){
    return length;
}
template <typename T>
bool Stack<T>::isEmpty(){
    return length==0;
}

//Testing

TEST(TESTSTACK,IsItPointing){
    Stack<int> s;
    s.push(25);
    s.push(35);
    s.push(125);
    ASSERT_EQ(s.top(),125);
}

TEST(TESTSTACK,Popping){
    Stack<int> s;
    s.push(25);
    s.push(35);
    s.push(125);
    s.pop();
    ASSERT_EQ(s.top(),35);
}

TEST(TESTSTACK,RightSize){
    Stack<int> s;
    s.push(25);
    s.push(35);
    s.push(125);
    s.pop();
    ASSERT_EQ(s.size(),2);
}
TEST(TESTSTACK,IsItEmpty){
    Stack<int> s;
    ASSERT_EQ(s.isEmpty(),true);
}

//int main

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


