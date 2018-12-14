#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
            QWidget(parent),
            mBackGroundColor (0,255,255),
            mShapeColor (255,255,255)
{

}

QSize RenderArea::minimumSizeHint() const
{
    return QSize (100,100);
}

QSize RenderArea::sizeHint() const
{
    return QSize (400,100);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setBrush (mBackGroundColor);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(mShapeColor);
    // drawing area
    painter.drawRect(this->rect());
    painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
}
