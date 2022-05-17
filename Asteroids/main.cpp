#include <iostream>
#include "graphics.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include <fstream>


using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
class Ship{
private:
     vector<Vec2d> shape={{0,10},{5*sqrt(2),-5*sqrt(2)},{0,0},{-5*sqrt(2),-5*sqrt(2)},{0,10}};
public:
    Vec2d pos;
    double angle;
    double angleacc;
    Vec2d Vel;
    Vec2d Acc{0,0};
    void DrawShip(Graphics& g);
    void goforward();
    void turnleft();
    void turnright();
    Ship(Vec2d inpos);
};
Ship::Ship(Vec2d inpos){
    pos=inpos;
    angle=0;
}
void Ship::DrawShip(Graphics& g){
    Vel={cos(angle+M_PI/2),sin(angle+M_PI/2)};
    Acc.x*=0.1;
    Acc.y*=0.1;
    angle+=angleacc;
    angleacc*=0.5;
    vector<Vec2d> newpos=shape;
    for(int x=0; x<newpos.size();x++){
        newpos[x].rotate(angle);
        newpos[x].x+=pos.x;
        newpos[x].y+=pos.y;
    }
    g.polygon(newpos,WHITE);
}
void Ship::goforward(){
    Vel=Acc+Vel;
    pos.x+=Vel.x;
    pos.y+=Vel.y;
}
void Ship::turnleft(){
    angle+=M_PI/45;
}
void Ship::turnright(){
    angle-=M_PI/45;
}
int main(){
    Graphics g("idk",1024,1024);
    Ship Ship1({0,0});
    while(g.draw()){
        if(g.isKeyPressed(Key::Left)){
            Ship1.turnleft();
        }
        if(g.isKeyPressed(Key::Right)){
            Ship1.turnright();
        }
        if(g.isKeyPressed(Key::Up)){
            Ship1.goforward();
        }
        Ship1.DrawShip(g);
    }
}
