/**
  customview.h

  Simple custom view to allow for zooming
  on graphics objects
**/

#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>

// Custom View to Allow User Interaction
class CustomView : public QGraphicsView
{
public:
    CustomView(QWidget* parent = 0);
protected:
    virtual void wheelEvent(QWheelEvent* event);
};

#endif // CUSTOMVIEW_H
