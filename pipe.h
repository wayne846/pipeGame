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

	int dir = 0; // 0 = up, 1 = right, 2 = down, 3 = left
	int type = 0; // 0 = -, 1 = T, 2 = +, 3 = Γ
	bool hasWater = 0;
	bool isdefaultPath = 0;
	bool canPass[4]; // 0 = up, 1 = right, 2 = down, 3 = left

    Pipe();
    Pipe(int type, bool isdefaultPath);

    static int getOpposieDir(int dir);

    vector<vector<int>> getShap(int type, int dir);
    //clockwise rotate
    void rotate();
};
