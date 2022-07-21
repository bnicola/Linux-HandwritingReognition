#include "DrawingBoardScene.hpp"

DrawingBoardScene::DrawingBoardScene()
      : mousePressed_(false)
{
}


DrawingBoardScene::~DrawingBoardScene()
{
}


void DrawingBoardScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
   mousePressed_ = true;
}


void DrawingBoardScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
   if (mousePressed_ == true)
   {
      qreal  pointX = event->scenePos().x();
      qreal  pointY = event->scenePos().y();
      QPoint outPoint(pointX, pointY);
      emit   mouseClick(outPoint);
   }
}


void DrawingBoardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
   mousePressed_ = false;
   emit FinishedDrawing();
}
