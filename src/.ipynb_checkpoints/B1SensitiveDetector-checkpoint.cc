// src/B1SensitiveDetector.cc

#include "B1SensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"

B1SensitiveDetector::B1SensitiveDetector(
                            const G4String& name,
                            const G4String& hitsCollectionName,
                            const G4String& fileName)
 : G4VSensitiveDetector(name),
   fFileName(fileName)
{
  collectionName.insert(hitsCollectionName);
  fOutputFile.open(fFileName, std::ios::out);
  fOutputFile << "EventID,TrackID,Particle,E_dep[MeV],X[mm],Y[mm],Z[mm],Time[ns],ProcessName" << std::endl;
}

// ---> AÑADE ESTE DESTRUCTOR VACÍO <---
B1SensitiveDetector::~B1SensitiveDetector()
{
}

void B1SensitiveDetector::Initialize(G4HCofThisEvent* /*hce*/)
{
}

G4bool B1SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if (edep == 0.) return false;

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4Track* track = aStep->GetTrack();
  const G4VProcess* process = preStepPoint->GetProcessDefinedStep();
  G4String processName = process ? process->GetProcessName() : "N/A";

  fOutputFile << G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID() << ","
              << track->GetTrackID() << ","
              << track->GetDefinition()->GetParticleName() << ","
              << edep / CLHEP::MeV << ","
              << preStepPoint->GetPosition().x() / CLHEP::mm << ","
              << preStepPoint->GetPosition().y() / CLHEP::mm << ","
              << preStepPoint->GetPosition().z() / CLHEP::mm << ","
              << preStepPoint->GetGlobalTime() / CLHEP::ns << ","
              << processName << std::endl;

  return true;
}

void B1SensitiveDetector::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
}