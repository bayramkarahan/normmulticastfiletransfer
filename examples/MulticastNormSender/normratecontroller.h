#pragma once

#include <QObject>

class NormRateController : public QObject
{
    Q_OBJECT

public:
    explicit NormRateController(QObject *parent = nullptr);

    void update(double rttMs, double bandwidthMbps);

    double getRateBps() const;

signals:
    void rateChanged(double bps);

private:
    double rate = 30e6;
};