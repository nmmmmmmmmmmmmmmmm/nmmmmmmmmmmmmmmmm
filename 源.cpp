#include<stdio.h>
#include<stdlib.h>
#define L 8
#define W 8
#define maxsize 1000
int count = 1;

int maze[L + 2][W + 2] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,1,1},
	{1,0,1,1,1,0,0,1,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,1,1},
	{1,0,1,1,1,1,0,0,1,1},
	{1,1,1,0,0,0,1,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};//创建迷宫

typedef struct {
	int x;
	int y;
}way;
typedef struct {
	way path[maxsize];
	int data[maxsize];
	int top;
}pathstack;

int MAZE(int x,int y,int ex,int ey, pathstack ps) {
	int sx,sy;
	int	next;
	ps.path[ps.top].x = x;
	ps.path[ps.top].y = y;
	ps.data[ps.top] = -1;//将初始坐标存入路径path中
	maze[x][y] = -1;
	bool find;
	while (ps.top > -1) {
		sx = ps.path[ps.top].x;
		sy = ps.path[ps.top].y;
		next = ps.data[ps.top];//初始化
		if (sx == ex && sy == ey) {
			return 0;
			printf("\n");
		}
		find = false;//初始值先赋予false
		while (next <4 && !find) {
			next++;
			switch (next) {//由next中的数字决定往哪个方向走
			case 0:
				sx = ps.path[ps.top].x - 1;//向上走
				sy = ps.path[ps.top].y;
				break;
			case 1:
				sx = ps.path[ps.top].x;
				sy = ps.path[ps.top].y - 1;//向左走
				break;
			case 2:
				sx = ps.path[ps.top].x + 1;//向下走
				sy = ps.path[ps.top].y;
				break;
			case 3:
				sx = ps.path[ps.top].x;
				sy = ps.path[ps.top].y + 1;//向右走
				break;
			}
			if (maze[sx][sy] == 0)
				find = true;//当迷宫里当前路径的下一位是路是，找到路径
		}
			if (find) { 
				ps.data[ps.top] = next;//将找的的next存入data路径里
				ps.top++;//进栈
				ps.path[ps.top].x = sx;
				ps.path[ps.top].y = sy;
				ps.data[ps.top] = -1;//把x，y存入path路径里，下一位data路径初始化并赋值-1
				maze[sx][sy] = -1;//将脚下的空地赋值-1，防止往回走
			}
			else {//后面无路可走时，退到上一个节点
				maze[ps.path[ps.top].x][ps.path[ps.top].y] = 0;//让该位置变成空地
				ps.top--;//退栈
			}
		}
	return 0;
	}

void printmaze() {
	printf("\n");
	printf("路径图如下：\n");//打印出路径图
	for (int j = 0; j < L+2; j++) {
		for (int k = 0; k < W+2; k++) {
			if (maze[j][k] == 1)
				printf("■");
			else
				if (maze[j][k] == 0)
					printf("  ");
				else
					if (maze[j][k] != 0 && maze[j][k] != 1)
						printf("○");
				if ((k + 1) % (W + 2) == 0)
					printf("\n");
		}
	}
}

int mazepath(int x, int y, int xe, int ye, pathstack ps){
	int sx, sy;
		if (x == xe && y == ye) { 
			ps.path[ps.top].x = x;
			ps.path[ps.top].y = y;
			ps.data[ps.top] = -1;//将终点坐标进入路径中，同时初始化data路径
			ps.top++;
			printf("迷宫第%d路径如下（0代表往上走，1代表往左走，2代表往下走，3代表往右走）：\n", count++);
			for (int k = 0; k < ps.top; k++) {
				printf("\t(%d,%d,%d)", ps.path[k].x, ps.path[k].y, ps.data[k]);
				if ((k + 1) % 4 == 0)  //每输出4个方块后换行 
					printf("\n");
			}
			printf("\n");
		}
		else {
			if (maze[x][y] == 0) {
				int next = 0; //用于四个方位移动的变量
				while (next < 4) {
					ps.path[ps.top].x = x;
					ps.path[ps.top].y = y;
					ps.data[ps.top] = next;//将xi,yi进入path路径中的x和y中 ，next存入data路径中
					ps.top++;
					switch (next) {//由next中的数字决定往哪个方向走
					case 0:
						sx = x - 1;//向上走
						sy = y;
						break;
					case 1:
						sx = x;
						sy = y - 1;//向左走
						break;
					case 2: 
						sx = x + 1;//向上走
						sy = y; 
						break;
					case 3: 
						sx = x; 
						sy = y + 1;//向右走
						break;
					} 
					maze[x][y] = -1;//将mg[xi][yi]=-1，避免往回走
					mazepath(sx, sy, xe, ye, ps);//使用递归求出所有的路径
					ps.top--;//出栈 
					maze[x][y] = 0;//回退path数组中的元素，并将回退元素mg[xi][yi]=0来寻找其他路径
					next++;
				}
			}
		}
		return 0;
	}
int main(){
	int x, y;
	x = y = 1;
	pathstack ps;//定义栈参数ps
	ps.top = 0;//栈顶为0
	mazepath(x, y, L, W, ps);//调用mazepath函数，用递归的方式求得并输出所有的路径
	MAZE(x, y, L, W, ps);//用循环的方式求出所有的路径
	printmaze();
	return 0;
}