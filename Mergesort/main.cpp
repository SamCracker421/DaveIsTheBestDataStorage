#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <cmath>
#include "gtest/gtest.h"

using namespace std;
template <typename T>
void mergeSort(vector<T>& values){
    vector<T> left;
    vector<T> right;
    vector<T> finale;
    int split=values.size()/2;
    if(values.size()>2){
        for(int x=0; x<split;x++){
            left.push_back(values[x]);
        }
        for(int x=split;x<values.size();x++){
            right.push_back(values[x]);
        }
        mergeSort(left);
        mergeSort(right);
        while(true){
            if(right.size()!=0 || left.size()!=0){
            if(left[0]<right[0]){
                finale.push_back(left[0]);
                left.erase(left.begin());
            }
            else{
                finale.push_back(right[0]);
                right.erase(right.begin());
            }
            }
            if(right.size()==0 && left.size()>0){
                for(int x =0; x<left.size();x++){
                    finale.push_back(left[x]);
                }
            }
            else if(right.size()>0 && left.size()==0){
                for(int x=0;x<right.size();x++){
                    finale.push_back(right[x]);
                }
            }
            if(right.size()==0 && left.size()==0){
                values=finale;
                break;
            }
        }
    }
    else if(values.size()==2){
        if(values[0]>values[1]){
            swap(values[0],values[1]);
        }
    }
}
TEST(MergeSort,doesitsort){
    vector<int> cheese={};
    mergeSort(cheese);
    ASSERT_EQ(cheese,vector<int> ({}));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


