/* INCLUDES */
#include "sensor/udpctl.h"
#include <unistd.h>
#include <gtest/gtest.h>

/********************************************
 * MAIN
 *******************************************/

int main (int argc, char *argv[])
{
//  testing::InitGoogleTest (&argc, argv);
//  return RUN_ALL_TESTS();
  double acx, acy, acz, gyx, gyy, gyz;
  int count = 0;

  Sensor::UdpCtl::init();

  while (true)
    {
      Sensor::UdpCtl::getData (0, acx, acy, acz, gyx, gyy, gyz);

      count++;
      if (count >= 5)
        {
          count = 0;
          printf ("%s", Sensor::UdpCtl::getSensorsList());
        }

      sleep (1);
    }
}

/*-----------------------------------------*/
