#include "class.cpp"
int width, height;//地图的长宽
int startx, starty, endx, endy;
int step = 0;
int flag = 0;
int f = 0;
vector<vector<int>> maze;//迷宫地图数据
vector<vector<int>> vis;//是否访问过和能否访问
vector<vector<int>> cost;//耗费 
vector<vector<int>> precost;//预消耗
vector<vector<Point>> fatherpoint;//父节点
string path1, path2;//输入输出路径
queue<Point> openlist;//访问表
vector<Point> pointlist;
ofstream out;
int listnumber = 0;
int caozuo[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int caozuo2[4][2] = { {1,1},{1,-1},{-1,1},{-1,-1} };
void readin() {
    ifstream in(path1);//地图数据地址
  //  ifstream in("D://maze.txt");//地图数据地址
    in >> width >> height;
    maze.resize(width);
    vis.resize(width);
    cost.resize(width);
    precost.resize(width);
    fatherpoint.resize(width);
    for (int i = 0; i < width; i++)
    {
        maze[i].resize(height);
        vis[i].resize(height);
        cost[i].resize(height);
        precost[i].resize(height);
        fatherpoint[i].resize(height);
    }
    //vector 构造
  //  cout << width << " " << height << endl;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            in >> maze[i][j];//读入每个格子的数据
            if (maze[i][j] == 4) {
                startx = i;
                starty = j;
            }
            else if (maze[i][j] == 8) {
                endx = i;
                endy = j;
            }
            else if (maze[i][j] == 1) {
                vis[i][j] = 5;
            }
        }
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (maze[i][j] == 1) {
                precost[i][j] = -1;
            }
            if (maze[i][j] != 1) {
                int m = abs(endx - i) + abs(endy - j);
                precost[i][j] = m * 10;
            }
        }
    }
    for (int i = 0; i < width; i++)//H矩阵
    {
        for (int j = 0; j < height; j++)
        {
            out << setw(5) << left << precost[i][j] << " ";
        }
        out << endl;
    }
    //    out << startx << " " << starty << endl;
    //    out << endx << " " << endy << endl;
    in.close();//用完后关闭
}

void GBFS() {
    openlist.push(Point(startx, starty));
    vis[startx][starty] = 1;
    fatherpoint[startx][starty] = Point(startx, starty);
    while (!openlist.empty()) {
        int num = 1;
        step++;
        int x_now = openlist.front().x, y_now = openlist.front().y;
        int cost_now = cost[x_now][y_now];
        out << step << ' ';
        int lenth = openlist.size();
        for (int i = 0; i < lenth; i++)
        {
            Point point_now = openlist.front();//取出
            openlist.pop();//删除队列头
            if (point_now.x == endx && point_now.y == endy)//终点出现了！
            {
                x_now = point_now.x; y_now = point_now.y;
                flag = 1;
                out << num << endl;
                cout << "find it!" << endl;
                out << "vis" << ' ' << x_now << ' ' << y_now << ' ' << cost_now << endl;
                vector<vector<int>>road;
                int listnumber = 0;
                road.resize(++listnumber);
                road[0].resize(2);
                road[0][0] = x_now; road[0][1] = y_now;
                while (true) {//找每个节点的父节点，输出路径
                    int x_next = fatherpoint[x_now][y_now].x; int y_next = fatherpoint[x_now][y_now].y;
                    road.resize(++listnumber);
                    road[listnumber - 1].resize(2);
                    road[listnumber - 1][0] = x_next; road[listnumber - 1][1] = y_next;
                    x_now = x_next; y_now = y_next;
                    if (x_next == startx && y_next == starty) {
                        break;
                    }
                }
                out << "way" << ':' << ' ' << listnumber << endl;
                for (int i = listnumber - 1; i >= 0; i--) {
                    out << road[i][0] << ' ' << road[i][1] << endl;
                }
                x_now = endx; y_now = endy;
                break;
            }
            else if (precost[point_now.x][point_now.y] < precost[x_now][y_now])
            {
                x_now = point_now.x;
                y_now = point_now.y;
                cost_now = cost[x_now][y_now];
            }
            openlist.push(point_now);
        }
        if (x_now == endx && y_now == endy)break;
        while (true) {
            Point point_now = openlist.front();//取出
            openlist.pop();//删除队列
            if (point_now.x == x_now && point_now.y == y_now)break;
            openlist.push(point_now);
        }
        vis[x_now][y_now] = 3;
        for (int i = 0; i < 4; i++) {//这里是上左下右
            int x_next = x_now + caozuo[i][0], y_next = y_now + caozuo[i][1];
            if (vis[x_next][y_next] == 1) {
                num++;
            }
            if (maze[x_next][y_next] != 1 && vis[x_next][y_next] == 0) {
                num++;
            }
        }
        for (int i = 0; i < 4; i++) {//这里是上左下右（斜）
            int x_next = x_now + caozuo2[i][0], y_next = y_now + caozuo2[i][1];
            if (maze[x_next][y_now] != 1 || maze[x_now][y_next] != 1) {
                if (vis[x_next][y_next] == 1) {
                    num++;
                }
                if (maze[x_next][y_next] != 1 && vis[x_next][y_next] == 0) {
                    num++;
                }
            }
        }
        out << num << endl;
        out << "vis" << ' ' << x_now << ' ' << y_now << ' ' << cost_now << endl;
        for (int i = 0; i < 4; i++) {//这里是上左下右
            int x_next = x_now + caozuo[i][0], y_next = y_now + caozuo[i][1];
            if (vis[x_next][y_next] == 1) {
                cost[x_next][y_next] = min(cost[x_next][y_next], cost_now + 10);
                out << "cost " << x_next << " " << y_next << " " << cost[x_next][y_next] << endl;
            }
            if (maze[x_next][y_next] != 1 && vis[x_next][y_next] == 0) {
                cost[x_next][y_next] = cost_now + 10;
                openlist.push(Point(x_next, y_next));
                out << "add" << ' ' << x_next << ' ' << y_next << ' ' << cost[x_next][y_next] << endl;
                fatherpoint[x_next][y_next] = Point(x_now,y_now);
                vis[x_next][y_next] = 1;
            }
        }
        for (int i = 0; i < 4; i++) {//这里是上左下右（斜）
            int x_next = x_now + caozuo2[i][0], y_next = y_now + caozuo2[i][1];
            if (maze[x_next][y_now] != 1 || maze[x_now][y_next] != 1) {
                if (vis[x_next][y_next] == 1) {
                    cost[x_next][y_next] = min(cost[x_next][y_next], cost_now + 14);
                    out << "cost " << x_next << " " << y_next << " " << cost[x_next][y_next] << endl;
                }
                if (maze[x_next][y_next] != 1 && vis[x_next][y_next] == 0) {
                    cost[x_next][y_next] = cost_now + 14;
                    openlist.push(Point(x_next, y_next));
                    out << "add" << ' ' << x_next << ' ' << y_next << ' ' << cost[x_next][y_next] << endl;
                    fatherpoint[x_next][y_next] = Point(x_now, y_now);
                    vis[x_next][y_next] = 1;
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    path1 = argv[1];
    path2 = argv[2];
    out = ofstream(path2);
    readin();
    GBFS();
    if (flag == 0) {
        out << "way" << ':' << ' ' << -1 << endl;
    }
    out.close();
    // cout << "Hello World!\n";
}