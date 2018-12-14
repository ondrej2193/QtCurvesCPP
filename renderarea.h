#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    enum Shapes {Astroid, Cycloid, HuygensCycloid, HypoCycloid};
    void setBackgroundColor (QColor color) {mBackGroundColor = color;}
    QColor backroundColor () const {return mBackGroundColor;}
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
private:
    QColor mBackGroundColor;
    QColor mShapeColor;
};

#endif // RENDERAREA_H
