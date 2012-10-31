#ifndef QMLVIDEO_H
#define QMLVIDEO_H

#include <QDeclarativeItem>

class QTimer;

class QmlVideo : public QDeclarativeItem
{
    Q_OBJECT
    Q_ENUMS(State);
    Q_PROPERTY(State state READ state WRITE setState);
public:
    enum State
    {
        Stopped,
        Playing,
        Paused
    };

    explicit QmlVideo(QDeclarativeItem *parent = 0);
    
    void paint(QPainter *p, const QStyleOptionGraphicsItem *style, QWidget *widget);

    Q_INVOKABLE State state();

signals:
    void stateChanged(State state);
    void stopped();
    void playing();
    void paused();

public slots:
    void play();
    void pause();
    void stop();
    void playPause();
    void setState(State state);

protected slots:
    virtual void frame();

private:
    QTimer *m_frameTimer;
    State m_state;
};

#endif // QMLVIDEO_H
