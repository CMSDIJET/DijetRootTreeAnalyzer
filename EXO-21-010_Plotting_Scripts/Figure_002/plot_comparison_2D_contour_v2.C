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
#include "setTDRStyle.C"
#include "TEllipse.h"

 void plot_comparison_2D_contour_v2(){

 gROOT->LoadMacro("setTDRStyle.C");
 setTDRStyle();

                                     //0.14
 //TPaveText *paveCMS = new TPaveText(0.2,0.85,0.4,0.9,"NDC"); //for PAS - ilias
 TPaveText *paveCMS = new TPaveText(0.2,0.85,0.3,0.9,"NDC"); //for PAPER - ilias
 //paveCMS->AddText("#splitline{CMS}{Preliminary}");
paveCMS->SetTextFont(42); // or 43  (the last digit refers to how you express the size if infraction or points○
//paveCMS->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}"); //for PAS - ilias
paveCMS->AddText("#bf{CMS}"); //for PAPER - ilias
 paveCMS->SetFillColor(0);
 paveCMS->SetBorderSize(0);
 paveCMS->SetTextSize(0.07);


TPaveText *paveCMS2 = new TPaveText(0.7,0.96,0.83,0.99,"NDC");
paveCMS2->SetTextFont(42);
 paveCMS2->AddText("138 fb^{-1} (13 TeV)");
 paveCMS2->SetFillColor(0);
 paveCMS2->SetBorderSize(0);
 paveCMS2->SetTextSize(0.04);


 /*TPaveText *paveCMS2 = new TPaveText(0.25,0.65,0.45,0.9,"NDC");
 paveCMS2->AddText("|#eta|<2.5" );
 paveCMS2->AddText("Masymmetry<0.1");
 paveCMS2->AddText("|#Delta #eta| < 1.1");
//paveCMS2->AddText("M4J > 4 TeV");
//paveCMS2->AddText("#Delta R <1.2");
 paveCMS2->SetFillColor(0);
 paveCMS2->SetBorderSize(0);
 paveCMS2->SetTextSize(0.04);*/

 TPaveText *paveCMS3 = new TPaveText(0.7,0.65,0.9,0.78,"NDC");
 paveCMS3->AddText("|#eta|<2.5" );
 paveCMS3->AddText("Masymmetry<0.1");
paveCMS3->AddText("|#Delta #eta| < 1.1");
//paveCMS3->AddText("M4J > 4 TeV");
//paveCMS3->AddText("#Delta R <1.2");
 paveCMS3->SetFillColor(0);
 paveCMS3->SetBorderSize(0);
 paveCMS3->SetTextSize(0.04);


 TPaveText *paveCMS7 = new TPaveText(0.5,0.65,0.7,0.9,"NDC");
 paveCMS7->AddText("|#eta|<2.5" );
 paveCMS7->AddText("Masymmetry < 0.1");
paveCMS7->AddText("|#Delta #eta| < 1.1");
//paveCMS7->AddText("M4J > 4 TeV");
 paveCMS7->SetFillColor(0);
 paveCMS7->SetBorderSize(0);
 paveCMS7->SetTextSize(0.04);

 TPaveText *paveCMS4 = new TPaveText(0.22,0.8,0.34,0.93,"NDC");
 paveCMS4->AddText("|#eta|<2.5" );
 paveCMS4->AddText("Masymmetry<0.1");
paveCMS4->AddText("|#Delta #eta| < 1.1");
//paveCMS4->AddText("M4J > 4 TeV");
//paveCMS4->AddText("#Delta R <1.2");
 paveCMS4->SetFillColor(0);
 paveCMS4->SetBorderSize(0);
 paveCMS4->SetTextSize(0.04);

 TPaveText *paveCMS5 = new TPaveText(0.39,0.80,0.51,0.93,"NDC");
 paveCMS5->AddText("|#eta|<2.5" );
 paveCMS5->AddText("Masymmetry<0.1");
 paveCMS5->AddText("|#Delta #eta| < 1.1");
//paveCMS5->AddText("M4J > 4 TeV");
//paveCMS5->AddText("#Delta R <1.2");
 paveCMS5->SetFillColor(0);
 paveCMS5->SetBorderSize(0);
 paveCMS5->SetTextSize(0.04);

 TPaveText *paveCMS6 = new TPaveText(0.39,0.80,0.51,0.93,"NDC");
 paveCMS6->AddText("|#eta|<2.5" );
paveCMS6->AddText("Masymmetry<0.1");
paveCMS6->AddText("|#Delta #eta| < 1.1");
//paveCMS6->AddText("M4J > 4 TeV");
 paveCMS6->SetFillColor(0);
 paveCMS6->SetBorderSize(0);
 paveCMS6->SetTextSize(0.04);

  float lumi;
 
//if(doJSON==1) fin = new TFile ("histos_4Jets_2017Data_allruns_nomjjcut_MASYMMETRY_lt_0p05.root","READ");
TFile *fin;
fin = new TFile("HISTOS_2016_2017_2018_Robert.root","READ");

//Robert.root alpha vs M4J=h_alpha_vs_M2J
 
  
TH2D *h_M4J_vs_M2J_data=(TH2D*)(fin->Get("h_M4J_vs_M2J"));

//TH2D *h_alpha_vs_M2J_data=(TH2D*)(fin->Get("h_M4J_vs_M2J"));

TH2D *Blank                   = (TH2D*)(h_M4J_vs_M2J_data->Clone());
Blank->SetMarkerColor(0);
Blank->SetLineColor(0);


TFile *f = new TFile("contour68.root","READ");
TH2D *hint=(TH2D*)(f->Get("h_M4J_vs_M2J"));

TFile *f1 = new TFile("contour94.root","READ");
TH2D *hint1=(TH2D*)(f1->Get("h_M4J_vs_M2J"));


//gStyle->SetPalette(kRedBlue);

 const int nMassBins = 103;
 
 double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
     4686,  4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};
 

    Double_t x[5], y[5];
  
   /*  x[0] = 5.25;
     y[0]= 2.0;
     x[2]=8.6;
     y[2]=2.0;
     x[3]=8.0;
     y[3]=1.2;
     x[1]=8.0;
     y[1]=2.2;
x[4] = 5.25;
     y[4]= 2.0;*/

 x[0] = 5.45;
     y[0]= 2.05;
     x[2]=8.8;
     y[2]=2.05;
     x[3]=8.2;
     y[3]=1.25;
     x[1]=8.2;
     y[1]=2.25;
x[4] = 5.45;
     y[4]= 2.05;
     
   
   //TGraph* gr = new TGraph(5,x,y);

Double_t x1[5], y1[5];
  
    /* x1[0] = 7.25;
     y1[0]= 2.0;
     x1[2]=8.33;
     y1[2]=2.0;
     x1[3]=8.0;
     y1[3]=1.8;
     x1[1]=8.0;
     y1[1]=2.1;
x1[4] = 7.25;
     y1[4]= 2.0;*/

x1[0] = 7.45;
     y1[0]= 2.05;
     x1[2]=8.5;
     y1[2]=2.05;
     x1[3]=8.2;
     y1[3]=1.85;
     x1[1]=8.2;
     y1[1]=2.15;
x1[4] = 7.45;
     y1[4]= 2.05;
     
   
  // TGraph* gr1 = new TGraph(5,x1,y1);
  



TLegend *leg4 =new TLegend(.4, .85, .65, .9);
     leg4->SetFillColor(0);
     leg4->SetBorderSize(0);
     leg4->AddEntry(Blank, "#splitline{Diquark: S #rightarrow #chi#chi #rightarrow (ug) (ug)}{#splitline{M(S) = 8.4 TeV}{M(#chi) = 2.1 TeV}}","l");
 //leg4->AddEntry(Blank, "#splitline{M(S) = 8.4 TeV}{M(#chi) = 2.1 TeV}","l");
leg4->SetTextSize(0.03);



TLegend *leg5 =new TLegend(.48, .15, .56, .3);
     leg5->SetFillColor(0);
     leg5->SetBorderSize(0);
     leg5->AddEntry(Blank, "#splitline{Diquark: S #rightarrow #chi#chi #rightarrow (ug) (ug)}{#splitline{68% and 95%}{contours}}","l");
leg5->SetTextSize(0.03);
leg5->SetTextColor(6);

TPaveText *legend = new TPaveText(0.62,0.17,0.72,0.37,"NDC"); //0.63,0.3,0.73,0.5,"NDC"
legend->SetTextFont(42);
legend->AddText("Diquark");
legend->AddText("S #rightarrow #chi#chi #rightarrow (ug) (ug)");
legend->AddText("68% and 95%");
legend->AddText("contours");
legend->SetFillColor(0);
legend->SetBorderSize(0);
legend->SetTextSize(0.045); //0.035
legend->SetTextColor(6);



TCanvas *pad67 = new TCanvas("pad67", "",1);
pad67->cd()->SetRightMargin(0.18);
pad67->cd()->SetLogz(1);
h_M4J_vs_M2J_data->GetXaxis()->SetTitle("4J vs 2J");
h_M4J_vs_M2J_data->GetXaxis()->SetRangeUser(1.6,10);
h_M4J_vs_M2J_data->GetYaxis()->SetRangeUser(0.15,2.5);
//h_M4J_vs_M2J_data->GetZaxis()->SetRangeUser(0.,1200);
h_M4J_vs_M2J_data->SetMinimum(1);
//h_M4J_vs_M2J_data->GetZaxis()->SetRangeUser(0.,13057178);
//h_M4J_vs_M2J_data->SetMaximum(13057178);
h_M4J_vs_M2J_data->GetXaxis()->SetTitleOffset(0.9);
h_M4J_vs_M2J_data->GetYaxis()->SetTitleOffset(1.);
h_M4J_vs_M2J_data->GetZaxis()->SetTitleOffset(0.9);
h_M4J_vs_M2J_data->SetXTitle("Four-jet mass [TeV]");
h_M4J_vs_M2J_data->SetYTitle("Average dijet mass [TeV]");
h_M4J_vs_M2J_data->SetZTitle("Events/bin");
h_M4J_vs_M2J_data->GetXaxis()->SetTitleSize(0.065);
h_M4J_vs_M2J_data->GetYaxis()->SetTitleSize(0.065);
h_M4J_vs_M2J_data->GetZaxis()->SetTitleSize(0.065);
h_M4J_vs_M2J_data->GetZaxis()->SetRangeUser(1.,200000);  
 
//gStyle->SetPalette(51); 
gStyle->SetPalette(53); 
//gStyle->SetPalette(86);
//gStyle->SetPalette(97);

h_M4J_vs_M2J_data->Draw("colz");
/*gr->SetLineColor(6);
gr->SetLineWidth(2);
gr1->SetLineWidth(2);
gr1->SetLineColor(6);
gr->Draw("CONT2");
gr1->Draw("CONT2");*/

hint->SetLineWidth(2);
hint->SetLineColor(6);
hint->SetLineStyle(3);
hint1->SetLineStyle(7);
hint1->SetLineWidth(2);
hint1->SetLineColor(6);

hint->Draw("CONT3 same");
hint1->Draw("CONT3 same");

//leg5->Draw("same");
paveCMS->Draw("same");
paveCMS2->Draw("same");
legend->Draw("same");


pad67->SaveAs("Figure_002.pdf");

}
