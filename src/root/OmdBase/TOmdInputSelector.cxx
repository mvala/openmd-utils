#include <TError.h>
#include <TFile.h>
#include <TTree.h>
#include <TOmdFrame.h>
#include <TOmdFrameObj.h>

#include "TOmdInputSelector.h"

ClassImp(TOmdInputSelector)

TOmdInputSelector::TOmdInputSelector(TTree * /*tree*/) :
    TSelector(), fChain(0), fFrame(0), fHist(0) {

}

TOmdInputSelector::~TOmdInputSelector() {
  delete fFrame;
}

void TOmdInputSelector::Init(TTree *tree) {
  if (!tree)
    return;
  fChain = tree;
  fFrame = new TOmdFrame();
  fChain->SetBranchAddress("omdFrame", &fFrame);
}

Bool_t TOmdInputSelector::Notify() {
  ::Info("", fChain->GetCurrentFile()->GetName());
  return kTRUE;
}

void TOmdInputSelector::Begin(TTree* /*tree*/) {
}

void TOmdInputSelector::SlaveBegin(TTree * /*tree*/) {
  TString option = GetOption();

  fHist = new TH1D("h", "My Hist", 1000, 0.0, 1000);
  fOutput->Add(fHist);
}

Bool_t TOmdInputSelector::Process(Long64_t entry) {

  GetEntry(entry);

  fHist->Fill(fFrame->GetId());
  Printf("ID=%d", fFrame->GetId());
  TOmdFrameObj *obj = 0;

  for (Int_t i = 0; i < fFrame->GetNObjects(); i++) {
    obj = (TOmdFrameObj *) fFrame->GetObjects()->UncheckedAt(i);
    Printf("id=%d x=%f y=%f z=%f", i, obj->GetPosition(0), obj->GetPosition(1), obj->GetPosition(2));
  }

  return kTRUE;
}

void TOmdInputSelector::SlaveTerminate() {
}

void TOmdInputSelector::Terminate() {
  fHist = dynamic_cast<TH1D*>(fOutput->FindObject("h"));
  if (fHist)
    fHist->DrawCopy();
}

Int_t TOmdInputSelector::Version() const {
  return 2;
}

Int_t TOmdInputSelector::GetEntry(Long64_t entry, Int_t getall) {
  return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
}
