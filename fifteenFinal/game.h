#pragma once
#include <vector>
using namespace std;
class game
{
private:
	int puzzleSize;
	int rowSize;
	int hVal;
	vector<vector<int>> puzzle;
	vector<vector<int>> goal;

public:
	game();
	game(double size);
	vector<vector<int>> returnGoal();
	int getRowSize();
	vector<vector<int>> getPuzzle();
	vector<vector<int>> getGoal(int rowSize, int puzzleSize);
	int* getCords(int num);
	void swap(int num);
	void print();
	vector<int> getMoveSet();
	void move(int move);
	int numberOfMisplacedTiles();
	int hDistance(int num);
	int numInversions();
	bool isSolveable();
	void shuffle();
	vector<game> getMovedPuzzles(game thisGame);
	void setHVal(int val);
	int returnHVal();
	int* getCordsGoal(int num);
};

