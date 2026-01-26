#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define SIZE 15
#define BLACK 1
#define WHITE 2

int board[SIZE][SIZE] = { 0 };

int Position(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int mapX(int x) { return 4 + 2 * x; }
int mapY(int y) { return 2 + y; }

int drawMap()
{
	Position(4, 1);
	for (int i = 0; i < SIZE; i++)
	{
		if (i < 9)
		{
			printf("%d ", i + 1);
		}
		else
		{
			printf("%d", i + 1);
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		Position(1, mapY(i));

		printf("%d", i + 1);
	}

	for (int i = 0; i < SIZE; i++)
	{
		Position(4, mapY(i));

		for (int j = 0; j < SIZE; j++)
		{
			printf("┼ ");
		}
	}
}

int drawStone(int x, int y, int count)
{
	Position(mapX(x), mapY(y));

	if (count % 2 == 1)
	{
		printf("○"); // 흑
		board[y][x] = BLACK;
	}
	else
	{
		printf("●"); // 백
		board[y][x] = WHITE;
	}
}

int main()
{
	int x, y;
	int count = 1;

	// printf("[오목]\n\n");
	// printf("1. 흑과 백이 번갈아가면서 돌을 둔다.\n\n");
	// printf("2. 한쪽이 가로, 세로, 대각선으로 5개를 연결하면 게임 종료\n\n");
	// printf("[Enter] 게임 시작");
	// _getch();
	// system("cls");

	drawMap();

	while (1)
	{
		Position(0, 18);
		if (count % 2 == 1)
		{
			printf("흑의 차례입니다.\n");
		}
		else
		{
			printf("백의 차례입니다.\n");
		}
		printf("x y 값을 입력해주세요.[x y]\n");
		printf("\r                                 \r");

		scanf_s("%d %d", &x,&y);

		x-=1; y-=1;

		if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
		{
			Position(0, 20);
			printf("범위를 벗어났습니다! [Enter]");
			_getch();
			continue;
		}
		if (board[y][x] !=0)
		{
			Position(0, 20);
			printf("이미 돌이 놓여있습니다! [Enter]");
			_getch();
			continue;
		}
		
		drawStone(x, y, count);

		count++;
	}
}