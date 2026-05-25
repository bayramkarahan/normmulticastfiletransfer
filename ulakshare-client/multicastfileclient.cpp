#include "multicastfileclient.h"

MulticastClient::MulticastClient(QObject *parent)
    : QObject(parent)
{
    lastPercent = -1;
    QFile file("/etc/hostname");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        clientHostName = QString::fromUtf8(file.readAll()).trimmed();

        file.close();
    }
}

void MulticastClient::log(const QString &msg)
{
    QString ts = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
    qDebug() << ts << msg;
}

QString MulticastClient::getLocalIp()
{
    for (const QNetworkInterface &iface : QNetworkInterface::allInterfaces())
    {
        if (!(iface.flags() & QNetworkInterface::IsUp) ||
            !(iface.flags() & QNetworkInterface::IsRunning))
            continue;

        for (const QNetworkAddressEntry &entry : iface.addressEntries())
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol &&
                entry.ip() != QHostAddress::LocalHost)
            {
                return entry.ip().toString();
            }
        }
    }
    return "";
}

void MulticastClient::start()
{
    log("CLIENT START");

    getServerSocket.setSocketOption(
        QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024);

    bool ok =
        getServerSocket.bind(QHostAddress::AnyIPv4,GET_PORT,
                    QUdpSocket::ShareAddress);

    ////qDebug() << "bind:" << ok;

    getServerSocket.joinMulticastGroup(
        QHostAddress(MULTICAST_IP));

    connect(&getServerSocket,
            &QUdpSocket::readyRead,
            this,
            &MulticastClient::processPendingDatagrams,
            Qt::UniqueConnection);

    if(receiver)
    {
        receiver->deleteLater();
        receiver = nullptr;
    }

    receiver = new NormReceiver(this);

    connect(receiver,
            &NormReceiver::log,
            this,
            [](QString text)
    {
        qDebug() << text;
    });

    connect(receiver,
            &NormReceiver::progress,
            this,
            [this](QString file,
               qint64 current,
               qint64 total,
               double percent_)
    {
        ///qDebug()<< file<< current<< total<< percent_;
        int percent=percent_;

        if(percent % 10 == 0 && percent != lastPercent)
        {
            lastPercent = percent;
            ///emit transferProgress(percent);
            sendProgress(percent);
        }
    });

    connect(receiver,
            &NormReceiver::fileReceived,
            this,
            [this](QString path)
    {
        qDebug() << "RECEIVED:" << path;
        fileMeta.normTempFileName=path;
        sendDone();
    });

  receiver->start("/tmp/",MULTICAST_IP,NORM_PORT);

}

void MulticastClient::processDatagram(const QByteArray &datagram, const QHostAddress &sender)
{
    QDataStream metaStream(datagram);
    quint32 type;
    metaStream >> type;

    // DISCOVERY
    if(type == DISCOVERY)
    {
        qint64 sentTime;
        metaStream >> sentTime;
        log("DISCOVERY Geldi.");
        discoveryReply(sentTime);
     }

    if(type == ALLFILESSENTDONE&&fileMeta.allowed)
    {
        if(!sendAllFilesState)
        {
            quint64 tid;
            metaStream >> tid;
            log("ALLFILESSENTDONE Geldi.");
            sendAllFilesState=true;

        QTimer::singleShot(1000, this, [tid,this]()
        {
            log("DOSYA İLE İLGİLİ İŞLEMLER YAPILACAK");
            sendAllFilesState=false;
            doneProcess();
         });

        }
     }

    if(type == META)
    {
        resetState();
        emit transferProgress(0);
        lastPercent = -1;
        quint64 tid;
        QString getSourcePath, getTempDestPath, getDestPath,sourceBaseName,sourceType;

        TransferType transferType;
        bool overwrite;
        QStringList list;

        metaStream >> tid >> getSourcePath
                >> getTempDestPath >>getDestPath>> transferType
                >> overwrite >> list
                >> sourceBaseName >> sourceType;

        fileMeta.transferId = tid;
        fileMeta.sourcePath = getSourcePath;
        fileMeta.tmpTargetPath = getTempDestPath;
        fileMeta.destTargetPath=getDestPath;
        fileMeta.overwrite = overwrite;
        fileMeta.transferType = transferType;
        fileMeta.sourceBaseName= sourceBaseName;
        fileMeta.sourceType=sourceType;
        fileMeta.allowedClients = list;
        /*qDebug()<<"transferId"<<fileMeta.transferId;
        qDebug()<<"sourcePath"<<fileMeta.sourcePath;
        qDebug()<<"sourceBaseName"<<fileMeta.sourceBaseName;
        qDebug()<<"tmpTargetPath"<<fileMeta.tmpTargetPath;
        qDebug()<<"destTargetPath"<<fileMeta.destTargetPath;
        qDebug()<<"overwrite"<<fileMeta.overwrite;
        qDebug()<<"transferType"<<static_cast<int>(transferType);
        qDebug()<<"sourceType"<<fileMeta.sourceType;
        qDebug()<<"allowedClients"<<fileMeta.allowedClients;*/

        QString myIp = getLocalIp();
        fileMeta.allowed =fileMeta.allowedClients.contains(myIp)
               || fileMeta.allowedClients.contains("0.0.0.0");

        if(!fileMeta.allowed)
        {
            log(QString("NOT IN LIST (%1) → IGNORING").arg(myIp));
            return;
        }


        log(QString("META: %1 (%2) overwrite=%3 allowed=%4")
                .arg(fileMeta.sourcePath)
                .arg(static_cast<int>(transferType))
                .arg(overwrite).arg(fileMeta.allowed));

        receiver->setAllowed(fileMeta.allowed);
        return;
    }

    // liste dışıysa hiçbir şey yapma
    if(!fileMeta.allowed)
        return;


    FileMeta header;
    metaStream >> header.transferId;
    if(header.transferId != fileMeta.transferId)
        return;

 }

void MulticastClient::discoveryReply(qint64 timestamp)
{
    log("DISCOVERY_REPLY gönderildi");
    //qDebug()<<"clientHostName"<<clientHostName;
    QUdpSocket sendSocket;
    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    stream << (quint32)DISCOVERY_REPLY;
    stream << (quint64)timestamp;
    stream << clientHostName;

    sendSocket.writeDatagram(msg, serverAddress, SEND_PORT);
}

void MulticastClient::sendDone()
{
    log("sendDone");
    QUdpSocket sendSocket;
    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    stream << (quint32)DONE;
    stream << fileMeta.transferId;
    sendSocket.writeDatagram(msg, serverAddress, SEND_PORT);
}

void MulticastClient::debInstallStart(quint64 tid)
{
      log("debInstallStart");
    QUdpSocket sendSocket;

    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);

    stream << (quint32)DEB_START;
    stream << tid;

    sendSocket.writeDatagram(msg, serverAddress, SEND_PORT);
}

void MulticastClient::debInstallDone(QString status,quint64 tid)
{
    log("debInstallDone");
    QUdpSocket sendSocket;

    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);

    stream << (quint32)DEB_DONE;
    stream << tid;
    stream << status;

    sendSocket.writeDatagram(msg, serverAddress, SEND_PORT);
}

void MulticastClient::scriptInstallStart(quint64 tid)
{
    log("scriptInstallStart");
    QUdpSocket sendSocket;

    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);

    stream << (quint32)SCRIPT_START;
    stream << tid;

    sendSocket.writeDatagram(msg, serverAddress, SEND_PORT);
}

void MulticastClient::scriptInstallDone(QString status, quint64 tid)
{
    log("scriptInstallDone");
    QUdpSocket sendSocket;

    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);

    stream << (quint32)SCRIPT_DONE;
    stream << tid;
    stream << status;

    sendSocket.writeDatagram(msg, serverAddress, SEND_PORT);
}

void MulticastClient::resetState()
{
    fileMeta=FileMeta();
    fileMeta.transferId = 0;
    fileMeta.allowed = true;
    log("READY FOR NEXT FILE");
}

void MulticastClient::sendProgress(int percent)
{
    QUdpSocket sendSocket;
    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    stream << (quint32)PROGRESS;
    stream << fileMeta.transferId;
    stream << percent;
    stream << clientHostName;
    sendSocket.writeDatagram(msg, serverAddress, SEND_PORT);
}

QString MulticastClient::resolveTargetPath(TransferType type, const QString& customPath)
{
    UserPrivilegeHelper helper;
    SessionInfo info = helper.getActiveSessionInfo();
    QString home = info.home;
    QString desktop = getDesktopPathFromHome(home);
    /* if (info.valid) {
         qDebug() << "Kullanıcı:" << info.username;
         qDebug() << "UID/GID:" << info.uid << "/" << info.gid;
         qDebug() << "Home:" << info.home;
         qDebug() << "Display:" << info.display;
         qDebug() << "Type:" << info.type;
         qDebug() << "Service:" << info.service;
     }*/

    //QString user = getActiveUser();
    //qDebug() << "Active user:" << user;
    //QString home="/home/"+user+"/";


    switch(type)
    {
        case TransferType::FileCopyDesktop:
            return desktop;

        case TransferType::FileCopyHome:
            return home;

    case TransferType::FileCopyTmp:
        return "/tmp";

        case TransferType::FileCopyCustom:
            return customPath;

        default:
            return "/tmp";
    }
}

QString  MulticastClient::getDesktopPathFromHome(const QString &home)
{
    QFile file(home + "/.config/user-dirs.dirs");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString line = file.readLine();

            if(line.startsWith("XDG_DESKTOP_DIR"))
            {
                int firstQuote = line.indexOf('"');
                int lastQuote = line.lastIndexOf('"');

                if(firstQuote != -1 && lastQuote != -1 && lastQuote > firstQuote)
                {
                    QString path = line.mid(firstQuote + 1, lastQuote - firstQuote - 1);
                    path.replace("$HOME", home);
                    return path;
                }
            }
        }
    }

    // fallback
    return home + "/Desktop";
}

bool MulticastClient::copyFile(const QString& src, const QString& dst, bool overwrite)
{
    ///qDebug()<<"copyFile"<<src<<dst;
    //QFileInfo info(src);
    //QString dst = dstDir + "/" + info.fileName();

   /* if(dstDir!="/tmp"){
    if(overwrite && QFile::exists(dst))
        QFile::remove(dst);
    }*/
    QFile::copy(src, dst);
    QFile::remove(src);
    return true;
}

bool MulticastClient::copyDirectory(const QString &sourceDir,
                                    const QString &targetDir,
                                    bool overwrite)
{
    QDir src(sourceDir);

    if(!src.exists())
        return false;

    QDir target(targetDir);

    if(!target.exists())
    {
        if(!QDir().mkpath(targetDir))
            return false;
    }

    QFileInfoList entries = src.entryInfoList(
                QDir::NoDotAndDotDot |
                QDir::Files |
                QDir::Dirs);

    for(const QFileInfo &entry : entries)
    {
        QString srcPath = entry.absoluteFilePath();
        QString dstPath = targetDir + "/" + entry.fileName();

        if(entry.isDir())
        {
            if(!copyDirectory(srcPath, dstPath, overwrite))
                return false;
        }
        else
        {
            if(overwrite && QFile::exists(dstPath))
                QFile::remove(dstPath);

            if(!QFile::copy(srcPath, dstPath))
                return false;
        }
    }

    // KOPYA BİTTİKTEN SONRA SİLİNİYO
    return QDir(sourceDir).removeRecursively();
}

void MulticastClient::processPendingDatagrams()
{
    while(getServerSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(getServerSocket.pendingDatagramSize());

        QHostAddress sender;

        getServerSocket.readDatagram(datagram.data(),
                            datagram.size(),
                            &sender);

        serverAddress = sender;

        processDatagram(datagram, sender);
    }
}

void MulticastClient::setPermissionsRecursive(const QString &path, uid_t uid, gid_t gid)
{
    QFileInfo info(path);

    // Ana dosya/dizin
    ::chown(path.toUtf8().constData(), uid, gid);

    if(info.isDir())
        ::chmod(path.toUtf8().constData(), 0755);
    else
        ::chmod(path.toUtf8().constData(), 0755);

    // Alt içerikler
    QDirIterator it(path,
                    QDir::NoDotAndDotDot |
                    QDir::AllEntries,
                    QDirIterator::Subdirectories);

    while(it.hasNext())
    {
        QString p = it.next();
        QFileInfo fi(p);

        ::chown(p.toUtf8().constData(), uid, gid);

        if(fi.isDir())
            ::chmod(p.toUtf8().constData(), 0755);
        else
            ::chmod(p.toUtf8().constData(), 0755);
    }
}

void MulticastClient::doneProcess()
{
    UserPrivilegeHelper helper;
    SessionInfo userInfo = helper.getActiveSessionInfo();

     qDebug()<<"********************************";
    /* qDebug()<<"allowed"<<fileMeta.allowed;
     qDebug()<<"destTargetPath"<<fileMeta.destTargetPath;
     qDebug()<<"normTempFileName"<<fileMeta.normTempFileName;
     qDebug()<<"sourceBaseName"<<fileMeta.sourceBaseName;
     qDebug()<<"sourcePath"<<fileMeta.sourcePath;
     qDebug()<<"sourceType"<<fileMeta.sourceType;
     qDebug()<<"tmpTargetPath"<<fileMeta.tmpTargetPath;
     qDebug()<<"transferId"<<fileMeta.transferId;
*/
     qDebug()<<"********************************";
    QString sourcePath = fileMeta.normTempFileName;
    QString finalDstPath=resolveTargetPath(fileMeta.transferType,fileMeta.destTargetPath);
    qDebug()<<"finalDstPath pre:"<<finalDstPath;
    QString finalTargetPath = finalDstPath + "/" + fileMeta.sourceBaseName;
    qDebug()<<"sourcePath"<<sourcePath;
    qDebug()<<"finalTargetPath"<<finalTargetPath;
    qDebug()<<"sourceType"<<fileMeta.sourceType;


    if(fileMeta.sourceType == "directory")
    {
        QDir dir(finalTargetPath);
        /** Varsa sil */
        dir.removeRecursively();


        QProcess p;
        //p.setWorkingDirectory("/tmp");

        QStringList args;

        args << "-xzf"
             << sourcePath
             << "-C"
             << "/tmp";

        qDebug() << "COMMAND:" << "tar" << args.join(" ");

        p.start("tar", args);
        log("Dizin Arşivi Açılıyor..");
        p.waitForFinished();
        log("Dizin Arşivi Açıldı.");
        QFile::remove(sourcePath);

        if(finalDstPath!="/tmp"){
        copyDirectory("/tmp/"+fileMeta.sourceBaseName, finalTargetPath, fileMeta.overwrite);
        }

    }
    else
    {
        QFileInfo fi(finalTargetPath);

        QDir().mkpath(fi.path());

        copyFile(sourcePath, finalTargetPath, fileMeta.overwrite);

    }
    setPermissionsRecursive(finalTargetPath, userInfo.uid, userInfo.gid);

    /**************************************************************/
    switch(fileMeta.transferType)
    {
        case TransferType::FileCopyDesktop:
        case TransferType::FileCopyHome:
        case TransferType::FileCopyCustom:
        {
        break;
        }

       case TransferType::DebInstall:
        {
            debInstallStart(fileMeta.transferId);


            QProcess esc;

            esc.start("systemd-escape",
                      QStringList() << finalTargetPath);

            esc.waitForFinished();

            QString escapedPath =
                QString::fromUtf8(
                    esc.readAllStandardOutput()).trimmed();

            QString serviceName =
                QString("multicastdebinstaller@%1.service")
                .arg(escapedPath);

            QProcess p;

            p.start("systemctl",
                    QStringList() << "start"
                                  << serviceName);

            p.waitForFinished();
            debInstallDone(p.exitCode() == 0 ? "0" : "1",fileMeta.transferId);

            break;
        }

        case TransferType::ScriptExecute:
        {


            scriptInstallStart(fileMeta.transferId);
            QProcess esc;

            esc.start("systemd-escape",
                      QStringList() << finalTargetPath);

            esc.waitForFinished();

            QString escapedPath =
                QString::fromUtf8(
                    esc.readAllStandardOutput()).trimmed();

            QString serviceName =
                QString("multicastscriptexec@%1.service")
                    .arg(escapedPath);
            qDebug()<<"escapedPath"<<escapedPath;
            qDebug()<<"escapedPath"<<serviceName;

            QProcess p;
            p.start("systemctl",
                    QStringList() << "start"
                                  << serviceName);

            p.waitForFinished();
            scriptInstallDone(p.exitCode() == 0 ? "0" : "1",fileMeta.transferId);
            break;
        }
    }
resetState();
}
