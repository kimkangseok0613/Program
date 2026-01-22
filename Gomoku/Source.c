#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define DRAW_WHITE_STONE printf("●");
#define DRAW_BLACK_STONE printf("○");

int Position(int x, int y)
{
	COORD position = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int drawStone(int x, int y,int count)
{	
		Position(2 + 2 * x, 1 + y);
		if (count % 2 == 1)
		{
			DRAW_WHITE_STONE
				
		}
		else
		{
			DRAW_BLACK_STONE
				
		}
		
}

int drawMap()
{
	Position(4, 1);
	for (int i = 0; i < 19; i++)
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
	for (int i = 0; i < 19; i++)
	{
		printf("%d\n", i + 1);
	}

	for (int i = 0; i < 19; i++)
	{
		Position(4, 2 + i);

		for (int j = 0; j < 19; j++)
		{			
			printf("┼ ");	
		}
		printf("\n");
	}
}

int main()
{
	// printf("규칙");
	// _getch();
	// system("cls");
	// 

	char key = 0;
	int x=0;
	int y=0;
	int count = 1;

	drawMap();

	while (1)
	{
		int x, y;
		Position(0, 22);
		if (count % 2 == 1)
		{
			printf("백의 차례입니다.\n");
		}
		else
		{
			printf("흑의 차례입니다.\n");
		}
		printf("x y의 값을 입력해주세요.[x y]\n");
		scanf_s("%d %d", &x,&y);
		printf("x : %d, y : %d", x, y);

		if (x > 0 && y > 0 && x < 20 && y < 20)
		{
			drawStone(x, y, count);
			count += 1;
		}
		else
		{
			printf("다시 입력해주세요.");
		}
	}
}