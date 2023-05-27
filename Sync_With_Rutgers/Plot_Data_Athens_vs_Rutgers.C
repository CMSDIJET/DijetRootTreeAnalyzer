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

void Plot_Data_Athens_vs_Rutgers(char era[1024], char var[1024]){

char xaxistitle[1024];

double xmin, xmax;

if(strcmp(var,"FourjetMass")==0) {sprintf(xaxistitle,"Four-jet mass [GeV]"); xmin = 1607; xmax = 7060;}
if(strcmp(var,"DijetMass")==0) {sprintf(xaxistitle,"Average dijet mass [GeV]"); xmin = 1; xmax = 2546;}

TPaveText *cms = new TPaveText(0.17,0.95,0.32,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname1[1024], fname2[1024];
sprintf(fname1,"Histos_4jets_2022Data_Athens.root");
sprintf(fname2,"Histos_4jets_2022Data_Rutgers.root");

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");

TH1D *h1c, *h1d, *h1e, *h1f, *h1g, *h1, *h2;

char hname1[1024], hname2[1024];

if(strcmp(var,"FourjetMass")==0)
{
	if(strcmp(era,"CDEFG")==0)
	{
		h1c = (TH1D*)f1->Get("h_FourjetMass_eraC");
		h1d = (TH1D*)f1->Get("h_FourjetMass_eraD");
		h1e = (TH1D*)f1->Get("h_FourjetMass_eraE");
		h1f = (TH1D*)f1->Get("h_FourjetMass_eraF");
		h1g = (TH1D*)f1->Get("h_FourjetMass_eraG");
		h1 = (TH1D*)h1c->Clone();
		h1->Add(h1d);
		h1->Add(h1e);
		h1->Add(h1f);
		h1->Add(h1g);
		h2 = (TH1D*)f2->Get("4JetMass_eraAll");
	}
	else
	{
		sprintf(hname1,"h_FourjetMass_era%s",era);
		sprintf(hname2,"4JetMass_era%s",era);
		h1 = (TH1D*)f1->Get(hname1);
		h2 = (TH1D*)f2->Get(hname2);
	}
}

if(strcmp(var,"DijetMass")==0)
{
	if(strcmp(era,"CDEFG")==0)
	{
		h1c = (TH1D*)f1->Get("h_AverageDijetMass_eraC");
		h1d = (TH1D*)f1->Get("h_AverageDijetMass_eraD");
		h1e = (TH1D*)f1->Get("h_AverageDijetMass_eraE");
		h1f = (TH1D*)f1->Get("h_AverageDijetMass_eraF");
		h1g = (TH1D*)f1->Get("h_AverageDijetMass_eraG");
		h1 = (TH1D*)h1c->Clone();
		h1->Add(h1d);
		h1->Add(h1e);
		h1->Add(h1f);
		h1->Add(h1g);
		h2 = (TH1D*)f2->Get("DijetMass_eraAll");
	}
	else
	{
		sprintf(hname1,"h_AverageDijetMass_era%s",era);
		sprintf(hname2,"DijetMass_era%s",era);
		h1 = (TH1D*)f1->Get(hname1);
		h2 = (TH1D*)f2->Get(hname2);
	}
}

for(int i=1; i<=h1->GetNbinsX(); i++)
{
	if(h1->GetBinContent(i)==0) h1->SetBinContent(i,0.00001);
	if(h2->GetBinContent(i)==0) h2->SetBinContent(i,0.00001);	
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
h1->GetYaxis()->SetTitle("Entries");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetMarkerColor(kBlack);
h1->SetMarkerStyle(8);
h1->SetMarkerSize(0.8);
h1->SetLineColor(kBlack);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
h1->SetMinimum(0.5);
//h1->SetMaximum(100);

h2->SetLineColor(kBlue);
h2->SetLineWidth(3);

h1->Draw("PE1");
h2->Draw("hist same");
h1->Draw("PE1 same");

char legname[1024];
if(strcmp(era,"CDEFG")==0)
{
	sprintf(legname,"All eras");
}
else
{
	sprintf(legname,"era %s",era);
}

char Athens_evts[1024], Rutgers_evts[1024];
sprintf(Athens_evts,"#splitline{Athens}{%.0f events}",h1->Integral());
sprintf(Rutgers_evts,"#splitline{Rutgers}{%.0f events}",h2->Integral());

TLegend *leg = new TLegend(0.65,0.5,0.8,0.9,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->SetHeader(legname);
leg->AddEntry(h1,Athens_evts,"PE");
leg->AddEntry(h2,Rutgers_evts,"L");
leg->Draw();


cms->Draw();

TPaveText *lumileg = new TPaveText(0.71,0.95,0.90,0.99,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);
if(strcmp(era,"CDEFG")==0) lumileg->AddText("34.6 fb^{-1} (13.6 TeV)");
if(strcmp(era,"C")==0) lumileg->AddText("5.1 fb^{-1} (13.6 TeV)");
if(strcmp(era,"D")==0) lumileg->AddText("2.9 fb^{-1} (13.6 TeV)");
if(strcmp(era,"E")==0) lumileg->AddText("5.8 fb^{-1} (13.6 TeV)");
if(strcmp(era,"F")==0) lumileg->AddText("17.7 fb^{-1} (13.6 TeV)");
if(strcmp(era,"G")==0) lumileg->AddText("3.1 fb^{-1} (13.6 TeV)");
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

TH1D *h_ratio = (TH1D*)h1->Clone();
h_ratio->Divide(h2);

h_ratio->SetStats(0);
h_ratio->SetMarkerStyle(8);
h_ratio->SetMarkerColor(kBlack);
h_ratio->SetLineColor(kBlack);
h_ratio->SetMarkerSize(0.8);
h_ratio->GetXaxis()->SetRangeUser(xmin, xmax);
h_ratio->GetYaxis()->SetRangeUser(0.961, 1.039);
h_ratio->GetYaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelOffset(0.03);
h_ratio->GetXaxis()->SetTitle(xaxistitle);
h_ratio->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio->GetYaxis()->SetTitle("Athens / Rutgers");
h_ratio->GetYaxis()->CenterTitle(1);
h_ratio->GetYaxis()->SetTitleSize(0.1);
h_ratio->GetYaxis()->SetTitleOffset(0.55);
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
sprintf(cname_1,"AllCuts_era%s_Athens_VS_Rutgers_%s.png",era,var);
sprintf(cname_2,"AllCuts_era%s_Athens_VS_Rutgers_%s.pdf",era,var);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
