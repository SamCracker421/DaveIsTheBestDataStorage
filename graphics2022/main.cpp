#include <iostream>
#include "graphics.h"
#include <random>
#include "windows.h"
#include <chrono>
#include <cmath>
 using namespace std;
 using namespace mssm;

class ball{
public:
ball(Vec2d rectpos);
Vec2d pos={200,200};
bool up=false;
bool left=false;
bool right=false;
bool down=false;
int xspeed=pow(-rand()%10,(rand()%2+1));
int yspeed=pow(-rand()%20,(rand()%2+1));
bool ishitting(Vec2d rectpos);
};

bool ball::ishitting(Vec2d rectpos){
    if(((this->pos.x)>rectpos.x) && (this->pos.x)<){

    }
}

int main(){
    Graphics g("pp",1920,1024);
    Vec2d ballpos={g.width()/2,g.height()/2};
    Vec2d rectpos={0,g.height()-g.height()/10};
    int rectlength=100;
    while(g.draw()){
        for (const Event& e : g.events()) {
            switch (e.evtType) {
            case EvtType::KeyPress:
                if (e.arg == 262) {
                    if(((rectpos.x+g.width()/10)+rectlength)<=g.width()){
                    rectpos.x+=g.width()/10;
                    }
                }
                if(e.arg == 263){
                    if(rectpos.x-g.width()/10>=0){
                    rectpos.x-=g.width()/10;
                    }
                }
                break;
            default:
                break;
            }
        }
            g.rect(rectpos,rectlength,10,BLUE,BLUE);
    }
}

