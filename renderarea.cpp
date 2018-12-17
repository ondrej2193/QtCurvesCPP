#include "renderarea.h"
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) :
            QWidget(parent),
            mBackGroundColor (0,255,255),
            mShapeColor (0,0,0),
            mShape (Astroid)
{
        on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize (100,100);
}

QSize RenderArea::sizeHint() const
{
    return QSize (400,100);
}

int RenderArea::on_shape_changed ()
{
    switch (mShape) {
        case Astroid:
            mScale = 40;
            mIntervalLength = 2* M_PI;
            mStepCount = 512;
        break;
        case Cycloid:
            mScale = 4;
            mIntervalLength = 6* M_PI;
            mStepCount = 128;
        break;
        case HypoCycloid:
            mScale = 15;
            mIntervalLength = 2* M_PI;
            mStepCount = 256;
        break;
        case HuygensCycloid:
            mScale = 4;
            mIntervalLength = 2* M_PI;
            mStepCount = 256;
        break;
        case Line:
            mScale = 50;
            mIntervalLength = 1;
            mStepCount = 128;
        break;
        default:
           break;
    }
    return 100;
}

QPointF RenderArea::compute  (float t)
{
    switch (mShape) {
        case Astroid:
            return compute_astroid (t);
            break;
        case Cycloid:
            return compute_cycloid (t);
            break;
        case HypoCycloid:
            return compute_hypo (t);
            break;
        case HuygensCycloid:
            return compute_huygens (t);
            break;
        case Line:
            return compute_line (t);
            break;
        default:
            return QPointF (0,0);
           break;
    }
}

QPointF RenderArea::compute_astroid (float t)
{
    float cos_t = cos (t);
    float sin_t = sin (t);
    float x = 2 * cos_t * cos_t * cos_t; // pow (cos_t, 3)
    float y = 2 * sin_t * sin_t * sin_t; // pow (sin_t, 3)
    return QPointF (x,y);

}

QPointF RenderArea::compute_cycloid (float t)
{
    float x =  1.5 * (1 - cos (t)); // X
    float y =  1.5 * (t - sin (t));  // Y

    return QPointF (x,y);
}

QPointF RenderArea::compute_hypo (float t)
{
    float x =  1.5 * (2 * cos (t) + cos (2 * t)); // X
    float y =  1.5 * (2 * sin (t) - sin (2 * t));  // Y

    return QPointF (x,y);
}

QPointF RenderArea::compute_huygens (float t)
{

//   return QPointF (
           float x =  4 * (3 * cos (t) - cos (3 * t)); // X
           float y =  4 * (3 * sin (t) - sin (3 * t));  // Y
//   );
     return QPointF (x,y);
}

QPointF RenderArea::compute_line (float t)
{
  return QPointF (1 - t, 1 - t);
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
    painter.drawRect(this->rect());   // draw rectangle
    QPoint center = this->rect().center();

    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());



    float step = mIntervalLength / mStepCount;
    for (float t = 0; t<mIntervalLength; t += step){
        QPointF point  = compute (t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());

//        painter.drawPoint(pixel);
        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }


    //painter.end(this);
}
