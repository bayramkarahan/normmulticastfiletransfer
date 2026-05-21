#include "normsenderworker.h"

#include <QFileInfo>
#include <QDateTime>
#include <QElapsedTimer>
#include <QDebug>

NormSenderWorker::NormSenderWorker(QObject *parent)
    : QObject(parent)
{
    running = false;
}

void NormSenderWorker::send(QString filePath,
                            QString multicastIp,
                            quint16 port)
{
    QString interfaceType = "wifi";

    running = true;

    QFileInfo info(filePath);

    QByteArray ip   = multicastIp.toUtf8();
    QByteArray path = filePath.toUtf8();
    QByteArray name = info.fileName().toUtf8();

    instance = NormCreateInstance();

    if(instance == NORM_INSTANCE_INVALID)
    {
        emit error("NormCreateInstance failed");
        return;
    }

    session = NormCreateSession(instance,
                                ip.constData(),
                                port,
                                1);

    if(session == NORM_SESSION_INVALID)
    {
        emit error("NormCreateSession failed");
        return;
    }

    NormSetRxPortReuse(session, true);

    NormSetMulticastLoopback(session, false);

    NormSessionId sessionId =
        (NormSessionId)
        QDateTime::currentMSecsSinceEpoch();

    /*
     * Başlangıç rate
     */
    double currentRate = 60.0e+06;

    /* =========================
     * WIFI PROFILI
     * ========================= */
    if(interfaceType == "wifi")
    {
        currentRate = 60.0e+06;

        NormSetTxRate(session,
                      currentRate);

        NormSetTxSocketBuffer(session,
                              16*1024*1024);

        NormSetBackoffFactor(session,
                             0.0);

        NormSetGroupSize(session,
                         1);

        NormSetGrttEstimate(session,
                            0.010);

        NormStartSender(session,
                        sessionId,
                        32*1024*1024,
                        1400,
                        128,
                        8);
    }

    /* =========================
     * ETHERNET PROFILI
     * ========================= */
    else if(interfaceType == "ethernet")
    {
        currentRate = 400.0e+06;

        NormSetTxRate(session,
                      currentRate);

        NormSetTxSocketBuffer(session,
                              32*1024*1024);

        NormSetBackoffFactor(session,
                             0.0);

        NormSetGroupSize(session,
                         1);

        NormSetGrttEstimate(session,
                            0.002);

        NormStartSender(session,
                        sessionId,
                        64*1024*1024,
                        1460,
                        256,
                        4);
    }

    /*
     * Dosya enqueue
     */
    NormFileEnqueue(session,
                    path.constData(),
                    name.constData(),
                    name.size());

    /*
     * Bandwidth estimator başlat
     */
    qint64 fileSizeBytes = info.size();

    estimator.startTest(fileSizeBytes);

    emit log("Sender started");

    /*
     * Rate update timer
     */
    QElapsedTimer rateTimer;

    rateTimer.start();

    while(running)
    {
        NormEvent event;

        if(!NormGetNextEvent(instance,
                             &event))
        {
            continue;
        }

        switch(event.type)
        {
        case NORM_TX_QUEUE_EMPTY:

            emit log("QUEUE EMPTY");

            break;

        case NORM_TX_FLUSH_COMPLETED:

            emit log("FLUSH COMPLETED");

            estimator.stopTest();

            emit completed();

            running = false;

            break;

        default:
            break;
        }

        /*
         * Her 1 saniyede bir adaptif rate güncelle
         */
        if(rateTimer.elapsed() >= 5000)
        {
            rateTimer.restart();

            probe.update(session);

            double rtt =
                probe.getRttMs();
            if(interfaceType == "wifi")
            {
                if(rtt > 20.0)
                {
                    currentRate -= 5.0e+06;
                }
                else if(rtt < 10.0)
                {
                    currentRate += 1.0e+06;   // küçük artış
                }

                if(currentRate < 20.0e+06)
                    currentRate = 20.0e+06;

                if(currentRate > 60.0e+06)
                    currentRate = 60.0e+06;
            }
            else if(interfaceType == "ethernet")
            {
                if(rtt > 5.0)
                {
                    currentRate -= 20.0e+06;
                }
                else if(rtt < 1.0)
                {
                    currentRate += 20.0e+06;
                }

                if(currentRate < 100.0e+06)
                    currentRate = 100.0e+06;

                if(currentRate > 900.0e+06)
                    currentRate = 900.0e+06;
            }

            NormSetTxRate(session,
                          currentRate);

            qDebug()
                << "RTT:"
                << rtt
                << "Rate:"
                << currentRate/1e6
                << "Mbps";
        }
    }

    NormStopSender(session);

    NormDestroySession(session);

    NormDestroyInstance(instance);

    session  = NORM_SESSION_INVALID;
    instance = NORM_INSTANCE_INVALID;
}

void NormSenderWorker::stop()
{
    running = false;
}
