#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

const int INF = 1e9;

vector<vector<int>> Floyd(vector<vector<int>> W, int n) {
    vector<vector<int>> D = W;
    
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (D[i][k] != INF && D[k][j] != INF) {
                    if (D[i][j] > D[i][k] + D[k][j]) {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
            }
        }
    }
    
    return D;
}

int main() {
    int n = 8;
    vector<vector<int>> W(n + 1, vector<int>(n + 1, INF));

    for (int i = 1; i <= n; ++i)
        W[i][i] = 0;

    W[1][3] = 2; W[3][1] = 2;
    W[1][4] = 4; W[4][1] = 4;
    W[1][2] = 8; W[2][1] = 8;
    W[1][5] = 3; W[5][1] = 3;

    W[2][3] = 6; W[3][2] = 6;
    W[2][6] = 3; W[6][2] = 3;
    W[2][5] = 6; W[5][2] = 6;

    W[3][8] = 4; W[8][3] = 4;
    W[3][6] = 7; W[6][3] = 7;

    W[4][5] = 1; W[5][4] = 1;

    W[5][7] = 4; W[7][5] = 4;

    W[6][8] = 1; W[8][6] = 1;
    W[6][7] = 3; W[7][6] = 3;

    W[7][8] = 5; W[8][7] = 5;

    vector<vector<int>> D = Floyd(W, n);

    cout << "Матриця найкоротших відстаней D (починаючи з вершини 1):\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (D[i][j] == INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << D[i][j];
        }
        cout << "\n";
    }

    return 0;
}
