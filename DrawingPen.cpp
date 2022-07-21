#include "DrawingPen.hpp"
#include <QPainter>

DrawingPen::DrawingPen(DrawingBoardScene& scene)
   : scene_(scene)
{
   setPen(QPen(Qt::blue));
   setBrush(QBrush(Qt::black));

   setFlags(QGraphicsItem::ItemIsSelectable);
   setZValue(1);

   scene.addItem(this);
   update();
}

DrawingPen::~DrawingPen()
{
}


void DrawingPen::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   // Draw ourselves in our normal colours
   painter->setPen(pen());
   painter->setBrush(brush());
   painter->drawEllipse(-7, -7, 14, 14);
   painter->setPen(QPen(Qt::blue));
   
}


void DrawingPen::SetPosition(const double xPosition, const double yPosition)
{
   setPos(xPosition, yPosition);
}


void DrawingPen::SetPenWidth(quint32 penWidth)
{
   penWidth_ = penWidth;
}
