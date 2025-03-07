//==========================================================================
//  AIDA Detector description implementation 
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : M.Frank
//
//==========================================================================

#ifndef DDG4_GEANT4UIMESSENGER_H
#define DDG4_GEANT4UIMESSENGER_H

// Framework include files
#include <DD4hep/ComponentProperties.h>
#include <DD4hep/Callback.h>
#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>

/// Namespace for the AIDA detector description toolkit
namespace dd4hep {

  /// Namespace for the Geant4 based simulation part of the AIDA detector description toolkit
  namespace sim {

    /// Generic implementation to export properties and actions to the Geant4 command prompt.
    /** @class Geant4UIMessenger Geant4UIMessenger.h DDG4/Geant4UIMessenger.h
     *
     * @author  M.Frank
     * @version 1.0
     */
    class Geant4UIMessenger: public G4UImessenger {
    public:
      typedef std::map<G4UIcommand*, std::string> Commands;
      typedef std::map<G4UIcommand*, Callback> Actions;
    protected:
      /// The UI directory of this component
      G4UIdirectory*   m_directory;
      /// Reference to the property manager corresponding to the component
      PropertyManager* m_properties;
      /// Component name
      std::string      m_name;
      /// Path in the UI hierarchy of this component
      std::string      m_path;
      /// Property update command map
      Commands         m_propertyCmd;
      /// Action map
      Actions          m_actionCmd;

    public:
      /// Initializing constructor
      Geant4UIMessenger(const std::string& name, const std::string& path);
      /// Default destructor
      virtual ~Geant4UIMessenger();
      /// Add a new callback structure
      void addCall(const std::string& name, const std::string& description, const Callback& cb, size_t npar=0);
      /// Add any callback without parameters to the messenger
      template <typename Q, typename R, typename T>
      void addCall(const std::string& name, const std::string& description, Q* p, R (T::*f)()) {
        CallbackSequence::checkTypes(typeid(Q), typeid(T), dynamic_cast<T*>(p));
        addCall(name, description, Callback(p).make(f), 0);
      }
      /// Add any callback with ONE parameter to the messenger
      template <typename Q, typename R, typename T, typename A1>
      void addCall(const std::string& name, const std::string& description, Q* p, R (T::*f)(A1)) {
        CallbackSequence::checkTypes(typeid(Q), typeid(T), dynamic_cast<T*>(p));
        addCall(name, description, Callback(p).make(f), 1);
      }
      /// Export all properties to the Geant4 UI
      void exportProperties(PropertyManager& mgr);
      /// Accept ne property value from Geant4 UI
      void SetNewValue(G4UIcommand *c, G4String val)  override;
      /// Pass current property value to Geant4 UI
      G4String GetCurrentValue(G4UIcommand *c)  override;
    };

  }    // End namespace sim
}      // End namespace dd4hep

#endif // DDG4_GEANT4UIMESSENGER_H
