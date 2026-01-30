#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define SIZE 15
#define BLACK 1
#define WHITE 2
#define SPACE 0

int board[SIZE][SIZE] = { 0 };

int play();

int initialize()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[j][i] = SPACE;
        }
    }
    return 0;
}

int position(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    return 0;
}

int mapX(int x) { return 4 + 2 * x; }
int mapY(int y) { return 2 + y; }

int drawMap()
{
    position(4, 1);
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
        position(1, mapY(i));

        printf("%2d", i + 1);
    }

    for (int i = 0; i < SIZE; i++)
    {
        position(4, mapY(i));

        for (int j = 0; j < SIZE; j++)
        {
            printf("┼ ");
        }
    }
    return 0;
}

int drawStone(int x, int y, int count)
{
    position(mapX(x), mapY(y));

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
    printf("1. 흑돌이 중앙(8,8)에 돌을 놓은 상태로 번갈아가며 돌을 둡니다.\n\n");
    printf("2. 가로, 세로, 대각선으로 5개를 먼저 일직선으로 연결하면 승리합니다.\n\n");
    printf("[금수]\n");
    printf("[흑돌은 33, 44, 6목을 둘 수 없다.]\n\n");
    printf("3 3 : 연결된 열린3이 동시에 두 개 이상 만들어지는 수\n\n");
    printf("4 4 : 연결된 4가 동시에 두 개 이상 만들어지는 수\n\n");
    printf("6목 : 6개 이상의 돌이 일렬로 나란히 놓이는 것.\n\n");
    printf("[Enter] 키를 눌러 메뉴로 돌아갑니다.");
    _getch();
    return 0;
}

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
            printf("\n1~3 사이 숫자를 입력하세요. [Enter]");
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
    int moveX[4] = { 1, 0, 1, 1 };
    int moveY[4] = { 0, 1, 1, -1 };

    for (int m = 0; m < 4; m++)
    {
        int count = 1;

        for (int i = 1; i < 5; i++)
        {
            int nextX = x + moveX[m] * i;
            int nextY = y + moveY[m] * i;
            if (nextX < 0 || nextY < 0 || nextX >= SIZE || nextY >= SIZE) break;
            if (board[nextY][nextX] != color) break;
            count++;
        }

        for (int i = 1; i < 5; i++)
        {
            int nextX = x - moveX[m] * i;
            int nextY = y - moveY[m] * i;
            if (nextX < 0 || nextY < 0 || nextX >= SIZE || nextY >= SIZE) break;
            if (board[nextY][nextX] != color) break;
            count++;
        }

        if (count >= 5) return 1;
    }
    return 0;
}

int countLine(int x, int y, int moveX, int moveY)
{
    int count = 0;
    int nextX = x + moveX;
    int nextY = y + moveY;

    while (nextX >= 0 && nextY >= 0 && nextX < SIZE && nextY < SIZE && board[nextY][nextX] == BLACK)
    {
        count++;
        nextX += moveX;
        nextY += moveY;
    }
    return count;
}

int isOpen(int x, int y)
{
    return (x >= 0 && y >= 0 && x < SIZE && y < SIZE && board[y][x] == SPACE);
}

int isOpenThree(int x, int y, int moveX, int moveY)
{
    int left = countLine(x, y, -moveX, -moveY);
    int right = countLine(x, y, moveX, moveY);
    if (left + right != 2) return 0;    

    int leftX = x - moveX * (left + 1);
    int leftY = y - moveY * (left + 1);
    int rightX = x + moveX * (right + 1);
    int rightY = y + moveY * (right + 1);

    return isOpen(leftX, leftY) && isOpen(rightX, rightY);
}

int isOpenFour(int x, int y, int moveX, int moveY)
{
    int left = countLine(x, y, -moveX, -moveY);
    int right = countLine(x, y, moveX, moveY);
    if (left + right != 3) return 0;

    int leftX = x - moveX * (left + 1);
    int leftY = y - moveY * (left + 1);
    int rightX = x + moveX * (right + 1);
    int rightY = y + moveY * (right + 1);

    return isOpen(leftX, leftY) || isOpen(rightX, rightY);
}

int cantPlace(int x, int y)
{
    int threeStone = 0;
    int fourStone = 0;
    int spaceThree = 0;

    int moveX[4] = { 1, 0, 1, 1 };
    int moveY[4] = { 0, 1, 1, -1 };

    board[y][x] = BLACK;

    for (int m = 0; m < 4; m++)
    {
        if ((countLine(x, y, moveX[m], moveY[m]) + countLine(x, y, -moveX[m], -moveY[m]) + 1)>=6)
        {
            board[y][x] = SPACE;
            return 1;
        }

        if (isOpenThree(x, y, moveX[m], moveY[m]))threeStone++;
        if (isOpenFour(x, y, moveX[m], moveY[m]))fourStone++;
    }

    board[y][x] = SPACE;

    if (threeStone >= 2)return 1;
    if (fourStone >= 2)return 1;

    return 0;
}

int printResult(int count)
{
    position(0, 20);
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

    position(0, 22);
    printf("\nPress 1. 게임을 다시 시작합니다.\n");
    printf("Any key. 메뉴로 돌아갑니다.\n\n");
    printf("선택: ");

    if (scanf_s("%d", &a) != 1)
    {
        while (getchar() != '\n');
        return 0;
    }

    if (a == 1)
    {
        system("cls");
        play();
    }

    return 0;
}

int play()
{
    int x, y;
    int count = 1;

    drawMap();

    drawStone(7, 7,count);
    count += 1;

    while (1)
    {
        position(0, 17);
        printf("                                          \n                                          \r");

        position(0, 18);
        if (count % 2 == 1)
        {
            printf("흑의 차례입니다.\n");
        }
        else
        {
            printf("백의 차례입니다.\n");
        }
        printf("x y 값을 입력하세요 (1~15)\n");
        printf("\r                                                  \r");

        if (scanf_s("%d %d", &x, &y) != 2)
        {
            position(0, 20);
            printf("숫자 두 개를 입력해주세요! [Enter]");
            while (getchar() != '\n');
            _getch();
            continue;
        }
        while (getchar() != '\n');

        x -= 1; y -= 1;

        if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
        {
            position(0, 20);
            printf("범위를 벗어났습니다! [Enter]");
            _getch();
            continue;
        }

        if (board[y][x] != SPACE)
        {
            position(0, 20);
            printf("이미 둔 자리입니다! [Enter]");
            _getch();
            continue;
        }

        if (count % 2 == 1 && cantPlace(x, y))
        {
            position(0, 20);
            printf("금수입니다. 다시 두세요. [Enter]");
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

        //count++;
    }
}

int consoleSize()
{
    system("mode con: cols=80 lines=28");
}

int main()
{
    consoleSize();

    printMenu();

    return 0;
}