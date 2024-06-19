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

void Plot_Mass_PtHatBins(){

char xaxistitle[1024];
sprintf(xaxistitle,"Four-jet mass [GeV]");
double xmin, xmax;
xmin = 1; xmax = 12395;

TPaveText *cms = new TPaveText(0.13,0.95,0.28,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

/*TFile *f1 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-50to80_PreselOnly.root","READ");
TFile *f2 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-80to120_PreselOnly.root","READ");
TFile *f3 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-120to170_PreselOnly.root","READ");
TFile *f4 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-170to300_PreselOnly.root","READ");
TFile *f5 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-300to470_PreselOnly.root","READ");
TFile *f6 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-470to600_PreselOnly.root","READ");
TFile *f7 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-600to800_PreselOnly.root","READ");
TFile *f8 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-800to1000_PreselOnly.root","READ");
TFile *f9 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-1000to1400_PreselOnly.root","READ");
TFile *f10 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-1400to1800_PreselOnly.root","READ");
TFile *f11 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-1800to2400_PreselOnly.root","READ");
TFile *f12 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-2400to3200_PreselOnly.root","READ");
*/

TFile *f1 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-50to80.root","READ");
TFile *f2 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-80to120.root","READ");
TFile *f3 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-120to170.root","READ");
TFile *f4 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-170to300.root","READ");
TFile *f5 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-300to470.root","READ");
TFile *f6 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-470to600.root","READ");
TFile *f7 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-600to800.root","READ");
TFile *f8 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-800to1000.root","READ");
TFile *f9 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-1000to1400.root","READ");
TFile *f10 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-1400to1800.root","READ");
TFile *f11 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-1800to2400.root","READ");
TFile *f12 = new TFile("mc_histos/Histos_Run3Summer22_QCD_PT-2400to3200.root","READ");

char hname[1024];

sprintf(hname,"h_FourjetMass_mc");

TH1D *h1 = (TH1D*)f1->Get(hname);
TH1D *h2 = (TH1D*)f2->Get(hname);
TH1D *h3 = (TH1D*)f3->Get(hname);
TH1D *h4 = (TH1D*)f4->Get(hname);
TH1D *h5 = (TH1D*)f5->Get(hname);
TH1D *h6 = (TH1D*)f6->Get(hname);
TH1D *h7 = (TH1D*)f7->Get(hname);
TH1D *h8 = (TH1D*)f8->Get(hname);
TH1D *h9 = (TH1D*)f9->Get(hname);
TH1D *h10 = (TH1D*)f10->Get(hname);
TH1D *h11 = (TH1D*)f11->Get(hname);
TH1D *h12 = (TH1D*)f12->Get(hname);

TCanvas *c = new TCanvas("c","",900,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);

TPad *pad1r = new TPad("pad1", "pad1", 0, 0.38, 1, 1);
pad1r->SetRightMargin(0.05);
pad1r->SetTopMargin(0.07);
pad1r->SetLeftMargin(0.08);
pad1r->SetBottomMargin(0.15);
pad1r->SetFillColor(0);
pad1r->SetBorderMode(0);
pad1r->SetFrameFillStyle(0);
pad1r->SetFrameBorderMode(0);
pad1r->Draw();
pad1r->cd();
pad1r->cd()->SetLogy(1);
pad1r->SetTickx(1);
pad1r->SetTicky(1);

h1->SetTitle("");
h1->SetStats(0);
h1->GetXaxis()->SetRangeUser(xmin, xmax);
h2->GetXaxis()->SetRangeUser(xmin, xmax);
h1->GetYaxis()->SetTitle("Entries (no weights)");
h1->GetXaxis()->SetTitle("Four-jet mass [GeV]");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.55);
h1->GetYaxis()->SetLabelSize(0.04);
h1->GetXaxis()->SetTitleSize(0.07);
h1->GetXaxis()->SetTitleOffset(0.9);
h1->GetXaxis()->SetLabelSize(0.04);
h1->SetMinimum(0.5);
h1->SetMaximum(1000000);

h1->SetLineWidth(2);
h2->SetLineWidth(2);
h3->SetLineWidth(2);
h4->SetLineWidth(2);
h5->SetLineWidth(2);
h6->SetLineWidth(2);
h7->SetLineWidth(2);
h8->SetLineWidth(2);
h9->SetLineWidth(2);
h10->SetLineWidth(2);
h11->SetLineWidth(2);
h12->SetLineWidth(2);

h1->SetLineColor(kBlack);
h2->SetLineColor(kRed);
h3->SetLineColor(kGreen);
h4->SetLineColor(kBlue);
h5->SetLineColor(kYellow);
h6->SetLineColor(kMagenta);
h7->SetLineColor(kRed+2);
h8->SetLineColor(kGreen-8);
h9->SetLineColor(kOrange+1);
h10->SetLineColor(kGray+1);
h11->SetLineColor(kCyan);
h12->SetLineColor(kYellow+3);

h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");
h4->Draw("hist same");
h5->Draw("hist same");
h6->Draw("hist same");
h7->Draw("hist same");
h8->Draw("hist same");
h9->Draw("hist same");
h10->Draw("hist same");
h11->Draw("hist same");
h12->Draw("hist same");

cms->Draw();

TPaveText *lumileg = new TPaveText(0.635,0.95,0.905,0.99,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("Run3Summer22 (pre-EE), 13.6 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);
lumileg->Draw();

TLine *line = new TLine(1607,0.5,1607,1000000);
line->SetLineColor(kBlack);
line->SetLineWidth(4);
//line->Draw("same");


c->cd();
TPad *pad2r = new TPad("pad2r", "pad2r", 0, 0., 1, 0.35);
pad2r->SetLeftMargin(0.13);
pad2r->SetBottomMargin(0.25);
pad2r->SetRightMargin(0.05);
pad2r->SetTopMargin(0.01);
pad2r->Draw();
pad2r->cd(); 
pad2r->SetTickx(1);
pad2r->SetTicky(1);


TPaveText *pave = new TPaveText(0.15,0.75,0.85,0.95,"NDC");
pave->SetFillColor(0);
pave->SetBorderSize(0);
pave->AddText("AK4 PUPPI");
pave->AddText("Pre-selection + selection criteria");
pave->SetTextFont(42);
pave->SetTextSize(0.08);
pave->Draw();


TLegend *leg1 = new TLegend(0.15,0.05,0.45,0.7,"");
leg1->SetBorderSize(0);
leg1->SetTextSize(0.07);
leg1->AddEntry(h1,"QCD_PT-50to80","L");
leg1->AddEntry(h2,"QCD_PT-80to120","L");
leg1->AddEntry(h3,"QCD_PT-120to170","L");
leg1->AddEntry(h4,"QCD_PT-170to300","L");
leg1->AddEntry(h5,"QCD_PT-300to470","L");
leg1->AddEntry(h6,"QCD_PT-470to600","L");
leg1->Draw();

TLegend *leg2 = new TLegend(0.55,0.05,0.85,0.7,"");
leg2->SetBorderSize(0);
leg2->SetTextSize(0.07);
leg2->AddEntry(h7,"QCD_PT-600to800","L");
leg2->AddEntry(h8,"QCD_PT-800to1000","L");
leg2->AddEntry(h9,"QCD_PT-1000to1400","L");
leg2->AddEntry(h10,"QCD_PT-1400to1800","L");
leg2->AddEntry(h11,"QCD_PT-1800to2400","L");
leg2->AddEntry(h12,"QCD_PT-2400to3200","L");
leg2->Draw();


char cname_1[1024], cname_2[1024];

sprintf(cname_1,"plots/QCD_PtHatBinned_Study/FourjetMass_Spectra_PtHatBinned_Run3Summer22.png");
sprintf(cname_2,"plots/QCD_PtHatBinned_Study/FourjetMass_Spectra_PtHatBinned_Run3Summer22.pdf");

c->SaveAs(cname_1);
c->SaveAs(cname_2);


}
