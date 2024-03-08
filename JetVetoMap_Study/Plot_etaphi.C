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

void Plot_etaphi(){

char xaxistitle[1024], yaxistitle[1024];

sprintf(xaxistitle,"#eta of the 4 leading jets");
sprintf(yaxistitle,"#phi of the 4 leading jets");
double xmin = -3.139;
double xmax = 3.139;
double ymin = -3.2;
double ymax = 3.2;

TPaveText *cms = new TPaveText(0.20,0.95,0.35,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.04);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname[1024];
sprintf(fname,"histos/Histos_AK4PUPPI_2022EFG_VetoMapAll.root");

TFile *f = new TFile(fname,"READ");

TH2D *h = (TH2D*)f->Get("h_etaphi_data");

TCanvas *c1 = new TCanvas("c1","",700,700);
c1->cd();
c1->SetTickx(1);
c1->SetTicky(1);
c1->SetRightMargin(0.17);
c1->SetTopMargin(0.06);
c1->SetLeftMargin(0.1);
c1->SetBottomMargin(0.1);
c1->SetFillColor(0);
c1->SetBorderMode(0);
c1->SetFrameFillStyle(0);
c1->SetFrameBorderMode(0);
//c->SetLogz(1);

h->SetTitle("");
h->SetStats(0);
h->GetXaxis()->SetRangeUser(xmin, xmax);
h->GetYaxis()->SetRangeUser(ymin, ymax);
h->GetZaxis()->SetTitle("Entries");
h->GetXaxis()->SetTitle(xaxistitle);
h->GetYaxis()->SetTitle(yaxistitle);
h->GetXaxis()->SetTitleSize(0.05);
h->GetYaxis()->SetTitleSize(0.05);
h->GetZaxis()->SetTitleSize(0.05);
h->GetXaxis()->SetTitleOffset(0.85);
h->GetYaxis()->SetTitleOffset(0.9);
h->GetZaxis()->SetTitleOffset(0.97);
h->GetZaxis()->SetRangeUser(0,170);
h->Draw("COLZ");


TPaveText *toprightleg = new TPaveText(0.63,0.95,0.73,0.99,"NDC");
toprightleg->AddText("2022EFG, 27 fb^{-1} (13.6 TeV)");
toprightleg->SetTextFont(42);
toprightleg->SetTextSize(0.035);
toprightleg->SetBorderSize(0);
toprightleg->SetFillColor(0);
toprightleg->Draw();

cms->Draw();

char cname_1[1024], cname_2[1024];

sprintf(cname_1,"plots/Data_2022EFG_etaphi_VetoMapAll.png");
sprintf(cname_2,"plots/Data_2022EFG_etaphi_VetoMapAll.pdf");

c1->SaveAs(cname_1);
c1->SaveAs(cname_2);

}
