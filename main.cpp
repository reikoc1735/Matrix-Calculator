#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

class Matrix{
    public:
    Matrix(int r, int c) : row(r), col(c){}

    double* at(int r, int c) {
        assert(0 <= c && c <= col);
        assert(0 <= r && r <= row);
        return &(m[r][c]);
    }

    private:
    int row;
    int col;
    double m[100][100];
};

class PageRank{
    public:
    //matrix multiplication
    //matrix scalar multiplication
    //create S matrix
    //create G matrix
    //find dominant eigenvector
    private:
    
};

int main(int argc, char *argv[]){
    cout << "Hi" << endl;
}