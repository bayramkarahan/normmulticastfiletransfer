#include "normratecontroller.h"

NormRateController::NormRateController(QObject *parent)
    : QObject(parent)
{
}

void NormRateController::update(double rttMs,
                                double bandwidthMbps)
{
    double newRate = bandwidthMbps * 0.6 * 1e6;
    // Mbps → bps

    // RTT penalty
    if(rttMs > 30)
        newRate *= 0.5;
    else if(rttMs > 10)
        newRate *= 0.7;
    else if(rttMs > 5)
        newRate *= 0.85;

    // clamp
    if(newRate < 5e6)
        newRate = 5e6;

    if(newRate > 300e6)
        newRate = 300e6;

    rate = newRate;

    emit rateChanged(rate);
}

double NormRateController::getRateBps() const
{
    return rate;
}