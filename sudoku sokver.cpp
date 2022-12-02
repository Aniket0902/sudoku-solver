#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int const N = 9;
int const n = 3;

void printBoard(vector<vector<int> > board) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool checkRow(vector<vector<int> > board) {
	for(int i=0; i<N; i++) {
		// create array
		int arr[N];
		for(int j=0; j<N; j++) arr[j] = board[i][j];

		// eval array
		sort(arr, arr+N);
		for(int j=1; j<N; j++) {
			if(arr[j] == 0) continue;
			if(arr[j] == arr[j-1]) return false;
		}
	} return true;
}

bool checkCol(vector<vector<int> > board) {
	for(int i=0; i<N; i++) {
		// create array
		int arr[N];
		for(int j=0; j<N; j++) arr[j] = board[j][i];

		// eval array
		sort(arr, arr+N);
		for(int j=1; j<N; j++) {
			if(arr[j] == 0) continue;
			if(arr[j] == arr[j-1]) return false;
		}
	} return true;
}

bool checkBox(vector<vector<int> > board) {
	for(int i=0; i<N; i++) {
		// create array
		int arr[N];
		for(int j=0; j<N; j++) arr[j] = board[((i/n)*n)+(j/n)][((i%n)*n)+(j%n)];

		// eval array
		sort(arr, arr+N);
		for(int j=1; j<N; j++) {
			if(arr[j] == 0) continue;
			if(arr[j] == arr[j-1]) return false;
		}
	} return true;
}


bool checkBoard(vector<vector<int> > board) {
	if(checkRow(board) && checkCol(board) && checkBox(board)) return true;
	else return false;
}

int findNextSpace(vector<vector<int> > board) {
	for(int i=0; i<N*N; i++) {
		if(board[i/N][i%N] == 0) return i;
	} return -1;
}

void insertBoard(vector<vector<int> > &board, int index, int num) {
	board[index/N].at(index%N) = num;
}

bool canInsertBoard(vector<vector<int> > board, int nextAvailableSpace, int num) {
	insertBoard(board,nextAvailableSpace,num);
	if(checkBoard(board)) return true;
	else return false;
}

bool solveBoard(vector<vector<int> > &board) {
	int nextAvailableSpace = findNextSpace(board);
	if(nextAvailableSpace == -1) return true;
	for(int i=1; i<=N; i++) {
		if(canInsertBoard(board,nextAvailableSpace,i)) {
			insertBoard(board,nextAvailableSpace,i);
			if (solveBoard(board)) return true;
			else insertBoard(board,nextAvailableSpace,0); // undo previous insert
		}
	} return false;
}

int main () {
	vector<vector<int> > board(N);
	
	// input into board
    cout<<"\nGIVE INPUT FOR THE SUDOKU, FOR BLANK SPACES GIVE 0 AS INPUT\n";
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			int input;
			cin>>input;
			if(input>=0 && input<=N) board[i].push_back(input);
			else {
				cout<<"Invalid inputs!"<<endl;
				return -1;
			}
		}
	}
	cout<<endl;
	if(solveBoard(board)) printBoard(board);
	else cout<<"This board is impossible to solve!"<<endl;
}