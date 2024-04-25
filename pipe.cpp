/***********************************************************************
 * File: Pipe.cpp
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215058
 * Update Date: 2024/04/24
 * Description: This program is the class of pipe
***********************************************************************/
#include "pipe.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

const int Pipe::UP = 0;
const int Pipe::RIGHT = 1;
const int Pipe::DOWN = 2;
const int Pipe::LEFT = 3;


// Intent: To create pipe class
// Pre: Create a pipe when this is not the default path
// Post: The function returns the pipe
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

// Intent: To create defaultPath pipe class by type
// Pre: Create a pipe when this is the default path
// Post: The function returns the pipe
Pipe::Pipe(int type, bool isdefaultPath) {
    this->dir = 0;
    this->type = type;
    this->isdefaultPath = isdefaultPath;

    //Generate canpass paths based on input
    for(int i = 0; i < 4; i++) {
        this->canPass[i] = CANPASS_ARR[type][i];
    }

    //random rotate
    int rateteTimes = rand() % 4;
    for(int i = 0; i < rateteTimes; i++){
        rotate();
    }
}

// Intent: To create pipe by type and dir
// Pre: Create a pipe when read the file
// Post: The function returns the pipe
Pipe::Pipe(int type, int dir){
    this->dir = 0;
    this->type = type;
    this->isdefaultPath = false;

    for(int i = 0; i < 4; i++) {
        this->canPass[i] = CANPASS_ARR[type][i];
    }

    for(int i = 0; i < dir; i++){
        rotate();
    }
}

// Intent: To get pipe shape
// Pre:  when read the file to compare input and shape
// Post: The function returns the shape
vector<vector<int>> Pipe::getShap(int type, int dir) {
	vector<vector<int>> shape[4][4];//shape[type][dir]

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
            // all elements are 3x3 vector
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

// Intent: To rotate pipe shape
// Pre:  when user click on the pipe
// Post: The pipe shape is rotated clockwise, and the direction is updated
void Pipe::rotate() {
    dir++;

    //remake if dir is out of range
    if (dir > 3){
        dir = 0;
    }

    //move canPass to rotate
    int tmp = canPass[0];
    canPass[0] = canPass[3];
    canPass[3] = canPass[2];
    canPass[2] = canPass[1];
    canPass[1] = tmp;
}

// Intent: To set pipe dir
// Pre:  when create map from file
// Post: return pipe
void Pipe::setDir(int d){
    if(dir == d) return;
    dir = 0;
    for(int i = 0; i < 4; i++){
        canPass[i] = CANPASS_ARR[type][i];
    }
    for(int i = 0; i < d; i++){
        rotate();
    }
}

// Intent: To get opposite dir
// Pre: when isEnd judge
// Post: return dir
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
