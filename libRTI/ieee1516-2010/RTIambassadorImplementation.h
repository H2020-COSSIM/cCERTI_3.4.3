// ----------------------------------------------------------------------------
// CERTI - HLA RunTime Infrastructure
// Copyright (C) 2002-2014  ONERA
//
// This file is part of CERTI-libRTI
//
// CERTI-libRTI is free software ; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation ; either version 2 of
// the License, or (at your option) any later version.
//
// CERTI-libRTI is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY ; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program ; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA
//
// ----------------------------------------------------------------------------
// This interface is used to access the services of the RTI. 

#ifndef RTIambassador_h
#define RTIambassador_h

#include <RTI/RTIambassador.h>
#include <RTI/RTIambassadorFactory.h>
#include "RTIambassadorImplementation.h"
#include "RTIambPrivateRefs.h"

namespace certi
{
class RTI_EXPORT RTI1516ambassador : rti1516e::RTIambassador
{
    friend std::auto_ptr< rti1516e::RTIambassador >
    rti1516e::RTIambassadorFactory::createRTIambassador()
    throw (rti1516e::RTIinternalError);

private:
    RTI1516ambPrivateRefs* privateRefs ;

    // Helper functions
    template<typename T> void
    assignAHSAndExecuteService(const rti1516e::AttributeHandleSet &AHS, T &req, T &rep);
    template<typename T> void
    assignPHVMAndExecuteService(const rti1516e::ParameterHandleValueMap &PHVM, T &req, T &rep);
    template<typename T> void
    assignAHVMAndExecuteService(const rti1516e::AttributeHandleValueMap &AHVM, T &req, T &rep);
    // Helper function for CallBacks
    bool __tick_kernel(bool, TickTime, TickTime)
    throw (rti1516e::SpecifiedSaveLabelDoesNotExist,
           rti1516e::NotConnected,
           rti1516e::RTIinternalError);

protected:
    RTI1516ambassador() throw ();

public:
    virtual
    ~RTI1516ambassador();

    // 4.2
    virtual void connect (
            rti1516e::FederateAmbassador & federateAmbassador,
            rti1516e::CallbackModel theCallbackModel,
            std::wstring const & localSettingsDesignator)
    throw (
            rti1516e::ConnectionFailed,
            rti1516e::InvalidLocalSettingsDesignator,
            rti1516e::UnsupportedCallbackModel,
            rti1516e::AlreadyConnected,
            rti1516e::CallNotAllowedFromWithinCallback,
            rti1516e::RTIinternalError);

    // 4.3
    virtual void disconnect ()
    throw (
            rti1516e::FederateIsExecutionMember,
            rti1516e::CallNotAllowedFromWithinCallback,
            rti1516e::RTIinternalError);
    // 4.5
    virtual void createFederationExecution
    (std::wstring const & federationExecutionName,
            std::wstring const & fullPathNameToTheFDDfile,
            std::wstring const & logicalTimeImplementationName = L"")
    throw (rti1516e::FederationExecutionAlreadyExists,
           rti1516e::CouldNotOpenFDD,
           rti1516e::ErrorReadingFDD,
           rti1516e::CouldNotCreateLogicalTimeFactory,
           rti1516e::NotConnected,
           rti1516e::RTIinternalError);

    virtual void createFederationExecution (
       std::wstring const & federationExecutionName,
       std::vector<std::wstring> const & fomModules,
       std::wstring const & logicalTimeImplementationName = L"")
       throw (
               rti1516e::CouldNotCreateLogicalTimeFactory,
               rti1516e::InconsistentFDD,
               rti1516e::ErrorReadingFDD,
               rti1516e::CouldNotOpenFDD,
               rti1516e::FederationExecutionAlreadyExists,
               rti1516e::NotConnected,
               rti1516e::RTIinternalError);

    virtual void createFederationExecutionWithMIM (
       std::wstring const & federationExecutionName,
       std::vector<std::wstring> const & fomModules,
       std::wstring const & mimModule,
       std::wstring const & logicalTimeImplementationName = L"")
       throw (
               rti1516e::CouldNotCreateLogicalTimeFactory,
               rti1516e::InconsistentFDD,
               rti1516e::ErrorReadingFDD,
               rti1516e::CouldNotOpenFDD,
               rti1516e::DesignatorIsHLAstandardMIM,
               rti1516e::ErrorReadingMIM,
               rti1516e::CouldNotOpenMIM,
               rti1516e::FederationExecutionAlreadyExists,
               rti1516e::NotConnected,
               rti1516e::RTIinternalError);

    // 4.3
    virtual void destroyFederationExecution
    (std::wstring const & federationExecutionName)
    throw (rti1516e::FederatesCurrentlyJoined,
           rti1516e::FederationExecutionDoesNotExist,
           rti1516e::NotConnected,
           rti1516e::RTIinternalError);

    virtual void listFederationExecutions ()
    throw (
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 4.9
    virtual rti1516e::FederateHandle joinFederationExecution
        (std::wstring const & federateType,
               std::wstring const & federationExecutionName,
               std::vector<std::wstring> const & additionalFomModules)
        throw (rti1516e::CouldNotCreateLogicalTimeFactory,
                rti1516e::FederationExecutionDoesNotExist,
                rti1516e::InconsistentFDD,
                rti1516e::ErrorReadingFDD,
                rti1516e::CouldNotOpenFDD,
                rti1516e::SaveInProgress,
                rti1516e::RestoreInProgress,
                rti1516e::FederateAlreadyExecutionMember,
                rti1516e::NotConnected,
                rti1516e::CallNotAllowedFromWithinCallback,
               rti1516e::RTIinternalError);

    virtual rti1516e::FederateHandle joinFederationExecution
    (std::wstring const & federateName,
           std::wstring const & federateType,
           std::wstring const & federationExecutionName,
           std::vector<std::wstring> const & additionalFomModules)
    throw (rti1516e::CouldNotCreateLogicalTimeFactory,
            rti1516e::FederationExecutionDoesNotExist,
            rti1516e::InconsistentFDD,
            rti1516e::ErrorReadingFDD,
            rti1516e::CouldNotOpenFDD,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateAlreadyExecutionMember,
            rti1516e::NotConnected,
            rti1516e::CallNotAllowedFromWithinCallback,
            rti1516e::RTIinternalError);

    // 4.10
    virtual void resignFederationExecution
    (rti1516e::ResignAction resignAction)
    throw (rti1516e::InvalidResignAction,
            rti1516e::OwnershipAcquisitionPending,
            rti1516e::FederateOwnsAttributes,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::CallNotAllowedFromWithinCallback,
            rti1516e::RTIinternalError);

    // 4.11
    virtual void registerFederationSynchronizationPoint
    (std::wstring const & label,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual void registerFederationSynchronizationPoint
    (std::wstring const & label,
            rti1516e::VariableLengthData const & theUserSuppliedTag,
            rti1516e::FederateHandleSet const & syncSet)
    throw (rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 4.14
    virtual void synchronizationPointAchieved
    (std::wstring const & label, bool successfully)
    throw (rti1516e::SynchronizationPointLabelNotAnnounced,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 4.16
    virtual void requestFederationSave
    (std::wstring const & label)
    throw (rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual void requestFederationSave
    (std::wstring const & label,
            rti1516e::LogicalTime const & theTime)
    throw (rti1516e::LogicalTimeAlreadyPassed,
            rti1516e::InvalidLogicalTime,
            rti1516e::FederateUnableToUseTime,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 4.18
    virtual void federateSaveBegun ()
    throw (rti1516e::SaveNotInitiated,
            rti1516e::FederateNotExecutionMember,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 4.19
    virtual void federateSaveComplete ()
    throw (rti1516e::FederateHasNotBegunSave,
            rti1516e::FederateNotExecutionMember,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual void federateSaveNotComplete()
    throw (rti1516e::FederateHasNotBegunSave,
            rti1516e::FederateNotExecutionMember,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 4.21
        virtual void abortFederationSave ()
        throw (rti1516e::FederateNotExecutionMember,
                rti1516e::SaveNotInProgress,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

    // 4.22
    virtual void queryFederationSaveStatus ()
    throw (rti1516e::FederateNotExecutionMember,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 4.24
    virtual void requestFederationRestore
    (std::wstring const & label)
    throw (rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 4.28
    virtual void federateRestoreComplete ()
    throw (rti1516e::RestoreNotRequested,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual void federateRestoreNotComplete ()
    throw (rti1516e::RestoreNotRequested,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);
    // 4.30
    virtual void abortFederationRestore ()
    throw (
            rti1516e::RestoreNotInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);
    // 4.31
    virtual void queryFederationRestoreStatus ()
    throw (rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    /////////////////////////////////////
    // Declaration Management Services //
    /////////////////////////////////////

    // 5.2
    virtual void publishObjectClassAttributes
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSet const & attributeList)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 5.3
    virtual void unpublishObjectClass
    (rti1516e::ObjectClassHandle theClass)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::OwnershipAcquisitionPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual void unpublishObjectClassAttributes
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSet const & attributeList)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::AttributeNotDefined,
            rti1516e::OwnershipAcquisitionPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 5.4
    virtual void publishInteractionClass
    (rti1516e::InteractionClassHandle theInteraction)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 5.5
    virtual void unpublishInteractionClass
    (rti1516e::InteractionClassHandle theInteraction)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 5.6
    virtual void subscribeObjectClassAttributes
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSet const & attributeList,
            bool active, std::wstring const & updateRateDesignator)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 5.7
    virtual void unsubscribeObjectClass
    (rti1516e::ObjectClassHandle theClass)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual void unsubscribeObjectClassAttributes
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSet const & attributeList)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 5.8
    virtual void subscribeInteractionClass
    (rti1516e::InteractionClassHandle theClass,
            bool active = true)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::FederateServiceInvocationsAreBeingReportedViaMOM,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 5.9
    virtual void unsubscribeInteractionClass
    (rti1516e::InteractionClassHandle theClass)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    ////////////////////////////////
    // Object Management Services //
    ////////////////////////////////

    // 6.2
    virtual void reserveObjectInstanceName
    (std::wstring const & theObjectInstanceName)
    throw (rti1516e::IllegalName,
            rti1516e::FederateNotExecutionMember,
           rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.4
    virtual void releaseObjectInstanceName (
            std::wstring const & theObjectInstanceName)
    throw (
            rti1516e::ObjectInstanceNameNotReserved,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.5
    virtual void reserveMultipleObjectInstanceName (
            std::set<std::wstring> const & theObjectInstanceNames)
    throw (
            rti1516e::IllegalName,
            rti1516e::NameSetWasEmpty,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.7
    virtual void releaseMultipleObjectInstanceName (
            std::set<std::wstring> const & theObjectInstanceNames)
    throw (
            rti1516e::ObjectInstanceNameNotReserved,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.8
    virtual rti1516e::ObjectInstanceHandle registerObjectInstance
    (rti1516e::ObjectClassHandle theClass)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::ObjectClassNotPublished,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual rti1516e::ObjectInstanceHandle registerObjectInstance
    (rti1516e::ObjectClassHandle theClass,
            std::wstring const & theObjectInstanceName)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::ObjectClassNotPublished,
            rti1516e::ObjectInstanceNameNotReserved,
            rti1516e::ObjectInstanceNameInUse,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.10
    virtual void updateAttributeValues
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleValueMap const & theAttributeValues,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotOwned,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual rti1516e::MessageRetractionHandle updateAttributeValues
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleValueMap const & theAttributeValues,
            rti1516e::VariableLengthData const & theUserSuppliedTag,
            rti1516e::LogicalTime const & theTime)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotOwned,
            rti1516e::InvalidLogicalTime,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.12
    virtual void sendInteraction
    (rti1516e::InteractionClassHandle theInteraction,
            rti1516e::ParameterHandleValueMap const & theParameterValues,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::InteractionClassNotPublished,
            rti1516e::InteractionClassNotDefined,
            rti1516e::InteractionParameterNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual rti1516e::MessageRetractionHandle sendInteraction
    (rti1516e::InteractionClassHandle theInteraction,
            rti1516e::ParameterHandleValueMap const & theParameterValues,
            rti1516e::VariableLengthData const & theUserSuppliedTag,
            rti1516e::LogicalTime const & theTime)
    throw (rti1516e::InteractionClassNotPublished,
            rti1516e::InteractionClassNotDefined,
            rti1516e::InteractionParameterNotDefined,
            rti1516e::InvalidLogicalTime,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.14
    virtual void deleteObjectInstance
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::DeletePrivilegeNotHeld,
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual rti1516e::MessageRetractionHandle deleteObjectInstance
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::VariableLengthData const & theUserSuppliedTag,
            rti1516e::LogicalTime  const & theTime)
    throw (rti1516e::DeletePrivilegeNotHeld,
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::InvalidLogicalTime,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.16
    virtual void localDeleteObjectInstance
    (rti1516e::ObjectInstanceHandle theObject)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::FederateOwnsAttributes,
            rti1516e::OwnershipAcquisitionPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.19
    virtual void requestAttributeValueUpdate
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual void requestAttributeValueUpdate
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSet const & theAttributes,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.23
    virtual void requestAttributeTransportationTypeChange (
            rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes,
            rti1516e::TransportationType theType)
    throw (
            rti1516e::AttributeAlreadyBeingChanged,
            rti1516e::AttributeNotOwned,
            rti1516e::AttributeNotDefined,
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::InvalidTransportationType,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.25
    virtual void queryAttributeTransportationType (
            rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandle theAttribute)
    throw (
            rti1516e::AttributeNotDefined,
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.27
    virtual void requestInteractionTransportationTypeChange (
            rti1516e::InteractionClassHandle theClass,
            rti1516e::TransportationType theType)
    throw (
            rti1516e::InteractionClassAlreadyBeingChanged,
            rti1516e::InteractionClassNotPublished,
            rti1516e::InteractionClassNotDefined,
            rti1516e::InvalidTransportationType,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 6.29
    virtual void queryInteractionTransportationType (
            rti1516e::FederateHandle theFederate,
            rti1516e::InteractionClassHandle theInteraction)
    throw (
            rti1516e::InteractionClassNotDefined,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    ///////////////////////////////////
    // Ownership Management Services //
    ///////////////////////////////////
    // 7.2
    virtual void unconditionalAttributeOwnershipDivestiture
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotOwned,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.3
    virtual void negotiatedAttributeOwnershipDivestiture
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotOwned,
            rti1516e::AttributeAlreadyBeingDivested,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.6
    virtual void confirmDivestiture
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & confirmedAttributes,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotOwned,
            rti1516e::AttributeDivestitureWasNotRequested,
            rti1516e::NoAcquisitionPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.8
    virtual void attributeOwnershipAcquisition
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & desiredAttributes,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::ObjectClassNotPublished,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotPublished,
            rti1516e::FederateOwnsAttributes,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.9
    virtual void attributeOwnershipAcquisitionIfAvailable
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & desiredAttributes)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::ObjectClassNotPublished,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotPublished,
            rti1516e::FederateOwnsAttributes,
            rti1516e::AttributeAlreadyBeingAcquired,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.12
    virtual void attributeOwnershipReleaseDenied (
            rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes)
    throw (
            rti1516e::AttributeNotOwned,
            rti1516e::AttributeNotDefined,
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.13
    virtual void attributeOwnershipDivestitureIfWanted
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes,
            rti1516e::AttributeHandleSet & theDivestedAttributes) // filled by RTI
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotOwned,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.14
    virtual void cancelNegotiatedAttributeOwnershipDivestiture
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotOwned,
            rti1516e::AttributeDivestitureWasNotRequested,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.15
    virtual void cancelAttributeOwnershipAcquisition
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeAlreadyOwned,
            rti1516e::AttributeAcquisitionWasNotRequested,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.17
    virtual void queryAttributeOwnership
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandle theAttribute)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 7.18
    virtual bool isAttributeOwnedByFederate
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandle theAttribute)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    //////////////////////////////
    // Time Management Services //
    //////////////////////////////

    // 8.2
    virtual void enableTimeRegulation
    (rti1516e::LogicalTimeInterval const & theLookahead)
    throw (rti1516e::TimeRegulationAlreadyEnabled,
            rti1516e::InvalidLookahead,
            rti1516e::InTimeAdvancingState,
            rti1516e::RequestForTimeRegulationPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.4
    virtual void disableTimeRegulation ()
    throw (rti1516e::TimeRegulationIsNotEnabled,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.5
    virtual void enableTimeConstrained ()
    throw (rti1516e::TimeConstrainedAlreadyEnabled,
            rti1516e::InTimeAdvancingState,
            rti1516e::RequestForTimeConstrainedPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.7
    virtual void disableTimeConstrained ()
    throw (rti1516e::TimeConstrainedIsNotEnabled,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.8
    virtual void timeAdvanceRequest
    (rti1516e::LogicalTime const & theTime)
    throw (rti1516e::InvalidLogicalTime,
            rti1516e::LogicalTimeAlreadyPassed,
            rti1516e::InTimeAdvancingState,
            rti1516e::RequestForTimeRegulationPending,
            rti1516e::RequestForTimeConstrainedPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.9
    virtual void timeAdvanceRequestAvailable
    (rti1516e::LogicalTime const & theTime)
    throw (rti1516e::InvalidLogicalTime,
            rti1516e::LogicalTimeAlreadyPassed,
            rti1516e::InTimeAdvancingState,
            rti1516e::RequestForTimeRegulationPending,
            rti1516e::RequestForTimeConstrainedPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.10
    virtual void nextMessageRequest
    (rti1516e::LogicalTime const & theTime)
    throw (rti1516e::InvalidLogicalTime,
            rti1516e::LogicalTimeAlreadyPassed,
            rti1516e::InTimeAdvancingState,
            rti1516e::RequestForTimeRegulationPending,
            rti1516e::RequestForTimeConstrainedPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.11
    virtual void nextMessageRequestAvailable
    (rti1516e::LogicalTime const & theTime)
    throw (rti1516e::InvalidLogicalTime,
            rti1516e::LogicalTimeAlreadyPassed,
            rti1516e::InTimeAdvancingState,
            rti1516e::RequestForTimeRegulationPending,
            rti1516e::RequestForTimeConstrainedPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.12
    virtual void flushQueueRequest
    (rti1516e::LogicalTime const & theTime)
    throw (rti1516e::InvalidLogicalTime,
            rti1516e::LogicalTimeAlreadyPassed,
            rti1516e::InTimeAdvancingState,
            rti1516e::RequestForTimeRegulationPending,
            rti1516e::RequestForTimeConstrainedPending,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.14
    virtual void enableAsynchronousDelivery ()
    throw (rti1516e::AsynchronousDeliveryAlreadyEnabled,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.15
    virtual void disableAsynchronousDelivery ()
    throw (rti1516e::AsynchronousDeliveryAlreadyDisabled,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.16
    virtual bool queryGALT (rti1516e::LogicalTime & theTime)
    throw (rti1516e::FederateNotExecutionMember,
           rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.17
    virtual void queryLogicalTime (rti1516e::LogicalTime & theTime)
    throw (rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.18
    virtual bool queryLITS (rti1516e::LogicalTime & theTime)
    throw (rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.19
    virtual void modifyLookahead
    (rti1516e::LogicalTimeInterval const & theLookahead)
    throw (rti1516e::TimeRegulationIsNotEnabled,
            rti1516e::InvalidLookahead,
            rti1516e::InTimeAdvancingState,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.20
    virtual void queryLookahead (rti1516e::LogicalTimeInterval & interval)
    throw (rti1516e::TimeRegulationIsNotEnabled,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.21
    virtual void retract
    (rti1516e::MessageRetractionHandle theHandle)
    throw (rti1516e::InvalidMessageRetractionHandle,
            rti1516e::TimeRegulationIsNotEnabled,
            rti1516e::MessageCanNoLongerBeRetracted,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.23
    virtual void changeAttributeOrderType
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSet const & theAttributes,
            rti1516e::OrderType theType)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotOwned,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 8.24
    virtual void changeInteractionOrderType
    (rti1516e::InteractionClassHandle theClass,
            rti1516e::OrderType theType)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::InteractionClassNotPublished,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    //////////////////////////////////
    // Data Distribution Management //
    //////////////////////////////////

    // 9.2
    virtual rti1516e::RegionHandle createRegion
    (rti1516e::DimensionHandleSet const & theDimensions)
    throw (rti1516e::InvalidDimensionHandle,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.3
    virtual void commitRegionModifications
    (rti1516e::RegionHandleSet const & theRegionHandleSet)
    throw (rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.4
    virtual void deleteRegion
    (rti1516e::RegionHandle const & theRegion)
    throw (rti1516e::RegionInUseForUpdateOrSubscription,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegion,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.5
    virtual rti1516e::ObjectInstanceHandle registerObjectInstanceWithRegions
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSetRegionHandleSetPairVector const &
            theAttributeHandleSetRegionHandleSetPairVector)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::ObjectClassNotPublished,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotPublished,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegionContext,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual rti1516e::ObjectInstanceHandle registerObjectInstanceWithRegions
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSetRegionHandleSetPairVector const &
            theAttributeHandleSetRegionHandleSetPairVector,
            std::wstring const & theObjectInstanceName)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::ObjectClassNotPublished,
            rti1516e::AttributeNotDefined,
            rti1516e::AttributeNotPublished,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegionContext,
            rti1516e::ObjectInstanceNameNotReserved,
            rti1516e::ObjectInstanceNameInUse,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.6
    virtual void associateRegionsForUpdates
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSetRegionHandleSetPairVector const &
            theAttributeHandleSetRegionHandleSetPairVector)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegionContext,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.7
    virtual void unassociateRegionsForUpdates
    (rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandleSetRegionHandleSetPairVector const &
            theAttributeHandleSetRegionHandleSetPairVector)
    throw (rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e:: InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.8
    virtual void subscribeObjectClassAttributesWithRegions
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSetRegionHandleSetPairVector const &
            theAttributeHandleSetRegionHandleSetPairVector,
            bool active, std::wstring const & updateRateDesignator)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::AttributeNotDefined,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegionContext,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.9
    virtual void unsubscribeObjectClassAttributesWithRegions
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSetRegionHandleSetPairVector const &
            theAttributeHandleSetRegionHandleSetPairVector)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::AttributeNotDefined,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.10
    virtual void subscribeInteractionClassWithRegions
    (rti1516e::InteractionClassHandle theClass,
            rti1516e::RegionHandleSet const & theRegionHandleSet,
            bool active = true)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegionContext,
            rti1516e::FederateServiceInvocationsAreBeingReportedViaMOM,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.11
    virtual void unsubscribeInteractionClassWithRegions
    (rti1516e::InteractionClassHandle theClass,
            rti1516e::RegionHandleSet const & theRegionHandleSet)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.12
    virtual void sendInteractionWithRegions
    (rti1516e::InteractionClassHandle theInteraction,
            rti1516e::ParameterHandleValueMap const & theParameterValues,
            rti1516e::RegionHandleSet const & theRegionHandleSet,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::InteractionClassNotPublished,
            rti1516e::InteractionParameterNotDefined,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegionContext,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual rti1516e::MessageRetractionHandle sendInteractionWithRegions
    (rti1516e::InteractionClassHandle theInteraction,
            rti1516e::ParameterHandleValueMap const & theParameterValues,
            rti1516e::RegionHandleSet const & theRegionHandleSet,
            rti1516e::VariableLengthData const & theUserSuppliedTag,
            rti1516e::LogicalTime const & theTime)
    throw (rti1516e::InteractionClassNotDefined,
            rti1516e::InteractionClassNotPublished,
            rti1516e::InteractionParameterNotDefined,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegionContext,
            rti1516e::InvalidLogicalTime,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 9.13
    virtual void requestAttributeValueUpdateWithRegions
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandleSetRegionHandleSetPairVector const & theSet,
            rti1516e::VariableLengthData const & theUserSuppliedTag)
    throw (rti1516e::ObjectClassNotDefined,
            rti1516e::AttributeNotDefined,
            rti1516e::InvalidRegion,
            rti1516e::RegionNotCreatedByThisFederate,
            rti1516e::InvalidRegionContext,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    //////////////////////////
    // RTI Support Services //
    //////////////////////////
    // 10.2
    virtual rti1516e::ResignAction getAutomaticResignDirective ()
    throw (
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.3
    virtual void setAutomaticResignDirective (
            rti1516e::ResignAction resignAction)
    throw (
            rti1516e::InvalidResignAction,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.4
    virtual rti1516e::FederateHandle getFederateHandle (
            std::wstring const & theName)
    throw (
            rti1516e::NameNotFound,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.5
    virtual std::wstring getFederateName (
            rti1516e::FederateHandle theHandle)
    throw (
            rti1516e::InvalidFederateHandle,
            rti1516e::FederateHandleNotKnown,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.6
    virtual rti1516e::ObjectClassHandle getObjectClassHandle
    (std::wstring const & theName)
    throw (rti1516e::NameNotFound,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.7
    virtual std::wstring getObjectClassName
    (rti1516e::ObjectClassHandle theHandle)
    throw (rti1516e::InvalidObjectClassHandle,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.8
    rti1516e::ObjectClassHandle getKnownObjectClassHandle (
            rti1516e::ObjectInstanceHandle theObject)
    throw (
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.9
    rti1516e::ObjectInstanceHandle getObjectInstanceHandle (
            std::wstring const & theName)
    throw (
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.10
    std::wstring getObjectInstanceName (
            rti1516e::ObjectInstanceHandle theHandle)
    throw (
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.11
    virtual rti1516e::AttributeHandle getAttributeHandle
    (rti1516e::ObjectClassHandle whichClass,
            std::wstring const & theAttributeName)
    throw (rti1516e::InvalidObjectClassHandle,
            rti1516e::NameNotFound,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.12
    virtual std::wstring getAttributeName
    (rti1516e::ObjectClassHandle whichClass,
            rti1516e::AttributeHandle theHandle)
    throw (rti1516e::InvalidObjectClassHandle,
            rti1516e::InvalidAttributeHandle,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.13
    virtual double getUpdateRateValue (
            std::wstring const & updateRateDesignator)
    throw (
            rti1516e::InvalidUpdateRateDesignator,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.14
    virtual double getUpdateRateValueForAttribute (
            rti1516e::ObjectInstanceHandle theObject,
            rti1516e::AttributeHandle theAttribute)
    throw (
            rti1516e::ObjectInstanceNotKnown,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.15
    virtual rti1516e::InteractionClassHandle getInteractionClassHandle
    (std::wstring const & theName)
    throw (rti1516e::NameNotFound,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.16
    virtual std::wstring getInteractionClassName
    (rti1516e::InteractionClassHandle theHandle)
    throw (rti1516e::InvalidInteractionClassHandle,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.17
    virtual rti1516e::ParameterHandle getParameterHandle
    (rti1516e::InteractionClassHandle whichClass,
            std::wstring const & theName)
    throw (rti1516e::InvalidInteractionClassHandle,
            rti1516e::NameNotFound,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.18
    virtual std::wstring getParameterName
    (rti1516e::InteractionClassHandle whichClass,
            rti1516e::ParameterHandle theHandle)
    throw (rti1516e::InvalidInteractionClassHandle,
            rti1516e::InvalidParameterHandle,
            rti1516e::InteractionParameterNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.20
    virtual rti1516e::OrderType getOrderType
    (std::wstring const & orderName)
    throw (rti1516e::InvalidOrderName,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.21
    virtual std::wstring getOrderName
    (rti1516e::OrderType orderType)
    throw (rti1516e::InvalidOrderType,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.18
    virtual rti1516e::TransportationType getTransportationType
    (std::wstring const & transportationName)
    throw (rti1516e::InvalidTransportationName,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.19
    virtual std::wstring getTransportationName
    (rti1516e::TransportationType transportationType)
    throw (rti1516e::InvalidTransportationType,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.15
    virtual rti1516e::DimensionHandleSet getAvailableDimensionsForClassAttribute
    (rti1516e::ObjectClassHandle theClass,
            rti1516e::AttributeHandle theHandle)
    throw (rti1516e::InvalidObjectClassHandle,
            rti1516e::InvalidAttributeHandle,
            rti1516e::AttributeNotDefined,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.17
    virtual rti1516e::DimensionHandleSet getAvailableDimensionsForInteractionClass
    (rti1516e::InteractionClassHandle theClass)
    throw (rti1516e::InvalidInteractionClassHandle,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.12
    virtual rti1516e::DimensionHandle getDimensionHandle
    (std::wstring const & theName)
    throw (rti1516e::NameNotFound,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.13
    virtual std::wstring getDimensionName
    (rti1516e::DimensionHandle theHandle)
    throw (rti1516e::InvalidDimensionHandle,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.14
    virtual unsigned long getDimensionUpperBound
    (rti1516e::DimensionHandle theHandle)
    throw (rti1516e::InvalidDimensionHandle,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.30
        virtual
        rti1516e::DimensionHandleSet getDimensionHandleSet
        (rti1516e::RegionHandle theRegionHandle)
        throw (rti1516e::InvalidRegion,
                rti1516e::FederateNotExecutionMember,
                rti1516e::SaveInProgress,
                rti1516e::RestoreInProgress,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

        // 10.31
        virtual
        rti1516e::RangeBounds getRangeBounds
        (rti1516e::RegionHandle theRegionHandle,
                rti1516e::DimensionHandle theDimensionHandle)
        throw (rti1516e::InvalidRegion,
                rti1516e::RegionDoesNotContainSpecifiedDimension,
                rti1516e::FederateNotExecutionMember,
                rti1516e::SaveInProgress,
                rti1516e::RestoreInProgress,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

        // 10.32
        virtual void setRangeBounds
        (rti1516e::RegionHandle theRegionHandle,
                rti1516e::DimensionHandle theDimensionHandle,
                rti1516e::RangeBounds const & theRangeBounds)
        throw (rti1516e::InvalidRegion,
                rti1516e::RegionNotCreatedByThisFederate,
                rti1516e::RegionDoesNotContainSpecifiedDimension,
                rti1516e::InvalidRangeBound,
                rti1516e::FederateNotExecutionMember,
                rti1516e::SaveInProgress,
                rti1516e::RestoreInProgress,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

        // 10.33
        virtual unsigned long normalizeFederateHandle
        (rti1516e::FederateHandle theFederateHandle)
        throw (rti1516e::FederateNotExecutionMember,
                rti1516e::InvalidFederateHandle,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

        // 10.34
        virtual unsigned long normalizeServiceGroup
        (rti1516e::ServiceGroup theServiceGroup)
        throw (rti1516e::FederateNotExecutionMember,
                rti1516e::InvalidServiceGroup,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

    // 10.22
    virtual void enableObjectClassRelevanceAdvisorySwitch ()
    throw (rti1516e::ObjectClassRelevanceAdvisorySwitchIsOn,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.23
    virtual void disableObjectClassRelevanceAdvisorySwitch ()
    throw (rti1516e::ObjectClassRelevanceAdvisorySwitchIsOff,
            rti1516e::FederateNotExecutionMember,
           rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.24
    virtual void enableAttributeRelevanceAdvisorySwitch ()
    throw (rti1516e::AttributeRelevanceAdvisorySwitchIsOn,
            rti1516e::FederateNotExecutionMember,
           rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.25
    virtual void disableAttributeRelevanceAdvisorySwitch ()
    throw (rti1516e::AttributeRelevanceAdvisorySwitchIsOff,
            rti1516e::FederateNotExecutionMember,
           rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.26
    virtual void enableAttributeScopeAdvisorySwitch ()
    throw (rti1516e::AttributeScopeAdvisorySwitchIsOn,
            rti1516e::FederateNotExecutionMember,
           rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.27
    virtual void disableAttributeScopeAdvisorySwitch ()
    throw (rti1516e::AttributeScopeAdvisorySwitchIsOff,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.28
    virtual void enableInteractionRelevanceAdvisorySwitch ()
    throw (rti1516e::InteractionRelevanceAdvisorySwitchIsOn,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    // 10.29
    virtual void disableInteractionRelevanceAdvisorySwitch ()
    throw (rti1516e::InteractionRelevanceAdvisorySwitchIsOff,
            rti1516e::FederateNotExecutionMember,
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);


    // 10.41
    virtual bool evokeCallback(double approximateMinimumTimeInSeconds)
    throw (rti1516e::CallNotAllowedFromWithinCallback,
            rti1516e::RTIinternalError);

    // 10.38
    virtual bool evokeMultipleCallbacks(double approximateMinimumTimeInSeconds,
            double approximateMaximumTimeInSeconds)
    throw (rti1516e::CallNotAllowedFromWithinCallback,
            rti1516e::RTIinternalError);

    // 10.39
    virtual void enableCallbacks ()
    throw (
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::RTIinternalError);

    // 10.40
    virtual void disableCallbacks ()
    throw (
            rti1516e::SaveInProgress,
            rti1516e::RestoreInProgress,
            rti1516e::RTIinternalError);

    // Return instance of time factory being used by the federation
    virtual std::auto_ptr<rti1516e::LogicalTimeFactory> getTimeFactory () const
                     throw (
                             rti1516e::FederateNotExecutionMember,
                             rti1516e::NotConnected,
                             rti1516e::RTIinternalError);

    virtual rti1516e::FederateHandle decodeFederateHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
            rti1516e::CouldNotDecode,
            rti1516e::FederateNotExecutionMember,
            rti1516e::NotConnected,
            rti1516e::RTIinternalError);

    virtual rti1516e::ObjectClassHandle decodeObjectClassHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
                    rti1516e::CouldNotDecode,
                    rti1516e::FederateNotExecutionMember,
                    rti1516e::NotConnected,
                    rti1516e::RTIinternalError);

    virtual rti1516e::InteractionClassHandle decodeInteractionClassHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
                rti1516e::CouldNotDecode,
                rti1516e::FederateNotExecutionMember,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

    virtual rti1516e::ObjectInstanceHandle decodeObjectInstanceHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
                rti1516e::CouldNotDecode,
                rti1516e::FederateNotExecutionMember,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

    virtual rti1516e::AttributeHandle decodeAttributeHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
                rti1516e::CouldNotDecode,
                rti1516e::FederateNotExecutionMember,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

    virtual rti1516e::ParameterHandle decodeParameterHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
                rti1516e::CouldNotDecode,
                rti1516e::FederateNotExecutionMember,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

    virtual rti1516e::DimensionHandle decodeDimensionHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
                rti1516e::CouldNotDecode,
                rti1516e::FederateNotExecutionMember,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

    virtual rti1516e::MessageRetractionHandle decodeMessageRetractionHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
                rti1516e::CouldNotDecode,
                rti1516e::FederateNotExecutionMember,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

    virtual rti1516e::RegionHandle decodeRegionHandle(
            rti1516e::VariableLengthData const & encodedValue) const
    throw (
                rti1516e::CouldNotDecode,
                rti1516e::FederateNotExecutionMember,
                rti1516e::NotConnected,
                rti1516e::RTIinternalError);

};
}

#endif // RTI_RTI1516ambassador_h
