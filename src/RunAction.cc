/**
 * 	Source for \sa RunAction
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */
#include "RunAction.hh"
#include "UMEventAction.hh"
#include "UMRootSaver.hh"
#include "G4Run.hh"
#include <sstream>
#include <iostream>


/// Constructor
RunAction::RunAction(UMEventAction* theEventAction ) : umEventAction(theEventAction)//,totalHits("totalHitsFile.dat",std::ofstream::app)
{
	/// Create an instance of RootSaver
	umEventAction->SetRootSaver( &RSaver );
}

/// At the start of the Run create the ROOT trees
void RunAction::BeginOfRunAction(const G4Run* aRun )
{	
	
	G4cout<<"Starting Run: "<<aRun->GetRunID()<<G4endl;
	///For each run a new TTree is created, with default names
	G4cout << "[INFO - RunAction::BeginOfRunAction] Creating Tree" << G4endl;
	RSaver.CreateTree();
}

/// at the end of a run print out some info
void RunAction::EndOfRunAction( const G4Run* aRun )
{
	G4cout<<"Ending Run: "<<aRun->GetRunID()<<G4endl;
	G4cout<<"Number of events: "<<aRun->GetNumberOfEvent()<<G4endl;

	RSaver.CloseTree();
}
