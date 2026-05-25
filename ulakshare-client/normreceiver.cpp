#include "normreceiver.h"
#include "normreceiverworker.h"

NormReceiver::NormReceiver(QObject *parent)
    : QObject(parent)
{
    worker = new NormReceiverWorker;

    worker->moveToThread(&thread);

    connect(&thread,
            &QThread::finished,
            worker,
            &QObject::deleteLater);

    connect(worker,
            &NormReceiverWorker::log,
            this,
            &NormReceiver::log);

    connect(worker,
            &NormReceiverWorker::progress,
            this,
            &NormReceiver::progress);

    connect(worker,
            &NormReceiverWorker::fileReceived,
            this,
            &NormReceiver::fileReceived);

    connect(worker,
            &NormReceiverWorker::senderActive,
            this,
            &NormReceiver::senderActive);

    connect(worker,
            &NormReceiverWorker::senderInactive,
            this,
            &NormReceiver::senderInactive);

    connect(worker,
            &NormReceiverWorker::error,
            this,
            &NormReceiver::error);

    thread.start();
}

NormReceiver::~NormReceiver()
{
    stop();

    thread.quit();

    thread.wait();
}

void NormReceiver::start(QString cacheDir,
                         QString multicastIp,
                         quint16 port)
{
    QMetaObject::invokeMethod(worker,
                              "startReceiver",
                              Qt::QueuedConnection,
                              Q_ARG(QString, cacheDir),
                              Q_ARG(QString, multicastIp),
                              Q_ARG(quint16, port));
}

void NormReceiver::stop()
{
    QMetaObject::invokeMethod(worker,
                              "stop",
                              Qt::QueuedConnection);
}
void NormReceiver::setAllowed(bool allowed)
{
    worker->allowed=allowed;
}
