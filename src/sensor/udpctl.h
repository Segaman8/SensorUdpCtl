#ifndef SENSORUDPCTL_H
#define SENSORUDPCTL_H

/* INCLUDES */
#include "global.h"
#include <vector>
#include <map>

/* NAMESPACE */
namespace Sensor
{

/****************************************//**
 * @brief Receiver for Udp messages
 * from ESP8226+MPU6050
 * @ingroup groupSensor
 * @date 31.07.2021
 * @author Segaman
 *******************************************/

namespace UdpCtl
{
/// initialize udp server to receive packets
void init();

/// get vector divide value
double getDivider();

/// set vector divide value
void setDivider (const double &v);

/// get string state info report
const char *getSensorsList();

/// get data from certain sensor by id
bool getData (
  /* in  */ const int &id,
  /* out */ double &acx,
  /* out */ double &acy,
  /* out */ double &acz,
  /* out */ double &gyx,
  /* out */ double &gyy,
  /* out */ double &gyz
);

/// @}
};
/*-----------------------------------------*/
};

/*-----------------------------------------*/
#endif // SENSORUDPCTL_H
