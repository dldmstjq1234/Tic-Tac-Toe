#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>

/*
���Ӽ���
�̸�: ƽ����(tic tac to)
���� ���:
(1) ������ �����ư��� 3x3������ �����ǿ� ��ġ�� ǥ���Ѵ�.
(2) ��� ������ �밢�� ���� ������ �� �������� 3ĭ�� ������ �¸��Ѵ�.
*/

int board[3][3] = { 0,0,0,0,0,0,0,0,0 }; //������
int turn = 1; //���״�� �÷��̾� 1�� 2�� ���� �������ٶ� �ʿ��� �����̴�. �ʱⰪ��1�̹Ƿ� ������ �׻� �÷��̾� 1
char name[2][10] = { "Player1","Player2" };
void view_board(); //���� �������� ǥ������(�ٵ���ó�� �����ߵ� ������ ���ڸ� ǥ��)
void game_play(); //���� �÷��� ���ִ���(�迭�� �����;Ƚᵵ ���� ������) ��ü���� �帧�� ������. �ٸ���� �Լ����� �ټ� ���ԵǾ�����.
void Cmove(); //�����Ӱ� ������ ����ϴ� �Լ��̴�. ����Ű�� ���� ������ �� �ְ� ����Ű�� ������ ���ϴ� ��ġ�� ǥ���� �� ����.
void game(); //�⺻���� ��ҵ� ȭ���̳� ��ǥ�õ��� �������Լ�. ��������������Ƽ� ����.
int win_check_garo(); //����3���� �Ǻ��Ͽ� �¸��� �Ǵ���.
int win_check_sero(); //����3���� �Ǻ��Ͽ� �¸��� �Ǵ���.
int win_check_degak(); //���� �밢���� �Ǻ��Ͽ� �¸��� �Ǵ���.
void nameChange(); //�̸��ٲ��ִ� scanf�� ���ԵǾ�����. �̸��ٲ��ִ� �Լ�

void view_board() {
	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 1) {
				printf(" X");
				if (j == 0 || j == 1) {
					printf("��");
				}
			}


			else if (board[i][j] == 2) {
				printf(" O");
				if (j == 0 || j == 1) {
					printf("��");
				}
			}

			else if (board[i][j] == 0) {
				printf("  ");
				if (j == 0 || j == 1) {
					printf("��");
				}
			}


		}
		if (i == 0 || i == 1) {
			printf("\n����������������\n");
		}

	}
	printf("\n");
}


//��ü���� ����� �����ϴ� �Լ�. ���� ��ü�� 0�̹Ƿ� �÷��̾�� 1�� 2�� ����Ͽ� ǥ�� �ҿ��� 
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
			printf("�����ϵ帳�ϴ�!!!��\n");
			printf("%s��(��) �¸��Ͽ����ϴ�.\n", name[endGame - 1]);
			view_board();
			system("pause");
			system("cls");
			break;
		}

		//�Ϲٲٴ� �˰��� ��
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
			printf("�ƽ��Ե� ���ºγ׿�~ ������\n");
			break;
		}
	}
}

void Cmove() { //�÷��̾��� ���Ͽ����� �����Ӱ� ������ ��Ÿ����. 
	int key;
	int x, y; //��ǥ
	bool endTurn = false;
	x = 0, y = 0;


	while (endTurn == false) {
		game();
		printf("\n���� ��ǥ (%d, %d)\n", x + 1, y + 1);
		printf("X) 1<-->3 �������� ���� ����\n");
		printf("Y) 1 �� 3 �������� ���� ����\n");
		key = getch();

		if (key == 13) { //��ǥ�� ����Ű�� �̵��� �� �����Ҷ� ���� (����Ű�������)
			if (board[y][x] == 0) {
				board[y][x] = turn;
				endTurn = true;
			}

			else {
				printf("\n*�̹� ������ üũ�Ͽ����ϴ�.*\n");
				system("pause");
			}
		}

		else if (key == 224) { // ����Ű�� ���� ���
			key = getch();

			if (key == 75 && x > 0) { //����
				x--;
			}

			else if (key == 77 && x < 2) { //������
				x++;
			}

			else if (key == 72 && y > 0) { //��
				y--;
			}

			else if (key == 80 && y < 2) { //�Ʒ�
				y++;
			}
		}
		system("cls");
	}


}


void game() {
	printf("%s�� ����\n", name[turn - 1]);
	printf("%s: X\n", name[0]);
	printf("%s: O\n\n", name[1]);
	view_board(board);
}


int win_check_garo() {
	int save = 0;
	//���� 3�� �Ǻ�
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
	//���� 3�� �Ǻ�
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
	//�밢�� �Ǻ�
	int save;

	//���Ⱑ ������ �밢�� �Ǻ�
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

	//���Ⱑ ����� �밢�� �Ǻ�
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
	printf("�����̸�\n");
	printf("1. user1: %s\n", name[0]);
	printf("2. user2: %s\n", name[1]);
	printf("3. �޴��� ������\n");
	printf("������ �̸� ��ȣ����: ");
	scanf_s("%d", &num);

	if (num == 1 || num == 2) {
		printf("������ �̸�(�������): ");
		scanf_s("%s", &name[num - 1], sizeof(name[num - 1]));
		system("cls");
		printf("�̸��� ����Ǿ����ϴ�.\n");
		system("pause");
	}


	else if (num == 3) {

	}

	else {
		printf("�ùٸ� �޴��� �ƴմϴ�.\n");
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
		printf("1. �÷���\n");
		printf("2. �̸� ����\n");
		printf("3. ����\n");
		printf("���ϴ� �׸��� �����ϼ���: ");
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
		case 3: printf("Tic Tac To�� �����մϴ�.\n"); endProg = true;
		}
	}



	return 0;
}