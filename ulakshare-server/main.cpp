#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include<QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>
#include <QFileInfo>

#include "multicastfileserver.h"
#include "progressdialog.h"

// --------------------------------------------------
// ARG STRUCT
// --------------------------------------------------
struct ParsedArgs
{
    QString mode = "project";
    QString target = "tmp";
    QString filePath;
};
// -----------------------------
// TARGET PATH RESOLVER
// -----------------------------
// --------------------------------------------------
// ARG PARSER
// --------------------------------------------------
ParsedArgs parseArguments(QStringList args)
{
    ParsedArgs result;

    args.removeFirst(); // program adı

    for(int i = 0; i < args.size(); i++)
    {
        const QString &arg = args[i];

        if(arg == "--mode" && i + 1 < args.size())
        {
            result.mode = args[i + 1].toLower();
            i++;
        }
        else if(arg == "--target" && i + 1 < args.size())
        {
            result.target = args[i + 1].toLower();
            i++;
        }
        else
        {
            if(result.filePath.isEmpty())
                result.filePath = arg;
        }
    }

    return result;
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   //// qDebug() << "Kullanım:";
   /// qDebug() << "multicast_sender --mode console --target home /dosya";

    // -----------------------------
    // ARG PARSE
    // -----------------------------
    ParsedArgs args = parseArguments(QCoreApplication::arguments());

  /*  qDebug() << "Mode:" << args.mode;
    qDebug() << "Target:" << args.target;
    qDebug() << "FilePath:" << args.filePath;
*/
    // -----------------------------
    // SERVER
    // -----------------------------
    MulticastServer server;
    server.fileMeta.targetTempPath = "/tmp";
    server.fileMeta.targetDestinationPath = "/tmp";

    if(args.target=="deb")
        server.fileMeta.transferType = TransferType::DebInstall;
    if(args.target=="script")
        server.fileMeta.transferType = TransferType::ScriptExecute;

    if(args.target=="desktop")
        server.fileMeta.transferType = TransferType::FileCopyDesktop;
    if(args.target=="home")
        server.fileMeta.transferType = TransferType::FileCopyHome;
    if(args.target=="tmp")
        server.fileMeta.transferType = TransferType::FileCopyTmp;
    if(args.target=="custom")
        server.fileMeta.transferType = TransferType::FileCopyCustom;

    if(args.target=="ask")
    {
        server.fileMeta.transferType = TransferType::FileCopyCustom;
        bool ok = false;
        QString dir = QInputDialog::getText(
            nullptr,
            "Hedef Konum",
            "Dosya nereye kopyalansın?\n"
            "Örnek:\n"
            "/home/user/Desktop\n"
            "/tmp\n"
            "/opt/data",
            QLineEdit::Normal,
            QDir::homePath(),
            &ok
        );

        if(!ok || dir.isEmpty())
        {
            qDebug() << "Kullanıcı iptal etti";
            return -1;
        }

        // (opsiyonel) basit doğrulama
        if(!dir.startsWith("/"))
        {
            qDebug() << "Geçersiz path";
            return -1;
        }
        server.fileMeta.targetDestinationPath = dir;
        qDebug() << "Custom target:" << server.fileMeta.targetDestinationPath;
    }


    server.fileMeta.transferOverwrite = true;
    // -----------------------------
    // MODE LOGIC
    // -----------------------------
    if(args.mode == "rightclick" || args.mode == "console")
    {

        if( args.filePath.isEmpty())
                {
                    qDebug() << "Hata: Dosya yolu yok!";
                    return -1;
                }
        server.fileMeta.sourcePath = args.filePath;

        // herkes kabul
        server.fileMeta.allowedClients.clear();
        server.fileMeta.allowedClients << "0.0.0.0";
    }
    else // project
    {

        server.fileMeta.sourcePath = "./ab.deb";
        server.fileMeta.sourcePath = "./test.sh";
        server.fileMeta.sourcePath = "./aaa";
        server.fileMeta.allowedClients<< "0.0.0.0";
        //server.fileMeta.allowedClients.clear();
    }


      server.fileNameDetect(server.fileMeta.sourcePath);


    /*qDebug() << "SourcePath:" << server.sourcePath;
    qDebug() << "sourceBaseName:" << server.sourceBaseName;
    qDebug() << "sourceType:" << server.sourceType;
    qDebug() << "TargetPath:" << server.targetTempPath;
    qDebug() << "AllowedClients:" << server.allowedClients;
    qDebug() << "TransferType:" << static_cast<int>(server.transferType);
    */// -----------------------------
    // UI
    // -----------------------------
    ProgressDialog *dlg = new ProgressDialog();
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->filePathLE->setText(server.fileMeta.sourceBasePath+"/"+server.fileMeta.sourceBaseName);

    // -----------------------------
    // SIGNALS
    // -----------------------------
    QObject::connect(&server, &MulticastServer::transferFinished,
                     [&](QString sender, QString receiver, QString file, QString id)
    {
        Q_UNUSED(receiver)
        Q_UNUSED(file)
        Q_UNUSED(id)

        //qDebug() << "Client tamamladı:" << sender;
        dlg->markDone(sender);
    });
    QObject::connect(&server,&MulticastServer::updateTotalBarText,
                     [&,&server](QString mesaj)
    {
        dlg->updateTotalBarText(mesaj);
     });

    QObject::connect(&server,&MulticastServer::clientAllProgressStart,
                     [&,&server]()
    {
        dlg->allProgressStart(server.fileMeta.totalFileSize);
     });

    QObject::connect(&server, &MulticastServer::allTransferFinished,
                     [&]()
    {
        qDebug() << "Tüm transfer tamamlandı";
        QTimer::singleShot(5000, qApp, []()
        {
            ///qApp->quit();
        });
    });

    QObject::connect(&server,&MulticastServer::clientProgressChanged,
                     [&,&server](QString ip, int percent,QString clientHostName)
    {
        dlg->updateProgress(ip, percent,clientHostName);
    });

    QObject::connect(&server,&MulticastServer::clientDebInstallStart,
                     [&](QString ip)
    {
        dlg->markDebInstallStart(ip);
    });
    QObject::connect(&server,&MulticastServer::clientDebInstallDone,
                     [&](QString ip, QString status)
    {
        dlg->markDebInstallDone(ip, status);
    });
    QObject::connect(&server,&MulticastServer::clientScriptInstallStart,
                     [&](QString ip)
    {
        dlg->markScriptInstallStart(ip);
    });
    QObject::connect(&server,&MulticastServer::clientScriptInstallDone,
                     [&](QString ip, QString status)
    {
        dlg->markScriptInstallDone(ip, status);
    });
    // -----------------------------
    // START
    // -----------------------------
    QObject::connect(dlg,&ProgressDialog::updateSelectClients,
                     [&,&server]()
    {
        server.fileMeta.allowedClients.clear();
        //qDebug() << "main updateSelectClients butonuna basıldı";
        int add=0;
        for(ClientRow *client : dlg->clients)
        {
            if(client->select->isChecked())
                server.fileMeta.allowedClients<<client->ip->text();

            //qDebug() << "allowedClient"<<client->ip->text()<<client->select->isChecked();
            add++;
        }
        if(add==0) server.fileMeta.allowedClients<<"0.0.0.0";

    });

    QObject::connect(dlg,
                     &ProgressDialog::sendFileTransferAllDone,
                     [&,&server](qint64 averageTime)
    {
        if(dlg->totalBar->value() > 90 && !server.transferAllDone)
        {
            server.transferAllDone = true;

            QTimer::singleShot((averageTime*3), &server, [&server,averageTime]()
            {
                ///qDebug() << "bitti gönder....."<<averageTime;
                server.transferAllDone = false;
                server.sendDoneAllClient();
            });
        }
    });

    QObject::connect(dlg,&ProgressDialog::startTransfer,
                     [&,&server](TransferType type)
    {
        //qDebug() << "main Gönder butonuna basıldı"<<"transferType"<<static_cast<int>(type);
        //qDebug() << "allowedClients"<<server.fileMeta.allowedClients;
        //return;
        server.fileMeta.transferType=type;
        if(!server.fileMeta.allowedClients.isEmpty())
        {
            server.fileNameDetect(server.fileMeta.sourceBasePath+"/"+
                                  server.fileMeta.sourceBaseName);
                 /*qDebug()<<"destTargetPath"<<server.fileMeta.targetDestinationPath;
                 qDebug()<<"sourceBaseName"<<server.fileMeta.sourceBaseName;
                 qDebug()<<"sourceBasePath"<<server.fileMeta.sourceBasePath;
                 qDebug()<<"sourcePath"<<server.fileMeta.sourcePath;
                 qDebug()<<"sourceType"<<server.fileMeta.sourceType;
                 qDebug()<<"tmpTargetPath"<<server.fileMeta.targetTempPath;
                 qDebug()<<"transferId"<<server.fileMeta.transferId;*/
            server.start();
        }
    });

    QObject::connect(dlg,&ProgressDialog::sendDiscovery,
                     [&,&server]()
    {
        //qDebug() << "main Gönder butonuna basıldı";
        server.sendDiscovery();
        QTimer::singleShot(50, [dlg,&server]()
        {
            //qDebug() <<"helloClients"<<server.helloClients.values();
            for(Client* item : server.clients)
            {
                dlg->updateProgress(item->ip, item->percent, item->hostName);
            }
        });

    });

    QObject::connect(dlg,&ProgressDialog::updatePath,
                     [&,&server](QString path)
    {
        server.fileNameDetect(path);
    });
    /*dlg->updateProgress("192.168.1.190", 20,"190");
    dlg->updateProgress("192.168.1.191", 30,"191");
    dlg->updateProgress("192.168.1.192", 60,"192");
    dlg->updateProgress("192.168.1.193", 70,"193");
    dlg->updateProgress("192.168.1.194", 80,"194");*/

    dlg->show();
    dlg->sendDiscovery();
    return a.exec();
}
