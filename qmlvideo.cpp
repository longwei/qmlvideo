#include "qmlvideo.h"
#include <QPainter>
#include <qgl.h>QT += opengl
#include <QDebug>

QmlVideo::QmlVideo(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}


void QmlVideo::paint(QPainter *p, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
    p->beginNativePainting();

    qDebug() << "Paint...";

    glClear(GL_COLOR_BUFFER_BIT);

    QRectF rect = sceneBoundingRect();



    glLoadIdentity();
    glBegin(GL_QUADS);
        glColor3f(255,0,0);
        glVertex2d(rect.x(), rect.y());
        glColor3f(0,255,0);
        glVertex2d(rect.x(), rect.y() + rect.height());
        glColor3f(0,0,255);
        glVertex2d(rect.x() + rect.width(), rect.y() + rect.height());
        glColor3f(0,255,0);
        glVertex2d(rect.x() + rect.width(), rect.y());
    glEnd();

    p->endNativePainting();
}
