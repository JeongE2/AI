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
{ // 스택에 새로운 항목을 추가
	if (top >= MAX_STACK_SIZE - 1) {
		printf("stack full");
		return;
	}
	stack[++top] = item;
	vnodes++; //bfs 사용시 주석처리
	length++;
}

element delete_() 
{ // 스택top의 항목을return
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

void path(void) {// 미로를 통과하는 경로가 존재할 경우, 이를 출력
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
	
	// 미로의 입구좌표와 E 방향으로 stack 초기화
	mark[START_ROW][START_COL] = 1; top = 0;
	stack[0].row = START_ROW; stack[0].col = START_COL; stack[0].dir = 2;

	while ( top > -1 && !found )  {// stack이 empty가 아니고, 아직
								   // 경로를 발견 못할 때까지 실행
		position = delete_();// top의 위치로 이동
		row = position.row;   
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !found) {// 8방향을 차례대로 검사
			next_row = row + move_[dir].x;// move in direction dir
			next_col = col + move_[dir].y;
			if ( next_row == EXIT_ROW && next_col == EXIT_COL )
				found = 1;// 출구 발견. 경로는 어디에?
			else if ( !maze[next_row][next_col] &&
				!mark[next_row][next_col] ) {// 아직 안 가본 길
				mark[next_row][next_col] = 1;
				position.row = row;
				position.col = col;
				position.dir =++dir;
				add(position);// 현재 좌표와 방향을stack저장
				row = next_row;// 안 가본 길로 전진. 방향은 북쪽
				col = next_col;
				dir = 0;
			}
			else ++dir;
		} }
	if (found) {// stack에 저장된 경로 출력 //마지막 지점까지 스택에 넣도록 변경
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

void print_path() {//벽 = "|" // 빈곳 = " " //지나온 경로 = "_" //최종경로 = "o"
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

void print_maze() {//빈 곳 = "  " //지나온 경로 = " @" //최종경로 = " v"
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
//여기서부터 BFS///////////////////////////////////////////
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
{ // Queue에 새로운 항목을 추가
	if (rear >= ((MAX_Q_SIZE) - 1)) {
		printf("queue is full.");
		return;
	}
	vnodes++;
	queue[++rear] = item;
}

elementq deleteq()
{ // Queue의 항목을 return
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

	// 미로의 입구좌표와 E 방향으로 stack 초기화
	mark[START_ROW][START_COL] = 1; front = -1;
	position.row = START_ROW; position.col = START_COL; position.p_row = 0; position.p_col = 0;
	addq(position);

	while (rear < ((MAX_Q_SIZE)-1)&&!found) {// queue가 max가 아니고, 아직
								   // 경로를 발견 못할 때까지 실행
		position = deleteq();//큐의 front를 1 증가 시키고 다음 position은 queue의 front에 해당하는 위치로 설정한다. 
		row = position.row; //-> delete 하여 position을 가져온다.
		col = position.col;

		//현재 row col 좌표에 대해 8방향 모두 검사해 안가본 땅이 있는지 확인하고 큐에 넣는다.
		while (dir < 8 && !found) {
			next_row = row + move_[dir].x;// move in direction dir
			next_col = col + move_[dir].y;
			if (next_row == EXIT_ROW && next_col == EXIT_COL) {
				found = 1;// 출구 발견. 경로는 어디에?
			}
			else if (!maze[next_row][next_col] &&
				!mark[next_row][next_col]) {// 아직 안 가본 길
				mark[next_row][next_col] = 1;
				position.row = next_row; position.col = next_col; position.p_row = row; position.p_col = col;
				addq(position);
			}
			dir++;
		}
		dir = 0;
	}
	if (found) {// queue에 마지막 지점에 대한 정보를 넣고 마지막 점부터 거꾸로 경로를 되돌아간다.
		element po;
		position.row = EXIT_ROW; position.col = EXIT_COL; position.p_row = row; position.p_col = col;
		addq(position);
		row = EXIT_ROW; col = EXIT_COL;
		int p = 0;
		while(1) {//첫번째 지점으로 돌아갈때까지
			//printf("wow");
			printf("%d, %d\n",row, col);
			po.row = row; po.col = col; po.dir = 0; //끝점부터 시작해서 현재 위치...
			add(po);//스택에 넣고
			if (row == START_ROW && col == START_COL) {//첫번째 지점 도착
				break;
			}
			//queue를 뒤에서 부터 보면서 현재 위치에 도달할때까지 delete해서 뽑아오다가
			//현재 위치면 그것의 부모를 불러워서 현재 위치로 바꿔줌
			//position = queue[front--];
			while (position.row != row||position.col!=col) {
				position = queue[front--]; //여기서부터
			}
			row = position.p_row; col = position.p_col;//부모 찾아서 현재 위치로 변경
		}
	}
	else printf(" The maze does not have a path\n");
}

int main() { //DFS나 BFS중 하나만 실행
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