#include <iostream>
#include "graphics.h"
#include "cmath"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif


//class AI{
//public:
//    moveup
//};


bool onedirection(Vec2d point, vector<Vec2d> points){
    if(points.size()>0){
    points.push_back(points[0]);
    }
double line=point.x;
int intersections=0;
if(points.size()>2){
for(int x=0;x<points.size()-1;x++){
        if(point.x==points[x].x && points[x].y==point.y){
            return true;
        }
        else{
        int b=points[x].y-(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x))*points[x].x);
        if(points[x].x>points[x+1].x){
        if(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x)*point.x+b>point.y) && (point.x<points[x].x) &&          (point.x>=points[x+1].x)){
        intersections+=1;
        }
        else if(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x)*point.x+b==point.y) && (point.x<=points[x].x) && (point.x>=points[x+1].x)){
            return true;
        }
        }
        else{
            if(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x)*line+b>point.y) && (point.x>=points[x].x) && (point.x<points[x+1].x)){
            intersections+=1;
            }
            else if(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x)*point.x+b==point.y) && (point.x>=points[x].x) && (point.x<=points[x+1].x)){
                return true;
            }
        }
        }
}
if(intersections%2==0){
    return false;
}
else{
    return true;
}
}
    return false;
}

class car{
public:
    Vec2d pos={700,700};
    double angle;
    double angleacceleration;
    vector<Vec2d> Car{
        {25,12.5},{25,-12.5},{-25,-12.5},{-25,12.5}
    };
    void rotatecar(double changle);
    void MoveForward();
    void drawcar(Graphics& g, vector<Vec2d> outside,vector<Vec2d> inside);
    bool checkcar(vector<Vec2d> outside, vector<Vec2d> inside);
};
void car::MoveForward(){
    Vec2d Velocity{4*cos(angle),4*sin(angle)};
    pos+=Velocity;
}
void car::drawcar(Graphics& g, vector<Vec2d> outside,vector<Vec2d> inside){
    vector<Vec2d> points;
    for(int x=0;x<Car.size();x++){
    points.push_back(pos+Car[x]);
    }
    if(checkcar(outside,inside)){
        g.polygon(points,RED,RED);
    }
    else{
        g.polygon(points,GREEN,GREEN);
    }
}
bool car::checkcar(vector<Vec2d> outside, vector<Vec2d> inside){
    for(int x=0; x<Car.size();x++){
        if(onedirection(Car[x]+pos,outside)==false|| onedirection(Car[x]+pos,inside)==true){
        return true;
        }
    }
    return false;
}
void car::rotatecar(double changle){
    for(int x=0; x<this->Car.size();x++){
        Car[x].rotate(changle);
    }
    this->angle+=changle;
}
int main()
{
    Graphics g("CDthesesnutes", 1920, 1024);
    srand(time(NULL));
    vector<Vec2d> polygonoutside{{200,600},{300,750},{700,800},{1400,750},{1600,400},{1200,200},{800,400},{600,200},{200,400}};
    vector<Vec2d> polygoninside{{611,338},{783,498},{1189,289},{1461,426},{1358,652},{800,680},{472,644},{349,435}};
    car potato;
    double carangle=0;

    while (g.draw()) {
        g.text({0,20},10,"x: " + to_string(g.mousePos().x) + " y: " + to_string(g.mousePos().y));
         if(g.isKeyPressed(Key::Left)){
            potato.rotatecar(-0.1);
         }
         if(g.isKeyPressed(Key::Right)){
            potato.rotatecar(0.1);
         }
         if(g.isKeyPressed(Key::Up)){
            potato.MoveForward();
         }
        g.polygon(polygonoutside,WHITE);
        g.polygon(polygoninside,WHITE);
        potato.drawcar(g,polygonoutside,polygoninside);
        }

    return 0;
}


