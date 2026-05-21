#pragma once

#include <QObject>
#include <QThread>
#include <QAtomicInt>

#include <normApi.h>

class NormSenderWorker;

class NormSender : public QObject
{
    Q_OBJECT

public:
    explicit NormSender(QObject *parent = nullptr);
    ~NormSender();

    void sendFile(QString filePath,
                  QString multicastIp = "224.1.2.3",
                  quint16 port = 6003);

    void stop();

signals:
    void log(QString text);

    void completed();

    void error(QString text);

private:
    QThread thread;

    NormSenderWorker *worker = nullptr;
};