#include <iostream>
#include "graphics.h"
#include "cmath"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
class PointPair{
public:
    Vec2d p1;
    Vec2d p2;
    double distance;
};

PointPair closestPoint(vector<Vec2d>& points){
    PointPair returning;
    returning.distance=100;
    for(int x=0; x<points.size();x++){
        for(int y=0; y<points.size();y++){
            if(x!=y){
                double distancebetweenpoints=sqrt(pow((points[x].x-points[y].x),2)+pow((points[x].y-points[y].y),2));
                if(distancebetweenpoints<returning.distance){
                    returning.distance=distancebetweenpoints;
                    returning.p1=points[x];
                    returning.p2=points[y];
                }
            }
        }
    }
    return returning;
}

int main(){
    vector<Vec2d> points;
    Graphics g("MazeGuy",1920,1024);
    for(int x=0; x<100;x++){
        points.push_back({rand()%1920,rand()%1024});
    }

    Vec2d point1=closestPoint(points).p1;
    Vec2d point2=closestPoint(points).p2;
    while(g.draw()){
        for(int x=0; x<points.size();x++){
            g.ellipse(points[x],2,2,WHITE,WHITE);
        }
        g.ellipse(point1,2,2,GREEN,GREEN);
        g.ellipse(point2,2,2,GREEN,GREEN);

    }
}
