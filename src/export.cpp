/* INCLUDES */
#include "sensor/udpctl.h"
#include "global.h"

/* EXPORT */
SENSORUDPCTL_EXPORT void init()
{
  Sensor::UdpCtl::init();
}

SENSORUDPCTL_EXPORT void deinit()
{
  Sensor::UdpCtl::deinit();
}

SENSORUDPCTL_EXPORT const char *getInfo()
{
  return Sensor::UdpCtl::getInfo();
}

SENSORUDPCTL_EXPORT int getSize()
{
  return Sensor::UdpCtl::getSize();
}

SENSORUDPCTL_EXPORT int getKeys (const int **dest)
{
  return Sensor::UdpCtl::getKeys (dest);
}

SENSORUDPCTL_EXPORT bool getData (
  /* in  */ int id,
  /* out */ float *out
)
{
  bool ypr  = Sensor::UdpCtl::getYpr (id, &out[0], &out[1], &out[2]);
  bool acc  = Sensor::UdpCtl::getAcc (id, &out[3], &out[4], &out[5]);
  bool gy   = Sensor::UdpCtl::getGy (id, &out[6], &out[7], &out[8]);
  return ypr && acc && gy;
}

SENSORUDPCTL_EXPORT bool getYpr (
  /* in  */ int id,
  /* out */ float *roll,
  /* out */ float *pitch,
  /* out */ float *yaw
)
{
  return Sensor::UdpCtl::getYpr (id, roll, pitch, yaw);
}

SENSORUDPCTL_EXPORT bool getAcc (
  /* in  */ int id,
  /* out */ float *acx,
  /* out */ float *acy,
  /* out */ float *acz
)
{
  return Sensor::UdpCtl::getAcc (id, acx, acy, acz);
}

SENSORUDPCTL_EXPORT bool getGy (
  /* in  */ int id,
  /* out */ float *gyx,
  /* out */ float *gyy,
  /* out */ float *gyz
)
{
  return Sensor::UdpCtl::getGy (id, gyx, gyy, gyz);
}

/*-----------------------------------------*/
