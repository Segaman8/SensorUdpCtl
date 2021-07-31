/* INCLUDES */
#include "sensor/udpctl.h"
#include "datahelper.h"
#include "sensor/unit.h"

#include <unistd.h>
#include <cstring>
#include <gtest/gtest.h>

/* VARS */

/* setup data in */
static char msgBuffer[256];
static const char *const results[] =
{
  "0",
  "00000422", "07041FEB",
  "FE0000E0", "00900000",
  "E0000000", "000041FE"
};
static const double values[] =
{
  0x0,
  int32_t (0x00000422) / 512.0, int32_t (0x07041FEB) / 512.0,
  int32_t (0xFE0000E0) / 512.0, int32_t (0x00900000) / 512.0,
  int32_t (0xE0000000) / 512.0, int32_t (0x000041FE) / 512.0
};

/********************************************
 * MAIN
 *******************************************/

int main (int argc, char *argv[])
{
  /* build sensor message */
  sprintf (
    msgBuffer,
    "%s %s %s %s %s %s %s",
    results[0],
    results[1], results[2], results[3],
    results[4], results[5], results[6]
  );

  testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();
}

/********************************************
 * TEST
 *******************************************/

/*-----------------------------------------*/

TEST (DataHelper, SplitTest)
{
  /* start helper and split */
  DataHelper h (msgBuffer, strlen (msgBuffer));
  auto list = h.split (' ');

  /* test result by cycle */
  for (size_t i = 0; i < GTEST_ARRAY_SIZE_ (results); i++)
    EXPECT_EQ (strcmp (list[i].data(), results[i]), 0)
        << "i: " << i
        << ", data: " << list[i].data()
        << ", expects: " << results[i];
}

/*-----------------------------------------*/

TEST (Unit, ParseTest)
{
  /* create instance */
  Sensor::Unit u (DataHelper (msgBuffer, strlen (msgBuffer)));

  /* check id */
  EXPECT_EQ (u.id(), values[0]);

  /* check vector values */
  for (size_t i = 1; i < GTEST_ARRAY_SIZE_ (values); i++)
    EXPECT_EQ (u[i - 1], values[i])
        << "i: " << i
        << ", unit: " << u[i - 1]
        << ", expects: " << values[i];
}

/*-----------------------------------------*/

TEST (UdpCtl, UdpServerTest)
{
  /* print warning */
  std::cerr << "[ WARNING  ] "
            << "This test require at least 1 sensor to be active."
            " Instead it will wait 15 seconds and fail."
            << std::endl;

  /* vars */
  double acx = 0, acy = 0,
         acz = 0, gyx = 0,
         gyy = 0, gyz = 0;
  int count = 1, sensorConnected = 0;

  /* start udp ctl */
  Sensor::UdpCtl::init();

  /* try cycle 15 seconds */
  while (true)
    {
      /* wait 1 second */
      sleep (1);

      /* get current sensors amount and sensor 0 data */
      int size = Sensor::UdpCtl::getSize();
      Sensor::UdpCtl::getData (0, acx, acy, acz, gyx, gyy, gyz);

      /* store stamp when first sensor connected */
      if (sensorConnected == 0 && size != 0)
        {
          std::cerr << "[ WARNING  ] "
                    << "some sensors got connected to udp server"
                    << std::endl;
          sensorConnected = count;
        }

      /* check if time passed */
      else if (sensorConnected < count && size != 0)
        {
          /* if no data present, print fail */
          if (acx == 0
              && acy == 0
              && acz == 0
              && gyx == 0
              && gyy == 0
              && gyz == 0)
            FAIL() << "sensor connected, but no data being sent. " << Sensor::UdpCtl::getInfo();
          /* success */
          else
            return;
        }

      /* count 15 seconds */
      if (++count >= 16)
        FAIL() << "no sensors connected. " << Sensor::UdpCtl::getInfo();

      /* print seconds passed */
      std::cerr << "[ WAITING  ] "
                << count
                << " seconds passed"
                << std::endl;
    }

  /* save us */
  FAIL() << "never gonna happen, but still exists for magic cases";
}

/*-----------------------------------------*/
