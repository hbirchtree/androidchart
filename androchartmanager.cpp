#include "androchartmanager.h"

AndroChartManager::AndroChartManager(QObject *parent) : QObject(parent)
{
    QQmlApplicationEngine engine;
    qmlRegisterType<ChartModel>("ChartModel", 1, 0, "ChartModel");
    qRegisterMetaType<ChartEntry>("ChartEntry");
    qRegisterMetaType<QQmlListProperty<ChartEntry> >("QQmlListProperty<ChartEntry>");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    qmlContext = engine.rootObjects().at(0);
    connect(qmlContext,SIGNAL(loadNewSource(QString,QString,QString)),SLOT(loadNewSource(QString,QString,QString)));
    QEventLoop eventLoop;
    connect(&engine,SIGNAL(quit()),&eventLoop,SLOT(quit()));
    eventLoop.exec();
}

void AndroChartManager::loadNewSource(QString sourceUrl,QString regex,QString searchType){
    ChartSource *source;
    if(searchType=="Nyaa")
        source = new NyaaSource(QUrl(sourceUrl),regex);
    else
        return;
    connect(source,SIGNAL(transmitEntry(QVariant)),qmlContext,SLOT(insertChartEntry(QVariant)));
//    connect(source,SIGNAL(transmitNewChannel(QString)),qmlContext,SLOT(announceNewChannel(QString)));
    source->startLoading();
    entrySource.append(source);
}

AndroChartManager::~AndroChartManager()
{

}
