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
#include<map>
#include<queue>
#include <time.h>
#include <cmath>
using namespace std;
//Ĭ�Ϲ��캯��
bool head_find(deque<pair<short,short> > _snake,pair<short,short> dir);
bool canfindtail = false;
Snake::Snake()
{
    snake.push_back(pair<short,short>(16,14));
    snake.push_back(pair<short,short>(15,14));
    snake.push_back(pair<short,short>(14,14));
    foodx=0;
    foody=0;//�ĳ�pair
    foodCreate();
}

Snake::~Snake()
{
    //dtor
}
void Snake::foodCreate()
{
    srand((unsigned)time(NULL));
    while(true)
    {
        bool outIndex = true;
        foodx=(rand() % 24 + 1);
        foody=(rand() % 24 + 1);
        for (auto i=snake.begin(); i!=snake.end(); i++)
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
    SetColor(4);
    cout<<"��";
    SetColor(7);
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
            cout<<"��";
            continue;
        }
        SetColor(7);
        SetCursorPosition(i.first,i.second);
        cout<<"��";
    }
    Sleep(30);
}
bool Snake::check()
{
    for (auto i=snake.begin()+1; i!=snake.end(); i++)
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
        //������ܵ�����
        /*
        if(kbhit())
        {
            //��direction��ɽ��յ����̵�ֵ
            int temp, temp2;
            temp2=getch();
            temp=getch();
            if (pow(direction-temp)!=2 && pow(direction-temp)!=8)
                direction = temp;
        }*/
        //Sleep(30);
        direction = getScore();
        //Sleep(30);
        //SetCursorPosition(30,9);
        //cout<<direction;
        switch(direction)//�˶����￴���ܲ��ܷ�װһ�£�Ū�ɾ�̬ȫ�ֺ���
        {
        //77�����ҷ���
        case 77:
            SetCursorPosition(snake.back().first,snake.back().second);
            cout<<"  ";
            snake.pop_back();
            snake.push_front(pair<short,short>(snake.front().first+1,snake.front().second));
            print();
            break;
        //����
        case 75:
            SetCursorPosition(snake.back().first,snake.back().second);
            cout<<"  ";
            snake.pop_back();
            snake.push_front(pair<short,short>(snake.front().first-1,snake.front().second));
            print();
            break;
        //�Ϸ���
        case 72:
            SetCursorPosition(snake.back().first,snake.back().second);
            cout<<"  ";
            snake.pop_back();
            snake.push_front(pair<short,short>(snake.front().first,snake.front().second-1));
            print();
            break;
        //�·���
        case 80:
            SetCursorPosition(snake.back().first,snake.back().second);
            cout<<"  ";
            snake.pop_back();
            snake.push_front(pair<short,short>(snake.front().first,snake.front().second+1));
            print();
            break;
        }
        /*
        SetCursorPosition(0,29);
        for(auto &i:snake)
        {
            cout<<i.first<<" "<<i.second<<"||";
        }
        */
    }
    system("PAUSE");
    Sleep(1000);
    system("cls");
    SetCursorPosition(12,12);
    cout << "Game Over" << endl;
}
bool Snake::isOnSnake(pair<short,short> p)
{
    if(p.first==0||p.first==25||p.second==0||p.second==25)
        return true;
    for(auto &i:snake)
    {
        if(p==i)
            return true;
    }
    return false;
}
int Snake::getScore()
{
    //1����ȡ��ͷ
    pair<short,short> snakeHead = snake.front();
    //2������һ��������������
    pair<short,short> dir[4];
    //��
    dir[0] = pair<short,short>(snakeHead.first,snakeHead.second-1);
    //��
    dir[1] = pair<short,short>(snakeHead.first,snakeHead.second+1);
    //��
    dir[2] = pair<short,short>(snakeHead.first-1,snakeHead.second);
    //��
    dir[3] = pair<short,short>(snakeHead.first+1,snakeHead.second);

    //3������һ���������� ����������
    //int Score[4]={9999999,99999999,99999999,99999999};
    int Score[4] = {INT_MAX,INT_MAX,INT_MAX,INT_MAX};

    //4�����ݹ��ɶ����÷���
    for(int i = 0; i < 4; i++)
    {
        //�ж��Ǹ����ڲ��������ϣ����û����������
        if(!isOnSnake(dir[i])&&(FindTail(dir[i])/*||head_find(snake,dir[i]))*/))
        {
            Score[i] = pow(dir[i].first-foodx,2)+pow(dir[i].second-foody,2);
        }
    }
    //5������һ��  ��->72 ��->80 ��->75 ��->77
    int dirToNum[4] = {72,80,75,77};
    //6���ҵ�Score��4��������С���Ǹ�
    int Min = INT_MAX;
    for(int i = 0; i < 4; i++)
        Min = min(Min,Score[i]);
    //�ҵ���С���Ǹ����±�
    for(int i = 0; i < 4; i++)
        if(Min==Score[i])
            return dirToNum[i];

    return 77;
}
/*
bool Snake::FindTail(pair<short,short> _curPos)
{
    bool isWalk[26][26] = {false};//�洢�Ƿ��߹���λ��
    for(int i = 0;i<=25;i++)isWalk[i][0] = true;
    for(int i = 0;i<=25;i++)isWalk[i][25] = true;
    for(int i = 0;i<=25;i++)isWalk[0][i] = true;
    for(int i = 0;i<=25;i++)isWalk[25][i] = true;

    map<short,pair<short,short> > score;//�洢��β�͵ľ�����±�
    pair<short,short> curPos = _curPos;
    pair<short,short> snakeTail = snake.back();
    int glx = snakeTail.first,gly = snakeTail.second;//Ŀ��λ�õ��±�
    score[pow(curPos.first-glx,2)+pow(curPos.second-gly,2)] = curPos;
    isWalk[_curpos.first][_curpos.second] = true;
    while(true)
    {
        int x = curPos.first,y = curPos.second;//��ǰλ�õ��±�
        if(x==glx&&y==gly)
            return true;
        SetCursorPosition(0,26);
        cout<<"                         "<<endl;
        SetCursorPosition(0,26);
        cout<<"_X:"<<x<<" _Y:"<<y<<endl;
        if(!isWalk[x+1][y]&&!isOnSnake(make_pair(x+1,y)))
        {
            score[pow(glx-(x+1),2)+pow(gly-y,2)] = make_pair(x+1,y);
            isWalk[x+1][y] = true;
        }
        if(!isWalk[x-1][y]&&!isOnSnake(make_pair(x-1,y)))
        {
            score[pow(glx-(x-1),2)+pow(gly-y,2)] = make_pair(x-1,y);
            isWalk[x-1][y] = true;
        }
        if(!isWalk[x][y+1]&&!isOnSnake(make_pair(x,y+1)))
        {
            score[pow((glx-x),2)+pow(gly-(y+1),2)] = make_pair(x,y+1);
            isWalk[x][y+1] = true;
        }
        if(!isWalk[x][y-1]&&!isOnSnake(make_pair(x,y-1)))
        {
            score[pow(glx-x,2)+pow(gly-(y-1),2)] = make_pair(x,y-1);
            isWalk[x][y-1] = true;
        }

        curPos = score.begin()->second;
        score.erase(score.begin());
        if(score.empty())
        {
            return false;
        }
    }
    return true;
}
*/
bool Snake::FindTail(pair<short,short> _curPos)
{
    bool snakePos[26][26] = {false};
    bool isWalk[25][25] = {false};
    memset(snakePos,0,sizeof(snakePos));
    memset(isWalk,0,sizeof(isWalk));
    pair<short,short> dir[8] = {make_pair(0,1),make_pair(1,0),make_pair(0,-1),
                                make_pair(-1,0),make_pair(1,1),make_pair(1,-1),make_pair(-1,1),make_pair(-1,-1)
                               };
    //pair<short,short> _dir[4] = {make_pair(0,1),make_pair(1,0),make_pair(0,-1),make_pair(-1,0)};
    pair<short,short> curPos = _curPos;
    for(auto &i : snake)
    {
        for(int j = 0; j < 8; j++)
        {
            snakePos[i.first+dir[j].first][i.second+dir[j].second] = true;
        }
    }
    for(auto &i:snake)
    {
        //if(i!=*snake.end())
        snakePos[i.first][i.second] = false;
    }
    for(int i = 0; i<=25; i++)
        snakePos[i][0] = false;
    for(int i = 0; i<=25; i++)
        snakePos[i][25] = false;
    for(int i = 0; i<=25; i++)
        snakePos[0][i] = false;
    for(int i = 0; i<=25; i++)
        snakePos[25][i] = false;
    isWalk[curPos.first][curPos.second] = true;
    bool continueWalk = true;

    //��ӡ���ݱ�
    if(kbhit())
    {
        char temp = getch();
        if(temp=='r'){
        for(int i = 0; i < 26; i++)
        {
            for(int j = 0; j < 26; j++)
            {
                SetCursorPosition(i+26,j);
                if(snakePos[i][j])
                {
                    SetColor(4);
                    cout<<snakePos[i][j];
                    SetColor(7);
                }else
                    cout<<snakePos[i][j];
            }
            cout<<endl;
        }
        }
    }


    queue<pair<short,short> > q;
    q.push(curPos);
    while(!q.empty())
    {
        curPos = q.front();
        /*
        SetCursorPosition(0,26);
        cout<<"                          ";
        SetCursorPosition(0,26);
        cout<<curPos.first<<" "<<curPos.second<<endl;
        */

        for(int i = 0; i < 4; i++)
        {
            if(snake.back()==pair<short,short>(q.front().first+dir[i].first,q.front().second+dir[i].second))
                return true;
        }
        for(int i = 0; i<4; i++)
        {
            if(snakePos[curPos.first+dir[i].first][curPos.second+dir[i].second]&&!isWalk[curPos.first+dir[i].first][curPos.second+dir[i].second])
            {
                //curPos = make_pair(curPos.first+_dir[i].first,curPos.second+_dir[i].second);

                isWalk[curPos.first+dir[i].first][curPos.second+dir[i].second] = true;
                q.push(make_pair(curPos.first+dir[i].first,curPos.second+dir[i].second));
            }
        }
        q.pop();

    }
    return false;
    /*
    pair<short,short> dir[8] = {make_pair(0,1),make_pair(1,0),make_pair(0,-1),make_pair(-1,0),
    make_pair(1,1),make_pair(-1,1),make_pair(-1,-1),make_pair(1,-1)};
    pair<short,short> _dir[4] = {make_pair(0,1),make_pair(1,0),make_pair(0,-1),make_pair(-1,0)};
    isWalk[_curPos.first][_curPos.second] = true;
    pair<short,short> curPos = _curPos;
    while(true)
    {
        for(int i = 0;i < 8;i++)
        {
            if(curPos.first+dir[i].first==snake.back().first&&curPos.second+dir[i].second==snake.back().second)
                return true;
            for(int j = 0;j < 4;j++)
            {

            }
        }
    }
    */
}

//�Ƿ��������������������Ժ������������

bool head_find(deque<pair<short,short> > _snake,pair<short,short> dir)
{
    short Count = 0;
    //����
    for(int i = dir.first; i<=25; i++)
    {
        bool breakIndex = false;
        for(auto &j:_snake)
        {
            if(i==j.first&&dir.second==j.second)
            {
                ++Count;
                breakIndex = true;
                break;
            }
        }
        if(breakIndex)
            break;
    }
    //����
    for(int i = dir.first; i>=0; i--)
    {
        bool breakIndex = false;
        for(auto &j:_snake)
        {
            if(i==j.first&&dir.second==j.second)
            {
                ++Count;
                breakIndex = true;
                break;
            }
        }
        if(breakIndex)
            break;
    }
    //����
    for(int i = dir.second; i<=25; i++)
    {
        bool breakIndex = false;
        for(auto &j:_snake)
        {
            if(dir.first==j.first&&i==j.second)
            {
                ++Count;
                breakIndex = true;
                break;
            }
        }
        if(breakIndex)
            break;
    }
    //����
    for(int i = dir.second; i>=0; i--)
    {
        bool breakIndex = false;
        for(auto &j:_snake)
        {
            if(dir.first==j.first&&i==j.second)
            {
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


