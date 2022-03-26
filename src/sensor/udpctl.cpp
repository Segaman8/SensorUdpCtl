/* INCLUDES */
#include "udpctl.h"
#include "datahelper.h"
#include "unit.h"
#include "container.h"
#include "operation.h"

#include <iostream>
#include <cstring>
#include <string>
#include <mutex>

/* NAMESPACE */
namespace Sensor
{

/********************************************
 * FUNCTIONS
 *******************************************/

void UdpCtl::init()
{
  try
    {
      Operation::start();
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
    }
}

bool UdpCtl::deinit()
{
  try
    {
      return Operation::stop();
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return false;
    }
}

const char *UdpCtl::getInfo()
{
  try
    {
      return Operation()()->getInfo();
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return "";
    }
}

int UdpCtl::getKeys (const int **dest)
{
  try
    {
      return Operation()()->getKeys (dest);
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return 0;
    }
}

int UdpCtl::getSize()
{
  try
    {
      return Operation()()->getSize();
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return 0;
    }
}

bool UdpCtl::getYpr (const int &id, float *roll, float *pitch, float *yaw)
{
  try
    {
      Operation o;
      auto item = o[id];

      /* if not present */
      if (!item.isValid())
        {
          /* return empty */
          *roll = 0; *pitch = 0; *yaw = 0;
          return false;
        }

      /* get it's values */
      *roll = item[0];
      *pitch = item[1];
      *yaw = item[2];

      return true;
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return false;
    }
}

bool UdpCtl::getAcc (const int &id, float *acx, float *acy, float *acz)
{
  try
    {
      Operation o;
      auto item = o[id];

      /* if not present */
      if (!item.isValid())
        {
          /* return empty */
          *acx = 0; *acy = 0; *acz = 0;
          return false;
        }

      /* get it's values */
      *acx = item[3];
      *acy = item[4];
      *acz = item[5];

      return true;
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return false;
    }
}

bool UdpCtl::getGy (const int &id, float *gyx, float *gyy, float *gyz)
{
  try
    {
      Operation o;
      auto item = o[id];

      /* if not present */
      if (!item.isValid())
        {
          /* return empty */
          *gyx = 0; *gyy = 0; *gyz = 0;
          return false;
        }

      /* get it's values */
      *gyx = item[6];
      *gyy = item[7];
      *gyz = item[8];

      return true;
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return false;
    }
}

/*-----------------------------------------*/
};
/*-----------------------------------------*/
