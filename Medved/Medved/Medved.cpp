#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

const int WIDTH = 21;
const int HEIGHT = 10;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int REST = 4;

bool isRunning = true;
char map[] =
"====================\n"
"|                  |\n"
"|                  |\n"
"|                  |\n"
"|                  |\n"
"|                  |\n"
"|                  |\n"
"|                  |\n"
"|                  |\n"
"====================\n";


void gotoxy(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

int Listener() {
	if (GetKeyState('W') & 0x8000)
	{
		return UP;
	}
	if (GetKeyState('S') & 0x8000)
	{
		return DOWN;
	}
	if (GetKeyState('A') & 0x8000)
	{
		return LEFT;
	}
	if (GetKeyState('D') & 0x8000)
	{
		return RIGHT;
	}
	else 
	{
		return REST;
	}
}
void Movement(int& dir, int& x, int& y) {
	if (dir == REST) {
		x = x;
		y = y;
	}
	if (dir == UP) {
		--y;
	}
	if (dir == DOWN) {
		++y;
	}
	if (dir == LEFT) {
		--x;
	}
	if (dir == RIGHT) {
		++x;
	}
	if (x == WIDTH - 2 || y == HEIGHT - 1 || x == 0 || y == 0) {
		isRunning = false;
	}
}
void ChaserMovement(int& x, int& y, int gx, int gy) {
	
	if (x < gx) {
		++x;
	}
	if (x > gx) {
		--x;
	}
	if (y < gy) {
		++y;
	}
	if (y > gy) {
		--y;
	}

}
void Render(int bx, int by, char bs, int tx, int ty, char ts) {
	gotoxy(0, 0);
	map[by * WIDTH + bx] = bs;
	map[ty * WIDTH + tx] = ts;
	std::cout << map;
	map[by * WIDTH + bx] = ' ';
	map[ty * WIDTH + tx] = ' ';
}

struct Character {
	int dir = REST;
	char symbol = 'O';
	int x;
	int y;
};



int main()
{
	int c_count = 2;
	int* hunters_x = new int[c_count];
	int* hunters_y = new int[c_count];

	Character bear;
	bear.x = WIDTH / 2;
	bear.y = HEIGHT / 2;

	Character teddy;
	teddy.x = bear.x + 2;
	teddy.y = bear.y + 2;
	teddy.symbol = '*';

	int time = clock();
	int gametime = 0;
	while (isRunning) {
		bear.dir = Listener();
		if ((clock() - time) / CLOCKS_PER_SEC >= 0.2) {
			Movement(bear.dir, bear.x, bear.y);
			time = clock();
			if (gametime % 2 == 0) {
				ChaserMovement(teddy.x, teddy.y, bear.x, bear.y);
			}
			Render(bear.x, bear.y, bear.symbol, teddy.x, teddy.y, teddy.symbol);
			++gametime;
		}
	}
	gotoxy(1, HEIGHT + 2);
	std::cout << "GAME OVER!" << std::endl;
}


