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

  void SetInitialPositionOnly(Bool_t initPosOnly);

private:

  TTree           *fChain;                  //!Pointer to the analyzed TTree or TChain
  TOmdFrame       *fFrame;                  //!Current frame

  TGeoManager     *fGeoManager;             // Geo Manager
  TGeoVolume      *fArrow;                  // Arrow object
  TGeoMedium      *fVacuum;                 // Material for arrow

  TList           *fListOfCombiTrans;       // List of rotations

  TCanvas         *fCanvas;                 //!Canvas to draw
  TString          fDrawOpt;                // Draw options

  TString          fOutputDir;              // Output directory
  Bool_t           fSaveGeometry;           // Flag if geometry should be saved
  Bool_t           fInitialPositionOnly;    // Flag if only initial position should be set

ClassDef(TOmdInputSelector, 1)

};

#endif
