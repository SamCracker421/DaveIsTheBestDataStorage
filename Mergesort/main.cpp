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
    int r=0;
    int l=0;
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
            if(r<right.size()){
            if(l<left.size()){
                if(left[l]<right[r]){
                finale.push_back(left[l]);
                l++;
                }
                else{
                    finale.push_back(right[r]);
                    r++;
                }
            }
            else{
                finale.push_back(right[r]);
                r++;
            }
            }
            else {
                if(l<left.size()){
                    finale.push_back(left[l]);
                    l++;
                }
                else{
                    values=finale;
                    break;
                }
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
    vector<int> cheese={1,2,3,6,3,6};
    mergeSort(cheese);
    ASSERT_EQ(cheese,vector<int> ({1,2,3,3,6,6}));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


