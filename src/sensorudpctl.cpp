/* INCLUDES */
#include "sensorudpctl.h"
#include <cstring>
#include <string>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/* DEFS */

/**********************************************/

class Data
{
  /* VARS */
  std::vector<char> d;

  /* CONSTRUCT/DESTRUCT */
public:
  Data (const char *data, const size_t &size)
  {
    d.resize (size);
    memcpy (d.data(), data, size);
  }

  /* METHODS */
  std::vector<Data> split (const char &c) const
  {
    std::vector<Data> result;
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
                Data value (d.data() + begin, end - begin);
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
        Data value (d.data() + begin, end - begin);
        result.push_back (value);
      }

    return result;
  }

  const std::vector<char> &data() const
  {
    return d;
  }
};

/**********************************************/

struct Item
{
  /* VARS */
  int m_id;
  double values[6];

  /* CONSTRUCT/DESTRUCT */
  Item();
  Item (const Data &data);

  /* METHODS */
  int id() const;
};

/**********************************************/

struct Container
{
  std::map<int, Item> items;

  double divider = 512.0;
  bool bindState = false;
  int msgCounter = 0;

  pthread_t mainThread;
  //pthread_mutex_t dataMutex;
  std::recursive_mutex dataMutex;

  void open()
  {
    //pthread_mutex_lock (&dataMutex);
    dataMutex.lock();
  }

  void close()
  {
    //pthread_mutex_unlock (&dataMutex);
    dataMutex.unlock();
  }
};

class Operation : public std::lock_guard<std::recursive_mutex>
{
public:
  Operation();
};

/**********************************************/

/* VARS */
static Container c;
static void *threadRoutine (void *p);

/********************************************
 * CONSTRUCT/DESTRUCT
 *******************************************/

void SensorUdpCtl::init()
{
  //pthread_mutex_init (&c.dataMutex, NULL);
  pthread_create (&c.mainThread, nullptr, &threadRoutine, nullptr);
}

/********************************************
 * STATIC METHODS
 *******************************************/
double SensorUdpCtl::getDivider()
{
  Operation o;
  return c.divider;
}

void SensorUdpCtl::setDivider (const double &v)
{
  Operation o;
  c.divider = v;
}

const char *SensorUdpCtl::getSensorsList()
{
  static std::string result;
  Operation o;

  auto sz = c.items.size();
  result    =
    std::string ("Bind: ")
    + std::to_string (c.bindState)
    + " Messages: "
    + std::to_string (c.msgCounter)
    + " Sensors: "
    + std::to_string (sz)
    + " >> ";

  for (auto i = c.items.begin(), e = c.items.end(); i != e; i++)
    result += std::to_string (i->first) + ", ";

  return result.c_str();
}

bool SensorUdpCtl::getData (
  /* in  */ const int &id,
  /* out */ double &acx,
  /* out */ double &acy,
  /* out */ double &acz,
  /* out */ double &gyx,
  /* out */ double &gyy,
  /* out */ double &gyz
)
{
  Operation o;

  /* if not present */
  if (!c.items.contains (id))
    {
      /* return empty */
      acx = 0; acy = 0; acz = 0;
      gyx = 0; gyy = 0; gyz = 0;
      return false;
    }

  /* get item */
  Item &item = c.items[id];

  /* get it's values */
  acx = item.values[0];
  acy = item.values[1];
  acz = item.values[2];
  gyx = item.values[3];
  gyy = item.values[4];
  gyz = item.values[5];

  return true;
}

/********************************************
 * FUNCTIONS
 *******************************************/

int32_t fromHex (const Data &v)
{
  /* setup union */
  union
  {
    int32_t i = 0;
    char c[4];
  };

  /* prepare cycle vars */
  auto data     = v.data();
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

/********************************************
 * ITEM
 *******************************************/

Item::Item()
{
  memset (this, 0, sizeof (Item));
}

Item::Item (const Data &data)
{
  /* packet structure */
  /* id acx acy acz gyx gyy gyz */

  /* sep packet by space */
  auto list = data.split (' ');

  /* get sensor id */
  m_id    = atoi (list.at (0).data().data());

  /* get divider */
  double divider;
  {
    Operation o;
    divider = c.divider;
  }

  /* get data via cycle */
  for (int i = 1; i < 7; i++)
    values[i - 1] = double (fromHex (list.at (i))) / divider;
}

int Item::id() const
{
  return m_id;
}

/********************************************
 * THREAD
 *******************************************/

void *threadRoutine (void *p)
{
  /* vars */
  int serSockDes, readStatus;
  struct sockaddr_in serAddr, cliAddr;
  socklen_t cliAddrLen = sizeof (cliAddr);
  char buff[1024] = {0};

  /* creating a new server socket */
  if ((serSockDes = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror ("socket creation error...\n");
      exit (-1);
    }

  /* binding the port to ip and port */
  serAddr.sin_family      = AF_INET;
  serAddr.sin_port        = htons (7989);
  serAddr.sin_addr.s_addr =
    //inet_addr ("192.168.0.255");
    INADDR_ANY;

  if ((bind (serSockDes, (struct sockaddr *)&serAddr, sizeof (serAddr))) < 0)
    {
      c.bindState = false;
      close (serSockDes);
      return nullptr;
    }
  else
    c.bindState = true;

  /* read via cycle */
  while (true)
    {
      /* get msg */
      readStatus =
        recvfrom (
          serSockDes,
          buff, 1024, 0,
          (struct sockaddr *)&cliAddr,
          &cliAddrLen
        );

      /* got error */
      if (readStatus < 0)
        {
          Operation o;
          c.bindState = false;
          close (serSockDes);
          return nullptr;
        }

      /* finalize */
      buff[readStatus] = '\0';

      {
        Operation o;
        /* count */
        c.msgCounter++;

        /* parse and store */
        Data data (buff, readStatus);
        Item item (data);
        c.items[item.id()] = item;
      }
    }

  /* finish */
  close (serSockDes);

//  /* cycle thru pending packets */
//  while (socket->hasPendingDatagrams())
//    {
//      msgCounter++;

//      /* allocate receiver */
//      QByteArray data;
//      data.resize (socket->pendingDatagramSize());

//      /* get data and receiver info */
//      QHostAddress sender;
//      quint16 senderPort;
//      socket->readDatagram (data.data(), data.size(), &sender, &senderPort);

//      /* parse and store */
//      Item item (data);
//      items[item.id()] = item;
//    }
}

Operation::Operation()
  : std::lock_guard<std::recursive_mutex> (c.dataMutex)
{
}

/*-----------------------------------------*/
