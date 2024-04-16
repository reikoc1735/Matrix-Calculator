#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class Matrix{
    public:
    Matrix(int r, int c) : row(r), col(c){}

    //Assumes the file given is in the correct format
    //Matrix is a valid matrix
    Matrix(istream& input) {
        input >> row >> col;
        for(size_t r = 0; r < row; r++){
            for(size_t c = 0; c < col; c++){
                double temp;
                input >> temp;
                m[r][c] = temp;
            }
        }
    }

    double* at(int r, int c) {
        assert(0 <= c && c <= col);
        assert(0 <= r && r <= row);
        return &(m[r][c]);
    }

    void print(ostream& output) {
        output.precision(3);
        output << row << " " << col << endl;
        for(size_t r = 0; r < row; r++){
            for(size_t c = 0; c < col; c++){
                //double value = round(m[r][c] * 1000.0) / 1000.0;
                output << m[r][c] << " ";
            }
            output << endl;
        }
    }

    int get_row(){
        return row;
    }

    int get_col(){
        return col;
    }

    bool operator==(Matrix rhs) {
        if(this == &rhs){
            return false;
        }
        if(rhs.get_row() != row) {return false;}
        if(rhs.get_col() != col) {return false;}
        for(size_t r = 0; r < row; r++){
            for(size_t c = 0; c < col; c++){
                double value1 = round(*(rhs.at(r, c)) * 100.0) / 100.0;
                double value2 = round(m[r][c] * 100.0) / 100.0;
                if(value1 != value2) {return false;}
            }
        }
        return true;
    }

    bool operator!=(Matrix rhs){
        return !operator==(rhs);
    }

    private:
    int row;
    int col;
    double m[100][100];
};

Matrix matrix_multiply(Matrix rhs, Matrix lhs){
    assert(rhs.get_col() == lhs.get_row());
    int row = rhs.get_row();
    int col = lhs.get_col();
    Matrix ans(row, col);
    for(size_t r = 0; r < row; r++){
        for(size_t c = 0; c < col; c++){
            *(ans.at(r, c)) = 0;

            for (size_t k = 0; k < lhs.get_row(); k++) {
                *(ans.at(r, c)) += *(rhs.at(r, k)) * *(lhs.at(k, c));
            }
        }
    }

    return ans;
}

Matrix scalar_multiply(double s, Matrix m){
    int row = m.get_row();
    int col = m.get_col();
    Matrix ans(row, col);
    for(size_t r = 0; r < row; r++){
        for(size_t c = 0; c < col; c++){
            *(ans.at(r, c)) = *(m.at(r, c)) * s;
        }
    }
    return ans;
}

Matrix add_matrix(Matrix rhs, Matrix lhs){
    assert(rhs.get_row() == lhs.get_row());
    assert(rhs.get_col() == lhs.get_col());
    int row = rhs.get_row();
    int col = rhs.get_col();
    Matrix ans(row, col);
    for(size_t r = 0; r < row; r++){
        for(size_t c = 0; c < col; c++){
            *(ans.at(r, c)) = *(rhs.at(r, c)) + *(lhs.at(r, c));
        }
    }

    return ans;
}

Matrix power_method(Matrix m, Matrix v){
    cout << "Note up to 2 decimal precision" << endl;
    Matrix prev = matrix_multiply(m, v);
    Matrix current = matrix_multiply(m, prev);
    while(prev != current){
        Matrix temp = current;
        prev = current;
        current = matrix_multiply(m, temp);
    }

    return current;
}

int main(int argc, char *argv[]){
    cout.precision(2);
    cout << "Give Matrix file" << endl;
    string filename;
    cin >> filename;

    ifstream fin(filename);
    if (!fin.is_open()) {
    cout << "Error opening " << filename << endl;
    return 1;
    }

    Matrix matrix1(fin);

    cout << "What would you like to do?" << endl;
    cout << "Matrix Multiplication (mm), Scalar Multiplication (sm), Matrix Addition (ma)"
    << ", Perform Power Method (pp)" << endl;

    string response;
    cin >> response;

    Matrix ans(0,0);

        if(response == "mm"){
            cout << "Give another matrix file" << endl;
            string filename2;
            cin >> filename2;

            ifstream fin2(filename2);
            if (!fin2.is_open()) {
                cout << "Error opening " << filename2 << endl;
                return 1;
            }

            Matrix matrix2(fin2);

            cout << "Do you want this new matrix to be on the left or right?" << endl;
            string response2;
            cin >> response2;
            if(response2 == "left"){
                ans = ans = matrix_multiply(matrix2, matrix1);
            }
            else{
                ans = matrix_multiply(matrix1, matrix2);
            }
            
        }
        if(response == "sm"){
            cout << "Give a number" << endl;
            double response2;
            cin >> response2;
            ans = scalar_multiply(response2, matrix1);
        }
        if(response == "ma"){
            cout << "Give another matrix file" << endl;
            string filename2;
            cin >> filename2;

            ifstream fin2(filename2);
            if (!fin2.is_open()) {
                cout << "Error opening " << filename2 << endl;
                return 1;
            }

            Matrix matrix2(fin2);
            ans = add_matrix(matrix1, matrix2);
        }
        if(response == "pp"){
            cout << "Give personalization matrix file" << endl;
            string filename2;
            cin >> filename2;

            ifstream fin2(filename2);
            if (!fin2.is_open()) {
                cout << "Error opening " << filename2 << endl;
                return 1;
            }

            Matrix v(fin2);
            ans = power_method(matrix1, v);
        }
        else{
            cout << "Try Again" << endl;
            return 1;
        }

        cout << "Give output filename" << endl;
        cin >> filename;
        ofstream fout(filename);
        ans.print(fout);

}