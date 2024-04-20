#include "gamemanager.h"
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>

int GameManager::randomGenerator(vector<int> v) {
    int sum = 0;
    for(int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    int randNum = rand() % 100;
    for(int i = 0; i < v.size(); i++) {
        if (randNum < v[i] * 100 / (double)sum) {
            return i;
        }
        randNum -= v[i] * 100 / (double)sum;
    }
    return 0;
}

GameManager::GameManager(int height, int width) {
	this->height = height;
	this->width = width;
	this->playerY = 0;
	this->playerX = 0;
	this->map = std::vector<std::vector<Pipe>>(height, std::vector<Pipe>(width));
	this->printmap = vector<std::vector<int>>(height * 3, std::vector<int>(width * 3));

	//generate map
	srand(time(NULL));
	startY = rand() % height;
	endY = rand() % width;
	createMapByRandom();
}

void GameManager::update(char a) {
    switch(a){
        case 'w':
            if (playerY - 1 >= 0){
                playerY--;
            }
            break;
        case 's':
            if (playerY + 1 < height){
                playerY++;
            }
            break;
        case 'd':
            if(playerX + 1 < width){
                playerX++;
            }
            break;
        case 'a':
            if(playerX - 1 >= 0){
                playerX--;
            }
            break;
        case 'r':
            map[playerY][playerX].rotate();
            break;
    }
}

bool GameManager::isEnd() {
    //clean water
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            this->map[i][j].hasWater = 0;
        }
    }

    if(map[startY][0].canPass[Pipe::LEFT] == false){
        return false;
    }

    //BFS
    bool flag = false;
    queue<int> qx;
    queue<int> qy;
    queue<int> qdir;
    qx.push(0);
    qy.push(startY);
    qdir.push(Pipe::RIGHT);
    while(!qx.empty() || !qy.empty()){
        int x = qx.front();
        int y = qy.front();
        int dir = qdir.front();
        qx.pop();
        qy.pop();
        qdir.pop();
        //check some case
        if(x < 0 || x >= width || y < 0 || y >= height) {
            continue;;
        }
        if(map[y][x].hasWater){
            continue;
        }
        if(map[y][x].canPass[Pipe::getOpposieDir(dir)] == false){
            continue;
        }

        map[y][x].hasWater = true;
        //flow water to connected pipe
        if(x == width - 1 && y == endY){
            flag = true;
        }
        if(map[y][x].canPass[Pipe::UP]){
            qx.push(x);
            qy.push(y - 1);
            qdir.push(Pipe::UP);
        }
        if(map[y][x].canPass[Pipe::RIGHT]){
            qx.push(x + 1);
            qy.push(y);
            qdir.push(Pipe::RIGHT);
        }
        if(map[y][x].canPass[Pipe::DOWN]){
            qx.push(x);
            qy.push(y + 1);
            qdir.push(Pipe::DOWN);
        }
        if(map[y][x].canPass[Pipe::LEFT]){
            qx.push(x - 1);
            qy.push(y);
            qdir.push(Pipe::LEFT);
        }
    }
    return flag;
}

void GameManager::createMapByRandom() {
    vector<vector<int> > grid; //0 = default, 1 = straight, 2 = curved
    for (int i = 0; i < height; ++i) {
        vector<int> row;
        for (int j = 0; j < width; ++j) {
            row.push_back(0);
        }
        grid.push_back(row);
    }

    //generate default path
    createMapByRandomDFS(grid, 0, startY, -1, 0);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if((i == startY && j == 0) || (i == endY && j == width - 1)){
                map[i][j] = Pipe(randomGenerator(IO_PIPE_RONDOM_LIST), true);
            }else if(grid[i][j] == 0){
                map[i][j] = Pipe(randomGenerator(DEFAULT_PIPE_RONDOM_LIST), false);
            }else if(grid[i][j] == 1){
                map[i][j] = Pipe(randomGenerator(STRAIGHT_PIPE_RONDOM_LIST), true);
            }else if(grid[i][j] == 2){
                map[i][j] = Pipe(randomGenerator(CURVED_PIPE_RONDOM_LIST), true);
            }
        }
    }
}

bool GameManager::createMapByRandomDFS(vector<vector<int>> &grid, int x, int y, int lastDir, int depth) {
    if(x == width - 1 && y == endY){
        grid[y][x] = 2;
        return true;
    }
    if(x < 0 || x >= height || y < 0 || y >= width){
        return false;
    }
    if(grid[y][x] != 0){

        return false;
    }
    depth++;
    if(depth > (height + width) * 1.3){
        return false;
    }

    //random direction
    int dirs[] = { 0, 1, 2, 3 }; //up, right, down, left
    int randNum = randomGenerator({20,80});
    if(randNum == 0){ //all direction
        for(int i = 0; i < 4; i++){
            int r = rand() % 4;
            int t = dirs[i];
            dirs[i] = dirs[r];
            dirs[r] = t;
        }
    }else{ //straight prior
        int tmp = dirs[0];
        dirs[0] = dirs[lastDir];
        dirs[lastDir] = tmp;
        for(int i = 1; i < 4; i++){
            int r = rand() % 4;
            int t = dirs[i];
            dirs[i] = dirs[r];
            dirs[r] = t;
        }
    }

    //tyr all direction
    for(int i = 0; i < 4; i++){
        //new position
        int nx = x;
        int ny = y;
        if(dirs[i] == 0){
            ny--;
        }else if(dirs[i] == 1){
            nx++;
        }else if(dirs[i] == 2){
            ny++;
        }else if(dirs[i] == 3){
            nx--;
        }

        if(dirs[i] == lastDir){
            grid[y][x] = 1;
        }else{
            grid[y][x] = 2;
        }

        if(createMapByRandomDFS(grid, nx, ny, dirs[i], depth)){
            return true;
        }else{
            grid[y][x] = 0;
        }
    }

    return false;
}
