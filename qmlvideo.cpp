#include "qmlvideo.h"
#include <QPainter>
#include <qgl.h>
#include <QDebug>
#include <QTimer>
#include <QMutexLocker>
#include <QImage>
#include <vlc/vlc.h>
#include <QLabel>

QmlVideo::QmlVideo(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_state(Stopped)
{
    //Set up item options
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    setSmooth(true);

    //Initialize the VLC library;
    const char *argv[] =
    {
        "--no-audio", /* skip any audio track */
        "--no-xlib", /* tell VLC to not use Xlib */
    };
    int argc = sizeof(argv) / sizeof(*argv);
    m_libVlc = libvlc_new(argc,argv);
}

QmlVideo::State QmlVideo::state()
{
    return(m_state);
}

void QmlVideo::play(const QString &fileName)
{
    if(fileName.isNull())
        setFileName(fileName);

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
        libvlc_media_player_stop(m_mediaPlayer);
        emit(stopped());
        break;
    case Playing:
        qDebug() << "Playing";
        libvlc_media_player_play(m_mediaPlayer);
        emit(playing());
        break;
    case Paused:
        qDebug() << "Paused";
        libvlc_media_player_set_pause(m_mediaPlayer,1);
        emit(paused());
        break;
    }

    emit(stateChanged(state));
}

QString QmlVideo::fileName()
{
    return(m_fileName);
}

void QmlVideo::setFileName(const QString &fileName)
{
    if(m_state != Stopped)
        setState(Stopped);
    m_fileName = fileName;

    libvlc_media_t *m;
    m = libvlc_media_new_path(m_libVlc, qPrintable(fileName));
    m_mediaPlayer = libvlc_media_player_new_from_media(m);
    libvlc_media_release(m);

    libvlc_video_set_format_callbacks(m_mediaPlayer, vlcVideoFormatCallback, NULL);
    libvlc_video_set_callbacks(m_mediaPlayer, vlcVideoLockCallBack, vlcVideoUnlockCallback, vlcVideoDisplayCallback, this);
}

void QmlVideo::paintFrame()
{
    //Just signal that we need to repaint the item.
    update();
}

void QmlVideo::paint(QPainter *p, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
    QImage img((uchar *)m_pixelBuff, m_width, m_height, QImage::Format_RGB888);
    p->drawImage(boundingRect(), img, QRect(0,0,m_width, m_height));
    /*
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
    */
}

unsigned int QmlVideo::vlcVideoFormatCallback(void **object, char *chroma, unsigned int *width, unsigned int *height,
                           unsigned int *pitches, unsigned int *lines)
{
    unsigned int retval = 0;
    QmlVideo *instance = (QmlVideo *)*object;
    QMetaObject::invokeMethod(instance, "setupFormat", Qt::BlockingQueuedConnection, Q_RETURN_ARG(quint32, retval),
                              Q_ARG(char *, chroma), Q_ARG(unsigned int *, width), Q_ARG(unsigned int *, height),
                              Q_ARG(unsigned int *, pitches), Q_ARG(unsigned int *, lines));
    return(retval);
}

void *QmlVideo::vlcVideoLockCallBack(void *object, void **planes)
{
    //Lock the pixel mutex, and hand the pixel buffer to VLC
    QmlVideo *instance = (QmlVideo *)object;
    QMutexLocker((instance->m_pixelMutex));
    *planes = (void *)instance->m_pixelBuff;
    return NULL;
}

void QmlVideo::vlcVideoUnlockCallback(void *object, void *picture, void * const *planes)
{
    QmlVideo *instance = (QmlVideo *)object;
    QMetaObject::invokeMethod(instance, "updateTexture", Qt::BlockingQueuedConnection,
                              Q_ARG(void *, picture), Q_ARG(void * const *, planes));
}

void QmlVideo::vlcVideoDisplayCallback(void *object, void *picture)
{
    //Call the paintFrame function in the main thread.
    QmlVideo *instance = (QmlVideo *)object;
    QMetaObject::invokeMethod(instance, "paintFrame", Qt::BlockingQueuedConnection);
}

quint32 QmlVideo::setupFormat(char *chroma, unsigned int *width, unsigned int *height, unsigned int *pitches, unsigned int *lines)
{
    qDebug() << "Got format request:" << chroma << *width << *height;
    strcpy(chroma, "RV24");
    pitches[0] = *width * 3;
    lines[0] = *height * 3;
    m_pixelBuff = (char *)malloc((*width)*(*height)*3);
    m_width = *width;
    m_height = *height;
    return(1);
}

void QmlVideo::updateTexture(void *picture, void * const *planes)
{

}
