/**
 *  Source file for \sa UMPhysicsList
 *  This is used for photons!
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#include "UMPhysicsList.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4EmPenelopePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4LossTableManager.hh"
#include "G4ProcessManager.hh"


//---------------------------------------Constructor & Destructor-------------------------------------

UMPhysicsList::UMPhysicsList():  G4VUserPhysicsList()
{
	G4LossTableManager::Instance();

	defaultCutValue = 1.*um; 	
	
	cutForGamma   = defaultCutValue ;      
	cutForElectron  = defaultCutValue ;    
	cutForPositron  = defaultCutValue ;    
	
	SetVerboseLevel(1);

	/// EM physics : EmPenelope + DecayPhysics
	emPhysicsList = new G4EmPenelopePhysics();
	decayPhysicsList = new G4DecayPhysics();
}

UMPhysicsList::~UMPhysicsList()
{
	delete emPhysicsList;
}

//-------------------------------------------------------Particles------------------------------------------------------

#include "G4ParticleTypes.hh"

// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

// leptons
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

// Mesons
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4PionZero.hh"
#include "G4Eta.hh"
#include "G4EtaPrime.hh"

#include "G4KaonPlus.hh"
#include "G4KaonMinus.hh"
#include "G4KaonZero.hh"
#include "G4AntiKaonZero.hh"
#include "G4KaonZeroLong.hh"
#include "G4KaonZeroShort.hh"

// Baryons
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Neutron.hh"
#include "G4AntiNeutron.hh"

// Nuclei
#include "G4Alpha.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4GenericIon.hh"

void UMPhysicsList::ConstructParticle()
{
  /// @brief     {In this method, static member functions should be called
  /// for all particles which you want to use.
  /// This ensures that objects of these particle types will be
  /// created in the program. }
	
  // pseudo-particles
      G4Geantino::GeantinoDefinition();
      G4ChargedGeantino::ChargedGeantinoDefinition();
  
  // gamma
      G4Gamma::GammaDefinition();
  
  // optical photon
      G4OpticalPhoton::OpticalPhotonDefinition();

  // leptons
      G4Electron::ElectronDefinition();
      G4Positron::PositronDefinition();
      G4MuonPlus::MuonPlusDefinition();
      G4MuonMinus::MuonMinusDefinition();

      G4NeutrinoE::NeutrinoEDefinition();
      G4AntiNeutrinoE::AntiNeutrinoEDefinition();
      G4NeutrinoMu::NeutrinoMuDefinition();
      G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();  

  // mesons
      G4PionPlus::PionPlusDefinition();
      G4PionMinus::PionMinusDefinition();
      G4PionZero::PionZeroDefinition();
      G4Eta::EtaDefinition();
      G4EtaPrime::EtaPrimeDefinition();
      G4KaonPlus::KaonPlusDefinition();
      G4KaonMinus::KaonMinusDefinition();
      G4KaonZero::KaonZeroDefinition();
      G4AntiKaonZero::AntiKaonZeroDefinition();
      G4KaonZeroLong::KaonZeroLongDefinition();
      G4KaonZeroShort::KaonZeroShortDefinition();

  // barions
      G4Proton::ProtonDefinition();
      G4AntiProton::AntiProtonDefinition();
      G4Neutron::NeutronDefinition();
      G4AntiNeutron::AntiNeutronDefinition();

  // ions
      G4Deuteron::DeuteronDefinition();
      G4Triton::TritonDefinition();
      G4He3::He3Definition();
      G4Alpha::AlphaDefinition();
      G4GenericIon::GenericIonDefinition();
}

//--------------------------------------------------Process--------------------------------------------------------------
void UMPhysicsList::ConstructProcess()
{
  
	// transportation	
	//
	AddTransportation();
	
	AddDecay();
  ///
	///electromagnetic physics list
	///
	emPhysicsList->ConstructProcess();
  
	decayPhysicsList->ConstructProcess();
}

//---------------------------------------------------Decay----------------------------------------------------------------

#include "G4Decay.hh"

void UMPhysicsList::AddDecay()
{
  ///
  /// decay process
  ///
  G4Decay* fDecayProcess = new G4Decay();

  theParticleIterator->reset();
  while( (*theParticleIterator)() )
	{
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();

		if (fDecayProcess->IsApplicable(*particle) && !particle->IsShortLived()) 
		{ 
			pmanager ->AddProcess(fDecayProcess);

			/// set ordering for PostStepDoIt and AtRestDoIt
			pmanager ->SetProcessOrdering(fDecayProcess, idxPostStep);
			pmanager ->SetProcessOrdering(fDecayProcess, idxAtRest);
		}
	}
}

//-------------------------------NEW CUTS-------------------------------------------------------------------------------
void UMPhysicsList::SetCuts(){
  ///pass
}
