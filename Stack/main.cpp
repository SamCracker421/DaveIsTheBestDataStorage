#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

template <typename T>
//Class Declaration
class Stack {
private:
    T* values;
    int length;
public:
    Stack();
    void push(T val); //test passed
    T pop();    //test passed
    T top();    //test passed
    int size(); //test passed
    bool isEmpty(); //testpassed
};

template <typename T>
Stack<T>::Stack(){
    length=0;
    values = new T[length];
}

//Methods
template <typename T>
void Stack<T>::push(T val){
    T* newvalues = new T[length+1];
    for(int x=0; x<length+1;x++){
        newvalues[length]=values[length];
    }
    length+=1;
    newvalues[length]=val;
    delete [] values;
    values = newvalues;
}


template <typename T>
T Stack<T>::pop(){
    T safety=values[length];
    T* newvalues = new T[length-1];
    for(int x=0;x<length;x++){
        newvalues[length]=values[length];
    }
    length-=1;
    delete [] values;
    values=newvalues;
    return safety;

}


template <typename T>
T Stack<T>::top(){
    return values[length];
}


template <typename T>
int Stack<T>::size(){
return length;
}


template <typename T>
bool Stack<T>::isEmpty(){
 if(length==0){
     return true;
 }
 else if(length!=0){
     return false;
 }
}

//Test Section

TEST(TESTSTACK,IsTopTrue){
    Stack<int> s;
s.push(100);
s.push(99);
    ASSERT_EQ(s.top(),99);
}


TEST(TESTSTACK,DidStackDecrease){
    Stack<int> s;
    s.push(5);
    s.push(10);
    s.pop();
    ASSERT_EQ(s.size(),1);
}

TEST(TESTSTACK,DidStackIncrease){
    Stack<double> s;
    s.push(4.1);
    ASSERT_EQ(s.size(),1);
}


TEST(TESTSTACK,IsStackEmpty){
    Stack<double> s;
    ASSERT_EQ(s.size(),0);
}

TEST(TESTSTACK,DoesIsEmptyWork){
    Stack<double> s;
    ASSERT_EQ(s.isEmpty(),true);
}

//int main

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


