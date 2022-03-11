#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <cmath>
#include "gtest/gtest.h"

using namespace std;
template <typename T>
class PriorityQueue{
    int sizzle=0;
    vector<T> values;
    public:
   void insert(T value);
   T remove();
   bool isEmpty();
   int size();
};
template <typename T>
bool PriorityQueue<T>::isEmpty(){
                        if(size()>=1){
                            return false;
                        }
                        else{
                            return true;
                        }
}
template <typename T>
int PriorityQueue<T>::size(){
    return sizzle;
}
template <typename T>
void PriorityQueue<T>::insert(T value){
    values.push_back(value);
    int place=size()-1;
    while(values[place]>values[floor((place-1)/2)]){
        T cheese=values[floor((place-1)/2)];
        values[floor((place-1)/2)]=values[place];
         values[place]=cheese;
         place=floor((place-1)/2);
    }
    sizzle+=1;
}
template <typename T>
T PriorityQueue<T>::remove(){
    int place=0;
    T potato=values[0];
    values[place]=values[size()-1];
    values.erase(values.end()-1);
    sizzle-=1;
    while(place<size()-1){
        int LeftIndex=(place*2)+1;
        int RightIndex=(place*2)+2;
        if(LeftIndex<=size()-1 && RightIndex<=size()-1){
            if(values[LeftIndex]>values[RightIndex]){
                if(values[LeftIndex]>values[place]){
                    swap(values[LeftIndex],values[place]);
                    place=LeftIndex;
                }
                else{
                    break;
                }
            }
            else{
                if(values[place]<values[RightIndex]){
                    swap(values[RightIndex],values[place]);
                    place=RightIndex;
                }
                else{
                    break;
                }
            }
        }
        else if(LeftIndex<=size()-1 && RightIndex>size()-1){
                if(values[LeftIndex]>values[place]){
                    swap(values[LeftIndex],values[place]);
                    place=LeftIndex;
                }
                else{
                    break;
                }
        }
        else if(LeftIndex>size()-1 && RightIndex<=size()-1){
            if(values[RightIndex]>values[place]){
                swap(values[RightIndex],values[place]);
                place=LeftIndex;
            }
            else{
                break;
            }
        }
        else if(RightIndex>=size()-1 && LeftIndex>=size()-1){
            break;
        }
    }
    return potato;
}

//int main
TEST(PriorityQueue,size){
    PriorityQueue<int> cheese;
    ASSERT_EQ(cheese.isEmpty(),true);
}
TEST(PriorityQueue,sorty){
    PriorityQueue<int> cheese;
    cheese.insert(100);
     cheese.insert(10);
      cheese.insert(500);
       cheese.insert(6);
        cheese.insert(30);
        cheese.insert(1500);
        cheese.insert(200);
        cheese.insert(20000);
        cheese.insert(2);
        cheese.remove();
        cheese.remove();
        ASSERT_EQ(cheese.remove(),500);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


