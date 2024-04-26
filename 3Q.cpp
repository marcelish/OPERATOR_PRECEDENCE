#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
void printMatrix(string type, const vector<string>& OrderedGrammar, const vector<string>& grammar, const vector<vector<int>>& matrix);
void transitiveClosure(vector<vector<int>>& matrix);
// Read the grammar from the file
void readGrammar(vector<string> &grammar) {
    ifstream file("3Q.txt");
    string line;
    unordered_set<string> uniqueTokens;
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            string token;
            while (iss >> token) {
                if (token == "|"){
                    continue;
                } else {
                    uniqueTokens.insert(token);
                }
            }
        }
        file.close(); // Close the file after reading
    } else {
        cout << "Unable to open file" << endl;
        return;
    }

    // Transfer unique tokens from set to vector in the order of appearance
    grammar.assign(uniqueTokens.begin(), uniqueTokens.end());
}
// FIRST matrix
void FIRST(vector<vector<int>>& FIRSTmatrix, const vector<vector<int>>& EQUALmatrix, const vector<string>& grammar, const vector<string>& OrderedGrammar) {
    FIRSTmatrix = {
        {0,1,0,0,0,0,0,0,0,0}, //E
        {0,0,0,0,0,0,0,0,0,0}, //a
        {0,0,0,0,0,0,0,0,0,0}, //:=
        {0,1,0,1,0,0,0,0,0,0}, //A
        {0,0,0,0,0,0,0,0,0,0}, //%
        {0,1,0,0,0,0,0,1,0,0}, //B
        {0,0,0,0,0,0,0,0,0,0}, //#
        {0,0,0,0,0,0,0,0,0,0}, //(
        {0,0,0,0,0,0,0,0,0,0}, //)
        {0,0,0,0,0,0,0,0,0,0} };// **
    printMatrix("FIRST ", OrderedGrammar, grammar, FIRSTmatrix);
    // getting firstplus
    // applying transitive closure
    transitiveClosure(FIRSTmatrix);
    printMatrix("FIRST+ ", OrderedGrammar, grammar, FIRSTmatrix);
}
// LAST matrix
void LAST(vector<vector<int>>& LASTmatrix, const vector<string>& grammar, const vector<string>& OrderedGrammar) {
    LASTmatrix = {
        {0,0,0,1,0,0,0,0,0,0}, //E
        {0,0,0,0,0,0,0,0,0,0}, //a
        {0,0,0,0,0,0,0,0,0,0}, //:=
        {0,1,0,0,0,1,0,0,0,0}, //A
        {0,0,0,0,0,0,0,0,0,0}, //%
        {0,1,0,0,0,1,0,0,1,0}, //B
        {0,0,0,0,0,0,0,0,0,0}, //#
        {0,0,0,0,0,0,0,0,0,0}, //(
        {0,0,0,0,0,0,0,0,0,0}, //)
        {0,0,0,0,0,0,0,0,0,0}// **
    };
    printMatrix("LAST", OrderedGrammar, grammar, LASTmatrix);
    // GETTING lastplus
    // applying transitive closure
    transitiveClosure(LASTmatrix);
    printMatrix("LAST+", OrderedGrammar, grammar, LASTmatrix);
}
// = matrix
void EQUAL(vector<vector<int>>& EQUALmatrix, const vector<string>& grammar, const vector<string>& OrderedGrammar) {
    //populate with 0s
    EQUALmatrix = {
        {0,0,0,0,0,0,0,0,0,0}, //E
        {0,0,1,0,0,0,0,0,0,1}, //a
        {0,0,0,1,0,0,0,0,0,0}, //:=
        {0,0,0,0,1,0,1,0,1,0}, //A
        {0,0,0,0,0,1,0,0,0,0}, //%
        {0,0,0,0,0,0,0,0,0,0}, //B
        {0,0,0,0,0,1,0,0,0,0}, //#
        {0,0,0,1,0,0,0,0,0,0}, //(
        {0,0,0,0,0,0,0,0,0,0}, //)
        {0,0,0,0,0,1,0,0,0,0}// **
    };
    printMatrix("= ", OrderedGrammar, grammar, EQUALmatrix);
}
// transitive closure
void transitiveClosure(vector<vector<int>>& matrix) {
    for (size_t k = 0; k < matrix.size(); ++k) {
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix.size(); ++j) {
                if (matrix[i][k] == 1 && matrix[k][j] == 1) {
                    matrix[i][j] = 1;
                }
            }
        }
    }
}
// multiplication of matrices
void multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& result) {
    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix2[0].size(); ++j) {
            for (size_t k = 0; k < matrix1[0].size(); ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}
// transpose of a matrix
void transposeMatrix(const vector<vector<int>>& matrix, vector<vector<int>>& result) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            result[j][i] = matrix[i][j];
        }
    }
}


// THEOREM 1
void THEOREM1(const vector<vector<int>>& FIRSTmatrix, const vector<vector<int>>& EQUALmatrix, vector<vector<int>>& YieldsTo, const vector<string>& grammar, const vector<string>& OrderedGrammar){
    // Perform matrix multiplication: TakesPrecedence = EQUALmatrix * FIRSTmatrix
    multiplyMatrices(EQUALmatrix, FIRSTmatrix, YieldsTo);
    printMatrix(" Theorem 1: < ", OrderedGrammar, grammar, YieldsTo);
}
// THEOREM 2
void THEOREM2(const vector<vector<int>>& LASTmatrix, const vector<vector<int>>& EQUALmatrix, const vector<vector<int>>& FIRSTmatrix, vector<vector<int>>& TakesPrecedence, const vector<string>& grammar, const vector<string>& OrderedGrammar){

    // getting the transpose of the last matrix
    vector<vector<int>> LastTranspose(LASTmatrix[0].size(), vector<int>(LASTmatrix.size(), 0));
    transposeMatrix(LASTmatrix, LastTranspose);
    // getting Identity matrix + first matrix
    vector<vector<int>> IdentityPlusFirst(EQUALmatrix.size(), vector<int>(EQUALmatrix[0].size(), 0));
    for (size_t i = 0; i < EQUALmatrix.size(); ++i) {
        for (size_t j = 0; j < EQUALmatrix[0].size(); ++j) {
            if (i == j) {
                IdentityPlusFirst[i][j] = 1;
            } else {
                IdentityPlusFirst[i][j] = FIRSTmatrix[i][j];
            }
        }
    }
    // yields to = LastTranspose * EQUALmatrix * IdentityPlusFirst
    // first multiplication is EQUALmatrix * IdentityPlusFirst
    vector<vector<int>> FirstMultiplication(EQUALmatrix.size(), vector<int>(EQUALmatrix[0].size(), 0));
    multiplyMatrices(EQUALmatrix, IdentityPlusFirst, FirstMultiplication);
    // second multiplication is LastTranspose * FirstMultiplication
    multiplyMatrices(LastTranspose, FirstMultiplication, TakesPrecedence);
    printMatrix(" Theorem 2: > ", OrderedGrammar, grammar, TakesPrecedence);
}
// COMPLETE PRECEDENCE TABLE
void completeprecedenceTable(vector<vector<string>>& PrecedenceTable, 
                             const vector<vector<int>>& TakesPrecedence, 
                             const vector<vector<int>>& YieldsTo, 
                             const vector<vector<int>>& EQUALmatrix, 
                             const vector<string>& OrderedGrammar) {
    // Iterate over each cell in the PrecedenceTable
    for (size_t i = 0; i < PrecedenceTable.size(); ++i) {
        for (size_t j = 0; j < PrecedenceTable[0].size(); ++j) {
            // Then check for other precedence relations
            if (EQUALmatrix[i][j] == 1 && TakesPrecedence[i][j] == 1 && YieldsTo[i][j] == 0) {
                PrecedenceTable[i][j] = "=>";
            } else if (EQUALmatrix[i][j] == 1 && TakesPrecedence[i][j] == 0 && YieldsTo[i][j] == 1) {
                PrecedenceTable[i][j] = "=<";
            } else{
            if (TakesPrecedence[i][j] == 1) {
                PrecedenceTable[i][j] = ">";
            } else if (YieldsTo[i][j] == 1) {
                PrecedenceTable[i][j] = "<";
            } else if (EQUALmatrix[i][j] == 1) {
                PrecedenceTable[i][j] = "=";
            } else if (EQUALmatrix[i][j] == 0 && TakesPrecedence[i][j] == 0 && YieldsTo[i][j] == 0) {
                PrecedenceTable[i][j] = "0";
            } }
        }
    }

    // Print the resulting precedence table
    cout << endl;
    cout << "Complete Precedence Table" << endl;
    cout << "   ";
    // Print column headers
    for (const auto& token : OrderedGrammar) {
        cout << token << " ";
    }
    cout << endl;
    // Print table body
    for (size_t i = 0; i < OrderedGrammar.size(); ++i) {
        if (OrderedGrammar[i] == ":=" || OrderedGrammar[i] == "**") {
            cout << OrderedGrammar[i] << " ";
        }
        else {
            cout << OrderedGrammar[i] << "  ";
        }
        // Print row elements
        for (size_t j = 0; j < OrderedGrammar.size(); ++j) {
            cout << PrecedenceTable[i][j] << " ";
        }
        cout << endl;
    }
}

void printMatrix(string type, const vector<string>& OrderedGrammar, const vector<string>& grammar, const vector<vector<int>>& matrix) {
    cout<<endl;
    cout << type << "Matrix of the grammar" << endl;
    cout << "   ";
    for (const auto& token : OrderedGrammar) {
        cout << token << " ";
    }
    cout << endl;
    for (size_t i = 0; i < OrderedGrammar.size(); ++i) {
        if (OrderedGrammar[i] == ":=" || OrderedGrammar[i] == "**"){
            cout << OrderedGrammar[i] << " ";
        }
        else {
            cout << OrderedGrammar[i] << "  ";
        }
        for (size_t j = 0; j < OrderedGrammar.size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    vector<string> grammar;
    vector<string> OrderedGrammar = {"E", "a", ":=", "A", "%", "B", "#", "(", ")", "**"};
    
    readGrammar(grammar);

    // matrices for FIRST, LAST, and EQUAL
    vector<vector<int>> FIRSTmatrix(grammar.size(), vector<int>(OrderedGrammar.size(), 0));
    vector<vector<int>> LASTmatrix(grammar.size(), vector<int>(OrderedGrammar.size(), 0));
    vector<vector<int>> EQUALmatrix(grammar.size(), vector<int>(OrderedGrammar.size(), 0));

    // matrices for THEOREM 1 and THEOREM 2
    vector<vector<int>> TakesPrecedence(EQUALmatrix.size(), vector<int>(EQUALmatrix[0].size(), 0));
    vector<vector<int>> YieldsTo(EQUALmatrix.size(), vector<int>(EQUALmatrix[0].size(), 0));
    
    // getting the first matrix
    EQUAL(EQUALmatrix, grammar, OrderedGrammar);
    FIRST(FIRSTmatrix, EQUALmatrix, grammar, OrderedGrammar);
    LAST(LASTmatrix, grammar, OrderedGrammar);

    // applying theorems
    THEOREM1(FIRSTmatrix, EQUALmatrix, YieldsTo, grammar, OrderedGrammar);

    THEOREM2(LASTmatrix, EQUALmatrix, FIRSTmatrix, TakesPrecedence, grammar, OrderedGrammar);

    // COMPLETE PRECEDENCE TABLE
    vector<vector<string>> PrecedenceTable(OrderedGrammar.size(), vector<string>(OrderedGrammar.size(), ""));
    completeprecedenceTable(PrecedenceTable, TakesPrecedence, YieldsTo, EQUALmatrix, OrderedGrammar);
    return 0;
}
