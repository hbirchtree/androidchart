#ifndef ANDROCHARTMANAGER_H
#define ANDROCHARTMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "chartentry.h"
#include "chartsource.h"
#include "rsssource.h"
#include "nyaasource.h"
#include "chartmodel.h"
#include <QList>
#include <QQmlListProperty>
#include <QEventLoop>

class AndroChartManager : public QObject
{
    Q_OBJECT
public:
    explicit AndroChartManager(QObject *parent = 0);
    ~AndroChartManager();
    void start();
signals:

public slots:
    void loadNewSource(QString sourceUrl,QString regex,QString searchType);
private:
    QList<ChartSource*> entrySource;
    QObject *qmlContext;
};

#endif // ANDROCHARTMANAGER_H
