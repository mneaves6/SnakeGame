// SnakeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool boolGameOver;

const int INTWIDTH = 20;
const int INTHEIGHT = 20;
int intX, intY, intFruitX, intFruitY;
int intTailX[100], intTailY[100];
int intNTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void voidSetup()
{
	boolGameOver = false;
	dir = STOP;
	intX = INTWIDTH / 2;
	intY = INTHEIGHT / 2;
	intFruitX = rand() % INTWIDTH;
	intFruitY = rand() % INTHEIGHT;
}

void voidDraw()
{
	system("cls"); //Linux: system("clear");
	for (int intI = 0; intI < INTWIDTH + 2; intI++)
		cout << "#";
	cout << endl;

	for (int intI = 0; intI < INTHEIGHT; intI++)
	{
		for (int intJ = 0; intJ < INTWIDTH; intJ++)
		{
			if (intJ == 0)
				cout << "#";
			if (intI == intY && intJ == intX)
				cout << "O";
			else if (intI == intFruitY && intJ == intFruitX)
				cout << "F";
			else
			{
				bool boolPrint = false;
				for (int intK = 0; intK < intNTail; intK++)
				{
					if (intTailX[intK] == intJ && intTailY[intK] == intI)
					{
						cout << "o";
						boolPrint = true;
					}
				}
				if (!boolPrint)
					cout << " ";
			}

			if (intJ == INTWIDTH - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int intI = 0; intI < INTWIDTH + 2; intI++)
		cout << "#";
}

void voidInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			boolGameOver = true;
			break;
		default:
			break;
		}
	}
}

void voidLogic()
{
	int intPrevX = intTailX[0];
	int intPrevY = intTailY[0];
	int intPrevX2, intPrevY2;
	intTailX[0] = intX;
	intTailY[0] = intY;
	for (int intI = 1; intI < intNTail; intI++)
	{
		intPrevX2 = intTailX[intI];
		intPrevY2 = intTailY[intI];
		intTailX[intI] = intPrevX;
		intTailY[intI] = intPrevY;
		intPrevX = intPrevX2;
		intPrevY = intPrevY2;
	}
	switch (dir)
	{
	case LEFT:
		intX--;
		break;
	case RIGHT:
		intX++;
		break;
	case UP:
		intY--;
		break;
	case DOWN:
		intY++;
		break;
	}
	if (intX > INTWIDTH || intX < 0 || intY > INTHEIGHT || intY < 0)
		boolGameOver = true;
	for (int intI = 0; intI < intNTail; intI++)
	{
		if (intTailX[intI] == intX && intTailY[intI] == intY)
			boolGameOver = true;
	}
	if (intX == intFruitX && intY == intFruitY)
	{
		intFruitX = rand() % INTWIDTH;
		intFruitY = rand() % INTHEIGHT;
		intNTail++;
	}
}

int main()
{
	voidSetup();
	while (!boolGameOver)
	{
		voidDraw();
		voidInput();
		voidLogic();
		Sleep(50); //Linux: sleep(50);
	}
    return 0;
}

