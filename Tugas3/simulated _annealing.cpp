#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
using namespace std;

const int N = 8; // Size of the board
const int MaxIterations = 100000; // Maximum number of iterations
const double InitialTemperature = 1000.0; // Initial temperature
const double CoolingRate = 0.99; // Cooling rate

// Initialize the board with a random placement of the queens
void InitializeBoard(int board[])
{
    for (int i = 0; i < N; i++) {
        board[i] = rand() % N;
    }
}

// Calculate the number of conflicts (pairs of queens that attack each other)
int CalculateConflicts(int board[])
{
    int conflicts = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (board[i] == board[j] || abs(i - j) == abs(board[i] - board[j])) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

// Generate a new candidate solution by randomly moving one queen to a new row in its column
void GenerateNeighbor(int board[])
{
    int column = rand() % N;
    int row = rand() % N;
    board[column] = row;
}

// Simulated Annealing algorithm to solve the 8-Queen problem
void SimulatedAnnealing(int board[])
{
    double temperature = InitialTemperature;
    int currentConflicts = CalculateConflicts(board);
    for (int i = 0; i < MaxIterations && currentConflicts > 0; i++) {
        int newBoard[N];
        memcpy(newBoard, board, N * sizeof(int));
        GenerateNeighbor(newBoard);
        int newConflicts = CalculateConflicts(newBoard);
        int delta = newConflicts - currentConflicts;
        if (delta < 0 || exp(-delta / temperature) > (double)rand() / RAND_MAX) {
            memcpy(board, newBoard, N * sizeof(int));
            currentConflicts = newConflicts;
        }
        temperature *= CoolingRate;
    }
}

// Print the board
void PrintBoard(int board[])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[j] == i) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main()
{
    srand(time(NULL));
    int board[N];
    InitializeBoard(board);
    cout << "Initial board:" << endl;
    PrintBoard(board);
    SimulatedAnnealing(board);
    cout << "Final board:" << endl;
    PrintBoard(board);
    return 0;
}
