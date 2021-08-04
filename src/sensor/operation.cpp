#include "operation.h"

/* NAMESPACE */
namespace Sensor
{

/* VARS */
Container *Operation::m_container = nullptr;
std::recursive_mutex Operation::m_mutex;

/********************************************
 * CONSTRUCT/DESTRUCT
 *******************************************/

Operation::Operation()
  : std::lock_guard<std::recursive_mutex> (m_mutex)
{
}

Operation::~Operation()
{
}

/********************************************
 * STATIC METHODS
 *******************************************/

bool Operation::start()
{
  if (m_container == nullptr)
    {
      m_container = new Container;
      return true;
    }
  return false;
}

bool Operation::stop()
{
  if (m_container == nullptr)
    return false;

  auto temp   = m_container;
  m_container = nullptr;
  delete temp;

  return true;
}

bool Operation::isValid()
{
  return m_container != nullptr;
}

/********************************************
 * OPERATORS
 *******************************************/

Container *Operation::operator()()
{
  preventNull();
  return m_container;
}

Operation &Operation::operator+= (const Unit &u)
{
  preventNull();
  (*m_container) += u;
  return *this;
}

Operation &Operation::operator+= (Unit &&u)
{
  preventNull();
  (*m_container) += u;
  return *this;
}

Unit Operation::operator[] (const int &id)
{
  preventNull();
  return (*m_container)[id];
}

/********************************************
 * PROTECTED METHODS
 *******************************************/

void Operation::preventNull()
{
  if (m_container == nullptr)
    throw std::runtime_error (
      "Operation unable to proceed, "
      "because all operations is stopped.");
}

/*-----------------------------------------*/
};
/*-----------------------------------------*/
