#include <iostream>
#include "graphics.h"
#include <cmath>
#include <algorithm>
#include <limits>

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
    bool equals(PointPair p3, double threshhold);
};

PointPair BruteForcePoint(vector<Vec2d>& points){
    PointPair returning;
    returning.distance=MAXINT32;
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
PointPair ClosestPointStep2(vector<Vec2d>& points,bool potato){
    PointPair ending;
    if(potato){
        sort(points.begin(),points.end(),[](Vec2d Point1,Vec2d Point2){return Point1.x<Point2.x;});
    }
    if(points.size()>2){
        vector<Vec2d> high;
        vector<Vec2d> low;
        for(int x=0;x<points.size();x++){
            if(points.size()%2==0){
            if(x<=(floor(points.size()/2))){
                low.push_back(points[x]);
            }
            if(x>=(floor(points.size()/2))){
                high.push_back(points[x]);
            }
            }
            else{
                if(points[x].x<points[0].x+((points[points.size()-1].x-points[0].x)/2)){
                    low.push_back(points[x]);
                }
                else{
                    high.push_back(points[x]);
                }
            }
        }
        PointPair p2=ClosestPointStep2(low,false);
        PointPair p1=ClosestPointStep2(high,false);
        if(p1.distance<p2.distance){
            ending=p1;
        }
        else{
            ending=p2;
        }
        vector<Vec2d> strip;
        PointPair Returning;
        Returning.distance=MAXINT32;
        for(int x=0; x<points.size();x++){
            if(points[x].x>(points[(floor(points.size()/2))].x-ending.distance) && points[x].x<points[(floor(points.size()/2))].x+ending.distance && x!=(floor(points.size()/2))){
                strip.push_back(points[x]);
            }
        }
        if(strip.size()>0){
        sort(strip.begin(),strip.end(),[](Vec2d Point1,Vec2d Point2){return Point1.y<Point2.y;});
        for(int x=0; x<strip.size();x++){
            for(int z=0; z<strip.size();z++){
                if(x!=z){
                    double Distance=sqrt(pow((strip[z].x-strip[x].x),2)+pow((strip[z].y-strip[x].y),2));
                    if(Distance<ending.distance){
                        Returning.p1=strip[z];
                        Returning.p2=strip[x];
                        Returning.distance=Distance;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        if(Returning.distance!=MAXINT32){
            ending=Returning;
        }
        }

    }
    if(points.size()<=2){
        PointPair returning;
        returning.p1=points[0];
        returning.p2=points[1];
        returning.distance=sqrt(pow((points[0].x-points[1].x),2)+pow((points[0].y-points[1].y),2));
        return returning;
    }

    return ending;
}
PointPair ClosestPoint(vector<Vec2d>& points){
    return ClosestPointStep2(points,true);
}

int main(){
    vector<Vec2d> points;
    Graphics g("MazeGuy",1024,1024);
    for(int x=0; x<100;x++){
        points.push_back({rand()%1024,rand()%1024});
    }
    PointPair Parmesan=BruteForcePoint(points);
    PointPair cheese=ClosestPoint(points);
    while(g.draw()){
        for(int x=0; x<points.size();x++){
            g.ellipse(points[x],2,2,WHITE,WHITE);
        }
        if(cheese.distance==Parmesan.distance){
            g.ellipse(Parmesan.p1,2,2,GREEN,GREEN);
            g.ellipse(Parmesan.p2,2,2,GREEN,GREEN);
        }
        else{
            g.ellipse(Parmesan.p1,2,2,RED,RED);
            g.ellipse(Parmesan.p2,2,2,RED,RED);
            g.ellipse(cheese.p1,2,2,BLUE,BLUE);
            g.ellipse(cheese.p2,2,2,BLUE,BLUE);
        }
        g.text({0,20},20,"Custom: "+to_string(cheese.distance));
        g.text({0,40},20,"Custom: {" + to_string(cheese.p1.x)+ " , " +to_string(cheese.p1.y) + "}:{"+to_string(cheese.p2.x) + " , " + to_string(cheese.p2.y)+ "}");
        g.text({0,60},20,"BruteForce: "+to_string(Parmesan.distance));
        g.text({0,80},20,"BruteForce: {" + to_string(Parmesan.p1.x)+ " , " +to_string(Parmesan.p1.y) + "}:{"+to_string(Parmesan.p2.x) + " , " + to_string(Parmesan.p2.y)+ "}");
    }
}
