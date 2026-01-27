#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define SIZE 15
#define BLACK 1
#define WHITE 2
#define	SPACE 0

int board[SIZE][SIZE] = { 0 };

int initialize()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			board[j][i] = SPACE;
		}
	}
}

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

int printRule()
{
	printf("[오목 규칙]\n\n");
	printf("1. 흑과 백이 번갈아가면서 돌을 둔다.\n\n");
	printf("2. 한쪽이 가로, 세로, 대각선으로 5개를 연결하면 게임 종료\n\n");
	printf("[Enter] 메뉴로 돌아가기");
	_getch();
}

int printMenu()
{
	int input;
	printf("[오목]\n\n");
	printf("1. 게임 시작\n\n");
	printf("2. 게임 규칙\n\n");
	printf("3. 게임 종료\n\n");
	scanf_s("%d", &input);
	switch (input)
	{
	case 1:	system("cls"); play();
	case 2:	system("cls"); printRule(); system("cls"); printMenu();
	case 3: return 0;
	}
}

int checkWin(int x, int y)
{
	int color = board[y][x];
	int dx[4] = { 1, 0, 1, 1 };
	int dy[4] = { 0, 1, 1, -1 };

	for (int d = 0; d < 4; d++)
	{
		int count = 1;

		for (int i = 1; i < 5; i++)
		{
			int nextX = x + dx[d] * i;
			int nextY = y + dy[d] * i;
			if (nextX < 0 || nextY < 0 || nextX >= SIZE || nextY >= SIZE) break;
			if (board[nextY][nextX] != color) break;
			count++;
		}
		for (int i = 1; i < 5; i++)
		{
			int nextX = x - dx[d] * i;
			int nextY = y - dy[d] * i;
			if (nextX < 0 || nextY < 0 || nextX >= SIZE || nextY >= SIZE) break;
			if (board[nextY][nextX] != color) break;
			count++;
		}

		if (count >= 2) return 1;
	}
	return 0;
}

int printResult(int count)
{
	if (count % 2 == 1)
	{
		Position(0, 20);
		printf("\n흑 승리! [Enter]\n");
	}
	else
	{
		Position(0, 20);
		printf("\n백 승리! [Enter]\n");
	}
}

int replay()
{
	int q = 0;
	printf("\n");
	printf("1. 게임 재시작\n");
	printf("2. 메뉴로\n");
	int a = 0;
	scanf_s("%d", &a);

	switch (a)
	{
	case 1: system("cls");  play(); break;
	case 2: system("cls");  printMenu(); break;
	}
}

int play()
{
	int x, y;
	int count = 1;
	int input = 0;

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
		scanf_s("%d %d", &x, &y);

		x -= 1; y -= 1;

		if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
		{
			Position(0, 20);
			printf("범위를 벗어났습니다! [Enter]");
			_getch();
			continue;
		}
		if (board[y][x] != 0)
		{
			Position(0, 20);
			printf("이미 돌이 놓여있습니다! [Enter]");
			_getch();
			continue;
		}

		drawStone(x, y, count);

		if (checkWin(x, y))
		{
			printResult(count);
			_getch();
			initialize();
			replay();
			break;
		}

		count++;
	}
}

int main()
{
	printMenu();

	return 0;
}