#ifndef QMLVIDEO_H
#define QMLVIDEO_H

#include <QDeclarativeItem>

class QmlVideo : public QDeclarativeItem
{
    Q_OBJECT
public:
    explicit QmlVideo(QDeclarativeItem *parent = 0);
    
    void paint(QPainter *p, const QStyleOptionGraphicsItem *style, QWidget *widget);

signals:
    
public slots:
    
};

#endif // QMLVIDEO_H
