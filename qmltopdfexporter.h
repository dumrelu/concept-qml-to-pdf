#ifndef QMLTOPDFEXPORTER_H
#define QMLTOPDFEXPORTER_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>

//! WARNING: This is just to simplify the proof of concept. Don't do this
#include <private/qquicktext_p.h>

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
    void onGrabImageReady(QQuickItem* item, QSharedPointer<QQuickItemGrabResult> grabResult);
    QList<QQuickText*> findTextItems(QQuickItem* item) const;
    QTextOption getTextOption(QQuickText* textItem) const;

    QString m_outputFile = "/tmp/my_file.pdf";
    bool m_exportInProgress = false;
};

#endif // QMLTOPDFEXPORTER_H
