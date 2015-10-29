/**
 * Source for the \sa UMSensitiveDetector
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */
 
#include "UMSD.hh"
#include "UMHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include <fstream>
#include <iostream>
#include "G4Track.hh" 
#include "G4VProcess.hh"


UMSD::UMSD(G4String SDname) : G4VSensitiveDetector(SDname){
	G4cout<<"Creating SD with name: "<<SDname<<G4endl;
	/// @brief{'collectionName' is a protected data member of base class G4VSensitiveDetector.
	/// Here we declare the name of the collection we will be using.}
	G4String myCollectionName = "UMCollection";
	
	/// @brief{Note that we may add as many collection names we would wish: ie
	// a sensitive detector can have many collections.
	// Add myCollectionName to the vector of names called collectionName variable
	// Use insert method of std::vector<> }
	collectionName.insert(myCollectionName);
	
	HCID = -1;
	hitsCollection = NULL;
}

   G4bool UMSD::ProcessHits(G4Step * step, G4TouchableHistory*){
	/// Get the track for the step
	G4Track* thistrack   = step->GetTrack();
	
	/// Generate the info for this track (position, energy, particle, etc)
	G4ThreeVector Position = thistrack->GetPosition();
	G4double edep = step->GetTotalEnergyDeposit();
	G4String ParticleName = thistrack->GetDefinition()->GetParticleName();
	G4int MotherID = thistrack->GetParentID();
    G4int PdgId = thistrack->GetDefinition()->GetPDGEncoding();
	G4String processName ;
	if(thistrack->GetCreatorProcess()!=0)
		processName = thistrack->GetCreatorProcess()->GetProcessName();
   
	/// Generate a new UMHit and store the information
	UMHit * newHit = new UMHit();                                          
	newHit->SetUMEDep(edep);
	newHit->SetUMParticleName(ParticleName);
	newHit->SetUMProcessName(processName);
	newHit->SetPosition(Position);
	newHit->SetMotherID(MotherID);
    newHit->SetUMPdgId(PdgId);
	
	newHit->Print();
	newHit->Draw();

	/// then insert the hit into the Hits Collection
	hitsCollection->insert(newHit);
	return true;
}

void UMSD::Initialize(G4HCofThisEvent * HCE){	
	// Creation of the collection
	hitsCollection = new UMHitsCollection(SensitiveDetectorName,collectionName[0]);
	
	/// To insert the collection, we need to get an index for it. This index
	/// is unique to the collection. It is provided by the GetCollectionID(...)
	/// method (which calls what is needed in the kernel to get this index).
	
	
	if (HCID < 0)
	{
		HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}
	HCE->AddHitsCollection(HCID, hitsCollection);
	
	hitMap.clear();
	

}

/// do nothing - \sa EndOfEventAction will take care of that
void UMSD::EndOfEvent(G4HCofThisEvent* HCE)
{
	// hitsCollection->PrintAllHits(); // bah
}

