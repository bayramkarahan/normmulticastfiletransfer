#include <QCoreApplication>
#include <QDebug>

#include "normreceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NormReceiver receiver;

    QObject::connect(&receiver,
                     &NormReceiver::log,
                     [](QString text)
                     {
                         qDebug() << text;
                     });

    QObject::connect(&receiver,
                     &NormReceiver::progress,
                     [](QString file,
                        qint64 current,
                        qint64 total,
                        double percent)
                     {
                        /* qDebug()
                         << file
                         << current
                         << total
                         << percent;*/
                     });

    QObject::connect(&receiver,
                     &NormReceiver::fileReceived,
                     [](QString path)
                     {
                         qDebug() << "RECEIVED:" << path;
                     });

    receiver.start("/tmp/");

    return a.exec();
}
