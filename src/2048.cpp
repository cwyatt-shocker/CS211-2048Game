#include "2048_helper.h"
#include <ctime>
#include <sstream>
using namespace std;

//Displays the current state below the original board layout.
void show_game(int board[][5], long long score, long long moves)
{
	print_board(board);
	cout << "Score: " << score << " | Successful moves: " << moves
	     << " | Highest tile: " << highest_tile(board) << endl;
	if(game_over(board))
		cout << "GAME OVER! No moves remain. Save, load, or start a new game.\n";
}

int main()
{
	int board[board_size][board_size] = {0}; //Row, then column
	long long score = 0;
	long long moves = 0;
	bool won = false;
	srand(static_cast<unsigned int>(time(nullptr)));
	new_game(board, score, moves);

	cout << "Initial Board : [5x5] :" << endl;
	print_help();
	show_game(board, score, moves);

	char choice = 'u'; //initialized
	string input;
	while(choice != 'e')
	{
		cout << "Please enter choice:{u,d,l,r,s,o,n,h,e} for UP, DOWN, LEFT, RIGHT, Save, Open, New, Help, Exit:" << endl;
		cout << "Choice: ";
		if(!getline(cin, input))
			break; //Handle end of input (Ctrl+D / Ctrl+Z).
		if(input.size() != 1){
			cout << "Invalid choice. Enter one letter from the menu.\n";
			continue;
		}
		choice = input[0];
		bool changed = false;
		bool movement = (choice == 'u' || choice == 'd' || choice == 'l' || choice == 'r');

		if(movement){
			if(game_over(board)){
				cout << "Game over! You cannot move unless you load or start a new game.\n";
				continue;
			}
			if(choice == 'u')
				changed = move_up(board, score);
			else if(choice == 'd')
				changed = move_down(board, score);
			else if(choice == 'l')
				changed = move_left(board, score);
			else if(choice == 'r')
				changed = move_right(board, score);

			if(changed){
				moves++;
				insert_random(board); //Exactly one new 2 after a successful move.
			}
			else
				cout << "No tiles moved. No new tile added.\n";
			show_game(board, score, moves);
			if(!won && highest_tile(board) >= 2048){
				cout << "Congratulations! You reached 2048! You can keep playing.\n";
				won = true;
			}
		}
		else if(choice == 's')
			save_game(board, score, moves);
		else if(choice == 'o'){
			if(load_game(board, score, moves)){
				won = (highest_tile(board) >= 2048);
				show_game(board, score, moves);
			}
		}
		else if(choice == 'n'){
			cout << "Start a new game? Current unsaved progress will be lost. (y/n): ";
			if(!getline(cin, input))
				break;
			if(input == "y" || input == "Y"){
				new_game(board, score, moves);
				won = false;
				cout << "New game started.\n";
				show_game(board, score, moves);
			}
			else
				cout << "New game canceled.\n";
		}
		else if(choice == 'h')
			print_help();
		else if(choice == 'e')
			cout << "Thanks for playing!\n";
		else
			cout << "Invalid choice. Enter one letter from the menu.\n";
	}
	return 0;
}
