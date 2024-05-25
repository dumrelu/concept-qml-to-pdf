#include "qmltopdfexporter.h"

#include <QPainter>
#include <QPrinter>
#include <QQuickItemGrabResult>

QmlToPdfExporter::QmlToPdfExporter(QObject *parent)
    : QObject{parent}
{
}

void QmlToPdfExporter::exportToPdf(QQuickItem *item)
{
    if(!item)
    {
        emit exportError(QStringLiteral("Null item"));
        return;
    }

    if(exportInProgress())
    {
        emit exportError(QStringLiteral("Export already in progress"));
        return;
    }

    setExportInProgress(true);

    //TODO: potentially make the text invisible
    auto grabResult = item->grabToImage();
    Q_ASSERT(grabResult);
    connect(grabResult.get(), &QQuickItemGrabResult::ready, this,
        [this, item, grabResult]()
        {
            onGrabImageReady(item, grabResult);
        }
    );
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

void QmlToPdfExporter::onGrabImageReady(QQuickItem* item, QSharedPointer<QQuickItemGrabResult> grabResult)
{
    qDebug() << "Image grab ready";

    auto textItems = findTextItems(item);
    qDebug() << "Text items: ";
    for(auto* textItem : textItems)
    {
        qDebug() << "\t" << textItem->text();
    }

    auto image = grabResult->image();

    QPrinter pdfPrinter(QPrinter::HighResolution);
    pdfPrinter.setPageSize(QPageSize(QPageSize::A4));
    pdfPrinter.setPageMargins({});
    pdfPrinter.setOutputFormat(QPrinter::PdfFormat);
    pdfPrinter.setOutputFileName(m_outputFile);

    if(!pdfPrinter.isValid())
    {
        emit exportError("Could not setup printer");
        setExportInProgress(false);
    }

    QPainter painter;
    painter.begin(&pdfPrinter);

    painter.setRenderHint(QPainter::LosslessImageRendering, true);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setWindow(0, 0, image.width(), image.height());


    painter.drawImage(QPoint{0, 0}, image);

    for(auto* textItem : textItems)
    {
        //TODO: there's an issue with the default font
        painter.setFont(textItem->font());

        QPen pen{ textItem->color() };
        painter.setPen(pen);

        auto position = textItem->mapToItem(item, {});
        auto textOption = getTextOption(textItem);

        QRectF textRect(position, textItem->size());
        painter.drawText(textRect, textItem->text(), textOption);
    }


    painter.end();

    qDebug() << "Wrote pdf: " << m_outputFile;

    setExportInProgress(false);
}

//! WARNING: don't use a private Qt header
QList<QQuickText*> QmlToPdfExporter::findTextItems(QQuickItem* item) const
{
    QList<QQuickText*> textItems;
    for(auto* childItem : item->childItems())
    {
        auto* textItem = qobject_cast<QQuickText*>(childItem);
        if(textItem)
        {
            textItems.push_back(textItem);
        }

        //! Shouldn't use recursion. Potential stack overflow if we have many items
        textItems.append(findTextItems(childItem));
    }

    return textItems;
}

QTextOption QmlToPdfExporter::getTextOption(QQuickText* textItem) const
{
    QTextOption option;
    //TODO: fill this out properly
    option.setWrapMode(static_cast<QTextOption::WrapMode>(textItem->wrapMode()));
    return option;
}
