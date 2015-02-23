import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import ChartModel 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    onClosing: Qt.quit()

    function insertChartEntry(item){
        rootModel.addChartEntry(item)
    }
    function announceChannel(title){
        testDial.open()
    }
    signal loadNewSource(string sourceUrl, string regex,string searchType)

    property double componentScale: 1.0
    property int componentHeight: 100*componentScale
    property int componentWidth: 300*componentScale

    property alias rootModel: chartModel

    MessageDialog {
        id:testDial
        text: "TEST"
    }

    ChartModel {
        id:chartModel
    }

    Component {
        id: gridDelegate
        Item {
            width: componentWidth
            height: componentHeight
            MouseArea {
                onClicked: Qt.openUrlExternally(linkedContent)
                anchors.fill:parent
            }
            Image {
                Text {
                    anchors.fill:parent
                    text: description
                }

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: titleText.top
                fillMode: Image.PreserveAspectFit
                source: imgLogoBig
            }
            Text {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                id:titleText
                text: title
                font.bold: true
                styleColor: "#d1d1d1"
                style: Text.Outline
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 12
                elide: Text.ElideRight
            }
        }
    }

    PinchArea {
        property double tempScale: 1.0;
        property point sPoint1;
        property point sPoint2;
        anchors.fill:parent
        onPinchUpdated: {
            if(pinch.pointCount>1){
                tempScale = Math.sqrt(Math.pow(Math.abs(pinch.point2.x-pinch.point1.x),2)+Math.pow(Math.abs(pinch.point2.y-pinch.point1.y),2))/Math.sqrt(Math.pow(Math.abs(sPoint2.x-sPoint1.x),2)+Math.pow(Math.abs(sPoint2.y-sPoint1.y),2))+tempScale-1
                tempScale = Math.max(Math.min(tempScale,15.0),1.0)
                componentScale = tempScale
            }
        }
        onPinchStarted: {
            sPoint1 = pinch.point1
            sPoint2 = pinch.point2
        }

        MainForm {
            id: mainForm
            anchors.fill: parent
            gridView.model: rootModel.entries
            gridView.delegate: gridDelegate
            gridView.cellHeight: componentHeight
            gridView.cellWidth: componentWidth
            gridView.focus: true
            Transition {
                id:addedTransition
                NumberAnimation {
                    properties: "opacity"
                    from: 0
                    to: 1
                    duration: 400
                    easing.type: Easing.InExpo
                }
            }
            Transition {
                id:movingTransition
                NumberAnimation {
                    properties: "x,y"
                    duration: 300
                    easing.type: Easing.InExpo
                }
            }
            gridView.move: movingTransition
            gridView.displaced: movingTransition
            gridView.add: addedTransition
            gridView.populate: addedTransition
            searchSelect.model: ["Nyaa"]

            addFeedButton.onClicked: {
                loadNewSource(feedUrl.text,regexField.text,searchSelect.currentText)
//                loadNewSource("http://www.nyaa.se/?page=rss&term=horrible+sword+art+online+ii+720p","\\[[A-Za-z]+\\] ([A-Za-z\\d\\W\\w]+) \\[","Nyaa")
            }
        }
    }

}
