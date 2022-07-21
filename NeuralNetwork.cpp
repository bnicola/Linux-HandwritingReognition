#include "NeuralNetwork.hpp"
#include <iostream>
#include <fstream>
#include <string>

NeuralNetwork::NeuralNetwork(uint32_t num_of_inputs, uint32_t num_of_hidden, uint32_t num_of_outputs, float learning_rate, Matrix& wih_passed, Matrix& who_passed, bool take_already_learned)
      : num_of_inputs_(num_of_inputs),
        num_of_hidden_(num_of_hidden),
        num_of_outputs_(num_of_outputs),
        learning_rate_(learning_rate),
        wih_(num_of_hidden, num_of_inputs),
        who_(num_of_outputs, num_of_hidden)
{
   if (take_already_learned == false)
   {
      wih_.Randomize();
      who_.Randomize();
   }
   else
   {
      for (uint32_t i = 0; i < wih_passed.Rows(); i++)
      {
         for (uint32_t  j = 0; j < wih_passed.Cols(); j++)
         {
            wih_.SetValue(i, j, wih_passed.Value(i, j));
         }
      }

      for (uint32_t  i = 0; i < who_passed.Rows(); i++)
      {
         for (uint32_t  j = 0; j < who_passed.Cols(); j++)
         {
            who_.SetValue(i, j, who_passed.Value(i, j));
         }
      }
   }
}


void NeuralNetwork::Train(std::vector<float> inputs, std::vector<float>targets)
{
   Matrix target_matrix;

   target_matrix = target_matrix.FromArray(targets);

   Matrix input_matrix;
   input_matrix = input_matrix.FromArray(inputs);

   //input --> Hidden
   Matrix hidden = wih_ * input_matrix;

   Matrix hidden_outputs = hidden.Sigmoid(true);

   // hidden --> Output
   Matrix output       = who_ * hidden_outputs;
   Matrix final_output = output.Sigmoid();

   //Output Error
   Matrix output_errors = target_matrix - final_output;

   // hidden error
   Matrix whot_        = who_.Transpose();
   Matrix hidden_error = whot_ * output_errors;

   // the value to update the who_ with is = lr * output_errors * final_output * (1 - final_output) * hidden_outputs_transpose
   // -----------Back propagating for who------------------------------------
   Matrix dSig          = dSig.DiSigmoid(final_output);
   Matrix intermediate1 = output_errors.Scale(dSig);
   intermediate1 = intermediate1.Scale(learning_rate_);
   Matrix outTranspose = hidden_outputs.Transpose();
   deltaWho_ = intermediate1 * outTranspose;
   who_      = who_ + deltaWho_;

   // -----------Back propagating for wih------------------------------------
   Matrix dSig2         = dSig2.DiSigmoid(hidden_outputs);
   Matrix intermediate2 = hidden_error.Scale(dSig2);
   intermediate2 = intermediate2.Scale(learning_rate_);
   Matrix inputTranspose = input_matrix.Transpose();
   deltaWih_ = intermediate2 * inputTranspose;
   wih_      = wih_ + deltaWih_;

}


void NeuralNetwork::SetLearningRate(float lr)
{
   learning_rate_ = lr;
}


void NeuralNetwork::SetDropRate(float dr)
{
   drop_rate_ = dr;
}


Matrix NeuralNetwork::FeedForward(std::vector<float> inputs)
{
   Matrix input_matrix;

   input_matrix = input_matrix.FromArray(inputs);

   //input --> Hidden
   Matrix hidden = wih_ * input_matrix;
   hidden = hidden.Sigmoid();

   // hidden --> Output
   Matrix output = who_ * hidden;
   output = output.Sigmoid();

   return output;
}


std::vector<float> NeuralNetwork::Ask(std::vector<float> inputs)
{
   std::vector<float> output;

   Matrix result = FeedForward(inputs);
   output = result.ToArray();

   return output;

}


Matrix NeuralNetwork::Wih()
{
   return wih_;
}


Matrix NeuralNetwork::Who()
{
   return who_;
}


std::vector<std::string> NeuralNetwork::split(std::string str, std::string delimiter)
{
   std::vector<std::string> matches;
   int pos = 0;
   if (str.find(delimiter) != -1)
   {
      while (str.length() > 0 && pos != -1)
      {
         pos = str.find(delimiter);
         if (pos != -1)
         {
            std::string token = str.substr(0, pos);
            matches.push_back(token);
            str = str.substr(pos + delimiter.size(), str.length());
         }
         else
         {
            matches.push_back(str);
         }
      }
   }

   return matches;
}


uint32_t NeuralNetwork::Maximum(std::vector<float> values)
{
   double   max_value = 0.0;
   uint32_t max_index = 0;

   for (uint32_t  i = 0; i < values.size(); i++)
   {
      if (values.at(i) > max_value)
      {
         max_index = i;
         max_value = values.at(i);
      }
   }
   return max_index;
}
