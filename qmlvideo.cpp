#include "qmlvideo.h"
#include <QPainter>
#include <qgl.h>QT += opengl
#include <QDebug>
#include <QTimer>

QmlVideo::QmlVideo(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_state(Stopped)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    setSmooth(true);


    m_frameTimer = new QTimer(this);
    QObject::connect(m_frameTimer, SIGNAL(timeout()), this, SLOT(frame()));
    m_frameTimer->setInterval(33);
}

QmlVideo::State QmlVideo::state()
{
    return(m_state);
}

void QmlVideo::play()
{
    setState(Playing);
}

void QmlVideo::pause()
{
    setState(Paused);
}

void QmlVideo::stop()
{
    setState(Stopped);
}

void QmlVideo::playPause()
{
    switch(m_state)
    {
    case Stopped:
        setState(Playing);
        break;
    case Playing:
        setState(Paused);
        break;
    case Paused:
        setState(Playing);
        break;
    }
}

void QmlVideo::setState(State state)
{
    if(state == m_state)
        return;

    m_state = state;

    switch(m_state)
    {
    case Stopped:
        qDebug() << "Stopped";
        m_frameTimer->stop();
        emit(stopped());
        break;
    case Playing:
        qDebug() << "Playing";
        m_frameTimer->start();
        emit(playing());
        break;
    case Paused:
        qDebug() << "Paused";
        m_frameTimer->stop();
        emit(paused());
        break;
    }

    emit(stateChanged(state));
}

void QmlVideo::frame()
{
    update();
}

void QmlVideo::paint(QPainter *p, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
    p->beginNativePainting();

    qDebug() << "Paint...";

    glClear(GL_COLOR_BUFFER_BIT);

    QRectF rect = boundingRect();

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
