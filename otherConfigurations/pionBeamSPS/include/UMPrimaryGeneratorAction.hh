/**
 * Header for the Particle Generator
 *
 *  The class also makes use of the UMConfig configuration
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */


#ifndef UMPrimaryGeneratorAction_h
#define UMPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"  // use these instead of globals.hh for units
#include "G4SystemOfUnits.hh"


class G4ParticleGun;
class G4Event;

class UMPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    UMPrimaryGeneratorAction();
    virtual ~UMPrimaryGeneratorAction();
public:
    void GeneratePrimaries(G4Event* anEvent);
private:
    G4ParticleGun* particleGun;
    
    /// some definitions
    G4ParticleDefinition* beamParticle;
    G4String beamParticleName;
    G4double beamEnergy;
    
    G4double particleGun_Xdistance;
    G4double particleGun_Ydistance;
    G4double particleGun_Z_distance;
    
    G4double pcb_total_thickness;
    G4double frame_total_thickness;
    G4double detector_half_width;
    G4double detector_total_thickness;
    
    G4double phi_angle, theta_angle;
    G4double dummy1, dummy2; 
};

#endif
