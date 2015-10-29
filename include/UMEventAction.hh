/**
 * Header for \sa UMEventAction
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */


#ifndef UMEventAction_h
#define UMEventAction_h 1

#include "UMDetectorConstruction.hh"
#include "UMSD.hh"
#include "UMRootSaver.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"

//ROOT stuff
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"

#include <fstream>

class G4Event;
class UMRootSaver;

using namespace std;

class UMEventAction : public G4UserEventAction
{
	public:
		UMEventAction(ofstream &totalHits, ofstream &energyHits);
	public:
		~UMEventAction();
	
	/// What happens at the beginning of Event?
	void BeginOfEventAction(const G4Event* anEvent);
	/// What happens at the end of an Event?
	void EndOfEventAction(const G4Event * anEvent);
		
	/// Set up the ROOT saver 
	inline void SetRootSaver(UMRootSaver* saver){
		RSaver = saver;
	}
	
	/// Get the sensitive detector 
	UMSD* GetSensitiveDetector(G4String detname);

	private:
		G4int hitsCollID;
		G4double TotalEDep;
		G4ThreeVector position; //new
		G4double EDep;
		G4int DeposCount;
		G4int mum;
		G4String particle;
		G4String process;
		G4double xpos;
		G4double ypos;
		G4double zpos;
    	G4int partPdgId;
	
		UMRootSaver* RSaver;
		
	 	std::ofstream &ftotalHits;
		std::ofstream &fenergyHits;
};
#endif
