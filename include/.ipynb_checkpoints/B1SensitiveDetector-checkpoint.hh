// include/B1SensitiveDetector.hh

#ifndef B1SensitiveDetector_h
#define B1SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include <fstream>

class B1SensitiveDetector : public G4VSensitiveDetector
{
public:
  B1SensitiveDetector(const G4String& name, const G4String& hitsCollectionName, const G4String& fileName);
  virtual ~B1SensitiveDetector(); // <-- DESTRUCTOR DEBE ESTAR DECLARADO

  virtual void Initialize(G4HCofThisEvent* hce);
  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void EndOfEvent(G4HCofThisEvent* hce);

private:
  G4String fFileName;
  std::ofstream fOutputFile;
};

#endif