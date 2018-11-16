#include "Map.h"
#include "Tool.h"
#include<iostream>
using namespace std;
Map::Map()
{
    //默认构造的时候打印地图
    print();
}
void Map::print()
{
    SetCursorPosition(0,0);
    for(int i = 0;i < 25;i++)
    {
        cout<<"■";
    }
    SetCursorPosition(0,0);
    for(int i = 0;i < 25;i++)
    {
        cout<<"■"<<endl;
    }
    for(int i = 0;i <= 25;i++)
    {
        SetCursorPosition(25,i);
        cout<<"■"<<endl;
    }
    SetCursorPosition(0,25);
    for(int i = 0;i < 25;i++)
    {
        cout<<"■";
    }
}
Map::~Map()
{
    //dtor
}
