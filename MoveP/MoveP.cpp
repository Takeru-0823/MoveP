#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

const enum OBJECT
{
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_PLAYER,
	OBJ_GOAL,
	OBJ_WARP
};

const int MAP_W = 8;
const int MAP_H = 6;

const char MAP_A[MAP_H][MAP_W + 1] =
{
	"########",
	"#      #",
	"#    # #",
	"# #    #",
	"#   W  #",
	"########"
};

const char MAP_B[MAP_H][MAP_W + 1] =
{
	"########",
	"#      #",
	"#  ### #",
	"#G#    #",
	"##    W#",
	"########"
};

void mainLoop();
void initialize(int state[MAP_H][MAP_W + 1], int width, int height, const char* stage);
void showMoveCount(int moveNum);
void drow(const int state[MAP_H][MAP_W + 1], int width, int height);
void update(int state[MAP_H][MAP_W + 1], char input, int width, int height, int* moveNum, bool& goal, bool& warp, const int warpX, const int warpY);
char moveInput();

int main()
{
	mainLoop();
}

void mainLoop()
{
	int moveNum = 0;
	bool goal = false;
	bool map = true;
	bool warp = false;

	int playerPosX = 4;
	int playerPosY = 2;

	int warpPosX = -1;
	int warpPosY = -1;

	int state[MAP_H][MAP_W + 1];

	initialize(state, MAP_W, MAP_H, &MAP_A[0][0]);
	state[playerPosY][playerPosX] = OBJ_PLAYER;

	while (true)
	{
		showMoveCount(moveNum);
		drow(state, MAP_W, MAP_H);

		if (goal)
		{
			break;
		}
		else if (moveNum >= 15)
		{
			break;
		}

		warp = false;
		update(state, moveInput(), MAP_W, MAP_H, &moveNum, goal, warp, warpPosX, warpPosY);

		if (warp)
		{
			if (map)
			{
				map = false;
				initialize(state, MAP_W, MAP_H, &MAP_B[0][0]);

			}
			else
			{
				map = true;
				initialize(state, MAP_W, MAP_H, &MAP_A[0][0]);
			}

			for (int y = 0; y < MAP_H; ++y)
			{
				for (int x = 0; x < MAP_W; ++x)
				{
					if (state[y][x] == OBJ_WARP)
					{
						warpPosY = y;
						warpPosX = x;
						state[y][x] = OBJ_PLAYER;
					}
				}
			}

		}

	}

}

void initialize(int state[MAP_H][MAP_W + 1], int width, int height, const char* stage)
{
	const char* d = stage;

	int x = 0;
	int y = 0;

	while (y < height)
	{
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
		case 'W': t = OBJ_WARP;
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
	cout << "移動回数:" << moveNum << " ターン目" << endl;
}

void drow(const int state[MAP_H][MAP_W + 1], int width, int height)
{
	const char font[] = { ' ', '#', 'P', 'G', 'W'};

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

void update(int state[MAP_H][MAP_W + 1], char input, int width, int height, int* moveNum, bool& goal, bool& warp, const int warpX, const int warpY)
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
		if (state[warpY][warpX] == OBJ_PLAYER)
		{
			state[ty][tx] = OBJ_PLAYER;
			state[iy][ix] = OBJ_WARP;
			(*moveNum)++;
		}
		else
		{
			state[ty][tx] = OBJ_PLAYER;
			state[iy][ix] = OBJ_SPACE;
			(*moveNum)++;
		}

		if (*moveNum >= 15)
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
	else if (state[ty][tx] == OBJ_WARP)
	{
		(*moveNum)++;
		warp = true;
	}

}

char moveInput()
{
	cout << "a:left d:right w:up s:down" << endl;
	char input;
	cin >> input;

	return input;
}
