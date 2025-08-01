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

void Plot_6_Mass_Spectra_for8p6TeVsignal(){

//TFile *f = new TFile("files/Information_panel_8p6TeV_PAS.root","READ");
TFile *f = new TFile("files/Information_panel_8p6TeV_PAPER.root","READ");
TFile *f_alpha7 = new TFile("files/Mass_spectrum_alphabin7_8p6TeV_obslim.root","READ");
TFile *f_alpha8 = new TFile("files/Mass_spectrum_alphabin8_8p6TeV_obslim.root","READ");
TFile *f_alpha9 = new TFile("files/Mass_spectrum_alphabin9_8p6TeV_obslim.root","READ");
TFile *f_alpha10 = new TFile("files/Mass_spectrum_alphabin10_8p6TeV_obslim.root","READ");
TFile *f_alpha11 = new TFile("files/Mass_spectrum_alphabin11_8p6TeV_obslim.root","READ");
TFile *f_alpha12 = new TFile("files/Mass_spectrum_alphabin12_8p6TeV_obslim.root","READ");

TCanvas *c_info_panel = (TCanvas*)f->Get("panel");
TCanvas *c_alpha7 = (TCanvas*)f_alpha7->Get("c1");
TCanvas *c_alpha8 = (TCanvas*)f_alpha8->Get("c1");
TCanvas *c_alpha9 = (TCanvas*)f_alpha9->Get("c1");
TCanvas *c_alpha10 = (TCanvas*)f_alpha10->Get("c1");
TCanvas *c_alpha11 = (TCanvas*)f_alpha11->Get("c1");
TCanvas *c_alpha12 = (TCanvas*)f_alpha12->Get("c1");

TLegend *leg_alpha7 = new TLegend(0.31,0.88,0.71,0.98);
leg_alpha7->SetTextFont(42);
leg_alpha7->SetFillColorAlpha(0,0);
leg_alpha7->SetLineColor(0);
leg_alpha7->SetHeader("0.22 < #alpha < 0.24");
leg_alpha7->SetTextSize(0.072);

TLegend *leg_alpha8 = new TLegend(0.245,0.88,0.645,0.98);
leg_alpha8->SetTextFont(42);
leg_alpha8->SetFillColorAlpha(0,0);
leg_alpha8->SetLineColor(0);
leg_alpha8->SetHeader("0.24 < #alpha < 0.26");
leg_alpha8->SetTextSize(0.079);

TLegend *leg_alpha9 = new TLegend(0.233,0.88,0.633,0.98);
leg_alpha9->SetTextFont(42);
leg_alpha9->SetFillColorAlpha(0,0);
leg_alpha9->SetLineColor(0);
leg_alpha9->SetHeader("0.26 < #alpha < 0.28");
leg_alpha9->SetTextSize(0.076);


TLegend *leg_alpha10 = new TLegend(0.31,0.88,0.71,0.98);
leg_alpha10->SetTextFont(42);
leg_alpha10->SetFillColorAlpha(0,0);
leg_alpha10->SetLineColor(0);
leg_alpha10->SetHeader("0.28 < #alpha < 0.30");
leg_alpha10->SetTextSize(0.072);

TLegend *leg_alpha11 = new TLegend(0.245,0.88,0.645,0.98);
leg_alpha11->SetTextFont(42);
leg_alpha11->SetFillColorAlpha(0,0);
leg_alpha11->SetLineColor(0);
leg_alpha11->SetHeader("0.30 < #alpha < 0.32");
leg_alpha11->SetTextSize(0.079);

TLegend *leg_alpha12 = new TLegend(0.233,0.88,0.633,0.98);
leg_alpha12->SetTextFont(42);
leg_alpha12->SetFillColorAlpha(0,0);
leg_alpha12->SetLineColor(0);
leg_alpha12->SetHeader("0.32 < #alpha < 0.34");
leg_alpha12->SetTextSize(0.076);

TCanvas *canvas = new TCanvas("canvas","",4500,5100);	

gStyle->SetLineScalePS(1);

TPad *info_panel = new TPad("info_panel", "info_panel", 0.098, 0.807, 0.962, 0.97); //0.807
TPad *Xaxis_panel = new TPad("Xaxis_panel", "Xaxis_panel", 0.05, 0, 1, 0.09);
TPad *Yaxis_panel = new TPad("Yaxis_panel", "Yaxis_panel", 0, 0, 0.075, 0.9);

TPad *pad_alpha7 = new TPad("pad_alpha7","pad_alpha7",0.075,0.45,0.382,0.81); //0.81
TPad *pad_alpha8 = new TPad("pad_alpha8","pad_alpha8",0.382,0.45,0.659,0.81);
TPad *pad_alpha9 = new TPad("pad_alpha9","pad_alpha9",0.659,0.45,0.95,0.81);

TPad *pad_alpha10 = new TPad("pad_alpha10","pad_alpha10",0.075,0.08,0.382,0.44);
TPad *pad_alpha11 = new TPad("pad_alpha11","pad_alpha11",0.382,0.08,0.659,0.44);
TPad *pad_alpha12 = new TPad("pad_alpha12","pad_alpha12",0.659,0.08,0.95,0.44);

info_panel->Draw();
Xaxis_panel->Draw();
Yaxis_panel->Draw();

pad_alpha7->Draw();
pad_alpha8->Draw();
pad_alpha9->Draw();
pad_alpha10->Draw();
pad_alpha11->Draw();
pad_alpha12->Draw();

info_panel->cd();
c_info_panel->DrawClonePad();

pad_alpha7->cd();
c_alpha7->DrawClonePad();
leg_alpha7->Draw();

pad_alpha8->cd();
c_alpha8->DrawClonePad();
leg_alpha8->Draw();

pad_alpha9->cd();
c_alpha9->DrawClonePad();
leg_alpha9->Draw();

pad_alpha10->cd();
c_alpha10->DrawClonePad();
leg_alpha10->Draw();

pad_alpha11->cd();
c_alpha11->DrawClonePad();
leg_alpha11->Draw();

pad_alpha12->cd();
c_alpha12->DrawClonePad();
leg_alpha12->Draw();


Xaxis_panel->cd();

TLatex *x = new TLatex(0.627, 0.23, "#font[42]{Four-jet mass [TeV]}");
x->SetTextSize(0.35);

x->Draw();

TLatex *xLab = new TLatex();
xLab->SetTextAlign(22);
xLab->SetTextFont(42);
xLab->SetTextSize(0.15);         
xLab->DrawLatex(0.095, 0.818, "2");
xLab->DrawLatex(0.1637, 0.818, "3");
xLab->DrawLatex(0.2105, 0.818, "4");
xLab->DrawLatex(0.25, 0.818, "5");
xLab->DrawLatex(0.28, 0.818, "6");
xLab->DrawLatex(0.305, 0.818, "7");
xLab->DrawLatex(0.3275, 0.818, "8");

xLab->DrawLatex(0.385, 0.818, "2");
xLab->DrawLatex(0.454, 0.818, "3");
xLab->DrawLatex(0.502, 0.818, "4");
xLab->DrawLatex(0.54, 0.818, "5");
xLab->DrawLatex(0.5705, 0.818, "6");
xLab->DrawLatex(0.596, 0.818, "7");
xLab->DrawLatex(0.6202, 0.818, "8");

xLab->DrawLatex(0.677, 0.818, "2");
xLab->DrawLatex(0.745, 0.818, "3");
xLab->DrawLatex(0.793, 0.818, "4");
xLab->DrawLatex(0.832, 0.818, "5");
xLab->DrawLatex(0.864, 0.818, "6");
xLab->DrawLatex(0.888, 0.818, "7");
xLab->DrawLatex(0.9115, 0.818, "8");

Yaxis_panel->cd();

TLatex *y1 = new TLatex(0.65, 0.725, "#font[42]{d#sigma/dm_{4j} [pb/TeV]}");
y1->SetTextSize(0.35);
y1->SetTextAngle(90);

y1->Draw();

TLatex *y2 = new TLatex(0.65, 0.512, "#font[42]{#frac{Data #minus Fit}{Uncertainty}}");
y2->SetTextSize(0.35);
y2->SetTextAngle(90);

y2->Draw();


TLatex *y3 = new TLatex(0.65, 0.313, "#font[42]{d#sigma/dm_{4j} [pb/TeV]}");
y3->SetTextSize(0.35);
y3->SetTextAngle(90);

y3->Draw();

TLatex *y4 = new TLatex(0.65, 0.100, "#font[42]{#frac{Data #minus Fit}{Uncertainty}}");
y4->SetTextSize(0.35);
y4->SetTextAngle(90);

y4->Draw();


canvas->SaveAs("plots/Figure_005.pdf");

}

