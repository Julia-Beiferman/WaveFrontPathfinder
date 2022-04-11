/*
Name: Julia Beiferman
Date: April 8th 2022
Description: Wave Front Path Finder program. It creates a nxm grid of just zeros then fills it with -1 obstacles based on the percentage the user chooses. Then it uses recursion to look
att the surrounding 8 squares to determine the distance a coordinate is to the goal position. From the start position, a path is then formed to the given start position by again looking
at the adjacent 8 squares and finding the coordinate that is 1 less than the starting position. 
Usage: User is prompted for the grid's width and height, the percentage of obstacles, goal coordinate and start coordinate. Then number and character grids are created.
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

void PrintEnvironment(int** array, char** map, int width, int height){ //prints the environment and the character array

    for(int j = 0; j < height; j++){ //loop through y axis
        for(int i = 0; i < width; i++){ //loop through x axis 
            if(i == 0 && array[j][i] < 10 && array[j][i] > -1){ //evenly space numbers if we have two digits
                if(array[j][i+1] == -1 || array[j][i+1] > 9){ //if the number after is double digit 
                    std::cout << " " << array[j][i] << " ";
                } else {
                    std::cout << " " << array[j][i];
                }
            } else if (array[j][i] == -1 || array[j][i] > 9){ //if the current number is a double digit 
                if(array[j][i+1] > -1 && array[j][i+1] < 10){ //if the number after is a double digit
                    std::cout << array[j][i];
                } else { //else 
                    std::cout << array[j][i] << " ";
                }
            }else if (array[j][i] < 10 && array[j][i] > -1 && (array[j][i+1] == -1 || array[j][i+1] > 9) ){ //if the number is not a double digit and the one after is not
                std::cout << "  " << array[j][i] << " ";
            } else { //else
                std::cout << "  " << array[j][i];
            }
        }

        std::cout << "         |"; //seperate char array from environment array a few spaces 

        for(int i = 0; i < width; i++){
            std::cout << ' ' << map[j][i] << ' '; //print out the character map paralllel to the environment
        }

        std::cout << "|"; //another border to make the char array look nicer
        
        std::cout << std::endl; //end line
    }
    
}

void createObstacles(int** grid, int width, int height, int percent, int startX, int startY){ //returns a 2d array of all of the obstacle coordinates 
    //toggle random
    int numObstacles = round(width*height*percent*0.01);
    //Random obstacle generator
    //Figure out how to prevent double obstacles

    while(numObstacles > 0){ //while we have obstacles to put
        int x = rand() % width; //pick a random number from 0 to width -1
        int y = rand() % height; //same here

        if(grid[y][x] != 0){ //if we run into another obstacle, run the loop again
            continue;
        }else{ //otherwise make that spot an obstacle
            grid[y][x] = -1;
            numObstacles --; //iterate through numObstacles
        }

    }
}

int **createGrid(int width, int height, int percent){ //instantiates the original grid with just zeros, this grid is then altered by other functions

    int widthLimit = width+width -1; 

    int** row = 0; //return grid
    row = new int*[height];

    for(int j = 0; j < height; j++){ //loop through each row space
        row[j] = new int[width];
        for(int i = 0; i < widthLimit; i++){ //loop through each column space
            row[j][i] = 0; //creates grid row by row
        }
    }

    return row;
}

void waveDistance(int** grid, int width, int height, int posX, int posY, int goalX, int goalY, int step){ //recursive function to determine the distance of a coordinate from goal position
    
    if(posX + 1 > width || posY + 1 > height || posX < 0 || posY < 0){ // in case things are out of bound end the function
        return;
    }

    if(grid[posY][posX] == -1){ // if we run into an obstacle end the function
        return;

    }

    int dx[] = {-1,0,1,-1,1,-1,0,1}; //every combination we can add for y and x to get the surrounding 8 squares
    int dy[] = {-1,-1,-1,0,0,1,1,1};


    if(grid[posY][posX] == 0 || grid[posY][posX] > step){ //check if we run into a zero or the value is greater than step aka. not the goal
        step = step+1; //add 1 to step or distance
        grid[posY][posX] = step; //assign value to the position
        for(int i = 0; i < 8; i++){
            int x = posX + dx[i]; // iterates through all addition or subtraction combinationss
            int y = posY + dy[i];
            waveDistance(grid, width, height, x, y, goalX, goalY, step); //recursively call function with all possible combinations

        }

    } else if(grid[posY][posX] == 1){ //if you are at the goal
        for(int i = 0; i < 8; i++){
            int x = posX + dx[i]; // iterates through all addition or subtraction combinationss
            int y = posY + dy[i];
            waveDistance(grid, width, height, x, y, goalX, goalY, step); //recursively call function
        }

    }

    return;
}


char** creatCharArray(int** grid, int width, int height, int goalX, int goalY, int startX, int startY){ //create the character array which we draw parallel to the environment

    char** charMap = new char*[height];;

    for(int j = 0; j < height; j++){ //loop through our original grid
        charMap[j] = new char[width];
        for(int i = 0; i < width; i++){
            if(grid[j][i] == -1){ //if there is an obstacle
                charMap[j][i] = 178; //print asci 178
            } else {
                charMap[j][i] = ' '; //otherwise just print a blank space
            }
        }
    }

    //define goal and start positions
    charMap[startY][startX] = '@';
    charMap[goalY][goalX] = '$';

    return charMap;

}


void pathFinder(int** grid, char** map, int width, int height, int goalX, int goalY, int startX, int startY){ //starts at the start positions to find a path to the goal position
    
    if(startY == goalY && startX == goalX){ //check if out of bounds
        return;
    }

    int numToFind = grid[startY][startX] - 1; // we want to find a number that is a smaller distance than our current position


    int dx[] = {-1,0,1,-1,1,-1,0,1};
    int dy[] = {-1,-1,-1,0,0,1,1,1};

    for(int i = 0; i < 8; i++){ //loop through surrouding 8 square similar in the waveDistance function
        
        int x = startX + dx[i];
        int y = startY + dy[i];
        
        if (x > width || x < 0 || y > height || y < 0){ //if out of bounds
            continue;
        }

        if(grid[y][x] == numToFind){ //if we run into the number that we want to get
            map[y][x] = '*'; //mark our path here
            pathFinder(grid, map, width, height, goalX, goalY, x, y); //recursively call function for 8 surrounding squares

            return;
        }
    }
}


int main(int argc, char *argv[]){

    //instantiate all prompted variables
    int width = 10;
    int height = 10;
    int percent = 10;
    int goalX = 0;
    int goalY = 0;
    int startX = 0;
    int startY = 0;
    char cont = 'n';

    if(argc > 1){ //folly attempt at extra credit
        if(strcmp("-f", argv[1]) == 0){
            //std::cout << "file mode";
        }
    }

    std::cout << "Welcome to Julia's CSE240 WaveFront Pather " << std::endl;
    std::cout << "Please tell me about the grid you want to generate." << std::endl; 
    std::cout << "Enter the width (at least 10): ";
    cin >> width;
    std::cout << "Enter the height (at least 10): ";
    cin >> height;

    std::cout << "Enter the percent of impassible terrain (0 – 100): ";
    cin >> percent;
    
    if (percent > 35){ //if percent given is higher than 35%
        while(cont != 'y'){ //keep prompting the user if they want to continue
            std::cout << "Having a value greater than 35% might create poor results, do you wish to continue? (y/n): ";
            cin >> cont;
            if(cont == 'y'){
                break;
            }
            //new percentage
            std::cout << "Enter the percent of impassible terrain (0 – 100): ";
            cin >> percent;
            if(percent < 35){
                break;
            }

        }
    }

    int** grid = createGrid(width, height, percent); //instantiate grid
    createObstacles(grid, width, height, percent, startX, startY); //create the obstacles

    //first prompt for goal position
    std::cout << "Please enter the Goal Position X: ";
    cin >> goalX;
    std::cout << "Please enter the Goal Position Y: ";
    cin >> goalY;


    while (goalX > width-1 || goalY > width-1 || goalX < 0 || goalY < 0 || grid[goalY][goalX] == -1 ){ //check if goal position is inside an obstacle or is out of bounds
        std::cout << "Sorry, that position is inside an obstacle" << std::endl;

        //reprompt the user for new coordinates
        std::cout << "Please enter the Goal Position X: "; 
        cin >> goalX;
        std::cout << "Please enter the Goal Position Y: ";
        cin >> goalY;

    }

    //first prompt for start position
    std::cout << "Please enter the Start Position X: ";
    cin >> startX;
    std::cout << "Please enter the Start Position Y: ";
    cin >> startY;

    while (startX > width-1 || startY > width-1 || startX < 0 || startY < 0 || grid[startY][startX] == -1){ //checks if start position is out of bounds or is in an obstacle
        std::cout << "Sorry, that position is inside an obstacle" << std::endl;

        //reprompt user
        std::cout << "Please enter the Start Position X: ";
        cin >> startX;
        std::cout << "Please enter the Start Position Y: ";
        cin >> startY;
    }

    grid[goalY][goalX] = 1;
    waveDistance(grid, width, height, goalX, goalY, goalX, goalY, 1); //call waveDistance to alter grid
    char** map = creatCharArray(grid, width, height, goalX, goalY, startX, startY); //create character array

    pathFinder(grid, map, width, height, goalX, goalY, startX, startY); //call pathFinder to alter character array (map)
    
    //set goal and start positions
    map[startY][startX] = '@';
    map[goalY][goalX] = '$'; 

    //finally print both arrays
    PrintEnvironment(grid, map, width, height);
    return 0;

}
