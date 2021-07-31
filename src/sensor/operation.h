#ifndef OPERATION_H
#define OPERATION_H

/* INCLUDES */
#include "container.h"

/* NAMESPACE */
namespace Sensor
{

/****************************************//**
 * @brief sensor container operation
 * basicaly a mutex with ptr to
 * Container class instance
 * @ingroup groupSensor
 * @date 31.07.2021
 * @author Segaman
 *******************************************/

class Operation : protected std::lock_guard<std::recursive_mutex>
{
  /****************************************//**
   * @name CONSTRUCT/DESTRUCT
   *******************************************/
  /// @{
public:
  Operation();
  ~Operation();
  /// @}

  /****************************************//**
   * @name OPERATORS
   *******************************************/
  /// @{
public:
  Container *operator*();
  /// @}
};
/*-----------------------------------------*/
};

/*-----------------------------------------*/
#endif // OPERATION_H
