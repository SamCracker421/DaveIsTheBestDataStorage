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
void drawthingy(Graphics& g, vector<vector<Civilization>> columns,int boardsize){
    Vec2d pos={g.width()/2-g.width()/4,0};
    for(int x =0; x<columns.size();x++){
        for(int y=0; y<columns[x].size();y++){
            if(columns[x][y].alive==true){
                g.rect({pos},g.height()/boardsize,g.height()/boardsize,BLUE,CYAN);
            }
            pos.x+=g.height()/boardsize;
        }
        pos.x=g.width()/2-g.width()/4;
        pos.y+=g.height()/boardsize;
    }
}
void findneighbors(vector<vector<Civilization>>& columns,int boardsize){
    for(int x=0; x<columns.size();x++){
        for(int y=0; y<columns[x].size();y++){
            if(x==0 || y==0){
                if(x==0 && y!=0){
                    if(columns[(x+1)%boardsize][(y)%boardsize].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[boardsize-1][(y)%boardsize].alive==true){
                        columns[x][y].neighbors+=2;
                    }
                    if(columns[(x)%boardsize][(y-1)%boardsize].alive==true){
                        columns[x][y].neighbors+=4;
                    }
                    if(columns[(x+1)%boardsize][(y-1)%boardsize].alive==true){
                        columns[x][y].neighbors+=8;
                    }
                    if(columns[boardsize-1][(y-1)%boardsize].alive==true){
                        columns[x][y].neighbors+=16;
                    }
                    if(columns[(x)%boardsize][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=32;
                    }
                    if(columns[(x+1)%boardsize][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=64;
                    }
                    if(columns[boardsize-1][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=128;
                    }
                    if(columns[x][y].alive==true){
                        columns[x][y].neighbors+=256;
                    }
                }
                else if(x!=0 && y==0){
                    if(columns[(x+1)%boardsize][(y)%boardsize].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[(x-1)%boardsize][(y)%boardsize].alive==true){
                        columns[x][y].neighbors+=2;
                    }
                    if(columns[(x)%boardsize][boardsize-1].alive==true){
                        columns[x][y].neighbors+=4;
                    }
                    if(columns[(x+1)%boardsize][boardsize-1].alive==true){
                        columns[x][y].neighbors+=8;
                    }
                    if(columns[(x-1)%boardsize][boardsize-1].alive==true){
                        columns[x][y].neighbors+=16;
                    }
                    if(columns[(x)%boardsize][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=32;
                    }
                    if(columns[(x+1)%boardsize][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=64;
                    }
                    if(columns[(x-1)%boardsize][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=128;
                    }
                    if(columns[x][y].alive==true){
                        columns[x][y].neighbors+=256;
                    }
                }
                else{
                    if(columns[(x+1)%boardsize][(y)%boardsize].alive==true){
                        columns[x][y].neighbors+=1;
                    }
                    if(columns[boardsize-1][(y)%boardsize].alive==true){
                        columns[x][y].neighbors+=2;
                    }
                    if(columns[(x)%boardsize][boardsize-1].alive==true){
                        columns[x][y].neighbors+=4;
                    }
                    if(columns[(x+1)%boardsize][boardsize-1].alive==true){
                        columns[x][y].neighbors+=8;
                    }
                    if(columns[boardsize-1][boardsize-1].alive==true){
                        columns[x][y].neighbors+=16;
                    }
                    if(columns[(x)%boardsize][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=32;
                    }
                    if(columns[(x+1)%boardsize][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=64;
                    }
                    if(columns[boardsize-1][(y+1)%boardsize].alive==true){
                        columns[x][y].neighbors+=128;
                    }
                    if(columns[x][y].alive==true){
                        columns[x][y].neighbors+=256;
                    }
                }
            }
            else{
                if(columns[(x+1)%boardsize][(y)%boardsize].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x-1)%boardsize][(y)%boardsize].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x)%boardsize][(y-1)%boardsize].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x+1)%boardsize][(y-1)%boardsize].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x-1)%boardsize][(y-1)%boardsize].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x)%boardsize][(y+1)%boardsize].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x+1)%boardsize][(y+1)%boardsize].alive==true){
                    columns[x][y].neighbors+=1;
                }
                if(columns[(x-1)%boardsize][(y+1)%boardsize].alive==true){
                    columns[x][y].neighbors+=1;
                }
            }

        }
    }
}
void switchrules(vector<bool>& rules){
    rules={};
    for(int x=0; x<512;x++){
        if(rand()%2==1){
            rules.push_back(true);
        }
        else{
            rules.push_back(false);
        }
    }
}
void rulesOLife(vector<vector<Civilization>>& columns,vector<bool> rules, int boardsize){
    thread th2(clear,ref(columns));
    thread th3(findneighbors,ref(columns),boardsize);
//    findneighbors(columns,boardsize);
//    switchrules(rules);
    th3.join();
    th2.join();
    for(int x=0; x<columns.size();x++){
        for(int y=0; y<columns[x].size();y++){
            columns[x][y].alive=rules[columns[x][y].neighbors];
        }
    }
}

int main()
{
    Graphics g("Test", 1024,1024);
    srand(time(NULL));
    vector<Civilization> row;
    vector<bool> rules;
    int boardsize=10;
    vector<vector<Civilization>> column;
    for(int y=0; y<boardsize;y++){
        for(int x=0;x<boardsize;x++){
            Civilization p;
            row.push_back(p);
        }
        column.push_back(row);
        row={};
    }
    switchrules(rules);

    while(g.draw()){
        g.text(Vec2d ({0,15}),15,to_string(g.elapsedMs()));
        drawthingy(g,column, boardsize);
        if(g.isKeyPressed(72)){
        thread th4(rulesOLife,ref(column),ref(rules),boardsize);
        th4.join();
//                rulesOLife(column,rules,boardsize);
        }
        if(g.isKeyPressed(69)){
            Vec2d cheese=g.mousePos();
            cheese.x=floor((cheese.x-g.width()/2+g.width()/4)/(g.height()/boardsize));
            cheese.y=floor(cheese.y/(g.height()/boardsize));
            column[cheese.y][cheese.x].alive=true;
        }
        if(g.isKeyPressed(70)){
            for(int x=0;x<100;x++){
            Vec2d cheese={rand()%boardsize,rand()%boardsize};
            column[cheese.x][cheese.y].alive=true;
            }
        }
            if(g.isKeyPressed(65)==true){
                for(int x=0; x<1000;x++){
                rulesOLife(column,rules,boardsize);
                }
    }
            }
}

