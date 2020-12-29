#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include< queue>
#include<iomanip>
using namespace std;
class Point {
public :
	int x, y;//зјБъ
	Point(int x,int y) {
		this->x = x;
		this->y = y;
	}
	Point() {
		x = 0, y = 0;
	}
};
