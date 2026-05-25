#pragma once

#include <QObject>
#include <QAtomicInt>

#include <normApi.h>
#include<QNetworkInterface>

class NormReceiverWorker : public QObject
{
    Q_OBJECT

public:
    explicit NormReceiverWorker(QObject *parent = nullptr);
    QString interfaceType;
    bool allowed;
public slots:
    void startReceiver(QString cacheDir,
                       QString multicastIp,
                       quint16 port);

    void stop();
    QString detectNetworkType();

signals:
    void log(QString text);

    void progress(QString fileName,
                  qint64 current,
                  qint64 total,
                  double percent);

    void fileReceived(QString filePath);

    void senderActive();

    void senderInactive();

    void error(QString text);

private:
    QAtomicInt running;

    NormInstanceHandle instance = NORM_INSTANCE_INVALID;

    NormSessionHandle session = NORM_SESSION_INVALID;
};
