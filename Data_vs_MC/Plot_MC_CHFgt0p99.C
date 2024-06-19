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

void Plot_MC_CHFgt0p99(){

char xaxistitle[1024];

sprintf(xaxistitle,"Dijet mass (m_{jj}) [GeV]");
double xmin = 1607;
double xmax = 14000;

TPaveText *cms = new TPaveText(0.17,0.95,0.32,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname[1024];
sprintf(fname,"/afs/cern.ch/work/i/izisopou/public/4jets_Run3/CMSSW_12_4_3/src/CMSDIJET/DijetRootTreeAnalyzer/jets_with_CHFgt0p99_study/Merged.root");

TFile *f = new TFile(fname,"READ");

TH1D *h1 = (TH1D*)f->Get("ak4puppi/h_mass_CHFlt0p9");
TH1D *h2 = (TH1D*)f->Get("ak4puppi/h_mass_CHFgt0p99");

/*for(int i=1; i<=h1->GetNbinsX(); i++)
{
	if(h1->GetBinContent(i)==0) h1->SetBinContent(i,0.00000001);
	if(h2->GetBinContent(i)==0) h2->SetBinContent(i,0.00000001);	
}*/

TCanvas *c = new TCanvas("c","",600,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetLogy(1);

TPad *pad1r = new TPad("pad1", "pad1", 0, 0.38, 1, 1);
pad1r->SetRightMargin(0.05);
pad1r->SetTopMargin(0.07);
pad1r->SetLeftMargin(0.13);
pad1r->SetBottomMargin(0.01);
pad1r->SetFillColor(0);
pad1r->SetBorderMode(0);
pad1r->SetFrameFillStyle(0);
pad1r->SetFrameBorderMode(0);
pad1r->Draw();
pad1r->cd();
pad1r->cd()->SetLogy(1);
//pad1r->cd()->SetLogx(1);
pad1r->SetTickx(1);
pad1r->SetTicky(1);

h1->SetTitle("");
h1->SetStats(0);
h1->GetXaxis()->SetRangeUser(xmin, xmax);
h2->GetXaxis()->SetRangeUser(xmin, xmax);
h1->GetYaxis()->SetTitle("Weighted entries (a.u.)");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetMarkerColor(kBlack);
h1->SetMarkerStyle(8);
h1->SetMarkerSize(0.8);
h1->SetLineColor(kBlack);
h1->SetLineWidth(3);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
h1->SetMinimum(0.00000000005);
h1->SetMaximum(100000);

h2->SetMarkerColor(kRed);
h2->SetMarkerSize(0.8);
h2->SetMarkerStyle(8);
h2->SetLineWidth(3);
h2->SetLineColor(kRed);

h1->Scale(h1->GetEntries()/h1->Integral());
h2->Scale(h2->GetEntries()/h2->Integral());
h1->Scale(h2->Integral()/h1->Integral());
h1->Draw("hist");
h2->Draw("hist same");

TLegend *leg = new TLegend(0.15,0.15,0.5,0.5,""); 
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->SetHeader("AK4 PUPPI");
leg->AddEntry(h1,"#splitline{Both jets with}{CHF #leq 0.9}","L");
leg->AddEntry(h2,"#splitline{At least one jet with}{CHF #geq 0.99}","L");
leg->Draw();

cms->Draw();

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
//pad2r->cd()->SetLogx(1);

TH1D *h_ratio = (TH1D*)h1->Clone();
h_ratio->Divide(h2);

//h_ratio->SetStats(0);
h_ratio->SetMarkerStyle(8);
h_ratio->SetMarkerColor(kBlack);
h_ratio->SetLineColor(kBlack);
h_ratio->SetMarkerSize(0.8);
h_ratio->GetXaxis()->SetRangeUser(xmin, xmax);
h_ratio->GetYaxis()->SetRangeUser(0.01, 2.99);
h_ratio->GetYaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelOffset(0.03);
h_ratio->GetXaxis()->SetTitle(xaxistitle);
h_ratio->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio->GetYaxis()->SetTitle("CHF#leq0.9 / CHF#geq0.99");
h_ratio->GetYaxis()->CenterTitle(1);
h_ratio->GetYaxis()->SetTitleSize(0.09);
h_ratio->GetYaxis()->SetTitleOffset(0.5);
h_ratio->GetYaxis()->SetNdivisions(210);
h_ratio->SetLineWidth(4);
h_ratio->SetLineStyle(kDashed);
h_ratio->Draw("hist");


TLine *line = new TLine(xmin,1,xmax,1);
line->SetLineWidth(2);
line->SetLineColor(kBlack);
line->SetLineStyle(kDashed);
line->Draw("same");


char cname1[1024], cname2[1024];
sprintf(cname1,"/afs/cern.ch/work/i/izisopou/public/4jets_Run3/CMSSW_12_4_3/src/CMSDIJET/DijetRootTreeAnalyzer/jets_with_CHFgt0p99_study/mass_CHFlt0p9_vs_CHFgt0p99.png");
sprintf(cname2,"/afs/cern.ch/work/i/izisopou/public/4jets_Run3/CMSSW_12_4_3/src/CMSDIJET/DijetRootTreeAnalyzer/jets_with_CHFgt0p99_study/mass_CHFlt0p9_vs_CHFgt0p99.pdf");
c->SaveAs(cname1);
c->SaveAs(cname2);

}
