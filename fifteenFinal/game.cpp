#include "game.h"
#include <stdexcept>
#include <iostream>
using namespace std;

game::game(double thisPuzzleSize) {
	if (sqrt(thisPuzzleSize) != (int)(sqrt(thisPuzzleSize))) {
		throw invalid_argument("the number of rows and columns must be the same");
	}
	puzzleSize = (int)thisPuzzleSize;
	rowSize = (int)sqrt(thisPuzzleSize);
	puzzle = getGoal(rowSize, puzzleSize);
	goal = getGoal(rowSize, puzzleSize);
	this->hVal = hVal;
}


int game::getRowSize() {
	return this->rowSize;
}

vector<vector<int>> game::getPuzzle() {
	return this->puzzle;
}

vector<vector<int>> game::getGoal(int rowSize, int puzzleSize) {
	vector<vector<int>> sol;
	vector<int> row;
	int count = 0;
	for (int i = 0; i < puzzleSize; i++) {
		if (i + 1 == puzzleSize) {
			row.push_back(0);
			sol.push_back(row);
			return sol;
		}
		row.push_back(i + 1);
		if (row.size() == rowSize) {
			sol.push_back(row);
			row.clear();
		}
	}
}

vector<vector<int>> game::returnGoal() {
	return this->goal;
}

int* game::getCords(int num) {
	if (num > (this->puzzleSize -1)) {
		throw std::invalid_argument("invalid tile value");
	}
	int* cords = new int[2];
	for (int i = 0; i < this->puzzle.size(); i++) {
		for (int j = 0; j < this->rowSize; j++) {
			if (puzzle[i][j] == num) {
				cords[0] = i;
				cords[1] = j;
				return cords;
			}
		}
	}
}

int* game::getCordsGoal(int num) {
	if (num > (this->puzzleSize - 1)) {
		throw std::invalid_argument("invalid tile value");
	}
	int* cords = new int[2];
	for (int i = 0; i < this->goal.size(); i++) {
		for (int j = 0; j < this->rowSize; j++) {
			if (goal[i][j] == num) {
				cords[0] = i;
				cords[1] = j;
				return cords;
			}
		}
	}
}


void game::swap(int num) {
	int* cordsOfSwap = getCords(num);
	int* cordsOfZero = getCords(0);
	int temp = puzzle[cordsOfSwap[0]][cordsOfSwap[1]];
	puzzle[cordsOfSwap[0]][cordsOfSwap[1]] = puzzle[cordsOfZero[0]][cordsOfZero[1]];
	puzzle[cordsOfZero[0]][cordsOfZero[1]] = temp;
}

void game::print() {
	for (int i = 0; i < this->rowSize; i++) {
		for (int j = 0; j < this->rowSize; j++) {
			cout << puzzle[i][j] << " ";
		}
		cout << endl;
	}
}

vector<int> game::getMoveSet() {
	int* zero = getCords(0);
	vector<int> moveSet;
	int moves = 1;
	if ((zero[0] + 1 < rowSize)) {
		moveSet.push_back(moves);
	}
	moves++;
	if (zero[1] + 1 < rowSize) {
		moveSet.push_back(moves);
	}
	moves++;
	if (zero[0] - 1 >= 0) {
		moveSet.push_back(moves);
	}
	moves++;
	if (zero[1] - 1 >= 0) {
		moveSet.push_back(moves);
	}
	return moveSet;
}

void game::move(int move) {
	int* zero = getCords(0);
	int i = zero[0];
	int j = zero[1];

	switch (move) {
	case 1:
		i++;
		swap(puzzle[i][j]);
		break;
	case 2:
		j++;
		swap(puzzle[i][j]);
		break;
	case 3:
		i--;
		swap(puzzle[i][j]);
		break;
	case 4:
		j--;
		swap(puzzle[i][j]);
		break;
	}
}


int game::numberOfMisplacedTiles() {
	int count = 0;
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < rowSize; j++) {
			if (puzzle[i][j] != goal[i][j]) {
				count++;
			}
		}
	}
	return count;
}

int game::hDistance(int num) {
	int* moved = getCords(num);
	int* original = getCordsGoal(num);
	int distance = abs(moved[0] - original[0]) + abs(moved[1] - original[1]);
	return distance;
}

int game::numInversions() {
	int invs = 0;
	vector<int> list;
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < rowSize; j++) {
			list.push_back(puzzle[i][j]);
		}
	}
	for (int n = 0; n < list.size() - 1; n++) {
		if (list[n] > list[n + 1]) {
			invs++;
		}
	}
	return invs;
}

bool game::isSolveable() {
	int invertions = numInversions();
	if ((invertions % 2 == 0 && rowSize % 2 != 0)
		|| (invertions % 2 != 0 && rowSize % 2 == 0)) {
		return true;
	}
	return false;
}


void game::shuffle() {
	bool solveable = false;
	vector<int>moveSet;
	while (!solveable) {
		int num = rand() % 10 + 15;
		for (int i = 0; i <= num; i++) {
			moveSet = getMoveSet();
			int chosen = rand() % (moveSet.size());
			chosen = moveSet[chosen];
			move(chosen);
		}
		if (this->isSolveable())
			solveable = true;
		}
	}

vector<game> game::getMovedPuzzles(game thisGame) {
	vector<game> moved;
	vector<int> moveSet = thisGame.getMoveSet();
	for (int i = 0; i < moveSet.size(); i++) {
		game copy = thisGame;
		copy.move(moveSet[i]);
		moved.push_back(copy);
	}
	return moved;

}

void game::setHVal(int val) {
	this->hVal = val;
}

int game::returnHVal() {
	return this->hVal;
}
