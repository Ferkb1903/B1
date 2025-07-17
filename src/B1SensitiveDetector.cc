//================================================================
// Archivo: src/B1SensitiveDetector.cc
//================================================================
#include "B1SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

B1SensitiveDetector::B1SensitiveDetector(const G4String& name, const G4String& filename)
    : G4VSensitiveDetector(name), 
      fOutputFilename(filename),
      fIsHeaderWritten(false)
{}

B1SensitiveDetector::~B1SensitiveDetector() {}

void B1SensitiveDetector::Initialize(G4HCofThisEvent*)
{
    if (!fIsHeaderWritten) {
        std::ofstream headerFile(fOutputFilename, std::ios_base::trunc);
        if (headerFile.is_open()) {
            headerFile << "EventID,Edep_keV\n";
            headerFile.close();
            fIsHeaderWritten = true;
        }
    }
    
    outFile.open(fOutputFilename, std::ios_base::app);
    if (!outFile.is_open()) {
        G4Exception("B1SensitiveDetector", "FileOpenError", FatalException, "No se pudo abrir el archivo CSV de hits.");
    }
}

G4bool B1SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep == 0.) return false;

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    outFile << eventID << "," << edep / keV << "\n";

    return true;
}

void B1SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    if (outFile.is_open()) {
        outFile.close();
    }
}