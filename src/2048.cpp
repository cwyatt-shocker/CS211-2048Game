//#include <iostream> This line isnt needed as its included in the helper file.
#include "2048_helper.h"
using namespace std;

int main()
{
	// int board_size = 5; //This is specified in helper.h
	// int board[board_size][board_size] = {
	// 	{0, 4, 2, 4, 0},
	// 	{0, 0, 0, 0, 0},
	// 	{2, 0, 2, 0, 2},
	// 	{0, 0, 2, 0, 0},
	// 	{2, 2, 2, 2, 2},
	// };
	int board[board_size][board_size] = { //Row, then column
		{2,2,8,0,32},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
	};

	//while getch == x loop for up down left right

	cout << "Initial Board : [5x5] :" << endl;
	print_board(board);

	char choice = 'u';	//initialized
	while (choice != 'e')
	{

		cout << "Please enter choice:{u,d,l,r,e} for UP, DOWN, LEFT, RIGHT, Exit: " << endl;
		cout << "Choice: ";
		cin >> choice;

		if (choice == 'u')
			move_up(board, board_size);
		else if (choice == 'd')
			move_down(board, board_size);
		else if (choice == 'l')
			move_left(board, board_size);
		else if (choice == 'r')
			move_right(board, board_size);

		//insert_random(board, board_size);
		print_board(board);

	}


	return 0;
}