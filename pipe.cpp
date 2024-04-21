#include "pipe.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

const int Pipe::UP = 0;
const int Pipe::RIGHT = 1;
const int Pipe::DOWN = 2;
const int Pipe::LEFT = 3;

Pipe::Pipe(){
    this->dir = 0;
    this->type = 0;
    this->hasWater = false;
    this->isdefaultPath = false;
    this->canPass[0] = 0;
    this->canPass[1] = 1;
    this->canPass[2] = 0;
    this->canPass[3] = 1;
}

Pipe::Pipe(int type, bool isdefaultPath) {
    this->dir = 0;
    this->type = type;
    this->isdefaultPath = isdefaultPath;
    bool canPassArr[4][4] = {{0, 1, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 0}};
    for(int i = 0; i < 4; i++) {
        this->canPass[i] = canPassArr[type][i];
    }

    //random rotate
    int rateteTimes = rand() % 4;
    for(int i = 0; i < rateteTimes; i++){
        rotate();
    }
}

vector<vector<int>> Pipe::getShap(int type, int dir) {
	vector<vector<int>> shape[4][4];//shape[type][dir]
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 将每个元素初始化为一个 3x3 的 vector，每个元素都是 0
			shape[i][j] = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
		}
	}
	//Clockwise
	//- pipes
	shape[0][0] = { {0,0,0},{1,1,1},{0,0,0} };
	shape[0][1] = { {0,1,0},{0,1,0},{0,1,0} };
	shape[0][2] = { {0,0,0},{1,1,1},{0,0,0} };
	shape[0][3] = { {0,1,0},{0,1,0},{0,1,0} };
	//T pipe
	shape[1][0] = { {0,0,0},{1,1,1},{0,1,0} };
	shape[1][1] = { {0,1,0},{1,1,0},{0,1,0} };
	shape[1][2] = { {0,1,0},{1,1,1},{0,0,0} };
	shape[1][3] = { {0,1,0},{0,1,1},{0,1,0} };
	//+ pipe
	shape[2][0] = { {0,1,0},{1,1,1},{0,1,0} };
	shape[2][1] = { {0,1,0},{1,1,1},{0,1,0} };
	shape[2][2] = { {0,1,0},{1,1,1},{0,1,0} };
	shape[2][3] = { {0,1,0},{1,1,1},{0,1,0} };
	//Γ pipe
	shape[3][0] = { {0,0,0},{0,1,1},{0,1,0} };
	shape[3][1] = { {0,0,0},{1,1,0},{0,1,0} };
	shape[3][2] = { {0,1,0},{1,1,0},{0,0,0} };
	shape[3][3] = { {0,1,0},{0,1,1},{0,0,0} };

	return shape[type][dir];
}

void Pipe::rotate() {
    dir++;
    if (dir > 3){
        dir = 0;
    }
    int tmp = canPass[0];
    canPass[0] = canPass[3];
    canPass[3] = canPass[2];
    canPass[2] = canPass[1];
    canPass[1] = tmp;
}

int Pipe::getOpposieDir(int dir){
    if(dir == UP){
        return DOWN;
    }else if(dir == RIGHT){
        return LEFT;
    }else if(dir == DOWN){
        return UP;
    }else{
        return RIGHT;
    }
}
