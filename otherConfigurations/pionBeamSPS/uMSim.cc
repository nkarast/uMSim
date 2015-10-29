/**
 * 	Main function of the package -- executable called `mylar`
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */



#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "UMDetectorConstruction.hh"
#include "UMPhysicsList.hh"
#include "UMPrimaryGeneratorAction.hh"
#include "UMEventAction.hh"
#include "RunAction.hh"
#include "UMSD.hh" 
#include "QGSP_BERT_HP.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BIC_HP.hh" 
#include "G4RadioactiveDecayPhysics.hh" 
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#include "Randomize.hh"
#include "time.h"
#include <cstdlib>
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
//#include "UMConfig.hh"
#include "G4ParticleTable.hh"

#include <fstream>

int main(int argc,char** argv)
{
    // Parser
	G4cout << "######  RUN INFO: " << G4endl;
    G4cout << "This is the 2D mesh version of mylar...." << G4endl;
	G4cout << " Beam     : pion beam 120GeV/c 20x7mm" << G4endl;
	G4cout << " Gas      : Ar:CO2 - 93:7" << G4endl;
	G4cout << " Physics  : BERT only" << G4endl;

	//std::ofstream totalHits("totalHitsFile.dat",std::ofstream::out);
	std::ofstream totalHits("totalHitsFile.csv",std::ofstream::out);
	totalHits<<"event,energy,particleName,pdgid,process,xpos,ypos,zpos\n";

	std::ofstream energyHits("energyHitsFile.csv",std::ofstream::out);
	energyHits<<"event,energy,particleName,pdgid,process,xpos,ypos,zpos\n";
    
    /// RunManager construction
	G4RunManager* runManager = new G4RunManager;

	/// mandatory user initialization classes
	UMDetectorConstruction* UMDetector = new UMDetectorConstruction;
	runManager->SetUserInitialization(UMDetector);

	G4VModularPhysicsList* physics = new QGSP_BERT;
	//G4VModularPhysicsList* physics = new QGSP_BIC_HP;
	runManager->SetUserInitialization(physics);
	//physics->RegisterPhysics(new G4RadioactiveDecayPhysics());

	//~ runManager->SetUserInitialization(UMPhysics);

	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
	
	///set random seed with system time
	G4long seed = time(NULL);
	
	G4long addseed = rand() % (unsigned)time(NULL);
	seed = abs(seed + addseed);
	CLHEP::HepRandom::setTheSeed(seed);

	G4cout << "#\n# The seed for this RanecuEngine is : " << seed << " \n#\n" << G4endl;
	
	/// initialize Geant4 kernel
	runManager->Initialize();

	/// mandatory user action class
	runManager->SetUserAction(new UMPrimaryGeneratorAction);
	/// optional user action classes
	UMEventAction* evt = new UMEventAction(totalHits,energyHits); 
	runManager->SetUserAction(evt);
	runManager->SetUserAction(new RunAction(evt));
    
    
    int numberOfEvent = 1;
    runManager->BeamOn(numberOfEvent);
    

    
 	//////commented out to run in "batch" mode
	#ifdef G4VIS_USE
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
	#endif    
	// Get the pointer to the User Interface manager
	G4UImanager * UImanager = G4UImanager::GetUIpointer();  

	if (argc!=1)   // batch mode  
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else           // interactive mode : define UI session
	{ 
		#ifdef G4UI_USE
		G4UIExecutive * ui = new G4UIExecutive(argc,argv);
		#ifdef G4VIS_USE
		UImanager->ApplyCommand("/control/execute vis.mac");     
		#endif
		ui->SessionStart();
		delete ui;
		#endif
    
		#ifdef G4VIS_USE
		delete visManager;
		#endif     
	}
 
	delete runManager;
	totalHits.close();
	energyHits.close();
	return 0;
}
