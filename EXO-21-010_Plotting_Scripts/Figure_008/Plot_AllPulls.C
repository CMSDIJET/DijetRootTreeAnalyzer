#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH3I.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TLatex.h"

void Plot_AllPulls(){


//TFile *f_pull1 = new TFile("pad1_margin_V3_PAS.root","READ");
TFile *f_pull1 = new TFile("new_pad1_margin_V3_PAPER_FR.root","READ");
TFile *f_pull2 = new TFile("new_pad2_margin_V3_FR.root","READ");
TFile *f_pull3 = new TFile("new_pad3_margin_V3_FR.root","READ");
TFile *f_pull4 = new TFile("new_pad4_margin_V3_FR.root","READ");
TFile *f_pull5 = new TFile("new_pad5_margin_V3_FR.root","READ");
TFile *f_pull6 = new TFile("new_pad6_margin_V3_FR.root","READ");
TFile *f_pull7 = new TFile("new_pad7_margin_V3_ilias_FR.root","READ");



TFile *f_pull8 = new TFile("new_pad8_margin_V3_FR.root","READ");
TFile *f_pull9 = new TFile("new_pad9_margin_V3_FR.root","READ");
TFile *f_pull10 = new TFile("new_pad10_margin_V3_FR.root","READ");
TFile *f_pull11 = new TFile("new_pad11_margin_V3_FR.root","READ");
TFile *f_pull12 = new TFile("new_pad12_margin_V3_FR.root","READ");
TFile *f_pull13 = new TFile("new_pad13_margin_V3_FR.root","READ");
TFile *f_pull14 = new TFile("new_pad14_margin_V3_FR.root","READ");

//TCanvas *c_info_panel = (TCanvas*)f->Get("panel");
TCanvas *c_pull1 = (TCanvas*)f_pull1->Get("c1");
TCanvas *c_pull2 = (TCanvas*)f_pull2->Get("c1");
TCanvas *c_pull3 = (TCanvas*)f_pull3->Get("c1");
TCanvas *c_pull4 = (TCanvas*)f_pull4->Get("c1");
TCanvas *c_pull5 = (TCanvas*)f_pull5->Get("c1");
TCanvas *c_pull6 = (TCanvas*)f_pull6->Get("c1");
TCanvas *c_pull7 = (TCanvas*)f_pull7->Get("c1");
TCanvas *c_pull8 = (TCanvas*)f_pull8->Get("c1");
TCanvas *c_pull9 = (TCanvas*)f_pull9->Get("c1");
TCanvas *c_pull10 = (TCanvas*)f_pull10->Get("c1");
TCanvas *c_pull11 = (TCanvas*)f_pull11->Get("c1");
TCanvas *c_pull12 = (TCanvas*)f_pull12->Get("c1");
TCanvas *c_pull13 = (TCanvas*)f_pull13->Get("c1");
TCanvas *c_pull14 = (TCanvas*)f_pull14->Get("c1");


//TCanvas *canvas = new TCanvas("canvas","",3000,4300);	

//gStyle->SetLineScalePS(1);
gStyle->SetOptStat(0);

//canvas->cd();

TCanvas *c = new TCanvas("c","Signal region Data & Prediction",3000,4300);
//c->Divide(2,7,0,0);



TPad *lumi_panel = new TPad("lumi_panel", "lumi_panel", 0.08, 0.95, 1., 1.);

TPad *Xaxis_panel = new TPad("Xaxis_panel", "Xaxis_panel", 0.05, 0, 1, 0.047);
TPad *Yaxis_panel = new TPad("Yaxis_panel", "Yaxis_panel", 0, 0, 0.08, 0.9);

TPad *pad_pull1 = new TPad("pad_pull1","pad_pull1",0.08,0.83,0.55,0.97);

TPad *pad_pull2 = new TPad("pad_pull2","pad_pull2",0.08,0.7,0.55,0.83);

TPad *pad_pull3 = new TPad("pad_pull3","pad_pull3",0.08,0.57,0.55,0.7);
TPad *pad_pull4 = new TPad("pad_pull4","pad_pull4",0.08,0.44,0.55,0.57);
TPad *pad_pull5 = new TPad("pad_pull5","pad_pull5",0.08,0.31,0.55,0.44);
TPad *pad_pull6 = new TPad("pad_pull6","pad_pull6",0.08,0.18,0.55,0.31);
TPad *pad_pull7 = new TPad("pad_pull7","pad_pull7",0.08,0.03,0.55,0.18);

TPad *pad_pull8 = new TPad("pad_pull8","pad_pull8",0.55,0.83,0.97,0.956); //0.55,0.83,0.97,0.956

TPad *pad_pull9 = new TPad("pad_pull9","pad_pull9",0.55,0.7,0.97,0.83);

TPad *pad_pull10 = new TPad("pad_pull10","pad_pull10",0.55,0.57,0.97,0.7);

TPad *pad_pull11 = new TPad("pad_pull11","pad_pull11",0.55,0.44,0.97,0.57);
TPad *pad_pull12 = new TPad("pad_pull12","pad_pull12",0.55,0.31,0.97,0.44);
TPad *pad_pull13 = new TPad("pad_pull13","pad_pull13",0.55,0.18,0.97,0.31);
TPad *pad_pull14 = new TPad("pad_pull14","pad_pull14",0.55,0.03,0.97,0.18);

pad_pull1->SetBottomMargin(0);
pad_pull2->SetBottomMargin(0);
pad_pull3->SetBottomMargin(0);
pad_pull4->SetBottomMargin(0);
pad_pull5->SetBottomMargin(0);
pad_pull6->SetBottomMargin(0);
//pad_pull7->SetBottomMargin(0);


pad_pull8->SetBottomMargin(0);
pad_pull9->SetBottomMargin(0);
pad_pull10->SetBottomMargin(0);
pad_pull11->SetBottomMargin(0);
pad_pull12->SetBottomMargin(0);
pad_pull13->SetBottomMargin(0);
pad_pull14->SetBottomMargin(0);



pad_pull1->SetTopMargin(0.02);
pad_pull2->SetTopMargin(0);
pad_pull3->SetTopMargin(0);
pad_pull4->SetTopMargin(0);
pad_pull5->SetTopMargin(0);
pad_pull6->SetTopMargin(0);
pad_pull7->SetTopMargin(0);

pad_pull8->SetTopMargin(0.02);
pad_pull9->SetTopMargin(0);
pad_pull10->SetTopMargin(0);
pad_pull11->SetTopMargin(0);
pad_pull12->SetTopMargin(0);
pad_pull13->SetTopMargin(0);
pad_pull14->SetTopMargin(0);


c_pull8->SetLeftMargin(0);
pad_pull8->SetLeftMargin(0);

c_pull9->SetLeftMargin(0);
pad_pull9->SetLeftMargin(0);


c_pull10->SetLeftMargin(0);
pad_pull10->SetLeftMargin(0);

c_pull11->SetLeftMargin(0);
pad_pull11->SetLeftMargin(0);

c_pull12->SetLeftMargin(0);
pad_pull12->SetLeftMargin(0);

c_pull13->SetLeftMargin(0);
pad_pull13->SetLeftMargin(0);

c_pull14->SetLeftMargin(0);
pad_pull14->SetLeftMargin(0);

c_pull1->SetBottomMargin(0);
c_pull2->SetBottomMargin(0);


c_pull3->SetBottomMargin(0);
c_pull4->SetBottomMargin(0);
c_pull5->SetBottomMargin(0);
c_pull6->SetBottomMargin(0);
//c_pull7->SetBottomMargin(0.04);
c_pull8->SetBottomMargin(0);
c_pull9->SetBottomMargin(0);
c_pull10->SetBottomMargin(0);
c_pull11->SetBottomMargin(0);
c_pull12->SetBottomMargin(0);
c_pull13->SetBottomMargin(0);


c_pull1->SetTopMargin(0.02);
c_pull2->SetTopMargin(0);
c_pull3->SetTopMargin(0);
c_pull4->SetTopMargin(0);
c_pull5->SetTopMargin(0);
c_pull6->SetTopMargin(0);
c_pull7->SetTopMargin(0);

c_pull8->SetTopMargin(0.02);
c_pull9->SetTopMargin(0);
c_pull10->SetTopMargin(0);
c_pull11->SetTopMargin(0);
c_pull12->SetTopMargin(0);
c_pull13->SetTopMargin(0);
c_pull14->SetTopMargin(0);



lumi_panel->Draw();
Xaxis_panel->Draw();
Yaxis_panel->Draw();

pad_pull1->Draw();
pad_pull2->Draw();

pad_pull3->Draw();
pad_pull4->Draw();
pad_pull5->Draw();
pad_pull6->Draw();
pad_pull7->Draw();

pad_pull8->Draw();
pad_pull9->Draw();

pad_pull10->Draw();
pad_pull11->Draw();
pad_pull12->Draw();
pad_pull13->Draw();
pad_pull14->Draw();




pad_pull1->cd();
c_pull1->DrawClonePad();
pad_pull2->cd();
c_pull2->DrawClonePad();
pad_pull3->cd();
c_pull3->DrawClonePad();
pad_pull4->cd();
c_pull4->DrawClonePad();
pad_pull5->cd();
c_pull5->DrawClonePad();
pad_pull6->cd();
c_pull6->DrawClonePad();
pad_pull7->cd();
c_pull7->DrawClonePad();
pad_pull8->cd();
c_pull8->DrawClonePad();
pad_pull9->cd();
c_pull9->DrawClonePad();
pad_pull10->cd();
c_pull10->DrawClonePad();
pad_pull11->cd();
c_pull11->DrawClonePad();
pad_pull12->cd();
c_pull12->DrawClonePad();
pad_pull13->cd();
c_pull13->DrawClonePad();
pad_pull14->cd();
c_pull14->DrawClonePad();


lumi_panel->cd();

TLatex *lumi = new TLatex(0.808, 0.17, "#font[42]{138 fb^{-1} (13 TeV)}"); //0.108
lumi->SetTextSize(0.3);
lumi->SetTextColor(kBlack);

lumi->Draw();

Xaxis_panel->cd();

TLatex *x = new TLatex(0.655, 0.116, "#font[42]{Four-jet mass [TeV]}"); //0.108
x->SetTextSize(0.55);

x->Draw();


Yaxis_panel->cd();

TLatex *y = new TLatex(0.65, 0.79, "#font[42]{#frac{(Data-Fit)}{Uncertainty}}");
y->SetTextSize(0.45);
y->SetTextAngle(90);

y->Draw();


pad_pull1->cd();
TLatex *yLab = new TLatex();
yLab->SetTextAlign(22);
yLab->SetTextFont(42);
yLab->SetTextSize(0.085);         
yLab->DrawLatex(0.98, 0.82, "3");
yLab->DrawLatex(0.98, 0.445, "0");
yLab->DrawLatex(0.975, 0.07, "-3");

//TFile *output = new TFile("output.root","RECREATE"); 
//c->Write();

c->SaveAs("Figure_008.pdf");
}
