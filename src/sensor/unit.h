#ifndef SENSORUNIT_H
#define SENSORUNIT_H

/* INCLUDES */
#include "datahelper.h"

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

class Unit
{
  /****************************************//**
   * @name VARS
   *******************************************/
  /// @{
private:
  int64_t m_id;
  float m_values[9];
  bool m_valid;
  /// @}

  /****************************************//**
   * @name CONSTRUCT/DESTRUCT
   *******************************************/
  /// @{
public:
  Unit();
  Unit (const Unit &value);
  Unit (Unit &&value) = delete;
  Unit (const DataHelper &data);
  ~Unit();
  /// @}

  /****************************************//**
   * @name PUBLIC METHODS
   *******************************************/
  /// @{
public:
  int id() const;
  bool isValid() const;
  /// @}

  /****************************************//**
   * @name OPERATORS
   *******************************************/
  /// @{
public:
  Unit &operator= (const Unit &value);
  Unit &operator= (Unit &&value) = delete;
  float operator[] (const int &index) const;
  /// @}
};
/*-----------------------------------------*/
};

/*-----------------------------------------*/
#endif // SENSORUNIT_H
