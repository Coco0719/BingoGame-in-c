#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h> 
#include <conio.h>
#include <time.h>
#include "bingoFunction.h"

int main(void)
{
	srand(time(NULL));  // 셔플 함수에서 랜덤으로 수를 선택하여 뽑을때 사용

	short select = introUi(); // 인트로 화면 실행 

	textcolor(7);

	if (select == 1) // 인트로 함수 반환값이 1이면 게임 실행
	{
		while (1)
		{
			gameUi(); // 게임 화면 그리기

			int win = 0; // 승부 체크용
						 // 각각의 빙고
			int user[25] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9 , 10 , 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 ,21, 22, 23, 24, 25 };
			int ai[25] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9 , 10 , 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 ,21, 22, 23, 24, 25 };
			int num = 0; // 사용자와 유저가 선택한 숫자를 저장
			short userBingo = 0; // 각각 빙고수
			short aiBingo = 0;
			short flag = 0; // 유저 입력용

							// user빙고와 ai빙고를 섞는다
			shuffle(user);
			shuffle(ai);

			// 진짜 게임시작
			while (1)
			{
				// 유저 빙고판과 그 외 글자를 각자 좌표위치에 찍는다
				printfBingo(user, 13, 8);
				gotoxy(11, 21);
				printf(">> USER Bingo >> %d", userBingo);

				gotoxy(42, 21);
				printf(">>   AI Bingo >> %d", aiBingo);

				gotoxy(42, 23);
				printf(">>   AI 입력 >> ");

				/*
				유저에게 입력을 받는 반복문
				만약 flag값이 0이면 계속 실행되고 1이되면 탈출한다.
				1이 되는 경우는 유저가 선택한 값이 유저의 빙고배열에서
				선택되지 않은 상태여야 한다.
				*/
				do {
					gotoxy(32, 23);
					printf("        ");

					gotoxy(11, 23);
					printf(">> 1~25 정수 입력 >> ");

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
				flag = 0; // 선택이 완료후에 flag 변수는 항상 0으로 초기화한다

						  /*
						  선택된 숫자를 각자의 빙고배열에서 0으로 만들고
						  유저의 빙고만 다시 갱신해서 화면에 출력한다
						  출력할때, 요소값이 0인것은 '$'문자로 출력한다
						  */
				makeZero(user, num);
				makeZero(ai, num);
				printfBingo(user, 13, 8);

				// 각자의 빙고수를 체크하고, 화면에 나타낸다
				userBingo = checkBingo(user);
				aiBingo = checkBingo(ai);
				gotoxy(11, 21);
				printf(">> USER Bingo >> %d", userBingo);
				gotoxy(42, 21);
				printf(">>   AI Bingo >> %d", checkBingo(ai));

				// 승자를 체크한다, 만약 win변수가 1이라면 반복문을 빠져나간다
				win = checkWinner(ai, userBingo, aiBingo);
				if (win == 1)
				{
					break;
				}

				/*
				ai가 값을 선택하고 num 변수에 선택한 값을
				반환하고 화면에 찍어준다
				*/
				num = aiSelectNum(ai);

				gotoxy(42, 23);
				printf(">>   AI 입력 >> %d", num);

				// ai가 선택후 3초가 지나야 유저가 입력할 수 있다
				delay(3000);

				// ai 선택한 숫자를 화면상에서 지워준다
				gotoxy(58, 23);
				printf("    ");
				// 각각의 빙고배열에서 선택된 값을 0으로 만들고 빙고를 다시 출력
				makeZero(user, num);
				makeZero(ai, num);
				printfBingo(user, 13, 8);

				// 빙고수 체크 후, 출력, 승자 체크
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

			// 5초간 대기
			delay(5000);
			gotoxy(10, 26);
			printf("5초만 대기!");
			gotoxy(16, 5);
			// 텍스트 출력 -> select로 유저의 입력을 받는다.
			printf("(1) 게임 재시작   ");
			gotoxy(48, 5);
			printf("(2) 게임 종료   ");
			gotoxy(10, 26);
			printf("            ");

			// 게임 재시작 / 종료 입력을 받는다
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

	// 종료 화면을 출력한다.
	endUi();
	gotoxy(15, 13);
	system("pause");
	return 0;
}
