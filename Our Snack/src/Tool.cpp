#include "Tool.h"
#include "windows.h"
void HideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //定义一个信息变量
    CONSOLE_CURSOR_INFO cursorInfo;
    //获取修改权限
    GetConsoleCursorInfo(handle,&cursorInfo);
    //设置为不可视
    cursorInfo.bVisible = false;
    //最后再设置
    SetConsoleCursorInfo(handle,&cursorInfo);
}

void SetCursorPosition(const int x,const int y)
{
    //新建个控制台位置坐标的类
    COORD position;
    //打印横轴位置为位置*2
    position.X = 2*x;//2*x
    position.Y = y;
    //获取控制台处理句柄（权限）
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置控制台光标位置到
    SetConsoleCursorPosition(handle,position);
}
void SetColor(int colorID)//设置文本颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
