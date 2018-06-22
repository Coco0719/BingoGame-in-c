#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// �˻��� �Լ�
void gotoxy(int x, int y); // x y ��ǥ
void delay(int nDelay);  // ���� �Լ�
void textcolor(int colorNum); // color �Լ�
int introUi(void); // ��Ʈ�� ȭ�� -> ���ñ��
int shuffle(int *arr); // ���� ����
void gameUi(void); // ���� ȭ��
void makeZero(int *arr, int num); // ������ ���� 0���� �����
void printfBingo(int *arr, int x, int y); // ������ ���
int userInput(void); // ������ �Է��Ҷ� �������� �ٸ� ui�� ���� �ȹ�ġ�� �ϱ�
int checkBingo(int *arr); // ������ üũ
int aiSelectNum(int *arr); // ai ���� 
int checkWinner(int *ai, int userBingo, int aiBingo); // ���� üũ
void endUi(void); // ����� ui

void textcolor(int colorNum) // �ؽ�Ʈ�� ������ �����ִ� �Լ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void gotoxy(int x, int y) // �ܼ�â�� ���� ��ǥ�� �ٲٴ� �Լ�
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int introUi(void) // ��Ʈ�� ȭ���� �׸��� �Լ�
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

	// ���ӱ�Ģ ����
	gotoxy(15, 6);
	printf("������� ��Ģ\n");
	gotoxy(15, 9);
	printf("1. ó�� ������ ������ ����ں��� �����Դϴ�.");
	gotoxy(15, 11);
	printf("2. AI ���� �� 3�ʰ� ����ϼž� �մϴ�.");
	gotoxy(15, 13);
	printf("3. �̹� ������ ���ڸ� �ߺ����� �Ұ��� �մϴ�.");
	gotoxy(15, 15);
	printf("4. ���� ���� 5�� �޼������� �¸��մϴ�.");
	gotoxy(15, 17);
	printf("5. �ºΰ� ������ �� 5�ʰ� ����ϼž� �մϴ�.");
	
	// ���ӽ��� �� ���� ����
	gotoxy(15, 21);
	printf("(1) ���ӽ��� \n");
	gotoxy(15, 23);
	printf("(2) ��������  \n");

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

int shuffle(int *arr) // ����迭�� ���� �Լ�
{
	int ran1;
	int ran2;
	int temp;
	/*
	1. �� �迭�� ���� �������� �� �� �����Ѵ�.
	2. �� ���� ��ġ�� �ٲ۴�.
	3. 100�� �ݺ��Ѵ�.
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

void gameUi(void) // ���� ����ȭ�� UI�� �׸��� �Լ�
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

void printfBingo(int *arr, int x, int y) // �������� �ܼ� ȭ�鿡 ����ִ� �Լ�
{
	int count = 0;


	for (int i = 0; i < 10; i += 2)
	{
		gotoxy(x, y + i);
		// 5�� 5�� �迭�� ȭ�鿡 ��´�.
		// ���� 0���� �ٲ�ٸ� $�� ����Ѵ�.

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

void makeZero(int *arr, int num) // ���õ� ���� 0���� �ٲ۴�
{
	for (int i = 0; i < 25; i++)
	{
		if (*(arr + i) == num)
		{
			arr[i] = 0;
			return; // ���� ���É�ٸ� �Լ��� �����Ѵ�
		}
	}
}

int checkBingo(int *arr) // �迭�� ������� üũ�ϴ� �Լ�
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

int aiSelectNum(int *arr) // AI�� ���ڸ� �����ϴ� �Լ�
{
	int countNum[12] = { 0 }; // �� �迭�� 5�� 5�� �밢�� 2���� 0������ �ľ��Ͽ� ����
	int count; // �� �迭�� �˻��� �� ���
	int n = 0; // countNum �迭�� �ε����� ���

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
	countNum �迭���� 5�� ������ ���� ���� �ε����� �����س��� �����Ѵ�.
	*/
	for (int i = 1; i < 12; i++)
	{
		if (countNum[key] < countNum[i])
		{					  	  // �� ������ �����Ѵٸ� i���� key�� �־�� 
			if (countNum[i] == 5) //  countNum�� 5��� ���� �̹� �����̴� ������ ���� ����
			{
				continue; //�׷��ϱ� �ݺ��� ��� ������.
			}
			key = i;
			if (countNum[key] == 4)
			{
				break;
			}
		}
	}


	/*
	key���� 0~4�̸�, ��Ģ�� ����1~5�� �߿� �˻�
	key���� 5~9�̸�, ��Ģ�� ����1~5�� �߿� �˻�
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

	// key �� 10�̸� ��->�� �밢��, 11�̸� ��->�� �밢�� �˻�
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
	�˻��ϴ� �� / �� / �밢������ ���� ���� 0�� �ƴ�
	���ڰ� ������ �� ���� AI�� �����Ѵ�.
	*/
}

void delay(int nDelay) // ȭ���� ������ �����ִ� �Լ�
{
	int tick = GetTickCount();
	while (GetTickCount() - tick < nDelay)
	{
	}
}

int checkWinner(int *ai, int userBingo, int aiBingo) // ���ڸ� üũ���ִ� �Լ�
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

int userInput(void) // ����ڿ��� ������ �䱸�ϰ�, �� ���� ��ȯ�ϴ� �Լ�
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

void endUi(void) // ���� ���� ȭ���� ����ִ� �Լ�
{
	system("cls");

	textcolor(15);
	gotoxy(15, 7);
	printf("����ϼ̽��ϴ�.");
	gotoxy(15, 9);
	printf("������ ���� �ϼ̽��ϴ�.");
	gotoxy(15, 11);
	printf("������ ���Ḧ ���Ͻø� �ƹ�Ű�� �����ʽÿ�.\n");
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

