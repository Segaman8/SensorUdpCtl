#include "operation.h"

/* NAMESPACE */
namespace Sensor
{

/* VARS */
static Container *c = nullptr;      ///< container instance
static std::recursive_mutex mutex;  ///< container mutex
static volatile int operationCounter = 0;

/********************************************
 * CONSTRUCT/DESTRUCT
 *******************************************/

Operation::Operation()
  : std::lock_guard<std::recursive_mutex> (mutex)
{
  if (c == nullptr)
    c = new Container;
  operationCounter++;
}

Operation::~Operation()
{
  operationCounter--;
}

/********************************************
 * OPERATORS
 *******************************************/

Container *Operation::operator*()
{
  return c;
}

/*-----------------------------------------*/
};
/*-----------------------------------------*/
