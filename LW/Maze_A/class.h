#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include< queue>
#include<iomanip>
class Point {
public:
	int x, y;//зјБъ
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Point() {
		this->x = 0;
		this->y = 0;
	}
};
