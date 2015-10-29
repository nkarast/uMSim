/**
 * Header for the Sensitive Detector Class
 *
 *	The sensitive areas are the only that record Hits
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#ifndef UMSD_h
#define UMSD_h 1

#include "G4VSensitiveDetector.hh"
#include "UMHit.hh"

class UMDetectorConstruction;
class RunAction;
class G4Step;
class G4TouchableHistory;
class G4HCofThisEvent;           // <<- means "H(it) C(ollections) of


/**
 * Defines the SD of the detector construction
 *	stores the hits in the Hit Collection of this Event.
 */
class UMSD : public G4VSensitiveDetector
{
	public:
		UMSD(G4String SDname);
		~UMSD(){};

	public:
 	/// Mandatory class
	G4bool ProcessHits(G4Step *step, G4TouchableHistory *ROhist);
  
	void Initialize(G4HCofThisEvent* HCE);
  	/// defines what happens at the end of each event.
	void EndOfEvent(G4HCofThisEvent* HCE);

	
	private:
		typedef std::map<G4int,UMHit*> hitMap_t; ///Helper mapping layer number with hit
		hitMap_t hitMap;
  
		UMHitsCollection* hitsCollection;      /// Collection of hits in the gas
		
		G4int HCID; /// the Hits Collection ID number 

};

#endif
