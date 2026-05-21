#include "normsender.h"
#include "normsenderworker.h"

NormSender::NormSender(QObject *parent)
    : QObject(parent)
{
    worker = new NormSenderWorker;

    worker->moveToThread(&thread);

    connect(&thread,
            &QThread::finished,
            worker,
            &QObject::deleteLater);

    connect(worker,
            &NormSenderWorker::log,
            this,
            &NormSender::log);

    connect(worker,
            &NormSenderWorker::completed,
            this,
            &NormSender::completed);

    connect(worker,
            &NormSenderWorker::error,
            this,
            &NormSender::error);

    thread.start();
}

NormSender::~NormSender()
{
    stop();

    thread.quit();

    thread.wait();
}

void NormSender::sendFile(QString filePath,
                          QString multicastIp,
                          quint16 port)
{
    QMetaObject::invokeMethod(worker,
                              "send",
                              Qt::QueuedConnection,
                              Q_ARG(QString, filePath),
                              Q_ARG(QString, multicastIp),
                              Q_ARG(quint16, port));
}

void NormSender::stop()
{
    QMetaObject::invokeMethod(worker,
                              "stop",
                              Qt::QueuedConnection);
}
