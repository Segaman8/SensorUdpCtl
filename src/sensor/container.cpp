/* INCLUDES */
#include "container.h"
#include "operation.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/* NAMESPACE */
namespace Sensor
{

/* VARS */
static void *threadRoutine (void *);
static int serSockDes; ///< socket id

/* LINKS */
static void except (const std::exception &ex);

/********************************************
 * CONSTRUCT/DESTRUCT
 *******************************************/

Container::Container()
{
  pthread_create (&m_thread, nullptr, &threadRoutine, nullptr);
}

Container::~Container()
{
  /* stop socket */
  shutdown (serSockDes, SHUT_RDWR);
  /* wait thread to finish */
  pthread_join (m_thread, nullptr);
}

/********************************************
 * PUBLIC METHODS
 *******************************************/

double Container::divider() const
{
  return m_divider;
}

void Container::setDivider (double divider)
{
  m_divider = divider;
}

bool Container::bindState() const
{
  return m_bindState;
}

void Container::setBindState (bool bindState)
{
  m_bindState = bindState;
}

int Container::msgCounter() const
{
  return m_msgCounter;
}

int Container::incMsgCounter()
{
  return ++m_msgCounter;
}

void Container::setMsgCounter (int msgCounter)
{
  m_msgCounter = msgCounter;
}

const char *Container::getInfo()
{
  static std::string result;

  auto sz = m_items.size();
  result    =
    std::string ("Bind: ")
    + std::to_string (m_bindState)
    + " Messages: "
    + std::to_string (m_msgCounter)
    + " Sensors: "
    + std::to_string (sz)
    + " {";

  for (auto i = m_items.begin(), e = m_items.end(); i != e; i++)
    result += std::to_string (i->first) + ", ";

  result += "}";

  return result.c_str();
}

int Container::getSize()
{
  return m_items.size();
}

int Container::getKeys (const int **dest)
{
  /* array holder */
  static int *array = nullptr;

  /* free old array */
  if (array)
    free (array);

  /* alloc array */
  int sz  = getSize();
  array   = reinterpret_cast<int *> (malloc (sizeof (int) * sz));

  /* store keys in cycle */
  int j = 0;
  for (auto i = m_items.begin(), e = m_items.end(); i != e; i++, j++)
    array[j] = i->first;

  /* return values */
  if (dest)
    *dest = array;
  return m_items.size();
}

/********************************************
 * OPERATORS
 *******************************************/

Container &Container::operator+= (const Unit &u)
{
//  m_items.emplace (u.id(), u);
  m_items[u.id()] = u;
  return *this;
}

Container &Container::operator+= (Unit &&u)
{
  m_items.emplace (u.id(), u);
//  m_items[u.id()] = u;
  return *this;
}

Unit Container::operator [] (const int &id)
{
  if (!m_items.contains (id))
    return Unit();
  return m_items[id];
}

/********************************************
 * THREAD
 *******************************************/

void *threadRoutine (void *)
{
  /* vars */
  int readStatus;
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

  /* bind with trycatch */
  try
    {
      if ((bind (serSockDes, (struct sockaddr *)&serAddr, sizeof (serAddr))) < 0)
        {
          Operation()()->setBindState (false);
          close (serSockDes);
          return nullptr;
        }
      else
        Operation()()->setBindState (true);
    }
  catch (const std::exception &ex)
    {
      except (ex);
      close (serSockDes);
      return 0;
    }

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

      try
        {
          /* got error */
          if (readStatus < 0)
            {
              Operation()()->setBindState (false);
              close (serSockDes);
              return nullptr;
            }

          /* finalize */
          buff[readStatus] = '\0';

          {
            /* begin operation */
            Operation op;

            /* increase counter */
            op()->incMsgCounter();

            /* parse and store */
            op += DataHelper (buff, readStatus);
          }
        }
      catch (const std::exception &ex)
        {
          except (ex);
          break;
        }
    }

  /* finish */
  close (serSockDes);

  return 0;
}

void except (const std::exception &ex)
{
  std::cout << "UdpCtlThread caught an issue: " << ex.what() << std::endl;
  std::cout << "UdpCtlThread will be finished." << std::endl;
}


/*-----------------------------------------*/
};
/*-----------------------------------------*/
