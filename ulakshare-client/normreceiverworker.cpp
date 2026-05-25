#include "normreceiverworker.h"

#include <QDir>

NormReceiverWorker::NormReceiverWorker(QObject *parent)
    : QObject(parent)
{
    running = false;
}

void NormReceiverWorker::startReceiver(QString cacheDir,
                                       QString multicastIp,
                                       quint16 port)
{
    interfaceType=detectNetworkType();
    qDebug()<<"interfaceType:"<<interfaceType;

    running = true;

    QByteArray ip = multicastIp.toUtf8();

    QByteArray cache = cacheDir.toUtf8();

    instance = NormCreateInstance();

    if(instance == NORM_INSTANCE_INVALID)
    {
        emit error("NormCreateInstance failed");
        return;
    }

    session = NormCreateSession(instance,
                                ip.constData(),
                                port,
                                NORM_NODE_ANY);

    NormSetRxPortReuse(session, true);
    NormSetMulticastLoopback(session, false);
    ///NormSetRxLoss(session, 10.0);

    if(!NormSetCacheDirectory(instance,
                               cache.constData()))
    {
        emit error("NormSetCacheDirectory failed");
        return;
    }
    //if(interfaceType == "wifi")
    NormSetRxSocketBuffer(session,16*1024*1024);
    NormStartReceiver(session,32*1024*1024);

  emit log("Receiver started");

    while(running)
    {
        NormEvent event;

        ///if(!NormGetNextEvent(instance, &event))
        if(!NormGetNextEvent(instance,
                             &event,
                             true))
            continue;
         switch(event.type)
        {

        case NORM_REMOTE_SENDER_NEW:

            emit log("REMOTE_SENDER_NEW");
            break;

        case NORM_REMOTE_SENDER_ACTIVE:
            emit log("REMOTE_SENDER_ACTIVE");
            emit senderActive();
            break;

        case NORM_REMOTE_SENDER_INACTIVE:
            emit log("REMOTE_SENDER_INACTIVE");
            emit senderInactive();
            break;

        case NORM_RX_OBJECT_NEW:

            emit log("RX_OBJECT_NEW");
             if(!allowed)
                {
                    emit log("REJECT OBJECT");

                    NormObjectCancel(event.object);

                    /**************************/
                    char path[2048];
                    if(NORM_OBJECT_FILE ==
                    NormObjectGetType(event.object))
                    {
                        NormFileGetName(event.object,
                                    path,
                                    2048);
                        //emit log(QString("remove TEMP FILE: %1").arg(path));
                        QFile::remove(path);
                    }
                    /***********************************/
                    break;
                }
            break;

        case NORM_RX_OBJECT_INFO:

            emit log("RX_OBJECT_INFO");

            break;

        case NORM_RX_OBJECT_UPDATED:
        {
            NormSize total =
                NormObjectGetSize(event.object);

            NormSize completed =
                total -
                NormObjectGetBytesPending(event.object);

            double percent =
                100.0 *
                ((double)completed /
                 (double)total);

            char info[1024];

            unsigned short len =
                NormObjectGetInfo(event.object,
                                  info,
                                  1023);

            info[len] = 0;

            emit progress(QString(info),
                          completed,
                          total,
                          percent);

            break;
        }

        case NORM_RX_OBJECT_COMPLETED:
        {
            emit log("RX_OBJECT_COMPLETED");

            char path[2048];

            if(NORM_OBJECT_FILE ==
                NormObjectGetType(event.object))
            {
                NormFileGetName(event.object,
                                path,
                                2048);

                emit fileReceived(QString(path));
            }

            break;
        }

        case NORM_RX_OBJECT_ABORTED:

            emit log("RX_OBJECT_ABORTED");

            break;

        default:
            break;
        }
    }

    NormStopReceiver(session);

    NormDestroySession(session);

    NormDestroyInstance(instance);

    session = NORM_SESSION_INVALID;

    instance = NORM_INSTANCE_INVALID;
}

void NormReceiverWorker::stop()
{
    running = false;
}

QString NormReceiverWorker::detectNetworkType()
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
               /// log("ACTIVE IFACE: " + activeIface);

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
