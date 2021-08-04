#ifndef DATAHELPER_H
#define DATAHELPER_H

/* INCLUDES */
#include <vector>

/****************************************//**
 * @brief helps to parse incoming data
 * @date 31.07.2021
 * @author Segaman
 *******************************************/

class DataHelper
{
  /****************************************//**
   * @name VARS
   *******************************************/
  /// @{
private:
  std::vector<char> d;
  /// @}

  /****************************************//**
   * @name CONSTRUCT/DESTRUCT
   *******************************************/
  /// @{
public:
  explicit DataHelper (const char *data, const size_t &size);
  /// @}

  /****************************************//**
   * @name PUBLIC METHODS
   *******************************************/
  /// @{
public:
  /// split data by symbol
  std::vector<DataHelper> split (const char &c) const;
  /// get buffer ptr
  char *data();
  /// @}

  /****************************************//**
   * @name OPERATORS
   *******************************************/
  /// @{
public:
  const std::vector<char> &operator*() const;
  /// @}
};

/*-----------------------------------------*/
#endif // DATAHELPER_H
