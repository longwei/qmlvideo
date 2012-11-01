# Add more folders to ship with the application, here
folder_01.source = qml/qmlvideo
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

QT += opengl declarative

win32 {
    INCLUDEPATH += "C:/Program Files (x86)/VideoLAN/VLC/sdk/include"
    LIBS += "C:/Program Files (x86)/VideoLAN/VLC/sdk/lib/libvlccore.lib"
    LIBS += "C:/Program Files (x86)/VideoLAN/VLC/sdk/lib/libvlc.lib"
}

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    qmlvideo.cpp

HEADERS += \
    qmlvideo.h

include(qmldeploy.pri)
qtcAddDeployment()
