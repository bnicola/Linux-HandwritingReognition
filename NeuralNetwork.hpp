#ifndef __NEURALNETWORK_HPP__
#define __NEURALNETWORK_HPP__

#include <stdint.h>
#include <QVector>
#include <QStringList>
#include <QFile>
#include "Matrix.hpp"

class NeuralNetwork
{
   public:
     

   public:
      NeuralNetwork(uint32_t num_of_inputs, uint32_t num_of_hidden, uint32_t num_of_outputs, float learning_rate, Matrix& wih_passed, Matrix& who_passed, bool take_already_learned);

      void Train(std::vector<float> inputs, std::vector<float>targets);

      void SetLearningRate(float lr);

      void SetDropRate(float dr);

      Matrix FeedForward(std::vector<float> inputs);

      std::vector<float> Ask(std::vector<float> inputs);

      uint32_t Maximum(std::vector<float> values);

      Matrix Wih();

      Matrix Who();

      //

   private:
      std::vector<std::string> split(std::string str, std::string delimiter);


   private:
      uint32_t num_of_inputs_;
      uint32_t num_of_hidden_;
      uint32_t num_of_outputs_;
      float learning_rate_;
      float drop_rate_;

      Matrix wih_;
      Matrix who_;

      Matrix deltaWho_;
      Matrix deltaWih_;

      Matrix target_matrix_;
      Matrix input_matrix_;
      Matrix hidden_;
      Matrix hidden_outputs_;
      Matrix output_;
      Matrix final_output_;

      Matrix output_errors_;

      Matrix whot_;
      Matrix hidden_error_;

      Matrix dSig_;

      Matrix intermediate1_;

      Matrix outTranspose_;

      Matrix dSig2_;

      Matrix intermediate2_;

      Matrix inputTranspose_;


};

#endif
