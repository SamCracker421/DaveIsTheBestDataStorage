#include <iostream>
#include "graphics.h"
#include <thread>
#include <chrono>

using namespace std;
using namespace mssm;
using namespace this_thread;

#pragma GCC diagnostic ignored "-Wsign-compare"


int main()
{
    Vec2d cheese={15,15};
    Vec2d potato={30,30};
    Vec2d pizza=cheese/potato;
    cout<<pizza.print();
}

