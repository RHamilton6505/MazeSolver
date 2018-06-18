#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int bruteForceMazeSolver(struct maze myMaze, int i, int j, char **pathArray, bool oneShot, int start, int end);
int backtrackingMazeSolver(int i, int j);
int greedyMazeSolver(int i, int j);
int divideAndConquerMazeSolver(int i, int j);
int dynamicProgrammingMazeSolver(int i, int j);
int randomizedMazeSolver(int i, int j);
bool isEmpty(struct maze myMaze, int i, int j);
bool hasBeenChecked(struct maze myMaze, int i, int j);
int bruteForceMazeSolver(struct maze myMaze, int i, int j, char **pathArray, bool oneShot, int start, int end);
void printArray(char **pathArray, int row, int col);

struct maze
{
	int rows;
	int cols;
	char matrix [100][100];
};

maze myMaze;

int main()
{
	//required variables
	ifstream in;
	in.open("maze.txt");
	char line;

	//read the matrix using plain c code, character by character
	in >> myMaze.rows;
	in >> line;
	in >> myMaze.cols;
	cout << "Reading a " << myMaze.rows << " by " << myMaze.cols << " matrix." << endl;
	//Burn the end of line character
	in.ignore(200,'\n');
	for(int i=0; i<myMaze.rows; i++)
	{
		for(int j=0; j<myMaze.cols; j++)
		{
			in.get( myMaze.matrix[i][j] );
		}
		//Burn the end of line character
		in.ignore(200,'\n');
	}

	//Print the empty maze
	for(int i=0; i<myMaze.rows; i++)
	{
		for(int j=0; j<myMaze.cols; j++)
		cout << myMaze.matrix[i][j];
		cout << endl;
	}
	int x=1,y=1;

	//Find starting coordinates
	for(int i=0; i<myMaze.rows; i++)
	for(int j=0; j<myMaze.cols; j++)
	if( myMaze.matrix[i][j] == 'S' ){
		x=i;
		y=j;
	}

	//Call a recursive mazeSolver
	//FIXME:RH:int bfDistance = bruteForceMazeSolver(x,y);     //brute force? dnc?
	int btDistance = backtrackingMazeSolver(x,y);     //brute force? dnc?
	int gDistance = greedyMazeSolver(x,y);
	int dncDistance = divideAndConquerMazeSolver(x,y);
	int dpDistance = dynamicProgrammingMazeSolver(x,y);
	int rDistance = randomizedMazeSolver(x,y);

	//cout << "Brute force distance: " << bfDistance << " units away!" << endl;
	cout << "Backtracking distance: " << btDistance << " units away!" << endl;
	cout << "Greedy distance: " << gDistance << " units away!" << endl;
	cout << "Divide and conquer distance: " << dncDistance << " units away!" << endl;
	cout << "Dynamic programming distance: " << dpDistance << " units away!" << endl;
	cout << "Randomized distance: " << rDistance << " units away!" << endl;

	//Print solved maze - x2
	// for(int i=0; i<myMaze.rows; i++)
	// {
	// 	for(int j=0; j<myMaze.cols; j++)
	// 	cout << myMaze.matrix[i][j];
	// 	cout << endl;
	// }

	// ****************************************
	// Begin Student Written Section
	// ****************************************

	char **path;
	bool alwaysTrue = true;

	path = new char *[myMaze.rows];
	for(int i=0 ; i<myMaze.rows ; i++){
		path[i] = new char[myMaze.cols];
		for(int j=0 ; j<myMaze.cols ; j++)
		path[i][j] = '-';
	}


	// path[0][0] = 'q';
	// path[0][1] = 'w';
	// path[1][0] = 'a';
	// path[1][1] = 'd';
	//
	// printArray(path,2,2);


	bruteForceMazeSolver(myMaze, 1, 1, path, !alwaysTrue, x, y);



	// // false
	// bool isEmptySpotZeroZero = isEmpty(myMaze,0,0);
	// // true
	// bool isEmptySpotOneTen = isEmpty(myMaze,1,10);
	//
	// if(isEmptySpotZeroZero) cout << "wrong" << endl;
	// else cout<< "right" << endl;
	//
	// if(!isEmptySpotOneTen) cout << "wrong" << endl;
	// else cout<< "right" << endl;

	return 0;
}

int bruteForceMazeSolver(struct maze myMaze, int i, int j, char **pathArray, bool oneShot, int start, int end)
{


	// will not activate unless this is the first iteration
	if(!oneShot){
		i = start;
		j = end;
		oneShot = true;
		printArray(pathArray, myMaze.rows, myMaze.cols);
	}

	printArray(pathArray, myMaze.rows, myMaze.cols);

	// Check if adjacent spot is F
	if(myMaze.matrix[i][j]=='F'){
		printArray(pathArray, myMaze.rows, myMaze.cols);
	}
	else{
		if(isEmpty(myMaze,i,j+1)){
			// pathArray[i][j] = 't'; FIXME:RH:Change pathArray's to myMaze t, not pathArray
			bruteForceMazeSolver(myMaze, i, j+1, pathArray, oneShot, start, end);
		}
		else{
			if(isEmpty(myMaze,i+1,j)){
				pathArray[i][j] = 't';
				bruteForceMazeSolver(myMaze, i+1, j, pathArray, oneShot, start, end);
			}
			else{
				if(isEmpty(myMaze,i-1,j)){
					pathArray[i][j] = 't';
					bruteForceMazeSolver(myMaze, i-1, j, pathArray, oneShot, start, end);
				}
				else{
					if(isEmpty(myMaze,i,j-1)){
						pathArray[i][j] = 't';
						bruteForceMazeSolver(myMaze, i, j-1, pathArray, oneShot, start, end);
					}
					else{
						if(hasBeenChecked(myMaze,i,j+1)){
							pathArray[i][j] = 'x';
							bruteForceMazeSolver(myMaze, i, j+1, pathArray, oneShot, start, end);
						}
						else{
							if(hasBeenChecked(myMaze,i+1,j)){
								pathArray[i][j] = 'x';
								bruteForceMazeSolver(myMaze, i+1, j, pathArray, oneShot, start, end);
							}
							else{
								if(hasBeenChecked(myMaze,i-1,j)){
									pathArray[i][j] = 'x';
									bruteForceMazeSolver(myMaze, i-1, j, pathArray, oneShot, start, end);
								}
								else{
									if(hasBeenChecked(myMaze,i,j-1)){
										pathArray[i][j] = 'x';
										bruteForceMazeSolver(myMaze, i, j-1, pathArray, oneShot, start, end);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Check if east is empty



	//add algorithm here
	return -1;
}
int backtrackingMazeSolver(int i, int j)
{
	//algorithm goes here
	return -1;
}
int greedyMazeSolver(int i, int j)
{
	//algorithm goes here
	return -1;
}
int divideAndConquerMazeSolver(int i, int j)
{
	//algorithm goes here
	return -1;
}
int dynamicProgrammingMazeSolver(int i, int j)
{
	//algorithm goes here
	return -1;
}
int randomizedMazeSolver(int i, int j)
{
	//algorithm goes here
	return -1;
}

// Added by RH
// given the maze, and the space to check, will check
// for to see if the lacation is valid first, then if so
// will check the character stored is a space character
// (not in the Master Chief sorta way), then set the return
// condition to true
bool isEmpty(struct maze myMaze, int i, int j){
	bool isEmpty = false;
	bool isValidLocation = true;

	// check if valid
	if(myMaze.rows < i){
		cout << "Not a valid row lacation";
		isValidLocation = !isValidLocation;
	}
	if(myMaze.cols < j){
		cout << "Not a valid col lacation";
		isValidLocation = !isValidLocation;
	}

	// check if space
	if(isValidLocation){
		if(myMaze.matrix[i][j] == ' ')
		{
			isEmpty = true;
		}
	}

	// FIXME: RH: add a tracking character to myMaze?



	return isEmpty;

}

// Added by RH
// Same as isValid, but for check the char 't'
bool hasBeenChecked(struct maze myMaze, int i, int j){
	bool isTracked = false;
	bool isValidLocation = true;

	// check if valid
	if(myMaze.rows < i){
		cout << "Not a valid row lacation";
		isValidLocation = !isValidLocation;
	}
	if(myMaze.cols < j){
		cout << "Not a valid col lacation";
		isValidLocation = !isValidLocation;
	}


	// check if space
	if(isValidLocation){
		if(myMaze.matrix[i][j] == ' ')
		{
			isTracked = true;
		}
	}

	return isTracked;

}

void printArray(char **pathArray, int row, int col){
	for(int i=0 ; i<row ; i++){
		for(int j=0 ; j<col ; j++){
			cout << pathArray[i][j];
		}
		cout << endl;
	}
}

//recursion!!
//Mark current location
//Base Case: Look north, south, east, west for victory!
//Mark our path
//Try going south if it is open
//Try going north if it is open
//Try going east if it is open
//Try going west if it is open
