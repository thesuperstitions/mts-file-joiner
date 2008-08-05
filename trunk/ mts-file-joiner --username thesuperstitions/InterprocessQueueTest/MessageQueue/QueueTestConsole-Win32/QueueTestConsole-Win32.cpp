// QueueTestConsole-Win32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ProducerThread.h"
#include "ConsumerThread.h"
#include "Queue.h"

ProducerThread*  producerThread;
ConsumerThread*  consumerThread;
Queue*           queue;


// Creates an instance of Queue, ProducerThread and ConsumerThread
// to test the performance of the Queue class.

int _tmain(int argc, _TCHAR* argv[])
{
  char c[5];

  printf("Hit any key to START queing messages");

  fgets(c, 2, stdin);

  queue = new Queue(1048576);

  producerThread = new ProducerThread(queue);
  producerThread->start();

  consumerThread = new ConsumerThread(queue);
  consumerThread->start();

  printf("Hit any key to STOP  queing/de-queing messages\n\n");

  fgets(c, 2, stdin);

  producerThread->stop();

  consumerThread->stop();

  delete producerThread;
  delete consumerThread;
  delete queue;

	return 0;
}

