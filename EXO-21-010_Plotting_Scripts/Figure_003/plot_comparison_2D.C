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

 void plot_comparison_2D(){

 gROOT->LoadMacro("setTDRStyle.C");
 setTDRStyle();
                                     //0.14
/* TPaveText *paveCMS = new TPaveText(0.2,0.86,0.4,0.9,"NDC");
 paveCMS->AddText("CMS Preliminary");
 paveCMS->SetFillColor(0);
 paveCMS->SetBorderSize(0);
 paveCMS->SetTextSize(0.04);


TPaveText *paveCMS2 = new TPaveText(0.65,0.96,0.87,0.99,"NDC");
 paveCMS2->AddText("138 fb^{-1} (13 TeV)");
 paveCMS2->SetFillColor(0);
 paveCMS2->SetBorderSize(0);
 paveCMS2->SetTextSize(0.04);*/

TPaveText *paveCMS = new TPaveText(0.17,0.825,0.37,0.875,"NDC"); //for PAPER - ilias
//TPaveText *paveCMS = new TPaveText(0.22,0.85,0.42,0.9,"NDC"); //for PAS - ilias
 //paveCMS->AddText("#splitline{CMS}{Preliminary}");
paveCMS->SetTextFont(42); // or 43  (the last digit refers to how you express the size if infraction or points○
paveCMS->AddText("#splitline{#bf{CMS}}{#scale[0.7]{#it{Simulation}}}"); //for PAPER - ilias
//paveCMS->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}"); //for PAS - ilias
 paveCMS->SetFillColor(0);
 paveCMS->SetBorderSize(0);
 paveCMS->SetTextSize(0.07);


TPaveText *paveCMS2 = new TPaveText(0.815,0.96,0.845,0.99,"NDC"); //0.8,0.96,0.83,0.99,"NDC"
paveCMS2->SetTextFont(42);
 paveCMS2->AddText("13 TeV");
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

TFile *finm;
finm= new TFile("MinDR_slices_alphavsM4J.root","READ");

//Robert.root alpha vs M4J=h_alpha_vs_M2J
 
  
//TH2D *h_M4J_vs_M2J_data=(TH2D*)(fin->Get("h_alpha_vs_M2J"));

TH2D *h_alpha_vs_M2J_data=(TH2D*)(finm->Get("h_M4J_vs_M2J"));

TH2D *Blank                   = (TH2D*)(h_alpha_vs_M2J_data->Clone());
Blank->SetMarkerColor(0);
Blank->SetLineColor(0);

//gStyle->SetPalette(kRedBlue);


 const int nMassBins = 103;
 
 double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
     4686,  4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};
 

 



TLegend *leg4 =new TLegend(.31, .77, .71, .89); //.35, .79, .75, .91
     leg4->SetFillColor(0);
     leg4->SetBorderSize(0);
     leg4->AddEntry(Blank, "#font[42]{#splitline{Diquark: S #rightarrow #chi#chi #rightarrow (ug) (ug)}{#splitline{M(S) = 8.4 TeV}{M(#chi) = 2.1 TeV}}}","l");
 //leg4->AddEntry(Blank, "#splitline{M(S) = 8.4 TeV}{M(#chi) = 2.1 TeV}","l");
leg4->SetTextSize(0.045); //0.037



TLegend *leg5 =new TLegend(.3, .3, .5, .6);
     leg5->SetFillColor(0);
     leg5->SetBorderSize(0);
     leg5->AddEntry(Blank, "#splitline{Signal}{#splitline{1#sigma and 2#sigma}{contours}}","l");
leg5->SetTextSize(0.03);
leg5->SetTextColor(6);




/*TCanvas *pad67 = new TCanvas("pad67", "",1);
     pad67->cd()->SetRightMargin(0.18);
pad67->cd()->SetLogz(1);
     h_M4J_vs_M2J_data->GetXaxis()->SetTitle("4J vs 2J");
h_M4J_vs_M2J_data->GetXaxis()->SetRangeUser(1.6,10);
h_M4J_vs_M2J_data->GetYaxis()->SetRangeUser(0.15,2.5);
//h_M4J_vs_M2J_data->GetZaxis()->SetRangeUser(0.,1200);
h_M4J_vs_M2J_data->SetMinimum(1);
//h_M4J_vs_M2J_data->GetZaxis()->SetRangeUser(0.,13057178);
//h_M4J_vs_M2J_data->SetMaximum(13057178);

 h_M4J_vs_M2J_data->GetXaxis()->SetTitleOffset(1.2);
h_M4J_vs_M2J_data->GetYaxis()->SetTitleOffset(1.2);
h_M4J_vs_M2J_data->GetZaxis()->SetTitleOffset(1.2);
     h_M4J_vs_M2J_data->SetXTitle("Four-jet Mass [TeV]");
h_M4J_vs_M2J_data->SetYTitle("Average Dijet Mass [TeV]");
h_M4J_vs_M2J_data->SetZTitle("Events/bin");

TEllipse *e = new TEllipse (7.27, 1.78, 1.25, 0.45);
e->SetLineColor(6);
e->SetFillStyle(0);
TEllipse *e2 = new TEllipse (7.96, 1.955, 0.48, 0.13);
e2->SetLineColor(6);
e2->SetFillStyle(0);
e->SetLineWidth(2);
e2->SetLineWidth(2);

     h_M4J_vs_M2J_data->Draw("colz");

     leg5->Draw("same");
paveCMS->Draw("same");
paveCMS2->Draw("same");
//e->Draw("same l");
//e2->Draw("same l");*/


TCanvas *pad67 = new TCanvas("pad67", "");
     pad67->cd()->SetRightMargin(0.18);
pad67->cd()->SetLogz(1);
     h_alpha_vs_M2J_data->GetXaxis()->SetTitle("4J vs 2J");
h_alpha_vs_M2J_data->GetXaxis()->SetRangeUser(1.6,10);
h_alpha_vs_M2J_data->GetYaxis()->SetRangeUser(0.08,0.5);
//h_alpha_vs_M2J_data->GetZaxis()->SetRangeUser(0.,1200);
//h_alpha_vs_M2J_data->SetMinimum(1);
//h_alpha_vs_M2J_data->GetZaxis()->SetRangeUser(0.,13057178);
//h_alpha_vs_M2J_data->SetMaximum(13057178);
 h_alpha_vs_M2J_data->GetXaxis()->SetTitleOffset(0.9);
h_alpha_vs_M2J_data->GetYaxis()->SetTitleOffset(1.2);
h_alpha_vs_M2J_data->GetZaxis()->SetTitleOffset(0.95);
     h_alpha_vs_M2J_data->SetXTitle("Four-jet mass [TeV]");
h_alpha_vs_M2J_data->SetYTitle("#alpha = Average dijet mass/ Four-jet mass");
h_alpha_vs_M2J_data->SetZTitle("Events/bin");
h_alpha_vs_M2J_data->GetXaxis()->SetTitleSize(0.065);
h_alpha_vs_M2J_data->GetYaxis()->SetTitleSize(0.055);
h_alpha_vs_M2J_data->GetZaxis()->SetTitleSize(0.065);

h_alpha_vs_M2J_data->GetZaxis()->SetRangeUser(0.0011,9);

//gStyle->SetPalette(51); 
gStyle->SetPalette(53); 
//gStyle->SetPalette(86);

     h_alpha_vs_M2J_data->Draw("colz");

/*TLine *l1 = new TLine(0.15,0.15,2.5,0.15);
l1->SetLineWidth(2);
l1->SetLineColor(1);
l1->SetLineStyle(2);

TLine *l2 = new TLine(0.15,0.25,2.5,0.25);
l2->SetLineWidth(2);
l2->SetLineColor(1);
l2->SetLineStyle(2);

TLine *l3 = new TLine(0.15,0.35,2.5,0.35);
l3->SetLineWidth(2);
l3->SetLineColor(1);
l3->SetLineStyle(2);*/


TLine *l1 = new TLine(1.6,0.10,10,0.10);
l1->SetLineWidth(2);
l1->SetLineColor(1);
l1->SetLineStyle(2);

TLine *l2 = new TLine(1.6,0.12,10,0.12);
l2->SetLineWidth(2);
l2->SetLineColor(1);
l2->SetLineStyle(2);

TLine *l3 = new TLine(1.6,0.14,10,0.14);
l3->SetLineWidth(2);
l3->SetLineColor(1);
l3->SetLineStyle(2);


TLine *l4 = new TLine(1.6,0.16,10.,0.16);
l4->SetLineWidth(2);
l4->SetLineColor(1);
l4->SetLineStyle(2);

TLine *l5 = new TLine(1.6,0.18,10.,0.18);
l5->SetLineWidth(2);
l5->SetLineColor(1);
l5->SetLineStyle(2);

TLine *l6 = new TLine(1.6,0.2,10.,0.2);
l6->SetLineWidth(2);
l6->SetLineColor(1);
l6->SetLineStyle(2);

TLine *l7 = new TLine(1.6,0.22,10.,0.22);
l7->SetLineWidth(2);
l7->SetLineColor(1);
l7->SetLineStyle(2);

TLine *l8 = new TLine(1.6,0.24,10.,0.24);
l8->SetLineWidth(2);
l8->SetLineColor(1);
l8->SetLineStyle(2);

TLine *l9 = new TLine(1.6,0.26,10.,0.26);
l9->SetLineWidth(2);
l9->SetLineColor(1);
l9->SetLineStyle(2);

TLine *l10 = new TLine(1.6,0.28,10.,0.28);
l10->SetLineWidth(2);
l10->SetLineColor(1);
l10->SetLineStyle(2);

TLine *l11 = new TLine(1.6,0.3,10.,0.3);
l11->SetLineWidth(2);
l11->SetLineColor(1);
l11->SetLineStyle(2);

TLine *l12 = new TLine(1.6,0.32,10.,0.32);
l12->SetLineWidth(2);
l12->SetLineColor(1);
l12->SetLineStyle(2);

TLine *l13 = new TLine(1.6,0.34,10.,0.34);
l13->SetLineWidth(2);
l13->SetLineColor(1);
l13->SetLineStyle(2);

     leg4->Draw("same");
paveCMS->Draw("same");
paveCMS2->Draw("same");
l1->Draw("same");
l2->Draw("same");
l3->Draw("same");
l4->Draw("same");
l5->Draw("same");
l6->Draw("same");
l7->Draw("same");
l8->Draw("same");
l9->Draw("same");
l10->Draw("same");
l11->Draw("same");
l12->Draw("same");
l13->Draw("same");

pad67->SaveAs("Figure_003-b.pdf");


}
