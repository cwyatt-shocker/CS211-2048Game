#ifndef HELPER_2048_H
#define HELPER_2048_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <climits>
using namespace std;

const int board_size = 5;

//Movement returns true if the board changed. Points earned are added to score.
bool move_left(int board[][5], long long &score, int board_size = 5);
bool move_right(int board[][5], long long &score, int board_size = 5);
bool move_up(int board[][5], long long &score, int board_size = 5);
bool move_down(int board[][5], long long &score, int board_size = 5);

void print_board(int board[][5], int board_size = 5);
void insert_random(int board[][5], int board_size = 5);
void new_game(int board[][5], long long &score, long long &moves, int board_size = 5);
int highest_tile(int board[][5], int board_size = 5);
bool game_over(int board[][5], int board_size = 5);
void print_help();
bool save_game(int board[][5], long long score, long long moves, int board_size = 5);
bool load_game(int board[][5], long long &score, long long &moves, int board_size = 5);

//Function implementations are kept in this header, as in the starter program.

//Each directional function handles sliding and merging directly.
//Random tile insertion stays outside these movement functions.

inline bool move_left(int board[][5], long long &score, int board_size)
{
    bool changed = false;

    //Go through each row of the board.
    for(int row = 0; row < board_size; row++){
        int original[5] = {0};
        int numbers[5] = {0};
        int result[5] = {0};
        int count = 0;

        //Save the original values and slide nonzero tiles together.
        for(int col = 0; col < board_size; col++){
            original[col] = board[row][col];
            if(board[row][col] != 0){
                numbers[count] = board[row][col];
                count++;
            }
        }

        //Merge matching tiles. Skip a tile after merging it once.
        int next = 0;
        for(int i = 0; i < count; i++){
            if(i + 1 < count && numbers[i] == numbers[i + 1]){
                result[next] = numbers[i] * 2;
                score += result[next];
                i++; //A newly merged tile cannot merge again this move.
            }
            else{
                result[next] = numbers[i];
            }
            next++;
        }

        //Write the completed line back and check if it changed.
        for(int col = 0; col < board_size; col++){
            board[row][col] = result[col];
            if(board[row][col] != original[col])
                changed = true;
        }
    }
    return changed;
}

inline bool move_right(int board[][5], long long &score, int board_size)
{
    bool changed = false;

    //Go through each row of the board.
    for(int row = 0; row < board_size; row++){
        int original[5] = {0};
        int numbers[5] = {0};
        int result[5] = {0};
        int count = 0;

        //Save the original values and slide nonzero tiles together.
        for(int col = 0; col < board_size; col++){
            original[col] = board[row][board_size - 1 - col];
            if(board[row][board_size - 1 - col] != 0){
                numbers[count] = board[row][board_size - 1 - col];
                count++;
            }
        }

        //Merge matching tiles. Skip a tile after merging it once.
        int next = 0;
        for(int i = 0; i < count; i++){
            if(i + 1 < count && numbers[i] == numbers[i + 1]){
                result[next] = numbers[i] * 2;
                score += result[next];
                i++; //A newly merged tile cannot merge again this move.
            }
            else{
                result[next] = numbers[i];
            }
            next++;
        }

        //Write the completed line back and check if it changed.
        for(int col = 0; col < board_size; col++){
            board[row][board_size - 1 - col] = result[col];
            if(board[row][board_size - 1 - col] != original[col])
                changed = true;
        }
    }
    return changed;
}

inline bool move_up(int board[][5], long long &score, int board_size)
{
    bool changed = false;

    //Go through each column of the board.
    for(int col = 0; col < board_size; col++){
        int original[5] = {0};
        int numbers[5] = {0};
        int result[5] = {0};
        int count = 0;

        //Save the original values and slide nonzero tiles together.
        for(int row = 0; row < board_size; row++){
            original[row] = board[row][col];
            if(board[row][col] != 0){
                numbers[count] = board[row][col];
                count++;
            }
        }

        //Merge matching tiles. Skip a tile after merging it once.
        int next = 0;
        for(int i = 0; i < count; i++){
            if(i + 1 < count && numbers[i] == numbers[i + 1]){
                result[next] = numbers[i] * 2;
                score += result[next];
                i++; //A newly merged tile cannot merge again this move.
            }
            else{
                result[next] = numbers[i];
            }
            next++;
        }

        //Write the completed line back and check if it changed.
        for(int row = 0; row < board_size; row++){
            board[row][col] = result[row];
            if(board[row][col] != original[row])
                changed = true;
        }
    }
    return changed;
}

inline bool move_down(int board[][5], long long &score, int board_size)
{
    bool changed = false;

    //Go through each column of the board.
    for(int col = 0; col < board_size; col++){
        int original[5] = {0};
        int numbers[5] = {0};
        int result[5] = {0};
        int count = 0;

        //Save the original values and slide nonzero tiles together.
        for(int row = 0; row < board_size; row++){
            original[row] = board[board_size - 1 - row][col];
            if(board[board_size - 1 - row][col] != 0){
                numbers[count] = board[board_size - 1 - row][col];
                count++;
            }
        }

        //Merge matching tiles. Skip a tile after merging it once.
        int next = 0;
        for(int i = 0; i < count; i++){
            if(i + 1 < count && numbers[i] == numbers[i + 1]){
                result[next] = numbers[i] * 2;
                score += result[next];
                i++; //A newly merged tile cannot merge again this move.
            }
            else{
                result[next] = numbers[i];
            }
            next++;
        }

        //Write the completed line back and check if it changed.
        for(int row = 0; row < board_size; row++){
            board[board_size - 1 - row][col] = result[row];
            if(board[board_size - 1 - row][col] != original[row])
                changed = true;
        }
    }
    return changed;
}

inline void print_board(int board[][5], int board_size)
{
	cout << endl << "\t-----------------------------------------" << endl;
	for(int r = 0; r < board_size; r++){
		for(int c = 0; c < board_size; c++){
			if(board[r][c] > 0)
				cout << "\t|" << right << setw(6) << setfill(' ') << board[r][c];
			else
				cout << "\t|" << right << setw(6) << setfill(' ') << " ";
		}
		cout << "\t|" << endl;
		cout << "\t-----------------------------------------" << endl;
	}
	cout << "\t" << endl << endl;
}

inline void insert_random(int board[][5], int board_size)
{
	//Count open positions so the new tile always goes into an empty cell.
	int empty_count = 0;
	for(int r = 0; r < board_size; r++)
		for(int c = 0; c < board_size; c++)
			if(board[r][c] == 0)
				empty_count++;

	if(empty_count == 0)
		return;

	//Select a random EMPTY cell, not a random cell on the board.
	int selected = rand() % empty_count;
	for(int r = 0; r < board_size; r++){
		for(int c = 0; c < board_size; c++){
			if(board[r][c] == 0){
				if(selected == 0){
					board[r][c] = 2;
					return;
				}
				selected--;
			}
		}
	}
}

inline void new_game(int board[][5], long long &score, long long &moves, int board_size)
{
	for(int r = 0; r < board_size; r++)
		for(int c = 0; c < board_size; c++)
			board[r][c] = 0;
	score = 0;
	moves = 0;
	insert_random(board, board_size);
	insert_random(board, board_size);
}

inline int highest_tile(int board[][5], int board_size)
{
	int highest = 0;
	for(int r = 0; r < board_size; r++)
		for(int c = 0; c < board_size; c++)
			if(board[r][c] > highest)
				highest = board[r][c];
	return highest;
}

inline bool game_over(int board[][5], int board_size)
{
	for(int r = 0; r < board_size; r++){
		for(int c = 0; c < board_size; c++){
			if(board[r][c] == 0)
				return false;
			if(c < board_size-1 && board[r][c] == board[r][c+1])
				return false;
			if(r < board_size-1 && board[r][c] == board[r+1][c])
				return false;
		}
	}
	return true;
}

inline void print_help()
{
	cout << "\n2048 - Commands:\n";
	cout << " u = UP, d = DOWN, l = LEFT, r = RIGHT\n";
	cout << " s = Save to savegame.txt (replaces the previous save)\n";
	cout << " o = Open savegame.txt (loads the saved board)\n";
	cout << " n = New game (asks for confirmation)\n";
	cout << " h = Help, e = Exit\n";
	cout << " Slide matching tiles together to make 2048.\n";
	cout << " Only successful moves create a new 2 tile.\n\n";
}

inline bool save_game(int board[][5], long long score, long long moves, int board_size)
{
	ofstream file("savegame.txt");
	if(!file){
		cout << "Error: Could not open savegame.txt for writing.\n";
		return false;
	}
	file << "CS211_2048_V1\n";
	file << score << " " << moves << "\n";
	for(int r = 0; r < board_size; r++){
		for(int c = 0; c < board_size; c++){
			if(c > 0) file << " ";
			file << board[r][c];
		}
		file << "\n";
	}
	file.flush();
	if(!file){
		cout << "Error: Could not finish writing savegame.txt.\n";
		return false;
	}
	cout << "Game saved to savegame.txt.\n";
	return true;
}

inline bool load_game(int board[][5], long long &score, long long &moves, int board_size)
{
	ifstream file("savegame.txt");
	if(!file){
		cout << "Error: Could not open savegame.txt. Game unchanged.\n";
		return false;
	}

	string marker;
	long long saved_score, saved_moves;
	int saved_board[5][5] = {0};
	if(!(file >> marker) || marker != "CS211_2048_V1" ||
	   !(file >> saved_score >> saved_moves) || saved_score < 0 || saved_moves < 0){
		cout << "Error: Invalid save header or counters. Game unchanged.\n";
		return false;
	}
	for(int r = 0; r < board_size; r++){
		for(int c = 0; c < board_size; c++){
			long long value;
			if(!(file >> value) || value < 0 || value > INT_MAX ||
			   (value != 0 && (value < 2 || (value & (value-1)) != 0))){
				cout << "Error: Invalid or missing tile value. Game unchanged.\n";
				return false;
			}
			saved_board[r][c] = static_cast<int>(value);
		}
	}
	string extra;
	if(file >> extra){
		cout << "Error: Unexpected extra save data. Game unchanged.\n";
		return false;
	}
	if(file.bad()){
		cout << "Error: Could not read the save completely. Game unchanged.\n";
		return false;
	}

	//Copy the saved state ONLY after every value has been checked.
	for(int r = 0; r < board_size; r++)
		for(int c = 0; c < board_size; c++)
			board[r][c] = saved_board[r][c];
	score = saved_score;
	moves = saved_moves;
	cout << "Game loaded from savegame.txt.\n";
	return true;
}

#endif
