/**
 *  Source file for \sa UMPhysicsList
 *  This is used for photons!
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#include "UMHit.hh"
#include "UMSD.hh"

#include "G4ios.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include <iostream>
#include <fstream>

using namespace std;

G4Allocator<UMHit> UMHitAllocator; 

/// Constructor
UMHit::UMHit(const UMHit& right)
{
	UMEDep = right.UMEDep;
	UMParticleName = right.UMParticleName;
	UMProcessName = right.UMProcessName;
	MotherID=right.MotherID;
	Position = right.Position;
    UMPdgId = right.UMPdgId;
}

/// Define = hit operator 
const UMHit& UMHit::operator=(const UMHit& right) //$$
{
	UMEDep = right.UMEDep;
	UMParticleName  = right.UMParticleName;
	UMProcessName  = right.UMProcessName;
	MotherID=right.MotherID;
	Position = right.Position;
	UMPdgId = right.UMPdgId;
    return *this;
}
/// Define == hit operator 
G4bool UMHit::operator==(const UMHit& right) const
{
	return (this==&right) ? 1 : 0;
}

void UMHit::Draw()
{
	/// pass
}

void UMHit::Print()
{
	/// std::ofstream fout("hits.out",ios::app);
	/// fout << std::setw(10) << UMEDep << '\t' << std::setw(20) <<  G4BestUnit(Position, "Length") << "\n";
}


