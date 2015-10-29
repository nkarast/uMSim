/**
 *  Source file for \sa UMEventAction
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#include "UMEventAction.hh"
#include "UMRootSaver.hh"
#include "UMHit.hh"
#include "UMSD.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"

#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include "UMConfig.hh"

#include <fstream>
#include <iostream>
#include "TROOT.h"

#include "TFile.h"
#include "TTree.h"
using namespace std;

/// Constructor
UMEventAction::UMEventAction(ofstream &totalHits, ofstream &energyHits): DeposCount(0),  mum(0), RSaver(0), ftotalHits(totalHits), fenergyHits(energyHits)//,totalHits("totalHitsFile.dat",std::ofstream::app)// umhisto(0),printModulo(1),hitsCollName("UMCollection"),
{

    hitsCollID=-1;
    // ftotalHits = totalHits;  // is to use a non serialized output
}

/// Destructor
UMEventAction::~UMEventAction()
{
	   /// pass
}

/// Get the Sensitive Detector
UMSD* UMEventAction::GetSensitiveDetector(G4String detname)
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    UMSD* sens = static_cast<UMSD*>(SDman->FindSensitiveDetector(detname));
    return sens;
}

/// At the begin of event setup the SD Manager and the hits Collection
void UMEventAction::BeginOfEventAction(const G4Event* anEvent)
{

    // G4cout << "#======== Event " << anEvent-> GetEventID() << "========" <<G4endl;

     if (anEvent->GetEventID()%100000==0)
     {
         G4cout << "Event " << anEvent-> GetEventID() <<G4endl;
     }//endif
    
    
    if ( hitsCollID == -1 )
    {
        G4SDManager * SDman = G4SDManager::GetSDMpointer();
        hitsCollID = SDman->GetCollectionID("UMCollection");
    }//endif
    
}

/// At the end of the event...
void UMEventAction::EndOfEventAction(const G4Event* anEvent)
{
    UMConfig config;
    
    if (hitsCollID<0)
    return;
    
    G4HCofThisEvent* EventHitColl = anEvent->GetHCofThisEvent();
    UMHitsCollection* hits = NULL;
    
    if (EventHitColl)
    {
        hits = (UMHitsCollection*)(EventHitColl->GetHC(hitsCollID));
    }//endif
    
    int n_hit = hits->entries();
    
    if (hits) //maria if!!!
    {
        
        typedef std::vector<UMHit*>::const_iterator hitsVector_it;
        hitsVector_it hit = hits->GetVector()->begin();
        hitsVector_it end = hits->GetVector()->end();
        
        EDep=0.0;
        TotalEDep=0.0;
        //areaEDep=0.0;
        //partEDep=0.0;
        //startEDep=0.0;
        //b=1000;
        //elecIoni = false;
        //strange = false;
        //hadrontime=false;
        //hIoniz=false;
        partPdgId = -100000000;
        
        mum = -1;
        
        
        /// loop over hits
        for ( ; hit != end ; ++hit){

            /// Get the information from the hit
            EDep = (*hit)->GetUMEDep();
            mum=(*hit)->GetMotherID();
            particle=(*hit)->GetUMParticleName();
            position=(*hit)->GetPos();
            process=(*hit)->GetUMProcessName();
            
            xpos=position.getX(); /// @attention {should be given in mm !!!}
            ypos=position.getY();
            zpos=position.getZ();
            
            partPdgId = (*hit)->GetUMPdgId();

            if (process==""){process="None";}
         
            /// uncomment below to write non-serialised file line 
            // ftotalHits<< anEvent->GetEventID() << "," << EDep/keV << "," << particle  << "," <<  partPdgId << "," << process  << "," << xpos/um  << "," << ypos/um << "," << zpos/um << "\n";
            // G4cout << "addline():"<< G4endl;
        
            ///
            /// to save up some storage save only if energy deposited within 
            /// the drift gas volumn 
            /// and if the energy is larger than 26eV = ionisation of Argon
            ///
            if (((xpos>=1117.*um)&&(xpos<1216.*um))||((xpos>=1240.*um)&&(xpos<6216.*um))){
                if(ypos>=-50000.*um && ypos<=50000.*um){
                    if(zpos>=-50000.*um && zpos<=50000.*um){
                        if (EDep>26.0*eV){
                            /// @attention {position in um, energy in keV} 
			       		    RSaver->addLine(anEvent->GetEventID(), EDep/keV, particle, partPdgId, process, xpos/um, ypos/um, zpos/um);
                        }//edep
                    }//zpos
                }//ypos
            }//xpos
          
        }//end for hits
    }// end if hits
    
}// end of function

