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
#include "TGraph2D.h"

void Plot_DNLL_forSupplementary_highmass(double width, double alpha_true, double Suu){

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char alpha_true_name[1024];
if (alpha_true==0.11) sprintf(alpha_true_name,"0p11");
if (alpha_true==0.13) sprintf(alpha_true_name,"0p13");
if (alpha_true==0.15) sprintf(alpha_true_name,"0p15");
if (alpha_true==0.17) sprintf(alpha_true_name,"0p17");
if (alpha_true==0.19) sprintf(alpha_true_name,"0p19");
if (alpha_true==0.21) sprintf(alpha_true_name,"0p21");
if (alpha_true==0.23) sprintf(alpha_true_name,"0p23");
if (alpha_true==0.25) sprintf(alpha_true_name,"0p25");
if (alpha_true==0.27) sprintf(alpha_true_name,"0p27");
if (alpha_true==0.29) sprintf(alpha_true_name,"0p29");
if (alpha_true==0.31) sprintf(alpha_true_name,"0p31");
if (alpha_true==0.33) sprintf(alpha_true_name,"0p33");
if (alpha_true==0.42) sprintf(alpha_true_name,"0p42");

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.04);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.18);
c->SetBottomMargin(0.14);


auto frame = c->DrawFrame(-0.0003,1158281.,0.0088,1158308.);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.93);
frame->GetXaxis()->SetTitle("Signal strength r [10^{-2} pb]");
frame->GetYaxis()->SetTitleSize(0.06);
frame->GetYaxis()->SetTitleOffset(1.55);
frame->GetYaxis()->SetTitle("-2lnL");
frame->GetYaxis()->SetMaxDigits(7);

char fname0[1024], fname1[1024], fname2[1024], fname3[1024];

sprintf(fname0,"files/higgsCombine_envelope_W-%s_%.0f_%.0f.MultiDimFit.mH120.root", width_name, Suu, Suu*alpha_true);
sprintf(fname1,"files/higgsCombine_dijet_W-%s_%.0f_%.0f.MultiDimFit.mH120.root", width_name, Suu, Suu*alpha_true);
sprintf(fname2,"files/higgsCombine_atlas_W-%s_%.0f_%.0f.MultiDimFit.mH120.root", width_name, Suu, Suu*alpha_true);
sprintf(fname3,"files/higgsCombine_moddijet_W-%s_%.0f_%.0f.MultiDimFit.mH120.root", width_name, Suu, Suu*alpha_true);

TFile *f0 = new TFile(fname0,"READ");
TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");
TFile *f3 = new TFile(fname3,"READ");

TTree *t0 = (TTree*)f0->Get("limit");
TTree *t1 = (TTree*)f1->Get("limit");
TTree *t2 = (TTree*)f2->Get("limit");
TTree *t3 = (TTree*)f3->Get("limit");

t0->SetMarkerColor(kBlack);
t0->SetMarkerStyle(20);
t0->SetMarkerSize(0.7);
t0->SetLineColor(kBlack);
t0->SetLineWidth(3);

t1->SetMarkerColor(kBlue-3);
t1->SetMarkerStyle(20);
t1->SetMarkerSize(0.7);
t1->SetLineColor(kBlue-3);
t1->SetLineWidth(3);

t2->SetMarkerColor(kRed+1);
t2->SetMarkerStyle(20);
t2->SetMarkerSize(0.7);
t2->SetLineColor(kRed+1);
t2->SetLineWidth(3);

t3->SetMarkerColor(kGreen+2);
t3->SetMarkerStyle(20);
t3->SetMarkerSize(0.7);
t3->SetLineColor(kGreen+2);
t3->SetLineWidth(3);



TGraph *g1 = new TGraph();
TGraph *g2 = new TGraph();
TGraph *g3 = new TGraph();
TGraph *g0 = new TGraph();

float r, dnll;
double nll0, nll;
int i = 0;

t1->SetBranchAddress("r", &r);
t1->SetBranchAddress("deltaNLL", &dnll);
t1->SetBranchAddress("nll0", &nll0);
t1->SetBranchAddress("nll", &nll);
i = 0;
while (t1->GetEntry(i++)) g1->SetPoint(i-1, r, 2*(dnll + nll0 + nll));

i = 0;
t2->SetBranchAddress("r", &r);
t2->SetBranchAddress("deltaNLL", &dnll);
t2->SetBranchAddress("nll0", &nll0);
t2->SetBranchAddress("nll", &nll);
while (t2->GetEntry(i++)) g2->SetPoint(i-1, r, 2*(dnll + nll0 + nll));

i = 0;
t3->SetBranchAddress("r", &r);
t3->SetBranchAddress("deltaNLL", &dnll);
t3->SetBranchAddress("nll0", &nll0);
t3->SetBranchAddress("nll", &nll);
while (t3->GetEntry(i++)) g3->SetPoint(i-1, r, 2*(dnll + nll0 + nll));

i = 0;
t0->SetBranchAddress("r", &r);
t0->SetBranchAddress("deltaNLL", &dnll);
t0->SetBranchAddress("nll0", &nll0);
t0->SetBranchAddress("nll", &nll);
while (t0->GetEntry(i++)) g0->SetPoint(i-1, r, 2*(dnll + nll0 + nll));

g1->Sort();
g2->Sort();
g3->Sort();
g0->Sort();

g1->SetMarkerColor(kBlue-3);
g1->SetMarkerStyle(20);
g1->SetMarkerSize(0.7);
g1->SetLineColor(kBlue-3);
g1->SetLineWidth(5);
g1->Draw("LP same");

g2->SetMarkerColor(kRed+1);
g2->SetMarkerStyle(20);
g2->SetMarkerSize(0.7);
g2->SetLineColor(kRed+1);
g2->SetLineWidth(5);
g2->Draw("LP same");

g3->SetMarkerColor(kGreen+2);
g3->SetMarkerStyle(20);
g3->SetMarkerSize(0.7);
g3->SetLineColor(kGreen+2);
g3->SetLineWidth(5);
g3->Draw("LP same");

g0->SetMarkerColor(kBlack);
g0->SetMarkerStyle(20);
g0->SetMarkerSize(0.4);
g0->SetLineColor(kBlack);
g0->SetLineWidth(2);
g0->Draw("LP same");


char siglegname1[1024], siglegname2[1024];

sprintf(siglegname1,"M_{S} = %.1f TeV, M_{#chi} = %.2f TeV", Suu/1000., (Suu*alpha_true)/1000.);

if(width==0.0043)
{
	sprintf(siglegname2,"#Gamma / M_{S} = %.2f%%", width*100.);
}
else if(width==0.015)
{
	sprintf(siglegname2,"#Gamma / M_{S} = %.1f%%", width*100.);
}
else
{
	sprintf(siglegname2,"#Gamma / M_{S} = %.0f%%", width*100.);
}



TPaveText *sigleg = new TPaveText(0.22,0.72,0.42,0.87,"NDC");
sigleg->SetFillColor(0);
sigleg->SetBorderSize(0);
sigleg->AddText("uu #rightarrow S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)");
sigleg->AddText(siglegname1);
sigleg->AddText(siglegname2);
sigleg->SetTextFont(42);
sigleg->SetTextSize(0.035);
sigleg->SetTextAlign(11);
sigleg->Draw();


TLegend *leg = new TLegend(0.69,0.17,0.89,0.37,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.035);
leg->AddEntry(t0,"Envelope","LP");
leg->AddEntry(t1,"Dijet-3p fit","LP");
leg->AddEntry(t2,"PowExp-3p fit","LP");
leg->AddEntry(t3,"ModDijet-3p fit","LP");
leg->Draw();


//TPaveText *paveCMS = new TPaveText(0.25,0.78,0.35,0.86,"NDC");
TPaveText *paveCMS = new TPaveText(0.27,0.93,0.37,0.96,"NDC");
//paveCMS->AddText("#splitline{#bf{CMS}}{#scale[0.7]{#it{Preliminary}}}");
paveCMS->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
paveCMS->SetTextFont(42); 
paveCMS->SetFillColor(0);
paveCMS->SetBorderSize(0);
paveCMS->SetTextSize(0.06);
paveCMS->Draw();

TPaveText *paveCMS2 = new TPaveText(0.765,0.93,0.865,0.96,"NDC");
paveCMS2->SetTextFont(42);
paveCMS2->AddText("138 fb^{-1} (13 TeV)");
paveCMS2->SetFillColor(0);
paveCMS2->SetBorderSize(0);
paveCMS2->SetTextSize(0.05);
paveCMS2->Draw();


char cname1[1024], cname2[1024];
sprintf(cname1,"plots/DNLL_W-%s_S-%.0f_chi-%.0f.png", width_name, Suu, Suu*alpha_true);
sprintf(cname2,"plots/DNLL_W-%s_S-%.0f_chi-%.0f.pdf", width_name, Suu, Suu*alpha_true);

//c->SaveAs(cname1);
c->SaveAs(cname2);


}
