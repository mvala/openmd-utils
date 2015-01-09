#include <TError.h>
#include <TTree.h>
#include <TH1.h>
#include <TOmdFrame.h>

#include "TOmdSelectorExample.h"

ClassImp(TOmdSelectorExample)

TOmdSelectorExample::TOmdSelectorExample(TTree * /*tree*/) :
        TSelector(), fChain(0), fFrame(0), fHist(0){

}

TOmdSelectorExample::~TOmdSelectorExample() {
  delete fFrame;
}

void TOmdSelectorExample::Init(TTree *tree) {
    if (!tree) return;
    fChain = tree;
    fFrame = new TOmdFrame();
    fChain->SetBranchAddress("omdFrame", &fFrame);
}

Bool_t TOmdSelectorExample::Notify() {
    ::Info("",fChain->GetCurrentFile()->GetName());
    return kTRUE;
}

void TOmdSelectorExample::Begin(TTree* /*tree*/) {
}

void TOmdSelectorExample::SlaveBegin(TTree * /*tree*/) {
    TString option = GetOption();

    fHist = new TH1D("h", "My Hist", 1000, 0.0, 1000);
    fOutput->Add(fHist);
}

Bool_t TOmdSelectorExample::Process(Long64_t entry) {

    GetEntry(entry);

    fHist->Fill(fFrame->GetId());
    Printf("ID=%ld", fFrame->GetId());
    return kTRUE;
}

void TOmdSelectorExample::SlaveTerminate() {
}

void TOmdSelectorExample::Terminate() {
    fHist = dynamic_cast<TH1D*>(fOutput->FindObject("h"));
    if (fHist) fHist->DrawCopy();
}

Int_t TOmdSelectorExample::Version() const {
    return 2;
}

Int_t TOmdSelectorExample::GetEntry(Long64_t entry, Int_t getall) {
    return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
}
