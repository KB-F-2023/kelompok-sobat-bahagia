#include <iostream>
#include <queue>
using namespace std;

const int N = 8;

struct State {
    int board[N][N];
    int row;
    int col;
};

void print_board(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(!board[i][j]) cout << ". ";
			else cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool is_valid(int board[N][N], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
        int row_diff = row - i;
        if (col - row_diff >= 0 && board[i][col - row_diff] == 1) {
            return false;
        }
        if (col + row_diff < N && board[i][col + row_diff] == 1) {
            return false;
        }
    }
    return true;
}

void bfs() {
    queue<State> q;
    State start_state = {0};
    start_state.row = 0;
    q.push(start_state);
    while (!q.empty()) {
        State curr_state = q.front();
        q.pop();
        if (curr_state.row == N) {
            print_board(curr_state.board);
            continue;
        }
        for (int i = 0; i < N; i++) {
            if (is_valid(curr_state.board, curr_state.row, i)) {
                State next_state = {0};
                for (int j = 0; j < N; j++) {
                    for (int k = 0; k < N; k++) {
                        next_state.board[j][k] = curr_state.board[j][k];
                    }
                }
                next_state.board[curr_state.row][i] = 1;
                next_state.row = curr_state.row + 1;
                next_state.col = i;
                q.push(next_state);
            }
        }
    }
}

int main() {
    bfs();
    return 0;
}
