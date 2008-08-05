/*********************************************************************
	Rhapsody	: 7.1 
	Login		: rosskw1
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Framework::IO::FederateIO_InputThread
//!	Generated Date	: Wed, 9, Apr 2008  
	File Path	: DefaultComponent\DefaultConfig\FederateIO_InputThread.h
*********************************************************************/


#ifndef FederateIO_InputThread_H 

#define FederateIO_InputThread_H 

#include <oxf/oxf.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Configuration.h"
#include "RTI\RTI1516.h"
#include "IO.h"
// class FederateIO_InputThread 
#include "FederateIO_OutputThread.h"

//----------------------------------------------------------------------------
// FederateIO_InputThread.h                                                                  
//----------------------------------------------------------------------------


namespace Framework {
    
    namespace Control {
        class Federate;
        
    } 
    
namespace IO {
    class FederateIO_Handler;
    class PostOffice;
    
} 

namespace utils {
    class Sleep;
}

}


//## package Framework::IO 

#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif

namespace Framework {
    namespace IO {
        //## class FederateIO_InputThread 
        class FederateIO_InputThread : public FederateIO_OutputThread {
        
        
        ////    Constructors and destructors    ////
        public :
            
            //## auto_generated 
            FederateIO_InputThread();
            
            //## auto_generated 
            ~FederateIO_InputThread();
        
        
        ////    Operations    ////
        public :
            
            //## operation threadOperation() 
            void threadOperation();
        
        
        ////    Additional operations    ////
        public :
            
            //## auto_generated 
            FederateIO_Handler* getItsFederateIO_Handler_1() const;
            
            //## auto_generated 
            void setItsFederateIO_Handler_1(FederateIO_Handler* p_FederateIO_Handler);
        
        
        ////    Framework operations    ////
        public :
            
            //## auto_generated 
            void __setItsFederateIO_Handler_1(FederateIO_Handler* p_FederateIO_Handler);
            
            //## auto_generated 
            void _setItsFederateIO_Handler_1(FederateIO_Handler* p_FederateIO_Handler);
            
            //## auto_generated 
            void _clearItsFederateIO_Handler_1();
        
        protected :
            
            //## auto_generated 
            void cleanUpRelations();
        
        
        ////    Relations and components    ////
        protected :
            
            FederateIO_Handler* itsFederateIO_Handler_1;		//## link itsFederateIO_Handler_1 
            
        
        
        };
    }
}


#endif  
/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\FederateIO_InputThread.h
*********************************************************************/

