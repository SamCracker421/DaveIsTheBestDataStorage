#include <iostream>
#include "graphics.h"
#include "cmath"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
class robotboi{
public:
    vector<vector<double>> Qtable;
    double epsilon=0.2;
    void createTable();
    void calculateQtable(vector<vector<int>>& potato);
    int state=0;
    int action;
    void setstate();
    double gamma=0.9;
    double learningrate=0.01;
    void paction(vector<vector<int>>& potato);
    int getreward(vector<vector<int>> potato);
    void MoveLeft(vector<vector<int>>& CurrentState);
    void MoveRight(vector<vector<int>>& CurrentState);
    double getmaxofnewstate();
    void MoveUp(vector<vector<int>>& CurrentState);
    void MoveDown(vector<vector<int>>& CurrentState);
};
void robotboi::setstate(){
    if(action==0){
        if(state>=10){
        state=state-10;
        }
    }
    if(action==1){

    }
}
void robotboi::createTable(){
for(int x=0;x<4;x++){
    vector<double> cheese;
for(int y=0;y<100;y++){
    cheese.push_back(0);
}
Qtable.push_back(cheese);
}
};
void robotboi::MoveDown(vector<vector<int>> &CurrentState){
    int zed=0;
    int yed=0;
    for(int x=0;x<CurrentState.size();x++){
        for(int y=0; y<CurrentState[x].size();y++){
            if(CurrentState[x][y]==1){
                zed=x;
                yed=y;
            }
        }
    }
    if(zed+1<CurrentState.size()){
        if(CurrentState[zed+1][yed]==0){
         if(state<=89){
            state=state+10;
        }
        CurrentState[zed+1][yed]=1;
        CurrentState[zed][yed]=0;
        }
    }
}
void robotboi::MoveUp(vector<vector<int>> &CurrentState){
    int zed=0;
    int yed=0;
    for(int x=0;x<CurrentState.size();x++){
        for(int y=0; y<CurrentState[x].size();y++){
            if(CurrentState[x][y]==1){
                zed=x;
                yed=y;
            }
        }
    }
    if(zed>=1){
        if(CurrentState[zed-1][yed]==0){
        if(state>=10){
        state=state-10;
        }
        CurrentState[zed-1][yed]=1;
        CurrentState[zed][yed]=0;
        }
    }
}
void robotboi::MoveRight(vector<vector<int>> &CurrentState){
    int zed=0;
    int yed=0;
    for(int x=0;x<CurrentState.size();x++){
        for(int y=0; y<CurrentState[x].size();y++){
            if(CurrentState[x][y]==1){
                zed=x;
                yed=y;
            }
        }
    }
    if(yed+1<CurrentState[zed].size()){
        if(CurrentState[zed][yed+1]==0){
        if(state<=98){
        state=state+1;
        }
        CurrentState[zed][yed+1]=1;
        CurrentState[zed][yed]=0;
        }
    }
}
void robotboi::MoveLeft(vector<vector<int>> &CurrentState){
    int zed=0;
    int yed=0;
    for(int x=0;x<CurrentState.size();x++){
        for(int y=0; y<CurrentState[x].size();y++){
            if(CurrentState[x][y]==1){
                zed=x;
                yed=y;
            }
        }
    }
    if(yed-1>=0){
        if(CurrentState[zed][yed-1]){
        if(state>=1){
        state-=1;
        }
        CurrentState[zed][yed-1]=1;
        CurrentState[zed][yed]=0;
        }
    }
}
double robotboi::getmaxofnewstate(){
    int newstate=state;
    double highest;
    if(action==0){
        if(state-10>=0){
          newstate-=10;
        }
    }
    if(action==1){
        if(state%10!=0){
          newstate-=1;
        }
    }
    if(action==2){
        if(state+10<100){
          newstate+=10;
        }
    }
    if(action==3){
        if(state%10!=9){
          newstate+=1;
        }
    }
    highest=Qtable[0][newstate];
for(int x=0; x<4;x++){
    if(Qtable[x][newstate]>highest){
        highest=Qtable[x][newstate];
    }
}
return highest;
}
int robotboi::getreward(vector<vector<int>> potato){
    if(action==0){
        if(((state-(state%10))/10)-1<0){
            return -100;
        }
            if(potato[((state-(state%10))/10)-1][state%10]==4){
                return -1;
            }
    }
    if(action==1){
        if(state%10==0){
            return -100;
        }
        else{
            if(potato[((state-(state%10))/10)][(state%10)-1]==4){
                return -1;
            }
        }
    }
    if(action==2){
        if((((state-(state%10))/10)+1)>9){
        return -100;
        }
            if(potato[((state-(state%10))/10)+1][state%10]==4){
                return -1;
            }
            if(potato[((state-(state%10))/10)][state%10]==2){
                return 100;
            }

    }
    if(action==3){
        if(state%10==9){
            return -100;
        }
        if(potato[((state-(state%10))/10)][(state%10)+1]==4){
            return -1;
        }
        if(potato[((state-(state%10))/10)][(state%10)+1]==2){
            return 100;
        }
    }
    return 0;
}
void robotboi::calculateQtable(vector<vector<int>>& potato){
    int reward=getreward(potato);
    int currentstate=state;
    if(reward!=0){
        potato[((state-(state%10)))/10][state%10]=0;
       state=0;
//       epsilon-=0.001;
       potato[0][0]=1;
    }
Qtable[action][currentstate]=Qtable[action][currentstate]+(learningrate*(reward+(gamma*getmaxofnewstate()-Qtable[action][currentstate])));
}
void robotboi::paction(vector<vector<int>>& potato){
    double lower_bound = 0;
    double upper_bound = 1;
    uniform_real_distribution<double> unif(lower_bound,upper_bound);
    default_random_engine re;
    double a_random_double = unif(re);
    if(a_random_double<epsilon){
        action=rand()%4;
    }
    else{
        int highestvalue=0;
        for(int x=0; x<4;x++){
            if(Qtable[x][state]>Qtable[highestvalue][state]){
            highestvalue=x;
            }
            }
        action=highestvalue;
    }
    if(action==0){
        MoveUp(potato);
    }
    else if(action==1){
        MoveLeft(potato);
    }
    else if(action==2){
        MoveDown(potato);
    }
     else if(action==3){
            MoveRight(potato);
        }
     else{
         paction(potato);
     }

}
int main(){
    srand(time(NULL));
    robotboi FirstTest;
    FirstTest.createTable();
    vector<vector<int>> potato;
    for(int z=0; z<10;z++){
        vector<int> row;
    for(int x=0; x<10;x++){
        row.push_back(0);
    }
    potato.push_back(row);
    }
    potato[0][0]=1;
    potato[9][9]=2;
/*    int cats=0;*//*
    while(cats<5){
        int x=rand()%10;
        int y=rand()%10;
        if(potato[x][y]==0){
            potato[x][y]=4;
            cats++;
        }*/
//    }
    Graphics g("MazeGuy",1920,1024);
    while(g.draw()){
        FirstTest.paction(potato);
        FirstTest.calculateQtable(potato);
    for(int x=0; x<potato.size();x++){
        for(int y=0;y<potato[x].size();y++){
            Color Potato;
            switch(potato[x][y]){
            case 0:
                Potato=WHITE;
                break;
            case 1:
                Potato=ORANGE;
                break;
            case 2:
                Potato=YELLOW;
                break;
            case 4:
                Potato=RED;
                break;
            }
            g.rect({(x*101),(y*101)},100,100,Potato,Potato);
            g.text({(x*101),(y*101)-50},10,to_string(FirstTest.Qtable[3][y*10+x]),BLACK);
        }
    }
    }
}
