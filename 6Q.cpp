#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
void printBMatrix(string type, vector<vector<int>> &BMATRIX);
// transpose matrix
void transpose(vector<vector<int>> &b){
    if (b.size() == 0)
        return;
    vector<vector<int> > trans_vec(b[0].size(), vector<int>());
    for (int i = 0; i < b.size(); i++){
        for (int j = 0; j < b[i].size(); j++){
            trans_vec[j].push_back(b[i][j]);
        }
    }
    b = trans_vec;
}
// multiply matrices
void multiply(vector<vector<int>> &a, vector<vector<int>> &b, vector<vector<int>> &c){
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < b[0].size(); j++){
            for (int k = 0; k < b.size(); k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
// transitive closure
void transitiveClosure(vector<vector<int>> &matrix){
    for (size_t k = 0; k < matrix.size(); ++k){
        for (size_t i = 0; i < matrix.size(); ++i){
            for (size_t j = 0; j < matrix.size(); ++j){
                if (matrix[i][k] == 1 && matrix[k][j] == 1){
                    matrix[i][j] = 1;
                }
            }
        }
    }
}
// PRINTING MATRIX WITH LABELS
void printMatrix(vector<vector<int>> &a, vector<string> &labels){
    cout << endl; cout << "  "; cout << endl;
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a[0].size(); j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void Yieldsto(vector<vector<int>> &Yieldsto, vector<string> &OrderedGrammar){
    Yieldsto = {
        // fill with 0s
        {0, 0, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 1}
    };
    cout << "YIELDS TO";
    printMatrix(Yieldsto, OrderedGrammar);
    cout << "YIELDS TO : TRANSPOSE";
    transpose(Yieldsto);
    printMatrix(Yieldsto, OrderedGrammar);
}
void TakesPresedence(vector<vector<int>> &TakesPrecedence, vector<string> &OrderedGrammar){
    TakesPrecedence = {
        // fill with 0s
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1},
    };
    cout << "TAKES PRECEDENCE";
    printMatrix(TakesPrecedence, OrderedGrammar);
}
void CONSTRUCTING(vector<vector<int>> &BMATRIX, vector<vector<int>> &TakesPrecedence, vector<vector<int>> &YieldsTo, vector<vector<int>> &Equals, vector<string> &OrderedGrammar){
    // putting takes precedence in the first quadrant of the b matrix
    for (int i = 0; i < TakesPrecedence.size(); i++){
        for (int j = 0; j < TakesPrecedence[0].size(); j++){
            BMATRIX[i][j + TakesPrecedence.size()] = TakesPrecedence[i][j];
        }
    }
    // putting yields to in the third quadrant of the b matrix
    for (int i = 0; i < YieldsTo.size(); i++){
        for (int j = 0; j < YieldsTo[0].size(); j++){
            BMATRIX[i + YieldsTo.size()][j] = YieldsTo[i][j];
        }
    }
    printBMatrix("B MATRIX: ", BMATRIX);
    // getting the transitive closure of the b matrix
    transitiveClosure(BMATRIX);
    printBMatrix("B+ : ", BMATRIX);
    // adding the identity matrix to the b matrix
    for (int i = 0; i < BMATRIX.size(); i++){
        for (int j = 0; j < BMATRIX[0].size(); j++){
            if (i == j){
                BMATRIX[i][j] = 1;}
        }
    }
    printBMatrix("B* : ", BMATRIX);
    // adding the rows of the b matrix and display the final row summation
    vector<int> rowSummation(BMATRIX.size(), 0);
    for (int i = 0; i < BMATRIX.size(); i++){
        for (int j = 0; j < BMATRIX[0].size(); j++){
            rowSummation[i] += BMATRIX[i][j];}}
    // Calculate the number of elements per row
    int elementsPerRow = rowSummation.size() / 2;
    // Displaying the row summation
    cout << endl;
    cout << "PRECEDENCE FUNCTION" << endl;
    cout << "f ";
    for (int i = 0; i < rowSummation.size(); i++){
        cout << rowSummation[i] << " ";
        // Print a newline after printing the first half of the elements
        if (i == elementsPerRow - 1){
            cout << endl;
            cout << "g ";
        }
    }
    cout << endl;
}
void printBMatrix(string type, vector<vector<int>> &BMATRIX){
    cout << endl;
    cout << type <<" MATRIX" << endl;
    cout << endl;
    for (int i = 0; i < BMATRIX.size(); i++){
        for (int j = 0; j < BMATRIX[0].size(); j++)
        {
            cout << BMATRIX[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    vector<string> OrderedGrammar = {"WHILE", "IF", "THEN", "=", "*", ":=", "DO","$"};
    // takes precedence
    vector<vector<int>> TakesPrecedence(OrderedGrammar.size(), vector<int>(OrderedGrammar.size(), 0));
    // yields to
    vector<vector<int>> YieldsTo(OrderedGrammar.size(), vector<int>(OrderedGrammar.size(), 0));
    // equals
    vector<vector<int>> Equals(OrderedGrammar.size(), vector<int>(OrderedGrammar.size(), 0));
    // setting up the bmatrix // b matrix
    vector<vector<int>> BMATRIX(OrderedGrammar.size() * 2, vector<int>(OrderedGrammar.size() * 2, 0));
    // yields to
    Yieldsto(YieldsTo, OrderedGrammar);
    // takes precedence
    TakesPresedence(TakesPrecedence, OrderedGrammar);
    // contructing the b matrix
    CONSTRUCTING(BMATRIX, TakesPrecedence, YieldsTo, Equals, OrderedGrammar);
    return 0;
}