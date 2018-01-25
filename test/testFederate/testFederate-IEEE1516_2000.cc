/*
 * Following code is IEEE-1516_2000 specific
 */
#ifndef IEEE1516_2000
#define IEEE1516_2000
#endif

#include "testFederate.hh"

#include <iostream>

bool testFederate::createFederationExecution(std::wstring federationName, std::wstring FOMFile) {
    this->federationName = federationName;
    this->FOMFile        = FOMFile;

    try {
        rtiAmb->createFederationExecution(federationName, FOMFile);
    } catch (rti1516::Exception& e) {
        std::wcout << L"CFE caught Error " << e.what() <<std::endl;
        status = false;
    }
    return status;
}

bool testFederate::destroyFederationExecution() {
    try {
        rtiAmb->destroyFederationExecution(federationName);
    }
    catch (rti1516::Exception& e) {
        std::wcout << L"DFE caught Error " << e.what() <<std::endl;
        status = false;
    }
    return status;
}

bool testFederate::joinFederationExecution() {
    try {
        rtiAmb->joinFederationExecution(name,federationName,*this);
    }
    catch (rti1516::Exception& e) {
        std::wcout << L"JFE caught Error " << e.what() <<std::endl;
    }

    return status;
}

bool testFederate::resignFederationExecution() {
    try {
           rtiAmb->resignFederationExecution(rti1516::CANCEL_THEN_DELETE_THEN_DIVEST);
       }
       catch (rti1516::Exception& e) {
           std::wcout << L"RFE caught Error " << e.what() <<std::endl;
       }
    return status;
}

bool testFederate::getHandles() {
    status = false;
    try {
        OCH_Data = rtiAmb->getObjectClassHandle(L"Data");
        AH_Attr1 = rtiAmb->getAttributeHandle(OCH_Data,L"Attr1");
        AH_Attr2 = rtiAmb->getAttributeHandle(OCH_Data,L"Attr2");
        ICH_Message = rtiAmb->getInteractionClassHandle(L"Message");
        PH_Param1 = rtiAmb->getParameterHandle(ICH_Message,L"Param1");
        PH_Param2 = rtiAmb->getParameterHandle(ICH_Message,L"Param2");
        status = true;
    } catch (rti1516::Exception& e) {
        std::wcout << L"getHandles() caught " << e.what() <<std::endl;
        status = false;
    }
    return status;
}

bool testFederate::publishObjectClassAttribute() { return false;}
bool testFederate::unpublishObjectClassAttribute() { return false;}
bool testFederate::publishInteractionClass() { return false;}
bool testFederate::unpublishInteractionClass() { return false;}

bool testFederate::subscribeObjectClassAttribute() { return false;}
bool testFederate::unsubscribeObjectClassAttribute() { return false;}
bool testFederate::subscribreInteractionClass() { return false;}
bool testFederate::unsubscribreInteractionClass() { return false;}

bool testFederate::evoke() { return false;}
bool testFederate::TAR() { return false;}
bool testFederate::TARA() { return false;}
bool testFederate::enableTR() { return false;}
bool testFederate::disableTR() { return false;}
bool testFederate::enableAD() { return false;}
bool testFederate::disableAD() { return false;}

bool testFederate::specificInitialize() {
    try {
        std::vector< std::wstring > constructorArgs;

        std::auto_ptr <rti1516::RTIambassadorFactory> rtiAmbFactory(new rti1516::RTIambassadorFactory());
        std::auto_ptr <rti1516::RTIambassador > rtiAmbAP = rtiAmbFactory->createRTIambassador(constructorArgs);
        rtiAmb = rtiAmbAP.release();
    } catch (rti1516::Exception& e) {
        std::wcout << L"RTIambassador creation caught Error " << e.what() <<std::endl;
        status = false;
    }
    return status;
}

