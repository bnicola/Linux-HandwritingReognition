#include "Matrix.hpp"
#include <stdio.h>
#include <time.h>
#include <random>
#include <math.h>

Matrix::Matrix(uint32_t rows, uint32_t cols, float initialValues)
      : rows_(rows),
        cols_(cols),
        drop_rate_(0.2)
{
   values_.resize(rows * cols);
   for (int i = 0; i < (rows * cols); i++)
   {
      values_[i] = initialValues;
   }
}


Matrix::~Matrix()
{
}


uint32_t Matrix::Rows()
{
   return rows_;
}


uint32_t Matrix::Cols()
{
   return cols_;
}


std::vector<float> Matrix::ToArray()
{
   std::vector<float> array;
   for (uint32_t i = 0; i < rows_ * cols_; i++)
   {
      array.push_back(values_[i]);
   }
   return array;
}


Matrix Matrix::FromArray(std::vector<float> arrayValues)
{
   rows_ = arrayValues.size();
   cols_ = 1;
   values_.resize(0);
   for (int i = 0; i < arrayValues.size(); i++)
   {
      values_.push_back(arrayValues.at(i));
   }

   return *this;
}


void Matrix::Randomize()
{
   for (uint32_t i = 0; i < rows_; i++)
   {
      for (uint32_t j = 0; j < cols_; j++)
      {
         float sign = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) > 0.5) ? -1 : 1;
         values_[i * j + j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * sign;
      }
   }
}


Matrix Matrix::Transpose()
{
   Matrix tr(this->Cols(), this->Rows());

   for (uint32_t i = 0; i < rows_; i++)
   {
      for (uint32_t j = 0; j < cols_; j++)
      {
         tr.SetValue(j, i, this->Value(i, j));
      }
   }

   return tr;
}


Matrix Matrix::Scale(float num)
{
   Matrix tr(this->Rows(), this->Cols());

   for (uint32_t i = 0; i < rows_; i++)
   {
      for (uint32_t j = 0; j < cols_; j++)
      {
         tr.SetValue(i, j, Value(i, j) * num);
      }
   }

   return tr;
}


Matrix Matrix::Scale(Matrix m)
{
   Matrix tr(this->Rows(), this->Cols());

   for (uint32_t i = 0; i < rows_; i++)
   {
      for (uint32_t j = 0; j < cols_; j++)
      {
         tr.SetValue(i, j, Value(i, j) * m.Value(i, j));
      }
   }

   return tr;
}


Matrix Matrix::Sigmoid(bool dropout)
{
   Matrix tr(this->Rows(), this->Cols());

   for (uint32_t i = 0; i < rows_; i++)
   {
      for (uint32_t j = 0; j < cols_; j++)
      {
         //
         //                             1
         // Sigmoid(x)   =    (---------------------)
         //                       1     +  e^-x
         //
         double expon = std::exp(Value(i, j) * -1) + 1;
         expon = 1 / expon;
         float sign = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) > (1 - drop_rate_)) ? 0 : 1;
         if (dropout == true)
         {
            if (sign == 1)
            {
               tr.SetValue(i, j, expon);
            }
            else
            {
               tr.SetValue(i, j, 0.00000001); // disable the neuron randomly as drop out prevents overfitting
            }
         }
         else
         {
            tr.SetValue(i, j, expon);
         }
      }
   }

   return tr;
}


Matrix Matrix::DiSigmoid(Matrix& x)
{
   Matrix tr(x.Rows(), x.Cols());

   for (uint32_t i = 0; i < x.Rows(); i++)
   {
      for (uint32_t j = 0; j < x.Cols(); j++)
      {
         tr.SetValue(i, j, x.Value(i, j) * (1 - x.Value(i, j)));
      }
   }

   return tr;
}


void Matrix::SetDropRate(float dr)
{
   drop_rate_ = dr;
}


void Matrix::Print()
{
   printf("\n");
   for (uint32_t i = 0; i < rows_; i++)
   {
      for (uint32_t j = 0; j < cols_; j++)
      {
         printf("%2.6f\t", this->Value(i, j));
      }
      printf("\n");
   }
}
