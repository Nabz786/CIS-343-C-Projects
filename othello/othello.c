//***************************************************
// Filename: othello.c
//
// Author: Nandigam
// Nabeel Vali
//***************************************************

#include "othello.h"

/**********************************************************************
 *Displays the Board as (SIZE x Size grid) on console
 *@Param Board, the game board we wish to draw
 *********************************************************************/
void displayBoard(char board[][SIZE])
{
	printf("\n");
	for (int i = 0; i < SIZE; i++) {
		printf((i == 0 ? "%5d" : "%3d"), i+1);
	}
	printf("\n");

	for (int i = 0; i < SIZE; i++) {
		printf("%2d", i+1);
		for (int j = 0; j < SIZE; j++) {
			printf("%3c", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/**********************************************************************
 *Initializes the board with start configuration of discs
 *@Param Board: Board we wish to initialize
 *********************************************************************/
void initializeBoard(char board[][SIZE])
{
	//We start by setting all positions on the board to -

	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			board[i][j] = EMPTY;
		}
	}

	//Set the positions of the four initial pieces

	board[3][3] = BLACK;
	board[3][4] = WHITE;
	board[4][3] = WHITE;
	board[4][4] = BLACK;

}

/**********************************************************************
 *Returns true if moving the disc to location row,col is valid
 *else returns false
 *@Param board: The board we check the move on
 *@Param row: The row we wish to move to
 *@Param col: The col we wish to move to
 *@Param disc: The current play for which we are validating the move
 *********************************************************************/
bool isValidMove(char board[][SIZE], int row, int col, char disc)
{
	//If A board position is currently occupied return false
	if(board[row][col] != EMPTY) {
		return false;
	}	

	//Check up
	for(int i = row - 1; i > -1; i--) {
		if(i -1 < 0) {
			break;
		}
		if(board[i][col] != disc && board[i][col]!= EMPTY 
				&& board[i-1][col]==disc) {
			return true;
		} else if(board[i][col] == EMPTY || board[i][col] == disc) {
			break;
		}
	}


	//Check Down
	for(int i = row + 1; i < SIZE; i++) {
		if (i + 1 >= SIZE) {
			break;
		}
		if(board[i][col] != disc && board[i][col]!= EMPTY 
				&& board[i+1][col]==disc) {
			return true;
		} else if(board[i][col] == EMPTY || board[i][col] == disc) {
			break;
		}
	}

	//Check Left
	for(int i = col -1; i > -1; i--) {
		if(i-1 < 0) {
			break;
		}
		if(board[row][i] != disc && board[row][i]!= EMPTY 
				&& board[row][i-1] == disc) {
			return true;
		} else if(board[row][i] == EMPTY || board[row][i]==disc) {
			break;
		}
	}

	//Check Right
	for(int i = col + 1; i < SIZE; i++) {
		if(i+1 > SIZE) {
			break;
		}
		if(board[row][i] != disc && board[row][i]!= EMPTY 
				&& board[row][i+1]==disc) {
			return true;
		} else if (board[row][i] == EMPTY || board[row][i] == disc) {
			break;
		}
	}


	//Temp value used to iterate through columns 
	//When moving diagonally
	int colIter = 0;

	//Check Diag-Up-Left
	colIter = col + 1;
	for(int i = row + 1; i < SIZE; i++) {
		if(colIter+1 >= SIZE || i + 1 >=SIZE) {
			break;
		}

		if(board[i][colIter] != disc && board[i][colIter] != EMPTY 
				&& board[i+1][colIter+1] == disc) {
			return true;
		} else if (board[i][colIter] == EMPTY || board[i][colIter]==disc) {
			break;
		}
		colIter++;
	}

	//Check Diag Up-right
	colIter = col - 1;
	for(int i = row + 1; i < SIZE; i++) {
		if(colIter -1 < 0 || i + 1 >= SIZE) {
			break;
		}
		if(board[i][colIter] != disc && board[i][colIter] != EMPTY 
				&& board[i+1][colIter - 1] == disc) {
			return true;
		} else if (board[i][colIter] == EMPTY || board[i][colIter] == disc) {
			break;
		}
		colIter--;
	}	

	//Cjeck Diag bottom-right
	colIter = col + 1;
	for(int i = row - 1; i > -1; i--) {
		if(colIter -1 >= SIZE || i - 1 < 0) {
			break;
		}

		if(board[i][colIter] != disc && board[i][colIter] != EMPTY 
				&& board[i-1][colIter+1] == disc) {
			return true;
		} else if(board[i][colIter] == EMPTY || board[i][colIter] == disc) {
			break;
		}	
		colIter++;
	}

	//Check Diag-Bottom-Left
	colIter = col - 1;
	for(int i = row -1; i > -1; i--) {
		if(colIter -1 < 0 || i -1 <0) {
			break;
		}

		if(board[i][colIter] != disc && board[i][colIter] != EMPTY 
				&& board[i-1][colIter-1] == disc) {
			return true;
		} else if(board[i][colIter] == EMPTY || board[i][colIter] == disc) {
			break;
		}
		colIter--;
	}

	return false;
}

/**********************************************************************
 *Places the disc at location row, col and flips the opponent discs 
 *as needed
 *@Param: Board: Instance of board where we will move the piece
 *@Param row: Row to move to and write over
 *@Param col: Col to move to and write over
 *@Param disc: Current Player disc
 *********************************************************************/
void placeDiscAt(char board[][SIZE], int row, int col, char disc)
{
	board[row][col] = disc;

	/* Number of times to write in a direction*/
	int numWrite = 0;

	/* Column iterator when iterating diagonally*/
	int colIter = 0;


	//To check up, down, left and right
	//We simply loop away from our newly placed cell
	//Checking to see if we find another disc of the same player
	//With enemies bounded between the two
	//If we do, We write in the direction n times

	//Check move up
	for(int i = row + 1; i < SIZE; i++) {
		numWrite++;
		if(i + 1 >= SIZE) {
			break;
		}
		if(board[i][col] != disc && board[i][col]!= EMPTY &&
				board[i+1][col] == disc) {
			for(int j = row + 1; j < SIZE; j++) {
				if( numWrite > 0) {
					board[j][col] = disc;
					numWrite--;
				}
			}
		} else if (board[i][col] == EMPTY || board[i][col] == disc) {
			break;
		} 
	}

	numWrite = 0;
	//Check Move down
	for(int i = row - 1; i > -1; i--) {
		numWrite++;
		if(i - 1 < 0) {
			break;
		}
		if(board[i][col] != disc && board[i][col] != EMPTY  && 
				board[i-1][col] == disc) {
			for(int j = row - 1; j > -1; j--) {
				if(numWrite > 0) {
					board[j][col] = disc;
					numWrite--;
				}
			}
		} else if (board[i][col] == EMPTY || board[i][col] == disc) {
			break;
		} 
	}

	numWrite = 0;
	//Check Move right
	for(int i = col - 1; i > -1; i--) {
		numWrite++;
		if(i -1 < 0) {
			break;
		}
		if(board[row][i] != disc && board[row][i] != EMPTY &&
				board[row][i-1] == disc) {
			for(int j = col - 1; j > -1; j--) {
				if(numWrite > 0) {
					board[row][j] = disc;
					numWrite--;
				}
			}
		} else if (board[row][i] == EMPTY || board[row][i] == disc) {
			break;
		} 
	}

	numWrite = 0;
	//Check Move left
	for(int i = col + 1; i < SIZE; i++) {
		numWrite++;
		if(i + 1 >= SIZE) {
			break;
		}
		if(board[row][i] != disc && board[row][i] != EMPTY &&
				board[row][i+1] == disc) {
			for(int j = col + 1; j < SIZE; j++) {
				if(numWrite > 0) {
					board[row][j] = disc;
					numWrite--;
				}
			}
		} else if(board[row][i] == EMPTY || board[row][i] == disc) {
			break;
		} 
	}


	//To perform Diagonal Checks we use col iter 
	//So that we can iterate through columns and rows
	//at the same time. The writing functionality
	//is the same as the basic moves above

	numWrite = 0;
	colIter = col - 1;
	//Check Up Right
	for(int i = row + 1; i < SIZE; i++) {
		numWrite++;
		if(colIter-1 < 0 || i + 1 >= SIZE){
			break;
		}
		if(board[i][colIter] != disc && board[i][colIter]!=EMPTY &&
				board[i+1][colIter-1] == disc) {
			int colTemp = col - 1;
			for(int j = row + 1; j < SIZE; j++) {
				if(numWrite > 0) {
					board[j][colTemp] = disc;
					colTemp--;
					numWrite--;
				}
			}
		} else if (board[i][colIter] == EMPTY || board[i][colIter] == disc) {
			break;
		}
		colIter--;
	}

	numWrite = 0;
	colIter = col + 1;
	//Check Up Left
	for(int i = row + 1; i < SIZE; i++) {
		numWrite++;
		if(colIter + 1 >= SIZE || i + 1 >= SIZE) {
			break;
		}

		if(board[i][colIter] != disc && board[i][colIter] != EMPTY && 
				board[i+1][colIter+1] == disc) {
			int colTemp = col + 1;
			for(int j = row + 1; j < SIZE; j++) {
				if(numWrite > 0) {
					board[j][colTemp] = disc;
					colTemp++;
					numWrite--;
				}
			}
		} else if(board[i][colIter] == EMPTY || board[i][colIter] == disc) {
			break;
		} 
		colIter++;
	}

	numWrite = 0;
	colIter = col + 1;
	//Check down-left
	for(int i = row - 1; i > -1; i--) {
		numWrite++;
		if(colIter + 1 >= SIZE || i - 1 < 0) {
			break;
		}
		if(board[i][colIter] != disc && board[i][colIter] != EMPTY 
				&& board[i-1][colIter+1] == disc) {
			int colTemp = col + 1;
			for(int j = row - 1; j > -1; j--) {
				if(numWrite > 0) {
					board[j][colTemp] = disc;
					colTemp++;
					numWrite--;
				}
			}
		}else if(board[i][colIter] == EMPTY || board[i][colIter] == disc) {
			break;
		} 
		colIter++;
	}

	numWrite = 0;
	colIter = col - 1;
	//Check down-right
	for(int i = row - 1; i > -1; i--) {
		numWrite++;
		if(colIter - 1 < 0 || i - 1 < 0) {
			break;
		}
		if(board[i][colIter] != disc && board[i][colIter] != EMPTY 
				&& board[i-1][colIter-1] == disc) {
			int colTemp = col - 1;
			for(int j = row - 1; j > -1; j--) {
				if(numWrite > 0) {
					board[j][colTemp] = disc;
					colTemp--;
					numWrite--;
				}
			}
		}else if (board[i][colIter] == EMPTY || board[i][colIter] == disc) {
			break;
		} 
		colIter--;
	}
}

/**********************************************************************
 *Returns true if a valid move for disc is available; else returns f
 *@Param Board: Board we check on
 *@Param disc: current player disc
 **********************************************************************/
bool isValidMoveAvailable(char board[][SIZE], char disc)
{
	//See if we can place a disc at any position on the board
	//If we can return true, else return false
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			if(isValidMove(board, i, j, disc)) {
				return true;
			}
		}
	}

	return false;
}

/**********************************************************************
 *Returns true if the board is fully occupied with discs; else returns
 *false
 *@Param board: Board to check
 *********************************************************************/
bool isBoardFull(char board[][SIZE])
{
	//Loop through the entire board to see if we can find an 
	//empty spot, if we do the board is not empty
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			if(board[i][j] == EMPTY) {
				return false;
			}
		}
	}

	return true;	
}

/**********************************************************************
 *Returns true if either the board is full or a valid move is not 
 *available for either disc
 *@Param Board: Board to check over
 *********************************************************************/
bool isGameOver(char board[][SIZE])
{
	//The board either has to be full, or there cannot be any 
	//moves for both players to be gameover
	if(isBoardFull(board) || (!isValidMoveAvailable(board, WHITE) && 
		!isValidMoveAvailable(board, BLACK))) {
		return true;
	}

	return false;	
}

/**********************************************************************
 *If there is a winner, it returns the disc (BLACK or WHITE) 
 *associated with the winner. In case of a tie, it returns EMPTY
 *@Param Board: Board to check over
 *********************************************************************/
char checkWinner(char board[][SIZE])
{
	/** Black disc count**/
	int bCount = 0;

	/** White disc count**/
	int wCount = 0;

	//Loop through board counting each players discs
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			if(board[i][j] == 'W') {
				wCount++;
			} else {
				bCount++;
			}	
		}
	}

	//The player with the larger disc count is the winner
	if(wCount > bCount) {
		return WHITE;
	} else if (bCount > wCount) {
		return BLACK;
	} else {
		return EMPTY;
	}
	return EMPTY;
}
