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
vector<Vec2d> GrahamScan(vector<Vec2d> points){
    vector<Vec2d> convexHull;
    sort(points.begin(),points.end(),[](Vec2d p1, Vec2d p2){return p1.y<p2.y;});
    convexHull.push_back(points[0]);
    points.erase(points.begin());
    sort(points.begin(),points.end(),[convexHull](Vec2d p1, Vec2d p2){
        double theta1=atan2(p1.x-convexHull[0].x,p1.y-convexHull[0].y);
        double theta2=atan2(p2.x-convexHull[0].x,p2.y-convexHull[0].y);
        return theta1<theta2;
    });

    convexHull.push_back(points[0]);
    points.erase(points.begin());
    for(int i=0; i<points.size();i++){

        Vec2d p1=convexHull[convexHull.size()-2];
        Vec2d p2=convexHull[convexHull.size()-1];
        Vec2d p3=points[i];
        double theta=(p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
        while(convexHull.size()>1 && theta>=0){
            convexHull.pop_back();
            p1=convexHull[convexHull.size()-2];
            p2=convexHull[convexHull.size()-1];
            p3=points[i];
            theta=(p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
        }
        convexHull.push_back(points[i]);
    }
    convexHull.push_back(convexHull[0]);
    return convexHull;
}

int main(){
    Graphics g("cheese",1024,1024);
    vector<Vec2d> points;
    srand(time(NULL));
    for(int x=0; x<100;x++){
        points.push_back({rand()%1024,rand()%1024});
    }
    while(g.draw()){
        for(int x=0; x<points.size();x++){
            g.ellipse(points[x],5,5,GREEN,WHITE);
        }
        g.polyline(GrahamScan(points),GREEN);
    }
}
