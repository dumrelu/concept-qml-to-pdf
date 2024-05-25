#ifndef QMLTOPDFEXPORTER_H
#define QMLTOPDFEXPORTER_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>

class QmlToPdfExporter : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString outputFile READ outputFile WRITE setOutputFile NOTIFY outputFileChanged)
    Q_PROPERTY(bool exportInProgress READ exportInProgress WRITE setExportInProgress NOTIFY exportInProgressChanged)
public:
    explicit QmlToPdfExporter(QObject *parent = nullptr);

    Q_INVOKABLE void exportToPdf(QQuickItem* item);

    QString outputFile() const { return m_outputFile; }
    bool exportInProgress() const { return m_exportInProgress; }

    void setOutputFile(QString outputFileName);
    void setExportInProgress(bool value);

signals:
    void exportDone();
    void exportError(QString errorMessage);

    void outputFileChanged();
    void exportInProgressChanged();

private:
    QString m_outputFile = "/tmp/my_file.pdf";
    bool m_exportInProgress = false;
};

#endif // QMLTOPDFEXPORTER_H
