#ifndef SENSORUDPCTL_H
#define SENSORUDPCTL_H

/* INCLUDES */
#include "sensorudpctl_global.h"
#include <vector>
#include <map>

/****************************************//**
 * @brief Receiver for Udp messages
 * from ESP8226+MPU6050
 * @date 30.07.2021
 * @author Segaman
 *******************************************/

namespace SensorUdpCtl
{
void init();
double getDivider();
void setDivider (const double &v);
const char *getSensorsList();
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
#endif // SENSORUDPCTL_H
