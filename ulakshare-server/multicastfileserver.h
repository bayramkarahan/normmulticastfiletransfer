#pragma once
#include<QCoreApplication>
#include <QObject>
#include <QUdpSocket>
#include <QFile>
#include <QVector>
#include <QThread>
#include <QDateTime>
#include <QSet>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QDirIterator>
#include <QQueue>
#include "normsender.h"
#include<QProcess>
#include<type.h>
#define MULTICAST_IP "239.255.7.1"
#define SEND_PORT 40004
#define GET_PORT 40005
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
/*enum class TransferType {
    FileCopyDesktop,
    FileCopyHome,
    FileCopyTmp,
    FileCopyCustom,
    DebInstall,
    ScriptExecute
};*/
struct FileMeta
{
    quint32 type;
    quint64 transferId;
    QString sourcePath;
    QString sourceType;
    QString sourceBaseName;
    QString sourceBasePath;

    QString targetTempPath;
    QString targetDestinationPath;
    TransferType transferType;
    bool transferOverwrite;
    QStringList allowedClients;
    quint64 totalFileSize;


};


struct Client
{
    QString ip;
    QString hostName;
    int percent;
    bool completed;
};
class MulticastServer : public QObject
{
    Q_OBJECT
public:
    explicit MulticastServer(QObject *parent = nullptr);
    void start();
    void sendDiscovery();
    void sendDoneAllClient();
    FileMeta fileMeta;
    QMap<QString, Client*> clients;
    bool transferAllDone = false;
    void fileNameDetect(QString path);


signals:
    void updateTotalBarText(QString mesaj);
    void clientAllProgressStart();
    void clientProgressChanged(QString client, int percent,QString clientHostName);
    void clientDebInstallStart(QString client);
    void clientDebInstallDone(QString client, QString status);
    void clientScriptInstallStart(QString client);
    void clientScriptInstallDone(QString client, QString status);
    void allTransferFinished();
    void transferFinished(QString sender,
                             QString receiver,
                             QString file,
                             QString id);
private slots:
    void processPendingDatagrams();
    QString detectNetworkType();

private:
    void log(const QString &msg);
    void sendMeta();
    void startSendFile();

    QUdpSocket getClientSocket;
    QString networkType="";
    NormSender *sender = nullptr;

};
