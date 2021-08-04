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
  explicit Operation();
  Operation (const Operation &) = delete;
  Operation (Operation &&) = delete;
  ~Operation();
  /// @}

  /****************************************//**
   * @name STATIC METHODS
   *******************************************/
  /// @{
public:
  static bool start();
  static bool stop();
  static bool isValid();
  /// @}

  /****************************************//**
   * @name OPERATORS
   *******************************************/
  /// @{
public:
  Container *operator()();
  Operation &operator+= (const Unit &u);
  Operation &operator+= (Unit &&u);
  Unit operator[] (const int &id);

  Operation &operator= (const Operation &) = delete;
  Operation &operator= (Operation &&) = delete;
  /// @}

  /****************************************//**
   * @name PROTECTED VARS
   *******************************************/
  /// @{
protected:
  static Container *m_container;        ///< container instance
  static std::recursive_mutex m_mutex;  ///< container mutex
  /// @}

  /****************************************//**
   * @name PROTECTED METHODS
   *******************************************/
  /// @{
protected:
  void preventNull();
  /// @}
};
/*-----------------------------------------*/
};

/*-----------------------------------------*/
#endif // OPERATION_H
