
#ifdef WIN32
#include <winsock2.h>
#include <Windows.h>
#include <mmsystem.h>
#endif

#include <QDesktopWidget>
#include <QTextStream>
#include "mainwindow.h"
#include "Queue.h"
#include "Sleep.h"

//****************************************************************************************************************************

MainWindow::MainWindow(QApplication* ThisApp)/* : consumerThread(&queue), producerThread(&queue)*/
{
  try
  {
  // Keep a pointer to the application so we can get the desktop environment.
  TheApp = ThisApp;

  // Set up the QSettings system.
  QCoreApplication::setOrganizationName("JHUAPL");      
  QCoreApplication::setOrganizationDomain("jhuapl.edu");
  QCoreApplication::setApplicationName("LinkRadio");

  AppSettings = new QSettings(QSettings::IniFormat, 
                              QSettings::UserScope, 
                              QCoreApplication::organizationName(), 
                              QCoreApplication::applicationName() );


  setupUi(this);

  QObject::connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(ProcessDataClicked(bool)));

  textEdit->append("DEBUG:MainWindow::MainWindow - DONE Initializing GUI");

  // sets the minimum timer resolution, in milliseconds, for an application or device driver.
#ifdef WIN32
  timeBeginPeriod(1);
#endif

  }
  catch(...)
  {
    textEdit->append("DEBUG:MainWindow::MainWindow - EXCEPTION");
  }
}

void MainWindow::ProcessDataClicked(bool checked)
{
  try
  {
  if (checked)
  {
    textEdit->append("DEBUG:MainWindow::ProcessDataClicked - User Clicked \"Start Program\" Button");
    pushButton->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));

//    queue          = new Queue();

    consumerThread = new ConsumerThread(&queue);
    consumerThread->start();

    producerThread = new ProducerThread(&queue);
    producerThread->start();


//    QObject::connect(&queue, SIGNAL(OnLogText(QString)), textEdit, SLOT(append(QString)));
  }
  else
  {
    textEdit->append("DEBUG:MainWindow::ProcessDataClicked - User Clicked \"Stop Processing\" Button");
    pushButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));

    consumerThread->stop();

    producerThread->stop();

//    framework::utils::Sleep::sleep(1, 0);

    delete producerThread;

//    delete queue;
    delete consumerThread;
//    QObject::disconnect(&queue, SIGNAL(OnLogText(QString)), textEdit, SLOT(append(QString)));
  }
  }
  catch(...)
  {
    textEdit->append("DEBUG:MainWindow::ProcessDataClicked - EXCEPTION");
  }
}

MainWindow::~MainWindow(void)
{
}
