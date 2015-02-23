#ifndef CHARTENTRY
#define CHARTENTRY

#include <QObject>
#include <QString>
#include <QUrl>

class ChartEntry : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString description READ description WRITE setdescription NOTIFY descriptionChanged)
    Q_PROPERTY(QUrl imgLogoBig READ imgLogoBig WRITE setImgLogoBig NOTIFY imgLogoBigChanged)
    Q_PROPERTY(QUrl linkedContent READ linkedContent WRITE setLinkedContent NOTIFY linkedContentChanged)
    Q_PROPERTY(QUrl imgSquare READ imgSquare WRITE setimgSquare NOTIFY imgSquareChanged)

    QString m_title;
    QUrl m_imgLogoBig;
    QUrl m_linkedContent;
    QString m_description;
    QUrl m_imgSquare;

public:
    ChartEntry(){}
    ChartEntry(const ChartEntry& oldEntry,QObject *parent=0) : QObject(parent){
        m_title = oldEntry.title();
        m_imgLogoBig = oldEntry.imgLogoBig();
        m_linkedContent = oldEntry.linkedContent();
    }

    ChartEntry(QString title,QUrl linkedContent,QUrl imgLogoBig=QUrl()){
        m_title = title;
        m_imgLogoBig = imgLogoBig;
        m_linkedContent = linkedContent;
    }

    QString title() const
    {
        return m_title;
    }
    QUrl imgLogoBig() const
    {
        return m_imgLogoBig;
    }

    QUrl linkedContent() const
    {
        return m_linkedContent;
    }

    QString description() const
    {
        return m_description;
    }

    QUrl imgSquare() const
    {
        return m_imgSquare;
    }

public slots:
    void setTitle(QString arg)
    {
        if (m_title == arg)
            return;

        m_title = arg;
        emit titleChanged(arg);
    }
    void setImgLogoBig(QUrl arg)
    {
        if (m_imgLogoBig == arg)
            return;

        m_imgLogoBig = arg;
        emit imgLogoBigChanged(arg);
    }

    void setLinkedContent(QUrl arg)
    {
        if (m_linkedContent == arg)
            return;

        m_linkedContent = arg;
        emit linkedContentChanged(arg);
    }

    void setdescription(QString arg)
    {
        if (m_description == arg)
            return;

        m_description = arg;
        emit descriptionChanged(arg);
    }

    void setimgSquare(QUrl arg)
    {
        if (m_imgSquare == arg)
            return;

        m_imgSquare = arg;
        emit imgSquareChanged(arg);
    }

signals:
    void titleChanged(QString arg);
    void imgLogoBigChanged(QUrl arg);
    void linkedContentChanged(QUrl arg);
    void descriptionChanged(QString arg);
    void imgSquareChanged(QUrl arg);
};

#endif // CHARTENTRY

