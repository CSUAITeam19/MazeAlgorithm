#include"class.h"
using namespace std;
vector<vector<int>> maze;
queue<Point> visited;
int height, width,startx, starty;
int cz[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
ofstream out("D://maze.txt");	
double percent=0;
int hole_number=0;
void step1()//第一步初始化
{
	srand((int)(time(NULL)));
	maze.resize(height);
	for (int i = 0; i < height; i++) {
		maze[i].resize(width);
	}
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			maze[i][j] = 1;
		}//把点全部设为墙
	startx = rand() % (height - 2) + 1;
	starty = rand() % (width - 2) + 1;
	visited.push(Point(startx, starty));
	while(!visited.empty())
	{
		int time = rand() % visited.size();
		Point a;
		for (int i = 0; i <=time; i++)
		{
			a = visited.front();
			visited.pop();
			visited.push(a);
		}//随机取点
		a = visited.front();
		visited.pop();
		int flag = 0;
		for (int i = 0; i < 4; i++)
		{
			if (maze[a.x + cz[i][0]][a.y + cz[i][1]]==2)
			{
				flag++;
			}
		}
		if (flag <= 1)
		{
			maze[a.x][a.y] = 2;
			if (maze[a.x - 1][a.y] == 1 && a.x > 1)visited.push(Point(a.x - 1, a.y));
			if (maze[a.x + 1][a.y] == 1 && a.x < height-2)visited.push(Point(a.x + 1, a.y));
			if (maze[a.x][a.y - 1] == 1 && a.y > 1)visited.push(Point(a.x, a.y - 1));
			if (maze[a.x][a.y + 1] == 1 && a.y < width - 2)visited.push(Point(a.x, a.y + 1));
		}
	}//prime生成
	int deletx, delety;
	for (int i = 0; i < (height - 1) * (width - 1)*(percent); i++)
	{
		deletx = rand() % (height - 2) + 1;
		delety = rand() % (width - 2) + 1;
		maze[deletx][delety] = 2;
	}
	for (int i = 1; i <= hole_number; i++)
	{
		int h = rand() % 10 + 5;
		int w = rand() % 10 + 5;
		int x1 = rand() % (height - 3) + 2;
		int y1 = rand() % (width - 3) + 2;
		for (int x2 = x1; x2 < x1 + h&&x2<height-1; x2++)
		{
			int k=rand()%5;
			if(k!=3)
				maze[x2][y1 - 1] = 1;
			else
				maze[x2][y1 - 1] = 2;
			if(k!=4)
				maze[x2][min(y1 + w, width - 1)] = 1;
			else
				maze[x2][min(y1 + w, width - 2)] = 2;
			for (int y2 = y1; y2 < y1 + w && y2 < width-1; y2++) {
				k = rand() % 5;
				if(k!=3)
					maze[x1 - 1][y2] = 1;
				else
					maze[x1 - 1][y2] = 2;
				if(k!=4)
					maze[min(x1 + h, height - 1)][y2] = 1;
				else
					maze[min(x1 + h, height - 2)][y2] = 2;
				maze[x2][y2] = 2;
			}
		}
	}
	
	int x_start = rand() % (height - 2) + 1;
	int y_start = rand() % (width - 2) + 1;
	int endx,endy;
	do {
		endx = rand() % (height - 2) + 1;
		endy = rand() % (width - 2) + 1;
	} while (abs(endx - x_start) < height / 3 || abs(endy - y_start) < width / 3);
	maze[x_start][y_start] = 4;
	maze[endx][endy] = 8;
	for (int i = 0; i < height; i++,out<<endl)
		for (int j = 0; j < width; j++) {
			out << maze[i][j] << " ";
	}
	
	return;
}
int main(int argc, char* argv[]) {
	int need_number=4;
	if (argc <= need_number)
	{
		cout << "Wrong!" << endl;
		return 0;
	}
	srand((int)(time(NULL)));
	int k1 = 0, k2 = 0;
	string a = argv[1];
	for (int i = 0; i < a.size(); i++) {
		if (a[i] > '9' || a[i] < '0') {
			cout << "wrong!" << endl;
		}
		k1 = k1 * 10 + (a[i] - '0');
	}
	a = argv[2];
	for (int i = 0; i < a.size(); i++) {
		if (a[i] > '9' || a[i] < '0') {
			cout << "wrong!" << endl;
		}
		k2 = k2 * 10 + (a[i] - '0');
	}
	a = argv[3];
	for (int i = 0; i < a.size(); i++) {
		if (a[i] > '9' || a[i] < '0') {
			cout << "wrong!" << endl;
		}
		percent =  percent* 10 + (double)(a[i] - '0');
	}
	percent = 1 - percent / 100;
	a = argv[4];
	for (int i = 0; i < a.size(); i++) {
		if (a[i] > '9' || a[i] < '0') {
			cout << "wrong!" << endl;
		}
		hole_number = hole_number * 10 + (a[i] - '0');
	}
	out=ofstream(argv[5]);
	height = k1;
	width = k2;
	if (argv[6][0] == '1')
		out << height << " " << width << endl;
	step1();
}
