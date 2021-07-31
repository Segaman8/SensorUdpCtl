#ifndef CONTAINER_H
#define CONTAINER_H

/* INCLUDES */
#include "unit.h"
#include <map>
#include <mutex>

/* NAMESPACE */
namespace Sensor
{

/****************************************//**
 * @brief definition of one unit
 * Unit made of ESP8226+MPU6050
 * @ingroup groupSensor
 * @date 31.07.2021
 * @author Segaman
 *******************************************/

class Container
{
  friend class Operation;

  /****************************************//**
   * @name VARS
   *******************************************/
  /// @{
protected:

  /// units map
  std::map<int, Unit> m_items;

  /// vector divider
  double m_divider  = 512.0;

  /// udp server state
  bool m_bindState  = false;

  /// udp messages counter
  int m_msgCounter  = 0;

  /// udp thread
  pthread_t m_thread;
  /// @}

  /****************************************//**
   * @name CONSTRUCT/DESTRUCT
   *******************************************/
  /// @{
protected:
  Container();
  /// @}

  /****************************************//**
   * @name PUBLIC METHODS
   *******************************************/
  /// @{
public:
  double divider() const;
  void setDivider (double divider);

  bool bindState() const;
  void setBindState (bool bindState);

  int msgCounter() const;
  int incMsgCounter();
  void setMsgCounter (int msgCounter);

  const char *getInfo();
  /// @}

  /****************************************//**
   * @name OPERATORS
   *******************************************/
  /// @{
public:
  Container &operator+= (Unit &u);
  const Unit *operator[] (const int &id);
  /// @}
};
/*-----------------------------------------*/
};

/*-----------------------------------------*/
#endif // CONTAINER_H
