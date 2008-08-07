######################################################################
# Automatically generated by qmake (2.01a) Fri Apr 11 10:09:55 2008
######################################################################

CONFIG += qt debug_and_release debug_and_release_target build_all thread
TEMPLATE = app
TARGET = QueueTest
DEPENDPATH += .
INCLUDEPATH += . \
               "C:\Program Files\boost\boost_1_35_0" \
               "C:\Documents and Settings\rosskw1\My Documents\ComponentizedCombatSystemFramework"

# Input
HEADERS += mainwindow.h Queue.h Thread.h Queue.h ConsumerThread.h ProducerThread.h \
           "C:\Program Files\boost\boost_1_35_0\boost\thread.hpp"
FORMS += QueueTest.ui
SOURCES += main.cpp mainwindow.cpp Queue.cpp Thread.cpp ConsumerThread.cpp ProducerThread.cpp

QT         += network

#win32:LIBS += -L..\..\QT-Plugins\KComboBox\debug\StaticLib -lKComboBox
win32:LIBS += -L"C:\Program Files\boost\boost_1_35_0\lib" \
              -l"C:\Program Files\boost\boost_1_35_0\lib\libboost_thread-vc71-mt-1_35" \
              -l"C:\Program Files\boost\boost_1_35_0\lib\libboost_thread-vc71-mt-gd-1_35" \
              -l"C:\Program Files\boost\boost_1_35_0\lib\libboost_date_time-vc71-mt-gd-1_35"

# This is used to set the system clock to 1 millisecond accuracy in "mainwindow.cpp".  
# It is for "Windows OS" systems only.
win32:LIBS += -lWinmm