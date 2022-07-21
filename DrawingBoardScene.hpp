#ifndef __DrawingBoardScene_HPP__
#define __DrawingBoardScene_HPP__

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPoint>
#include <QWheelEvent>

class DrawingBoardScene : public QGraphicsScene
{
   Q_OBJECT

   public:
      DrawingBoardScene();
      ~DrawingBoardScene();

   protected:
      void mousePressEvent(QGraphicsSceneMouseEvent* e);
      void mouseMoveEvent(QGraphicsSceneMouseEvent* e);
      void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);


   signals:
      void mouseClick(QPointF point);
      void FinishedDrawing();

   private:
      bool mousePressed_;

};

#endif // DrawingBoardScene_HPP__
