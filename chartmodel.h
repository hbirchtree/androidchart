#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include <QObject>
#include <QQmlListProperty>
#include "chartentry.h"
#include "rsssource.h"
#include <QDebug>

class ChartModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> entries READ entries NOTIFY entriesChanged)
    QQmlListProperty<QObject> m_entries;
    QList<QObject*> m_AllEntries;

public:
    explicit ChartModel(QObject *parent = 0);
    ~ChartModel();

QQmlListProperty<QObject> entries()
{
    return QQmlListProperty<QObject>(this,m_AllEntries);
}

signals:

void entriesChanged(QQmlListProperty<QObject> arg);

public slots:
void addChartEntry(QObject *newEntry){
    m_AllEntries.append(newEntry);
    entriesChanged(entries());
}
void clearEntries(){
    m_AllEntries.clear();
    entriesChanged(entries());
}
};

#endif // CHARTMODEL_H
