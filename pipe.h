#pragma once
#include <vector>
#include <QGraphicsPixmapItem>

using namespace std;

class Pipe{
public:
    static const int UP;
    static const int RIGHT;
    static const int DOWN;
    static const int LEFT;
    static int getOpposieDir(int dir);

    //[type][dir]
    const bool CANPASS_ARR[4][4] = {{0, 1, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 0}};

	int dir = 0; // 0 = up, 1 = right, 2 = down, 3 = left
	int type = 0; // 0 = -, 1 = T, 2 = +, 3 = Γ
	bool hasWater = 0;
	bool isdefaultPath = 0;
	bool canPass[4]; // 0 = up, 1 = right, 2 = down, 3 = left

    Pipe();
    Pipe(int type, bool isdefaultPath);
    Pipe(int type, int dir);

    //clockwise rotate
    void rotate();
    //change dir and canPass
    void setDir(int d);

    vector<vector<int>> getShap(int type, int dir);
};
