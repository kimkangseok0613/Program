#include <stdio.h>

void shuffle(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int seed = rand() % size;

		int temporary = array[seed];

		array[seed] = array[i];

		array[i] = temporary;
	}
}

void Life(int currentHP, int maxHP)
{
	printf("Life : ");
	for (int i = 0; i < currentHP; i++)
	{
		printf("♥");
	}
	if (currentHP < maxHP)
	{
		for (int i = 0; i < (maxHP - currentHP); i++)
		{
			printf("♡");
		}
	}
}

int main()
{
#pragma region 의사 난수
	// 0 ~ 32767 사이의 난수 값을 반환하는 함수입니다.

	// UTC 기준으로 1970년 1월 1일 0시 0분 0초부터 경과된
	// 시간을 초(sec)로 변환하는 함수입니다.

	// srand : rand()가 사용할 초기값(seed)을 설정하는 함수

	// srand(time(NULL));
	// 
	// int random = rand() % 10 + 1;
	// 
	// printf("random : %d\n", random);

#pragma endregion

#pragma region 셔플 함수

	// srand(time(NULL));
	// 
	// int list[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// 
	// int size = sizeof(list) / sizeof(list[0]);
	// 
	// shuffle(list, size);
	// 
	// for (int i = 0; i < size; i++)
	// {
	// 	printf("list[%d]의 값 : %d\n", i, list[i]);
	// }

#pragma endregion

#pragma region UP - DOWN 게임

	srand(time(NULL));

	int computerNumber = rand() % 50 + 1;

	int userNumber = 0;

	int maxHP = 5;
	int currentHP = 5;

	printf("UP - DOWN 게임\n");
	printf("\n1 ~ 50중에 숫자를 하나 선택하세요.\n");

	while (1)
	{
		Life(currentHP, maxHP);
		printf("\n");
		scanf_s("%d", &userNumber);

		if (userNumber < 1 || userNumber>50)
		{
			printf("1 ~ 50중에 숫자를 하나 선택하세요.\n");
		}
		else if (userNumber == computerNumber)
		{
			printf("컴퓨터가 가지고 있는 값을 맞추었습니다.\n");
			printf("\nVictory");
			break;
		}
		else if (userNumber < computerNumber)
		{
			printf("컴퓨터가 가지고 있는 값보다 작습니다.\n");
			currentHP--;
		}
		else if (userNumber > computerNumber)
		{
			printf("컴퓨터가 가지고있는 값보다 큽니다.\n");
			currentHP--;
		}
		if (currentHP == 0)
		{
			Life(currentHP, maxHP);
			printf("\nDefeat\n");
			printf("정답 : %d\n", computerNumber);
			break;
		}
	}

#pragma endregion


	return 0;
}