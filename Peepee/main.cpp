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
bool onedirection(Vec2d point, vector<Vec2d>& points){
double line=point.x;
int intersections=0;
if(points.size()>3){
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
        if(point.x==points[x].x && points[x].y>point.y){
            intersections+=2;
        }
        else if(point.x==points[x].x && points[x].y>point.y){
            return true;
        }
        else{
        int b=points[x].y-(points[x].y-points[x+1].y)/(points[x].x-points[x+1].x)*points[x].x;
        if(points[x].x>points[x+1].x){
        if(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x)*line+b>=point.y) && (point.x<points[x].x) && (point.x>points[x+1].x)){
        intersections+=1;
        }
        }
        else{
            if(((points[x].y-points[x+1].y)/(points[x].x-points[x+1].x)*line+b>=point.y) && (point.x>points[x].x) && (point.x<points[x+1].x)){
            intersections+=1;
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
else{
    return false;
}
}

int main()
{
    Graphics g("CDthesesnutes", 1920, 1024);
    vector<Vec2d> polygons;

    while (g.draw()) {
        Vec2d point=g.mousePos();
        g.text({0,20},10,to_string(onedirection(point,polygons)));
        for (const Event& e : g.events()) {
            switch (e.evtType) {
            case EvtType::MousePress:
                polygons.push_back(g.mousePos());
                break;
            case EvtType::KeyPress:
                if(e.arg == ' '){
                    polygons.push_back(polygons[0]);
                }
            default:
                break;
            }
        }
        if(polygons.size()>0){
        g.polygon(polygons,WHITE);
        g.ellipse(point,5,5,BLUE,BLUE);
        }
        }

    return 0;
}


