#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define SIZE 15 // 바둑판 15X15
#define BLACK 1 // 흑돌
#define WHITE 2 // 백돌
#define SPACE 0 // 빈곳

int board[SIZE][SIZE] = { 0 };

int play();

void initialize() // 돌 초기화
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[j][i] = SPACE;
        }
    }
}

int position(int x, int y) // 위치 변경
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    return 0;
}

// 돌 두는 기준
int mapX(int x) { return 4 + 2 * x; }
int mapY(int y) { return 2 + y; }

int drawMap() // 맵 그리기
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

int drawStone(int x, int y, int count) // 돌 그리기
{
    position(mapX(x), mapY(y));

    if (count % 2 == 1)
    {
        printf("●"); // 흑
        board[y][x] = BLACK;
    }
    else
    {
        printf("○"); // 백
        board[y][x] = WHITE;
    }
    return 0;
}

int printRule() // 규칙
{
    printf("[규칙]\n\n");
    printf("1. 흑돌이 중앙(8,8)에 돌을 놓은 상태로 번갈아가며 돌을 둡니다.\n\n");
    printf("2. 가로, 세로, 대각선으로 5개를 먼저 일직선으로 연결하면 승리합니다.\n\n\n");
    printf("[금수] 흑돌은 33, 44, 6목을 둘 수 없다.\n\n");
    printf("3 3 : 연결된 열린3이 동시에 두 개 이상 만들어지는 수\n\n");
    printf("4 4 : 연결된 4가 동시에 두 개 이상 만들어지는 수\n\n");
    printf("6목 : 6개 이상의 돌이 일렬로 나란히 놓이는 것.\n\n\n");
    printf("[Enter] 키를 눌러 메뉴로 돌아갑니다.");
    _getch();
    return 0;
}

int printMenu() // 메뉴
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
            printf("\n1~3 사이 숫자를 입력하세요. [Enter]");
            _getch();
            break;
        }
    }
}

int checkWin(int x, int y) // 승리 판별
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

        if (color == BLACK)
        {
            if (count == 5) return 1;
        }
        else
        {
            if (count >= 5) return 1;
        }
    }
    return 0;
}

int countLine(int x, int y, int moveX, int moveY) // 줄 확인
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

int isOpen(int x, int y) // 끝 부분 비어있는지 판별
{
    return (x >= 0 && y >= 0 && x < SIZE && y < SIZE && board[y][x] == SPACE);
}

int isOpenThree(int x, int y, int moveX, int moveY) // 33 판별
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

int isOpenFour(int x, int y, int moveX, int moveY) // 44 판별
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

int cantPlace(int x, int y) // 금수 판별
{
    int threeStone = 0;
    int fourStone = 0;

    int moveX[4] = { 1, 0, 1, 1 };
    int moveY[4] = { 0, 1, 1, -1 };

    board[y][x] = BLACK;

    for (int m = 0; m < 4; m++)
    {
        if ((countLine(x, y, moveX[m], moveY[m]) + countLine(x, y, -moveX[m], -moveY[m]) + 1) >= 6) // 6목 판별
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

int printResult(int count) // 결과 출력
{
    position(0, 20);
    if (count % 2 == 1)
    {
        printf("\n흑돌 승리! [Enter]\n");
    }
    else
    {
        printf("\n백돌 승리! [Enter]\n");
    }
    return 0;
}

int replay() // 게임 재시작
{
    initialize();
    int a = 0;

    position(0, 22);
    printf("\nPress 1. 게임을 다시 시작합니다.\n");
    printf("Press 2. 게임을 종료합니다.\n");
    printf("Any key. 메뉴로 돌아갑니다.\n");
    printf("\n선택: ");

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
    
    if (a == 2)
    {
        exit(0);
    }

    
    return 0;
}

int play() // 본 게임
{
    int x, y;
    int count = 1;
    char input[32];

    drawMap();

    drawStone(7, 7,count);
    count += 1;

    while (1)
    {
        position(0, 17);
        printf("%-80s", "");

        position(0, 18);
        if (count % 2 == 1)
        {
            printf("흑돌의 차례입니다.\n");
        }
        else
        {
            printf("백돌의 차례입니다.\n");
        }
        printf("x y 값을 입력하세요 (1~15), 0 0 : 항복\n");
        printf("\r                                                  \r");

        fgets(input, sizeof(input), stdin);

        if (sscanf_s(input, "%d %d", &x, &y) != 2)
        {
            position(0, 20);
            printf("숫자 두 개를 입력해주세요! [Enter]");
            _getch();
            continue;
        }

        if (x == 0 && y == 0)
        {
            position(0, 20);
            if (count % 2 == 1)
                printf("\n흑돌이 항복했습니다. 백돌 승리! [Enter]\n");
            else
                printf("\n백돌이 항복했습니다. 흑돌 승리! [Enter]\n");

            _getch();
            replay();
            return 0;
        }

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
            
            replay();
            return 0;
        }

        count++;
    }
}

void setConsoleEffect() // 콘솔창 꾸미기
{
    system("mode con: cols=80 lines=30");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    system("color F0");
}

int main()
{
    setConsoleEffect();

    printMenu();

    return 0;
}