/***********************************************************************
 * File: gameManager.h
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215058
 * Update Date: 2024/04/24
 * Description: This program is responsible for the main functions, including reading maps, generating maps, etc.
***********************************************************************/
#ifndef gameManager_H
#define gameManager_H
#include <vector>
#include "Pipe.h"
using namespace std;

class GameManager {
private:
    //adjust the generation probability of pipes according to different situations.
    const vector<int> DEFAULT_PIPE_RANDOM_LIST = {30, 30, 10, 30 };
    const vector<int> STRAIGHT_PIPE_RANDOM_LIST = {50, 25, 25, 0};
    const vector<int> CURVED_PIPE_RANDOM_LIST = {0, 25, 25, 50};
    const vector<int> IO_PIPE_RANDOM_LIST = {0, 70, 30, 0};
    const vector<int> DIR_RANDOM_LIST = { 25, 25, 25, 25 };

    //use multiple pipe classes to store maps.
	vector<vector<Pipe*> > map;
	vector<vector<int> > printmap;


	int playerX, playerY;
	int startY; //game is always start from left, x = 0
	int endY; //game is always end from right, x = width - 1
	int height;
	int width;


    //return random number, contorled by vector
    int randomGenerator(vector<int> v);
    void createMapByRandom();
    bool createMapByRandomDFS(vector<vector<int>> &grid, int x, int y, int lastDir, int depth); //DFS, call by createMapByRandom
public:
    static bool isSuccess;

    GameManager(int height, int width); //random map
    GameManager(); //read map from filea
    ~GameManager();

	//let water flow, return true if end
	bool isEnd();
	void printMap();

	//getter
	int getStartY() {
		return startY;
	}
	int getEndY(){
		return endY;
	}
	int getWidth(){
		return width;
	}
	int getHeight(){
		return height;
	}
	Pipe* getPipe(int x, int y){
		return map[y][x];
	}
};
#endif
