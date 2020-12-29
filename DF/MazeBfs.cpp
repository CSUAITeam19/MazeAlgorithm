#include "class.cpp"
int width, height;//地图的长宽
int startx, starty, endx, endy;
int step = 0;
int flag = 0;
int f = 0;
vector<vector<int>> maze;//迷宫地图数据
vector<vector<int>> vis;//是否访问过和能否访问
vector<vector<int>> cost;//耗费 
vector<vector<int>> b;//步数
string path1, path2;//输入输出路径
vector<vector<int>> precost;
queue<Point> openlist;//访问表
vector<Point> pointlist;
int listnumber = 0;
ofstream out;
int caozuo[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int caozuo2[4][2] = { {1,1},{1,-1},{-1,1},{-1,-1} };
void readin() {
    ifstream in(path1);//地图数据地址
    in >> width >> height;
    maze.resize(width);
    vis.resize(width);
    cost.resize(width);
    b.resize(width);
    precost.resize(width);
    for (int i = 0; i < width; i++)
    {
        maze[i].resize(height);
        vis[i].resize(height);
        cost[i].resize(height);
        b[i].resize(height);
        precost[i].resize(height);
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
                b[i][j] = 1;
            }
            else if (maze[i][j] == 8) {
                endx = i;
                endy = j;
            }
            else if (maze[i][j] == 1) {
                vis[i][j] = 5;
                precost[i][j] = -1;
            }
        }
    }
    for (int i = 0; i < width; i++)
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

void bfs() {
    openlist.push(Point(startx, starty));
    vis[startx][starty] = 1;
    while (!openlist.empty()) {
        int num = 1;
        step++;
        int x_now = openlist.front().x, y_now = openlist.front().y;
        vis[x_now][y_now] = 3;
        int cost_now = cost[x_now][y_now];
        out << step << ' ';
        if (x_now == endx && y_now == endy) {
            flag = 1;
            out << num << endl;
            out << "vis" << ' ' << x_now << ' ' << y_now << ' ' << cost_now << endl;
            out << "way" << ':' << ' ';
            while (!(x_now == startx && y_now == starty)) {
                Point point1(x_now, y_now);
                pointlist.push_back(point1);
                listnumber++;
                for (int i = 0; i < 4; i++) {
                    int x_next = x_now + caozuo[i][0], y_next = y_now + caozuo[i][1];
                    if (maze[x_next][y_next] != 1&&b[x_next][y_next]==(b[x_now][y_now]-1)) {
                        x_now = x_next; y_now = y_next;
                        f = 1;
                        break;
                    }
                }
                if (f==0) {
                    for (int i = 0; i < 4; i++) {
                        int x_next = x_now + caozuo2[i][0], y_next = y_now + caozuo2[i][1];
                        if (maze[x_next][y_now] != 1 || maze[x_now][y_next] != 1) {
                            if (maze[x_next][y_next] != 1 && b[x_next][y_next] == b[x_now][y_now] - 1) {
                                x_now = x_next; y_now = y_next;
                                break;
                            }
                        }
                    }
                }
                f = 0;
            }
            Point point2(startx, starty);
            pointlist.push_back(point2);
            listnumber++;
            out << listnumber << endl;
            for (int i = listnumber - 1; i >= 0; i--) {
                out << pointlist[i].x << ' ' << pointlist[i].y << endl;
            }
            cout << "find it!" << endl;
            break;
        }
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
                b[x_next][y_next] = b[x_now][y_now] + 1;
                openlist.push(Point(x_next, y_next));
                out << "add" << ' ' << x_next << ' ' << y_next << ' ' << cost[x_next][y_next] << endl;
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
                    b[x_next][y_next] = b[x_now][y_now] + 1;
                    openlist.push(Point(x_next, y_next));
                    out << "add" << ' ' << x_next << ' ' << y_next << ' ' << cost[x_next][y_next] << endl;
                    vis[x_next][y_next] = 1; 
                }
            }
        }
        openlist.pop();//拓展完队首出队
    }
}

int main(int argc, char* argv[])
{
    path1 = argv[1];
    path2 = argv[2];
    out = ofstream(path2);
    readin();
    bfs();
    if (flag == 0) {
        out << "way" << ' ' << -1 << endl;
    }
    out.close();
}