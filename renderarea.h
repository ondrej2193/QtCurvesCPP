#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {Astroid, Cycloid, HuygensCycloid, HypoCycloid, Line, Circle, Elipse, Flower1, Flower2, Starfish, Fancy};

    void setBackgroundColor (QColor color) {mBackGroundColor = color;}
    QColor backroundColor () const {return mBackGroundColor;}

    void setShapeColor (QColor color) {mPen.setColor(color);}
    QColor shapeColor () const {return mPen.color();}

    void setShape (ShapeType shape) {mShape = shape; on_shape_changed ();}
    ShapeType shape () const {return mShape;}

    void setScale (float scale) {mScale = scale; repaint();}
    float scale () {return mScale; }

    void setIntervalLength (float IntervalLength) {mIntervalLength = IntervalLength; repaint();}
    float IntervalLength () {return mIntervalLength;}

    void setStepCount (int StepCount) {mStepCount = StepCount; repaint();}
    int StepCount () {return mStepCount;}

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
private:
    int on_shape_changed (void);
    QPointF compute (float t);
    QPointF compute_astroid (float t);
    QPointF compute_cycloid (float t);
    QPointF compute_hypo (float t);
    QPointF compute_huygens (float t);
    QPointF compute_line (float t);
    QPointF compute_circle (float t);
    QPointF compute_elipse (float t);
    QPointF compute_flower1 (float t);
    QPointF compute_flower2 (float t);
    QPointF compute_starfish (float t);
    QPointF compute_fancy (float t);
private:
    QColor mBackGroundColor;
    QPen   mPen;
    ShapeType mShape;
    float mIntervalLength;
    float mScale;
    int mStepCount;
};

#endif // RENDERAREA_H
