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
vector<Point> road;
int way = 0;
int maxdeep;
string path1, path2;//输入输出路径
int maxDeep;
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
    for (int i = 0; i < width; i++)
    {
        maze[i].resize(height);
        vis[i].resize(height);
        cost[i].resize(height);
        precost[i].resize(height);
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
                int m = abs(endx - i) + abs(endy - j);
                precost[i][j] = m * 10;
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

bool dfs(int x, int y, int depth) {
    if ((depth * 10 + precost[x][y]) > maxDeep) {
        return false;
    }
    if (x == endx && y == endy) {//找到终点
        cout << "find it!" << endl;
        out << ++step << ' ' << 1 << endl;
        out << "vis " << x << ' ' << y << ' ' << cost[x][y] << endl;
        flag = 1;//停止递归
        out << "way" << ':' << ' ' << way << endl;
        for (int i = 0; i < way; i++) {
            out << road[i].x << ' ' << road[i].y << endl;
        }
        return true;
    }
    for (int k = 0; k <= 3; k++) {//依次向右下左上判断是否可走
        if (flag == 0) {
            int tx, ty;
            tx = x + dx[k];
            ty = y + dy[k];
            if (maze[tx][ty] != 1 && vis[tx][ty] == 0) {//有路可走
                step += 1;
                road.push_back(Point(tx, ty));
                way++;
                out << step << ' ' << num << endl;
                out << "vis " << x << ' ' << y << ' ' << cost[x][y] << endl;
                vis[tx][ty] = 1;
                cost_now = cost_now + 10;
                cost[tx][ty] = cost_now;
                out << "add " << tx << ' ' << ty << ' ' << cost[tx][ty] << endl;
                if (dfs(tx, ty, depth + 1)) {
                    return true;
                }
                vis[tx][ty] = 0;
                if (flag == 0) {//走入死路往回走
                    if (((depth + 1) * 10 + precost[tx][ty]) >= maxdeep) {
                        maxdeep = (depth + 1) * 10 + precost[tx][ty];
                    }
                    step += 1;
                    out << step << ' ' << num << endl;
                    out << "vis " << tx << ' ' << ty << ' ' << cost[tx][ty] << endl;
                    road.pop_back();
                    way--;
                    cost_now = cost_now - 10;
                    cost[x][y] = cost_now;
                    out << "del " << tx << ' ' << ty << endl;
                }
            }
        }
    }
    return false;
}

void IDAstar() {
    maxDeep = precost[startx][starty];
    vis[startx][starty] = 1;
    while (!dfs(startx, starty, 0)) {
        if (maxdeep <= maxDeep) {
            break;
        }
        maxDeep = maxDeep + 10;
    }
}

int main(int argc, char* argv[]) {
    path1 = argv[1];
    path2 = argv[2];
    out = ofstream(path2);
    readin();
    road.push_back(Point(startx, starty));
    way++;
    IDAstar();
    if (flag == 0) {
        out << "way" << ':' << ' ' << -1 << endl;
    }
    out.close();
}