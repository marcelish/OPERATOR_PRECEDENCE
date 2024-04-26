#include <iostream>
#include <vector>

using namespace std;

void yield(vector<vector<int>> &equal, vector<vector<int>> &first, vector<vector<int>> &firstterm, vector<vector<int>> &less);
void takes(vector<vector<int>> &equal, vector<vector<int>> &last, vector<vector<int>> &lastterm, vector<vector<int>> &greater);
void transitiveClosure(vector<vector<int>>& matrix);
void transpose(vector<vector<int>> &b);
void addIdentity(vector<vector<int>> &a);
void multiply(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& result);
void printMatrix(vector<vector<int>> &a);
void printRelation(vector<vector<int>> &a, vector<vector<int>> &b, vector<vector<int>> &c, vector<string> &labels);

int main() {
    // labels
    vector<string> labels = {
        "E", "a", "=", "A", "%", "B", "#", "(", ")", "*"
    };
    // firstterm matrix 
    vector<vector<int>> firstterm = {
        {0,0,1,0,0,0,0,0,0,0}, //E
        {0,0,0,0,0,0,0,0,0,0}, //a
        {0,0,0,0,0,0,0,0,0,0}, //:=
        {0,0,0,0,1,0,1,0,0,0}, //A
        {0,0,0,0,0,0,0,0,0,0}, //%
        {0,0,0,0,0,0,0,1,0,1}, //B
        {0,0,0,0,0,0,0,0,0,0}, //#
        {0,0,0,0,0,0,0,0,0,0}, //(
        {0,0,0,0,0,0,0,0,0,0}, //)
        {0,0,0,0,0,0,0,0,0,0}, //**
    };
    cout << "Firstterm matrix" << endl;
    printMatrix(firstterm);
    
    // lastterm matrix
    vector<vector<int>> lastterm = {
        {0,0,1,0,0,0,0,0,0,0}, //E
        {0,0,0,0,0,0,0,0,0,0}, //a
        {0,0,0,0,0,0,0,0,0,0}, //:=
        {0,0,0,0,1,0,1,0,0,0}, //A
        {0,0,0,0,0,0,0,0,0,0}, //%
        {0,0,0,0,0,0,0,0,1,1}, //B
        {0,0,0,0,0,0,0,0,0,0}, //#
        {0,0,0,0,0,0,0,0,0,0}, //(
        {0,0,0,0,0,0,0,0,0,0}, //)
        {0,0,0,0,0,0,0,0,0,0}, //**
    };
    cout << "Lastterm matrix" << endl;
    printMatrix(lastterm);

    // first matrix
    vector<vector<int>> first = {
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
    transitiveClosure(first);
    addIdentity(first); // this is now first*
    cout << "First* matrix" << endl;
    printMatrix(first);
    // last matrix
    vector<vector<int>> last = {
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
    transitiveClosure(last);
    addIdentity(last); // this is now last*
    cout << "Last* matrix" << endl;
    printMatrix(last);
    // equal matrix
    vector<vector<int>> equal = {
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
    cout << "Equal matrix" << endl;
    printMatrix(equal);
    // finding "<" relation
    vector<vector<int>> less;
    yield(equal, first, firstterm, less);
    // finding ">" relation
    vector<vector<int>> greater;
    takes(equal, last, lastterm, greater);
    // print relation
    printRelation(less, greater, equal, labels);
    return 0;
}
// yield function
void yield(vector<vector<int>> &equal, vector<vector<int>> &first, vector<vector<int>> &firstterm, vector<vector<int>> &less){
    vector<vector<int>> result;
    // multiply equal and first
    multiply(equal, first, result);
    cout << "Equal * First" << endl;
    printMatrix(result);
    // multiply less * firstterm
    multiply(result, firstterm, less);
    // printing less
    cout << "<" << endl;
    printMatrix(less);
}
// takes precedence function
void takes(vector<vector<int>> &equal, vector<vector<int>> &last, vector<vector<int>> &lastterm, vector<vector<int>> &greater){
    vector<vector<int>> takes;
    // multiply last* and lastterm
    multiply(last, lastterm, takes);
    // get the transpose of greater
    transpose(takes);
    // multiply greater * equal
    multiply(takes, equal, greater);
    // printing greater
    cout << ">" << endl;
    printMatrix(greater);
}
// transitive closure function
void transitiveClosure(vector<vector<int>>& matrix) {
    for (size_t k = 0; k < matrix.size(); ++k) {
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix.size(); ++j) {
                if (matrix[i][k] == 1 && matrix[k][j] == 1) {
                    matrix[i][j] = 1;
                }}}}}
// transpose function
void transpose(vector<vector<int>> &b){
    if (b.size() == 0)
        return;
    vector<vector<int> > trans_vec(b[0].size(), vector<int>());
    for (int i = 0; i < b.size(); i++){
        for (int j = 0; j < b[i].size(); j++){
            trans_vec[j].push_back(b[i][j]);
        }}
    b = trans_vec;}
// adding the identity matrix to the matrix
void addIdentity(vector<vector<int>> &a){
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[0].size(); ++j) {
            if (i == j) {
                a[i][j] = 1;
            } else {
                a[i][j] = a[i][j];
            }
        }
    } }
// multiply matrices function
void multiply(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& result) {
    // Check for valid dimensions
    if (matrix1[0].size() != matrix2.size()) {
        cout << "Invalid matrix dimensions for multiplication!" << endl;
        return;
    }
    
    // Resize the result matrix to match the dimensions of the product
    result.assign(matrix1.size(), vector<int>(matrix2[0].size(), 0));

    // Perform matrix multiplication
    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix2[0].size(); ++j) {
            for (size_t k = 0; k < matrix1[0].size(); ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}
// print matrix function 
void printMatrix(vector<vector<int>> &a){
    cout << endl;
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a[0].size(); j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// print relation function (<, >, =)
void printRelation(vector<vector<int>> &a, vector<vector<int>> &b, vector<vector<int>> &c, vector<string> &labels) {
    cout << "Operator Precedence Matrix" << endl;
    cout << "  ";
    
    for (const auto& label : labels) {
        cout << label << " ";
    }
    cout << endl;
    
    for (int i = 0; i < labels.size(); ++i) {
        cout << labels[i] << " ";
        for (int j = 0; j < labels.size(); ++j) {
            if (a[i][j] == 1) {
                cout << "< ";
            } else if (b[i][j] == 1) {
                cout << "> ";
            } else if (c[i][j] == 1) {
                cout << "= ";
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}