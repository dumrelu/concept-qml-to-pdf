#include "qmltopdfexporter.h"

QmlToPdfExporter::QmlToPdfExporter(QObject *parent)
    : QObject{parent}
{
}

void QmlToPdfExporter::setOutputFile(QString outputFileName)
{
    if(m_outputFile != outputFileName)
    {
        m_outputFile = outputFileName;
        emit outputFileChanged();
    }
}

void QmlToPdfExporter::setExportInProgress(bool value)
{
    if(m_exportInProgress != value)
    {
        m_exportInProgress = value;
        emit exportInProgressChanged();
    }
}
