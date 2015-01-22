#include <TError.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TGeoMatrix.h>

#include <TOmdFrame.h>
#include <TOmdFrameObj.h>

#include "TOmdInputSelector.h"

ClassImp(TOmdInputSelector)

//_________________________________________________________________________________________________
TOmdInputSelector::TOmdInputSelector(TTree * /*tree*/) :
    TSelector(), fChain(0), fFrame(0), fGeoManager(0), fArrow(0), fVacuum(0), fListOfCombiTrans(0), fCanvas(0), fDrawOpt(
        ""), fOutputDir("/tmp"), fSaveGeometry(kFALSE), fInitialPositionOnly(kTRUE) {
  //
  // Standard constructor
  //

}

//_________________________________________________________________________________________________
TOmdInputSelector::~TOmdInputSelector() {
  //
  // Destructor
  //

  delete fFrame;
  fListOfCombiTrans->Delete();
  SafeDelete(fListOfCombiTrans);
}

//_________________________________________________________________________________________________
void TOmdInputSelector::Init(TTree *tree) {
  //
  // Init of OpenMD Tree
  //

  if (!tree)
    return;
  fChain = tree;
  fFrame = new TOmdFrame();
  fChain->SetBranchAddress("omdFrame", &fFrame);
}

//_________________________________________________________________________________________________
Bool_t TOmdInputSelector::Notify() {
  if (fChain)
    ::Info("", fChain->GetCurrentFile()->GetName());
  return kTRUE;
}

//_________________________________________________________________________________________________
void TOmdInputSelector::Begin(TTree* /*tree*/) {
}

//_________________________________________________________________________________________________
void TOmdInputSelector::SlaveBegin(TTree * /*tree*/) {
  TString option = GetOption();

  CreateGeometry();

}

//_________________________________________________________________________________________________
Bool_t TOmdInputSelector::Process(Long64_t entry) {

  GetEntry(entry);
  Printf("ID=%d", fFrame->GetId());

  ProcessGeometry();

  return kTRUE;
}

//_________________________________________________________________________________________________
void TOmdInputSelector::SlaveTerminate() {

  delete fCanvas;
  fCanvas = 0;
}

//_________________________________________________________________________________________________
void TOmdInputSelector::Terminate() {
}

//_________________________________________________________________________________________________
Int_t TOmdInputSelector::Version() const {
  return 2;
}

//_________________________________________________________________________________________________
Int_t TOmdInputSelector::GetEntry(Long64_t entry, Int_t getall) {
  return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
}

//_________________________________________________________________________________________________
void TOmdInputSelector::CreateGeometry() {

  Double_t worldScale = 100.;

  fGeoManager = new TGeoManager("frame", "Frame");

  // Define some materials
  TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum", 0, 0, 0);
  // Define some media
  fVacuum = new TGeoMedium("Vacuum", 1, matVacuum);

  // Make the top container volume
  Double_t worldx = 1. * worldScale;
  Double_t worldy = 1. * worldScale;
  Double_t worldz = 1. * worldScale;
  TGeoVolume *top = fGeoManager->MakeBox("TOP", fVacuum, worldx, worldy, worldz);
  top->SetTransparency(10);
  top->SetLineColor(kBlack);
  fGeoManager->SetTopVolume(top);

}

//_________________________________________________________________________________________________
void TOmdInputSelector::ProcessGeometry() {

  Double_t scale = 1.;

  TGeoVolume *top = fGeoManager->GetTopVolume();

  Printf("Processing Arrow (nodes=%d)...", top->GetNdaughters());

  if (!fArrow) {

    Printf("Initializing ARROW !!!");
    fArrow = fGeoManager->MakeBox("arrow", fVacuum, 0.25 * scale, 0.25 * scale, 0.50 * scale);
    fArrow->SetTransparency(50);
    fArrow->SetLineColor(kRed);
    fArrow->SetVisibility(kTRUE);

    TGeoVolume *arrowUp = fGeoManager->MakeCone("aUp", fVacuum, 0.20 * scale, 0. * scale, 0.25 * scale, 0. * scale,
        0. * scale);
    arrowUp->SetLineColor(kBlue);
    fArrow->AddNode(arrowUp, 1, new TGeoTranslation("aUpTrans", 0. * scale, 0. * scale, 0.30 * scale));

    TGeoVolume *arrowDown = fGeoManager->MakeTube("aDown", fVacuum, 0. * scale, 0.10 * scale, 0.30 * scale);
    arrowDown->SetLineColor(kBlue);
    fArrow->AddNode(arrowDown, 2, new TGeoTranslation("aDownTrans", 0. * scale, 0. * scale, -0.20 * scale));

  }

  if (!fListOfCombiTrans)
    fListOfCombiTrans = new TList();

  TGeoRotation *r;
  TGeoCombiTrans *combiTrans;
  TOmdFrameObj *obj = 0;
  Double_t phi, theta, psi;
  for (Int_t i = 0; i < fFrame->GetNObjects(); i++) {
    obj = (TOmdFrameObj *) fFrame->GetObjects()->UncheckedAt(i);

    if (fListOfCombiTrans->GetSize() < fFrame->GetNObjects()) {
      r = new TGeoRotation(TString::Format("r%d", i).Data(), 0, 0, 0);
      obj->ApplyRotationMatrix(r);
      combiTrans = new TGeoCombiTrans(obj->GetPosition(0), obj->GetPosition(1), obj->GetPosition(2), r);
      r->GetAngles(phi, theta, psi);
      fListOfCombiTrans->Add(combiTrans);
    } else {
      combiTrans = (TGeoCombiTrans*) fListOfCombiTrans->At(i);
      if (!fInitialPositionOnly)
        combiTrans->SetTranslation(obj->GetPosition(0), obj->GetPosition(1), obj->GetPosition(2));
      r = combiTrans->GetRotation();
      obj->ApplyRotationMatrix(r);
      r->GetAngles(phi, theta, psi);
    }

    top->AddNode(fArrow, 1, combiTrans);
  }

  if (!fCanvas)
    fCanvas = new TCanvas("frames", "Frames");
  top->Draw(fDrawOpt.Data());
  fCanvas->SaveAs(TString::Format("%s/frame%05d.png", fOutputDir.Data(), fFrame->GetId()).Data());

  fGeoManager->Export(TString::Format("%s/geom%05d.root", fOutputDir.Data(), fFrame->GetId()).Data());

}

//_________________________________________________________________________________________________
void TOmdInputSelector::SetOutputDir(TString outputDir) {
  if (!outputDir.IsNull())
    fOutputDir = outputDir;
}

//_________________________________________________________________________________________________
void TOmdInputSelector::SetDrawOption(TString opt) {
  fDrawOpt = opt;
}

//_________________________________________________________________________________________________
void TOmdInputSelector::SetInitialPositionOnly(Bool_t initPosOnly) {
  fInitialPositionOnly = initPosOnly;
}
