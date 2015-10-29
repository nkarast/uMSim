/**
 *  The class for the Run Action definition
 *
 * @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 * @version   v2.0
 */

#ifndef RUNACTION_HH_
#define RUNACTION_HH_
#include "G4UserRunAction.hh"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"

#include "UMRootSaver.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>


class G4Run;
class UMEventAction;

/*!
 * \brief The user-defined Run action class 
 *  At the \sa BeginOfRunAction a RootSaver object is created to store the
 *  information
 */
class RunAction : public G4UserRunAction{
public:
  /// Constructor
  RunAction( UMEventAction* evAct );

  /// Destructor
  virtual ~RunAction() {};

  /// At the beggining of each Run execute these statements
  void BeginOfRunAction(const G4Run*);

  /// When the Run ends execute these statements
  void EndOfRunAction(const G4Run*);

	private:
  /// Link the run with the \sa UMRootSaver object (\sa RSaver)
  UMRootSaver RSaver;   		

  /// Link to the to the \sa UMEventAction
  UMEventAction* umEventAction;
 
};

#endif /* RUNACTION_HH_ */
