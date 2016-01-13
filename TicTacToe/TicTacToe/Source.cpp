#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

class Validator {
	public:
		Validator() {}
		string getInput() {
			string input = "";
			char currentKey;
			const static int maxLineLength = 20;

			currentKey = _getch();
			while (currentKey != 13) {
				if ((currentKey >= 32) && (currentKey <= 126)) {
					// valid character, accept and print
					if (maxLineLength > input.length()) {
						input += currentKey;
						printf("%c", currentKey);
					}
				} else if (currentKey == 8) {
					// backspace - change string var and erase from screen.
					if (input.length() > 0) {
						input.erase(input.length() - 1);
						printf("\b \b"); // "print" the backspace to screen.
					}
				}
				currentKey = _getch();
			}
			cout << endl;
			return input;
		} // end method getInput
		~Validator() {}
		string getYN(string msg) {
			cout << msg;
			string answer = getInput();
			while (answer != "y" && answer != "n") {
				cout << endl << "** Please enter y or n only **" << endl << endl << msg;
				answer = getInput();
			}
			return answer;
		}
		string getInd(string msg) {
			cout << msg;
			string nums = "123456789";
			string answer = getInput();
			while (nums.find(answer) == string::npos || answer.length() != 1) {
				cout << endl << "** Please enter 1 to 9 only **" << endl << endl << msg;
				answer = getInput();
			}
			return answer;
		}

}; // end class Validator

class Point {
	public:
		Point() {
			row = -1;
			col = -1;
		}
		Point(int rw, int cl) {
			row = rw;
			col = cl;
		}
		int getRow() {
			return row;
		}
		int getCol() {
			return col;
		}
		~Point() {}
		string toString() {
			return "(" + to_string(row) + ", " + to_string(col) + ")";
		}
	private:
		int row, col;
};

class Board {
private:
	char entries[3][3];

public:
	const static char X = 'X';
	const static char O = 'O';
	const static char BLANK = ' ';
	const static char TIE = 'T';
	Board() {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				entries[row][col] = BLANK;
			}
		}
	}
	~Board() {}
	static Point indToPoint(int index) {
		int col = (index-1) % 3;
		int row = ((index-1) - col) / 3;
		return Point(row, col);
	}
	static int pointToInd(Point pt) {
		return pt.getRow() * 3 + pt.getCol() + 1;
	}
	static char getOther(char chr) {
		if (chr == X) {
			return O;
		}
		else {
			return X;
		}
	}
	static void showRefBoard() {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				string entry = to_string(row*3 + col + 1);
				cout << " " << entry << " ";
				if (col != 2) {
					cout << "|";
				}
			}
			if (row != 2) {
				cout << endl << "-----------";
			}
			cout << endl;
		}
	}
	char get(Point pt) {
		return entries[pt.getRow()][pt.getCol()];
	}

	bool play(char chr, Point pt) {
		if (chr == X || chr == O || chr == BLANK) {
			entries[pt.getRow()][pt.getCol()] = chr;
		}
		return (entries[pt.getRow()][pt.getCol()] == chr);
	} // end method play

	void show() {
		// output the board to screen.
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				cout << " " << entries[row][col] << " ";
				if (col != 2) {
					cout << "|";
				}
			}
			if (row != 2) {
				cout << endl << "-----------";
			}
			cout << endl;
		}
	} // end method show

	char getWinner() {
		for (int idx = 0; idx < 3; idx++) {
			// check for row-win
			if (entries[idx][0] == entries[idx][1] && entries[idx][0] == entries[idx][2]) {
				if (entries[idx][0] != BLANK) {
					return entries[idx][0];
				}
			}
			//check for col-win
			if (entries[0][idx] == entries[1][idx] && entries[0][idx] == entries[2][idx]) {
				if (entries[0][idx] != BLANK) {
					return entries[0][idx];
				}
			}
		}
		//check for diag-win
		if ((entries[0][0] == entries[1][1] && entries[0][0] == entries[2][2]) ||
			(entries[0][2] == entries[1][1] && entries[0][2] == entries[2][0])) {
			if (entries[1][1] != BLANK) {
				return entries[1][1];
			}
		}
		// check for 'cat' ie board full
		bool full = true;
		for (int rw = 0; rw < 3; rw++) {
			for (int cl = 0; cl < 3; cl++) {
				if (isEmpty(Point(rw, cl))) {
					full = false;
				}
			}
		}
		if (full) {
			return TIE;
		}
		// no winner found.
		return BLANK;
	} // end method getWinner

	bool isEmpty(Point pt) {
		return get(pt) == BLANK;
	}

	bool allEmpty() {
		bool allEmpt = true;
		for (int rw = 0; rw < 3; rw++) {
			for (int cl = 0; cl < 3; cl++) {
				if (!isEmpty(Point(rw, cl))) {
					allEmpt = false;
				}
			}
		}
		return allEmpt;
	}
};

class TTTAI {
private:
	char myChar, playerChar;
public:
	TTTAI(char chr) {
		this->myChar = chr;
		this->playerChar = Board::getOther(myChar);
	}

	Point getMove(Board brd) {
		// if it's the first move, be a little random.
		if (brd.allEmpty()) {
			int indices[] = { 1, 3, 5, 7, 9 };
			return Board::indToPoint(indices[rand() % 5]);
		}

		// search for the max score of the available ai-play moves
		int max = -1000;
		Point bestMove;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (brd.isEmpty(Point(row, col))) {
					brd.play(myChar, Point(row, col));
					int subscore = scoreBoard(brd, false, 1);
					if (subscore > max) {
						max = subscore;
						bestMove = Point(row, col);
					}
					brd.play(Board::BLANK, Point(row, col));
				}
			}
		}
		// at this point max and bestMove should be populated.
		return bestMove;

		return Point(0, 0);
	} // end getMove

	int scoreBoard(Board brd, bool aiturn, int depth) {
		char winner = brd.getWinner();
		// check for base cases.
		if (winner == myChar) {
			return 100 - depth;
		}
		else if (winner == playerChar) {
			return -100 + depth;
		}
		else if (winner == Board::TIE) {
			return 0 + depth;
		}
		else {
			if (aiturn) {
				// search for the max score of the available ai-play moves
				int max = -1000;
				for (int row = 0; row < 3; row++) {
					for (int col = 0; col < 3; col++) {
						if (brd.isEmpty(Point(row, col))) {
							brd.play(myChar, Point(row, col));
							int subscore = scoreBoard(brd, !aiturn, depth + 1);
							if (subscore > max) {
								max = subscore;
							}
							brd.play(Board::BLANK, Point(row, col));
						}
					}
				}
				// at this point max should be populated.
				return max;
			}
			else {
				// search for the min score of the available player-play moves
				int min = 1000;
				for (int row = 0; row < 3; row++) {
					for (int col = 0; col < 3; col++) {
						if (brd.isEmpty(Point(row, col))) {
							brd.play(playerChar, Point(row, col));
							int subscore = scoreBoard(brd, !aiturn, depth + 1);
							if (subscore < min) {
								min = subscore;
							}
							brd.play(Board::BLANK, Point(row, col));
						}
					}
				}
				// at this point min should be populated.
				return min;
			}
		}
	}
}; // end class TTTAI

int main() {
	// welcome message
	cout << "WELCOME TO TIC-TAC-TOE!" << endl;
	cout << "You'll be playing against the computer." << endl << endl;

	// Initialize variables.
	Validator val;
	Board board;
	bool playerTurn;
	char aiChar, playerChar;
	string wantX, wantFirst;
	string playAgain = "y";
	int playerWins = 0;
	int aiWins = 0;
	int TieGames = 0;
	
	// start new games as long as player wants to play.
	while (playAgain == "y") {
		board = Board();
		wantX = val.getYN("Would you like to be X's? (y/n) ");
		wantFirst = val.getYN("Would you like to play first? (y/n) ");
		if (wantX == "y") {
			playerChar = Board::X;
			aiChar = Board::O;
		}
		else {
			playerChar = Board::O;
			aiChar = Board::X;
		}
		TTTAI ai(aiChar);
		playerTurn = (wantFirst == "y");

		char winner = Board::BLANK;
		while (winner == Board::BLANK) {
			if (playerTurn) {
				cout << endl << "It's your turn!" << endl;
				cout << "CURRENT BOARD:" << endl;
				board.show();
				cout << endl << "REFERENCE BOARD:" << endl;
				Board::showRefBoard();
				cout << "Enter a number from the reference board to choose where to play your " << playerChar << endl;
				cout << "(remember to choose an available square!)" << endl;
				string moveInd = val.getInd("Enter a number (1-9): ");
				Point movePoint = Board::indToPoint(stoi(moveInd));
				while (!board.isEmpty(movePoint)) {
					// make player rechoose
					cout << "That square is occupied! Choose again." << endl;
					moveInd = val.getInd("Enter a number (1-9): ");
					movePoint = Board::indToPoint(stoi(moveInd));
				}
				cout << "You play " << playerChar << " at position " << moveInd << endl;
				board.play(playerChar, movePoint);
			}
			else {
				cout << endl << "It's the computer's turn!" << endl;
				cout << "CURRENT BOARD:" << endl;
				board.show();
				Point currentMove = ai.getMove(board);
				int currentIndex = Board::pointToInd(currentMove);
				cout << "Computer plays its " << aiChar << " at position " << currentIndex << endl;
				board.play(aiChar, currentMove);
			}
			playerTurn = !playerTurn;
			winner = board.getWinner();
		}
		cout << "CURRENT BOARD:" << endl;
		board.show();
		if (winner == aiChar) {
			cout << "Computer wins!  Better luck next time!" << endl;
			aiWins++;
		}
		else if (winner == playerChar) {
			cout << "Player wins! (hey, this thing is supposed to be unbeatable..." << endl;
			playerWins++;
		}
		else {
			cout << "Tie game!  No winner." << endl;
			TieGames++;
		}
		cout << endl << "RESULTS SO FAR:" << endl;
		cout << "\tPlayer Wins:\t" << playerWins << endl;
		cout << "\tComputer Wins:\t" << aiWins << endl;
		cout << "\tTie Games:\t" << TieGames << endl << endl;
		playAgain = val.getYN("Would you like to play again?");
		cout << endl << endl;
	}

	// Done playing
	cout << "Thanks for playing Tic-Tac-Toe!" << endl;
	cout << "Push any key to exit.";

	_getch();
	return 0;
}