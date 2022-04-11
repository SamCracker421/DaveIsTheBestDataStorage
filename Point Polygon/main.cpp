#include <iostream>
#include "graphics.h"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

// Note:  Mac Users who are using Qt Creator...
//        if the program compiles and runs but a window doesn't open up
//        try un-checking "run in terminal"


// Here are some of the basic drawing commands:

//void   line(Vec2d p1, Vec2d p2, Color c = WHITE);
//void   ellipse(Vec2d center, double w, double h, Color c = WHITE, Color f = TRANSPARENT);
//void   arc(Vec2d center, double w, double h, double a, double alen, Color c = WHITE);
//void   chord(Vec2d center, double w, double h, double a, double alen, Color c = WHITE, Color f = TRANSPARENT);
//void   pie(Vec2d center, double w, double h, double a, double alen, Color c = WHITE, Color f = TRANSPARENT);
//void   rect(Vec2d corner, double w, double h, Color c = WHITE, Color f = TRANSPARENT);
//void   polygon(std::vector<Vec2d> pts, Color border, Color fill = TRANSPARENT);
//void   polyline(std::vector<Vec2d> pts, Color color);
//void   text(Vec2d pos, double size, const std::string& str, Color textColor = WHITE, HAlign hAlign = HAlign::left, VAlign vAlign = VAlign::baseline);
bool onedirection(Vec2d point, vector<Vec2d> points){
    if(points.size()>0){
    points.push_back(points[0]);
    }
double line=point.x;
int intersections=0;
if(points.size()>2){
for(int x=0;x<points.size()-1;x++){
    if(points[x].x-points[x+1].x==0){
    if(point.x==points[x].x){
    if(points[x+1].y>points[x].y){
        if(point.y<points[x+1].y && point.y>points[x].y){
            return true;
        }
    }
    else{
        if(point.y>points[x+1].y && point.y<points[x].y){
            return true;
        }
    }
    }
    }
    else{
        if(point.x==points[x].x && points[x].y==point.y){
            return true;
        }
        else{
        int b=points[x].y-(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x))*points[x].x);
        if(points[x].x>points[x+1].x){
        if(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x)*point.x+b>point.y) && (point.x<points[x].x) && (point.x>=points[x+1].x)){
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

int main()
{
    Graphics g("CDthesesnutes", 1920, 1024);
    srand(time(NULL));
    vector<Vec2d> polygons;
    vector<Vec2d> points;
    for(int z=0; z<50000;z++){
        Vec2d potato={rand()%g.width(),rand()%g.height()};
        points.push_back(potato);
    }
    while (g.draw()) {
        g.text({0,20},10,"x: " + to_string(g.mousePos().x) + " y: " + to_string(g.mousePos().y));
        for (const Event& e : g.events()) {
            switch (e.evtType) {
            case EvtType::MousePress:
                polygons.push_back(g.mousePos());
                break;
            case EvtType::KeyPress:
                if(e.arg==' '){
                    polygons.push_back(polygons[0]);
                }
            default:
                break;
            }
        }
        for(int x=0;x<points.size();x++){
            if(onedirection(points[x],polygons)){
                   g.ellipse(points[x],2,2,GREEN,GREEN);
            }
            else{
                   g.ellipse(points[x],2,2,RED,RED);
            }
        }
        if(polygons.size()>0){
        g.polygon(polygons,WHITE);
        }
        }

    return 0;
}


