/*****************************************************
 * CS411 - HW3
 *
 * 8-Puzzle Solver implemented with A*
 * using the following heuristics:
 *
 *   1. Manhattan distance
 *   2. Misplaced tiles
 *   3. n-MaxSwap
 *   4. Nilsson's distance
 *
 * Written by Dmitry Svistula
 * Email: dsvistyu@cs.uic.edu
 *
 *****************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <ctime>

using namespace std;

// file output
ofstream fileOut("result.txt");

/*
 * State
 */
typedef int State[9];

/*
 * TreeNode
 */
struct TreeNode {
	
	// pathcost from root
	int pathcost;
	// heuristic
	int heuristic;
	// total score
	int score;

	// where piece moved
	int move;
	// number of node children
	int numchildren;
	// depth of node
	int depth;

	// state
	State state;

	// children pointer
	TreeNode *children[4];
	// parent pointer
	TreeNode *parent;

};

/* 
 * Class Solver for 8-Puzzle
 */
class Solver {

	private:

		// defines operators
		int moving_rules[9][4];

		// goal state
		int solution[9];

		// start state
		int startstate[9];

		// number of tiles
		int n_tiles;
		// number of possible moves
		int n_moves;

		// choice of heuristic
		int kindOfHeuristic;

		// timer
		time_t start_time, cur_time;
		int runtime;

		// fringe
		list<TreeNode*> fringe;

		// total depth of solution
		int totalSteps;

		// search finish flag
		bool finished;

	public:
		// Solver constructors
		Solver();
		Solver(State, int);

		// Solver methods
		TreeNode *newnode();
		TreeNode *create(TreeNode *, int);
		int checkRepeated(TreeNode *);
		void initialize(State);
		void expand(TreeNode *);
		void printSolution(TreeNode *);
		void makeChildren(TreeNode *);
		void printBoard(State);
		bool solutionFound(TreeNode *);
		int getHeuristic(int, TreeNode *);
		void addToFringe(TreeNode *);
		void printFringe();
		void evaluate(TreeNode *);
		int setDepth(TreeNode *, int);
		void done(TreeNode *);
		void start();
		int getTotalSteps();
		void swap(State, int, int);
};

/*
 * Default solver constructor
 */
Solver::Solver() { }

/*
 * Solver constructor
 * Input: start state, choce of heuristic
 */
Solver::Solver(State start, int h) {

	int i, j;

	int rules[9][4] = {
	/* 0 */ {1, 3,-9,-9},/*expands 3,1		2 children*/
	/* 1 */ {0, 2, 4,-9},/*expands 4,2,0	3 children*/
	/* 2 */ {1, 5,-9,-9},/*expands 5,1		2 children*/
	/* 3 */ {0, 4, 6,-9},/*expands 6,4,0	3 children*/
	/* 4 */ {1, 3, 5, 7},/*expands 7,5,3,1	4 children*/
	/* 5 */ {2, 4, 8,-9},/*expands 8,4,2	3 children*/
	/* 6 */ {3, 7,-9,-9},/*expands 7,3		2 children*/
	/* 7 */ {4, 6, 8,-9},/*expands 8,6,4	3 children*/
	/* 8 */ {5, 7,-9,-9} /*expands 7,5		2 children*/
	};

	n_tiles = 9;
	n_moves = 4;

	for(i=0;i<n_tiles;i++) {
		for(j=0;j<n_moves;j++) {
			moving_rules[i][j] = rules[i][j];
		}
	}

	for(i=0;i<n_tiles;i++) {
		solution[i] = i;
	}

	for(i=0;i<n_tiles;i++) {
		startstate[i] = start[i];
	}

	kindOfHeuristic = h;
	totalSteps =0;
	finished = false;
}

/*
 * Swaps two values in a state
 * Input: state, two value positions
 */
void Solver::swap(State s, int v1, int v2) {
	int temp = s[v1];
	s[v1] = s[v2];
	s[v2] = temp;
}

/*
 * Returns # of steps taken to reach solution
 * Output: # of steps
 */
int Solver::getTotalSteps() {
	return totalSteps;
}

/*
 * Computes heuristic based on choice for a none
 * Input: choice of heuristic, node
 */
int Solver::getHeuristic(int kind, TreeNode *node) {

	int i;

	// Manhattan distance
	if(kind == 1) {
		int manhattan = 0;

		int distances[9][9] ={

		//////*0 1 2 3 4 5 6 7 8*//////
		/*0*/{ 0,1,2,1,2,3,2,3,4 }/*0*/,
		/*1*/{ 1,0,1,2,1,2,3,2,3 }/*1*/,
		/*2*/{ 2,1,0,3,2,1,4,3,2 }/*2*/,
		/*3*/{ 1,2,3,0,1,2,1,2,3 }/*3*/,
		/*4*/{ 2,1,2,1,0,1,2,1,2 }/*4*/,
		/*5*/{ 3,2,1,2,1,0,3,2,1 }/*5*/,
		/*6*/{ 2,3,4,1,2,3,0,1,2 }/*6*/,
		/*7*/{ 3,2,3,2,1,2,1,0,1 }/*7*/,
		/*8*/{ 4,3,2,3,2,1,2,1,0 }/*8*/
		//////*0 1 2 3 4 5 6 7 8*//////
		};

		
		for(i=0; i<n_tiles; i++) {
			manhattan += distances[i][node->state[i]];
		}

		return manhattan;
	}


	// Misplaced tiles
	if(kind == 2) {

		int heuristic = 0;

		for(i=0;i<n_tiles;i++) {
			if(node->state[i] != solution[i]) {
				heuristic++;
			}
		}

		return heuristic;

	}


	// N-MaxSwap
	if(kind == 3) {

		State tempState;

		for(i=0;i<n_tiles;i++) {
			tempState[i] = node->state[i];
		}

		int heuristic =0;
		
		int hole_pos;
	
		while(true) {
			for(i=0;i<n_tiles;i++) {
				if(tempState[i] == 0) break;
			}

			hole_pos = i;

			for(i=0;i<n_tiles;i++) {
				if(tempState[i] == hole_pos) {
					swap(tempState, hole_pos, i);
					heuristic++;
				}
			

				if(tempState[0] == 0) {
					for(i=0;i<n_tiles;i++) {
						if(tempState[i] != solution[i]) {
							swap(tempState, 0, i);
							heuristic++;
						}
					}
				}

			}

			int s_count=0;
			for(i=0;i<n_tiles;i++) {
				if(tempState[i] == solution[i]) {
					s_count++;
				}
			}

			if(s_count == n_tiles) break;
		}

		return heuristic;
	}

	// Nilsson's distance
	if(kind == 4) {

		int manhattan = 0;
		int sequence_score = 0;


		int distances[9][9] ={

		//////*0 1 2 3 4 5 6 7 8*//////
		/*0*/{ 0,1,2,1,2,3,2,3,4 }/*0*/,
		/*1*/{ 1,0,1,2,1,2,3,2,3 }/*1*/,
		/*2*/{ 2,1,0,3,2,1,4,3,2 }/*2*/,
		/*3*/{ 1,2,3,0,1,2,1,2,3 }/*3*/,
		/*4*/{ 2,1,2,1,0,1,2,1,2 }/*4*/,
		/*5*/{ 3,2,1,2,1,0,3,2,1 }/*5*/,
		/*6*/{ 2,3,4,1,2,3,0,1,2 }/*6*/,
		/*7*/{ 3,2,3,2,1,2,1,0,1 }/*7*/,
		/*8*/{ 4,3,2,3,2,1,2,1,0 }/*8*/
		//////*0 1 2 3 4 5 6 7 8*//////
		};

		
		for(i=0; i<n_tiles; i++) {
			manhattan += distances[i][node->state[i]];
		}


		int first, second;
		for(i=0; i<8; i++) {
			first = node->state[i];
			second = node->state[i+1];

			if((first + 1) != second) {
				sequence_score++;
			}
		}
		
		if(node->state[8] != solution[8]) {
			sequence_score++;
		}

		return manhattan + sequence_score;

	}

	return 0;
}

/*
 * Initiates tree expansion and search
 */
void Solver::start() {


	TreeNode *root = newnode();

	initialize(root->state);
	root->score = 10000;
	addToFringe(root);

	time(&start_time);

	while(finished == false) {
		expand(root);
	}
}

/*
 * Procedure when done searching
 */
void Solver::done(TreeNode *node) {
	time(&cur_time);
	runtime = cur_time - start_time;


	fileOut<<"At depth="<<node->depth<<" with nodes="
		<<fringe.size()<<" in time="<<runtime<<endl;

	cout<<"At depth="<<node->depth<<" with nodes="
		<<fringe.size()<<" in time="<<runtime<<endl;

	finished = true;
	printSolution(node);
}

/*
 * Creates a new node
 * Output: new node
 */
TreeNode* Solver::newnode() {
	int i;
	TreeNode *node;

	if(!(node=(TreeNode*)malloc(sizeof(TreeNode)))) {
		cout<<"Out of memory!"<<endl;
		exit(1);
	}

	for(i=0;i<n_tiles;i++) { node->state[i]=i; }

	for(i=0;i<n_moves;i++) { node->children[i] = NULL; }

	node->parent		=NULL;
	node->move			=-1;
	node->numchildren	=0;
	node->heuristic		=0;
	node->pathcost		=0;
	node->score			=0;
	node->depth			=0;

	return node;
}

/*
 * Initializes start state
 * Input: state
 */
void Solver::initialize(State state) {
	for(int i=0;i<n_tiles;i++) {
		state[i] = startstate[i];
	}
}
			
/*
 * Functions swaps two values in a state
 * Input: state, two value positions
 */
void Solver::addToFringe(TreeNode *node) {
	list<TreeNode*>::iterator itr;

	for(itr=fringe.begin();itr!=fringe.end();itr++) {
		if(node->score <= (*itr)->score) break;
	}
	

	fringe.insert(itr,node);
	//printFringe();
}

/*
 * Prints the fringe
 */
void Solver::printFringe() {
	list<TreeNode*>::iterator itr;

	for(itr=fringe.begin();itr!=fringe.end();itr++) {
		cout<<(*itr)->score<<" ";
	}
	cout<<endl;
}

/*
 * Expand and search
 * Input: node
 */
void Solver::expand(TreeNode *node) {

	TreeNode *temp;

	if(node == NULL) {
		cout<<"Node points to NULL."<<endl;
		exit(1);
	}

	if(node->children[0] == NULL
		&& node->children[1] == NULL
		&& node->children[2] == NULL
		&& node->children[3] == NULL) {
		makeChildren(node);
	}
	else {
		if(node!= NULL) {

			temp = fringe.front();

			fringe.pop_front();
		
			if(solutionFound(temp)) {
				fileOut<<endl<<"SOLUTION FOUND!"<<endl;
				cout<<endl<<"SOLUTION FOUND!"<<endl;
				done(fringe.front());
				if(finished==true) return;
			}

			
			fileOut<<"nodes in memory="<<fringe.size();
			fileOut<<" exploring depth="<<temp->depth<<endl;

			cout<<"nodes in memory="<<fringe.size();
			cout<<" exploring depth="<<temp->depth<<endl;

			fileOut<<"expanding node:"<<endl;
			cout<<"expanding node:"<<endl;
			printBoard(temp->state);
			fileOut<<"with F(N)="<<temp->score<<endl;
			cout<<"with F(N)="<<temp->score<<endl;

			expand(temp);
		}
	}
}

/*
 * Checks for repeated state
 * Input: node
 * Output: integer indicating the status
 *
 * 2 - node repeated
 * 1 - at least one tile misplaced
 * 0 - ancestor points to null
 */
int Solver::checkRepeated(TreeNode *node) {
	TreeNode *grandpa = node->parent->parent;
	if(grandpa == NULL) return 0;
	else {
		for(int i=0;i<n_tiles;i++) {
			if(grandpa->state[i] != node->state[i]) {
				return 1;
			}
		}
	}


	return 2;
}

/*
 * Sets node depth by propagating up the tree
 * Input: node, depth counter
 * Output: depth
 */
int Solver::setDepth(TreeNode *node, int count) {

	if(node->parent == NULL) {
		return count;
	}
	
	count++;

	return setDepth(node->parent, count);

}

/*
 * Create children and swap in appropriate positions
 * Input: node, index of the possibly legal move
 * Output: child node
 */
TreeNode* Solver::create(TreeNode *node, int index) {
	int i, hole_pos, piece_pos;
	TreeNode *child;

	for(i=0;i<n_tiles;i++) {
		if(node->state[i] == 0) break;
	}

	hole_pos = i;
	piece_pos = moving_rules[hole_pos][index];

	// if move is illegal return null
	if(piece_pos == -9) return NULL;

	// otherwise go on with child creation
	child = newnode();
	child->parent = node;


	child->depth = setDepth(node,0);

	for(i=0;i<n_tiles;i++) {
		child->state[i] = node->state[i];
	}
	
	child->state[hole_pos] = node->state[piece_pos];
	child->state[piece_pos] = node->state[hole_pos];
	child->move = node->state[piece_pos];


	evaluate(child);


	return child;
}

/*
 * Check if solution is reached
 * Input: node
 * Output: boolean flag
 */
bool Solver::solutionFound(TreeNode *node) {
	int i;

	for(i=0;i<n_tiles;i++) {
		if(node->state[i] != solution[i]) {
			return false;
		}
	}
	return true;
}

/*
 * Evaluate the note with appropriate heuristics
 * Input: node
 */
void Solver::evaluate(TreeNode *node) {
	// get path cost g(n)
	node->pathcost = node->depth;
	// get heuristic value h(n)
	node->heuristic = getHeuristic(kindOfHeuristic,node);
	// compute f(n)
	node->score = node->pathcost + node->heuristic;
}

/*
 * Functions creates children for a node
 * Input: node
 */
void Solver::makeChildren(TreeNode *node) {

	TreeNode *child;
	int i;

	
	for(i=0;i<n_moves;i++) {

		child = create(node,i);

		if(child == NULL) {
			node->children[i] = NULL;
			continue;
		}

		// check if solutions is reached
		if(solutionFound(child)) {
			fileOut<<endl<<"SOLUTION FOUND!"<<endl;
			cout<<endl<<"SOLUTION FOUND!"<<endl;
			done(child);
			if(finished==true) return;
		}
	
		node->children[i]=child;
		node->numchildren++;

		// add to fringe if not repeated
		if(checkRepeated(child) != 2) {
			addToFringe(child);

		}
	
	}
}


/*
 * Prints the a state on the screen and to file
 * Input: state
 */
void Solver::printBoard(State state) {

	fileOut<<"| "<<state[0]<<" | "
		      <<state[1]<<" | "
			  <<state[2]<<" |"<<endl;

	fileOut<<"| "<<"-"<<" | "<<"-"<<" | "<<"-"<<" |"<<endl;

	fileOut<<"| "<<state[3]<<" | "
			  <<state[4]<<" | "
			  <<state[5]<<" |"<<endl;

	fileOut<<"| "<<"-"<<" | "<<"-"<<" | "<<"-"<<" |"<<endl;

	fileOut<<"| "<<state[6]<<" | "
		      <<state[7]<<" | "
			  <<state[8]<<" |"<<endl;




	cout<<"| "<<state[0]<<" | "
		      <<state[1]<<" | "
			  <<state[2]<<" |"<<endl;

	cout<<"| "<<"-"<<" | "<<"-"<<" | "<<"-"<<" |"<<endl;

	cout<<"| "<<state[3]<<" | "
			  <<state[4]<<" | "
			  <<state[5]<<" |"<<endl;

	cout<<"| "<<"-"<<" | "<<"-"<<" | "<<"-"<<" |"<<endl;

	cout<<"| "<<state[6]<<" | "
		      <<state[7]<<" | "
			  <<state[8]<<" |"<<endl;
}


/*
 * Prints the solution when searching is done by
 * propagating up the tree until null is reached
 * Input: solution node
 */
void Solver::printSolution(TreeNode *node) {
	if(node == NULL) return;

	if(node->move != -1) {
		fileOut<<"Expanded node. ";
		cout<<"Expanded node. ";
		
		fileOut<<"Move: "<<node->move<<endl;
		cout<<"Move: "<<node->move<<endl;
		printBoard(node->state);

		fileOut<<"Node's F(N)="<<node->score<<endl;
		cout<<"Node's F(N)="<<node->score<<endl<<endl;
	}
	else {
		fileOut<<"Initial state: "<<endl;
		cout<<"Initial state: "<<endl;
		printBoard(node->state);
	}

	totalSteps++;
	printSolution(node->parent);
}


/*
 * Main
 */
int main() {

	int hChoice;

	State aState;

	aState[0] = 7;
	aState[1] = 2;
	aState[2] = 4;
	aState[3] = 5;
	aState[4] = 0;
	aState[5] = 6;
	aState[6] = 8;
	aState[7] = 3;
	aState[8] = 1;

	cout<<"1 Manhattan Distance"<<endl
		<<"2 Misplaced tiles"<<endl
		<<"3 n-Maxswap"<<endl
		<<"4 Nilsson's distance"<<endl<<endl;

	cout<<"Choice: ";
	cin>>hChoice;



	Solver puzzle(aState,hChoice);
	puzzle.start();

	fileOut.close();

	return 0;
}