#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

void Isort(vector<int>& pp){
    vector<int> low;
    vector<int> high;
    vector<int> finale;
    int mid=pp.size()/2;
    if(pp.size()>=3){
        for(int x=0; x<pp.size();x++){
            if(x!=mid){
                if(pp[x]>pp[mid]){
                    high.push_back(pp[x]);
                }
                else{
                    low.push_back(pp[x]);
                }
            }
        }
        Isort(low);
        Isort(high);
        for(int x=0; x<low.size();x++){
            finale.push_back(low[x]);
        }
        finale.push_back(pp[mid]);
        for(int x=0; x<high.size();x++){
            finale.push_back(high[x]);
        }
        pp=finale;
    }
    if(pp.size()==2){
        if(pp[0]>pp[1]){
            swap(pp[0],pp[1]);
        }
    }
}

int main(){
    srand(time(NULL));
        vector<int> cheese;
    for(int x=0;x<10000000;x++){
cheese.push_back(rand()%100000);
    }
    cout<<endl;
    Isort(cheese);
}
