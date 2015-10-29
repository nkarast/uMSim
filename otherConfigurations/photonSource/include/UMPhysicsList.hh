// $Id: PhysicsList.hh 22 2009-12-22 12:36:46Z schaelic $

#ifndef UMPhysicsList_h
#define UMPhysicsList_h 1

/**
 * @file
 * @brief Defines mandatory user class PhysicsList.
*/

#include "G4VModularPhysicsList.hh"
#include "G4VUserPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4VPhysicsConstructor;

/*!
\brief This mandatory user class provides the physics

It is responsible for
 - Definition of particles
 - Construction of physics processes
 - setting of user cuts
*/

class UMPhysicsList: public G4VModularPhysicsList
{
public:
  //! Constructor
  UMPhysicsList();
  //! Destructor
  ~UMPhysicsList();

protected:
  //! Construct particle and physics (mandatory)
  
	void ConstructParticle();
	void ConstructProcess();
        void AddPhysicsList(const G4String& name);
	void ConstructHadronic();
   
    void SetCuts();
	void SetCutForGamma(G4double);
	void SetCutForElectron(G4double);
	void SetCutForPositron(G4double);        	
	void SetCutForNeutron(G4double);        
	void SetCutForProton(G4double);        
	void AddDecay();
  
private:
	G4double cutForGamma;
	G4double cutForElectron;
	G4double cutForPositron;
	G4double cutForNeutron;
	G4double cutForProton;

	G4String emName;
	G4VPhysicsConstructor*  emPhysicsList;
	G4VPhysicsConstructor*  decayPhysicsList;
 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

 
