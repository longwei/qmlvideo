# Add more folders to ship with the application, here
folder_01.source = qml/qmlvideo
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

QT += opengl declarative

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    qmlvideo.cpp

HEADERS += \
    qmlvideo.h

include(qmldeploy.pri)
qtcAddDeployment()
