/* INCLUDES */
#include "unit.h"
#include "operation.h"
#include <cstring>

/* NAMESPACE */
namespace Sensor
{

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

  /* get sensor id */
  m_id    = atoi (list.at (0).data());

  /* get divider */
  double divider = (*Operation())->divider();

  /* get data via cycle */
  for (int i = 1; i < 7; i++)
    values[i - 1] = double (fromHex (list.at (i))) / divider;
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

/********************************************
 * OPERATORS
 *******************************************/

Unit &Unit::operator= (const Unit &v)
{
  this->m_id    = v.m_id;

  for (int i = 0; i < 6; i++)
    this->values[i] = v.values[i];

  return *this;
}

double Unit::operator[] (const int index) const
{
  if (index < 6)
    return values[index];
  return 0;
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
