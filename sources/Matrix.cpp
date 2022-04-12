#include "Matrix.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>

namespace zich {


//constractor 
    Matrix::Matrix( vector<double> const & newData, const int newRow, const int newCol) {
        if (newRow <= 0 || newCol <= 0) {
            throw runtime_error("The size must be positive");
        }
        if (newRow * newCol != newData.size()){
            throw runtime_error("size should be in the amount of the value");
        }
        if (newData.empty()){
            throw runtime_error("cannot work with empty vector");
        }

        this->data = newData;
        this->row = newRow;
        col = newCol;
    }



//sum of 2 matrixes operator 
    Matrix Matrix::operator+(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrices should be the same size");
        }

        unsigned int length = (unsigned int)(row * col);
        vector<double> newData;
        newData.resize(length);
        for (unsigned int i = 0; i < length; i++) {
            newData[i] = this->data[i] + otherMat.data[i];

        }
        return Matrix(newData, row, col);
    }


//add 1 to each number in the matrix by reference  . 
    Matrix &Matrix::operator++() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] += 1;
            }
        }
        return *this;
    }


//add 1 to each number in the matrix by value
    Matrix Matrix::operator++(const int flag) {
        Matrix copy = *this;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] += 1;
            }
        }
        return copy;
    }

// sum of 2 matrix - checking if they are in the same size => then just sum the data inside 
    Matrix &Matrix::operator+=(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrices should be the same size");
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] += otherMat.data[(unsigned int)(i * col + j)];
            }
        }
        return *this;
    }

//minus operator 
    Matrix Matrix::operator-(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrices should be the same size");
        }
        unsigned int length = (unsigned int)(row * col);
        vector<double> newData;
        newData.resize(length);
        for (unsigned int i = 0; i < length; i++) {
            newData[i] = this->data[i] - otherMat.data[i];

        }
        return Matrix(newData, row, col);
    }


// minus 1 from every number in the matrix  by refernce 
    Matrix &Matrix::operator--() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] -= 1;
            }
        }
        return *this;
    }


// minus 1 from every number in the matrix by value 
    Matrix Matrix::operator--(const int flag) {
        Matrix copy = *this;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] -= 1;
            }
        }
        return copy;
    }


// minus operator - works only if the same size => and its right matrix minus from the left 
    Matrix &Matrix::operator-=(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrices should be the same size");
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] -= otherMat.data[(unsigned int)(i * col + j)];
            }
        }
        return *this;
    }


// inner product space multiplication 
    double Matrix::multiplicate_row_with_col(const Matrix &otherMat, const int row_to_mult, const int col_to_mult) {
        double result = 0;
        for (int i = 0; i < this->col; i++) {
            result += this->data[(unsigned int)(this->col * row_to_mult + i)] * otherMat.data[(unsigned int)(otherMat.col * i + col_to_mult)];
        }
        return result;
    }


// multiplication of 2 matrix. only if the size follow the rules of : col of right == row of left. 
    Matrix Matrix::operator*(const Matrix &otherMat) {
        if (this->col != otherMat.row) {
            throw runtime_error("The sizes of the matrices do not match");
        }
        vector<double> n;
        n.resize((unsigned int )(row*otherMat.col));
        Matrix newMatrix(n, row, otherMat.col);
        for (int i = 0; i < newMatrix.row; i++) {
            for (int j = 0; j < newMatrix.col; j++) {
                newMatrix.data[(unsigned int)(i * newMatrix.col + j)] = multiplicate_row_with_col(otherMat, i, j);
            }
        }
        return newMatrix;
    }

    // multiplicate a matrix by scaler . 

    Matrix Matrix::operator*(const double scaler) {
        Matrix newMatrix = *this;
        for (unsigned int i = 0; i < row; i++) {
            for (unsigned int j = 0; j < col; j++) {
                newMatrix.data[(unsigned int)(col) * i + j] *= scaler;
            }
        }
        return newMatrix;
    }

    // multiplicate self with other.  

    Matrix &Matrix::operator*=(const Matrix &otherMat) {
        *this = (*this * otherMat);
        return *this;
    }
// same as above just with reference 
    Matrix &Matrix::operator*=(const double scaler) {
        *this = (*this * scaler);
        return *this;
    }


// checking the sum of values in the matrix for the comperators operators .
    double Matrix::sum_of_matrix() const {
        double result = 0;
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                result += data[(unsigned int)(i * (this->col) + j)];
            }
        }
        return result;
    }

// check first sizes => check who has bigger sum 
    bool Matrix::operator>(const Matrix &otherMat) {
        if (this->col != otherMat.col || this->row != otherMat.row){
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return (*this).sum_of_matrix() > otherMat.sum_of_matrix();
    }
// check first sizes => check who has bigger sum 
    bool Matrix::operator<(const Matrix &otherMat) {
        if (this->col != otherMat.col || this->row != otherMat.row){
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return (*this).sum_of_matrix() < otherMat.sum_of_matrix();
    }
// check first sizes => then check the values -> if not the same -> false . else true 
    bool Matrix::operator==(const Matrix &otherMat) {

        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrix must been in the same size ! ");
        }
        unsigned int size = (unsigned int)(row * col);
        for (unsigned int i = 0; i < size; i++) {
            if (this->data[i] != otherMat.data[i]) {
                return false;
            }
        }
        return true;

    }


// just using invert of == operator . 
    bool Matrix::operator!=(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return !(((*this) == otherMat));
    }


// using == and > , if 1 us true then it will return if true . 
    bool Matrix::operator>=(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return ((*this) > otherMat) || ((*this) == otherMat);
    }

// same as above 
    bool Matrix::operator<=(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return ((*this) < otherMat) || ((*this) == otherMat);
    }


// ostream for cout . 
//example of printing : 
//[1 1 2]
//[2 4 6]
//[6 7 7]
//
//
    ostream &operator<<(ostream &COUT, const Matrix &scaler) {
        for (int i = 0; i < scaler.row; i++) {
            COUT << "[";
            for (int j = 0; j < scaler.col; j++) {
                if (j < scaler.col-1) {
                    COUT << scaler.data[(unsigned int) (scaler.col * i + j)] << " ";
                }
                else {
                    COUT << scaler.data[(unsigned int) (scaler.col * i + j)] ;

                }
            }

            if ( i < scaler.row-1){
                COUT << "]"<< endl ;
            }
            else {
                COUT<< "]";
            }
        }
        return COUT;
    }
    
    Matrix operator*(const double scaler, Matrix &otherMat) {
        return otherMat * scaler;
    }

    Matrix operator-(Matrix &A) {
        return A *= -1;
    }

    Matrix operator+(Matrix &A){
        return A ;
    }

         Matrix Matrix::operator-(const double number)
    {
        return *this;
    };
    Matrix Matrix::operator-(const int number)
    {
        return *this;
    };
    Matrix Matrix::operator+(const double number)
    {
        return *this;
    };
    Matrix Matrix::operator+(const int number)
    {
        return *this;
    };

    bool operator==(const Matrix &A , const Matrix &B){
         if (A.row != B.row || A.col != B.col) {
            return false;
        }
        unsigned int size = (unsigned int)(A.row * A.col);
        for (unsigned int i = 0; i < size; i++) {
            if (A.data[i] != B.data[i]) {
                return false;
            }
        }
        return true;
      
    }

        vector<string> splitString(const string &str, const char c)
    {
        vector<string> res;
        res.resize(str.size()); // max size of res;

        unsigned int realSize = 0; // the real size of res;
        for (unsigned int i = 0; i < str.size(); i++)
        {
            if (str.at(i) == c)
            {
                ++realSize;
            }
            else
            {
                res[realSize] += str.at(i);
            }
        }

        ++realSize;
        res.resize(realSize);
        return res;
    }
   
// 
//devide string to array , devided by a char 
//
//
    vector<string> deviderStr(string str, char splitChar){
    vector<string> temp;
    for (unsigned int i = 0; i < str.size(); i++) {
        string token;
        while (str[i] != splitChar && i < str.size())  
        {
            token += str[i++];                          
        }
        temp.push_back(token);                         
    }
    return temp;
}

//we getting a istream for example = "[1 1 1 1], [1 1 1 1], [1 1 1 1]\n"
//
//
//
//
// "[1 1 1 1], | this is just a spepator for testing 
//  [1 1 1 1], |
//  [1 1 1 1]\n"
//
//

    istream & operator >> (std::istream & inputSteam, Matrix & mat){
        vector<double> newData;
        string strInput = " "; // all lines have space in the start also the first one
        char check=0;
        while (check != '\n')  //convert inputSteam to string
        {
            check = inputSteam.get();
            strInput += check;
        }

        vector<string> rows = deviderStr(strInput, ',');   //splite to lines
        for (unsigned int i = 0; i < rows.size(); i++)
        {
            rows[i] = rows[i].substr(2, rows[i].size() - 3); // remove the [ ] from the string
        }
        rows[rows.size() - 1] = rows[rows.size() - 1].substr(0, rows[rows.size() - 1].size() - 1); // remove the last ]
        vector<string> firstRow = deviderStr(rows[0], ' ');                            // save the numbers of the first row
        unsigned int newCol = firstRow.size(); // save the newCol number
        for (unsigned int i = 0; i < rows.size(); i++){
            vector<string> rowArr = deviderStr(rows[i], ' ');
            if (rowArr.size() != newCol)
            {
                throw runtime_error("bad input - the size of row or colom not match ");
            }
            for (unsigned int j = 0; j < rowArr.size(); j++)
            { // push the numbers to the array 
                try
                {
                    newData.push_back(stod(rowArr[j])); // convert nubmer to double and push to arr 
                }
                catch (exception e)
                {
                    throw runtime_error("bad input - cannot insert a number ");
                }
            }
        }
        mat.row = rows.size();
        mat.col = (int)newCol;
        mat.data = newData;

        return inputSteam;
    }


    
}