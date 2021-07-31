/* INCLUDES */
#include "udpctl.h"
#include "datahelper.h"
#include "unit.h"
#include "container.h"
#include "operation.h"

#include <cstring>
#include <string>
#include <mutex>

/* NAMESPACE */
namespace Sensor
{

/* VARS */
static void *threadRoutine (void *p);

/********************************************
 * CONSTRUCT/DESTRUCT
 *******************************************/

void UdpCtl::init()
{
  Operation o;
}

/********************************************
 * STATIC METHODS
 *******************************************/
double UdpCtl::getDivider()
{
  return (*Operation())->divider();
}

void UdpCtl::setDivider (const double &v)
{
  (*Operation())->setDivider (v);
}

const char *UdpCtl::getSensorsList()
{
  return (*Operation())->getInfo();
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
  Operation o;
  auto item = (**o)[id];

  /* if not present */
  if (item == nullptr)
    {
      /* return empty */
      acx = 0; acy = 0; acz = 0;
      gyx = 0; gyy = 0; gyz = 0;
      return false;
    }

  /* get it's values */
  acx = (*item)[0];
  acy = (*item)[1];
  acz = (*item)[2];
  gyx = (*item)[3];
  gyy = (*item)[4];
  gyz = (*item)[5];

  return true;
}

/*-----------------------------------------*/
};
/*-----------------------------------------*/
