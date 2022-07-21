#ifndef __HAND_WRITEN_RECOGNITION_HPP__
#define __HAND_WRITEN_RECOGNITION_HPP__

#include "DrawingBoardScene.hpp"

#include <ui_HandwritingRecognition.h>
//#include "Matrix.hpp"
#include "NeuralNetwork.hpp"
#include "DrawingPen.hpp"
#include <vector>
#include <time.h>
#include <fstream>

class HandwritingRecognition : public QMainWindow, public Ui::HandwritingRecognition
{
   Q_OBJECT

   public:
   struct Symbol
   {
      uint32_t value;
      double   pixels[784];
   };

   public:
      struct Symbols
      {
         uint32_t index;
         QString  label;
      };

      static const uint32_t numOfPixels_       = 784;
      static const uint32_t numOfHiddenLayers_ = 200;


   public:
      HandwritingRecognition();

   public slots:
      void MouseClick(QPointF point);
      void FinishedDrawing();
      void ClearBoard();
      void WhatIsIt();
      void Train();

      void CorrectMe();
      void CreateSymbolDataFile(std::vector<float> input, std::vector<float> target);

   private:
      std::vector<std::string> split(std::string str, std::string delimiter);

      std::vector<float> SerializeImage();

      bool CheckPreviousLearning(Matrix& already_wih, Matrix& already_who);

      void ClearImage();

      void SaveWeightToFile(Matrix wih, Matrix who);

      QVector<HandwritingRecognition::Symbol> ReadTestDataFile(QString test_data_file);

      QVector<Symbol> ReadTrainingData(QString training_data_file);

      void ShiftImageX(int offsetX, int offsetY, double**  image, double** updatedImage);
      void ShiftImageY(int offsetY, double**  image, double** updatedImage);


   private:
      DrawingBoardScene drawingBoardScene_;

      NeuralNetwork* nn_;

      double** image_;
      double** updatedImage_;
      uint32_t width_;
      uint32_t height_;

      uint32_t minX_;
      uint32_t minY_;

      uint32_t maxX_;
      uint32_t maxY_;

      QList<Symbols> symbols_;

      float learning_rate_;

      bool cancelled_;

};


#endif //__HAND_WRITEN_RECOGNITION_HPP__
