//================================================================
// Archivo: include/B1SensitiveDetector.hh
//================================================================
#ifndef B1SENSITIVEDETECTOR_HH
#define B1SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4String.hh"
#include <fstream>

class G4Step;
class G4TouchableHistory;
class G4Run;

/// Detector Sensible para el ejemplo B1.
/// Escribe cada "hit" (depósito de energía) a un archivo CSV.
class B1SensitiveDetector : public G4VSensitiveDetector
{
public:
    B1SensitiveDetector(const G4String& name, const G4String& filename);
    virtual ~B1SensitiveDetector();

    virtual void Initialize(G4HCofThisEvent*);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    virtual void EndOfEvent(G4HCofThisEvent*);

private:
    std::ofstream outFile;
    G4String fOutputFilename;
    G4bool fIsHeaderWritten;
};

#endif