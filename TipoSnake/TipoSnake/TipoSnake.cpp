#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

void setcur(int x, int y)//установка курсора на позицию  x y 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void OutPut(string SnakeMap[40][40], int Score)
{
	setcur(0, 0);
	cout << "Score: " << Score <<"(For exit press any Key)"<< endl;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			cout << SnakeMap[i][j];
		}
		cout << endl;
	}
}

int main()
{
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	int SnakeSpeed;
	int score = 0, size = 2;
	bool ex = 1;
	int Xfood = rand() % 48 + 1, Yfood = rand() % 48 + 1;
	srand(time(0));
	string Map[40][40];//y then x
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (i == 0 || i == 39)	Map[i][j] = char(254);
			else if (j == 0 || j == 39)	Map[i][j] = char(254);
			else Map[i][j] = ' ';
		}
	}
	Map[Yfood][Xfood] = '*';
	vector<int> Event(2);
	vector<int> Xcord(size); Xcord[0] = 15; Xcord[1] = 15;
	vector<int> Ycord(size); Ycord[0] = 15; Ycord[1] = 15;
	Map[Ycord[0]][Xcord[0]] = '#';
	cout << "Choose ur speed(1-Normal/2-Fast/3-Very Fast): "; cin >> SnakeSpeed;
	switch (SnakeSpeed)
	{
	case 1:SnakeSpeed = 50; cout << "U chose Normal Speed" << endl;
		break;
	case 2:SnakeSpeed = 20; cout << "U chose Fast Speed" << endl;
		break;
	case 3:SnakeSpeed = 5; cout << "U chose Very Fast Speed" << endl;
		break;
	default:
		cout << "U input wrong value so Speed was put to Normal" << endl;
		break;
	}
	cout << "____________What u pres here that will be u start movment diraction(USE ONLY:A,S,D,W)_________" << endl;
	int choice, last = 0, command = tolower(_getch());
	vector<int>Xl(2); Xl[0] = 15;
	vector<int>Yl(2); Yl[0] = 15;
	int r = 0;
	for (int i = 0; i < 11; i++)
	{
		cout << "Download: " << r << "%" << endl;
		Sleep(200);
		r += 10;
	}
	Sleep(200);
	system("cls");
	while (ex != 0)			//0-head
	{
		OutPut(Map, score);
		switch (command)
		{
		case 'a':Xl[0] = Xcord[0]; Yl[0] = Ycord[0]; Xcord[0]--;
			break;
		case 'd':Xl[0] = Xcord[0]; Yl[0] = Ycord[0]; Xcord[0]++;
			break;
		case 'w':Yl[0] = Ycord[0]; Xl[0] = Xcord[0]; Ycord[0]--;
			break;
		case 's':Yl[0] = Ycord[0]; Xl[0] = Xcord[0]; Ycord[0]++;
			break;
		default:
			ex = 0;
			break;
		}
		Sleep(SnakeSpeed);
		if (_kbhit())
		{
			command = tolower(_getch());
		}
		while (_kbhit())
		{
			_getch();
		}
		clock();
		for (int i = 1; i < size; i++)
		{
			Xl[i] = Xcord[i]; Xcord[i] = Xl[i - 1];
			Yl[i] = Ycord[i]; Ycord[i] = Yl[i - 1];
			
		};
		if (Ycord[1] == 0 || Ycord[1] == 39 || Xcord[1] == 0 || Xcord[1] == 39)
		{
			break;
		}
		if (Ycord[1] == Yfood && Xcord[1] == Xfood)
		{
			score += 10; last++;
			if (Xcord[size - 1] > Xcord[size - 2])//left
			{
				Xcord.push_back(Xcord[size - 1] - 1); Ycord.push_back(Ycord[size - 1]); Xl.push_back(Xcord[size - 1]); Yl.push_back(Xcord[size - 1]);
			}
			if (Xcord[size - 1] < Xcord[size - 2])//right
			{
				Xcord.push_back(Xcord[size - 1] + 1); Ycord.push_back(Ycord[size - 1]); Xl.push_back(Xcord[size - 1]); Yl.push_back(Xcord[size - 1]);
			}
			if (Ycord[size - 1] > Ycord[size - 2])
			{
				Ycord.push_back(Ycord[size - 1] + 1); Xcord.push_back(Xcord[size - 1]); Xl.push_back(Xcord[size - 1]); Yl.push_back(Xcord[size - 1]);
			}
			if (Ycord[size - 1] < Ycord[size - 2])
			{
				Ycord.push_back(Ycord[size - 1] - 1); Xcord.push_back(Xcord[size - 1]); Xl.push_back(Xcord[size - 1]); Yl.push_back(Xcord[size - 1]);
			}
			size++;
			Xfood = rand() % 38 + 1, Yfood = rand() % 38 + 1;
			Map[Yfood][Xfood] = '*';
		}
		Map[Ycord[0]][Xcord[0]] = '#';
		Map[Ycord[size - 1]][Xcord[size - 1]] = ' ';
		OutPut(Map, score);
		for (int i = 1; i < size; i++)
		{
			if (Xcord[0] == Xl[i] && Ycord[0] == Yl[i])
			{
				ex = 0;;
			}
		}
	}
	system("cls");
	for (int i = 0; i < 80; i++)
	{
		cout << "-";
	}cout << endl;
	cout << "\t Your score: " << score <<" (It mean "<<score/10<< " fuits)  Your game Time: " << clock() / 1000 << " Seconds" << endl;
	for (int i = 0; i < 80; i++)
	{
		cout << "-";
	}cout << endl;
	
}

