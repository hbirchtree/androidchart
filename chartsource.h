#ifndef CHARTSOURCE
#define CHARTSOURCE

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include "chartentry.h"

class ChartSource : public QObject {
    Q_OBJECT
public:
    explicit ChartSource(QUrl source, QString titleRegex, QObject *parent=0){}
    ~ChartSource(){}
    virtual void startLoading() = 0;
    virtual QString searchGuid() = 0;
public slots:
    virtual void processFeed(QNetworkReply *reply) = 0;
signals:
    void transmitEntry(QVariant);
    void transmitNewChannel(QString);
};

#endif // CHARTSOURCE

