#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "Math/MinimizerOptions.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "setTDRStyle_teliko.C"

 void Plot_DeltaEta(){

 gROOT->LoadMacro("setTDRStyle_teliko.C");
 setTDRStyle_teliko();
                                     //0.14
 TPaveText *paveCMS = new TPaveText(0.16,0.96,0.96,0.99,"NDC");
// TGaxis::SetMaxDigits(3);
 paveCMS->AddText("CMS Preliminary    #sqrt{s} = 13 TeV       L = 137 fb^{-1}");
 paveCMS->SetFillColor(0);
 paveCMS->SetBorderSize(0);
 paveCMS->SetTextSize(0.04);

 TPaveText *paveCMS2 = new TPaveText(0.25,0.75,0.45,0.9,"NDC");
 paveCMS2->AddText("|#eta| < 2.5" );
 paveCMS2->AddText("m_{jj} > 2.4 TeV");
// paveCMS2->SetFillColor(0);
// paveCMS2->SetBorderSize(0);
// paveCMS2->SetTextSize(0.04);
        paveCMS2->SetFillColor(0);
        paveCMS2->SetBorderSize(0);
        paveCMS2->SetFillStyle(0);
        paveCMS2->SetTextFont(42);
        paveCMS2->SetTextSize(0.04);
//        paveCMS2->SetTextAlign(11);


 TPaveText *paveCMS10 = new TPaveText(0.65,0.75,0.85,0.9,"NDC");
 paveCMS10->AddText("|#eta|<2.5" );
 paveCMS10->AddText("m_{jj} > 2.4 TeV");
        paveCMS10->SetFillColor(0);
        paveCMS10->SetBorderSize(0);
        paveCMS10->SetFillStyle(0);
        paveCMS10->SetTextFont(42);
        paveCMS10->SetTextSize(0.045);
        paveCMS10->SetTextAlign(11);
 
// paveCMS10->SetFillColor(0);
// paveCMS10->SetBorderSize(0);
// paveCMS10->SetTextSize(0.04);

 TPaveText *paveCMS3 = new TPaveText(0.25,0.65,0.38,0.68,"NDC");
 paveCMS3->AddText("SR");
 paveCMS3->SetTextColor(2);
 paveCMS3->SetFillColor(0);
 paveCMS3->SetBorderSize(0);
 paveCMS3->SetTextSize(0.033);

 TPaveText *paveCMS4 = new TPaveText(0.72,0.65,0.85,0.68,"NDC");
 paveCMS4->AddText("CR_{high}");
 paveCMS4->SetTextColor(2);
 paveCMS4->SetFillColor(0);
 paveCMS4->SetBorderSize(0);
 paveCMS4->SetTextSize(0.033);

 TPaveText *paveCMS8 = new TPaveText(0.46,0.65,0.65,0.68,"NDC");  
 paveCMS8->AddText("CR_{middle}");
 paveCMS8->SetFillColor(0);
 paveCMS8->SetTextColor(2);
 paveCMS8->SetBorderSize(0);
 paveCMS8->SetTextSize(0.033); // 0.25

 TPaveText *paveCMS7 = new TPaveText(0.5,0.65,0.7,0.78,"NDC");
 paveCMS7->AddText("|#eta|<2.5" );
 paveCMS7->AddText("1.3<|#Delta #eta|<2.6");
 paveCMS7->AddText("m_{jj} > 2.4 TeV");
        paveCMS7->SetFillColor(0);
        paveCMS7->SetBorderSize(0);
        paveCMS7->SetFillStyle(0);
        paveCMS7->SetTextFont(42);
        paveCMS7->SetTextSize(0.045);
        paveCMS7->SetTextAlign(11);
// paveCMS7->SetFillColor(0);
// paveCMS7->SetBorderSize(0);
// paveCMS7->SetTextSize(0.04);

 TPaveText *paveCMS5 = new TPaveText(0.39,0.80,0.51,0.93,"NDC");
 paveCMS5->AddText("|#eta|<2.5" );
 paveCMS5->AddText("1.3<|#Delta #eta|<2.6");
 paveCMS5->AddText("m_{jj} > 2.4 TeV");
        paveCMS5->SetFillColor(0);
        paveCMS5->SetBorderSize(0);
        paveCMS5->SetFillStyle(0);
        paveCMS5->SetTextFont(42);
        paveCMS5->SetTextSize(0.045);
        paveCMS5->SetTextAlign(11);
// paveCMS5->SetFillColor(0);
// paveCMS5->SetBorderSize(0);
// paveCMS5->SetTextSize(0.04);

 TPaveText *paveCMS6 = new TPaveText(0.39,0.80,0.51,0.93,"NDC");
 paveCMS6->AddText("|#eta|<2.5" );
 paveCMS6->AddText("1.3<|#Delta #eta|<2.6");
 paveCMS6->AddText("M_{jj} > 4 TeV");
 paveCMS6->SetFillColor(0);
 paveCMS6->SetBorderSize(0);
 paveCMS6->SetTextSize(0.04);

  float lumi;
  lumi = 137500.;

  TFile *fin  = new TFile("../inputs/histos_FULL_deltaEta0p6.root","READ");
  TFile *finm = new TFile("../inputs/histos_MC2017_41p85FB_mjj2438_cemf_lt0p8_wo_deltaETAcut.root","READ");
  TFile *find = new TFile("../inputs/deltaETAjj_0to2p6_mjj2438_RSGtoQQ_M3000.root","READ");
  TFile *finx = new TFile("../inputs/deltaETAjj_0to2p6_mjj2438_QstartoJJ_M3000.root","READ");
  
  TH1D *h_deltaETAjj         = (TH1D*)(finm->Get("h_deltaETAjj"));
  TH1D *h_deltaETAjj_data    = (TH1D*)(fin->Get("h_deltaETAjj_data"));
  TH1D *h_deltaETAjj_sima1   = (TH1D*)(find->Get("h_deltaETAjj_data"));
  TH1D *h_deltaETAjj_sima2   = (TH1D*)(finx->Get("h_deltaETAjj_data"));
 
  char name[100]; 
  const int nMassBins = 103;
 
 double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
     4686,  4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};
 
     TLegend *leg2 =new TLegend(.52, .77, .98, .92); // .62, .77, .98, .92);
     leg2->SetFillColor(0);
     leg2->SetFillStyle(0);
     leg2->SetBorderSize(0);
     leg2->SetTextSize(0.033);
     leg2->AddEntry(h_deltaETAjj_data, "Data", "p");
     leg2->AddEntry(h_deltaETAjj, "QCD PYTHIA", "L");
     leg2->AddEntry(h_deltaETAjj_sima1,"RS graviton #rightarrow q#bar{q}","L");

     h_deltaETAjj_data->Sumw2();
//     h_deltaETAjj_data->Scale(1./1000.);
//     h_deltaETAjj_sima1->Scale(1./1000.);
//     h_deltaETAjj->Scale(1./1000.);
    
     h_deltaETAjj_data->Scale(1.);
     h_deltaETAjj_sima1->Scale(1.);
     h_deltaETAjj->Scale(1.);

    TCanvas *pad21r = new TCanvas("pad21r","example",600,600);
    pad21r->cd();
    //pad21r->cd()->SetLogx(1);
    h_deltaETAjj_data->GetXaxis()->SetTitle("Dijet |#Delta#eta|");
    h_deltaETAjj_data->GetYaxis()->SetTitle("Events/bin");
    h_deltaETAjj_data->GetYaxis()->SetRangeUser(0.,120000.);
     h_deltaETAjj_data->GetYaxis()->SetTitleOffset(1.6); //  
     h_deltaETAjj_data->GetXaxis()->SetTitleOffset(1.1);
 //    TGaxis::SetExponentOffset(-0.087, -0.04, "y");  // edw!!!
     h_deltaETAjj_data->SetLineWidth(2);
     h_deltaETAjj_data->SetLineWidth(2);
     h_deltaETAjj->SetLineColor(2);
     h_deltaETAjj_data->SetLineColor(1);
     h_deltaETAjj_sima1->SetLineColor(4);
     h_deltaETAjj->Scale(h_deltaETAjj_data->Integral()/h_deltaETAjj->Integral());
     h_deltaETAjj_sima1->Scale(h_deltaETAjj_data->Integral()/h_deltaETAjj_sima1->Integral());
     h_deltaETAjj->GetXaxis()->SetLabelSize(0.05);
     h_deltaETAjj->GetYaxis()->SetLabelSize(0.05); 

     h_deltaETAjj_data->GetXaxis()->SetLabelSize(0.05);
     h_deltaETAjj_data->GetYaxis()->SetLabelSize(0.047);

         h_deltaETAjj->GetXaxis()->SetLabelSize(0.05);
         h_deltaETAjj->GetYaxis()->SetLabelSize(0.05);
         h_deltaETAjj->GetXaxis()->SetTitleSize(0.05);
         h_deltaETAjj->GetYaxis()->SetTitleSize(0.05);
         h_deltaETAjj->GetXaxis()->SetTitleFont(42);
         h_deltaETAjj->GetYaxis()->SetTitleFont(42);
         h_deltaETAjj->GetXaxis()->SetTitleOffset(1.2);
         h_deltaETAjj->GetYaxis()->SetTitleOffset(1.3); // 1.3
     
     h_deltaETAjj_data->Draw("e");
     h_deltaETAjj->Draw("same HIST");
     h_deltaETAjj_sima1->Draw("same HIST");
     //h_deltaETAjj_sima2->Draw("same HIST");
    TLatex *l = new TLatex();
    l->SetTextAlign(11);
    l->SetTextSize(0.045);
    l->SetNDC();
    l->SetTextFont(62);
      l->DrawLatex(0.2,0.89,"CMS");
      l->SetTextFont(52);
      l->SetTextFont(42);
      l->DrawLatex(0.66,0.96,"137 fb^{-1} (13 TeV)");
      paveCMS3->Draw("same");
      paveCMS4->Draw("same");
      paveCMS8->Draw("same");
      paveCMS2->Draw("same");
      leg2->Draw();
TLine *ld = new TLine(1.1,0.,1.1,90000.);
ld->SetLineColor(1.);
ld->SetLineStyle(kDashed);
ld->Draw("same");
TLine *l2 = new TLine(1.5,0.,1.5,90000.);
l2->SetLineColor(1.);
l2->SetLineStyle(kDashed);
l2->Draw("same");

pad21r->SaveAs("deltaETA_mjj2438_data_vs_MC_RSGtoQQ_v2.pdf");
pad21r->SaveAs("deltaETA_mjj2438_data_vs_MC_RSGtoQQ_v2.png");

 }
