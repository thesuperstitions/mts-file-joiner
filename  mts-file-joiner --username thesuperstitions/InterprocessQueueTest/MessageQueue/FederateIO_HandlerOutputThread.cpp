/********************************************************************
	Rhapsody	: 7.1 
	Login		: rosskw1
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Framework::IO::FederateIO_HandlerOutputThread
//!	Generated Date	: Thu, 3, Apr 2008  
	File Path	: DefaultComponent\DefaultConfig\FederateIO_HandlerOutputThread.cpp
*********************************************************************/

#include "FederateIO_HandlerOutputThread.h"
// dependency Control 
#include "Control.h"
// operation FederateIO_HandlerOutputThread(FederateInterface*) 
#include "FederateInterface.h"
// link itsFederateIO_Handler 
#include "FederateIO_Handler.h"
// dependency PostOffice 
#include "PostOffice.h"
#include "boost/bind.hpp"
#include "boost/function.hpp"
#include "boost/thread.hpp"

//----------------------------------------------------------------------------
// FederateIO_HandlerOutputThread.cpp                                                                  
//----------------------------------------------------------------------------

//## package Framework::IO 

//## class FederateIO_HandlerOutputThread 

namespace Framework {
    namespace IO {
        
        
        FederateIO_HandlerOutputThread::FederateIO_HandlerOutputThread(FederateInterface* federateInterface) : federateInterface(federateInterface) {
            itsFederateIO_Handler = NULL;
            //#[ operation FederateIO_HandlerOutputThread(FederateInterface*) 
            //#]
        }
        
        FederateIO_HandlerOutputThread::FederateIO_HandlerOutputThread() {
            itsFederateIO_Handler = NULL;
            //#[ operation FederateIO_HandlerOutputThread() 
            itsFederateIO_Handler = NULL;
            //#]
        }
        
        FederateIO_HandlerOutputThread::~FederateIO_HandlerOutputThread() {
            cleanUpRelations();
        }
        
        void FederateIO_HandlerOutputThread::addFederateMessage(FederateMessage* message) {
            //#[ operation addFederateMessage(FederateMessage*) 
            this->addItsFederateMessage(message);
            //#]
        }
        
        void FederateIO_HandlerOutputThread::threadOperation() {
            //#[ operation threadOperation() 
            
            FederateMessage* fm_Ptr;  
                      
            while (true)
            {    
              try
              {  
                boost::detail::thread::lock_ops<boost::mutex>::lock(myMutex);
                
                // Check to see if there's a Federate Message in the list   
                if (itsFederateMessage.empty() != true)
                {                                        
                  // Send the message to the Post Office for delivery.
                  fm_Ptr = *itsFederateMessage.begin();  // Get the first FederateMessage in the list. 
                
                  Framework::Control::getPostOffice()->sendMessage( federateInterface, fm_Ptr);
                     
                  removeItsFederateMessage(fm_Ptr);   // Remove the just-sent FederateMessage from the list.
                }   
              } 
              catch (...)
              {
                boost::detail::thread::lock_ops<boost::mutex>::unlock(myMutex);
              } 
              
              boost::detail::thread::lock_ops<boost::mutex>::unlock(myMutex);
            //              Sleep(1);
            };  
            //#]
        }
        
        FederateInterface* FederateIO_HandlerOutputThread::getFederateInterface() const {
            return federateInterface;
        }
        
        void FederateIO_HandlerOutputThread::setFederateInterface(FederateInterface* p_federateInterface) {
            federateInterface = p_federateInterface;
        }
        
        Framework::IO::FederateIO_Handler* FederateIO_HandlerOutputThread::getItsFederateIO_Handler() const {
            return itsFederateIO_Handler;
        }
        
        void FederateIO_HandlerOutputThread::__setItsFederateIO_Handler(Framework::IO::FederateIO_Handler* p_FederateIO_Handler) {
            itsFederateIO_Handler = p_FederateIO_Handler;
        }
        
        void FederateIO_HandlerOutputThread::_setItsFederateIO_Handler(Framework::IO::FederateIO_Handler* p_FederateIO_Handler) {
            if(itsFederateIO_Handler != NULL)
                {
                    itsFederateIO_Handler->__setItsFederateIO_HandlerOutputThread(NULL);
                }
            __setItsFederateIO_Handler(p_FederateIO_Handler);
        }
        
        void FederateIO_HandlerOutputThread::setItsFederateIO_Handler(Framework::IO::FederateIO_Handler* p_FederateIO_Handler) {
            if(p_FederateIO_Handler != NULL)
                {
                    p_FederateIO_Handler->_setItsFederateIO_HandlerOutputThread(this);
                }
            _setItsFederateIO_Handler(p_FederateIO_Handler);
        }
        
        void FederateIO_HandlerOutputThread::_clearItsFederateIO_Handler() {
            itsFederateIO_Handler = NULL;
        }
        
        std::vector<Framework::IO::FederateMessage*>::const_iterator FederateIO_HandlerOutputThread::getItsFederateMessage() const {
            std::vector<Framework::IO::FederateMessage*>::const_iterator iter;
            iter = itsFederateMessage.begin();
            return iter;
        }
        
        std::vector<Framework::IO::FederateMessage*>::const_iterator FederateIO_HandlerOutputThread::getItsFederateMessageEnd() const {
            return itsFederateMessage.end();
        }
        
        void FederateIO_HandlerOutputThread::addItsFederateMessage(Framework::IO::FederateMessage* p_FederateMessage) {
            itsFederateMessage.push_back(p_FederateMessage);
        }
        
        void FederateIO_HandlerOutputThread::removeItsFederateMessage(Framework::IO::FederateMessage* p_FederateMessage) {
            std::vector<Framework::IO::FederateMessage*>::iterator pos = std::find(itsFederateMessage.begin(), itsFederateMessage.end(),p_FederateMessage);
            if (pos != itsFederateMessage.end()) {
            	itsFederateMessage.erase(pos);
            }
        }
        
        void FederateIO_HandlerOutputThread::clearItsFederateMessage() {
            itsFederateMessage.clear();
        }
        
        void FederateIO_HandlerOutputThread::cleanUpRelations() {
            if(itsFederateIO_Handler != NULL)
                {
                    Framework::IO::FederateIO_HandlerOutputThread* p_FederateIO_HandlerOutputThread = itsFederateIO_Handler->getItsFederateIO_HandlerOutputThread();
                    if(p_FederateIO_HandlerOutputThread != NULL)
                        {
                            itsFederateIO_Handler->__setItsFederateIO_HandlerOutputThread(NULL);
                        }
                    itsFederateIO_Handler = NULL;
                }
            {
                itsFederateMessage.clear();
            }
        }
        
    }
}


/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\FederateIO_HandlerOutputThread.cpp
*********************************************************************/

