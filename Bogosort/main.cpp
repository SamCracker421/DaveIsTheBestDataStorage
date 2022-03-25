#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
bool check(vector<int> something){
    for(int x=0; x<something.size()-1;x++){
        if(something[x]>something[x+1]){
            return false;
        }
    }
    return true;
}
void bozosort(vector<int>& bozosort,int& z){
    bool thingy=check(bozosort);
    while(thingy==false){
        int x=rand()%bozosort.size();
        int y=rand()%bozosort.size();
        swap(bozosort[x],bozosort[y]);
        z+=1;
        thingy=check(bozosort);
//        cout<<"{";
//        for(int x=0; x<bozosort.size()-1;x++){
//        cout<<bozosort[x]<<",";
//        }
//        cout<<bozosort[bozosort.size()-1]<<"}"<<endl;
    }
}
int main(){
    srand(time(NULL));
    vector<int> potato;
    int sum=0;
    for(int x=0;x<1;x++){
           vector<int> cheese;
        for(int x=0;x<12;x++){
            cheese.push_back(rand()%100);
        }
    int z=0;
    bozosort(cheese,z);
    potato.push_back(z);
    }
    for(int x=0; x<potato.size();x++){
    sum=sum+potato[x];
    }
    cout<<(sum/potato.size());
}
