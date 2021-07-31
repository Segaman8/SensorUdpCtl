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
  DataHelper (const char *data, const size_t &size);
  /// @}

  /****************************************//**
   * @name PUBLIC METHODS
   *******************************************/
  /// @{
public:
  /// split data by symbol
  std::vector<DataHelper> split (const char &c) const;
  /// get buffer ptr
  const std::vector<char> &data() const;
  /// @}
};

/*-----------------------------------------*/
#endif // DATAHELPER_H
