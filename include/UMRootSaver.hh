/**
 * Header for the ROOT Saver Class
 *
 *	Two ROOT files are created:
 *		- One with general information about the run
 *		- One with per event information for energy deposition, 
 *			particle position and process type as well as 
 *			particle energy and total energy
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#ifndef UMROOTSAVER_HH_
#define UMROOTSAVER_HH_

#include <string>

#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>

#include <TFile.h>
#include "TGraph.h"
#include "UMEventAction.hh"
#include "TNtuple.h"
#include <iostream>
#include "TCanvas.h"
#include <vector>

class TFile;

double const Pi = 3.141592;

double const enchannel=10/1024.;

class UMRootSaver
{
	public:
		UMRootSaver();
		virtual ~UMRootSaver();
		virtual void CreateTree();
		virtual void CloseTree();

		/// 
		/// Imagine that you're writing to a plain txt file...
		/// Call this function whenever you want to add a line
		/// I'll handle the @magic	;)
		///
		virtual void addLine(G4int event, G4double energy, G4String particleName, G4int pdgid, G4String process, G4double xpos, G4double ypos, G4double zpos);
		
	
	
	private:
		TFile* RFile;
		TTree *linetree;
		TTree *infotree;
		unsigned int runCounter;
		
		/**
		 * Some initialization is required
		 */
		int line_event = -1000;
		double line_totalEnergy = 0;
		std::vector<double> line_energy;
		std::vector<std::string> line_particle;
		std::vector<int> line_pdgid;
		std::vector<std::string> line_process;
		std::vector<double> line_xpos;
		std::vector<double> line_ypos;
		std::vector<double> line_zpos;

		double line_above_resistive = 1117.0;
		double line_below_mesh = 1216.0;
		double line_above_mesh = 1240.0;
		double line_below_drift = 6216.0;
		double line_positivey = 50000.;
		double line_negativey = -50000.;
		double line_positivez = 50000.;
		double line_negativez = -50000.;
		double line_positivex = 23000.;
		double line_beam_energy = 0;
		double line_beam_startX = 0;
		double line_beam_startY = 0;
		double line_beam_startZ = 0;
		double line_Argon_percent = 0;
		double line_CO2_percent = 0;

		

};
#endif
