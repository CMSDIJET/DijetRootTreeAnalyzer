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

void Plot_Data_Run2_vs_Run3(){

char xaxistitle[1024];

sprintf(xaxistitle,"Four-jet mass [GeV]");
double xmin = 1607;
double xmax = 9067;

TPaveText *cms = new TPaveText(0.17,0.95,0.32,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname1[1024], fname2[1024];
sprintf(fname1,"RunsBCDE_Full/Histos_DataRuns2022BCDE_VS_QCDFlatMC_AllSelCrit_PUReweight_AK4PUPPI_MCtruthPlusL2L3ResV2.root");
//sprintf(fname2,"../HISTOS_4J_Alldata_Run2.root");
sprintf(fname2,"../HISTOS_4J_2016Data_13p4fb-1_Run2.root");

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");

TH1D *h1 = (TH1D*)f1->Get("h_FourjetMass_data");
TH1D *h2 = (TH1D*)f2->Get("h_FourjetMass");

/*for(int i=1; i<=h1->GetNbinsX(); i++)
{
	if(h1->GetBinContent(i)==0) h1->SetBinContent(i,0.00000001);
	if(h2->GetBinContent(i)==0) h2->SetBinContent(i,0.00000001);	
}*/

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
h1->GetYaxis()->SetTitle("Entries");
//h1->GetYaxis()->SetTitle("Entries normalized");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetMarkerColor(kBlack);
h1->SetMarkerStyle(8);
h1->SetMarkerSize(0.8);
h1->SetLineColor(kBlack);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
//h1->SetMinimum(0.011);
h1->SetMinimum(0.5);

h2->SetMarkerColor(kRed);
h2->SetMarkerSize(0.8);
h2->SetMarkerStyle(8);
h2->SetLineColor(kRed);

h1->Draw("PE1");
//h2->Scale(13.44/137.6);
h2->Draw("PE1 same");
//h1->Draw("PE1 same");

TLegend *leg = new TLegend(0.45,0.7,0.7,0.9,""); //top right
//TLegend *leg = new TLegend(0.5,0.07,0.7,0.47,""); //bottom right
//TLegend *leg = new TLegend(0.2,0.07,0.5,0.47,""); //bottom left
//TLegend *leg = new TLegend(0.32,0.07,0.52,0.47,""); //bottom middle
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->AddEntry(h1,"Run3 (13.6 TeV): 13.44 fb^{-1}","PE");
leg->AddEntry(h2,"Run2 (13 TeV): 13.42 fb^{-1}","PE");
//leg->AddEntry(h2,"#splitline{Run2 (13 TeV): All data}{scaled to 13.44 fb^{-1}}","PE");
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
h_ratio->GetYaxis()->SetRangeUser(0.31, 2.31);
h_ratio->GetYaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelOffset(0.03);
h_ratio->GetXaxis()->SetTitle(xaxistitle);
h_ratio->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio->GetYaxis()->SetTitle("Run3 / Run2");
h_ratio->GetYaxis()->CenterTitle(1);
h_ratio->GetYaxis()->SetTitleSize(0.12);
h_ratio->GetYaxis()->SetTitleOffset(0.5);
h_ratio->GetYaxis()->SetNdivisions(210);
h_ratio->Draw("PE");

//gStyle->SetOptFit(1111);
h_ratio->Fit("pol1");


TLine *line = new TLine(xmin,1,xmax,1);
line->SetLineWidth(2);
line->SetLineColor(kBlack);
line->SetLineStyle(kDashed);
line->Draw("same");
 
TLegend *fitres = new TLegend(0.6,0.73,0.85,0.93,"");
fitres->SetTextSize(0.06);
fitres->SetBorderSize(0);
fitres->AddEntry((TObject*)0,"Fit with p0+p1*x","");
fitres->AddEntry((TObject*)0,"#chi^{2} / ndf = 36.8 / 27","");
fitres->AddEntry((TObject*)0,"p0 = 1.16 #pm 0.06","");
fitres->AddEntry((TObject*)0,"p1 = 4.73e-05 #pm 3.06e-05","");
fitres->Draw();

char cname_1[1024], cname_2[1024];
sprintf(cname_1,"Run3_vs_Run2_13p4fb-1_FourjetMass.png");
sprintf(cname_2,"Run3_vs_Run2_13p4fb-1_FourjetMass.pdf");
//sprintf(cname_1,"Run3_vs_Run2_scaled_to_lumi_FourjetMass.png");
//sprintf(cname_2,"Run3_vs_Run2_scaled_to_lumi_FourjetMass.pdf");

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
