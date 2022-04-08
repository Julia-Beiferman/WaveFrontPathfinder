/*
Name: Julia Beiferman
Date: April 8th 2022
Description: <short description of code in file/project>
Usage: <how to use your program, including syntax for launching the program (command line
arguments)>
*/ 

#include <stack>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cmath>
#include <iomanip>

using namespace std;

int **createObstacles(int width, int height, int percent){ //returns a 2d array of all of the obstacle coordinates 
    //toggle random
    int numObstacles = round(width*height*percent*0.01);

    //Random obstacle generator
    //Figure out how to prevent double obstacles
    int** obstaclePlaces = 0; 
    obstaclePlaces = new int*[numObstacles];

    int v1 = rand() % height;
    int v2 = rand() % width;

    for(int i = 0; i < numObstacles; i++){
        v2 = rand() % width;
        v1 = rand() % height;
        obstaclePlaces[i] = new int[2];

        obstaclePlaces[i][0] = v1; //0 represents the y coordinate
        obstaclePlaces[i][1] = v2; //1 represents the x coordinate

        //std::cout << "Obstacle coordinates: " << obstaclePlaces[i][0] <<  obstaclePlaces[i][1] << std::endl;

    }

    return obstaclePlaces;

}



void PrintEnvironment(int** array, char** map, int width, int height){

    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if(array[j][i+1] == -1 || array[j][i+1] > 9){ //evenly space numbers if we have two digits
                std::cout << " " << array[j][i];
            } else if (i == 0 && (array[j][i] == -1 || array[j][i] > 9)){
                std::cout << array[j][i] << " ";
            } else {
                std::cout << " " << array[j][i] << " ";
            }
        }
        std::cout << std::endl;
    }

    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            std::cout << map[j][i] << ' ';
        }
        std::cout << std::endl;
    }
}


int **createGrid(int width, int height, int percent){

    int widthLimit = width+width -1;
    //const char *row[widthLimit][height];

    int** row = 0;
    row = new int*[height];


    int numObstacles = round(width*height*percent*0.01);

    int** obstaclePlaces = createObstacles(width, height, percent);

    int on = 0;
    int found = 0;

    for(int j = 0; j < height; j++){ //loop through each row space
        row[j] = new int[width];

        for (int i = 0; i < numObstacles; i++){
            if(j == obstaclePlaces[i][0]){
                on = 1;
            }
        }
        
        for(int i = 0; i < widthLimit; i++){ //loop through each column space
            //std::cout << "i = " << i << std::endl;
            if(on == 1){
                for (int k = 0; k < numObstacles; k++){
                    if(i == obstaclePlaces[k][1] && j == obstaclePlaces[k][0]){ //checks if i and j match the obstacle coordinate
                        row[j][i] = -1;
                        found = 1;
                        //std::cout << "Placed an obstacle at i = " << i << " and j = " << j << " x coordinate is " << obstaclePlaces[k][1] << std::endl;
                    } 

                }

                if(found == 0){
                    row[j][i] = 0;
                }

                found = 0;

            } else {
                row[j][i] = 0;
            }

            //std::cout << row[j][i];
            
        }
        on = 0; //sets the on switch back to zero
    }

    return row;
}

int waveDistance(int posX, int posY, int goalX, int goalY){ //recursive function to determine the distance of a coordinate from goal position
    int distance = 1;

    //edit this so it accounts for obstacles

    if(posX != goalX && posY != goalY){
        int xAdd = 1;
        int yAdd = 1;

        if (posX > goalX){
            xAdd = -1;
        }
        if (posY > goalY){
            yAdd = -1;
        }

        return distance + waveDistance(posX+xAdd, posY+yAdd, goalX, goalY);

    } else if(posX != goalX || posY != goalY){
        if (posX < goalX){
            return distance + waveDistance(posX+1, posY, goalX, goalY);
        } else if (posX >goalX){
            return distance + waveDistance(posX-1, posY, goalX, goalY);
        }

        if (posY < goalY){
            return distance + waveDistance(posX, posY+1, goalX, goalY);
        } else if (posY >goalY){
            return distance + waveDistance(posX, posY-1, goalX, goalY);
        }

    } else {
        return 1;
    }

    return distance;

}

int** createWave(int** grid, int width, int height, int goalX, int goalY){
    
    grid[goalY][goalX] = 1;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if(grid[j][i] == 0){ 
                int distance = waveDistance(i, j, goalX, goalY);
                grid[j][i] = distance;
            }
        }
    }

    return grid;
}

char** creatCharArray(int** grid, int width, int height, int goalX, int goalY, int startX, int startY){

    char** charMap = new char*[height];;

    for(int j = 0; j < height; j++){
        charMap[j] = new char[width];
        for(int i = 0; i < width; i++){
            if(grid[j][i] == -1){ 
                charMap[j][i] = 178;
            } else {
                charMap[j][i] = ' ';
            }
        }
    }

    //define goal and start positions
    charMap[startY][startX] = '@';
    charMap[goalY][goalX] = '$';

    return charMap;

}

void pathFinder(int** grid, char** map, int width, int height, int goalX, int goalY, int startX, int startY){
    int** path;

}


int main(){

    int width = 10;
    int height = 10;
    int percent = 10;
    //char cont = 'y';
    int goalX = 0;
    int goalY = 0;
    int startX = 0;
    int startY = 0;

    std::cout << "Welcome to CSE240 WaveFront Pather " << std::endl;
    std::cout << "Please tell me about the grid you want to generate." << std::endl; 
    std::cout << "Enter the width (at least 10): ";
    cin >> width;
    std::cout << "Enter the height (at least 10): ";
    cin >> height;

    std::cout << "Enter the percent of impassible terrain (0 – 100): ";
    cin >> percent;
    //std::cout << "Having a value greater than 35% might create poor results, do you wish to continue? (y/n): " << std::endl;
    //cin >> cont;

    std::cout << "Please enter the Goal Position X: ";
    cin >> goalX;
    std::cout << "Please enter the Goal Position Y: ";
    cin >> goalY;

    std::cout << "Please enter the Start Position X: ";
    cin >> startX;
    std::cout << "Please enter the Start Position Y: ";
    cin >> startY;

    //goalX = goalX - 1; //to get more accurate goal points intstead of (0,0) being the first spot
    //goalY = goalY - 1;

    int** grid = createGrid(width, height, percent);
/*     if(grid[goalY][goalX] == -1){
        std::cout << "Sorry, that position is inside an obstacle";
    } */


    int** waveGrid = createWave(grid, width, height, goalX, goalY);
    char** map = creatCharArray(grid, width, height, goalX, goalY, startX, startY);

    PrintEnvironment(waveGrid, map, width, height);


    return 0;

}
