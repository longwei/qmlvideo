#ifndef QMLVIDEO_H
#define QMLVIDEO_H

#include <QDeclarativeItem>
#include <QMutex>

struct libvlc_instance_t;
struct libvlc_media_player_t;
struct libvlc_event_t;

class QmlVideo : public QDeclarativeItem
{
    Q_OBJECT
    Q_ENUMS(State)
    Q_PROPERTY(State state READ state WRITE setState)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName)

    enum PaintMode
    {
        PaintModeQPainter,
        PaintModeTexture,
        PaintModePBO
    };

public:
    enum State
    {
        Opening,
        Buffering,
        Stopped,
        Playing,
        Paused
    };

    explicit QmlVideo(QDeclarativeItem *parent = 0);
    ~QmlVideo();
    
    void paint(QPainter *p, const QStyleOptionGraphicsItem *style, QWidget *widget);

    Q_INVOKABLE State state();
    Q_INVOKABLE QString fileName();
    Q_INVOKABLE void setFileName(const QString &fileName);

signals:
    void stateChanged(State state);
    void stopped();
    void playing();
    void paused();

public slots:
    void play(const QString &ileName = QString::Null());
    void pause();
    void stop();
    void setState(State state);

protected slots:
    quint32 setupFormat(char *chroma, unsigned int *width, unsigned int *height,
                               unsigned int *pitches, unsigned int *lines);
    void updateTexture(void *picture, void * const *planes);
    void paintFrame();
    void playerEvent(const libvlc_event_t *event);

private:
    //VLC callback functions
    static unsigned int vlcVideoFormatCallback(void **object, char *chroma, unsigned int *width, unsigned int *height,
                               unsigned int *pitches, unsigned int *lines);
    static void *vlcVideoLockCallBack(void *object, void **planes);
    static void vlcVideoUnlockCallback(void *object, void *picture, void * const *planes);
    static void vlcVideoDisplayCallback(void *object, void *picture);
    static void vlcVideoEventCallback(const libvlc_event_t *event, void *object);

    void clearUp();

    void setupPlanes(char *chroma, unsigned int *width, unsigned int *height,
                     unsigned int *pitches, unsigned int *lines);
    void setupBuffers();
    void cleanupBuffers();
    void setupTextures();
    void cleanupTextures();
    void updateTextures();
    void setupPBOs();
    void cleanupPBOs();
    void updatePBOs();

    //Video Properties
    QString m_fileName;
    quint32 m_width;
    quint32 m_height;

    //State and buffer variables
    State m_state;
    char *m_pixelBuff[3];
    QMutex *m_pixelMutex;
    libvlc_instance_t *m_libVlc;
    libvlc_media_player_t *m_mediaPlayer;
    PaintMode m_paintMode;
    quint32 m_textureId[3];
    quint32 m_pbo1[3];
    quint32 m_pbo2[3];
    int m_numPlanes;
};

#endif // QMLVIDEO_H
