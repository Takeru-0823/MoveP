#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

const enum OBJECT
{
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_PLAYER,
	OBJ_GOAL
};

const int MAP_W = 8;
const int MAP_H = 6;

const char MAP_A[MAP_H][MAP_W + 1] =
{
	"########",
	"#      #",
	"#   P# #",
	"# #    #",
	"#G     #",
	"########"

};

void mainLoop();
void initialize(int state[MAP_H][MAP_W + 1], int width, int height, const char* stage);
void showMoveCount(int moveNum);
void drow(const int state[MAP_H][MAP_W + 1], int width, int height);
void update(int state[MAP_H][MAP_W + 1], char input, int width, int height, int* moveNum, bool& goal);
char moveInput();

//void drow2(void)
//{
//	for (int y = 0; y < MAP_H; ++y)
//	{
//		for (int x = 0; x < MAP_W; ++x)
//		{
//			if (MAP_A[y][x] == '#') cout << '#';
//			if (MAP_A[y][x] == ' ') cout << ' ';
//			if (MAP_A[y][x] == 'P') cout << 'P';
//			if (MAP_A[y][x] == 'G') cout << 'G';
//		}
//		cout << endl;
//	}
//}


int main()
{
	//for (int y = 0; y < MAP_H; ++y)
	//{
	//	for (int x = 0; x < MAP_W; ++x)
	//	{
	//		cout << y << x;
	//		cout << (unsigned int)&MAP_A[y][x] << endl;
	//	}
	//}
	//cout << MAP_A[1][0] << endl;

	mainLoop();
}

void mainLoop()
{
	int moveNum = 0;
	bool goal = false;

	int state[MAP_H][MAP_W + 1];

	initialize(state, MAP_W, MAP_H, &MAP_A[0][0]);

	while (true)
	{
		showMoveCount(moveNum);
		drow(state, MAP_W, MAP_H);

		if (goal)
		{
			break;
		}
		else if (moveNum == 15)
		{
			break;
		}

		update(state, moveInput(), MAP_W, MAP_H, &moveNum, goal);

	}

}

void initialize(int state[MAP_H][MAP_W + 1], int width, int height, const char* stage)
{
	const char* d = stage;

	int x = 0;
	int y = 0;

	while (y < height)
	{
		//cout << y;
		//cout << x;
		//cout << (unsigned int)d << endl;


		int t = 0;
		switch (*d)
		{
		case '#': t = OBJ_WALL;
			break;
		case ' ': t = OBJ_SPACE;
			break;
		case 'P': t = OBJ_PLAYER;
			break;
		case 'G': t = OBJ_GOAL;
			break;
		}
		++d;

		state[y][x] = t;
		++x;

		if (x > width)
		{
			++y;
			x = 0;
		}
	}
}

void showMoveCount(int moveNum)
{
	cout << "移動回数:" << moveNum << " 回" << endl;
}

void drow(const int state[MAP_H][MAP_W + 1], int width, int height)
{
	const char font[] = { ' ', '#', 'P', 'G' };

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int o = state[y][x];
			cout << font[o];
		}
		cout << endl;
	}
}

void update(int state[MAP_H][MAP_W + 1], char input, int width, int height, int* moveNum, bool& goal)
{
	int dx = 0;
	int dy = 0;

	switch (input)
	{
	case 'a': dx = -1;
		break;
	case 'd': dx = 1;
		break;
	case 'w': dy = -1;
		break;
	case 's':dy = 1;
		break;
	}

	int iy = -1;
	int ix = -1;


	for (iy = 0; iy < height; ++iy)
	{
		for (ix = 0; ix < width; ++ix)
		{
			if (state[iy][ix] == OBJ_PLAYER)
			{
				break;
			}
		}

		if (state[iy][ix] == OBJ_PLAYER)
		{
			break;
		}
	}

	int tx = ix + dx;
	int ty = iy + dy;

	if (tx < 0 || ty < 0 || tx >= width || ty >= height)
	{
		return;
	}

	if (state[ty][tx] == OBJ_SPACE)
	{
		state[ty][tx] = OBJ_PLAYER;
		state[iy][ix] = OBJ_SPACE;
		(*moveNum)++;

		if (*moveNum == 15)
		{
			cout << "GAME OVER!" << endl;
			return;
		}
	}
	else if (state[ty][tx] == OBJ_GOAL)
	{
		state[ty][tx] = OBJ_PLAYER;
		state[iy][ix] = OBJ_SPACE;
		(*moveNum)++;

		goal = true;
		cout << "GOAL!" << endl;
		return;
	}

}

char moveInput()
{
	cout << "a:left d:right w:up s:down" << endl;
	char input;
	cin >> input;

	return input;
}