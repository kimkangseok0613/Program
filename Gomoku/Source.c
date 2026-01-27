#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define SIZE 15
#define BLACK 1
#define WHITE 2
#define SPACE 0

int board[SIZE][SIZE] = { 0 };

int initialize()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = SPACE;   // 인덱스 순서 통일 (i=row, j=col)
        }
    }
    return 0;
}

int Position(int x, int y)
{
    COORD pos = { x, y };
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
    return 0;
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
    return 0;
}

int printRule()
{
    printf("[규칙]\n\n");
    printf("1. 흑(선공)과 백(후공)이 번갈아가며 돌을 둡니다.\n\n");
    printf("2. 가로, 세로, 대각선으로 5개를 먼저 만드는 쪽이 승리합니다.\n\n");
    printf("[Enter] 키를 눌러 메뉴로 돌아갑니다.");
    _getch();
    return 0;
}

int play();

int printMenu()
{
    int input;

    while (1)
    {
        system("cls");
        printf("[오목]\n\n");
        printf("1. 게임 시작\n\n");
        printf("2. 게임 규칙\n\n");
        printf("3. 게임 종료\n\n");
        printf("선택: ");

        if (scanf_s("%d", &input) != 1)
        {
            while (getchar() != '\n');
            printf("\n1~3 사이 숫자를 입력하세요.\n[Enter]");
            _getch();
            continue;
        }
        while (getchar() != '\n');

        switch (input)
        {
        case 1:
            system("cls");
            play();
            break;

        case 2:
            system("cls");
            printRule();
            break;

        case 3:
            return 0;

        default:
            printf("\n잘못된 선택입니다. [Enter]");
            _getch();
            break;
        }
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

        // 한 방향으로
        for (int i = 1; i < 5; i++)
        {
            int nextX = x + dx[d] * i;
            int nextY = y + dy[d] * i;
            if (nextX < 0 || nextY < 0 || nextX >= SIZE || nextY >= SIZE) break;
            if (board[nextY][nextX] != color) break;
            count++;
        }

        // 반대 방향으로
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
    Position(0, 20);
    if (count % 2 == 1)
    {
        printf("\n흑 승리! [Enter]\n");
    }
    else
    {
        printf("\n백 승리! [Enter]\n");
    }
    return 0;
}

int replay()
{
    int a = 0;

    Position(0, 22);
    printf("\n1. 다시 하기\n");
    printf("2. 메뉴로 돌아가기\n");
    printf("선택: ");

    scanf_s("%d", &a);
    while (getchar() != '\n');

    if (a == 1)
    {
        system("cls");
        play();
    }
    // 2번 또는 잘못된 입력 → 그냥 return → 메뉴로 복귀
    return 0;
}

int play()
{
    int x, y;
    int count = 1;

    drawMap();

    while (1)
    {
        // 이전 메시지 영역 지우기
        Position(0, 17);
        printf("                                          \n                                          \r");

        Position(0, 18);
        if (count % 2 == 1)
        {
            printf("흑의 차례입니다.\n");
        }
        else
        {
            printf("백의 차례입니다.\n");
        }
        printf("x y 값을 입력하세요 (1~15)\n");
        printf("\r                                      \r");

        if (scanf_s("%d %d", &x, &y) != 2)
        {
            Position(0, 20);
            printf("숫자 두 개를 입력해주세요! [Enter]");
            while (getchar() != '\n');
            _getch();
            continue;
        }
        while (getchar() != '\n');

        x -= 1; y -= 1;

        if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
        {
            Position(0, 20);
            printf("범위를 벗어났습니다! [Enter]");
            _getch();
            continue;
        }

        if (board[y][x] != SPACE)
        {
            Position(0, 20);
            printf("이미 둔 자리입니다! [Enter]");
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
            return 0;
        }

        count++;
    }
}

int main()
{
    printMenu();
    return 0;
}