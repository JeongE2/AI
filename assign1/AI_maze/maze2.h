/* 미로 2 */
#define ROWS 30
#define COLS 40
#define START_ROW 1
#define START_COL 1
#define EXIT_ROW 28
#define EXIT_COL 38

int mark[ROWS][COLS];
int maze[ROWS][COLS] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,1},
{1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1},
{1,0,0,0,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,1,0,1,1,1,1,0,1,0,0,1},
{1,0,1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1},
{1,0,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1},
{1,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,0,1,1,1,0,0,1,0,1},
{1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1},
{1,0,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,1,0,0,1},
{1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,1,1,0,0,1},
{1,0,0,1,0,0,0,0,0,1,0,1,1,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1},
{1,1,0,1,0,1,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1},
{1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1},
{1,0,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1},
{1,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1},
{1,0,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1},
{1,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1},
{1,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,0,0,0,1},
{1,0,0,1,1,1,0,1,0,1,0,1,0,1,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1},
{1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
{1,0,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,1,1,0,1,0,1,0,1,1,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
{1,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1},
{1,1,0,1,0,1,0,1,1,0,0,1,0,1,0,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
{1,0,0,1,0,1,0,1,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
{1,1,0,0,0,1,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
{1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
