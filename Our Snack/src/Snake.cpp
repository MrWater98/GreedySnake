#include "Snake.h"
#include "Tool.h"
#include <deque>
#include "conio.h"
#include<windows.h>
#include "stdio.h"
#include "Food.h"
#include<string.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;
//默认构造函数
bool deque_find(deque<pair<short,short> > _snake,pair<short,short> dir);
bool head_find(deque<pair<short,short> > _snake,pair<short,short> dir);
Snake::Snake()
{
    snake.push_back(pair<short,short>(16,14));
    snake.push_back(pair<short,short>(15,14));
    snake.push_back(pair<short,short>(14,14));
    foodx=0;
    foody=0;//改成pair
    foodCreate();
}

Snake::~Snake()
{
    //dtor
}
void Snake::foodCreate()
{
    srand((unsigned)time(NULL));
    while(true){
        bool outIndex = true;
        foodx=(rand() % 24 + 1);
        foody=(rand() % 24 + 1);
        for (auto i=snake.begin();i!=snake.end();i++)
        {
            if(foodx==i->first && foody==i->second)
                outIndex = false;
        }
        if(outIndex)
            break;
    }
    printFood();
}
void Snake::printFood()
{
    SetCursorPosition(foodx,foody);
    cout<<"●";
    SetCursorPosition(0,28);
    cout<<"                             ";
    SetCursorPosition(0,28);
    cout<<"x:"<<foodx<<" y:"<<foody<<endl;
}
void Snake::print()
{
    for(auto &i : snake)
    {
        if(i==*snake.begin())
        {
            SetColor(3);
            SetCursorPosition(i.first,i.second);
            cout<<"●";
            continue;
        }
        SetColor(7);
        SetCursorPosition(i.first,i.second);
        cout<<"●";
    }
    Sleep(50);
}
bool Snake::check()
{
    for (auto i=snake.begin()+1;i!=snake.end();i++)
    {
        if(snake.front().first==i->first && snake.front().second==i->second)
            {
                return false;
            }
    }
    return true;
}
void Snake::walk()
{
    HideCursor();
    print();
    int point = 0;
    while(!((snake.front().first<1||snake.front().first>24)||(snake.front().second<1||snake.front().second>24))&& check())
    {
        if(snake.front().first==foodx && snake.front().second==foody)
        {
            ++point;
            snake.push_front(pair<short,short>(foodx,foody));
            foodCreate();
            SetCursorPosition(0,27);
            cout<<"Your Score is "<<point*10<<endl;
        }
        //如果接受到键盘
        /*
        if(kbhit())
        {
            //令direction变成接收到键盘的值
            int temp, temp2;
            temp2=getch();
            temp=getch();
            if (abs(direction-temp)!=2 && abs(direction-temp)!=8)
                direction = temp;
        }*/
        //Sleep(30);
        direction = getScore();
        //Sleep(30);
        //SetCursorPosition(30,9);
        //cout<<direction;
        switch(direction)//运动这里看看能不能封装一下，弄成静态全局函数
        {
        //77代表右方向
        case 77:
            SetCursorPosition(snake.back().first,snake.back().second);
            cout<<"  ";
            snake.pop_back();
            snake.push_front(pair<short,short>(snake.front().first+1,snake.front().second));
            print();
            break;
        //左方向
        case 75:
            SetCursorPosition(snake.back().first,snake.back().second);
            cout<<"  ";
            snake.pop_back();
            snake.push_front(pair<short,short>(snake.front().first-1,snake.front().second));
            print();
            break;
        //上方向
        case 72:
            SetCursorPosition(snake.back().first,snake.back().second);
            cout<<"  ";
            snake.pop_back();
            snake.push_front(pair<short,short>(snake.front().first,snake.front().second-1));
            print();
            break;
            //下方向
        case 80:
            SetCursorPosition(snake.back().first,snake.back().second);
            cout<<"  ";
            snake.pop_back();
            snake.push_front(pair<short,short>(snake.front().first,snake.front().second+1));
            print();
            break;
        }
    }
    system("PAUSE");
    Sleep(1000);
    system("cls");
    SetCursorPosition(12,12);
    cout << "Game Over" << endl;
}
bool Snake::isOnSnake(pair<short,short> p)
{
    for(auto &i:snake)
    {
        if(p==i)
            return true;
    }
    return false;
}
int Snake::getScore()
{
    //1、获取蛇头
    pair<short,short> snakeHead = snake.front();
    //2、定义一个上下左右数组
    pair<short,short> dir[4];
    //上
    dir[0] = pair<short,short>(snakeHead.first,snakeHead.second-1);
    //下
    dir[1] = pair<short,short>(snakeHead.first,snakeHead.second+1);
    //左
    dir[2] = pair<short,short>(snakeHead.first-1,snakeHead.second);
    //右
    dir[3] = pair<short,short>(snakeHead.first+1,snakeHead.second);

    //3、定义一个上下左右 分数的数组
    //int Score[4]={9999999,99999999,99999999,99999999};
    int Score[4] = {INT_MAX,INT_MAX,INT_MAX,INT_MAX};

    //4、根据勾股定理获得分数
    for(int i = 0;i < 4;i++)
    {
        //判断那个点在不在蛇身上？如果没有在蛇身上
        if(!isOnSnake(dir[i])&&head_find(snake,dir[i]))
        {
            Score[i] = pow(dir[i].first-foodx,2)+pow(dir[i].second-foody,2);
        }
    }
    //5、定义一个  上->72 下->80 左->75 右->77
    int dirToNum[4] = {72,80,75,77};
    //6、找到Score中4个数中最小的那个
    int Min = INT_MAX;
    for(int i = 0;i < 4;i++)
        Min = min(Min,Score[i]);
    //找到最小的那个的下标
    for(int i = 0;i < 4;i++)
        if(Min==Score[i])
            return dirToNum[i];

    return 77;
}


//是否会进入出不来的情况，测试函数，不用理会
bool head_find(deque<pair<short,short> > _snake,pair<short,short> dir)
{
    short Count = 0;
    //向右
    for(int i = dir.first;i<=25;i++)
    {
        bool breakIndex = false;
        for(auto &j:_snake)
        {
            if(i==j.first&&dir.second==j.second){
                ++Count;
                breakIndex = true;
                break;
            }
        }
        if(breakIndex)
            break;
    }
    //向左
    for(int i = dir.first;i>=0;i--)
    {
        bool breakIndex = false;
        for(auto &j:_snake)
        {
            if(i==j.first&&dir.second==j.second){
                ++Count;
                breakIndex = true;
                break;
            }
        }
        if(breakIndex)
            break;
    }
    //向下
    for(int i = dir.second;i<=25;i++)
    {
        bool breakIndex = false;
        for(auto &j:_snake)
        {
            if(dir.first==j.first&&i==j.second){
                ++Count;
                breakIndex = true;
                break;
            }
        }
        if(breakIndex)
            break;
    }
    //向上
    for(int i = dir.second;i>=0;i--)
    {
        bool breakIndex = false;
        for(auto &j:_snake)
        {
            if(dir.first==j.first&&i==j.second){
                ++Count;
                breakIndex = true;
                break;
            }
        }
        if(breakIndex)
            break;
    }
    return Count!=4;
}

