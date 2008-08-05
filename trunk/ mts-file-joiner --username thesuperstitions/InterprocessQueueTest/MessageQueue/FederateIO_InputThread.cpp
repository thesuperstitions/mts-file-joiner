/********************************************************************
	Rhapsody	: 7.1 
	Login		: rosskw1
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Framework::IO::FederateIO_InputThread
//!	Generated Date	: Wed, 9, Apr 2008  
	File Path	: DefaultComponent\DefaultConfig\FederateIO_InputThread.cpp
*********************************************************************/

#include "FederateIO_InputThread.h"
// dependency Control 
#include "Control.h"
// dependency Federate 
#include "Federate.h"
#include "FederateIO_Handler.h"
// dependency PostOffice 
#include "PostOffice.h"
// dependency Sleep 
#include "Sleep.h"

//----------------------------------------------------------------------------
// FederateIO_InputThread.cpp                                                                  
//----------------------------------------------------------------------------

//## package Framework::IO 

//## class FederateIO_InputThread 

namespace Framework {
    namespace IO {
        
        
        FederateIO_InputThread::FederateIO_InputThread() {
            itsFederateIO_Handler_1 = NULL;
        }
        
        FederateIO_InputThread::~FederateIO_InputThread() {
            cleanUpRelations();
        }
        
        void FederateIO_InputThread::threadOperation() {
            //#[ operation threadOperation() 
            
            timespec ts;
            FederateMessage* fm_Ptr;  
                      
            while (true)
            {    
              try
              {  
                boost::detail::thread::lock_ops<boost::mutex>::lock(myMutex);
                
                // Check to see if there's a Federate Message in the list   
                if (itsFederateMessage.empty() != true)
                {      
                  // Get the first message in the list.                                  
                  fm_Ptr = *itsFederateMessage.begin();  // Get the first FederateMessage in the list. 
                
                  // Send the message to the Post Office for delivery.  
                  if (/*fm_Ptr->getFederateInterface()->FederateInterface::*/getItsFederateIO_Handler()->passMessageToApplication(fm_Ptr) == true)
                  {
                    // Remove the message from the list now so that the mutex can be unlocked prior to sending.  
                    removeItsFederateMessage(fm_Ptr);   // Remove the just-sent FederateMessage from the list.
                  }
                  
                  // Unlock mutex prior to sending message.
                  boost::detail::thread::lock_ops<boost::mutex>::unlock(myMutex);
                }   
              } 
              catch (...)
              {
                boost::detail::thread::lock_ops<boost::mutex>::unlock(myMutex);
              } 
                  
              this->yield();
            //              ts.tv_nsec = 1 * Framework::utils::Sleep::NANOSECONDS_PER_MILLISECOND;
            //              ts.tv_sec = 0;
            //              Framework::utils::Sleep::sleep(ts);
            };  
            //#]
        }
        
        Framework::IO::FederateIO_Handler* FederateIO_InputThread::getItsFederateIO_Handler_1() const {
            return itsFederateIO_Handler_1;
        }
        
        void FederateIO_InputThread::__setItsFederateIO_Handler_1(Framework::IO::FederateIO_Handler* p_FederateIO_Handler) {
            itsFederateIO_Handler_1 = p_FederateIO_Handler;
        }
        
        void FederateIO_InputThread::_setItsFederateIO_Handler_1(Framework::IO::FederateIO_Handler* p_FederateIO_Handler) {
            if(itsFederateIO_Handler_1 != NULL)
                {
                    itsFederateIO_Handler_1->__setItsFederateIO_InputThread(NULL);
                }
            __setItsFederateIO_Handler_1(p_FederateIO_Handler);
        }
        
        void FederateIO_InputThread::setItsFederateIO_Handler_1(Framework::IO::FederateIO_Handler* p_FederateIO_Handler) {
            if(p_FederateIO_Handler != NULL)
                {
                    p_FederateIO_Handler->_setItsFederateIO_InputThread(this);
                }
            _setItsFederateIO_Handler_1(p_FederateIO_Handler);
        }
        
        void FederateIO_InputThread::_clearItsFederateIO_Handler_1() {
            itsFederateIO_Handler_1 = NULL;
        }
        
        void FederateIO_InputThread::cleanUpRelations() {
            if(itsFederateIO_Handler_1 != NULL)
                {
                    Framework::IO::FederateIO_InputThread* p_FederateIO_InputThread = itsFederateIO_Handler_1->getItsFederateIO_InputThread();
                    if(p_FederateIO_InputThread != NULL)
                        {
                            itsFederateIO_Handler_1->__setItsFederateIO_InputThread(NULL);
                        }
                    itsFederateIO_Handler_1 = NULL;
                }
        }
        
    }
}


/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\FederateIO_InputThread.cpp
*********************************************************************/

