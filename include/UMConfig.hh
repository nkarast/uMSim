    #ifndef UMCONFIG_H
    #define UMCONFIG_H

    #include "G4PhysicalConstants.hh"
    #include "G4SystemOfUnits.hh"
    #include "globals.hh"
    /**
     * "Configuration" header for the package
     *
     *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
     *  @version   v2.0
     */

    struct UMConfig{

    ///
    /// Gas related configuration
    ///
    G4double ArMolWeight  = 39.948;
    G4double ArPerCent_norm    = 0.93;  // normalized to Unity
    G4double ArPerCent_perCent    = 93.*perCent;
        
    G4double CO2MolWeight = 44.01;
    G4double CO2PerCent_norm   = 0.07;
    G4double CO2PerCent_perCent   = 7.*perCent;

    G4double temperature = 273.15*kelvin;
    G4double pressure = 1.*atmosphere;


    ///
    /// Geometry related configuration
    ///
    G4double world_halfX            = 250.*cm;
    G4double world_halfY            = 250.*cm;
    G4double world_halfZ            = 250.*cm;

    G4double null                   = 0.*um;

    G4double detectorVol_halfX      = 25000.*um;
    G4double detectorVol_halfY      = 500000.*um;
    G4double detectorVol_halfZ      = 500000.*um;

    G4double pcb_halfX              = 1000.*um;
    G4double pcb_halfY              = 86800.*um;
    G4double pcb_halfZ              = 86800.*um;

    //G4double frame_half_thickness   = 15500.*um;
    G4double frame_halfX            = 9500.*um;//10500.*um;
    G4double frame_halfY            = 86800.*um;//100000.*um;
    G4double frame_halfZ            = 86800.*um;//100000.*um;

    G4double frame_hole_halfX       = 9600.*um;//10500.*um;
    G4double frame_hole_halfY       = 71300.*um;//100000.*um;
    G4double frame_hole_halfZ       = 71300.*um;//100000.*um;

    G4double topBrass_halfX         = 17.5*um;
    G4double topBrass_halfY         = 86800.*um;//100000.*um;
    G4double topBrass_halfZ         = 86800.*um;//100000.*um;
    G4double topPCB_halfX           = 982.5*um; //pcb half x - brass half x
    G4double topPCB_halfY           = 86800.*um;//100000.*um;
    G4double topPCB_halfZ           = 86800.*um;//100000.*um;

    G4double topHole_halfX          = 1000.*um; //pcb half x - brass half x
    G4double topHole_halfY          = 50200*um;//100000.*um;
    G4double topHole_halfZ          = 50200.*um;//100000.*um;

    G4double active_area_halfY      = 50000.*um;
    G4double active_area_halfZ      = 50000.*um;

    G4double strip_halfX            = 8.5*um;
    G4double strip_halfY            = 75.*um;
    G4double strip_halfZ            = 50000.*um;
    G4double strip_pitch            = 250.*um;

    G4double glue_block_halfX       = 4.*um;
    G4double glue_block_halfY       = 50000.*um;
    G4double glue_block_halfZ       = 50000.*um;
    
    G4double glue_strip_halfX       = strip_halfX;
    G4double glue_strip_halfY       = (strip_pitch-2.*strip_halfY)/2.;
    G4double glue_strip_halfZ       = strip_halfZ;
    
    G4double insulator_block_halfX  = 12.5*um;
    G4double insulator_block_halfY  = 50000.*um;
    G4double insulator_block_halfZ  = 50000.*um;
    
    G4double mesh_inner_radius      = 0.0*um;
    G4double mesh_outer_radius      = 12.*um;
    G4double mesh_half_width        = active_area_halfY;
    G4double mesh_starting_angle    = 0.*deg;
    G4double mesh_spanning_angle    = 360*deg;
    G4double mesh_pitch             = 78.0*um;
    

    G4double amplification_gap      = 128.*um;
    G4double drift_gap              = 5000.*um;

    G4double pillar_inner_radius    = 0.0*deg;
    G4double pillar_outer_radius    = 200.*um;
    G4double pillar_half_width      = (amplification_gap-2*strip_halfX-mesh_outer_radius)/2.;
    G4double pillar_starting_angle  = 0.*deg;
    G4double pillar_spanning_angle  = 360*deg;
    G4double pillar_pitch           = 2500.0*um;

    G4double mylar_half_thickness   = 60*um;

    G4double pcb_total_thickness = 2.*pcb_halfX;//2000.*um;
    G4double frame_total_thickness = 2.*(frame_halfX+topBrass_halfX+topPCB_halfX+mylar_half_thickness);
    G4double detector_half_width = pcb_halfY; //86800.*um;//100000.*um;
    G4double detector_half_height = pcb_halfX+frame_halfX+mylar_half_thickness+topPCB_halfX+topBrass_halfX;
        
    ///
    /// Primary Generator configuration
    ///    
    G4String beamParticleName = "neutron";
    G4double beamEnergy = 5.1*MeV;

    /** @brief     { define the distance of the particle gun
        wrt to the center of the world
        assuming that the gun is at the center of the detector
        in a vertical distance of particleGun_Xdistance:} */
    G4double particleGun_Xdistance = 183850*um; /// --26cm when inclined: 2x^2=26^2 -> x=18,385cm
    G4double particleGun_Ydistance = 0.0*um;
    G4double particleGun_Z_distance = 0.0*um;

    };

    #endif
