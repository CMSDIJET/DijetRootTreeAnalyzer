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

void Plot_DNLL_vsWidth(int Suu, int Chi){


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.04);
c->SetTopMargin(0.07);
c->SetLeftMargin(0.18);

auto frame = c->DrawFrame(-0.05,2319824.,0.65,2319845.);
frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitleOffset(0.93);
frame->GetXaxis()->SetTitle("r #times 10^{-4} [pb]");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(1.8);
frame->GetYaxis()->SetTitle("2#times(deltaNLL+nll0+nll)");

char fname0[1024], fname1[1024], fname2[1024], fname3[1024], fname4[1024];
sprintf(fname0,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/combine_rootfiles/MultiDimFit/higgsCombine_CMSplusATLASpseudodataset_W-0p0043_%d_%d_Envelope.MultiDimFit.mH120.root",Suu,Chi);
sprintf(fname1,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/combine_rootfiles/MultiDimFit/higgsCombine_CMSplusATLASpseudodataset_W-0p015_%d_%d_Envelope.MultiDimFit.mH120.root",Suu,Chi);
sprintf(fname2,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/combine_rootfiles/MultiDimFit/higgsCombine_CMSplusATLASpseudodataset_W-0p05_%d_%d_Envelope.MultiDimFit.mH120.root",Suu,Chi);
sprintf(fname3,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/combine_rootfiles/MultiDimFit/higgsCombine_CMSplusATLASpseudodataset_W-0p07_%d_%d_Envelope.MultiDimFit.mH120.root",Suu,Chi);
sprintf(fname4,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/combine_rootfiles/MultiDimFit/higgsCombine_CMSplusATLASpseudodataset_W-0p1_%d_%d_Envelope.MultiDimFit.mH120.root",Suu,Chi);

TFile *f0 = new TFile(fname0,"READ");
TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");
TFile *f3 = new TFile(fname3,"READ");
TFile *f4 = new TFile(fname3,"READ");

TTree *t0 = (TTree*)f0->Get("limit");
TTree *t1 = (TTree*)f1->Get("limit");
TTree *t2 = (TTree*)f2->Get("limit");
TTree *t3 = (TTree*)f3->Get("limit");
TTree *t4 = (TTree*)f4->Get("limit");

t0->SetMarkerColor(kBlack);
t0->SetMarkerStyle(20);
t0->SetMarkerSize(0.6);
t0->SetLineColor(kBlack);
t0->SetLineWidth(2);

t1->SetMarkerColor(kRed+1);
t1->SetMarkerStyle(20);
t1->SetMarkerSize(0.6);
t1->SetLineColor(kRed+1);
t1->SetLineWidth(2);

t2->SetMarkerColor(kBlue-3);
t2->SetMarkerStyle(20);
t2->SetMarkerSize(0.6);
t2->SetLineColor(kBlue-3);
t2->SetLineWidth(2);

t3->SetMarkerColor(kOrange+1);
t3->SetMarkerStyle(20);
t3->SetMarkerSize(0.8);
t3->SetLineColor(kOrange+1);
t3->SetLineWidth(2);

t4->SetMarkerColor(kViolet);
t4->SetMarkerStyle(20);
t4->SetMarkerSize(0.6);
t4->SetLineColor(kViolet);
t4->SetLineWidth(2);

t0->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.0006 && r<0.5994", "same");
t1->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.0006 && r<0.5994", "same");
t2->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.0006 && r<0.5994", "same");
t3->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.0006 && r<0.5994", "same");
t4->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.0006 && r<0.5994", "same");

char siglegname1[1024];
sprintf(siglegname1,"M(S) = %.2f TeV, M(#chi) = %.2f TeV",Suu/1000.,Chi/1000.);


TPaveText *sigleg = new TPaveText(0.59,0.95,0.89,0.95,"NDC");
sigleg->SetFillColor(0);
sigleg->SetBorderSize(0);
sigleg->AddText(siglegname1);
sigleg->SetTextFont(42);
sigleg->SetTextSize(0.036);
sigleg->Draw();

t0->SetMarkerSize(1.1);
t1->SetMarkerSize(1.1);
t2->SetMarkerSize(1.1);
t3->SetMarkerSize(1.1);
t4->SetMarkerSize(1.1);

TLegend *leg = new TLegend(0.4,0.67,0.6,0.87,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->SetHeader("Envelope");
leg->AddEntry(t0,"#Gamma/M = 0.43 %","P");
leg->AddEntry(t1,"#Gamma/M = 1.5 %","P");
leg->AddEntry(t2,"#Gamma/M = 5 %","P");
leg->AddEntry(t3,"#Gamma/M = 7 %","P");
leg->AddEntry(t4,"#Gamma/M = 10 %","P");
leg->Draw();

TPaveText *leg2 = new TPaveText(0.61,0.11,0.81,0.21,"NDC");
//TPaveText *leg2 = new TPaveText(0.35,0.58,0.55,0.68,"NDC");
leg2->SetBorderSize(0);
leg2->SetFillStyle(0);
leg2->SetTextFont(42);
leg2->SetTextSize(0.04);
leg2->AddText("CMS + ATLAS pseudo-dataset");
leg2->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/plots/DNLL_envelope_vsWidth_CMSplusATLASpseudodataset_S-%d_chi-%d.png",Suu,Chi);
sprintf(cname2,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/plots/DNLL_envelope_vsWidth_CMSplusATLASpseudodataset_S-%d_chi-%d.pdf",Suu,Chi);

c->SaveAs(cname1);
c->SaveAs(cname2);


}
