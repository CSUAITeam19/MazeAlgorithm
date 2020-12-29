#include "class.cpp"
int width, height;//地图的长宽
int startx, starty, endx, endy;
int flag = 0;//函数递归是否结束标志
int cost_now = 0;
int num = 2;//操作数每次都是1
int step = 0;//走过的步数
vector<vector<int>> maze;//迷宫地图数据
vector<vector<int>> vis;//是否访问过和能否访问
vector<vector<int>> cost;//耗费 
vector<vector<int>> precost;//预消耗
string path1, path2;//输入输出路径
vector<vector<int>> fatherpoint_x;//父节点
vector<vector<int>> fatherpoint_y;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
ofstream out;
void readin() {
    ifstream in(path1);//地图数据地址
    in >> width >> height;
    maze.resize(width);
    vis.resize(width);
    cost.resize(width);
    precost.resize(width);
    fatherpoint_x.resize(width);
    fatherpoint_y.resize(width);
    for (int i = 0; i < width; i++)
    {
        maze[i].resize(height);
        vis[i].resize(height);
        cost[i].resize(height);
        precost[i].resize(height);
        fatherpoint_x[i].resize(height);
        fatherpoint_y[i].resize(height);
    }
    //vector 构造
    //cout << width << " " << height << endl;

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
                precost[i][j] = 0;
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
    //out << startx << " " << starty << endl;
    //out << endx << " " << endy << endl;
    in.close();//用完后关闭
}

void dfs(int x, int y) {
    fatherpoint_x[startx][starty] = startx;
    fatherpoint_y[startx][starty] = starty;
    if (x == endx && y == endy) {//找到终点
        cout << "find it!" << endl;
        out << ++step << ' ' << 1 << endl;
        out << "vis " << x << ' ' << y << ' ' << cost[x][y] << endl;
        vector<vector<int>>road;
        int listnumber = 0;
        road.resize(++listnumber);
        road[0].resize(2);
        road[0][0] = endx; road[0][1] = endy;
        int x_now = endx; int y_now = endy;
        while (true) {
            int x_next = fatherpoint_x[x_now][y_now]; int y_next = fatherpoint_y[x_now][y_now];
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
        flag = 1;//停止递归
        return;
    }
    for (int k = 0; k <= 3; k++) {//依次向右下左上判断是否可走
            if (flag == 0) {
                int tx, ty;
                tx = x + dx[k];
                ty = y + dy[k];
                if (maze[tx][ty] != 1 && vis[tx][ty] == 0) {//有路可走
                    step += 1;
                    out << step << ' ' << num << endl;
                    out << "vis " << x << ' ' << y << ' ' << cost[x][y] << endl;
                    vis[tx][ty] = 1;
                    fatherpoint_x[tx][ty] = x;
                    fatherpoint_y[tx][ty] = y;
                    cost_now = cost_now + 10;
                    cost[tx][ty] = cost_now;
                    out << "add " << tx << ' ' << ty << ' ' << cost[tx][ty] << endl;
                    dfs(tx, ty);//递归到下个点继续找路
                    if (flag == 0) {//走入死路往回走
                        step += 1;
                        out << step << ' ' << num << endl;
                        out << "vis " << tx << ' ' << ty << ' ' << cost[tx][ty] << endl;
                        cost_now = cost_now - 10;
                        cost[x][y] = cost_now;
                        out << "del " << tx << ' ' << ty << endl;
                    }
                }
            }
    }
}
int main(int argc, char* argv[]) {
    path1 = argv[1];
    path2 = argv[2];
    out = ofstream(path2);
    readin();
    Point Point_now(startx, starty);
    vis[startx][starty] = 1;
    dfs(Point_now.x, Point_now.y);
    if (flag == 0) {
        out << "way" << ' ' << -1 << endl;
    }
    out.close();
}