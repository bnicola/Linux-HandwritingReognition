#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <stdint.h>
#include <stdio.h>
#include <vector>

class Matrix
{

   public:
      Matrix(uint32_t rows = 1, uint32_t cols = 1, float initialValues = 0.0);
      ~Matrix();

      uint32_t Rows();

      uint32_t Cols();

      void SetDimensions(uint32_t rows, uint32_t cols)
      {
         rows_ = rows;
         cols_ = cols;
         values_.resize(rows_ * cols);
      }

      void SetValue(uint32_t row, uint32_t col, double val)
      {
         if ((rows_ >= row) && (cols_ >= col))
         {
            int index = (row * cols_ + col);
            values_[index] = val;
         }
      }

      double Value(uint32_t row, uint32_t col)
      {
         double curVal;

         if ((rows_ >= row) && (cols_ >= col))
         {
            int index = (row * cols_ + col);
            curVal = values_[index];
         }

         return curVal;
      }

      std::vector<float> ToArray();

      Matrix FromArray(std::vector<float> arrayValues);

      void Randomize();

      Matrix Transpose();

      Matrix Scale(float num);

      Matrix Scale(Matrix m);

      void SetDropRate(float dr);

      Matrix Sigmoid(bool dropout = false);

      Matrix DiSigmoid(Matrix& x);

      void Print();

      Matrix operator+(Matrix& b)
      {
         Matrix matrix(b.Rows(), b.Cols());

         if ((this->rows_ == b.rows_) && (this->cols_ == b.cols_))
         {
            for (uint32_t i = 0; i < rows_; i++)
            {
               for (uint32_t j = 0; j < cols_; j++)
               {
                  matrix.SetValue(i, j, Value(i, j) + b.Value(i, j));
                  //matrix.values_[i][j] = this->values_[i][j] + b.values_[i][j];
               }
            }
         }
         else
         {
            printf("Unmatched rows and columns for operation");
         }

         return matrix;
      }

      Matrix operator-(Matrix& b)
      {
         Matrix matrix(b.Rows(), b.Cols());

         if ((this->rows_ == b.rows_) && (this->cols_ == b.cols_))
         {
            for (uint32_t i = 0; i < rows_; i++)
            {
               for (uint32_t j = 0; j < cols_; j++)
               {
                  matrix.SetValue(i, j, Value(i, j) - b.Value(i, j));
               }
            }
         }
         else
         {
            printf("Unmatched rows and columns for operation");
         }

         return matrix;
      }

      Matrix operator*(Matrix& b)
      {
         Matrix matrix(this->Rows(), b.Cols(), 0);        // the

         if (this->cols_ == b.rows_)
         {
            for (uint32_t i = 0; i < this->Rows(); i++)
            {
               for (uint32_t j = 0; j < b.Cols(); j++)
               {
                  for (uint32_t l = 0; l < this->cols_; l++)
                  {
                     matrix.SetValue(i, j, matrix.Value(i, j) + Value(i, l) * b.Value(l, j));
                  }
               }
            }
         }
         else
         {
            printf("Unmatched rows and columns for operation");
         }

         return matrix;
      }

   private:
      uint32_t rows_;
      uint32_t cols_;
      std::vector<float> values_;
      float drop_rate_;
};

#endif
