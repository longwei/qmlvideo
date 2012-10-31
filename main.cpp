#include <QApplication>
#include <QDeclarativeView>
#include <QGLWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    QDeclarativeView *view = new QDeclarativeView();
    QGLWidget *gl = new QGLWidget();
    view->setViewport(gl);

    view->setSource(QUrl::fromLocalFile("qml/qmlvideo/main.qml"));

    view->show();

    return app.exec();
}
