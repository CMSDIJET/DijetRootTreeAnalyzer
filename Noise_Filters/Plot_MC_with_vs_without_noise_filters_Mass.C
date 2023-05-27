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

void Plot_MC_with_vs_without_noise_filters_Mass(){

char xaxistitle[1024];
char run[1024];

sprintf(xaxistitle,"Four-jet mass [GeV]");
double xmin = 1607;
double xmax = 10072;

TPaveText *cms = new TPaveText(0.225,0.95,0.375,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TPaveText *lumileg = new TPaveText(0.81,0.95,0.96,0.99,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("13.6 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);

char fname1[1024], fname2[1024];
sprintf(fname1,"Paired_Dijet_Analysis_etalt3/Histos_QCDFlatMC_AllSelCrit_AK4PUPPI_withoutNoiseFilters.root");
sprintf(fname2,"Paired_Dijet_Analysis_etalt3/Histos_QCDFlatMC_AllSelCrit_AK4PUPPI_withBadChargedCandidate.root");

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");


TH1D *h1 = (TH1D*)f1->Get("h_FourjetMass_mc");
TH1D *h2 = (TH1D*)f2->Get("h_FourjetMass_mc");

for(int i=1; i<=h1->GetNbinsX(); i++)
{
	if(h1->GetBinContent(i)==0) h1->SetBinContent(i,0.000000000000001);
	if(h2->GetBinContent(i)==0) h2->SetBinContent(i,0.000000000000001);	
}


TCanvas *c = new TCanvas("c","",600,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);

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
h1->GetYaxis()->SetTitle("Weighted entries");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetMarkerColor(kBlack);
h1->SetLineColor(kBlack);
h1->SetLineWidth(3);
h1->SetMarkerStyle(8);
h1->SetMarkerSize(0.8);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
//h1->SetMinimum(0.0000000005);
h1->SetMinimum(0.000000000005);
//h1->SetMaximum(100);

h2->SetLineColor(kRed);
h2->SetLineWidth(3);

h1->Draw("hist");
h2->Draw("hist same");


char integNoFilt[1024], integWithFilt[1024];
sprintf(integNoFilt,"Integral NoFilter = %.7f",h1->Integral());
sprintf(integWithFilt,"Integral WithFilter = %.7f",h2->Integral());

//TLegend *leg = new TLegend(0.4,0.5,0.7,0.9,""); //top right
//TLegend *leg = new TLegend(0.5,0.05,0.7,0.45,""); //bottom right
TLegend *leg = new TLegend(0.15,0.04,0.45,0.49,""); //bottom left
//TLegend *leg = new TLegend(0.36,0.05,0.56,0.45,""); //bottom middle
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->AddEntry((TObject*)0,"AK4 PUPPI","");
leg->AddEntry((TObject*)0,"#splitline{All selection criteria}{+ |#eta| < 3}","");
//leg->AddEntry((TObject*)0,"All selection criteria","");
leg->AddEntry(h1,"No filter","L");
leg->AddEntry(h2,"With BadChargedCandidate","L");
leg->AddEntry((TObject*)0,integNoFilt,"");
leg->AddEntry((TObject*)0,integWithFilt,"");
leg->Draw();

cms->Draw();
lumileg->Draw();


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

TH1D *h_ratio = (TH1D*)h2->Clone();
h_ratio->Divide(h1);

//h_ratio->SetBinContent(4,1);

h_ratio->SetStats(0);
h_ratio->SetMarkerStyle(8);
h_ratio->SetMarkerColor(kBlack);
h_ratio->SetLineColor(kBlack);
h_ratio->SetMarkerSize(0.8);
h_ratio->GetXaxis()->SetRangeUser(xmin, xmax);
h_ratio->GetYaxis()->SetRangeUser(0.71, 1.04);
h_ratio->GetYaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelOffset(0.03);
h_ratio->GetXaxis()->SetTitle(xaxistitle);
h_ratio->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio->GetYaxis()->SetTitle("With Filter / No Filter");
h_ratio->GetYaxis()->CenterTitle(1);
h_ratio->GetYaxis()->SetTitleSize(0.08);
h_ratio->GetYaxis()->SetTitleOffset(0.6);
h_ratio->GetYaxis()->SetNdivisions(210);
h_ratio->SetLineWidth(4);
h_ratio->SetLineStyle(kDashed);
h_ratio->Draw("hist");

TLine *line = new TLine(xmin,1,xmax,1);
line->SetLineWidth(2);
line->SetLineColor(kRed);
//line->SetLineStyle(kDashed);
line->Draw("same");

char cname_1[1024], cname_2[1024];
sprintf(cname_1,"Paired_Dijet_Analysis_etalt3/AllCuts_QCDMC_with_VS_without_BadChargedCandidate_FourjetMass.png");
sprintf(cname_2,"Paired_Dijet_Analysis_etalt3/AllCuts_QCDMC_with_VS_without_BadChargedCandidate_FourjetMass.pdf");

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
