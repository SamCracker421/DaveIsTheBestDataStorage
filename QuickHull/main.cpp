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

vector<Vec2d> GetDataPoints(int numofangles, Vec2d Point){
    vector<Vec2d> data;
    for(int x=0; x<numofangles;x++){
        double dividerthingy=((M_PI*2)/numofangles);
        double theta=dividerthingy*x;
        double r=Point.x*cos(theta)+Point.y*sin(theta);
        data.push_back({theta,r});
    }
    return data;
}
Vec2d final(vector<Vec2d> points, Graphics& g){
    Vec2d finale;
    int numofangles=360;
    int RCount=100;
    double maxR=Vec2d({g.width(),g.height()}).magnitude();
    vector<vector<int>> tally(RCount,vector<int>(numofangles));
    for(int i=0; i<points.size();i++){
        vector<Vec2d> processing=GetDataPoints(numofangles,points[i]);
        for(int p=0; p<processing.size();p++){
            double r=processing[p].y;
            int rIndex=(r*RCount)/maxR;
            int thetaIndex=p;
            if(rIndex>=0 && rIndex<tally.size()){
            tally[rIndex][thetaIndex]++;
            }
            else{
                rIndex=abs(rIndex);
                thetaIndex=(p+numofangles/2)%numofangles;
                tally[rIndex][thetaIndex]++;
            }
        }
    }
    int inty=0;
    int intx=0;
    int value=0;
    for(int Rs=0; Rs<tally.size();Rs++){
        for(int Ts=0; Ts<tally.size();Ts++){
            if(tally[Rs][Ts]>value){
                value=tally[Rs][Ts];
                intx=Rs;
                inty=Ts;
            }
        }
    }
    return {intx*maxR/RCount,(inty*M_PI*2)/numofangles};
}

int main(){
    Graphics g("Cum",1240,1240);
    vector<Vec2d> Points;
//    ifstream pointsFile("C:\\Users\\Samantha\\Desktop\\DataStructures\\LineThingy\\assets\\Pts.csv");
//    string line;
//    while(getline(pointsFile, line)){
//        stringstream ss(line);;
//        double yval;
//        double xval;
//        char comma(',');
//        ss >> xval;
//        ss>>comma;
//        ss>> yval;
//        Points.push_back({xval,yval});
//    }
//     double lowestx=Points[0].x;
//     double highestx=Points[0].x;
//     double lowesty=Points[0].y;
//     double highesty=Points[0].y;
//    for(int x=0; x<Points.size();x++){
//        if(Points[x].x<lowestx){
//            lowestx=Points[x].x;
//        }
//        if(Points[x].x>highestx){
//            highestx=Points[x].x;
//        }
//    }
//    for(int i=0; i<Points.size();i++){
//        if(Points[i].y<lowesty){
//            lowesty=Points[i].y;
//        }
//        if(Points[i].y>highesty){
//            highesty=Points[i].y;
//        }
//    }
//    for(int x=0; x<Points.size();x++){
//Points[x]={(Points[x].x+abs(lowestx))/((abs(lowestx)+highestx)/g.width()),(Points[x].y+abs(lowesty))/((abs(lowesty)+highesty)/g.height())};
//    }

    while(g.draw()){
        Vec2d lines;
            if(g.isKeyPressed(Key::ENTER)){
                Points.push_back(g.mousePos());
            }
            lines=final(Points,g);
            Vec2d P1={lines.x,0};
            P1.rotate(lines.y);
            Vec2d P2={1000,0};
            P2.rotate(lines.y+M_PI/2);
            Vec2d Point1=P1+P2;
            Vec2d Point2=P1-P2;
            g.line(Point1,Point2,BLUE);
        for(int x=0; x<Points.size();x++){
            g.ellipse(Points[x],5,5,GREEN,GREEN);
        }
    }       
}
