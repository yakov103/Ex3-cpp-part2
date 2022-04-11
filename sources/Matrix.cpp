#include "Matrix.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>

namespace zich {

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

    Matrix &Matrix::operator++() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] += 1;
            }
        }
        return *this;
    }

    Matrix Matrix::operator++(const int flag) {
        Matrix copy = *this;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] += 1;
            }
        }
        return copy;
    }

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

    Matrix &Matrix::operator--() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] -= 1;
            }
        }
        return *this;
    }

    Matrix Matrix::operator--(const int flag) {
        Matrix copy = *this;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[(unsigned int)(i * col + j)] -= 1;
            }
        }
        return copy;
    }

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

    double Matrix::multiplicate_row_with_col(const Matrix &otherMat, const int row_to_mult, const int col_to_mult) {
        double result = 0;
        for (int i = 0; i < this->col; i++) {
            result += this->data[(unsigned int)(this->col * row_to_mult + i)] * otherMat.data[(unsigned int)(otherMat.col * i + col_to_mult)];
        }
        return result;
    }

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

    Matrix Matrix::operator*(const double scaler) {
        Matrix newMatrix = *this;
        for (unsigned int i = 0; i < row; i++) {
            for (unsigned int j = 0; j < col; j++) {
                newMatrix.data[(unsigned int)(col) * i + j] *= scaler;
            }
        }
        return newMatrix;
    }

    Matrix &Matrix::operator*=(const Matrix &otherMat) {
        *this = (*this * otherMat);
        return *this;
    }

    Matrix &Matrix::operator*=(const double scaler) {
        *this = (*this * scaler);
        return *this;
    }

    double Matrix::sum_of_matrix() const {
        double result = 0;
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                result += data[(unsigned int)(i * (this->col) + j)];
            }
        }
        return result;
    }

    bool Matrix::operator>(const Matrix &otherMat) {
        if (this->col != otherMat.col || this->row != otherMat.row){
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return (*this).sum_of_matrix() > otherMat.sum_of_matrix();
    }

    bool Matrix::operator<(const Matrix &otherMat) {
        if (this->col != otherMat.col || this->row != otherMat.row){
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return (*this).sum_of_matrix() < otherMat.sum_of_matrix();
    }

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

    bool Matrix::operator!=(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return !(((*this) == otherMat));
    }


    bool Matrix::operator>=(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return ((*this) > otherMat) || ((*this) == otherMat);
    }

    bool Matrix::operator<=(const Matrix &otherMat) {
        if (this->row != otherMat.row || this->col != otherMat.col) {
            throw runtime_error("The matrix must been in the same size ! ");
        }
        return ((*this) < otherMat) || ((*this) == otherMat);
    }

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

    istream & operator >> (std::istream & is, Matrix & self){
        string element;
        string matend;
        int col = -2;
        int row = 0;
        vector<double> data;
        while(!is.eof()){
            is >> element;
            matend+=" "+element;
        }

        row = (int)count(matend.begin(), matend.end(), '[');

        for(unsigned long i=0; i < matend.size(); i++){
            if(matend[i] == ' '){
                col++;
            }
            if(matend[i] == ']'){
                break;
            }
        }

        // matrix_input_exeption(&matend,row,col);

        int sum_spaces = row*(col+2);
        int sum_psiks = row-1;
        if(row != (int)count(matend.begin(), matend.end(), ']')){
            throw std::out_of_range{"not in format"};
        }
        int sum_spaces_between = 0;
        for(unsigned long i=0; i < matend.size(); i++){
            if(matend[i] == ' '){
                sum_spaces--;
                sum_spaces_between++;
            }
            if(matend[i] == ','){
                sum_psiks--;
            }
            if(i != matend.size()-1 && matend[i] == ']' && matend[i+1] != ','){
                throw std::out_of_range{"not in format"};
            }
            if(matend[i] == ']'){
                if(sum_spaces_between != (col+2)){
                    throw std::out_of_range{"not in format"};
                }
                sum_spaces_between = 0;
            }
        }
        if(sum_spaces != 0 || sum_psiks !=0){
            throw std::out_of_range{"not in format"};
        }

        replace(matend.begin(),matend.end(),'[', ' ');
        replace(matend.begin(),matend.end(),']', ' ');
        replace(matend.begin(),matend.end(),',', ' ');

        string num_in_matrix;
        stringstream stream_matrix(matend);
        while (getline(stream_matrix, num_in_matrix,' ')) {
            if( num_in_matrix != "\0"){
                try{
                    double num_double =stod(num_in_matrix);
                    data.push_back(num_double);
                }
                catch (exception& ex) {
                    throw std::out_of_range{"not number"};
                }
            }
        }
        self.col = col;
        self.row = row;
        self.data = data;
        return is;





//        //string matrix_str;
//        string token ;
//        int newCol = 0 ;
//        int newRow = 0 ;
//        vector <double> newData;
//
//
//        //https://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
//        string matrix_str (std::istreambuf_iterator<char>(is),{});
////        while (!is.eof()){
////            is >> token ;
////            matrix_str +=" "+token;
////        }
//
//
//        newRow = (int)count(matrix_str.begin(), matrix_str.end(), '[');
//        int rightBraces = 0;
//        int leftBraces = 0 ;
//        for ( unsigned int j  = 0 ; j < matrix_str.size() ; j ++){
//            if (matrix_str[j] == '['){
//                leftBraces++;
//            }
//            if (matrix_str[j] == ']'){
//                rightBraces++;
//            }
//
//        }
//
//        if (leftBraces != rightBraces){
//            string error_id = "bad input from user "+ std::to_string(newRow)+" and the left is " + to_string((int)count(matrix_str.begin(), matrix_str.end(), ']'));
//
//            throw runtime_error(error_id + matrix_str);
//        }
//        unsigned int i = 0;
//        int cnt = 0  ;
//        for ( i = 0; i < matrix_str.size(); i++){
//            if (matrix_str[i] == ' '){
//                cnt++;
//            }
//            if (matrix_str[i] == ']'){
//                break;
//            }
//        }
//
//        int space_counter_all = newRow*(newCol+2);
//        int space_counter_in =  0;
//        int deviders_counter = newRow-1;
//
//        for ( i = 0 ; i < matrix_str.size() ; i++){
//            if (matrix_str[i] == ' '){
//                space_counter_all--;
//                space_counter_in++;
//            }
//            if (matrix_str[i] == ','){
//                deviders_counter--;
//            }
////            if (i != matrix_str.size() && matrix_str[i] == ']' && matrix_str[i+1] == ','){
////                throw runtime_error("invalid input "+ matrix_str + to_string(i));
////            }
//            if (matrix_str[i] == ']'){
////                if (space_counter_in != newCol+2){
////                    throw runtime_error("invalid input aaaa");
////                }
//                 // because its a new row
//                    space_counter_in = 0 ;
//
//            }
//
//
//        }
//        if (deviders_counter != 0 ){
//            throw runtime_error ("invalid input ");
//
//        }
//
//        replace(matrix_str.begin(),matrix_str.end(),',',' ');
//        replace(matrix_str.begin(),matrix_str.end(),'[',' ');
//        replace(matrix_str.begin(),matrix_str.end(),']',' ');
////        string token2 ;
////        stringstream stream_matrix_str(matrix_str);
////        stringstream sstest;
////        sstest << matrix_str;
////        double found ;
////        while (!sstest.eof()) {
////
////            /* extracting word by word from stream */
////            sstest >> token2;
////
////            /* Checking the given word is integer or not */
////            if (stringstream(token2) >> found){
////                newData.push_back(found);
////            }else {
////                if (token2!= " ") {
////                    throw runtime_error("opsi" + matrix_str);
////                }
////            }
////
////            /* To save from space at the end of string */
////            token2 = "";
////        }
//        string num_in_matrix;
//        stringstream stream_matrix(matrix_str);
//        while (getline(stream_matrix, num_in_matrix,' ')) {
//            if( num_in_matrix != "\0"){
//                try{
//                    double num_double =stod(num_in_matrix);
//                    newData.push_back(num_double);
//                }
//                catch (exception& ex) {
//                    throw std::out_of_range{"not number"+ matrix_str};
//                }
//            }
//        }
//
//        self.data =newData;
//        self.col= newCol;
//        self.row =newRow;
//
//    return is;
    }

    Matrix operator*(const Matrix &matrix1,const Matrix &matrix2){
        return matrix1;
    }

    
}