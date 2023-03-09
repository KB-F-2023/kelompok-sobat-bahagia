


#include <bits/stdc++.h>
using namespace std;

const int N = 8;
vector<int> queens(N,-1); // queens[i] is the row position of the queen in column i

bool is_valid(int col, int row) {
  for (int i = 0; i < col; i++) 
    if (queens[i] == row || abs(queens[i] - row) == abs(i - col)) 
      return false; // check if the new queen conflicts with existing queens
  return true;
}

void dfs(int col) {
  if (col == N) { // found a valid solution
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (queens[j] == i) {
          cout << i << " "; // print Q for queen
        } else {
          cout << ". "; // print . for empty square
        }
      }
      cout << endl;
    }
    cout << endl;
    return;
  }

  for (int row = 0; row < N; row++) {
    if (is_valid(col, row)) {
      queens[col] = row; // place the queen in the current column
      dfs(col+1); // move on to the next column
    }
  }
}

int main() {
  dfs(0);
}
