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

double UdpCtl::getDivider()
{
  try
    {
      return Operation()()->divider();
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return 0.0;
    }
}

void UdpCtl::setDivider (const double &v)
{
  try
    {
      Operation()()->setDivider (v);
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
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

bool UdpCtl::getData (
  /* in  */ const int &id,
  /* out */ double &acx,
  /* out */ double &acy,
  /* out */ double &acz,
  /* out */ double &gyx,
  /* out */ double &gyy,
  /* out */ double &gyz
)
{
  try
    {
      Operation o;
      auto item = o[id];

      /* if not present */
      if (!item.isValid())
        {
          /* return empty */
          acx = 0; acy = 0; acz = 0;
          gyx = 0; gyy = 0; gyz = 0;
          return false;
        }

      /* get it's values */
      acx = item[0];
      acy = item[1];
      acz = item[2];
      gyx = item[3];
      gyy = item[4];
      gyz = item[5];

      return true;
    }
  catch (const std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
      return false;
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

/*-----------------------------------------*/
};
/*-----------------------------------------*/
