/**
 * Header for the Detector Construction
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#ifndef UMDetectorConstruction_h
#define UMDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "UMSD.hh"


class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4Element;


/** Header for detector construction for the MicroMeGaS detector
 *	 
 *	All materials and \sa calculateDensity function is declared
 */
class UMDetectorConstruction : public G4VUserDetectorConstruction
{		
	public:
		UMDetectorConstruction();
		~UMDetectorConstruction();

	public:
		G4VPhysicalVolume* Construct();
		// G4ElectricField*        fEMfield;
		// G4FieldManager*         fFieldMgr;

		/// Calculates the density of a mixture of gasses given the relative molecular weight and the percentage
    	G4double calculateDensity(G4double molWeightA, G4double perCentA, G4double molWeightB, G4double perCentB);

	private:
    
		void DefineMaterials();
		G4Material *Al,  *Fe, *Cu,  *Na, *Ca, *Si, *Mg, *C, *Zn;
		G4Material *Na2O, *CaO, *MgO, *Al2O3, *Cl, *Epoxy, *SiO2, *Mylar, *CO2, *ArCO2, *ResStripMat,
		  *ArgonGas, *N2, *Air, *O2, *G10, *DryAir, *water, *H2, *Kapton, *StainlessSteel, *Brass, *Graphite;
		G4VPhysicalVolume* ConstructDetector();
};


#endif
