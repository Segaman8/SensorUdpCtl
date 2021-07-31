/* INCLUDES */
#include "sensorudpctl.h"
#include <unistd.h>

/********************************************
 * MAIN
 *******************************************/

int main (int argc, char *argv[])
{
  double acx, acy, acz, gyx, gyy, gyz;
  int count = 0;

  SensorUdpCtl::init();

  while (true)
    {
      SensorUdpCtl::getData (0, acx, acy, acz, gyx, gyy, gyz);

      count++;
      if (count >= 5)
        {
          count = 0;
          printf ("%s", SensorUdpCtl::getSensorsList());
        }

      sleep (1);
    }
}

/*-----------------------------------------*/
