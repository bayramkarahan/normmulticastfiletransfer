#pragma once

#include <QObject>
#include <QThread>

class NormReceiverWorker;

class NormReceiver : public QObject
{
    Q_OBJECT

public:
    explicit NormReceiver(QObject *parent = nullptr);
    ~NormReceiver();

    void start(QString cacheDir,
               QString multicastIp = "224.1.2.3",
               quint16 port = 6003);

    void stop();

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
    QThread thread;

    NormReceiverWorker *worker = nullptr;
};