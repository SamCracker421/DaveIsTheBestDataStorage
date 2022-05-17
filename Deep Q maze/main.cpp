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
    double gamma=0.90;
    double learningrate=0.01;
    void paction(vector<vector<int>>& potato);
    int getreward(vector<vector<int>> potato);
    void MoveLeft(vector<vector<int>>& CurrentState);
    void MoveRight(vector<vector<int>>& CurrentState);
    double getmaxofnewstate();
    void MoveUp(vector<vector<int>>& CurrentState);
    void MoveDown(vector<vector<int>>& CurrentState);
};
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
    if(yed<=CurrentState.size()-2){
        if(CurrentState[zed][yed+1]==0){
         if(state<=98){
            state=state+1;
        }
        CurrentState[zed][yed+1]=1;
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
    if(yed>0){
        if(CurrentState[zed][yed-1]==0){
        if(state>0){
        state=state-1;
        }
        CurrentState[zed][yed-1]=1;
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
    if(zed<CurrentState.size()-1){
        if(CurrentState[zed+1][yed]==0){
        if(state<=89){
        state=state+10;
        }
        CurrentState[zed+1][yed]=1;
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
    if(zed>0){
        if(CurrentState[zed-1][yed]==0){
        if(state>=10){
        state-=10;
        }
        CurrentState[zed-1][yed]=1;
        CurrentState[zed][yed]=0;
        }
    }
}
double robotboi::getmaxofnewstate(){
    int newstate=state;
    double highest;
    if(action==0){
        if(state>0){
          newstate-=1;
        }
    }
    if(action==1){
        if(state%10!=0){
          newstate-=10;
        }
    }
    if(action==2){
        if(state<98){
          newstate+=1;
        }
    }
    if(action==3){
        if(state%10!=9){
          newstate+=10;
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
    if(action==1){
        if(((state-(state%10))/10)-1>=0){
            if(potato[((state-(state%10))/10)-1][state%10]==4){
                return -10;
            }
        }
    }
    if(action==0){
        if(state%10!=0){
            if(potato[((state-(state%10))/10)][(state%10)-1]==4){
                return -10;
            }
        }
    }
    if(action==3){
        if((((state-(state%10))/10)+1)<=9){
            if(potato[((state-(state%10))/10)+1][state%10]==4){
                return -10;
            }
            if(potato[((state-(state%10))/10)+1][state%10]==2){
                return 100;
            }
        }
    }
    if(action==2){
        if(state%10!=9){
        if(potato[((state-(state%10))/10)][(state%10)+1]==4){
            return -10;
        }
        if(potato[((state-(state%10))/10)][(state%10)+1]==2){
            return 100;
        }
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
//       epsilon-=0.00001;
       potato[0][0]=1;
    }
Qtable[action][currentstate]=Qtable[action][currentstate]+(learningrate*(reward+(gamma*getmaxofnewstate()-Qtable[action][currentstate])));
}
void robotboi::paction(vector<vector<int>>& potato){
    double r = ((double)rand()/(double)(RAND_MAX));
    if(r<epsilon){
        action=rand()%4;
    }
    else{
        int highestvalue=5;
        vector<int> randomthingy;
        for(int x=0; x<3;x++){
            if(Qtable[x][state]<Qtable[x+1][state]){
                highestvalue=x+1;
            }
            else if(Qtable[x][state]==0){
                randomthingy.push_back(x);
            }
            }
        if(Qtable[3][state]==0){
            randomthingy.push_back(3);
        }
        if(highestvalue!=5){
        action=highestvalue;
        }
        else{
            if(randomthingy.size()==0){
                action=0;
            }
            else{
            action=randomthingy[rand()%randomthingy.size()];
}
        }
    }
    calculateQtable(potato);
    if(action==0){
        MoveUp(potato);
    }
    if(action==1){
        MoveLeft(potato);
    }
    if(action==2){
        MoveDown(potato);
    }
      if(action==3){
            MoveRight(potato);
        }

}
void pausefunction(robotboi somethingidk,vector<vector<int>> potato){
    somethingidk;
    potato;
    int pause=1;
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
    int cats=0;
    while(cats<8){
        int x=rand()%10;
        int y=rand()%10;
        if(potato[x][y]==0){
            potato[x][y]=4;
            cats++;
        }
    }
    Graphics g("MazeGuy",1920,1024);
    while(g.draw()){
            FirstTest.paction(potato);
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
            if(g.isKeyPressed(' ')){
                    FirstTest.epsilon-=0.1;
        }
            g.rect({(x*101),(y*101)},100,100,Potato,Potato);
            g.text({(x*101),(y*101)+10},10,to_string(FirstTest.Qtable[0][x*10+y]),BLACK);
            g.text({(x*101),(y*101)+20},10,to_string(FirstTest.Qtable[1][x*10+y]),BLACK);
            g.text({(x*101),(y*101)+30},10,to_string(FirstTest.Qtable[2][x*10+y]),BLACK);
            g.text({(x*101),(y*101)+40},10,to_string(FirstTest.Qtable[3][x*10+y]),BLACK);
            g.text({g.width()-100,g.height()-100},10,to_string((1000*(1/g.elapsedMs()))));
        }
    }
    }
}
