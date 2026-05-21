#include <QCoreApplication>
#include <QDebug>
#include<QDateTime>

#include "normsender.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NormSender sender;

    QObject::connect(&sender,
                     &NormSender::log,
                     [](QString text)
                     {
                         QString ts = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
                         qDebug() << ts <<text;

                     });

    QObject::connect(&sender,
                     &NormSender::completed,
                     []()
                     {
                         QString ts = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
                         qDebug() <<ts << "SEND COMPLETED";
                     });

    sender.sendFile("./ab1.deb");

    return a.exec();
}
