// InterprocessQueueTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>

using namespace boost::interprocess;

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

//#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
  char c[5];
  Message msg(1, 2, 333.333);
  char cMsg[100];
  std::ostream os;


  printf("Hit any key to START queing messages\n\n");

  fgets(c, 2, stdin);


  if (strcmp(argv[1], "server") == 0)
  {

  }

  if (strcmp(argv[1], "client") == 0)
  {
  }

  printf("Hit any key to STOP  queing/de-queing messages\n\n");

  fgets(c, 2, stdin);



	return 0;
}

