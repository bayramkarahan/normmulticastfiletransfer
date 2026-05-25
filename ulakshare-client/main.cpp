#include <QCoreApplication>

#include "multicastfileclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
     MulticastClient client;

      QObject::connect(&client, &MulticastClient::transferProgress,
                      [](int p)
     {
         qDebug() << "Progress:" << p << "%";
     });

     //QTimer::singleShot(0, [&](){
         client.start();
     //});
    return a.exec();
}
