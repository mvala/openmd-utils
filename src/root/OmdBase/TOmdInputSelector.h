#ifndef TOmdInputSelector_H
#define TOmdInputSelector_H

#include <TTree.h>
#include <TSelector.h>
#include <TH1D.h>
#include <TCanvas.h>

#include <TGeoManager.h>
#include <TGeoVolume.h>
#include <TGeoMaterial.h>



class TTree;
class TOmdFrame;

//class TGeoManager;
//class TGeoVolume;
//class TGeoMedium;

class TOmdInputSelector: public TSelector {

public:

  TOmdInputSelector(TTree *tree = 0);
  virtual ~TOmdInputSelector();

  virtual Int_t Version() const;
  virtual void Begin(TTree */*tree*/);
  virtual void SlaveBegin(TTree *tree);
  virtual void Init(TTree *tree);
  virtual Bool_t Notify();
  virtual Bool_t Process(Long64_t entry);
  virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0);
  virtual void SlaveTerminate();
  virtual void Terminate();

  void CreateGeometry();
  void ProcessGeometry();

  void SetDrawOption(TString opt);
  void SetOutputDir(TString outputDir);

private:

  TTree *fChain;                  //!pointer to the analyzed TTree or TChain
  TOmdFrame *fFrame;

  TGeoManager *fGeoManager;
  TGeoVolume *fArrow;
  TGeoMedium *fVacuum;

  TList *fListOfCombiTrans;

  TCanvas *fCanvas;
  TString fDrawOpt;

  TH1D *fHist;

  TString fOutputDir;

ClassDef(TOmdInputSelector, 1)

};

#endif
