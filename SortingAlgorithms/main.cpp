#include <iostream>
#include "graphics.h"
#include <thread>
#include <chrono>

using namespace std;
using namespace mssm;
using namespace this_thread;

#pragma GCC diagnostic ignored "-Wsign-compare"

void drawthingy(vector<int> pp,Graphics& g){
for(int x=0; x<pp.size();x++){
    Vec2d cheese={x,0};
    g.rect(cheese,1,pp[x],RED,RED);
}
}
void Isort(vector<int>& pp, Graphics& g){
    drawthingy(pp,g);
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
        Isort(low,g);
        Isort(high,g);
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



int main()
{
    srand(time(NULL));
    Graphics g("Test", 1024,1024);
     vector<int> cheese;
 for(int x=0;x<1024;x++){
cheese.push_back(rand()%1024);
 }
 Isort(cheese,g);
}
