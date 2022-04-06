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

using namespace std;

int **createObstacles(int width, int height, int percent){ //returns a 2d array of all of the obstacle coordinates 
    //toggle random
    int widthLimit = width+width -1;
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


void createGrid(int width, int height, int percent){

    int widthLimit = width+width -1;
    const char *row[width+width-1][height];
    int numObstacles = round(width*height*percent*0.01);

    int** obstaclePlaces = createObstacles(width, height, percent);

    int on = 0;
    int yCor = 0;
    int found = 0;

    for(int j = 0; j < height; j++){ //loop through each row space

        for (int i = 0; i < numObstacles; i++){
            if(j == obstaclePlaces[i][0]){
                on = 1;
            }
        }
        
        for(int i = 0; i < widthLimit; i+=2){ //loop through each column space
            //std::cout << "i = " << i << std::endl;
            if(on == 1){
                for (int k = 0; k < numObstacles; k++){
                    if(i == obstaclePlaces[k][1]*2 && j == obstaclePlaces[k][0]){
                        row[j][i] = "-1";
                        found = 1;
                        //std::cout << "Placed an obstacle at i = " << i << " and j = " << j << " x coordinate is " << obstaclePlaces[k][1] << std::endl;
                    } 

                }

                if(found == 0){
                    row[j][i] = "0";
                }

                found = 0;

            } else {
                row[j][i] = "0";
            }

            std::cout << row[j][i];


            if(i < widthLimit-2){
                row[j][i+1] = " ";
                std::cout << row[j][i+1];
            }
            
        }


        on = 0;
        std::cout << std::endl;
    }

}


int main(){

    int width = 10;
    int height = 10;
    int percent = 10;
    char cont = 'y';

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

    createGrid(width, height, percent);


    return 0;

}
