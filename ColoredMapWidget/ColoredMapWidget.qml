import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuickSoft.Samples 1.0

Item {
    anchors.fill: parent

    // add a mapView component
    MapView {
        id: view
        objectName: "mapView"
        anchors.fill: parent
    }

    // Declare the C++ instance which creates the scene etc. and supply the view
    ColoredMap {
        id: coloredMap
        objectName: "coloredMap"
        mapView: view
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: {
            if (mouse.button == Qt.RightButton){
                coloredMap.takeSnapshot()
            }
        }
    }

    // Create outter rectangle for the legend
    Rectangle {
        id: legendRect
        anchors {
            bottomMargin: 20
            right: parent.right
            bottom: parent.bottom
        }
        property bool expanded: true
        height: 0.10 * parent.height
        width: (0.2 * parent.width) > (maximumValueText.paintedWidth + minimumValueText.paintedWidth + offsetRectangle.width) ? (0.2 * parent.width) : (maximumValueText.paintedWidth + minimumValueText.paintedWidth + offsetRectangle.width)
        color: "lightgrey"
        opacity: 0.75
        clip: true
        border {
            color: "white"
            width: 1
        }
        visible: false

        // Animate the expand and collapse of the legend
        Behavior on height {
            SpringAnimation {
                spring: 3
                damping: .4
            }
        }

        // Catch mouse signals so they don't propagate to the map
        MouseArea {
            anchors.fill: parent
            onClicked: mouse.accepted = true
            onWheel: wheel.accepted = true
        }

        Rectangle {
            id: gradientLegend
            anchors.fill: parent

            Rectangle {
                id: gradientRectangle
                height: parent.height * 0.7
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: minMaxValues.top
            }

            Rectangle {
                id: minMaxValues
                height: parent.height * 0.3
                width: maximumValueText.paintedWidth + minimumValueText.paintedWidth + offsetRectangle.width
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 3
                color: Qt.rgba(0,0,0,0)

                Rectangle {
                    id: minimumValue
                    width: minimumValueText.paintedWidth
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.right: offsetRectangle.left
                    color: Qt.rgba(0,0,0,0)

                    Text {
                        id: minimumValueText
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: parent.height * 0.8
                        text: ""
                    }
                }
                Rectangle {
                    id: offsetRectangle
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 10
                    color: Qt.rgba(0,0,0,0)
                }

                Rectangle {
                    id: maximumValue
                    width: maximumValueText.paintedWidth
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.left: offsetRectangle.right
                    color: Qt.rgba(0,0,0,0)

                    Text {
                        id: maximumValueText
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignRight
                        font.pixelSize: parent.height * 0.8
                        text: ""
                    }
                }
            }
        }
    }
}
