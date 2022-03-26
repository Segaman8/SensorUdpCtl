/* INCLUDES */
#include "datahelper.h"
#include <cstring>

/********************************************
 * CONSTRUCT/DESTRUCT
 *******************************************/

DataHelper::DataHelper (const char *data, const size_t &size)
{
  d.resize (size);
  memcpy (d.data(), data, size);
}

/********************************************
 * PUBLIC METHODS
 *******************************************/

std::vector<DataHelper> DataHelper::split (const char &c) const
{
  std::vector<DataHelper> result;
  int begin = 0, end = 0;

  /* split in cycle */
  for (auto i = d.begin(), e = d.end(); i != e; i++)
    {
      /* found letter */
      if (*i == c)
        {
          /* store */
          if (end - begin)
            {
              DataHelper value (d.data() + begin, end - begin + 1);
              value.data()[end - begin] = '\0';
              result.push_back (value);
            }

          /* proceed */
          end++;
          begin = end;

          /* check issue */
          if (end >= int (d.size()))
            break;
        }

      /* proceed */
      else
        end++;
    }

  /* store */
  if (end - begin)
    {
      DataHelper value (d.data() + begin, end - begin);
      result.push_back (value);
    }

  return result;
}

char *DataHelper::data()
{
  return d.data();
}

/********************************************
 * OPERATORS
 *******************************************/

const std::vector<char> &DataHelper::operator*() const
{
  return d;
}

/*-----------------------------------------*/
