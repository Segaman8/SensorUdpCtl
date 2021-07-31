/* INCLUDES */
#include "container.h"
#include "operation.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/* NAMESPACE */
namespace Sensor
{

/* LINKS */
static void *threadRoutine (void *p);

/********************************************
 * CONSTRUCT/DESTRUCT
 *******************************************/

Container::Container()
{
  pthread_create (&m_thread, nullptr, &threadRoutine, nullptr);
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
    + " >> ";

  for (auto i = m_items.begin(), e = m_items.end(); i != e; i++)
    result += std::to_string (i->first) + ", ";

  return result.c_str();
}

/********************************************
 * OPERATORS
 *******************************************/

Container &Container::operator+= (Unit &u)
{
  m_items[u.id()] = u;
  return *this;
}

const Unit *Container::operator[] (const int &id)
{
  if (!m_items.contains (id))
    return nullptr;
  return &m_items[id];
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
      (*Operation())->setBindState (false);
      close (serSockDes);
      return nullptr;
    }
  else
    (*Operation())->setBindState (true);

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
          (*Operation())->setBindState (false);
          close (serSockDes);
          return nullptr;
        }

      /* finalize */
      buff[readStatus] = '\0';

      {
        Operation o;

        /* counter */
        (*o)->incMsgCounter();

        /* parse and store */
        Unit item (DataHelper (buff, readStatus));
        (**o) += item;
      }
    }

  /* finish */
  close (serSockDes);
}

/*-----------------------------------------*/
};
/*-----------------------------------------*/
