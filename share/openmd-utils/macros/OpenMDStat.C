void OpenMDStat(const char *filename, Bool_t isPDF=kFALSE) {
//    gROOT->SetBatch();

    TTree *t = new TTree("md","OpenMD stat");
    t->ReadFile(filename, "t:E:Ep:Ek:T:p:V:CQ");

    TCanvas *c = new TCanvas();
    TFile f(TString::Format("%s.root",filename).Data(), "RECREATE");
    TGraph *graph;
    
    t->Draw("E:t");
    if (isPDF) c->Print("E_t.pdf");
    graph = (TGraph*)gPad->GetPrimitive("Graph");
    graph->SetTitle("E vs. time");
    graph->Write("E_t");

    t->Draw("Ep:t");
    if (isPDF) c->Print("Ep_t.pdf");
    graph = (TGraph*)gPad->GetPrimitive("Graph");
    graph->SetTitle("Ep vs. time");
    graph->Write("Ep_t");
    
    t->Draw("Ek:t");
    if (isPDF) c->Print("Ek_t.pdf");
    graph = (TGraph*)gPad->GetPrimitive("Graph");
    graph->SetTitle("Ek vs. time");
    graph->Write("Ek_t");

    t->Draw("T:t"); 
    if (isPDF) c->Print("T_t.pdf");
    graph = (TGraph*)gPad->GetPrimitive("Graph");
    graph->SetTitle("T vs. time");
    graph->Write("T_t");
    
    t->Draw("p:t");
    if (isPDF) c->Print("p_t.pdf");
    graph = (TGraph*)gPad->GetPrimitive("Graph");
    graph->SetTitle("p vs. time");
    graph->Write("p_t");
    
    t->Draw("V:t");
    if (isPDF) c->Print("V_t.pdf");
    graph = (TGraph*)gPad->GetPrimitive("Graph");
    graph->SetTitle("V vs. time");
    graph->Write("V_t");
    
    t->Draw("CQ:t");
    if (isPDF) c->Print("CQ_t.pdf");
    graph = (TGraph*)gPad->GetPrimitive("Graph");
    graph->SetTitle("CQ vs. time");
    graph->Write("CQ_t");


    delete c;
//    gROOT->SetBatch(kFALSE);

   f.Close();
}
