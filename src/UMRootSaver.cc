/**
 * Source for the \sa UMRootSaver class
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */
 

#include "UMRootSaver.hh"
#include "UMEventAction.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "TNtuple.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH1F.h"
#include <TH2F.h>
#include "TMath.h"

#include <sstream> // strings 
#include <cassert> //assert
#include <string>
#include "UMConfig.hh"

using namespace std;


/**
 * @brief{The Class creates a ROOT saver object with two trees to be
 *         output}
 *
 */
UMRootSaver::UMRootSaver() : RFile(0),runCounter(1)//, line_energy(new std::vector<double>()), line_particle( new std::vector<std::string>()), line_pdgid( new std::vector<int>()),line_process( new std::vector<std::string>()),line_xpos( new std::vector<double>()),line_ypos( new std::vector<double>()),line_zpos( new std::vector<double>())
{	

		cout << "[INFO - UMRootSaver::UMRootSaver] Initialized UMRootSaver variables" << endl;
}

UMRootSaver::~UMRootSaver()
{
    if(RFile) delete RFile;
}

void UMRootSaver::CreateTree()
{

	std::ostringstream fn;
    fn<<"output.root";  /// name this output to handle for multiple job submission
	RFile = TFile::Open(fn.str().data(), "recreate");

	cout<<"Tree for Run "<< runCounter<<endl; /// useless...

	/// Load the configuration
   	UMConfig config;

   	/// set some global run info to the Run
	line_beam_energy=config.beamEnergy;
    line_beam_startX=config.particleGun_Xdistance;
    line_beam_startY=-config.particleGun_Xdistance;
    line_beam_startZ=config.particleGun_Z_distance;
	line_Argon_percent=config.ArPerCent_norm;
    line_CO2_percent=config.CO2PerCent_norm;

    /**
     * Create the two trees and their branches
     */
    RFile->cd();
	linetree = new TTree("Geant4","Geant4");
	linetree->Branch("eventNumber",&line_event,"eventNumber/I");
	linetree->Branch("totalEventEnergy",&line_totalEnergy,"totalEventEnergy/D");
	linetree->Branch("energy",&line_energy);
	linetree->Branch("particleName",&line_particle);
	linetree->Branch("pdgId",&line_pdgid);
	linetree->Branch("processName",&line_process);
	linetree->Branch("xPos",&line_xpos);
	linetree->Branch("yPos",&line_ypos);
	linetree->Branch("zPos",&line_zpos);


	infotree = new TTree("Info","Info");
	infotree->Branch("aboveResistive",&line_above_resistive,"aboveResistive/D");
	infotree->Branch("belowMesh",&line_below_mesh,"belowMesh/D");
	infotree->Branch("aboveMesh",&line_above_mesh,"aboveMesh/D");
	infotree->Branch("belowDrift",&line_below_drift,"belowDrift/D");

	infotree->Branch("totalPositiveY",&line_positivey,"totalPositiveY/D");
	infotree->Branch("totalNegativeY",&line_negativey,"totalNegativeY/D");
	infotree->Branch("totalPositiveZ",&line_positivez,"totalPositiveZ/D");
	infotree->Branch("totalNegativeZ",&line_negativez,"totalNegativeZ/D");
	infotree->Branch("totalPositiveX",&line_positivex,"totalPositiveX/D");

	infotree->Branch("beamEnergy",&line_beam_energy,"beamEnergy/D");
	infotree->Branch("beamPositionX",&line_beam_startX,"beamPositionX/D");
	infotree->Branch("beamPositionY",&line_beam_startY,"beamPositionY/D");
	infotree->Branch("beamPositionZ",&line_beam_startZ,"beamPositionZ/D");

	infotree->Branch("gasArgonPercentage",&line_Argon_percent,"gasArgonPercentage/D");
	infotree->Branch("gasCO2Percentage",&line_CO2_percent,"gasCO2Percentage/D");
	infotree->Fill();
		
}


void UMRootSaver::CloseTree(){

	
	linetree->Fill();  /// this is for the last event to be written, since we add one line per `addLine` call
	linetree->Write();	
	infotree->Write();	
	RFile->Close();
	
}


/// 
///	Here is where all the ROOT magic happens
///
void UMRootSaver::addLine(G4int event, G4double energy, G4String particleName, G4int pdgid, G4String process, G4double xpos, G4double ypos, G4double zpos){

	// cout << "[DEBUG - UMRootSaver::addLine] Input is : " << event<<", " <<energy<<", " <<particleName<<", " <<pdgid<<", " <<process<<", " <<xpos<<", " <<ypos<<", " <<zpos << endl;

	// cout << "[DEBUG - UMRootSaver::addLine] linetree =  "  << linetree << endl;
	// cout << "[DEBUG - UMRootSaver::addLine] line_event =  "  << line_event << endl;
	// cout << "[DEBUG - UMRootSaver::addLine] linetree entries =  "  << linetree->GetEntries() << endl;

	if (event == line_event || line_event == - 1000 /* for the first event */){
		// cout << "[DEBUG - UMRootSaver::addLine] Within event==line_event " << endl;
		line_event=event;

		line_energy.push_back(energy);
		line_particle.push_back(particleName);
		line_pdgid.push_back(pdgid);
		line_process.push_back(process);
		line_xpos.push_back(xpos);
		line_ypos.push_back(ypos);
		line_zpos.push_back(zpos);
	}
	else if (event != line_event){
		// cout << "[DEBUG - UMRootSaver::addLine] Within event!=line_event " << endl;
		// first loop for total energy
		double loopEnergy = 0.;
		for(unsigned int i=0; i<line_energy.size();i++){
			loopEnergy+=line_energy.at(i);
		}
		// cout << "[DEBUG - UMRootSaver::addLine] Calculating total energy of event  " << endl;
		line_totalEnergy = loopEnergy;
		// then fill
		linetree->Fill();
		// cout << "[DEBUG - UMRootSaver::addLine] Filling Tree.. Now it has entries:  "  << linetree->GetEntries() << endl;
		// then clear
		// cout << "[DEBUG - UMRootSaver::addLine] Resetting values  " << endl;
		line_energy.clear();
		line_particle.clear();
		line_pdgid.clear();
		line_process.clear();
		line_xpos.clear();
		line_ypos.clear();
		line_zpos.clear();
		line_totalEnergy=0.;
		line_event = 0 ;
		// then set values
		// cout << "[DEBUG - UMRootSaver::addLine] Setting values for new event  " << endl;
		line_event=event;
		line_energy.push_back(energy);
		line_particle.push_back(particleName);
		line_pdgid.push_back(pdgid);
		line_process.push_back(process);
		line_xpos.push_back(xpos);
		line_ypos.push_back(ypos);
		line_zpos.push_back(zpos);



	}//else if
	
}