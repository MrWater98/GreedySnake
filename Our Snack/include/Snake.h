#ifndef SNAKE_H
#define SNAKE_H
#include<iostream>
#include<deque>
#include<map>
using namespace std;
class Snake
{
    public:
        Snake();
        virtual ~Snake();
        deque<pair<short,short> > snake;
        int foodx;
        int foody;
        int direction = 77;
        //��foodx��foodyд��pair<short,short> food;
        bool isOnSnake(pair<short,short> p);
        bool FindTail(pair<short,short> curPos);
        map<pair<short,short>,bool> revSnake;
        int makeScore();
        int getScore();
        void print();
        void printFood();
        void foodCreate();
        //��printFood��foodCreate�ϲ�
        //int AIWalk(deque<pair<short,short> &snake,pair<short,short> food);
        void walk();
        bool check();
    protected:

    private:
};

#endif // SNAKE_H
