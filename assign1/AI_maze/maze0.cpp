#include <iostream>
#include "maze0.h"
using namespace std;

#define MAX_STACK_SIZE (ROWS-2)*(COLS-2)
#define MAX_Q_SIZE (ROWS-2)*(COLS-2)
int top = -1, vnodes=0,length=0;
int path_[ROWS][COLS] = { 0 };

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[MAX_STACK_SIZE];

void add(element item) 
{ // ���ÿ� ���ο� �׸��� �߰�
	if (top >= MAX_STACK_SIZE - 1) {
		printf("stack full");
		return;
	}
	stack[++top] = item;
	vnodes++; //bfs ���� �ּ�ó��
	length++;
}

element delete_() 
{ // ����top�� �׸���return
	if (top == -1) {
		printf("stack_empty");
	}
	length--;
	return stack[top--];
}

typedef struct { 
	short int x;
	short int y;
} offsets;
offsets move_[8];

void path(void) {// �̷θ� ����ϴ� ��ΰ� ������ ���, �̸� ���
	int i, row, col, next_row, next_col, dir;
	int found = 0;
	element position;

	move_[0].x = -1; move_[0].y =  0;
	move_[1].x = -1; move_[1].y =  1;
	move_[2].x =  0; move_[2].y =  1;
	move_[3].x =  1; move_[3].y =  1;
	move_[4].x =  1; move_[4].y =  0;
	move_[5].x =  1; move_[5].y = -1;
	move_[6].x =  0; move_[6].y = -1;
	move_[7].x = -1; move_[7].y = -1;
	
	// �̷��� �Ա���ǥ�� E �������� stack �ʱ�ȭ
	mark[START_ROW][START_COL] = 1; top = 0;
	stack[0].row = START_ROW; stack[0].col = START_COL; stack[0].dir = 2;

	while ( top > -1 && !found )  {// stack�� empty�� �ƴϰ�, ����
								   // ��θ� �߰� ���� ������ ����
		position = delete_();// top�� ��ġ�� �̵�
		row = position.row;   
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !found) {// 8������ ���ʴ�� �˻�
			next_row = row + move_[dir].x;// move in direction dir
			next_col = col + move_[dir].y;
			if ( next_row == EXIT_ROW && next_col == EXIT_COL )
				found = 1;// �ⱸ �߰�. ��δ� ���?
			else if ( !maze[next_row][next_col] &&
				!mark[next_row][next_col] ) {// ���� �� ���� ��
				mark[next_row][next_col] = 1;
				position.row = row;
				position.col = col;
				position.dir =++dir;
				add(position);// ���� ��ǥ�� ������stack����
				row = next_row;// �� ���� ��� ����. ������ ����
				col = next_col;
				dir = 0;
			}
			else ++dir;
		} }
	if (found) {// stack�� ����� ��� ��� //������ �������� ���ÿ� �ֵ��� ����
		position.row = row;
		position.col = col;
		position.dir = 0;
		add(position);
		position.row = EXIT_ROW;
		position.col = EXIT_COL;
		position.dir = 0;
		add(position);

		/*
		printf(" The path is:\n");
		printf ( "row col\n" );
		for (i = 0; i <= top; i++)
			printf( "%2d, %d\n", stack[i].row, stack[i].col );//*/
	}
	else printf( " The maze does not have a path\n" );
}

void print_path() {//�� = "|" // ��� = " " //������ ��� = "_" //������� = "o"
	for (int i = 0; i < ROWS; i++) {
		printf(" ");
		for (int j = 0; j < COLS; j++) {
			if (i == START_ROW && j == START_COL)
				printf("S");
			else if (i == EXIT_ROW && j == EXIT_COL)
				printf("G");
			else if (maze[i][j] == 1)
				printf("|");
			else {
				if (mark[i][j] == 1) {
					if (path_[i][j] == 1)
						printf("o");
					else
						printf("_");
				}
				else
					printf(" ");
			}
				
		}
		printf("\n");
	}
}

void print_maze() {//�� �� = "  " //������ ��� = " @" //������� = " v"
	printf("\n");
	for (int i = 0; i < ROWS; i++) {
		printf(" ");
		for (int j = 0; j < COLS; j++) {
			if (maze[i][j] == 1)
				printf("|");
			else {
					printf("_");
			}
		}
		printf("\n");
	}
}

/// <summary>
//���⼭���� BFS///////////////////////////////////////////
/// </summary>
typedef struct {
	short int row;
	short int col;
	short int p_row;
	short int p_col;
} elementq;
elementq queue[MAX_Q_SIZE];
int rear = -1, front = -1;

void addq(elementq item)
{ // Queue�� ���ο� �׸��� �߰�
	if (rear >= ((MAX_Q_SIZE) - 1)) {
		printf("queue is full.");
		return;
	}
	vnodes++;
	queue[++rear] = item;
}

elementq deleteq()
{ // Queue�� �׸��� return
	if (front == rear){
		printf("queue is empty.");
	}
	return queue[++front];
}

void bfs() {
	int i, row, col, next_row, next_col, dir=2;
	int found = 0;
	elementq position;

	move_[0].x = -1; move_[0].y = 0;
	move_[1].x = -1; move_[1].y = 1;
	move_[2].x = 0; move_[2].y = 1;
	move_[3].x = 1; move_[3].y = 1;
	move_[4].x = 1; move_[4].y = 0;
	move_[5].x = 1; move_[5].y = -1;
	move_[6].x = 0; move_[6].y = -1;
	move_[7].x = -1; move_[7].y = -1;

	// �̷��� �Ա���ǥ�� E �������� stack �ʱ�ȭ
	mark[START_ROW][START_COL] = 1; front = -1;
	position.row = START_ROW; position.col = START_COL; position.p_row = 0; position.p_col = 0;
	addq(position);

	while (rear < ((MAX_Q_SIZE)-1)&&!found) {// queue�� max�� �ƴϰ�, ����
								   // ��θ� �߰� ���� ������ ����
		position = deleteq();//ť�� front�� 1 ���� ��Ű�� ���� position�� queue�� front�� �ش��ϴ� ��ġ�� �����Ѵ�. 
		row = position.row; //-> delete �Ͽ� position�� �����´�.
		col = position.col;

		//���� row col ��ǥ�� ���� 8���� ��� �˻��� �Ȱ��� ���� �ִ��� Ȯ���ϰ� ť�� �ִ´�.
		while (dir < 8 && !found) {
			next_row = row + move_[dir].x;// move in direction dir
			next_col = col + move_[dir].y;
			if (next_row == EXIT_ROW && next_col == EXIT_COL) {
				found = 1;// �ⱸ �߰�. ��δ� ���?
			}
			else if (!maze[next_row][next_col] &&
				!mark[next_row][next_col]) {// ���� �� ���� ��
				mark[next_row][next_col] = 1;
				position.row = next_row; position.col = next_col; position.p_row = row; position.p_col = col;
				addq(position);
			}
			dir++;
		}
		dir = 0;
	}
	if (found) {// queue�� ������ ������ ���� ������ �ְ� ������ ������ �Ųٷ� ��θ� �ǵ��ư���.
		element po;
		position.row = EXIT_ROW; position.col = EXIT_COL; position.p_row = row; position.p_col = col;
		addq(position);
		row = EXIT_ROW; col = EXIT_COL;
		int p = 0;
		while(1) {//ù��° �������� ���ư�������
			//printf("wow");
			printf("%d, %d\n",row, col);
			po.row = row; po.col = col; po.dir = 0; //�������� �����ؼ� ���� ��ġ...
			add(po);//���ÿ� �ְ�
			if (row == START_ROW && col == START_COL) {//ù��° ���� ����
				break;
			}
			//queue�� �ڿ��� ���� ���鼭 ���� ��ġ�� �����Ҷ����� delete�ؼ� �̾ƿ��ٰ�
			//���� ��ġ�� �װ��� �θ� �ҷ����� ���� ��ġ�� �ٲ���
			//position = queue[front--];
			while (position.row != row||position.col!=col) {
				position = queue[front--]; //���⼭����
			}
			row = position.p_row; col = position.p_col;//�θ� ã�Ƽ� ���� ��ġ�� ����
		}
	}
	else printf(" The maze does not have a path\n");
}

int main() { //DFS�� BFS�� �ϳ��� ����
	///* DFS
	path();
	for (int i = 0; i <= top; i++) {
		path_[stack[i].row][stack[i].col] = 1;
	}
	print_maze();
	printf("\n DFS : \n");
	print_path();
	printf("\n   visited nodes : %d\n", vnodes);
	printf("\n   length : %d\n", length); //*/
	
	/* BFS
	bfs();
	length = top;
	for (int i = 0; i <= top; i++) {
		path_[stack[i].row][stack[i].col] = 1;
	}
	printf("\n BFS : \n");
	print_path();
	printf("\n   visited nodes : %d\n", vnodes);
	printf("\n   length : %d\n", length); //*/
}