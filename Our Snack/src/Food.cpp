#include "Food.h"
#include "Snake.h"
#include "Tool.h"
#include <deque>
#include "conio.h"
#include<windows.h>
#include "stdio.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
Food::Food()
{

}

Food::~Food()
{
    //dtor
}
void Food::print()
{
    SetCursorPosition(foodx,foody);
        cout<<"¡ñ";
}
