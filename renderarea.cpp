#include "renderarea.h"
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) :
            QWidget(parent),
            mBackGroundColor (0,255,255),
            mPen (Qt::white),
            mShape (Astroid)
{
        mPen.setWidth(2);
        on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize (400,400);
}

QSize RenderArea::sizeHint() const
{
    return QSize (400,400);
}

int RenderArea::on_shape_changed ()
{
    switch (mShape) {
        case Astroid:
            mScale = 90;                // Section 3, Lecture 23
            mIntervalLength = 2* M_PI;
            mStepCount = 512;
        break;
        case Cycloid:
            mScale = 10;                // Section 3, Lecture 23
            mIntervalLength = 4* M_PI;  // Section 3, Lecture 23
            mStepCount = 128;
        break;
        case HypoCycloid:
            mScale = 40;                // Section 3, Lecture 23
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
        case Circle:
            mScale = 100;
            mIntervalLength = 2 * M_PI;
            mStepCount = 512;
        break;
        case Elipse:
            mScale = 75;
            mIntervalLength = 2 * M_PI;
            mStepCount = 256;
        break;
        case Flower1:
            mScale = 75;
            mIntervalLength = 2 * M_PI;
            mStepCount = 256;
        break;
        case Flower2:
            mScale = 75;
            mIntervalLength = 2 * M_PI;
            mStepCount = 256;
        break;
        case Starfish:
            mScale = 25;
            mIntervalLength = 6 * M_PI;
            mStepCount = 256;
        break;
        case Fancy:
            mScale = 10;
            mIntervalLength = 12 * M_PI;
            mStepCount = 512;
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
        case Circle:
            return compute_circle (t);
            break;
        case Elipse:
            return compute_elipse (t);
            break;
        case Flower1:
            return compute_flower1 (t);
            break;
        case Flower2:
            return compute_flower1 (t);
            break;
        case Starfish:
            return compute_starfish (t);
            break;
        case Fancy:
            return compute_fancy (t);
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

   return QPointF (
           4 * (3 * cos (t) - cos (3 * t)), // X
           4 * (3 * sin (t) - sin (3 * t))  // Y
   );

}

QPointF RenderArea::compute_line (float t)
{
  return QPointF (1 - t, 1 - t);
}

QPointF RenderArea::compute_circle (float t)
{
  return QPointF (cos(t), sin(t));
}

QPointF RenderArea::compute_elipse (float t)
{
  float a = 2;
  float b = 1.1;
  return QPointF (a * cos(t), b * sin(t));
}

QPointF RenderArea::compute_flower1 (float t)
{
  float a = 2;
  float b = 1.1;
  return QPointF (a * cos(t), b * sin(t));
}

QPointF RenderArea::compute_flower2 (float t)
{
  float a = 2;
  float b = 1.1;
  return QPointF (a * cos(t), b * sin(t));
}

QPointF RenderArea::compute_starfish (float t)
{
  float R = 5.0;
  float r = 3.0;
  float d = 5.0;

  float x = (R-r) * cos (t) + d * cos (t * (R-r) / r);
  float y = (R-r) * sin (t) + d * sin (t * (R-r) / r);

  //return QPointF ((R-r) * cos(t) + d * cos(t*((R-r)/r)), (R-r) * sin(t) + d * sin(t*((R-r)/r)));

  return QPointF (x, y);
}

QPointF RenderArea::compute_fancy (float t)
{
  return QPointF (11.0f * cos(t) - 6.0f * cos((11.0f/6.0f)*t), 11.0f * sin(t) - 6.0f * sin((11.0f/6.0f)*t));
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush (mBackGroundColor);
    painter.setPen(mPen);

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
// last line
    QPointF point  = compute (mIntervalLength);
    QPoint pixel;
    pixel.setX(point.x() * mScale + center.x());
    pixel.setY(point.y() * mScale + center.y());
    painter.drawLine(pixel, prevPixel);
}
