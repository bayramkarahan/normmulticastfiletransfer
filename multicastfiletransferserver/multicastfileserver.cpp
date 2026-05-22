#include "multicastfileserver.h"
#include <QDataStream>

MulticastServer::MulticastServer(QObject *parent)
    : QObject(parent)
{

    transferId = QDateTime::currentMSecsSinceEpoch();

    doneTimer = new QTimer(this);

    doneTimer->setSingleShot(true);

    connect(doneTimer, &QTimer::timeout, this, [this]()
            {
                int totalClient;

                if(allClients.contains("0.0.0.0"))
                    totalClient = allClients.size() - 1;
                else
                    totalClient = allClients.size();

                qDebug() << "Beklenen client:" << totalClient;
                qDebug() << "DONE gelen:" << completedClients.size();

                QSet<QString> missing;

                for(const QString &ip : allClients)
                {
                    if(ip == "0.0.0.0")
                        continue;

                    if(!completedClients.contains(ip))
                        missing.insert(ip);
                }

                if(!missing.isEmpty())
                {
                    qDebug() << "Eksik clientlar:" << missing;
                }

                qDebug() << "Yeni işe geçiliyor...";
                startNextJob();
            });

}

void MulticastServer::log(const QString &msg)
{
    QString ts = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
    qDebug() << ts << msg;
}

void MulticastServer::start()
{
    log("SERVER START");

    socket.setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 16*1024*1024);
    socket.setSocketOption(QAbstractSocket::MulticastTtlOption, 4);
    scanPath(sourcePath);

    if(jobQueue.isEmpty())
    {
        log("No files found");
        return;
    }

    nackSocket.bind(QHostAddress::AnyIPv4, NACK_PORT, QUdpSocket::ShareAddress);

    connect(&nackSocket,
            &QUdpSocket::readyRead,
            this,
            &MulticastServer::processPendingDatagrams);

    /// sendHello();
    calculateNextJobTimeout();
    qDebug() << "Network Type:" << networkType;
    qDebug() << "startNextJobTimeout:" << startNextJobTimeout;
    startNextJob();

}

void MulticastServer::scanPath(const QString &path)
{
    QFileInfo fi(path);

    if(fi.isFile())
    {
        QFile f(path);
        if(!f.open(QIODevice::ReadOnly)) return;

        FileJob job;
        job.absolutePath = path;
        job.relativePath = fi.fileName();
        job.data = f.readAll();
        job.totalPackets = (job.data.size()+PACKET_SIZE-1)/PACKET_SIZE;

        jobQueue.enqueue(job);
    }
    else if(fi.isDir())
    {
        QString basePath = QFileInfo(path).absoluteFilePath();   // 🔥 kritik
        QDir baseDir(basePath);
        QString baseName = QFileInfo(basePath).fileName();       // aaa

        QDirIterator it(basePath, QDir::Files, QDirIterator::Subdirectories);

        while(it.hasNext())
        {
            QString filePath = it.next();

            QFile f(filePath);
            if(!f.open(QIODevice::ReadOnly)) continue;

            FileJob job;
            job.absolutePath = filePath;

            QString rel = baseDir.relativeFilePath(filePath);
            job.relativePath = baseName + "/" + rel;   // doğru çözüm

            job.data = f.readAll();
            job.totalPackets = (job.data.size()+PACKET_SIZE-1)/PACKET_SIZE;

            jobQueue.enqueue(job);
        }
    }
    totalJobCount=jobQueue.size();

}

void MulticastServer::startNextJob()
{
    if(jobQueue.isEmpty())
    {
        log("ALL FILES SENT");
        allFilesSendDone();
        return;
    }

    currentJob = jobQueue.dequeue();
    currentIndex = 0;

    emit clientAllProgressStart();

    completedClients.clear();
    allClients.clear();

    if(!allowedClients.isEmpty())
        allClients = QSet<QString>(allowedClients.begin(),
                                   allowedClients.end());

    sendMeta();

    QTimer::singleShot(200,
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
            QString ts =QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
            qDebug() << ts << text;
        });

        connect(sender,&NormSender::completed,this,[this]()
        {
            QString ts =QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
            qDebug() << ts<< "SEND COMPLETED";
            startNextJob();
        });

        sender->sendFile(currentJob.absolutePath);
    });
}

void MulticastServer::sendMeta()
{
    QByteArray msg;
    QDataStream s(&msg, QIODevice::WriteOnly);

    s << (quint32)META;
    s << transferId;
    s << currentJob.relativePath;
    s << targetTempPath;
    s << targetDestinationPath;
    s << transferType;
    s << transferOverwrite;
    s << (quint32)currentJob.totalPackets;
    s << allowedClients;
    s << sourceBaseName;
    s << sourceType;

    socket.writeDatagram(msg, QHostAddress(MULTICAST_IP), PORT);
    if(!allowedClients.isEmpty())
    {
        allClients = QSet<QString>(allowedClients.begin(), allowedClients.end());
    }
    log("META: " + currentJob.relativePath);

}



void MulticastServer::allFilesSendDone()
{
    log("ALLFILESSENTDONE Gönderildi");
    QByteArray datagram;

    QDataStream s(&datagram, QIODevice::WriteOnly);
    s << (quint32)ALLFILESSENTDONE;
    s << transferId;
    socket.writeDatagram(
        datagram,
        QHostAddress(MULTICAST_IP),PORT);
}

void MulticastServer::processPendingDatagrams()
{
    while(nackSocket.hasPendingDatagrams())
    {
        QByteArray d;
        d.resize(nackSocket.pendingDatagramSize());

        QHostAddress sender;
        nackSocket.readDatagram(d.data(), d.size(), &sender);

        QDataStream s(d);
        quint32 type;
        s >> type;

        if(type == DONE)
        {
            quint64 tid;
            s >> tid;

            if(tid == transferId)
            {
                QString ip = sender.toString();

                // 🔥 CLIENT'I HER ZAMAN EKLE


                if(!completedClients.contains(ip))
                {
                    completedClients.insert(ip);

                    log("CLIENT DONE: " + ip);

                    log(QString("allClients: %1 completed: %2")
                        .arg(allClients.size())
                        .arg(completedClients.size()));


                    emit transferFinished(
                        ip,
                        "server",
                        currentJob.relativePath,
                        QString::number(transferId)
                    );
                    ///qDebug()<<"DOSYA TAMAMLANDI. YENİ DOSYAYA GEÇİLİYOR..";
                    /// doneTimer->start(startNextJobTimeout);
                }

            }
        }

        else if(type == PROGRESS)
        {
            quint64 tid;
            int percent;
            QString  clientHostName;

            s >> tid >> percent>>clientHostName;

            if(tid == transferId)
            {
                QString ip = sender.toString();
                clientProgress[ip] = percent;
                allClients.insert(ip);
                emit clientProgressChanged(ip, percent,clientHostName);
            }
        }

        else if(type == DEB_START)
        {
            quint64 tid;
            s >> tid;

            if(tid == transferId)
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

            if(tid == transferId)
            {
                QString ip = sender.toString();
                emit clientDebInstallDone(ip, status);
            }
        }

        else if(type == SCRIPT_START)
        {
            quint64 tid;
            s >> tid;
            if(tid == transferId)
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
            if(tid == transferId)
            {
                QString ip = sender.toString();
                emit clientScriptInstallDone(ip, status);
            }
        }

    }


}


void MulticastServer::calculateNextJobTimeout()
{
    // Ağ tipi tespiti
    networkType = detectNetworkType();

    // WiFi düzeltmesi
    if(networkType == "wifi")
    {
        // WiFi multicast daha hassas
        burst -= 2;

        // Çok agresif olmasın
        interval += 1;

        startNextJobTimeout = 1000;
    }
    else if(networkType == "ethernet")
    {
        startNextJobTimeout = 1000;
    }
    else
    {
        startNextJobTimeout = 500;
    }


//    qDebug() << "Network Type:" << networkType;
//    qDebug() << "startNextJobTimeout:" << startNextJobTimeout;

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
