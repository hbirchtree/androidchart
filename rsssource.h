#ifndef RSSSOURCE_H
#define RSSSOURCE_H

#include <QList>
#include "chartsource.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QRegExp>

class RssSource : public ChartSource
{
    Q_OBJECT
public:
    explicit RssSource(QUrl source, QString titleRegex, QObject *parent=0) : ChartSource(source,titleRegex,parent){
        webAccess = new QNetworkAccessManager();
        connect(webAccess,SIGNAL(finished(QNetworkReply*)),this,SLOT(processFeed(QNetworkReply*)));
        if(!titleRegex.isEmpty())
            this->titleRegex = titleRegex;
        else
            this->titleRegex = ".*";
        sourceUrl = source;
    }

    ~RssSource(){

    }

    void startLoading(){
        QNetworkRequest fileGet(sourceUrl);
        webAccess->get(fileGet);
    }
    QString searchGuid(){return "RSS";}
public slots:
    void processFeed(QNetworkReply *reply){
        QByteArray data = reply->readAll();
        reply->deleteLater();
        QXmlStreamReader feedReader(data);
        while(!feedReader.isEndDocument()){
            if(feedReader.hasError())
                break;
            if(feedReader.name().toString()=="title")
                transmitNewChannel(feedReader.text().toString());
            if(feedReader.name().toString()=="item"){
                feedReader.readNext();
                ChartEntry *item = new ChartEntry();
                while(feedReader.name().toString()!="item"){
                    if(feedReader.name().toString()=="title"){
                        feedReader.readNext();
                        if(feedReader.name().toString().isEmpty()){
                            QRegExp titleCapture;
                            titleCapture.setPattern(titleRegex);
                            if(titleCapture.indexIn(feedReader.text().toString())!=-1)
                                item->setTitle(titleCapture.cap(1));
                            else
                                item->setTitle(feedReader.text().toString());
                        }
                    }
                    if(feedReader.name().toString()=="link"){
                        feedReader.readNext();
                        if(feedReader.name().toString().isEmpty())
                            item->setLinkedContent(QUrl(feedReader.text().toString()));
                    }
                    if(feedReader.name().toString()=="description"){
                        feedReader.readNext();
                        if(feedReader.name().toString().isEmpty())
                            item->setdescription(feedReader.text().toString());
                    }
                    feedReader.readNext();
                }
                transmitEntry(QVariant::fromValue(item));
            }
            feedReader.readNext();
        }
    }
signals:
    void transmitEntry(QVariant);
    void transmitNewChannel(QString);
private:
    enum ImageType {
        IMG_LOGO_BIG,IMG_SQUARE
    };
    QUrl getImageUrl(enum ImageType variant, QString searchCriteria);
    QNetworkAccessManager *webAccess;
    QString titleRegex;
    QUrl sourceUrl;
};

#endif // RSSSOURCE_H
