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
#include "TEllipse.h"

void Plot_M4J_vs_M2J_QCD(){

TPaveText *paveCMS = new TPaveText(0.235,0.935,0.335,0.965,"NDC");
paveCMS->AddText("#bf{CMS} #scale[0.7]{#it{Simulation}}");
paveCMS->SetTextFont(42); 
paveCMS->SetFillColor(0);
paveCMS->SetBorderSize(0);
paveCMS->SetTextSize(0.08); 

TPaveText *paveCMS2 = new TPaveText(0.625,0.93,0.755,0.96,"NDC");
paveCMS2->SetTextFont(42);
paveCMS2->AddText("138 fb^{-1} (13 TeV)");
paveCMS2->SetFillColor(0);
paveCMS2->SetBorderSize(0);
paveCMS2->SetTextSize(0.05);


TPaveText *paveCMS3 = new TPaveText(0.15,0.813,0.30,0.893,"NDC");
paveCMS3->AddText("LO QCD MC");
paveCMS3->SetTextFont(42); 
paveCMS3->SetFillColor(0);
paveCMS3->SetBorderSize(0);
paveCMS3->SetTextSize(0.045);
paveCMS3->SetTextAlign(12);


char f_name[1024], f_name_contour_1[1024], f_name_contour_2[1024], f_name_contour_3[1024], f_name_contour_4[1024];
sprintf(f_name, "files/M4JvsM2J_QCDMC.root");
sprintf(f_name_contour_1, "files/contour68_M4JvsM2J_Suu-Diquark_W-0p0043_S-8400_chi-2100.root");
sprintf(f_name_contour_2, "files/contour68_M4JvsM2J_Suu-Diquark_W-0p015_S-8400_chi-2100.root");
sprintf(f_name_contour_3, "files/contour68_M4JvsM2J_Suu-Diquark_W-0p05_S-8400_chi-2100.root");
sprintf(f_name_contour_4, "files/contour68_M4JvsM2J_Suu-Diquark_W-0p1_S-8400_chi-2100.root");

TFile *f = new TFile(f_name,"READ");
TFile *f_contour1 = new TFile(f_name_contour_1,"READ");
TFile *f_contour2 = new TFile(f_name_contour_2,"READ");
TFile *f_contour3 = new TFile(f_name_contour_3,"READ");
TFile *f_contour4 = new TFile(f_name_contour_4,"READ");

TH2D *h_M4J_vs_M2J = (TH2D*)(f->Get("h_M4J_vs_M2J"));
TH2D *h_M4J_vs_M2J_contour1 = (TH2D*)(f_contour1->Get("h_M4J_vs_M2J"));
TH2D *h_M4J_vs_M2J_contour2 = (TH2D*)(f_contour2->Get("h_M4J_vs_M2J"));
TH2D *h_M4J_vs_M2J_contour3 = (TH2D*)(f_contour3->Get("h_M4J_vs_M2J"));
TH2D *h_M4J_vs_M2J_contour4 = (TH2D*)(f_contour4->Get("h_M4J_vs_M2J"));

h_M4J_vs_M2J_contour1->SetStats(0);
h_M4J_vs_M2J_contour2->SetStats(0);
h_M4J_vs_M2J_contour3->SetStats(0);
h_M4J_vs_M2J_contour4->SetStats(0);

gStyle->SetPalette(53);

TCanvas *c = new TCanvas("c","",800,650);
c->cd();
c->SetLogz(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.18);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.12);
c->SetBottomMargin(0.12);

double xmin=1.6;
double xmax=10.4; 
double ymin=0.15;
double ymax=2.6;

auto frame = c->DrawFrame(xmin,ymin,xmax,ymax);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.9);
frame->GetXaxis()->SetTitle("Four-jet mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.02);
frame->GetYaxis()->SetTitle("Average dijet mass [TeV]");
frame->GetYaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelOffset(0.015);
frame->GetXaxis()->SetLabelSize(0.05);

h_M4J_vs_M2J->SetZTitle("Events/bin");
h_M4J_vs_M2J->GetZaxis()->SetTitleSize(0.065);
h_M4J_vs_M2J->GetZaxis()->SetRangeUser(0.1,10000);  
h_M4J_vs_M2J->GetZaxis()->SetTitleOffset(1.);
h_M4J_vs_M2J->GetZaxis()->SetLabelSize(0.05);

h_M4J_vs_M2J->Draw("colz same");

h_M4J_vs_M2J_contour1->SetLineColor(kViolet);
h_M4J_vs_M2J_contour1->SetLineWidth(2);
h_M4J_vs_M2J_contour1->SetLineStyle(1);

h_M4J_vs_M2J_contour2->SetLineColor(kRed-3);
h_M4J_vs_M2J_contour2->SetLineWidth(2);
h_M4J_vs_M2J_contour2->SetLineStyle(1);

h_M4J_vs_M2J_contour3->SetLineColor(kBlue-3);
h_M4J_vs_M2J_contour3->SetLineWidth(2);
h_M4J_vs_M2J_contour3->SetLineStyle(1);

h_M4J_vs_M2J_contour4->SetLineColor(kGreen+2);
h_M4J_vs_M2J_contour4->SetLineWidth(2);
h_M4J_vs_M2J_contour4->SetLineStyle(1);


h_M4J_vs_M2J_contour2->Draw("CONT3 same");
h_M4J_vs_M2J_contour3->Draw("CONT3 same");
h_M4J_vs_M2J_contour4->Draw("CONT3 same");

frame->Draw("AXIS same");

paveCMS->Draw("same");
paveCMS2->Draw("same");
paveCMS3->Draw("same");


TLatex *lat = new TLatex();
lat->SetTextFont(42);
lat->SetTextSize(0.036);
lat->DrawLatexNDC(0.155, 0.783, "#color[629]{0.4} #color[418]{(33)} QCD events");
lat->DrawLatexNDC(0.155, 0.738, "expected in the");
lat->DrawLatexNDC(0.155, 0.693, "68% contour for");
lat->DrawLatexNDC(0.155, 0.648, "#Gamma / M_{S} = #color[629]{1.5} #color[418]{(10)}%");


TPaveText *paveCMS4 = new TPaveText(0.54,0.15,0.7775,0.53,"NDC");
paveCMS4->SetTextFont(42);
paveCMS4->AddText("Diquark");
paveCMS4->AddText("S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)");
paveCMS4->AddText("M_{#chi} / M_{S} = 0.25");
paveCMS4->AddText("M_{S} = 8.4 TeV");
paveCMS4->AddText("68% contours");
paveCMS4->AddText("#Gamma / M_{S} = 1.5%");
paveCMS4->AddText("#Gamma / M_{S} = 5%");
paveCMS4->AddText("#Gamma / M_{S} = 10%");
paveCMS4->SetFillColor(0);
paveCMS4->SetBorderSize(0);
paveCMS4->SetTextSize(0.036);
paveCMS4->SetTextAlign(12);
((TText*)paveCMS4->GetListOfLines()->At(5))->SetTextColor(kRed-3);
((TText*)paveCMS4->GetListOfLines()->At(6))->SetTextColor(kBlue-3);
((TText*)paveCMS4->GetListOfLines()->At(7))->SetTextColor(kGreen+2);
paveCMS4->Draw();


char cname[1024];
sprintf(cname, "plots/Figure_002-c.pdf");

c->SaveAs(cname);

}
