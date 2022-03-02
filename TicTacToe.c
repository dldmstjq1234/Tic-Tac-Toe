#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>

/*
게임설명
이름: 틱택토(tic tac to)
게임 방식:
(1) 순서를 번갈아가며 3x3형태의 보드판에 위치를 표시한다.
(2) 어느 한쪽이 대각선 가로 세로중 한 방향으로 3칸을 이으면 승리한다.
*/

int board[3][3] = { 0,0,0,0,0,0,0,0,0 }; //보드판
int turn = 1; //말그대로 플레이어 1과 2의 턴을 변경해줄때 필요한 변수이다. 초기값은1이므로 선공은 항상 플레이어 1
char name[2][10] = { "Player1","Player2" };
void view_board(); //게임 보드판을 표시해줌(바둑판처럼 만들어야됨 현제는 숫자만 표시)
void game_play(); //게임 플레이 해주는판(배열은 포인터안써도 서로 연동됨) 전체적인 흐름도 포함함. 다른기능 함수들이 다수 포함되어있음.
void Cmove(); //움직임과 선택을 담당하는 함수이다. 방향키를 눌러 움직일 수 있고 엔터키를 눌러서 원하는 위치에 표시할 수 있음.
void game(); //기본적인 요소들 화면이나 턴표시등을 포함한함수. 여러번쓰기귀찮아서 만듬.
int win_check_garo(); //가로3줄을 판별하여 승리를 판단함.
int win_check_sero(); //세로3줄을 판별하여 승리를 판단함.
int win_check_degak(); //양쪽 대각선을 판별하여 승리를 판단함.
void nameChange(); //이름바꿔주는 scanf가 포함되어있음. 이름바꿔주는 함수

void view_board() {
	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 1) {
				printf(" X");
				if (j == 0 || j == 1) {
					printf("│");
				}
			}


			else if (board[i][j] == 2) {
				printf(" O");
				if (j == 0 || j == 1) {
					printf("│");
				}
			}

			else if (board[i][j] == 0) {
				printf("  ");
				if (j == 0 || j == 1) {
					printf("│");
				}
			}


		}
		if (i == 0 || i == 1) {
			printf("\n──┼──┼──\n");
		}

	}
	printf("\n");
}


//전체적인 기능을 포함하는 함수. 판은 전체다 0이므로 플레이어각각 1과 2를 사용하여 표시 할예정 
void game_play() {
	int turnCnt = 1;
	int endGame;
	while (1) {
		endGame = 0;

		Cmove(board, turn);

		endGame = win_check_garo();
		if (endGame == 0) {
			endGame = win_check_sero();
			if (endGame == 0) {
				endGame = win_check_degak();
			}
		}

		if (endGame == 1 || endGame == 2) {
			printf("★축하드립니다!!!★\n");
			printf("%s이(가) 승리하였습니다.\n", name[endGame - 1]);
			view_board();
			system("pause");
			system("cls");
			break;
		}

		//턴바꾸는 알고리즘 ↓
		if (turn == 1) {
			turn++;
		}

		else {
			turn--;
		}

		system("cls");
		turnCnt++;
		if (turnCnt == 10) {
			view_board();
			printf("아쉽게도 무승부네요~ ㅋㅅㅋ\n");
			break;
		}
	}
}

void Cmove() { //플레이어의 한턴에서의 움직임과 선택을 나타낸다. 
	int key;
	int x, y; //좌표
	bool endTurn = false;
	x = 0, y = 0;


	while (endTurn == false) {
		game();
		printf("\n현재 좌표 (%d, %d)\n", x + 1, y + 1);
		printf("X) 1<-->3 방향으로 숫자 증가\n");
		printf("Y) 1 ↕ 3 방향으로 숫자 증가\n");
		key = getch();

		if (key == 13) { //좌표를 방향키로 이동한 후 선택할때 누름 (엔터키누른경우)
			if (board[y][x] == 0) {
				board[y][x] = turn;
				endTurn = true;
			}

			else {
				printf("\n*이미 누군가 체크하였습니다.*\n");
				system("pause");
			}
		}

		else if (key == 224) { // 방향키를 누른 경우
			key = getch();

			if (key == 75 && x > 0) { //왼쪽
				x--;
			}

			else if (key == 77 && x < 2) { //오른쪽
				x++;
			}

			else if (key == 72 && y > 0) { //위
				y--;
			}

			else if (key == 80 && y < 2) { //아래
				y++;
			}
		}
		system("cls");
	}


}


void game() {
	printf("%s의 차례\n", name[turn - 1]);
	printf("%s: X\n", name[0]);
	printf("%s: O\n\n", name[1]);
	view_board(board);
}


int win_check_garo() {
	int save = 0;
	//가로 3줄 판별
	for (int i = 0; i < 3; i++) {
		save = 0;
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0) {
				save += 100;
			}
			else {
				save += board[i][j];
			}

		}

		if (save == 3) {
			return 1;
		}

		else if (save == 6) {
			return 2;
		}
	}
	return 0;
}


int win_check_sero() {
	//세로 3줄 판별
	int save;
	for (int i = 0; i < 3; i++) {
		save = 0;
		for (int j = 0; j < 3; j++) {
			if (board[j][i] == 0) {
				save += 100;
			}

			else {
				save += board[j][i];
			}
		}

		if (save == 3) {
			return 1;
		}

		else if (save == 6) {
			return 2;
		}
	}
	return 0;
}


int win_check_degak() {
	//대각선 판별
	int save;

	//기울기가 음수인 대각선 판별
	save = 0;
	if (board[0][0] != 0 && board[1][1] != 0 && board[2][2]) {
		save += board[0][0] + board[1][1] + board[2][2];
	}

	if (save == 3) {
		return 1;
	}

	else if (save == 6) {
		return 2;
	}

	//기울기가 양수인 대각선 판별
	save = 0;
	if (board[0][2] != 0 && board[1][1] != 0 && board[2][0]) {
		save += board[0][2] + board[1][1] + board[2][0];
	}

	if (save == 3) {
		return 1;
	}

	else if (save == 6) {
		return 2;
	}

	return 0;
}



void nameChange() {
	int num;
	printf("현제이름\n");
	printf("1. user1: %s\n", name[0]);
	printf("2. user2: %s\n", name[1]);
	printf("3. 메뉴로 나가기\n");
	printf("변경할 이름 번호선택: ");
	scanf_s("%d", &num);

	if (num == 1 || num == 2) {
		printf("변경할 이름(공백없이): ");
		scanf_s("%s", &name[num - 1], sizeof(name[num - 1]));
		system("cls");
		printf("이름이 변경되었습니다.\n");
		system("pause");
	}


	else if (num == 3) {

	}

	else {
		printf("올바른 메뉴가 아닙니다.\n");
		system("pause");
		system("cls");
		nameChange();

	}

	system("cls");
}

int main(void) {
	int choise;
	int num;
	bool endProg = false;

	while (endProg == false) {
		int num = 0;
		printf("Tic Tac To\n");
		printf("1. 플레이\n");
		printf("2. 이름 설정\n");
		printf("3. 종료\n");
		printf("원하는 항목을 선택하세요: ");
		scanf_s("%d", &choise);
		system("cls");
		switch (choise) {
		case 1:
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					board[i][j] = 0;
				}
			}
			game_play();
			break;

		case 2:
			nameChange();
			break;
		case 3: printf("Tic Tac To를 종료합니다.\n"); endProg = true;
		}
	}



	return 0;
}