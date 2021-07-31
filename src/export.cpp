/* INCLUDES */
#include "sensorudpctl.h"
#include "sensorudpctl_global.h"

/* EXPORT */
SENSORUDPCTL_EXPORT void init()
{
  SensorUdpCtl::init();
}

SENSORUDPCTL_EXPORT double getDivider()
{
  return SensorUdpCtl::getDivider();
}

SENSORUDPCTL_EXPORT void setDivider (const double &v)
{
  SensorUdpCtl::setDivider (v);
}

SENSORUDPCTL_EXPORT const char *getSensorsList()
{
  return SensorUdpCtl::getSensorsList();
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
  return SensorUdpCtl::getData (id, acx, acy, acz, gyx, gyy, gyz);
}

#ifdef MAKEELF
int main (int argc, char *argv[])
{
  double acx, acy, acz, gyx, gyy, gyz;
  int count = 0;

  init();

  while (true)
    {
      getData (0, acx, acy, acz, gyx, gyy, gyz);

      count++;
      if (count >= 5)
        {
          count = 0;
          printf ("%s", getSensorsList());
        }

      sleep (1);
    }
}
#endif // MAKEELF

/*-----------------------------------------*/
