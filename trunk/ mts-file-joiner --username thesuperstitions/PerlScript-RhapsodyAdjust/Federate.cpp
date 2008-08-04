/********************************************************************
	Rhapsody	: 7.1 
	Login		: rosskw1
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: framework::Control::Federate
//!	Generated Date	: Mon, 19, May 2008  
	File Path	: DefaultComponent\DefaultConfig\Federate.cpp
*********************************************************************/

#include "Federate.h"
// dependency FederateInterfaceFactory 
#include "FederateInterfaceFactory.h"
// operation Federate(FederateFrameworkType,FederateType,FrameworkFederateAmbassador*) 
#include "FrameworkFederateAmbassador.h"
// dependency HLA_PostOffice 
#include "HLA_PostOffice.h"
// dependency PostOffice 
#include "PostOffice.h"

//----------------------------------------------------------------------------
// Federate.cpp                                                                  
//----------------------------------------------------------------------------

//## package framework::Control 

//## class Federate 

namespace framework {
    namespace Control {
        
        
        Federate::Federate(FederateFrameworkType fedFrameworkType, FederateType fedType, FrameworkFederateAmbassador* frameworkFederateAmbassador) {
            thePostOffice = NULL;
            itsFederateIO_Handler = NULL;
            //#[ operation Federate(FederateFrameworkType,FederateType,FrameworkFederateAmbassador*) 
                             
            // Save this class' attributes.
            setFederateFrameworkType(fedFrameworkType);
            setFederateType(fedType);      
            
            setFederate(this);
            
            switch(fedFrameworkType)
            {
              case HLA_FederateFrameworkType :  
                setThePostOffice( static_cast<framework::io::PostOffice*>(new framework::io::hla::HLA_PostOffice(frameworkFederateAmbassador)) );  
              break;
                
              case OASIS_FederateFrameworkType :    
            //    setThePostOffice( static_cast<Framework::io::PostOffice>(new Framework::io::OASIS_PostOffice()) );
              break;
            }; 
            
            // Create the FederateIO_Handler
            setItsFederateIO_Handler(new framework::io::FederateIO_Handler(fedFrameworkType)); 
            getItsFederateIO_Handler()->setItsFederate(this);
            
            //#]
        }
        
        Federate::~Federate() 
        {
          framework::io::hla::HLA_PostOffice* HPO;

          framework::io::FederateIO_Handler* FIOH = getItsFederateIO_Handler();
          delete FIOH;

          framework::io::PostOffice* PO = getThePostOffice();
          switch(getFederateFrameworkType())
          {
            case HLA_FederateFrameworkType :  
              HPO = static_cast<framework::io::hla::HLA_PostOffice*> (getThePostOffice()); 
              delete HPO;
           	break;
                
            case OASIS_FederateFrameworkType :    
            break;
          }; 

          cleanUpRelations();
        }
        
        FederateFrameworkType Federate::getFederateFrameworkType() const {
            return federateFrameworkType;
        }
        
        void Federate::setFederateFrameworkType(FederateFrameworkType p_federateFrameworkType) {
            federateFrameworkType = p_federateFrameworkType;
        }
        
        FederateInterfaceFactory* Federate::getFederateInterfaceFactory() const {
            return federateInterfaceFactory;
        }
        
        void Federate::setFederateInterfaceFactory(FederateInterfaceFactory* p_federateInterfaceFactory) {
            federateInterfaceFactory = p_federateInterfaceFactory;
        }
        
        int Federate::getFederateType() const {
            return federateType;
        }
        
        void Federate::setFederateType(int p_federateType) {
            federateType = p_federateType;
        }
        
        framework::io::FederateIO_Handler* Federate::getItsFederateIO_Handler() const {
            return itsFederateIO_Handler;
        }
        
        void Federate::__setItsFederateIO_Handler(framework::io::FederateIO_Handler* p_FederateIO_Handler) {
            itsFederateIO_Handler = p_FederateIO_Handler;
        }
        
        void Federate::_setItsFederateIO_Handler(framework::io::FederateIO_Handler* p_FederateIO_Handler) {
            if(itsFederateIO_Handler != NULL)
                {
                    itsFederateIO_Handler->__setItsFederate(NULL);
                }
            __setItsFederateIO_Handler(p_FederateIO_Handler);
        }
        
        void Federate::setItsFederateIO_Handler(framework::io::FederateIO_Handler* p_FederateIO_Handler) {
            if(p_FederateIO_Handler != NULL)
                {
                    p_FederateIO_Handler->_setItsFederate(this);
                }
            _setItsFederateIO_Handler(p_FederateIO_Handler);
        }
        
        void Federate::_clearItsFederateIO_Handler() {
            itsFederateIO_Handler = NULL;
        }
        
        framework::io::PostOffice* Federate::getThePostOffice() const {
            return thePostOffice;
        }
        
        void Federate::__setThePostOffice(framework::io::PostOffice* p_PostOffice) {
            thePostOffice = p_PostOffice;
        }
        
        void Federate::_setThePostOffice(framework::io::PostOffice* p_PostOffice) {
            if(thePostOffice != NULL)
                {
                    thePostOffice->__setTheFederate(NULL);
                }
            __setThePostOffice(p_PostOffice);
        }
        
        void Federate::setThePostOffice(framework::io::PostOffice* p_PostOffice) {
            if(p_PostOffice != NULL)
                {
                    p_PostOffice->_setTheFederate(this);
                }
            _setThePostOffice(p_PostOffice);
        }
        
        void Federate::_clearThePostOffice() {
            thePostOffice = NULL;
        }
        
        void Federate::cleanUpRelations() {
            if(itsFederateIO_Handler != NULL)
                {
                    framework::Control::Federate* p_Federate = itsFederateIO_Handler->getItsFederate();
                    if(p_Federate != NULL)
                        {
                            itsFederateIO_Handler->__setItsFederate(NULL);
                        }
                    itsFederateIO_Handler = NULL;
                }
            if(thePostOffice != NULL)
                {
                    framework::Control::Federate* p_Federate = thePostOffice->getTheFederate();
                    if(p_Federate != NULL)
                        {
                            thePostOffice->__setTheFederate(NULL);
                        }
                    thePostOffice = NULL;
                }
        }
        
    }
}


/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\Federate.cpp
*********************************************************************/

