#include <stdio.h>
#include <Windows.h>

#define SIZE 10

int main()
{
#pragma region 포인터 배열

	const char* dialog[SIZE];

	dialog[0] = "안녕하세요."; // 의뢰인
	dialog[1] = "의뢰인이신가요?";
	dialog[2] = "네, 맞습니다.";
	dialog[3] = "어떤 일로 찾아와주신 걸까요?";
	dialog[4] = "제 자택을 조사해주셨으면 합니다.";
	dialog[5] = "조사라함은?";
	dialog[6] = "고용인들이 밤중에 자택에서 이상한 소리가 들리는거 같다고 했어요. 저는 듣지 못했지만요.";
	dialog[7] = "이상한 소리라...궁금해지네요.";
	dialog[8] = "얘기를 듣자마자 당신에게 부탁해야겠다고 생각했어요.";
	dialog[9] = "벌써 재미있어지는데요. 자세한 얘기는 자택으로 가면서 듣도록 하죠.";

	// for (int i = 0; i < SIZE; i++)
	// {
	// 	printf("%s\n", dialog[i]);
	// }

	// 0x0000 : 이전에 누른 적이 없고 호출 시점에도 눌려있지 않은 상태
	// 0x0001 : 이전에 누른 적이 있고 호출 시점에는 눌려있지 않은 상태
	// 0x8000 : 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태
	// 0x8001 : 이전에 누른 적이 있고 호출 시점에도 눌려있는 상태
	int n = 0;
	while (n < 10)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		{
			printf("%s\n", dialog[n]);
			n++;
		}
	}

#pragma endregion

	return 0;
}