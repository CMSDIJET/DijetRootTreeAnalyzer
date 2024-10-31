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

void Plot_DNLL_HiggsCombine_versions(double width, int Suu, int Chi){

// Set style to avoid scientific notation
gStyle->SetOptStat(0);  // Disable statistics box
gStyle->SetHistMinimumZero(kFALSE);  // Ensure axis labels show full numbers
gStyle->SetPaintTextFormat("g"); // Set format to show full numbers

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.07) sprintf(width_name,"0p07");
if (width==0.1) sprintf(width_name,"0p1");

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.04);
c->SetTopMargin(0.07);
c->SetLeftMargin(0.18);

auto frame = c->DrawFrame(-0.001,0,0.008,20.);
frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitleOffset(0.93);
frame->GetXaxis()->SetTitle("r [10^{-2} pb]");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(1.8);
//frame->GetYaxis()->SetTitle("2(deltaNLL+nll0+nll)");
//frame->GetYaxis()->SetTitle("2(nll0+nll)");
frame->GetYaxis()->SetTitle("2(deltaNLL)");

frame->GetYaxis()->SetNoExponent(kTRUE);
frame->GetYaxis()->SetMoreLogLabels(kTRUE);

char fname0[1024], fname1[1024], fname2[1024], fname3[1024];
sprintf(fname0,"higgsCombine_envelope_W-%s_%d_%d_V8.MultiDimFit.mH120.root",width_name,Suu,Chi);
sprintf(fname1,"higgsCombine_envelope_W-%s_%d_%d_V10.MultiDimFit.mH120.root",width_name,Suu,Chi);

TFile *f0 = new TFile(fname0,"READ");
TFile *f1 = new TFile(fname1,"READ");

TTree *t0 = (TTree*)f0->Get("limit");
TTree *t1 = (TTree*)f1->Get("limit");

t0->SetMarkerColor(kBlack);
t0->SetMarkerStyle(8);
t0->SetMarkerSize(1.);
t0->SetLineColor(kRed);
t0->SetLineWidth(2);

t1->SetMarkerColor(kBlue-3);
t1->SetMarkerStyle(8);
t1->SetMarkerSize(0.8);
t1->SetLineColor(kBlue);
t1->SetLineWidth(2);


//t0->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.0001 && r<0.008", "same");
//t1->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.0001 && r<0.008", "same");

//t0->Draw("(2*(nll0+nll)):r","r>-0.0001 && r<0.008", "same");
//t1->Draw("(2*(nll0+nll)):r","r>-0.0001 && r<0.008", "same");

t0->Draw("(2*(deltaNLL)):r","r>-0.0001 && r<0.008", "same");
t1->Draw("(2*(deltaNLL)):r","r>-0.0001 && r<0.008", "same");

char siglegname1[1024];

if(width==0.0043)
{
	sprintf(siglegname1,"M_{S} = %.2f TeV, M_{#chi} = %.2f TeV, #Gamma / M_{S} = %.2f %%",Suu/1000.,Chi/1000.,width*100.);
}
else if(width==0.015)
{
	sprintf(siglegname1,"M(S) = %.2f TeV, M(#chi) = %.2f TeV, Width = %.1f %%",Suu/1000.,Chi/1000.,width*100.);
}
else
{
	sprintf(siglegname1,"M(S) = %.2f TeV, M(#chi) = %.2f TeV, Width = %.0f %%",Suu/1000.,Chi/1000.,width*100.);
}

TPaveText *sigleg = new TPaveText(0.48,0.95,0.78,0.95,"NDC");
sigleg->SetFillColor(0);
sigleg->SetBorderSize(0);
sigleg->AddText(siglegname1);
sigleg->SetTextFont(42);
sigleg->SetTextSize(0.036);
sigleg->Draw();


TLegend *leg = new TLegend(0.4,0.47,0.6,0.67,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->AddEntry(t0,"HiggsCombine v8","P");
leg->AddEntry(t1,"HiggsCombine v10","P");
leg->Draw();


TPaveText *leg2 = new TPaveText(0.61,0.11,0.81,0.21,"NDC");
leg2->SetBorderSize(0);
leg2->SetFillStyle(0);
leg2->SetTextFont(42);
leg2->SetTextSize(0.04);
leg2->AddText("CMS + ATLAS pseudo-dataset");
//leg2->Draw();

char cname1[1024], cname2[1024];
//sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/higgs_combine_version_comparisons/DNLLplusNLL0plusNLL_V10vsV8_3func_envelope_W-%s_S-%d_chi-%d.png",width_name,Suu,Chi);
//sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/higgs_combine_version_comparisons/DNLLplusNLL0plusNLL_V10vsV8_3func_envelope_W-%s_S-%d_chi-%d.pdf",width_name,Suu,Chi);

//sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/higgs_combine_version_comparisons/NLL0plusNLL_V10vsV8_3func_envelope_W-%s_S-%d_chi-%d.png",width_name,Suu,Chi);
//sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/higgs_combine_version_comparisons/NLL0plusNLL_V10vsV8_3func_envelope_W-%s_S-%d_chi-%d.pdf",width_name,Suu,Chi);

sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/higgs_combine_version_comparisons/DNLL_V10vsV8_3func_envelope_W-%s_S-%d_chi-%d.png",width_name,Suu,Chi);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/higgs_combine_version_comparisons/DNLL_V10vsV8_3func_envelope_W-%s_S-%d_chi-%d.pdf",width_name,Suu,Chi);

c->SaveAs(cname1);
c->SaveAs(cname2);


}
