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
class Deque {
private:
    int length;
    Node<T> head;
public:
    Deque();
    void push_back(T val);
    void push_front(T val);
    T pop_back();
    T pop_front();
    T top();
    T bottom();
    int size();
    bool isEmpty();
};

//Method Declaration

template <typename T>
Deque<T>::Deque(){
    length=0;
    head.next=nullptr;
};

template <typename T>
T Deque<T>::pop_front(){
    length-=1;
    T cheese= head.next->value;
    head.next=head.next->next;
    delete head.next;
    return cheese;
};

template <typename T>
T Deque<T>::top(){
    return head.next->value;
};

template <typename T>
T Deque<T>::bottom(){
    Node<T>* cheese;
    cheese=head.next;
    while(cheese->next!=nullptr){
        cheese=cheese->next;
    }
    return cheese->value;
};

template <typename T>
void Deque<T>::push_front(T val){\
    length+=1;
    Node<T>* newnode=new Node<T>;
    newnode->value=val;
    newnode->next=head.next;
    head.next=newnode;
}
template <typename T>
void Deque<T>::push_back(T val){
    if(head.next==nullptr){
    Node<T>* newnode=new Node<T>;
    newnode->value=val;
    newnode->next=head.next;
    head.next=newnode;
    }
    else{
        if(head.next->next!=nullptr){
            Node<T>* pizza;
            pizza=head.next;
            Node<T>* newnode=new Node<T>;
            while(pizza->next!=nullptr){
                pizza=pizza->next;
            }
            pizza->next=newnode;
            newnode->value=val;
            newnode->next=nullptr;
        }
        else{
            push_front(val);
        }
    }
}
template <typename T>
T Deque<T>::pop_back(){
    Node<T>* cheese;
    cheese=head.next;
    while(cheese->next!=nullptr){
        cheese=cheese->next;
    }

}

template <typename T>
int Deque<T>::size(){
    return length;
}
template <typename T>
bool Deque<T>::isEmpty(){
    return length==0;
}

//Testing
TEST(TESTDeque,PushingBack){
    Deque<int> s;
    s.push_back(12);
    s.push_front(15);
    s.push_back(35);
    ASSERT_EQ(s.bottom(),35);
    ASSERT_EQ(s.top(),15);
}

TEST(TESTDeque,BottomWorking){
    Deque<int> s;
    s.push_front(25);
    s.push_front(35);
    s.push_front(125);
    ASSERT_EQ(s.bottom(),25);
}
TEST(TESTDeque,PoppingFromBack){
    Deque<int> s;
    s.push_front(25);
    s.push_front(35);
    s.push_front(125);
    s.pop_back();
    ASSERT_EQ(s.bottom(),35);
}

TEST(TESTDeque,IsItPointing){
    Deque<int> s;
    s.push_front(25);
    s.push_front(35);
    s.push_front(125);
    ASSERT_EQ(s.top(),125);
}

TEST(TESTDeque,Popping){
    Deque<int> s;
    s.push_front(25);
    s.push_front(35);
    s.push_front(125);
    s.pop_front();
    ASSERT_EQ(s.top(),35);
}

TEST(TESTDeque,RightSize){
    Deque<int> s;
    s.push_front(25);
    s.push_front(35);
    s.push_front(125);
    s.pop_front();
    ASSERT_EQ(s.size(),2);
}
TEST(TESTDeque,IsItEmpty){
    Deque<int> s;
    ASSERT_EQ(s.isEmpty(),true);
}

//int main

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


