#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define DRAW_WHITE_STONE printf("●");
#define DRAW_BLACK_STONE printf("○");
#define MAP_X_1 2 + 2 * x
#define MAP_Y_1 1 + y
#define SIZE 15
#define BLACK 1
#define WHITE 2

int board[SIZE][SIZE] = { 0 };

int Position(int x, int y)
{
	COORD position = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	return 0;
}

int drawStone(int x, int y,int count)
{
	Position(MAP_X_1, MAP_Y_1);
	if (count % 2 == 1)
	{
		DRAW_BLACK_STONE // 흑
			board[x][y] = BLACK;
	}
	else
	{
		DRAW_WHITE_STONE // 백
			board[x][y] = WHITE;
	}
	return 0;
}

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
	printf("\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\n", i + 1);
	}

	for (int i = 0; i < SIZE; i++)
	{
		Position(4, 2 + i);

		for (int j = 0; j < SIZE; j++)
		{			
			printf("┼ ");
		}
		printf("\n");
	}
	return 0;
}

int main()
{
	 // printf("[오목]\n\n");
	 // printf("1. 흑과 백이 번갈아가면서 돌을 둔다.\n\n");
	 // printf("2. 한쪽이 가로, 세로, 대각선으로 5개를 연결하면 게임 종료\n\n");
	 // printf("[Enter] 게임 시작");
	 // _getch();
	 // system("cls");
	 

	int x=0;
	int y=0;
	int count = 1;

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
		printf("\r                            \r");
		scanf_s("%d %d", &x,&y);
		printf("x : %d, y : %d           ", x, y);

		if (x > 0 && y > 0 && x < SIZE+1 && y < SIZE+1)
		{
			if (board[x][y] != 0)
			{
				printf("\r이미 돌이 놓여있습니다! [Enter]        \r");
				_getch();
				printf("                                    ");
				continue;
			}
			drawStone(x, y, count);
			count += 1;
		}
		else
		{
			printf("\r다시 입력해주세요.[Enter]                       \r");
			_getch();
			printf("                                        ");
		}
	}
}