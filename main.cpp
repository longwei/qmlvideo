#include <QApplication>
#include <QDeclarativeView>
#include <QGLWidget>
#include "qmlvideo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    qmlRegisterType<QmlVideo>("QmlVideo", 1, 0, "Video");

    QDeclarativeView *view = new QDeclarativeView();
    QGLWidget *gl = new QGLWidget();
    view->setViewport(gl);

    view->setSource(QUrl::fromLocalFile("qml/qmlvideo/main.qml"));
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    view->show();

    return app.exec();
}
