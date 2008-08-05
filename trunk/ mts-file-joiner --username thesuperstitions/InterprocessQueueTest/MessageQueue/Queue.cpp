//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Queue.h"
//#include "boost/bind.hpp"
//#include "boost/function.hpp"
#include "boost/thread.hpp"

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------


        
        Queue::~Queue() {
            cleanUpRelations();
        }
        
        void Queue::addMessage(void* message)
        {
            //#[ operation addMessage(void*)
            this->addItsMessage(message);
            //#]
        }
        
        void Queue::threadOperation()
        {
            //#[ operation threadOperation()
            //#]
        }
        
        
        std::vector<void*>::const_iterator Queue::getItsMessage() const
        {
            std::vector<void*>::const_iterator iter;
            iter = itsMessage.begin();
            return iter;
        }
        
        std::vector<void*>::const_iterator Queue::getItsMessageEnd() const {
            return itsMessage.end();
        }
        
        void Queue::addItsMessage(void* p_Message) {
            itsMessage.push_back(p_Message);
        }
        
        void Queue::removeItsMessage(void* p_Message) {
            std::vector<void*>::iterator pos = std::find(itsMessage.begin(), itsMessage.end(),p_Message);
            if (pos != itsMessage.end()) {
            	itsMessage.erase(pos);
            }
        }
        
        void Queue::clearItsMessage() {
            itsMessage.clear();
        }
        
        void Queue::cleanUpRelations()
        {
                itsMessage.clear();
        }

