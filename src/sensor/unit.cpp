/* INCLUDES */
#include "unit.h"
#include "operation.h"

#include <iostream>
#include <cstring>

/* NAMESPACE */
namespace Sensor
{

/* DEFS */
#define VALUES (7)

/* LINKS */
static int32_t fromHex (const DataHelper &v);

/********************************************
 * CONSTRUCT/DESTRUCT
 *******************************************/

Unit::Unit()
{
  memset (this, 0, sizeof (Unit));
}

Unit::Unit (const Unit &value)
  : m_id (0)
{
  operator= (value);
}

Unit::Unit (const DataHelper &data)
  : m_id (0)
{
  /* packet structure */
  /* id acx acy acz gyx gyy gyz */

  /* sep packet by space */
  auto list = data.split (' ');

  /* check if empty or corrupted data get */
  if (list.size() != VALUES)
    {
      memset (this, 0, sizeof (Unit));
      return;
    }

  /* get sensor id */
  m_id    = atoi (list.at (0).data());

  /* get divider or use default */
  double divider = 512.0;
  if (Operation::isValid())
    try
      {
        divider = Operation()()->divider();
      }
    catch (const std::exception &ex)
      {
        std::cout << ex.what() << std::endl;
      }

  /* get data via cycle */
  for (int i = 1; i < 7; i++)
    m_values[i - 1] = double (fromHex (list.at (i))) / divider;

  /* set as valid */
  m_valid = true;
}

Unit::~Unit()
{

}

/********************************************
 * PUBLIC METHODS
 *******************************************/

int Unit::id() const
{
  return m_id;
}

bool Unit::isValid() const
{
  return m_valid;
}

/********************************************
 * OPERATORS
 *******************************************/

Unit &Unit::operator= (const Unit &v)
{
  this->m_id    = v.m_id;

  for (int i = 0; i < 6; i++)
    this->m_values[i] = v.m_values[i];

  m_valid = v.m_valid;

  return *this;
}

double Unit::operator[] (const int &index) const
{
  if (!m_valid)
    return 0.0;

  if (index < 6)
    return m_values[index];

  return 0.0;
}

/********************************************
 * FUNCTIONS
 *******************************************/

int32_t fromHex (const DataHelper &v)
{
  /* setup union */
  union
  {
    int32_t i = 0;
    char c[4];
  };

  /* prepare cycle vars */
  auto data     = *v;
  bool nibble   = false;
  int index     = 0;

  /* parse via cycle */
  for (auto i = data.end() - 1, e = data.begin() - 1; i != e; i--)
    {
      /* get hex value */
      char j = *i - 0x30;

      /* decrease if higher than 9 */
      if (j > 9)
        j -= 7;

      /* if high nibble, shift (x*16) */
      if (nibble)
        j <<= 4;

      /* store into byte */
      c[index] |= j;

      /* increase index */
      if (nibble)
        index++;

      /* toggle nibble */
      nibble = !nibble;
    }

  return i;
}

/*-----------------------------------------*/
};
/*-----------------------------------------*/
