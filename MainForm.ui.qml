import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    id: item1
    width: 640
    height: 480

    property alias gridView: gridView1
    property alias addFeedButton: button1
    property alias feedUrl: textField1
    property alias regexField: textField2
    property alias searchSelect: comboBox1

    GridView {
        id: gridView1
        snapMode: GridView.SnapToRow
        anchors.fill: parent
    }

    Button {
        id: button1
        x: 547
        text: qsTr("Add")
        anchors.top: comboBox1.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
    }

    TextField {
        id: textField1
        text: ""
        anchors.top: comboBox1.top
        anchors.topMargin: 0
        anchors.left: comboBox1.right
        anchors.leftMargin: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 0
        placeholderText: qsTr("Feed URL")
    }

    TextField {
        id: textField2
        text: "\\[[A-Za-z]+\\] ([A-Za-z\\d\\W\\w]+) \\["
        anchors.top: comboBox1.top
        anchors.topMargin: 0
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 0
        anchors.right: button1.left
        anchors.rightMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        placeholderText: qsTr("Regex")
    }

    ComboBox {
        id: comboBox1
        y: 445
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
    }
}
