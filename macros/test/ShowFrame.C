#ifndef __CINT__
#include <TSystem.h>
#include <TGeoManager.h>
#include <TStyle.h>
#endif

void ShowFrame(Double_t arrowScale  = 1., Double_t worldScale  = 10., TString outputFileName = "/tmp/omd_event.root") {

  gSystem->Load("libGeom");

  TGeoManager *geom = new TGeoManager("frame", "Frame");

  //--- define some materials
  TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum", 0,0,0);
  //--- define some media
  TGeoMedium *Vacuum = new TGeoMedium("Vacuum",1, matVacuum);

  //--- make the top container volume
  Double_t worldx = 1.*worldScale;
  Double_t worldy = 1.*worldScale;
  Double_t worldz = 1.*worldScale;
  TGeoVolume *top = geom->MakeBox("TOP", Vacuum, worldx, worldy, worldz);
  top->SetTransparency(10);
  top->SetLineColor(kBlack);
  geom->SetTopVolume(top);

  TGeoVolume *arrow = BuildArrow(geom, Vacuum, arrowScale);


  // Build Frames
  LoopFrames(top,arrow);

  //--- close the geometry
  geom->CloseGeometry();

  // saving geometry to file
  geom->Export(outputFileName.Data());

  Bool_t isTopVisible = kFALSE;
  isTopVisible = kTRUE;

  // top is invisible by default
  if (isTopVisible) geom->SetTopVisible();

  top->Draw();
//  top->Draw("ogl");
}

void LoopFrames(TGeoVolume *top, TGeoVolume *arrow) {
  Long64_t id = 0;
  BuildFrame(id, top, arrow);
}

void BuildFrame(Long64_t id, TGeoVolume *top, TGeoVolume *arrow) {

  // LOOP
  TGeoRotation *r1 = new TGeoRotation("r1",0,0,0);
  TGeoCombiTrans *transRotArrow1 = new TGeoCombiTrans(0., 0., 0., r1);
  top->AddNode(arrow, 1, transRotArrow1);

  TGeoRotation *r2 = new TGeoRotation("r2",90,90,0);
  TGeoCombiTrans *transRotArrow2 = new TGeoCombiTrans(1., 2., 3., r2);
  top->AddNode(arrow, 2, transRotArrow2);
  // END LOOP
}

TGeoVolume * BuildArrow(TGeoManager *geom, TGeoMedium *Vacuum , Double_t scale = 1.) {

  // Arrow
  TGeoVolume *arrow = geom->MakeBox("arrow", Vacuum, 0.25*scale, 0.25*scale, 0.50*scale);
  arrow->SetTransparency(50);
  arrow->SetLineColor(kRed);
  arrow->SetVisibility(kTRUE);

  TGeoVolume *arrowUp = geom->MakeCone("aUp", Vacuum, 0.20*scale, 0.*scale, 0.25*scale, 0.*scale, 0.*scale);
  arrowUp->SetLineColor(kBlue);
  arrow->AddNode(arrowUp, 1, new TGeoTranslation("aUpTrans", 0.*scale, 0.*scale, 0.30*scale));

  TGeoVolume *arrowDown = geom->MakeTube("aDown", Vacuum, 0.*scale, 0.10*scale, 0.30*scale);
  arrowDown->SetLineColor(kBlue);
  arrow->AddNode(arrowDown, 2, new TGeoTranslation("aDownTrans", 0.*scale, 0.*scale, -0.20*scale));
  return arrow;
}
