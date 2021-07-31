/* INCLUDES */
#include "sensor/udpctl.h"
#include "global.h"

/* EXPORT */
SENSORUDPCTL_EXPORT void init()
{
  Sensor::UdpCtl::init();
}

SENSORUDPCTL_EXPORT double getDivider()
{
  return Sensor::UdpCtl::getDivider();
}

SENSORUDPCTL_EXPORT void setDivider (const double &v)
{
  Sensor::UdpCtl::setDivider (v);
}

SENSORUDPCTL_EXPORT const char *getSensorsList()
{
  return Sensor::UdpCtl::getSensorsList();
}

SENSORUDPCTL_EXPORT bool getData (
  /* in  */ int id,
  /* out */ double &acx,
  /* out */ double &acy,
  /* out */ double &acz,
  /* out */ double &gyx,
  /* out */ double &gyy,
  /* out */ double &gyz
)
{
  return Sensor::UdpCtl::getData (id, acx, acy, acz, gyx, gyy, gyz);
}

/*-----------------------------------------*/
