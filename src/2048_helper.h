#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

const int board_size = 5;


void move_left(int board[][5], int board_size = 5)
{
	//CODE HERE

	/*
	when moving left, iterate through the board and look for if there are 2 matching types next to each other. if there are, double the value of the leftmost one, and shift all other tiles over.
	*/
	//Iterating through each row.
	for(int row=0;row<board_size;row++){
		//Iterating through each column, except the last one
		for(int col=0; col<board_size-1; col++){
			//Checks for if there is another element with the same value to the right of the current value
			if((board[row][col] == board[row][col+1]) && board[row][col] != 0){
				//Double the current value, empty the cell to the right of the current space
				board[row][col] *= 2;
				board[row][col+1] = 0;
			}

			//Shifting everything to the left

			//If the current cell is empty, look forward in the array for a cell to move over.
			if(board[row][col] == 0){
				//Checking future cells.
				for(int i = col; i < board_size; i++)
					if(board[row][i] !=0){
						board[row][col] = board[row][i];
						board[row][i] = 0;
						break;//this should only exit the for loop, right??
					}
			}
		}
	}	
}

void move_right(int board[][5], int board_size = 5)
{
	//CODE HERE
}

void move_up(int board[][5], int board_size = 5)
{
	//CODE HERE
}

void move_down(int board[][5], int board_size = 5)
{
	//CODE HERE
}


void print_board(int board[][5], int board_size = 5)
{
	cout << endl << "\t-----------------------------------------" << endl;

	for (int r = 0; r < board_size; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			if(board[r][c] > 0)
				cout << "\t|" << right << setw(6) << setfill(' ') << board[r][c];
			else
				cout << "\t|" << right << setw(6) << setfill(' ') << " ";

			//cout << board[r][c] << "\t|\t";
		}
		cout << "\t|" << endl;
		cout << "\t-----------------------------------------" << endl;
	}

	cout << "\t" << endl << endl;
}


void insert_random(int board[][5], int board_size = 5)
{
	int r, c;
	//count empty
	int empty_count = 0;
	for (int r = 0; r < board_size; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			if (board[r][c] == 0)
				empty_count++;
		}
	}

	if (empty_count > 0)
	{
		while (true)
		{
			//generate random location r, c
			r = rand() % board_size;
			c = rand() % board_size;
			//check if empty
			if (board[r][c] == 0)
			{
				//add number randomly {2,4}
				board[r][c] = 2 * (1 + (rand() % 2));
				break;
			}
		}

	}
}

