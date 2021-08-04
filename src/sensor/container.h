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
  std::map<int, Unit> m_items;  ///< units map
  double m_divider  = 512.0;    ///< vector divider
  bool m_bindState  = false;    ///< udp server state
  int m_msgCounter  = 0;        ///< udp messages counter
  pthread_t m_thread;           ///< udp thread
  /// @}

  /****************************************//**
   * @name CONSTRUCT/DESTRUCT
   *******************************************/
  /// @{
protected:
  Container();
  Container (const Container &) = delete;
  Container (Container &&) = delete;
  ~Container();
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
  int getSize();
  int getKeys (const int **dest);
  /// @}

  /****************************************//**
   * @name OPERATORS
   *******************************************/
  /// @{
public:
  Container &operator= (const Container &) = delete;
  Container &operator= (Container &&) = delete;
  Container &operator+= (const Unit &u);
  Container &operator+= (Unit &&u);
  Unit operator[] (const int &id);
  /// @}
};
/*-----------------------------------------*/
};

/*-----------------------------------------*/
#endif // CONTAINER_H
