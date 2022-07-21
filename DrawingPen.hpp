#ifndef DRAWING_PEN_HPP
#define DRAWING_PEN_HPP

#include <QGraphicsItem>
#include <QPainter>

#include "DrawingBoardScene.hpp"

class DrawingPen : public QObject, public QGraphicsPathItem
{
   Q_OBJECT

   public:
      DrawingPen(DrawingBoardScene& scene);
      ~DrawingPen();

      void SetPosition(const double xPosition, const double yPosition);

      void SetPenWidth(quint32 penWidth);

   protected:
      virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

   private:
      DrawingBoardScene& scene_;

      quint32 penWidth_;

};

#endif
