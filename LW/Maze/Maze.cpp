#include "class.cpp"
int width, height;//地图的长宽
int startx, starty, endx, endy;
vector<vector<int>> maze;//迷宫地图数据
string path1, path2;//输入输出路径
vector<vector<int>> vis;//是否访问过和能否访问
vector<vector<int>> cost;//耗费 
queue<Point> openlist;//访问表
queue<Point> vislist;
vector<Point> waylist;
vector<vector<Point>> fatherpoint;
ofstream out;
int caozuo[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int caozuo2[4][2] = { {1,1},{1,-1},{-1,1},{-1,-1} };
void readin() {
    ifstream in(path1);//地图数据地址
    in >> width>>height;
    maze.resize(width);
    vis.resize(width);
    cost.resize(width);
    fatherpoint.resize(width);
    for (int i = 0; i < width; i++)
    {
        maze[i].resize(height);
        vis[i].resize(height);
        cost[i].resize(height);
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
            out << setw(5) << left << "0 ";
        }
        out << endl;
    }
//    out << startx << " " << starty << endl;
//    out << endx << " " << endy << endl;
    in.close();//用完后关闭
}
void show() {
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            out << setw(2) << left<< vis[i][j];
        } 
        out <<"                 " ;
        for (int j = 0; j < height; j++)
        {
            out << setw(4) <<left<< cost[i][j];
        }
        out << endl;
    }
    out << endl;
}
void UCS() {
    int num = 0;
    openlist.push(Point(startx, starty));//将开始节点加入
    int x_now = startx, y_now = starty;
    fatherpoint[x_now][y_now] = Point(x_now, y_now);
    while (true) {
        num++;
        out << num << " ";
        int cost_now = 100000;//F=G+H
        if (openlist.empty()) {
            cout << "无效！";
            out << "0" << endl;
            out << "way: " << "-1" << endl;
            return;
        }
        int lenth = openlist.size();
        for (int i = 0; i < lenth; i++)
        {
            Point point_now = openlist.front();//取出
            openlist.pop();//删除队列头
            if (point_now.x == endx && point_now.y == endy)//终点出现了！
            {
                x_now = point_now.x;
                y_now = point_now.y;
                cost_now = cost[x_now][y_now];
                openlist.push(point_now);
                break;
            }
            else if (cost[point_now.x][point_now.y]< cost_now)
            {
                x_now = point_now.x;
                y_now = point_now.y;
                cost_now = cost[x_now][y_now] ;
            }
            openlist.push(point_now);
        }
        while (true) {
            Point point_now = openlist.front();//取出
            openlist.pop();//删除队列
            if (point_now.x == x_now && point_now.y == y_now)break;
            openlist.push(point_now);
        }
        vis[x_now][y_now] = 3;//标记为使用过
        int cznum = 1;
        for (int i = 0; i < 4; i++) {//这里是上左下右
            int x_next = x_now + caozuo[i][0], y_next = y_now + caozuo[i][1];
            if (vis[x_next][y_next] != 5)//排除是墙
            {
                if (vis[x_next][y_next] == 1)//如果在队列里
                {
                    cznum++;
                }
                else if (vis[x_next][y_next] != 3)//不在队列里且没有使用过
                {
                    cznum++;
                }
            }
        }
        for (int i = 0; i < 4; i++) {//这里是上左下右（斜）
            int x_next = x_now + caozuo2[i][0], y_next = y_now + caozuo2[i][1];
            if (vis[x_next][y_now] == 5 && vis[x_now][y_next] == 5)continue;
            if (vis[x_next][y_next] != 5)
            {
                if (vis[x_next][y_next] == 1)//如果在队列里
                {
                    cznum++;
                }
                else if (vis[x_next][y_next] != 3)//不在队列里且没有使用过
                {
                    cznum++;
                }
            }
        }
        if (x_now == endx && y_now == endy) cznum = 1;
        out << cznum << endl;
        out << "vis  " << x_now << " " << y_now << " " << cost[x_now][y_now] << endl;

        if (x_now == endx && y_now == endy)
        {
            cout << "find it!" << endl;

            while (true)
            {
                vislist.push(Point(x_now, y_now));
                Point a = fatherpoint[x_now][y_now];
                if (a.x == x_now && a.y == y_now)
                {
                    break;
                }
                x_now = a.x;
                y_now = a.y;
            }
            out << "way:" << " " << vislist.size() << endl;
            int vislength = vislist.size();
            waylist.resize(vislength + 1);
            for (int len = 0; len < vislength; len++)
            {
                Point a = vislist.front();
                vislist.pop();
                waylist[len] = a;
            }
            for (int len = vislength - 1; len >= 0; len--)
            {
                out << waylist[len].x << " " << waylist[len].y << endl;
            }
            return;
        }
        for (int i = 0; i < 4; i++) {//这里是上左下右
            int x_next = x_now + caozuo[i][0], y_next = y_now + caozuo[i][1];
            if (vis[x_next][y_next] != 5)//排除是墙
            {
                if (vis[x_next][y_next] == 1)//如果在队列里
                {
                    if (cost[x_next][y_next] > cost[x_now][y_now] + 10) {//如果更新了最小值
                        cost[x_next][y_next] = cost[x_now][y_now] + 10;
                        fatherpoint[x_next][y_next] = Point(x_now, y_now);
                    }
                    out << "cost " << x_next << " " << y_next << " " << cost[x_next][y_next] << endl;
                }
                else if (vis[x_next][y_next] != 3)//不在队列里且没有使用过
                {
                    vis[x_next][y_next] = 1;
                    openlist.push(Point(x_next, y_next));
                    cost[x_next][y_next] = cost[x_now][y_now] + 10;
                    fatherpoint[x_next][y_next] = Point(x_now, y_now);
                    out << "add  " << x_next << " " << y_next << " " << cost[x_next][y_next] << endl;
                }
            }
        }
        for (int i = 0; i < 4; i++) {//这里是上左下右（斜）
            int x_next = x_now + caozuo2[i][0], y_next = y_now + caozuo2[i][1];
            if (vis[x_next][y_now] == 5 && vis[x_now][y_next] == 5)continue;
            if (vis[x_next][y_next] != 5)
            {
                if (vis[x_next][y_next] == 1)//如果在队列里
                {
                    if (cost[x_next][y_next] > cost[x_now][y_now] + 14) {//如果更新了最小值
                        cost[x_next][y_next] = cost[x_now][y_now] + 14;
                        fatherpoint[x_next][y_next] = Point(x_now, y_now);
                    }
                    out << "cost " << x_next << " " << y_next << " " << cost[x_next][y_next] << endl;
                }
                else if (vis[x_next][y_next] != 3)//不在队列里且没有使用过
                {
                    vis[x_next][y_next] = 1;
                    openlist.push(Point(x_next, y_next));
                    cost[x_next][y_next] = cost[x_now][y_now] + 14;
                    fatherpoint[x_next][y_next] = Point(x_now, y_now);
                    out << "add  " << x_next << " " << y_next << " " << cost[x_next][y_next] << endl;
                }
            }
        }
        //        show();
    }
}
int main(int argc,char* argv[])
{
    path1 = argv[1];
    path2 = argv[2];
    out=ofstream(path2);
    readin();
    UCS();
    out.close();
   // cout << "Hello World!\n";
}