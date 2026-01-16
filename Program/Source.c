#include <stdio.h>
#include <stdlib.h>

// #define SIZE 1000

void load(const char* filename)
{
	FILE* file = fopen(filename, "r");

	// long size = 0;

	// 파일 포인터를 파일 끝으로 이동시킵니다.
	// fseek(file, 0, SEEK_END);

	// END_OF_FILE (EOF)
	int character = '\0';
	int count = 0;

	// 파일의 끝이 아니면 count값을 증가시킵니다.

	// while (character != EOF) // count : 52
	// {
	// 	character = fgetc(file); // EOF
	// 	count++;
	// } //(X)
	while ((character = fgetc(file)) != EOF) // count : 51
	{
		count++;
	}

	// printf("count : %d\n", count); // 51

	rewind(file);

	// char buffer[SIZE] = { NULL }; // buffer[] == *buffer
	// char buffer[10000] = { NULL }; || char buffer[10000] = { 0, };

	char* buffer = malloc(count + 1);

	buffer[count] = NULL;

	// fread( [1], [2], [3], [4])
	// [1] 읽을 데이터를 저장할 메모리 버퍼의 포인터 변수
	// [2] 각 데이터 항목의 크기
	// [3] 데이터를 읽어올 항목의 수
	// [4] 데이터를 읽어올 파일의 포인터 변수

	fread(buffer, sizeof(char), count, file);

	printf("%s", buffer);

	fclose(file);

	free(buffer);
}

int main()
{
#pragma region 파일 입출력

#pragma region 파일 쓰기
	// 첫번째 매개변수 (파일의 이름)
	// 두번째 매개변수 (파일의 입출력 모드)
	
	// FILE* file = fopen("data.txt","w");
	// 
	// fputs("Character Information\n",file);
	// 
	// fputs("Health :\n",file);
	// fputs("Attack :\n",file);
	// fputs("Defense :\n",file);
	// 
	// fclose(file);

#pragma endregion

#pragma region 파일 읽기

	//load("Resources/Pachirisu.txt");

#pragma endregion
	
#pragma endregion

	return 0;
}