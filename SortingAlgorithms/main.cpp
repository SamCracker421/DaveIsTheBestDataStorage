#include <iostream>
#include "graphics.h"
#include <thread>
#include <chrono>

using namespace std;
using namespace mssm;
using namespace this_thread;

#pragma GCC diagnostic ignored "-Wsign-compare"

class Civilization{
public:
    bool alive=false;
    int neighbors=0;
};
void clear(vector<vector<Civilization>>& columns){
    for(int x=0; x<columns.size();x++){
        for(int y=0; y<columns.size();y++){
            columns[x][y].neighbors=0;
        }
    }
}
void drawthingy(Graphics& g, vector<vector<Civilization>> columns){
    Vec2d pos={0,0};
    for(int x =0; x<columns.size();x++){
        for(int y=0; y<columns[x].size();y++){
            if(columns[x][y].alive==false){
                g.rect(pos,10,10,WHITE,BLACK);
            }
            else{
                g.rect(pos,10,10,WHITE,YELLOW);
            }
            pos.x+=10;
        }
        pos.x=0;
        pos.y+=10;
    }
}
void findneighbors(vector<vector<Civilization>>& columns){
    for(int x=0; x<columns.size();x++){
        for(int y=0; y<columns[x].size();y++){
            if(x==0 || y==0){
                if(x==0 && y!=0){
                    if(columns[(x+1)%100][(y)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[99][(y)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x)%100][(y-1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x+1)%100][(y-1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[99][(y-1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x)%100][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x+1)%100][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[99][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                }
                else if(x!=0 && y==0){
                    if(columns[(x+1)%100][(y)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x-1)%100][(y)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x)%100][99].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x+1)%100][99].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x-1)%100][99].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x)%100][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x+1)%100][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x-1)%100][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                }
                else{
                    if(columns[(x+1)%100][(y)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[99][(y)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x)%100][99].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x+1)%100][99].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[99][99].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x)%100][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x+1)%100][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[99][(y+1)%100].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                }
            }
            else{
                if(columns[(x+1)%100][(y)%100].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x-1)%100][(y)%100].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x)%100][(y-1)%100].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x+1)%100][(y-1)%100].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x-1)%100][(y-1)%100].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x)%100][(y+1)%100].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x+1)%100][(y+1)%100].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x-1)%100][(y+1)%100].alive==true){
                    columns[x][y].neighbors+=1;
                }
            }

        }
    }
}
void rulesOLife(vector<vector<Civilization>>& columns){
    clear(columns);
    findneighbors(columns);
    for(int x=0; x<columns.size();x++){
        for(int y=0; y<columns[x].size();y++){
            if(columns[x][y].neighbors<2){
                columns[x][y].alive=false;
            }
            else if(columns[x][y].neighbors>=4){
                columns[x][y].alive=false;
            }
            else if(columns[x][y].neighbors==3){
                columns[x][y].alive=true;
            }
        }
    }
}
int main()
{
    srand(time(NULL));
    vector<Civilization> row;
    vector<vector<Civilization>> column;
    for(int y=0; y<100;y++){
        for(int x=0;x<100;x++){
            Civilization p;
            row.push_back(p);
        }
        column.push_back(row);
        row={};
    }

    Graphics g("Test", 1024,1024);

    while(g.draw()){
        drawthingy(g,column);
        if(g.isKeyPressed(83)){
            rulesOLife(column);
        }
        if(g.isKeyPressed(69)){
            Vec2d cheese=g.mousePos();
            cheese.x=floor(cheese.x/10);
            cheese.y=floor(cheese.y/10);
            column[cheese.y][cheese.x].alive=true;
        }
        if(g.isKeyPressed(70)){
            for(int x=0;x<100;x++){
            Vec2d cheese={rand()%100,rand()%100};
            column[cheese.x][cheese.y].alive=true;
            }
        }
            if(g.isKeyPressed(65)==true){
                for(int x=0; x<1000;x++){
                rulesOLife(column);
                }
    }
    }
}

