#include "multicastfileserver.h"
#include <QDataStream>

MulticastServer::MulticastServer(QObject *parent)
    : QObject(parent)
{
    networkType=detectNetworkType();
    fileMeta.transferId = QDateTime::currentMSecsSinceEpoch();
    log("SERVER START");
    getClientSocket.bind(QHostAddress::AnyIPv4, GET_PORT, QUdpSocket::ShareAddress);
    connect(&getClientSocket,&QUdpSocket::readyRead,this,
            &MulticastServer::processPendingDatagrams);
}

void MulticastServer::log(const QString &msg)
{
    QString ts = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
    qDebug() << ts << msg;
}

void MulticastServer::start()
{
    log(QString("Network Type: %1").arg(networkType));
    if(fileMeta.sourceType=="directory")
    {
        /*QProcess p;
        QStringList args;
        args << "-czf"
             << "/tmp/"+fileMeta.sourceBaseName+".tar.gz"
             << fileMeta.sourcePath;

        QFileInfo info(fileMeta.sourcePath);*/

        QProcess p;
        QStringList args;

        args << "-czf"
             << "/tmp/" + fileMeta.sourceBaseName + ".tar.gz"
             << "-C"
             << fileMeta.sourceBasePath
             << fileMeta.sourceBaseName;

        qDebug() << "Sıkıştırma COMMAND:" << "tar" << args.join(" ");
        p.start("tar", args);

        log("Dizin Sıkıştırıldı.");
        emit updateTotalBarText("Dizin Sıkıştırılıyor");
        p.waitForFinished();
        fileMeta.sourcePath="/tmp/"+fileMeta.sourceBaseName+".tar.gz";
    }
    QFileInfo fi(fileMeta.sourcePath);
    if(fi.isFile())
    {
        QFile f(fileMeta.sourcePath);
        fileMeta.totalFileSize=f.size();
    }

    QTimer::singleShot(1000,this,[this](){

        if(fileMeta.sourcePath.isEmpty())
        {
            log("No files found");
            emit updateTotalBarText("Gönderdirilecek Dosya/Dizin Yok");
            return;
        }
        startSendFile();

    });



}
void MulticastServer::startSendFile()
{
    emit clientAllProgressStart();
    clients.clear();
    sendMeta();

    QTimer::singleShot(500,
                       this,
                       [this]()
    {

        if(sender)
        {
            sender->deleteLater();
            sender = nullptr;
        }

        sender = new NormSender(this);

        connect(sender,&NormSender::log,this,[this](QString text)
        {
            log(text);
        });

        connect(sender,&NormSender::completed,this,[this]()
        {
            log("SEND COMPLETED");
            emit updateTotalBarText("Dosya/Dizin Gönderme Tamamlandı");
            //clients[ip]->completed=false;
            sendDoneAllClient();
        });

        sender->sendFile(fileMeta.sourcePath,MULTICAST_IP,NORM_PORT);

        emit updateTotalBarText("Dosya/Dizin Gönderme Başladı");

    });
}

void MulticastServer::sendMeta()
{
    QUdpSocket sendSocket;
    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    stream << (quint32)META;
    stream << fileMeta.transferId;
    stream << fileMeta.sourcePath;
    stream << fileMeta.targetTempPath;
    stream << fileMeta.targetDestinationPath;
    stream << fileMeta.transferType;
    stream << fileMeta.transferOverwrite;
    stream << fileMeta.allowedClients;
    stream << fileMeta.sourceBaseName;
    stream << fileMeta.sourceType;

    sendSocket.writeDatagram(msg,QHostAddress(MULTICAST_IP),SEND_PORT);
    log("META: " + fileMeta.sourcePath+" id:"+QString::number(fileMeta.transferId));
}

void MulticastServer::sendDoneAllClient()
{
    log("ALLFILESSENTDONE Gönderildi");
    QUdpSocket sendSocket;
    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    stream << (quint32)ALLFILESSENTDONE;
    stream << fileMeta.transferId;
    sendSocket.writeDatagram(msg,QHostAddress(MULTICAST_IP),SEND_PORT);
}

void MulticastServer::sendDiscovery()
{
    log("DISCOVERY Gönderildi");
    QUdpSocket sendSocket;
    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    stream << (quint32)DISCOVERY;
    stream << (quint64)now;
    sendSocket.writeDatagram(msg,QHostAddress(MULTICAST_IP),SEND_PORT);
}

void MulticastServer::processPendingDatagrams()
{
    while(getClientSocket.hasPendingDatagrams())
    {
        QByteArray d;
        d.resize(getClientSocket.pendingDatagramSize());
        QHostAddress sender;
        getClientSocket.readDatagram(d.data(), d.size(), &sender);

        QDataStream s(d);
        quint32 type;
        s >> type;

        if(type == DONE)
        {
            quint64 tid;
            s >> tid;

            if(tid == fileMeta.transferId)
            {
                QString ip = sender.toString();
                if(!clients.contains(ip))
                {
                    Client *client=new Client;
                    client->ip=ip;
                    client->completed=true;
                    clients[ip]=client;
                }else{
                       clients[ip]->completed=true;
                    }
                    ///log("CLIENT DONE: " + ip);
                    emit transferFinished(ip,"server",fileMeta.sourcePath,
                        QString::number(fileMeta.transferId)
                    );
            }
        }
        else if(type == PROGRESS)
        {
            quint64 tid;
            int percent;
            QString  clientHostName;

            s >> tid >> percent>>clientHostName;

            if(tid == fileMeta.transferId)
            {
                QString ip = sender.toString();
                emit clientProgressChanged(ip, percent,clientHostName);

            }
        }
        else if(type == DEB_START)
        {
            quint64 tid;
            s >> tid;

            if(tid == fileMeta.transferId)
            {
                QString ip = sender.toString();
                emit clientDebInstallStart(ip);
            }
        }
        else if(type == DEB_DONE)
        {
            quint64 tid;
            QString status;

            s >> tid >> status;

            if(tid == fileMeta.transferId)
            {
                QString ip = sender.toString();
                emit clientDebInstallDone(ip, status);
            }
        }
        else if(type == SCRIPT_START)
        {
            quint64 tid;
            s >> tid;
            if(tid == fileMeta.transferId)
            {
                QString ip = sender.toString();
                //clientProgress[ip] = percent;
                emit clientScriptInstallStart(ip);
            }
        }
        else if(type == SCRIPT_DONE)
        {
            quint64 tid;
            QString status;

            s >> tid >> status;
           // qDebug()<<"script"<<tid << transferId;
            if(tid == fileMeta.transferId)
            {
                QString ip = sender.toString();
                emit clientScriptInstallDone(ip, status);
            }
        }
        else if(type == DISCOVERY_REPLY)
        {
            qint64 sentTime;
            QString clientHostName;
            s >> sentTime>>clientHostName;
            QString ip = sender.toString();
            qint64 now = QDateTime::currentMSecsSinceEpoch();
            qint64 rtt = now - sentTime;
            if(!clients.contains(ip))
            {
                Client *client=new Client;
                client->ip=ip;
                client->completed=false;
                clients[ip]=client;
                clients[ip]->hostName=clientHostName;
            }else{
                   clients[ip]->completed=false;
                   clients[ip]->hostName=clientHostName;
                }
            //qDebug() << "RTT:" << ip << clientHostName;
        }
    }

}

QString MulticastServer::detectNetworkType()
{
    QString activeIface;
    for (const QNetworkInterface &iface : QNetworkInterface::allInterfaces())
    {
        //log(QString("%1 | %2")
        //   .arg(iface.name())
        // .arg(iface.humanReadableName()));

        // sadece çalışanlar
        if (!(iface.flags() & QNetworkInterface::IsUp) ||
            !(iface.flags() & QNetworkInterface::IsRunning))
            continue;

        // loopback skip
        if (iface.flags() & QNetworkInterface::IsLoopBack)
            continue;

        // IP var mı?
        for (const QNetworkAddressEntry &entry : iface.addressEntries())
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                activeIface = iface.name();
                ///log("ACTIVE IFACE: " + activeIface);

                // 🔥 Linux naming standard
                if (activeIface.startsWith("wl"))
                    return "wifi";

                if (activeIface.startsWith("en") || activeIface.startsWith("eth"))
                    return "ethernet";

                return "unknown";
            }
        }
    }

    return "unknown";
}

void MulticastServer::fileNameDetect(QString path)
{
    QFileInfo info(path);

    if(info.exists())
    {
        fileMeta.sourceBaseName = info.fileName();
        fileMeta.sourceBasePath=info.path();

        if(info.isFile())
        {
            fileMeta.sourceType="file";
        }
        else if(info.isDir())
        {
            fileMeta.sourceType="directory";
        }

    }
    /*qDebug() << ""<<fileMeta.sourcePath;
    qDebug() << ""<<fileMeta.sourceBasePath;
    qDebug() << ""<<fileMeta.sourceBaseName;
    qDebug() << ""<<fileMeta.sourceType;*/
}
