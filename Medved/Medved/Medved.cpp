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

const int HUNTERS_COUNT = 4;
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
void Render(int bx, int by, char bs, int tx, int ty, char ts, int* hx, int* hy, char hs) {
	gotoxy(0, 0);
	map[by * WIDTH + bx] = bs;
	map[ty * WIDTH + tx] = ts;
	for (int i = 0; i < HUNTERS_COUNT; i++)
	{
		map[hy[i] * WIDTH + hx[i]] = hs;
	}

	std::cout << map;

	map[by * WIDTH + bx] = ' ';
	map[ty * WIDTH + tx] = ' ';
	for (int i = 0; i < HUNTERS_COUNT; i++)
	{
		map[hy[i] * WIDTH + hx[i]] = ' ';
	}


	
}

struct Character {
	int dir = REST;
	char symbol;
	int x;
	int y;
};



int main()
{
#pragma region Characters
	Character bear;
	bear.x = WIDTH / 2;
	bear.y = HEIGHT / 2;
	bear.symbol = 'O';

	Character teddy;
	teddy.x = bear.x + 2;
	teddy.y = bear.y + 2;
	teddy.symbol = 'o';

	Character hunter[4];
	hunter->symbol = '*';
	hunter[0].x = 1;
	hunter[0].y = 1;
	hunter[1].x = WIDTH - 3;
	hunter[1].y = HEIGHT - 2;
	hunter[2].x = 1;
	hunter[2].y = HEIGHT - 2;
	hunter[3].x = WIDTH - 3;
	hunter[3].y = 1;

#pragma endregion

	int* hunters_x = new int[HUNTERS_COUNT];
	int* hunters_y = new int[HUNTERS_COUNT];
	int time = clock();
	int gametime = 0;
	while (isRunning) {
		bear.dir = Listener();
		if ((clock() - time) / CLOCKS_PER_SEC >= 0.2) {

			for (int i = 0; i < HUNTERS_COUNT; i++)
			{
				hunters_x[i] = hunter[i].x;
				hunters_y[i] = hunter[i].y;
			}

			Movement(bear.dir, bear.x, bear.y);
			time = clock();
			if (gametime % 3 == 0) {
				ChaserMovement(teddy.x, teddy.y, bear.x, bear.y);
			}
			if (gametime % 2 == 0) {

				for (int i = 0; i <	HUNTERS_COUNT ; i++)
				{
					ChaserMovement(hunter[i].x, hunter[i].y, teddy.x, teddy.y);
				}
					

			}
			Render(bear.x, bear.y, bear.symbol, teddy.x, teddy.y, teddy.symbol, hunters_x, hunters_y, hunter->symbol);
			++gametime;

			if (hunter->x == teddy.x && hunter->y == teddy.y) {
				isRunning = false;
			}
		}
	}
	gotoxy(1, HEIGHT + 2);
	std::cout << "GAME OVER!" << std::endl;
}


