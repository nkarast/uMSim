/**
 * Header for Hit definition for the SD
 *
 *  @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 *  @version   v2.0
 */


#ifndef UMHit_hh 
#define UMHit_hh 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"


class UMHit : public G4VHit
{
	public:
		/// Constructor and set the deposited energy to 0
		UMHit() : UMEDep(0.0)
        {
		// pass
		}
	/// Destructor - None
	~UMHit()
	{
		// pass
	}
      
	UMHit(const UMHit& right);
	const UMHit & operator=(const UMHit& right);
	G4bool operator==(const UMHit& right) const; 

	inline void * operator new(size_t);
	inline void operator delete(void * hit);

	virtual void Draw();
	virtual void Print();
	
		
	/// Setter for Energy Deposit	
	inline void SetUMEDep(const G4double e)
	{	UMEDep = e;	}
	
	inline G4double GetUMEDep() const
	{	return UMEDep;	}
	
	/// Setter for Position
	inline void SetPosition(const G4ThreeVector xyz)
	{	Position = xyz;	}
	
	/// Getter for position
	inline G4ThreeVector GetPos() const
	{	return Position;	}
	
	/// Setter for Particle Name
	inline void SetUMParticleName(const G4String pn)
	{	UMParticleName = pn;	}
	
	/// Setter for Process Name
	inline void SetUMProcessName(const G4String pn)
	{	UMProcessName = pn;	}
	
	/// Getter for Process Name
	inline G4String GetUMParticleName() const
	{	return UMParticleName;	}
	
	/// Getter for process name
	inline G4String GetUMProcessName() const
	{	return UMProcessName;	}
	
	/// Setter for mother particle
	inline void SetMotherID(const G4int MID)
	{	MotherID=MID;		}
	
	/// Getter for mother particle
	inline G4int GetMotherID()const
	{	return MotherID;	}
    
    /// Getter for pdg ID
    inline G4int GetUMPdgId()const
    {	return UMPdgId;	}
    
    /// Setter for pdf ID
    inline void SetUMPdgId(const G4int pdgid)
    {	UMPdgId = pdgid;	}
	
	/// Adding deposited energy to total deposited energy
	void  AddEDep(const double e){ 	
		EDep += e; 
	}

	/// Getter for deposited energy
	G4double GetEDep()  const
	{ return EDep;}     

	private:
		G4double UMEDep;
		G4double EDep;
		G4int MotherID;
		G4String UMParticleName;
		G4String UMProcessName;
		G4ThreeVector Position;
    	G4int UMPdgId;
};

/// Define the "hit collection" using the template class G4THitsCollection:
typedef G4THitsCollection<UMHit> UMHitsCollection;

/// new and delete overloaded operators:
extern G4Allocator<UMHit> UMHitAllocator;

inline void * UMHit::operator new(size_t){
	void * aHit;
	aHit = (void*)UMHitAllocator.MallocSingle();
	return aHit;
}

inline void UMHit::operator delete(void * hit){
	UMHitAllocator.FreeSingle((UMHit*) hit);
}


#endif	