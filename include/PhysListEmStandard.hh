/**
 * Header for Electromagnetic Interactions Physics List
 * EmStandard is used
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#ifndef PhysListEmStandard_h
#define PhysListEmStandard_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


class PhysListEmStandard : public G4VPhysicsConstructor
{
  public: 
    /// Construnctor
    PhysListEmStandard(const G4String& name = "standard");
   ~PhysListEmStandard();

  public: 
    /// This method is dummy for physics
    void ConstructParticle() {};
 
    /// This method will be invoked in the Construct() method.
    /// each physics process will be instantiated and
    /// registered to the process manager of each particle type 
    void ConstructProcess();
};

#endif








