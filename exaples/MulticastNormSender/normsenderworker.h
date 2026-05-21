#pragma once

#include <QObject>
#include <QAtomicInt>

#include <normApi.h>
#include<normnetworkprobe.h>
#include<normbandwidthestimator.h>
#include<normratecontroller.h>


class NormSenderWorker : public QObject
{
    Q_OBJECT

public:
    explicit NormSenderWorker(QObject *parent = nullptr);

public slots:
    void send(QString filePath,
              QString multicastIp,
              quint16 port);

    void stop();

signals:
    void log(QString text);

    void completed();

    void error(QString text);

private:
    QAtomicInt running;

    NormInstanceHandle instance = NORM_INSTANCE_INVALID;
    NormSessionHandle session = NORM_SESSION_INVALID;
    NormNetworkProbe probe;
    NormRateController controller;
    NormBandwidthEstimator estimator;
};