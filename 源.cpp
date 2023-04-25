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
};//�����Թ�

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
	ps.data[ps.top] = -1;//����ʼ�������·��path��
	maze[x][y] = -1;
	bool find;
	while (ps.top > -1) {
		sx = ps.path[ps.top].x;
		sy = ps.path[ps.top].y;
		next = ps.data[ps.top];//��ʼ��
		if (sx == ex && sy == ey) {
			return 0;
			printf("\n");
		}
		find = false;//��ʼֵ�ȸ���false
		while (next <4 && !find) {
			next++;
			switch (next) {//��next�е����־������ĸ�������
			case 0:
				sx = ps.path[ps.top].x - 1;//������
				sy = ps.path[ps.top].y;
				break;
			case 1:
				sx = ps.path[ps.top].x;
				sy = ps.path[ps.top].y - 1;//������
				break;
			case 2:
				sx = ps.path[ps.top].x + 1;//������
				sy = ps.path[ps.top].y;
				break;
			case 3:
				sx = ps.path[ps.top].x;
				sy = ps.path[ps.top].y + 1;//������
				break;
			}
			if (maze[sx][sy] == 0)
				find = true;//���Թ��ﵱǰ·������һλ��·�ǣ��ҵ�·��
		}
			if (find) { 
				ps.data[ps.top] = next;//���ҵĵ�next����data·����
				ps.top++;//��ջ
				ps.path[ps.top].x = sx;
				ps.path[ps.top].y = sy;
				ps.data[ps.top] = -1;//��x��y����path·�����һλdata·����ʼ������ֵ-1
				maze[sx][sy] = -1;//�����µĿյظ�ֵ-1����ֹ������
			}
			else {//������·����ʱ���˵���һ���ڵ�
				maze[ps.path[ps.top].x][ps.path[ps.top].y] = 0;//�ø�λ�ñ�ɿյ�
				ps.top--;//��ջ
			}
		}
	return 0;
	}

void printmaze() {
	printf("\n");
	printf("·��ͼ���£�\n");//��ӡ��·��ͼ
	for (int j = 0; j < L+2; j++) {
		for (int k = 0; k < W+2; k++) {
			if (maze[j][k] == 1)
				printf("��");
			else
				if (maze[j][k] == 0)
					printf("  ");
				else
					if (maze[j][k] != 0 && maze[j][k] != 1)
						printf("��");
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
			ps.data[ps.top] = -1;//���յ��������·���У�ͬʱ��ʼ��data·��
			ps.top++;
			printf("�Թ���%d·�����£�0���������ߣ�1���������ߣ�2���������ߣ�3���������ߣ���\n", count++);
			for (int k = 0; k < ps.top; k++) {
				printf("\t(%d,%d,%d)", ps.path[k].x, ps.path[k].y, ps.data[k]);
				if ((k + 1) % 4 == 0)  //ÿ���4��������� 
					printf("\n");
			}
			printf("\n");
		}
		else {
			if (maze[x][y] == 0) {
				int next = 0; //�����ĸ���λ�ƶ��ı���
				while (next < 4) {
					ps.path[ps.top].x = x;
					ps.path[ps.top].y = y;
					ps.data[ps.top] = next;//��xi,yi����path·���е�x��y�� ��next����data·����
					ps.top++;
					switch (next) {//��next�е����־������ĸ�������
					case 0:
						sx = x - 1;//������
						sy = y;
						break;
					case 1:
						sx = x;
						sy = y - 1;//������
						break;
					case 2: 
						sx = x + 1;//������
						sy = y; 
						break;
					case 3: 
						sx = x; 
						sy = y + 1;//������
						break;
					} 
					maze[x][y] = -1;//��mg[xi][yi]=-1������������
					mazepath(sx, sy, xe, ye, ps);//ʹ�õݹ�������е�·��
					ps.top--;//��ջ 
					maze[x][y] = 0;//����path�����е�Ԫ�أ���������Ԫ��mg[xi][yi]=0��Ѱ������·��
					next++;
				}
			}
		}
		return 0;
	}
int main(){
	int x, y;
	x = y = 1;
	pathstack ps;//����ջ����ps
	ps.top = 0;//ջ��Ϊ0
	mazepath(x, y, L, W, ps);//����mazepath�������õݹ�ķ�ʽ��ò�������е�·��
	MAZE(x, y, L, W, ps);//��ѭ���ķ�ʽ������е�·��
	printmaze();
	return 0;
}