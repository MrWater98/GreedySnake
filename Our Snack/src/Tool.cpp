#include "Tool.h"
#include "windows.h"
void HideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //����һ����Ϣ����
    CONSOLE_CURSOR_INFO cursorInfo;
    //��ȡ�޸�Ȩ��
    GetConsoleCursorInfo(handle,&cursorInfo);
    //����Ϊ������
    cursorInfo.bVisible = false;
    //���������
    SetConsoleCursorInfo(handle,&cursorInfo);
}

void SetCursorPosition(const int x,const int y)
{
    //�½�������̨λ���������
    COORD position;
    //��ӡ����λ��Ϊλ��*2
    position.X = 2*x;//2*x
    position.Y = y;
    //��ȡ����̨��������Ȩ�ޣ�
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //���ÿ���̨���λ�õ�
    SetConsoleCursorPosition(handle,position);
}
void SetColor(int colorID)//�����ı���ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
