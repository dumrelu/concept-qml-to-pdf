import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import concept_qml_to_pdf

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    QmlToPdfExporter {
        id: qmlToPdfExporter
        outputFile: "/tmp/sample_qml_to_pdf.pdf"

        onExportDone: function() {
           console.log("Exported pdf: %s".arg(qmlToPdfExporter.outputFile));
        }

        onExportError: function(errorMessage) {
            console.warn("Export to pdf error: %1".arg(errorMessage));
        }
    }

    Item {
        id: itemToBePrintedToPdf

        anchors.fill: parent

        Rectangle {
            id: background
            anchors.fill: parent
            color: "gray"
        }

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                Text {
                    text: "Default font text"
                }

                Item {
                    Layout.fillWidth: true
                }

                Text {
                    text: "Bigger font"
                    font.pixelSize: 32
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                text: "Middle text"
                font.pixelSize: 48

                Rectangle {
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "black"
                    border.width: 1
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                Layout.fillWidth: true
                wrapMode: Text.Wrap
                text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum"
            }

            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Print to pdf(%1)".arg(qmlToPdfExporter.outputFile)

                onClicked: function() {
                    qmlToPdfExporter.exportToPdf(itemToBePrintedToPdf);
                }
            }
        }
    }

    BusyIndicator {
        anchors.centerIn: parent
        running: qmlToPdfExporter.exportInProgress
    }
}
