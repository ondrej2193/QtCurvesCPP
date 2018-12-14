#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
            QWidget(parent),
            mBackGroundColor (0,255,255),
            mShapeColor (255,255,255),
            mShape (Astroid)
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
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    switch (mShape) {
        case Astroid:
            mBackGroundColor = Qt::red;
            break;
        case Cycloid:
            mBackGroundColor = Qt::green;
            break;
        case HypoCycloid:
            mBackGroundColor = Qt::blue;
            break;
        case HuygensCycloid:
            mBackGroundColor = Qt::yellow;
            break;
        default:
           break;
    }
    painter.setBrush (mBackGroundColor);
    painter.setPen(mShapeColor);

    // drawing area
    painter.drawRect(this->rect());
    painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
    //painter.end(this);
}
