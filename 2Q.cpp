#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void printMatrix(const vector<string>& OrderedGrammar, const vector<vector<int>>& matrix);
void FIRST(vector<vector<int>>& FIRSTmatrix, const vector<string>& OrderedGrammar);
void generateRoutes(const vector<vector<int>>& FIRSTmatrix, const vector<string>& OrderedGrammar, int start, int end, vector<string>& path, vector<vector<string>>& routes);
void transitiveClosure(vector<vector<int>>& matrix);
int main() {
    vector<string> OrderedGrammar = {"A", "B", "C", "D", "E", "F", "G", "H", "J", "K"};
    vector<vector<int>> FIRSTmatrix(OrderedGrammar.size(), vector<int>(OrderedGrammar.size(), 0));
    FIRST(FIRSTmatrix, OrderedGrammar);

    // Prompt user to input start and end points
    int start, end;
    cout << "Enter the index of the starting point (0-" << OrderedGrammar.size() - 1 << "): ";
    cin >> start;
    cout << "Enter the index of the ending point (0-" << OrderedGrammar.size() - 1 << "): ";
    cin >> end;

    if (start < 0 || start >= OrderedGrammar.size() || end < 0 || end >= OrderedGrammar.size()) {
        cout << "Invalid input. Exiting." << endl;
        return 1;
    }

    // Generate routes between two points
    vector<string> path;
    vector<vector<string>> routes;
    generateRoutes(FIRSTmatrix, OrderedGrammar, start, end, path, routes);

    // Display routes
    cout << endl;
    cout << "Routes from " << OrderedGrammar[start] << " to " << OrderedGrammar[end] << ":" << endl;
    for (const auto& route : routes) {
        cout << "Route: ";
        for (const auto& node : route) {
            cout << node << " -> ";
        }
        cout << endl;
    }
    cout << endl;
    transitiveClosure(FIRSTmatrix);
    cout << "transitive closure: ";
    printMatrix(OrderedGrammar, FIRSTmatrix);
    // Display all mappings
    cout << endl;
    cout << "Mappings:" << endl;
    for (int i = 0; i < OrderedGrammar.size(); ++i) {
        unordered_set<string> nonTerminals;
        for (int j = 0; j < OrderedGrammar.size(); ++j) {
            if (FIRSTmatrix[i][j] == 1) {
                nonTerminals.insert(OrderedGrammar[j]);
            }
        }
        if (!nonTerminals.empty()) {
            cout << " ( " << OrderedGrammar[i] << " ) --> {";
            bool first = true;
            for (const auto& nt : nonTerminals) {
                if (!first) cout << ", ";
                cout << nt;
                first = false;
            }
            cout << "}" << endl;
        }
    }
    return 0;
}

void printMatrix(const vector<string>& OrderedGrammar, const vector<vector<int>>& matrix) {
    cout << "Matrix" << endl;
    cout << "   ";
    for (int i = 0; i < OrderedGrammar.size(); ++i) {
        if (i != 0) cout << " ";
        cout << OrderedGrammar[i];
    }
    cout << endl;
    for (int i = 0; i < OrderedGrammar.size(); ++i) {
        cout << OrderedGrammar[i] << "  ";
        for (int j = 0; j < OrderedGrammar.size(); ++j) {
            cout << matrix[i][j];
            if (j != OrderedGrammar.size() - 1) cout << " ";
        }
        cout << endl;
    }
}

void FIRST(vector<vector<int>>& FIRSTmatrix, const vector<string>& OrderedGrammar) {
    FIRSTmatrix = {
        {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 1, 0, 1, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    printMatrix(OrderedGrammar, FIRSTmatrix);
}
void generateRoutes(const vector<vector<int>>& FIRSTmatrix, const vector<string>& OrderedGrammar, int start, int end, vector<string>& path, vector<vector<string>>& routes) {
    path.push_back(OrderedGrammar[start]);

    if (start == end) {
        routes.push_back(path);
    } else {
        for (int i = 0; i < FIRSTmatrix.size(); ++i) {
            if (FIRSTmatrix[start][i] == 1) {
                // Check if the node has already been visited to avoid cycles
                if (find(path.begin(), path.end(), OrderedGrammar[i]) == path.end()) {
                    generateRoutes(FIRSTmatrix, OrderedGrammar, i, end, path, routes);
                }
            }
        }
    }

    path.pop_back(); // Backtrack
}
void transitiveClosure(vector<vector<int>>& matrix) {
    for (int k = 0; k < matrix.size(); ++k) {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                if (matrix[i][k] == 1 && matrix[k][j] == 1) {
                    matrix[i][j] = 1;
                }
            }
        }
    }
}