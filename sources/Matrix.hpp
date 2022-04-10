#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
namespace zich {
    class Matrix {
    private:
        vector<double> data;
        int row;
        int col;


    public:
         Matrix( vector<double> const & newData, const int newRow, const int newCol) ;

        double multiplicate_row_with_col(const Matrix &otherMat, const int row_to_mult, const int col_to_mult);

        double sum_of_matrix() const;

        

        Matrix operator+(const Matrix &otherMat);

        Matrix &operator++();

        Matrix operator++(const int flag);

        Matrix &operator+=(const Matrix &otherMat);

        Matrix operator-(const Matrix &otherMat);

        Matrix &operator--();

        Matrix operator--(const int flag);

        Matrix &operator-=(const Matrix &otherMat);

        Matrix operator*(const Matrix &otherMat);

        Matrix operator*(const double scaler);

        Matrix &operator*=(const Matrix &otherMat);

        Matrix &operator*=(const double scaler);

        bool operator>(const Matrix &otherMat);

        bool operator<(const Matrix &otherMat);

        bool operator==(const Matrix &otherMat);

        bool operator!=(const Matrix &otherMat);


        bool operator>=(const Matrix &otherMat);

        bool operator<=(const Matrix &otherMat);

        friend ostream &operator<<(ostream &COUT, const Matrix &scaler);

        friend Matrix operator*(const double scaler, Matrix &otherMat);

        friend Matrix operator-(Matrix &A);

        friend bool operator==(const Matrix &A , const Matrix &B); 

        friend Matrix operator*(const Matrix &matrix1,const Matrix &matrix2);
        Matrix operator-(const double);
        Matrix operator-(const int);
        Matrix operator+(const double);
        Matrix operator+(const int);
       
    };

};