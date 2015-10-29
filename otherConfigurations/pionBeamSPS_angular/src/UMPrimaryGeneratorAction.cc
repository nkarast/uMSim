/**
 * Source file for \sa UMPrimaryGeneratorAction
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */

#include "UMPrimaryGeneratorAction.hh"
#include "UMDetectorConstruction.hh"

#include "Randomize.hh"

#include "globals.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"

#include "UMConfig.hh"

#include <fstream>
#include <iostream>

UMPrimaryGeneratorAction::UMPrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),
particleGun(0)
{
    
    UMConfig config;
    
    G4int nparticle=1;
    particleGun=new G4ParticleGun(nparticle);		// particles per event
    G4ParticleTable* particleTable=G4ParticleTable::GetParticleTable();
    G4String particleName;
    beamParticle = particleTable->FindParticle(particleName=config.beamParticleName);
    
    // define the energy of the beam
    beamEnergy = config.beamEnergy;

	G4cout << "---> Beam energy : " << config.beamEnergy << G4endl;
    
    // define the distance of the particle gun
    // wrt to the center of the world
    // assuming that the gun is at the center of the detector
    // in a vertical distance of particleGun_Xdistance:
    particleGun_Xdistance = config.particleGun_Xdistance;//2300000.*um;
    particleGun_Ydistance = config.particleGun_Ydistance;//0.0*um;
    particleGun_Z_distance = config.particleGun_Z_distance; //0.0*um;
    
    
    // detector construction related
    pcb_total_thickness = config.pcb_total_thickness; //2000.*um;
    frame_total_thickness = config.frame_total_thickness;//20000*um;
    detector_half_width = config.detector_half_width;//100000.*um;
    detector_total_thickness = pcb_total_thickness+frame_total_thickness; // equals to the width of PCB+Aluminum frame
    
    
    
}

UMPrimaryGeneratorAction::~UMPrimaryGeneratorAction()
{
    delete particleGun;
}

void UMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    
    ///@attention {CAREFULL ABOUT THE Y POSITION HERE! -- This is set for ANGULAR BEAMS!}
    

    G4double positionX = 2.*m;
    // Y axis has a width of 20mm
    // Z axis has a width of 7mm
    G4double Ynumber = G4UniformRand()*20*mm;
    G4double Znumber = G4UniformRand()*7*mm;

    
    particleGun->SetParticlePosition(G4ThreeVector(positionX, -positionX+Ynumber, 0.+Znumber));//new
    particleGun->SetParticleDefinition(beamParticle);

    particleGun->SetParticleEnergy(beamEnergy);
    
    /// the particle gun is particleGun_Xdistance away from the CENTER of the detector
    /// but the maximum opening distance would be aquired if we calculate the angles
    /// with respect to the first frame that the particle impacts
    /// ===>> to calculate the angles we subtract the half_width of the detector
    // G4double bestDistance = particleGun_Xdistance-(detector_total_thickness/2.0);
    //G4cout << "[INFO] PrimaryGenerator : best distance (gun_distance - detector_half_thickness = " << bestDistance << G4endl;
    
    // G4double max_height = sqrt((detector_half_width*detector_half_width)+(detector_half_width*detector_half_width));
    
    
    // G4double tantheta = (max_height/bestDistance);
    // G4double theta = atan(tantheta);
    // G4double phi= (G4UniformRand())*2*pi;
    // G4double cosrand = 1-(G4UniformRand())*(1-cos(theta));
    
    
    // G4double uy= cos(phi) * sqrt(1-cosrand*cosrand);
    // G4double uz= sin(phi) * sqrt(1-cosrand*cosrand);
    // G4double ux =cosrand;
    
    /// set the momentum of X-axis towards the negative direction
    particleGun->SetParticleMomentumDirection(G4ThreeVector(-1,0,0).rotateZ(-45.*deg));
    
    
    /// now that everything is setup generate an event!
    particleGun->GeneratePrimaryVertex(anEvent);
    
}