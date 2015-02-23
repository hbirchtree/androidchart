#ifndef NYAASOURCE_H
#define NYAASOURCE_H

#include <QList>
#include "chartsource.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QRegExp>
#include <QHash>

class NyaaSource : public ChartSource
{
    Q_OBJECT
public:
    explicit NyaaSource(QUrl source, QString titleRegex, QObject *parent=0) : ChartSource(source,titleRegex,parent){
        webAccess = new QNetworkAccessManager();
        connect(webAccess,SIGNAL(finished(QNetworkReply*)),this,SLOT(processFeed(QNetworkReply*)));
        if(!titleRegex.isEmpty())
            this->titleRegex = titleRegex;
        else
            this->titleRegex = ".*";
        sourceUrl = source;
    }

    ~NyaaSource(){

    }

    void startLoading(){
        QNetworkRequest fileGet(sourceUrl);
        webAccess->get(fileGet);
    }
    QString searchGuid(){return "Nyaa";}
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
                    if(feedReader.name().toString()=="category"){
                        feedReader.readNext();
                        if(feedReader.name().toString().isEmpty())
                            item->setImgLogoBig(getImageUrl(IMG_UNSPECIFIC,feedReader.text().toString()));
                        feedReader.readNext();
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
        IMG_UNSPECIFIC,IMG_LOGO_BIG,IMG_SQUARE
    };
    typedef QHash<QString,QString> CategoryMap;
    CategoryMap categoryTranslate = defineCategories();
    CategoryMap defineCategories(){
        CategoryMap cats;
        cats.insert("English-translated Anime","http://files.nyaa.se/www-37.png");
        return cats;
    }
    QUrl getImageUrl(enum ImageType variant, QString searchCriteria){
        return QUrl(categoryTranslate.value(searchCriteria));
    }

    QNetworkAccessManager *webAccess;
    QString titleRegex;
    QUrl sourceUrl;
};

#endif // NYAASOURCE_H
