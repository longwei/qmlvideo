// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import QmlVideo 1.0

Rectangle {
    width: 360
    height: 360

    Grid {
        rows: 2; columns: 2;
        anchors.fill: parent;
        id: column;
        Video {
            id: video
            anchors.margins: 10;
            width: parent.width/2;
            height: parent.height/2;
            //fileName: "C:\\Users\\Public\\Videos\\Sample Videos\\wildlife.wmv";
            //fileName: "rtsp://10.0.0.33/img/video.sav"
            fileName: "C:\\Users\\XWeng\\Downloads\\big_buck_bunny_1080p_h264.mov"
            state: Video.Playing;
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    parent.pause();
                }
            }
        }
        Video {
            id: video2
            anchors.margins: 10;
            width: parent.width/2;
            height: parent.height/2;
            fileName: "C:\\Users\\Public\\Videos\\Sample Videos\\wildlife.wmv";
            //fileName: "rtsp://10.0.0.33/img/video.sav"
            state: Video.Playing;
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    parent.playPause();
                }
            }
        }
        Video {
            id: video3
            anchors.margins: 10;
            width: parent.width/2;
            height: parent.height/2;
            fileName: "C:\\Users\\Public\\Videos\\Sample Videos\\wildlife.wmv";
            //fileName: "rtsp://10.0.0.33/img/video.sav"
            state: Video.Playing;
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    parent.playPause();
                }
            }
        }
        Video {
            id: video4
            anchors.margins: 10;
            width: parent.width/2;
            height: parent.height/2;
            //fileName: "C:\\Users\\Public\\Videos\\Sample Videos\\wildlife.wmv";
            fileName: "rtsp://10.0.0.33/img/video.sav"
            state: Video.Playing;
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    parent.playPause();
                }
            }
        }
    }
}
