// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import QmlVideo 1.0

Rectangle {
    width: 360
    height: 360

    Video {
        id: video
        anchors.margins: 10;
        anchors.fill: parent;
        fileName: "C:\\Users\\Public\\Videos\\Sample Videos\\wildlife.wmv";
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            video.playPause();
        }
    }
}
