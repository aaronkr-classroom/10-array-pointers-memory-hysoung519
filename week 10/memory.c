//memory.c
#include <stdio.h>

int* BP, * SP; //Base Pointer, Stack Pointer
int stack[1024]; //(int) 4바이트 * 1024 (스택)
int stackIndex = 0;//스택 포인터 위치


show()
{
	printf("-----------------\n");
	printf("현재 스택 상태 (TOP -> Bottom):\n");
	for (int i = stackIndex - 1; i >= 0; i--) {
		//주소 값과 해당 주소에서의 실제 값을 출력
		int* addr = (int*)&stack[i];
		int value = *addr;
		printf("스택[%d]: %p (주소), %d (값)\n", i, addr, value);

	}
	printf("Base Pointer (BP): %p\n", (void*)BP);
	printf("Base Pointer (SP): %p\n", (void*)SP);
	printf("---------------------------\n");
}

push(int value)
{
	stack[stackIndex++] = value; //stack[0] = vlaue; 0++;
	SP = &stack[stackIndex]; //SP = stack[1];
}

int* pop()
{
	if (stackIndex > 0) {
		SP = &stack[--stackIndex]; //1--; stack[0]
		return stack[stackIndex];
	}
	return -1; //스택에서 값이 업ㅅ다

}

Test(int a, int b, int c) {
	//지역 변수
	int x = a + b;
	int y = b + c;
	int z = c + a;

	printf("Test() 함수 진입 - 스택 프레임 생성\n");
	push((int)BP); //이전 BP를 저장

	//현재 스택 프레임 푸시
	push((int)&x);
	push((int)&y);
	push((int)&z);

	show();

	printf("Test()함수 반환 - 스택 프레임 해제\n");
	pop(); //z
	pop(); //y
	pop(); //x

	BP = pop();

	show();


}

int main()
{
	int a = 10,
		b = 20,
		c = 30;

	printf("Main() 함수 시작 - 초기 스택 상태\n");

	push((int)&a);
	push((int)&b);
	push((int)&c);

	BP = &stack;

	show();

	printf("Test()함수 호출\n");
	Test(a, b, c);

	printf("Main()함수 종료 - 스택 상태 복구\n");

	pop();
	pop();
	pop();

	show();

	return 0;
}