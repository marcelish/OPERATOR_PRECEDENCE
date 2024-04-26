#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
/*1. Define a function grammar(nonterminals, terminals):
   - Open the grammar file "1QGRAMMAR.txt".
   - Iterate through each line in the file:
     - Extract the first character of each line as a nonterminal.
     - Store lowercase characters as terminals.
   - Close the file.

2. Define a function conmatrix(combinedVectors, matrix):
   - Open the grammar file "1QGRAMMAR.txt".
   - Iterate through each line in the file:
     - Skip empty lines or special characters.
     - Find the row index corresponding to the nonterminal in the combinedVectors.
     - Traverse the line character by character:
       - If a lowercase character is followed by an uppercase character:
         - Find the column index corresponding to the uppercase character in the combinedVectors.
         - Set the matrix element at (row, col) to 1.
   - Close the file.

3. Define a function conplusmatrix(combinedVectors, matrix):
   - Initialize a type variable to "CON+".
   - Perform transitive closure on the matrix:
     - For each k from 0 to the size of the matrix:
       - For each i from 0 to the size of the matrix:
         - For each j from 0 to the size of the matrix:
           - Update the matrix element at (i, j) to be true if there's a path from i to j via k.
   - Print the matrix with labels.

4. Define a function constarmatrix(combinedVectors, matrix):
   - Initialize a type variable to "CON*".
   - Perform transitive closure on the matrix:
     - For each k from 0 to the size of the matrix:
       - For each i from 0 to the size of the matrix:
         - For each j from 0 to the size of the matrix:
           - Update the matrix element at (i, j) to be true if there's a path from i to j via k.
   - Add an identity matrix (diagonal elements set to 1).
   - Print the matrix with labels.

5. Define a function GRD(combinedVectors, groundmatrix):
   - Open the grammar file "1QGRAMMAR.txt".
   - Iterate through each line in the file:
     - Skip empty lines or special characters.
     - Find the row index corresponding to the nonterminal in the combinedVectors.
     - Traverse the line character by character:
       - If an uppercase character is followed by a lowercase character:
         - Find the column index corresponding to the lowercase character in the combinedVectors.
         - Set the groundmatrix element at (row, col) to 1.
   - Close the file.
   - Print the matrix with labels.

6. Define a function printMatrixWithLabels(type, combinedVectors, matrix):
   - Print the type of the matrix.
   - Print the labels for the columns.
   - Iterate over each row and print the corresponding row label followed by the row elements.

7. In the main function:
   - Define variables for nonterminals, terminals, matrix, and groundmatrix.
   - Call the grammar function to populate nonterminals and terminals.
   - Combine nonterminals and terminals into a single vector.
   - Initialize matrices with appropriate sizes and values.
   - Call conmatrix, conplusmatrix, constarmatrix, and GRD functions to generate matrices.
   - Multiply the CON* matrix with the GRD matrix to get the result matrix.
   - Print the result matrix.
*/
void printMatrixWithLabels(string type, const vector<string>& combinedVectors, const vector<vector<int>>& matrix);
void grammar(vector<string>& nonterminals, set<char>& terminals) {
    ifstream file("1QGRAMMAR.txt");
    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        if (line.empty() || line == "=" || line == "|") { // Skip empty lines or special characters
            continue;
        }
        nonterminals.push_back(line.substr(0, 1)); // Store the first character of each line as a nonterminal
        // Store the lowercase characters as terminals (avoiding duplicates)
        for (char ch : line) {
            if (islower(ch)) {
                terminals.insert(ch);
            }
        }
        cout << line << endl;
    }
    file.close();
}
void conmatrix(const vector<string>& combinedVectors, vector<vector<int>>& matrix) {
    ifstream file("1QGRAMMAR.txt");
    string line;
    while (getline(file, line)) {
        if (line.empty() || line == "=" || line == "|") {
            continue;
        }
        int row = distance(combinedVectors.begin(), find(combinedVectors.begin(), combinedVectors.end(), line.substr(0, 1)));
        bool foundEquals = false; // Flag to indicate if '=' has been found
        for (size_t i = 0; i < line.size() - 1; ++i) { // Iterate until the second last character
            char ch = line[i];
            if (ch == '=') {
                foundEquals = true;
                continue; // Skip '=' and start processing characters after it
            }
            if (!foundEquals) {
                continue; // Skip characters until '=' is found
            }
            char nextch = line[i + 1];
            if (islower(ch) && isupper(nextch)) { // Check if ch is lowercase and nextch is uppercase
                int col = distance(combinedVectors.begin(), find(combinedVectors.begin(), combinedVectors.end(), string(1, nextch)));
                matrix[row][col] = 1;
            }
            if (isupper(ch) && islower(nextch)) { // Check if ch is uppercase and nextch is lowercase
                int col = distance(combinedVectors.begin(), find(combinedVectors.begin(), combinedVectors.end(), string(1, ch)));
                matrix[row][col] = 1;
            }
            if (isupper(ch) && isupper(nextch)) { // Check if ch is uppercase and nextch is uppercase
                int col = distance(combinedVectors.begin(), find(combinedVectors.begin(), combinedVectors.end(), string(1, ch)));
                matrix[row][col] = 1;
            }
            if (isupper(ch) && (nextch == '|' || nextch == ' ' || nextch == '\n')) { // check if ch is uppercase and nextch is | or space or \n
                int col = distance(combinedVectors.begin(), find(combinedVectors.begin(), combinedVectors.end(), string(1, ch)));
                matrix[row][col] = 1;
            }
        }
    }
    file.close();
     // Printing the matrix with the labels
    string type = "CON";
    printMatrixWithLabels(type, combinedVectors, matrix);
}
void conplusmatrix(const vector<string>& combinedVectors, vector<vector<int>>& matrix) {
    string type = "CON+";
    
    // Perform transitive closure and handle disconnected symbols
    for (int k = 0; k < matrix.size(); ++k) {
        for (int i = 0; i < matrix.size(); ++i) {
            bool connected = false;
            for (int j = 0; j < matrix.size(); ++j) {
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
                if (matrix[i][j]) {
                    connected = true;
                }
            }
            // If not connected and not distinguished symbol, mark as not connected
            if (!connected && combinedVectors[i] != "distinguished_symbol") {
                for (int j = 0; j < matrix.size(); ++j) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
    
    // Printing the CON+ matrix with the labels
    printMatrixWithLabels(type, combinedVectors, matrix);
}
void constarmatrix(const vector<string>& combinedVectors, vector<vector<int>>& matrix) {
    string type = "CON*";

    // Perform transitive closure on the CON matrix
    for (int k = 0; k < matrix.size(); ++k) {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
            }
        }
    }

    // Add the identity matrix (diagonal elements set to 1)
    for (int i = 0; i < matrix.size(); ++i) {
        matrix[i][i] = 1;
    }

    // Printing the CON* matrix with the labels
    printMatrixWithLabels(type, combinedVectors, matrix);
}
void GRD(const vector<string>& combinedVectors, vector<vector<int>>& groundmatrix) {
    string type = "GROUND";
    ifstream file("1QGRAMMAR.txt");
    string line;
    while (getline(file, line)) {
    if (line.empty() || line == "=" || line == "|") {
        continue;
    }
    int row = distance(combinedVectors.begin(), find(combinedVectors.begin(), combinedVectors.end(), line.substr(0, 1)));
    for (size_t i = 0; i < line.size() - 1; ++i) { // Iterate until the second last character
        char ch = line[i];
        char nextch = line[i + 1];
        if (isupper(ch) && islower(nextch)) {
            // Skip untile | or space or \n is found
            while (nextch != '|' && nextch != ' ' && nextch != '\n') {
                i++;
                nextch = line[i + 1];
                if (nextch == '\n' || nextch == '|' || nextch == ' ') {
                    ch = line[i];
                }
            }
        } else if (islower(ch) && (nextch == '|' || nextch == ' ' || nextch == '\n')) {
            int col = distance(combinedVectors.begin(), find(combinedVectors.begin(), combinedVectors.end(), string(1, ch)));
            groundmatrix[row][col] = 1;
        }
    }
}
    file.close();
    printMatrixWithLabels(type, combinedVectors, groundmatrix);
}
void printMatrixWithLabels(string type, const vector<string>& combinedVectors, const vector<vector<int>>& matrix) {
    cout << type << " MATRIX" << endl;
    cout << "  ";
    for (string s : combinedVectors) {
        cout << s << " ";
    }
    cout << endl;
    for (int i = 0; i < matrix.size(); i++) {
        cout << combinedVectors[i] << " ";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int main() {
    // Nonterminal and terminal vectors
    vector<string> nonterminals;
    set<char> terminals;
    vector<vector<int>> matrix;
    vector<vector<int>> groundmatrix;
    // Populate grammar
    grammar(nonterminals, terminals);
    // Combine nonterminals and terminals into a single vector
    vector<string> combinedVectors;
    combinedVectors.insert(combinedVectors.end(), nonterminals.begin(), nonterminals.end());
    // Add terminals to the combined vector
    for (char ch : terminals) {
        combinedVectors.push_back(string(1, ch));
    }
    matrix.assign(combinedVectors.size(), vector<int>(combinedVectors.size(), 0));
    groundmatrix.assign(combinedVectors.size(), vector<int>(combinedVectors.size(), 0));
    // Generating conmatrix
    conmatrix(combinedVectors, matrix);
    // Generating the con+ matrix
    conplusmatrix(combinedVectors, matrix);
    // Generating the con* matrix
    constarmatrix(combinedVectors, matrix);
    // Generating groundmatrix
    GRD(combinedVectors, groundmatrix);
    // matrix multiplication for con* and groundmatrix
    vector<vector<int>> resultmatrix;
    resultmatrix.assign(combinedVectors.size(), vector<int>(combinedVectors.size(), 0));
    for (int i = 0; i < combinedVectors.size(); i++) {
        for (int j = 0; j < combinedVectors.size(); j++) {
            for (int k = 0; k < combinedVectors.size(); k++) {
                resultmatrix[i][j] += matrix[i][k] * groundmatrix[k][j];
            }
        }
    }
    // Printing the result matrix
    string type = "(CON*)^(GRD)";
    printMatrixWithLabels(type, combinedVectors, resultmatrix);
    
    return 0;
}
