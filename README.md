# MazeAlgorithm

迷宫算法: 包括迷宫生成和迷宫搜索, 搜索时将具体的搜索过程记录为搜索结果, 供其他程序使用.

## 编译方法

- 将每个程序生成后, 按照下表修改为对应的名称, 保证 MazeEditor 能正确调用相应的算法.
  - Maze_1     dfs
  - Maze_2     bfs
  - Maze_3     A\*（曼哈顿距离）
  - Maze_4     A\*（欧式距离）
  - Maze_5     A\*（切比雪夫距离）
  - Maze_6     UCS
  - Maze_7     GBFS
  - Maze_8     IDA\*

- `DF/`: 将[`class.cpp`](DF/class.cpp)作为头文件, 每个`<算法名>.cpp`分别对应一个算法程序.

- `LW/`: 使用 VS 打开对应的 `.vcxproj` 进行编译即可.

  - `LW/Maze/`: 等代价算法

  - `LW/Maze_A/`: A\*算法. 需要将第62行的距离算法修改为对应的算法, 再编译为需要的程序. 如

    ```c++
    precost[i][j] = (int)(sqrt(a*a+b*b)*14); // 欧氏距离
    ```

  - `LW/Create_mode/`: 迷宫生成算法

## 程序调用参数

- 所有算法程序默认从 `D:\maze.txt` 读取迷宫, 结果输出到 `D:\answer.txt`
  - 使用参数指定输入输出:  

```bash
Maze_x.exe in-path out-path
```

- 迷宫生成算法有6个参数: 长度(行数) 宽度(列数) 随机留存比(0%不代表无方格) 框数 输出文件路径 是否开头有长宽(1为有 其他数字为无)

