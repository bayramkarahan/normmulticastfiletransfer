#pragma once
#include <QObject>
#include <QUdpSocket>
#include <QVector>
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QDateTime>
#include <QFileInfo>
#include <QNetworkInterface>
#include<QDir>
#include<QStandardPaths>
#include<QProcess>
#include <unistd.h>
#include <sys/stat.h>
#include <QDirIterator>
#include<userprivilegehelper.h>
#include "normreceiver.h"

#define MULTICAST_IP "239.255.7.1"
#define GET_PORT 40004
#define SEND_PORT 40005
#define NORM_PORT 40006

#define META 0
#define DATA 1
#define END 2
#define NACK 3
#define DONE 4
#define PROGRESS 5
#define DEB_START         6
#define DEB_DONE          7
#define SCRIPT_START      8
#define SCRIPT_DONE       9
#define DISCOVERY 10
#define DISCOVERY_REPLY 11
#define ALLFILESSENTDONE 12

enum class TransferType {
    FileCopyDesktop,
    FileCopyHome,
    FileCopyTmp,
    FileCopyCustom,
    DebInstall,
    ScriptExecute
};
struct FileMeta
{
    quint32 type;
    quint64 transferId;  
    QString sourcePath;
    QString tmpTargetPath;
    QString destTargetPath;
    QString sourceBaseName;
    QString sourceType;
    QString normTempFileName;
    bool overwrite;
    TransferType transferType;
    QStringList allowedClients;
    bool allowed;
};

class MulticastClient : public QObject
{
    Q_OBJECT
public:
    QString clientHostName;
    explicit MulticastClient(QObject *parent=nullptr);
    void start();
    QString resolveTargetPath(TransferType type, const QString& customPath = "");
    void doneProcess();

    bool copyFile(const QString& src, const QString& dstDir, bool overwrite);
    bool copyDirectory(const QString &sourceDir,const QString &targetDir,
                       bool overwrite);
    void setPermissionsRecursive(const QString &path, uid_t uid, gid_t gid);

    QString getDesktopPathFromHome(const QString &home);
    void debInstallStart(quint64 tid);
    void debInstallDone(QString status, quint64 tid);
    void scriptInstallStart(quint64 tid);
    void scriptInstallDone(QString status,quint64 tid);
    void discoveryReply(qint64 timestamp);

signals:
    void fileReceived(QString tmpPath,
                      QString destPath,
                      QString fileName,
                      QString transferId,
                      TransferType transferType,
                      bool transferOverwrite);
    void transferProgress(int percent);

private slots:
    void log(const QString &msg);
    void processDatagram(const QByteArray &datagram, const QHostAddress &sender);
    void resetState();
    void sendDone();
    void processPendingDatagrams();
    void sendProgress(int percent);
    QString getLocalIp();
private:
    QUdpSocket getServerSocket;
    QHostAddress serverAddress;

    // META

    FileMeta fileMeta;
    int lastPercent;
    bool sendAllFilesState=false;
    NormReceiver* receiver = nullptr;
};
