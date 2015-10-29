/**
 * Header for custom Physics List
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#ifndef UMPhysicsList_h
#define UMPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;

/**
 *	UMPhysicsList inherits from G4VModularPhysicsList
*/
class UMPhysicsList: public G4VModularPhysicsList
{
public:
  /// Constructor
  UMPhysicsList();
  /// Destructor
  ~UMPhysicsList();

protected:
  /// Construct particle and physics (mandatory)
  
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

#endif

 
