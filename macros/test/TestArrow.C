#ifndef __CINT__
#include <TSystem.h>
#include <TGeoManager.h>
#include <TStyle.h>
#endif

void TestArrow(TString filename = "arrow.root") {

//  gStyle->SetCanvasPreferGL(kTRUE);

  gSystem->Load("libGeom");
  TGeoManager *geom = new TGeoManager("simple1", "Simple geometry");

  //--- define some materials
  TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum", 0,0,0);
  //--- define some media
  TGeoMedium *Vacuum = new TGeoMedium("Vacuum",1, matVacuum);

  //--- make the top container volume
  Double_t worldx = 110.;
  Double_t worldy = 50.;
  Double_t worldz = 5.;
  TGeoVolume *top = geom->MakeBox("TOP", Vacuum, 100., 100., 100.);
  geom->SetTopVolume(top);

  // Arrow
  TGeoVolume *arrow = geom->MakeBox("arrow", Vacuum, 25., 25., 50.);
  arrow->SetTransparency(50);
  arrow->SetLineColor(kRed);
  arrow->SetVisibility(kTRUE);


  TGeoVolume *arrowUp = geom->MakeCone("aUp", Vacuum, 20., 0., 25., 0., 0.);
  arrowUp->SetLineColor(kBlue);
  arrow->AddNode(arrowUp, 1, new TGeoTranslation("aUpTrans", 0., 0., 30.));

  TGeoVolume *arrowDown = geom->MakeTube("aDown", Vacuum, 0., 10., 30.);
  arrowDown->SetLineColor(kBlue);
  arrow->AddNode(arrowDown, 2, new TGeoTranslation("aDownTrans", 0., 0., -20.));

  TGeoRotation *rotArrow = new TGeoRotation("rotArrow",0,0,0);
  TGeoCombiTrans *transRotArrow = new TGeoCombiTrans(0, 0, 0, rotArrow);
  top->AddNode(arrow, 1, transRotArrow);

  TGeoRotation *rotArrow = new TGeoRotation("rotArrow",30,20,0);
  TGeoCombiTrans *transRotArrow = new TGeoCombiTrans(50, 30, 20., rotArrow);
  top->AddNode(arrow, 1, transRotArrow);

  //--- close the geometry
  geom->CloseGeometry();

  geom->Export(filename.Data());

//  TGeoManager::Import(filename.Data());

  //
  geom->SetTopVisible();

  geom->SetVisLevel(4);
//  arrow->Draw("ogl");
  top->Draw("ogl");

}


