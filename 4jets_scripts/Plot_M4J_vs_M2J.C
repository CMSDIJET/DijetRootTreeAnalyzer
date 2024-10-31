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

void Plot_M4J_vs_M2J(){

TPaveText *paveCMS = new TPaveText(0.15,0.93,0.35,0.96,"NDC");
paveCMS->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
paveCMS->SetTextFont(42); 
paveCMS->SetFillColor(0);
paveCMS->SetBorderSize(0);
paveCMS->SetTextSize(0.06);

TPaveText *paveCMS2 = new TPaveText(0.625,0.93,0.755,0.96,"NDC");
paveCMS2->SetTextFont(42);
paveCMS2->AddText("138 fb^{-1} (13 TeV)");
paveCMS2->SetFillColor(0);
paveCMS2->SetBorderSize(0);
paveCMS2->SetTextSize(0.05);


char f_name[1024];
//sprintf(f_name, "2D_masses_data/Histos_M4JvsM2J_AllDataRun2.root");
sprintf(f_name, "/afs/cern.ch/user/i/izisopou/public/EXO-21-010/EXO-21-010-Plotting-Scripts/Figure_002/HISTOS_2016_2017_2018_Robert.root");

TFile *f = new TFile(f_name,"READ");

//TH2D *h_data = (TH2D*)(f->Get("h_2DMass_M4JplusAlpha"));
TH2D *h_data = (TH2D*)(f->Get("h_M4J_vs_M2J"));

h_data->SetStats(0);



TPaveText *paveCMS3 = new TPaveText(0.16,0.55,0.36,0.85,"NDC");
paveCMS3->SetTextFont(42);
paveCMS3->AddText("m_{4j} > 1607 GeV");
paveCMS3->AddText("M_{asymmetry} < 0.1");
paveCMS3->AddText("#Delta R_{1,2} < 2");
paveCMS3->AddText("#Delta#eta < 1.1");
paveCMS3->AddText("#alpha > 0.1");
paveCMS3->SetFillColor(0);
paveCMS3->SetBorderSize(0);
paveCMS3->SetTextSize(0.035);
paveCMS3->SetTextAlign(12);


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

auto frame = c->DrawFrame(1.4,0.001,10.4,3.5);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.9);
frame->GetXaxis()->SetTitle("Four-jet mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.02);
frame->GetYaxis()->SetTitle("Average dijet mass [TeV]");
frame->GetYaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelOffset(0.015);
frame->GetXaxis()->SetLabelSize(0.05);

h_data->SetZTitle("Events/bin");
h_data->GetZaxis()->SetTitleSize(0.065);
h_data->GetZaxis()->SetRangeUser(1.,2000000);  
h_data->GetZaxis()->SetTitleOffset(1.);
h_data->GetZaxis()->SetLabelSize(0.05);

h_data->Draw("colz same");

frame->Draw("AXIS same");

paveCMS->Draw("same");
paveCMS2->Draw("same");
paveCMS3->Draw("same");

char cname[1024];
sprintf(cname, "2D_masses_data/2DMass_allcuts.pdf");

c->SaveAs(cname);

}
