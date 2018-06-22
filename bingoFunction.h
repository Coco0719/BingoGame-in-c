#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// 검색한 함수
void gotoxy(int x, int y); // x y 좌표
void delay(int nDelay);  // 지연 함수
void textcolor(int colorNum); // color 함수
int introUi(void); // 인트로 화면 -> 선택기능
int shuffle(int *arr); // 빙고 셔플
void gameUi(void); // 게임 화면
void makeZero(int *arr, int num); // 선택한 값을 0으로 만든다
void printfBingo(int *arr, int x, int y); // 빙고판 출력
int userInput(void); // 유저가 입력할때 여러가지 다른 ui에 영향 안미치게 하기
int checkBingo(int *arr); // 빙고개수 체크
int aiSelectNum(int *arr); // ai 선택 
int checkWinner(int *ai, int userBingo, int aiBingo); // 승자 체크
void endUi(void); // 종료시 ui

void textcolor(int colorNum) // 텍스트에 색깔을 입혀주는 함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void gotoxy(int x, int y) // 콘솔창의 시작 좌표를 바꾸는 함수
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int introUi(void) // 인트로 화면을 그리는 함수
{
	system("cls");

	gotoxy(9, 4);
	printf("%c", 1);
	gotoxy(70, 4);
	printf("%c", 2);
	gotoxy(9, 25);
	printf("%c", 3);
	gotoxy(70, 25);
	printf("%c", 4);

	for (int i = 10; i < 70; i++)
	{
		gotoxy(i, 4);
		printf("%c", 6);
		gotoxy(i, 19);
		printf("%c", 6);
		gotoxy(i, 25);
		printf("%c", 6);
	}
	for (int i = 5; i < 25; i++)
	{
		gotoxy(9, i);
		printf("%c", 5);
		gotoxy(70, i);
		printf("%c", 5);
	}

	gotoxy(70, 19);
	printf("%c", 23);
	gotoxy(9, 19);
	printf("%c", 25);

	textcolor(15);

	// 게임규칙 설명
	gotoxy(15, 6);
	printf("빙고게임 규칙\n");
	gotoxy(15, 9);
	printf("1. 처음 선택은 무조건 사용자부터 시작입니다.");
	gotoxy(15, 11);
	printf("2. AI 선택 후 3초간 대기하셔야 합니다.");
	gotoxy(15, 13);
	printf("3. 이미 선택한 숫자를 중복선택 불가능 합니다.");
	gotoxy(15, 15);
	printf("4. 빙고를 먼저 5개 달성한쪽이 승리합니다.");
	gotoxy(15, 17);
	printf("5. 승부가 결정난 후 5초간 대기하셔야 합니다.");
	
	// 게임시작 및 종료 선택
	gotoxy(15, 21);
	printf("(1) 게임시작 \n");
	gotoxy(15, 23);
	printf("(2) 게임종료  \n");

	while (1)
	{
		int a = 0;
		int b = 0;

		gotoxy(30, 23);
		printf("Select >> ");

	back:
		gotoxy(40, 23);

		a = _getche();
		a -= 48;
		if (a == -35)
		{
			goto back;
		}

		b = _getche();

		if (a == 1 && b == 13)
		{
			return 1;
		}
		else if (a == 2 && b == 13)
		{
			return 2;
		}
		else
		{
			gotoxy(40, 23);
			printf("   ");
			goto back;
		}
	}
}

int shuffle(int *arr) // 빙고배열을 섞는 함수
{
	int ran1;
	int ran2;
	int temp;
	/*
	1. 각 배열의 수를 무작위로 두 개 선택한다.
	2. 두 개의 위치를 바꾼다.
	3. 100번 반복한다.
	*/
	for (int i = 0; i < 100; i++)
	{
		ran1 = (rand() % 25);
		ran2 = (rand() % 25);

		temp = *(arr + ran1);
		*(arr + ran1) = *(arr + ran2);
		*(arr + ran2) = temp;
	}

	return 0;
}

void gameUi(void) // 실제 게임화면 UI를 그리는 함수
{
	system("cls");

	textcolor(9);

	gotoxy(9, 4);
	printf("%c", 1);
	gotoxy(70, 4);
	printf("%c", 2);
	gotoxy(9, 25);
	printf("%c", 3);
	gotoxy(70, 25);
	printf("%c", 4);

	for (int i = 10; i < 70; i++)
	{
		gotoxy(i, 4);
		printf("%c", 6);
		gotoxy(i, 19);
		printf("%c", 6);
		gotoxy(i, 25);
		printf("%c", 6);
		gotoxy(i, 6);
		printf("%c", 6);
	}
	for (int i = 5; i < 25; i++)
	{
		gotoxy(9, i);
		printf("%c", 5);
		gotoxy(40, i);
		printf("%c", 5);
		gotoxy(70, i);
		printf("%c", 5);
	}

	gotoxy(9, 19);
	printf("%c", 25);
	gotoxy(40, 19);
	printf("%c", 16);
	gotoxy(70, 19);
	printf("%c", 23);
	gotoxy(40, 4);
	printf("%c", 22);
	gotoxy(40, 25);
	printf("%c", 21);

	gotoxy(9, 6);
	printf("%c", 25);
	gotoxy(40, 6);
	printf("%c", 16);
	gotoxy(70, 6);
	printf("%c", 23);

	textcolor(15);
	gotoxy(21, 5);
	printf("U S E R");
	gotoxy(53, 5);
	printf("A  I");
	textcolor(7);
}

void printfBingo(int *arr, int x, int y) // 빙고판을 콘솔 화면에 찍어주는 함수
{
	int count = 0;


	for (int i = 0; i < 10; i += 2)
	{
		gotoxy(x, y + i);
		// 5행 5열 배열로 화면에 찍는다.
		// 만약 0으로 바꿨다면 $로 출력한다.

		textcolor(15);
		for (int j = 0; j < 5; j++)
		{
			if (*(arr + count) == 0)
			{
				textcolor(10);
				printf("%4c", '$');
				textcolor(15);
			}
			else
			{
				printf("%4d", *(arr + count));
			}
			count++;
		}
	}
	textcolor(7);
}

void makeZero(int *arr, int num) // 선택된 수를 0으로 바꾼다
{
	for (int i = 0; i < 25; i++)
	{
		if (*(arr + i) == num)
		{
			arr[i] = 0;
			return; // 만약 선택됬다면 함수를 종료한다
		}
	}
}

int checkBingo(int *arr) // 배열의 빙고수를 체크하는 함수
{
	int check = 0;
	int count;

	for (int i = 0; i < 25; i += 5)
	{
		count = 0;

		for (int j = 0; j < 5; j++)
		{
			if (*(arr + i + j) == 0)
			{
				count++;
			}
		}
		if (count == 5)
		{
			check++;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		count = 0;

		for (int j = 0; j < 25; j += 5)
		{
			if (*(arr + i + j) == 0)
			{
				count++;
			}
		}
		if (count == 5)
		{
			check++;
		}
	}

	count = 0;
	for (int i = 4; i < 24; i += 4)
	{
		if (*(arr + i) == 0)
		{
			count++;
		}
	}
	if (count == 5)
	{
		check++;
	}

	count = 0;
	for (int i = 0; i < 30; i += 6)
	{
		if (*(arr + i) == 0)
		{
			count++;
		}
	}
	if (count == 5)
	{
		check++;
	}

	return check;
}

int aiSelectNum(int *arr) // AI가 숫자를 선택하는 함수
{
	int countNum[12] = { 0 }; // 이 배열에 5행 5열 대각선 2줄의 0개수를 파악하여 저장
	int count; // 각 배열을 검사할 때 사용
	int n = 0; // countNum 배열의 인덱스로 사용

	for (int i = 0; i < 25; i += 5)
	{
		count = 0;

		for (int j = 0; j < 5; j++)
		{
			if (*(arr + i + j) == 0)
			{
				count++;
			}
		}
		countNum[n] = count;
		n++;
	}

	for (int i = 0; i < 5; i++)
	{
		count = 0;

		for (int j = 0; j < 25; j += 5)
		{
			if (*(arr + i + j) == 0)
			{
				count++;
			}
		}
		countNum[n] = count;
		n++;
	}

	count = 0;
	for (int i = 4; i < 24; i += 4)
	{
		if (*(arr + i) == 0)
		{
			count++;
		}
	}
	countNum[n] = count;
	n++;

	count = 0;
	for (int i = 0; i < 30; i += 6)
	{
		if (*(arr + i) == 0)
		{
			count++;
		}
	}
	countNum[n] = count;

	int key = 0;
	/*
	countNum 배열에서 5를 제외한 가장 높은 인덱스를 추출해내서 저장한다.
	*/
	for (int i = 1; i < 12; i++)
	{
		if (countNum[key] < countNum[i])
		{					  	  // 이 조건을 만족한다면 i값을 key에 넣어라 
			if (countNum[i] == 5) //  countNum이 5라는 뜻인 이미 빙고이니 선택할 수가 없다
			{
				continue; //그러니까 반복문 계속 돌려라.
			}
			key = i;
			if (countNum[key] == 4)
			{
				break;
			}
		}
	}


	/*
	key값이 0~4이면, 규칙에 따라1~5행 중에 검사
	key값이 5~9이면, 규칙에 따라1~5열 중에 검사
	*/
	if ((key >= 0) && (4 >= key))
	{
		key *= 5;

		for (int j = 0; j < 5; j++)
		{
			if (0 != *(arr + key + j))
			{
				return *(arr + key + j);
			}
		}
	}
	else if ((key >= 5) && (9 >= key))
	{
		key -= 5;

		for (int j = 0; j < 25; j += 5)
		{
			if (0 != *(arr + key + j))
			{
				return *(arr + key + j);
			}
		}
	}

	// key 가 10이면 왼->오 대각선, 11이면 오->왼 대각선 검사
	key %= 10;
	if (key == 0)
	{
		for (int i = 4; i < 24; i += 4)
		{
			if (0 != *(arr + i))
			{
				return *(arr + i);
			}
		}
	}
	else
	{
		for (int i = 0; i < 30; i += 6)
		{
			if (0 != *(arr + i))
			{
				return *(arr + i);
			}
		}
	}
	/*
	검사하는 행 / 열 / 대각선에서 가장 먼저 0이 아닌
	숫자가 나오면 그 값을 AI가 선택한다.
	*/
}

void delay(int nDelay) // 화면을 딜레이 시켜주는 함수
{
	int tick = GetTickCount();
	while (GetTickCount() - tick < nDelay)
	{
	}
}

int checkWinner(int *ai, int userBingo, int aiBingo) // 승자를 체크해주는 함수
{
	if ((userBingo >= 5) && (aiBingo >= 5))
	{
		printfBingo(ai, 44, 8);
		gotoxy(20, 5);
		printf("D R A W  ");
		gotoxy(52, 5);
		printf("D R A W  ");
		return 1;
	}
	else if (userBingo >= 5)
	{
		printfBingo(ai, 44, 8);
		gotoxy(20, 5);
		printf("  W I N    ");
		gotoxy(52, 5);
		printf("L O S E  ");
		return 1;
	}
	else if (aiBingo >= 5)
	{
		printfBingo(ai, 44, 8);
		gotoxy(20, 5);
		printf("L O S E   ");
		gotoxy(52, 5);
		printf("W I N    ");
		return 1;
	}
	else
	{
		return 0;
	}
}

int userInput(void) // 사용자에게 선택을 요구하고, 그 값을 반환하는 함수
{
	int a = 0;
	int b = 0;
	int c = 0;
	int num = 0;

back:
	gotoxy(32, 23);

	a = _getche();
	if (a == 13)
	{
		gotoxy(32, 23);
		printf("        ");
		gotoxy(32, 23);
		goto back;
	}

	b = _getche();
	if ((a >= 49 && a <= 57) && b == 13)
	{
		return (a - 48);
	}

	c = _getche();

	a -= 48;
	b -= 48;
	c -= 48;

	if (c != -35)
	{
		gotoxy(32, 23);
		printf("        ");
		gotoxy(32, 23);
		goto back;
	}

	if (a == 0 && b == 0)
	{
		num = a;
	}
	else if (a == 1 && b == 0)
	{
		if (b == -16 || b == -35 || b == -39)
		{
			num = a;
		}
		else if (num = a)
		{
			a = 10;
			num = a;
		}
	}
	else if (a == 2 && b == 0)
	{
		if (b == -16 || b == -35 || b == -39)
		{
			num = a;
		}
		else if (num = a)
		{
			a = 20;
			num = a;
		}
	}
	else if (a == 1)
	{
		a = 10;
		num = a + b;
	}
	else if (a == 2)
	{
		a = 20;
		num = a + b;
	}
	else if (b == 0 && a >= 3)
	{
		num = 0;
	}
	else if (b == 0)
	{
		num = a;
	}

	if (num < 1 || num > 25)
	{
		gotoxy(32, 23);
		printf("        ");
		gotoxy(32, 23);
		goto back;
	}

	return num;
}

void endUi(void) // 게임 종료 화면을 찍어주는 함수
{
	system("cls");

	textcolor(15);
	gotoxy(15, 7);
	printf("고생하셨습니다.");
	gotoxy(15, 9);
	printf("게임을 종료 하셨습니다.");
	gotoxy(15, 11);
	printf("완전한 종료를 원하시면 아무키나 누르십시요.\n");
	textcolor(7);

	for (int i = 10; i < 70; i++)
	{
		gotoxy(i, 4);
		printf("%c", 6);
		gotoxy(i, 19);
		printf("%c", 6);
	}
	for (int i = 5; i < 20; i++)
	{
		gotoxy(9, i);
		printf("%c", 5);

		gotoxy(70, i);
		printf("%c", 5);
	}

	gotoxy(9, 4);
	printf("%c", 1);
	gotoxy(70, 4);
	printf("%c", 2);

	gotoxy(9, 19);
	printf("%c", 3);
	gotoxy(70, 19);
	printf("%c", 4);
}

