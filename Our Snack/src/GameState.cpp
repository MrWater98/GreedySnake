#include "GameState.h"
#include"Map.h"
#include"Snake.h"
#include"Tool.h"
#include<iostream>
#include<windows.h>
#include<stdio.h>
#include"Food.h"
using namespace std;
GameState::GameState()
{
    changeGameState(STARTINTERFACE);
}

GameState::~GameState()
{
    //dtor
}
void GameState::changeGameState(GameManager gameManager)
{
    if(gameManager==STARTINTERFACE)
    {
        cout<<"1.单人游戏"<<endl;
        cout<<"2.AI模式"<<endl;
        cout<<"3.退出游戏"<<endl;
        int i;cin>>i;system("cls");
        changeGameState(SINGLEPLAY);
    }
    if(gameManager==SINGLEPLAY)
    {
        Map _map;
        Snake snake;
        Food food;
        snake.print();
        snake.printFood();
        Sleep(1000);
        snake.walk();
        Sleep(1000);
        system("cls");
        changeGameState(STARTINTERFACE);
    }
    getchar();
}
