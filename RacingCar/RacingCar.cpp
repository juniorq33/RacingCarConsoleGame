// RacingCar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"  
#include <iostream>  
#include <conio.h>  
#include <stdio.h>  
#include <stdlib.h>



DWORD WINAPI ThreadFn(LPVOID vpParam);
void gotoxy(int x, int y);
void drawp(int x, int y);
void drawc(int x, int y);
void resetb();
int getr();
char b;
int track[6][16];
int g = 0, gameOn = 1, l = 0, r;
int score = 1, level = 1, dela = 101;
using namespace std;


int main() {
	DWORD qThreadID;
	HANDLE hThread = CreateThread(0, 0, ThreadFn, 0, 0, &qThreadID);
	gotoxy(7, 2); 
	cout << "CONTROLS"; 
	gotoxy(7, 3); 
	cout << "========"; 
	gotoxy(7, 4); 
	cout << "[A]=LEFT"; 
	gotoxy(7, 5); 
	cout << "[D]=RIGHT";


	for (int i = 5; i >= 0; i--) 
	{
		gotoxy(7, 7); 
		cout << i; 
		gotoxy(14, 14); 
		Sleep(1000);
	}

	system("cls");



	while (gameOn) {
		gotoxy(14, 4);
		cout << "SCORE:" << score;
		gotoxy(14, 5);
		cout << "LEVEL:" << level;
		resetb();
		drawc(r, g);
		drawc(l, 12);


		for (int j = 0; j < 16; j++)
		{
			gotoxy(4, j + 1);
			cout << "i";
			gotoxy(5, j + 1);

			for (int i = 0; i < 6; i++)
			{
				if (track[i][j] == 1)
				{
					cout << "O";
				}
				else
				{
					cout << " ";
				}
			}

			gotoxy(11, j + 1);
			cout << "i";

			if (g >= 12 & l == r)
			{
				gameOn = 0;
			}
		}


		g++;
		if (g == 15)
		{
			g = -4;
			r = getr();
			score++;
		}
		if (score % 5 == 0 & (g == 15 | g == -4))
		{
			level++;
			dela = dela - 10;

			if (dela < 0)
			{
				gotoxy(14, 4);
				cout << "YOU WIN!" << endl;
				gameOn = 0;
			}

			
		}

		Sleep(dela);
	}//end while 

	 // Close the handle to the thread  
	if (dela>0) 
	{ 
		gotoxy(14, 4); 
		cout << "GAME OVER" << endl; 
	}


	CloseHandle(hThread);
	_getch();
	return 0;
}


DWORD WINAPI ThreadFn(LPVOID vpParam)
{
	while(1) 
	{
		b = _getch();

		if (b == 'a') 
		{ 
			l = 0; 
		}
		else if (b == 'd') 
		{ 
			l = 3; 
		}
	}

	return 0;
}


//get windows position x y
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//reset track
void resetb()
{
	for (int j = 0; j<16; j++) 
	{
		for (int i = 0; i<6; i++) 
			{ 
				track[i][j] = 0; 
			}
	}
}



void drawp(int x, int y)
{
	if (x >= 0 & x<6 & y >= 0 & y<16) 
	{ 
		track[x][y] = 1; 
	}
}


//draw car
void drawc(int x, int y)
{
	drawp(1 + x, 0 + y);
	drawp(0 + x, 1 + y); drawp(1 + x, 1 + y); drawp(2 + x, 1 + y);
	drawp(1 + x, 2 + y);
	drawp(0 + x, 3 + y); drawp(1 + x, 3 + y); drawp(2 + x, 3 + y);
}



int getr()
{
	int n;
	if (rand() % 2 == 0)
	{
		n = 0;
	}
	else
	{
		n = 3;
	}
	return n;
}

