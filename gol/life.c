#include "life.h"
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************
 * Creates new memory for a "grid".
 * Param x is the height
 * Param y is the width.
 *********************************************************************/
char** get_grid(int x, int y){

	//If either the width or height of our board is less than one we exit
	if((x < 1 || y < 1) || (x > 30 || y > 30)) {
		printf("\nInvalid Board Dimensions! Now exiting\n");
		exit(0);
	}
	
	//Allocate memory for the game board
	char** grid = (char **)malloc(y * sizeof(char*));

	//Allocate memory for the spaces in the grid	
	for(int i = 0; i < y; i++) {
		grid[i] = (char *)malloc(x * sizeof(char));
	}
	return grid;
}

/**********************************************************************
 * print_grid attempts to print an x height
 * by y width grid stored at the location
 * provided by grid
 * Param X: Width
 * Param Y: height 
 * Param grid: Grid to print
 *********************************************************************/
void print_grid(int x, int y, char** grid){
	int r,c;
	
	//Loop through the grid printing the entries row by row	
	for(r = 0; r < x; r++) {
		for(c = 0; c < y; c++) {
			if(grid[r][c] == 1) {
				printf(" 1");
			} else {
				printf(" 0");
			}
		}
		printf("\n");
	}
	printf("\n");
}

/**********************************************************************
 * mutate takes a grid and mutates that grid
 * according to Conway's rules.  A new grid
 * is returned.
 * Param x: Width of grid
 * Param y: Height of grid
 * Param grid: current Grid
 * Return Grid: Newly Mutated Grid
 *********************************************************************/
char** mutate(int x, int y, char** grid){
	
	//Allocate memory for our new grid
	char ** newGrid = (char **)malloc(y * sizeof(char*));

	//Allocate memory for the space in the grid
	for(int i = 0; i < y; i++) {
		newGrid[i] = (char *)malloc(x * sizeof(char));
	}		

	//Loop through the grid to mutate according to conways rules
	for(int r = 0; r < x; r++) {
		for(int c = 0; c < y; c++) {
			newGrid[r][c] = grid[r][c];
			//We obtain the number of neigbors for a cell
			int numNeigh = get_neighbors(r,c,x,y, grid);
			if(numNeigh < 2 && newGrid[r][c] == 1) {
				newGrid[r][c] = 0;
			} else if (newGrid[r][c] == 1 && (numNeigh == 2 || numNeigh == 3)) {
				newGrid[r][c] = 1;
			} else if (numNeigh > 3 && newGrid[r][c] == 1) {
				newGrid[r][c] = 0;
			} else if (numNeigh == 3 && newGrid[r][c] == 0) {
				newGrid[r][c] = 1;
			}
		}
	}
	
	//We no longer need the old gird
	//We free the memory it took up
	for(int g = 0; g < y; g++) {
		free(grid[g]);
	}
	free(grid);
	return newGrid;
}

/**********************************************************************
 * Returns the number of live neighbors a cell has
 * @Param i: Current Row
 * @Param j: Current Col
 * @Param x: Current Width
 * @Param y: Current Height
 * @Param grid: Current Grid
 * @Return int: Number of neighbors a cell has
 */
int get_neighbors(int i, int j, int x, int y, char** grid){

	//Search each space next to our specified cell and determine
	//if it has a neighbor
	int numNeigh = 0;

	//We are given the position of the cell we want to check via i = row, c = col;
	//We check the neighbers
	//m = row, n = col
	for(int m = -1; m <= 1; m++) {
		for(int n = -1; n <= 1; n++) {
			if (i == 0 && (j!=0 || j!= y-1) &&m == -1 ) {
				continue;
			} else if (j == 0 && (i != 0|| i!=x-1)&&n == -1) {
				continue;
			} else if(i == x -1 && (j!= 0 || j != y -1) && m == 1){
				continue;
			} else if(j == y -1 && (i != 0 || i != x -1) && n == 1) {
				continue;
			} else if (i == 0 && j == 0 && (m == -1 || n == -1)) {
				continue;
			} else if (i == 0 && (j == y - 1) && (m == -1 || n == 1)) {
				continue;
			} else if ((i == x - 1) && (j == y - 1) && (m == 1 || n == 1)) {
				continue;
			} else if ((i == x -1) && (j == 0) && (m == 1 || n == -1)) {
				continue;
			} else {
				if(grid[m + i][n + j] == 1) {
					numNeigh++;
				}
			}
		}
	}	
	if(grid[i][j] == 1) {
		numNeigh--;
	}
	//Offset numNeigh by 1 to account for looping over the cell we are looking at
	return numNeigh;
}

