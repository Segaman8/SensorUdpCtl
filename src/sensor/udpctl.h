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

/// finish udp socket thread
/// @return true when thread successfully stopped, false if there is no thread present
bool deinit();

/// get string state info report
const char *getInfo();

/// get data from certain sensor by id
bool getYpr (
  /* in  */ const int &id,
  /* out */ float *roll,
  /* out */ float *pitch,
  /* out */ float *yaw
);

bool getAcc (
  /* in  */ const int &id,
  /* out */ float *acx,
  /* out */ float *acy,
  /* out */ float *acz
);

bool getGy (
  /* in  */ const int &id,
  /* out */ float *gyx,
  /* out */ float *gyy,
  /* out */ float *gyz
);

/// get amount of udp connected sensors
int getSize();

/// get available sensor ids
int getKeys (const int **dest);

/// @}
};
/*-----------------------------------------*/
};

/*-----------------------------------------*/
#endif // SENSORUDPCTL_H
