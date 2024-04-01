#include "game.h"
#include <iostream>
#include <queue>

//breadth first algo: 
vector<game> breadthFirst(game& startNode) {
    vector<game> solution;
    queue<vector<game>> queue;
    vector<game> expanded;
    int numExpanded = 0;

    queue.push({ startNode }); //enqueues the scrambled grid
    while (!queue.empty()) {
        vector<game> path = queue.front(); //exploring this node
        queue.pop(); //pops the grid off the queue
        game endNode = path.back();
        expanded.push_back(endNode);
        numExpanded++;
        if (endNode.getPuzzle() == endNode.returnGoal()) {
            solution = path;
            cout << "\n" << "Breadth first: " << numExpanded << " nodes expanded \n";
            return solution;
        }
        for (int j = 0; j < expanded.size(); j++) {
            bool found = false;
            for (int i = 0; i < endNode.getMovedPuzzles(endNode).size(); i++) {
                if (expanded[j].getPuzzle() == endNode.getMovedPuzzles(endNode)[i].getPuzzle()) {
                    found = true;
                    break;
                }
            }

        }
        for (game thisPuzzle : endNode.getMovedPuzzles(endNode)) {
            bool found = false;
            for (int i = 0; i < expanded.size(); i++) {
                if (expanded[i].getPuzzle() == thisPuzzle.getPuzzle()) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                vector<game> newPath = path;
                newPath.push_back(thisPuzzle);
                queue.push(newPath);
            }
        }
    }
}

int getHValue(game thisGame) {
    int val = 0;
    for (int i = 0; i < thisGame.getPuzzle().size(); i++) {
        val += thisGame.hDistance(i);
    }
    return val;
}

int getPathH(vector<game> thisPath) {
    int v = 0;
    for (game thisGame : thisPath) {
        v += getHValue(thisGame);
    }
    return v;
}

typedef struct node
{
	vector<game> data;

	int priority;

	struct node* next;

} Node;

Node* newNode(vector<game> thisPath, int priority)
{
    Node* temp = new Node;
    temp->data = thisPath;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}

class linkedList{
public:
    vector<game> getHead(Node** head)
    {
        return (*head)->data;
    }

    void pop(Node** head)
    {
        Node* temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }

    void push(Node** head, vector<game> data, int thisPriority)
    {
        Node* start = (*head); //points to the head node
        Node* temp = newNode(data, thisPriority);

        if ((*head)->priority > thisPriority)
        {

            temp->next = *head; //if the temp priority is greater than the head priority then temp is first
            (*head) = temp;
        }
        else
        {
            while (start->next != NULL &&
                start->next->priority < thisPriority)
            {
                start = start->next;
            }

            temp->next = start->next;
            start->next = temp;
        }
    }

    int isEmpty(Node** head)
    {
        return (*head) == NULL;
    }
};

vector<game> aStarAlgo(game startNode) {
    linkedList queue;
    vector<game> solution;
    vector<game> expanded;
    int numExpanded = 0;
    int p = getHValue(startNode);
    Node* thisNode = newNode({ startNode }, p);
    Node** head = &thisNode;
    queue.push(head, { startNode }, p);

    while (!queue.isEmpty(head)){
        vector<game> path = queue.getHead(head);
        queue.pop(head);
        game endNode = path.back();
        expanded.push_back(endNode);
        numExpanded++;
        if (endNode.getPuzzle() == endNode.returnGoal()) {
            solution = path;
            for (game thisGame : solution) {
                thisGame.print();
                cout << "\n";
            }
            cout << "\n" << "A*: " << numExpanded << " nodes expanded \n";
            return solution;
        }
        for (int j = 0; j < expanded.size(); j++) {
            bool found = false;
            for (int i = 0; i < endNode.getMovedPuzzles(endNode).size(); i++) {
                if (expanded[j].getPuzzle() == endNode.getMovedPuzzles(endNode)[i].getPuzzle()) {
                    found = true;
                    break;
                }
            }
        }
        for (game thisPuzzle : endNode.getMovedPuzzles(endNode)) {
            bool found = false;
            for (int i = 0; i < expanded.size(); i++) {
                if (expanded[i].getPuzzle() == thisPuzzle.getPuzzle()) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                vector<game> newPath = path;
                newPath.push_back(thisPuzzle);
                int p = getPathH(newPath);
                queue.push(head, newPath, p);
            }
        }
    }
}

game generate(double size) {
    game thisGame(size);
    thisGame.shuffle();
    return thisGame;
}

int main() {
    bool run = true;
    while (run) {
        double n;
        cout << "enter desired puzzle size (grid must be a square)" << "\n";
        cin >> n;
        game puzzle = generate(n);
        cout << "\n";
        cout << "puzzle:";
        cout << "\n";
        puzzle.print();
        cout << "\n";
        cout << "solution: \n";
        aStarAlgo(puzzle);
        cout << "\n";
        breadthFirst(puzzle);
        cout << "\n";
        string s;
        cout << "continue? \n";
        cin >> s;
        if (s == "n") {
            run = false;
        }
    }
}