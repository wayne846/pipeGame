/***********************************************************************
 * File: gameManager.cpp
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215058
 * Update Date: 2024/04/24
 * Description: This program is responsible for the main functions, including reading maps, generating maps, etc.
***********************************************************************/
#include "gamemanager.h"
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <fstream>

bool GameManager::isSuccess = false;

// Intent: To give random pipe type.
// Pre: Give shape when spawning pipes.
// Post: The function returns the type
int GameManager::randomGenerator(vector<int> v) {
    int sum = 0;//store vector sum.

    for(int i = 0; i < v.size(); i++) {
        sum += v[i];//calculate vector sum.
    }

    int randNum = rand() % 100;//create random number.

    for(int i = 0; i < v.size(); i++) {
        //If type is within the range, return type.
        if (randNum < v[i] * 100 / (double)sum) {
            return i;
        }

        //Subtract non-matching values
        randNum -= v[i] * 100 / (double)sum;
    }

    return 0;
}

// Intent: Create map by height and width.
// Pre: When the user inputs the length and width to generate a map
// Post: The function returns create the map
GameManager::GameManager(int height, int width) {
	this->height = height;
	this->width = width;
	this->playerY = 0;
	this->playerX = 0;
	this->map = std::vector<std::vector<Pipe*>>(height, std::vector<Pipe*>(width));
	this->printmap = vector<std::vector<int>>(height * 3, std::vector<int>(width * 3));

	//generate map
	srand(time(NULL));

	startY = rand() % height;
	endY = rand() % height;
	createMapByRandom();

	isSuccess = true;
}

// Intent: Read map from file
// Pre: When the user use read map by txt
// Post: The function returns create the map
GameManager::GameManager() {
    //open the windows
    ifstream file;
    file.open("test.txt");

    if (!file.is_open()){
        qDebug() << "cannot open file";
        return ;
    }

    file >> this->height;
    file >> this->width;
    this->playerY = 0;
    this->playerX = 0;
    this->startY = 0;
    this->endY = height - 1;
    this->map = std::vector<std::vector<Pipe*>>(height, std::vector<Pipe*>(width));
    this->printmap = vector<std::vector<int>>(height * 3, std::vector<int>(width * 3));

    for (int i = 0; i < height * 3; i++) {
        for (int j = 0; j < width * 3; j++) {

            //read one character from file
            char character;
            file >> character;

            //if read P set pipe
            if (character == 'P')
                printmap[i][j] = 1;
            else
                printmap[i][j] = 0;
        }
    }

    for (int i = 0; i < height * 3; i += 3) {
        for (int j = 0; j < width * 3; j += 3) {
            for (int dir = 0; dir < 4; dir++) {
                for (int type = 0; type < 4; type++) {

                    int count = 0;
                    Pipe compare;
                    vector<vector<int>> compareVector;
                    compareVector = vector<std::vector<int>>(3, std::vector<int>(3));
                    compareVector = compare.getShap(type, dir);

                    for (int k = i; k < i + 3; k++) {
                        for (int l = j; l < j + 3; l++) {

                            //compare 3*3vector and pipes,if equal,count++
                            if (printmap[k][l] == compareVector[k - i][l - j])
                                count++;
                        }
                    }

                    //if 3*3vector and pipes all equal,set the corresponding water pipe
                    if (count == 9) {
                        this->map[i / 3][j / 3] = new Pipe(type, dir);
                    }
                }
            }
        }
    }

    file.close();
    isSuccess = true;
}

// Intent: Determine the status of water pipe connections
// Pre:After the user selects the water pipe
// Post:The function returns reached the destination and the connection situation
bool GameManager::isEnd() {
    //clean water
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            this->map[i][j]->hasWater = 0;
        }
    }

    //if start not connection return false
    if(map[startY][0]->canPass[Pipe::LEFT] == false){
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
        if(map[y][x]->hasWater){
            continue;
        }
        if(map[y][x]->canPass[Pipe::getOpposieDir(dir)] == false){
            continue;
        }

        map[y][x]->hasWater = true;
        //flow water to connected pipe
        if(x == width - 1 && y == endY && map[y][x]->canPass[Pipe::RIGHT]){
            flag = true;
        }
        if(map[y][x]->canPass[Pipe::UP]){
            qx.push(x);
            qy.push(y - 1);
            qdir.push(Pipe::UP);
        }
        if(map[y][x]->canPass[Pipe::RIGHT]){
            qx.push(x + 1);
            qy.push(y);
            qdir.push(Pipe::RIGHT);
        }
        if(map[y][x]->canPass[Pipe::DOWN]){
            qx.push(x);
            qy.push(y + 1);
            qdir.push(Pipe::DOWN);
        }
        if(map[y][x]->canPass[Pipe::LEFT]){
            qx.push(x - 1);
            qy.push(y);
            qdir.push(Pipe::LEFT);
        }
    }
    return flag;
}

// Intent: Create map
// Pre:After createMapByRandom call
// Post:The function return create map
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

    //create pipe
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if((i == startY && j == 0) || (i == endY && j == width - 1)){
                map[i][j] = new Pipe(randomGenerator(IO_PIPE_RANDOM_LIST), true);
            }else if(grid[i][j] == 0){
                map[i][j] = new Pipe(randomGenerator(DEFAULT_PIPE_RANDOM_LIST), false);
            }else if(grid[i][j] == 1){
                map[i][j] = new Pipe(randomGenerator(STRAIGHT_PIPE_RANDOM_LIST), true);
            }else if(grid[i][j] == 2){
                map[i][j] = new Pipe(randomGenerator(CURVED_PIPE_RANDOM_LIST), true);
            }
        }
    }


    //check for not end game when start
    //random rotate all pipe until not finish game or 100 times;
    for(int t = 0; t < 100; t++){
        if(!isEnd()) break;

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                int rotateTimes = randomGenerator(DIR_RANDOM_LIST);
                for(int k = 0; k < rotateTimes; k++){
                    map[i][j]->rotate();
                }
            }
        }
    }
}

// Intent: Create map by BFS
// Pre:After the user enter height and width
// Post:The function the data used to generate map
bool GameManager::createMapByRandomDFS(vector<vector<int>> &grid, int x, int y, int lastDir, int depth) {
    if(x == width - 1 && y == endY){
        grid[y][x] = 2;
        return true;
    }
    if(x < 0 || x >= width || y < 0 || y >= height){
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

// Intent: Delete map
// Pre:when the program ends
GameManager::~GameManager(){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j] != NULL){
                delete(map[i][j]);
                map[i][j] = NULL;
            }
        }
    }

    map.clear();
}
