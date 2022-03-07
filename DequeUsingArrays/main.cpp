#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

template <typename T>
//Class Declaration
class Deque {
private:
    T* values;
    int length;
    int numvalues;
    int start;
    int end;
public:
    Deque();
    void push_front(T val);
    T pop_front();
    T top();
    T bottom();
    T pop_back();
    void push_back(T val);
    int size();
    bool isEmpty();
};
//methods
template <typename T>
Deque<T>::Deque(){
    length=10;
    values = new T[length];
    start=0;
    end=9;
    numvalues=0;
}
template <typename T>
void Deque<T>::push_front(T val){
    if(start!=end){
        values[start]=val;
        start=start+1;
        numvalues+=1;
     }
    else{
        T* cheese = new T[length+10];
        for(int x=length-1; x>end;x--){
            cheese[x+10]=values[x];
        }
        for(int x=0; x<start;x++){
            cheese[x]=values[x];
        }
        values=cheese;
        push_front(val);
    }
}
template <typename T>
T Deque<T>::pop_front(){
    T cheese=values[start-1];
    values[start-1]=NULL;
    start=start-1;
    return cheese;
}
template <typename T>
T Deque<T>::top(){
    return values[start-1];
}
template <typename T>
T Deque<T>::bottom(){
    return values[end+1];
}
template <typename T>
T Deque<T>::pop_back(){
    T cheese=values[length-1];
    for(int x=length-1; x>end;x--){
        values[x]=values[x-1];
    }
    values[end+1]=NULL;
    end+=1;
    numvalues-=1;
    return cheese;
}
template <typename T>
void Deque<T>::push_back(T val){
    if(end!=start){
        values[end]=val;
        end-=1;
        numvalues+=1;
     }
    else{
        T* cheese = new T[length+10];
        for(int x=length-1; x>end;x--){
            cheese[x+10]=values[x];
        }
        for(int x=0; x<start;x++){
            cheese[x]=values[x];
        }
        values=cheese;
        push_back(val);
    }
}
template <typename T>
int Deque<T>::size(){
    return numvalues;
}
template <typename T>
bool Deque<T>::isEmpty(){
    return numvalues==0;
}
//Test Section
TEST(DequeTests,PushFrontTest){
    Deque<int> t;
    t.push_front(10);
    t.push_front(15);
    ASSERT_EQ(t.top(),15);
}
TEST(DequeTests,PushBackTest){
    Deque<int> t;
    t.push_front(10);
    t.push_back(25);
    ASSERT_EQ(t.bottom(),25);
}
TEST(DequeTests,PopFront){
    Deque<int> t;
    t.push_front(10);
    t.push_front(25);
    t.pop_front();
    ASSERT_EQ(t.top(),10);
}
TEST(DequeTests,PopBack){
    Deque<int> t;
    t.push_back(16);
    t.push_back(20);
    t.push_back(14);
    t.pop_back();
    t.pop_back();
    ASSERT_EQ(t.bottom(),14);
    ASSERT_EQ(t.size(),1);
}
TEST(DequeTests,Sizeing){
    Deque<int> t;
    t.push_back(16);
    t.push_back(20);
    t.push_back(14);
    t.push_back(19);
    t.push_back(20);
    t.push_back(102);
    t.push_back(106);
    t.push_back(202);
    t.push_back(134);
    t.push_back(160);
    t.push_back(210);
    t.push_back(114);
    ASSERT_EQ(t.bottom(),114);
}
//int main

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


