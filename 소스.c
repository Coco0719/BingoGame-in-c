#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h> 
#include <conio.h>
#include <time.h>
#include "bingoFunction.h"

int main(void)
{
	srand(time(NULL));  // ���� �Լ����� �������� ���� �����Ͽ� ������ ���

	short select = introUi(); // ��Ʈ�� ȭ�� ���� 

	textcolor(7);

	if (select == 1) // ��Ʈ�� �Լ� ��ȯ���� 1�̸� ���� ����
	{
		while (1)
		{
			gameUi(); // ���� ȭ�� �׸���

			int win = 0; // �º� üũ��
						 // ������ ����
			int user[25] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9 , 10 , 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 ,21, 22, 23, 24, 25 };
			int ai[25] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9 , 10 , 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 ,21, 22, 23, 24, 25 };
			int num = 0; // ����ڿ� ������ ������ ���ڸ� ����
			short userBingo = 0; // ���� �����
			short aiBingo = 0;
			short flag = 0; // ���� �Է¿�

							// user����� ai���� ���´�
			shuffle(user);
			shuffle(ai);

			// ��¥ ���ӽ���
			while (1)
			{
				// ���� �����ǰ� �� �� ���ڸ� ���� ��ǥ��ġ�� ��´�
				printfBingo(user, 13, 8);
				gotoxy(11, 21);
				printf(">> USER Bingo >> %d", userBingo);

				gotoxy(42, 21);
				printf(">>   AI Bingo >> %d", aiBingo);

				gotoxy(42, 23);
				printf(">>   AI �Է� >> ");

				/*
				�������� �Է��� �޴� �ݺ���
				���� flag���� 0�̸� ��� ����ǰ� 1�̵Ǹ� Ż���Ѵ�.
				1�� �Ǵ� ���� ������ ������ ���� ������ ����迭����
				���õ��� ���� ���¿��� �Ѵ�.
				*/
				do {
					gotoxy(32, 23);
					printf("        ");

					gotoxy(11, 23);
					printf(">> 1~25 ���� �Է� >> ");

					num = userInput();

					for (int i = 0; i < 25; i++)
					{
						if (user[i] == num)
						{
							flag = 1;
							break;
						}
					}

					if (flag == 1)
					{
						break;
					}
				} while (flag == 0);
				flag = 0; // ������ �Ϸ��Ŀ� flag ������ �׻� 0���� �ʱ�ȭ�Ѵ�

						  /*
						  ���õ� ���ڸ� ������ ����迭���� 0���� �����
						  ������ ���� �ٽ� �����ؼ� ȭ�鿡 ����Ѵ�
						  ����Ҷ�, ��Ұ��� 0�ΰ��� '$'���ڷ� ����Ѵ�
						  */
				makeZero(user, num);
				makeZero(ai, num);
				printfBingo(user, 13, 8);

				// ������ ������� üũ�ϰ�, ȭ�鿡 ��Ÿ����
				userBingo = checkBingo(user);
				aiBingo = checkBingo(ai);
				gotoxy(11, 21);
				printf(">> USER Bingo >> %d", userBingo);
				gotoxy(42, 21);
				printf(">>   AI Bingo >> %d", checkBingo(ai));

				// ���ڸ� üũ�Ѵ�, ���� win������ 1�̶�� �ݺ����� ����������
				win = checkWinner(ai, userBingo, aiBingo);
				if (win == 1)
				{
					break;
				}

				/*
				ai�� ���� �����ϰ� num ������ ������ ����
				��ȯ�ϰ� ȭ�鿡 ����ش�
				*/
				num = aiSelectNum(ai);

				gotoxy(42, 23);
				printf(">>   AI �Է� >> %d", num);

				// ai�� ������ 3�ʰ� ������ ������ �Է��� �� �ִ�
				delay(3000);

				// ai ������ ���ڸ� ȭ��󿡼� �����ش�
				gotoxy(58, 23);
				printf("    ");
				// ������ ����迭���� ���õ� ���� 0���� ����� ���� �ٽ� ���
				makeZero(user, num);
				makeZero(ai, num);
				printfBingo(user, 13, 8);

				// ����� üũ ��, ���, ���� üũ
				userBingo = checkBingo(user);
				aiBingo = checkBingo(ai);
				gotoxy(11, 21);
				printf(">> USER Bingo >> %d", userBingo);
				gotoxy(42, 21);
				printf(">>   AI Bingo >> %d", checkBingo(ai));
				win = checkWinner(ai, userBingo, aiBingo);
				if (win == 1)
				{
					break;
				}

			}

			// 5�ʰ� ���
			delay(5000);
			gotoxy(10, 26);
			printf("5�ʸ� ���!");
			gotoxy(16, 5);
			// �ؽ�Ʈ ��� -> select�� ������ �Է��� �޴´�.
			printf("(1) ���� �����   ");
			gotoxy(48, 5);
			printf("(2) ���� ����   ");
			gotoxy(10, 26);
			printf("            ");

			// ���� ����� / ���� �Է��� �޴´�
		back:
			gotoxy(10, 26);
			printf("select >> ");
			int a;
			int b;

			gotoxy(20, 26);

			a = _getche();
			a -= 48;
			if (a == -35)
			{
				goto back;
			}

			b = _getche();

			if (a == 1 && b == 13)
			{
				continue;
			}
			else if (a == 2 && b == 13)
			{
				break;
			}
			else
			{
				gotoxy(20, 26);
				printf("   ");
				goto back;
			}
		}
	}

	// ���� ȭ���� ����Ѵ�.
	endUi();
	gotoxy(15, 13);
	system("pause");
	return 0;
}
