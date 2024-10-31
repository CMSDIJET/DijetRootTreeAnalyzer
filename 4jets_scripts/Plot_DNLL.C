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

void Plot_DNLL(double width, int Suu, int Chi){

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

//auto frame = c->DrawFrame(-0.06,1158325.,0.28,1158360.);
//auto frame = c->DrawFrame(-0.06,1158285.,0.28,1158330.);
//auto frame = c->DrawFrame(-0.06,1158284.,0.28,1158320.);
//auto frame = c->DrawFrame(-0.06,1158280.,0.28,1158315.);
//auto frame = c->DrawFrame(-0.5,1158328.,2.5,1158360.);
//auto frame = c->DrawFrame(-0.5,1158288.,2.5,1158345.);
//auto frame = c->DrawFrame(-0.5,1158286.,2.5,1158320.);
//auto frame = c->DrawFrame(-0.5,1158282.,2.5,1158318.);
auto frame = c->DrawFrame(-0.0005,1158282.,0.0082,1158304.);
frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitleOffset(0.93);
frame->GetXaxis()->SetTitle("r #times 10^{-2} [pb]");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(1.8);
frame->GetYaxis()->SetTitle("2#times(deltaNLL+nll0+nll)");

char fname0[1024], fname1[1024], fname2[1024], fname3[1024];
sprintf(fname0,"output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/dnlls/higgsCombine_envelope_W-%s_%d_%d.MultiDimFit.mH120.root",width_name,Suu,Chi);
sprintf(fname1,"output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/dnlls/higgsCombine_dijet_W-%s_%d_%d.MultiDimFit.mH120.root",width_name,Suu,Chi);
sprintf(fname2,"output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/dnlls/higgsCombine_atlas_W-%s_%d_%d.MultiDimFit.mH120.root",width_name,Suu,Chi);
sprintf(fname3,"output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/dnlls/higgsCombine_moddijet_W-%s_%d_%d.MultiDimFit.mH120.root",width_name,Suu,Chi);

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
t0->SetMarkerSize(0.8);
t0->SetLineColor(kBlack);
t0->SetLineWidth(2);

t1->SetMarkerColor(kBlue-3);
t1->SetMarkerStyle(20);
t1->SetMarkerSize(1.);
t1->SetLineColor(kBlue-3);
t1->SetLineWidth(2);

t2->SetMarkerColor(kRed+1);
t2->SetMarkerStyle(20);
t2->SetMarkerSize(1.);
t2->SetLineColor(kRed+1);
t2->SetLineWidth(2);

t3->SetMarkerColor(kGreen+1);
t3->SetMarkerStyle(20);
t3->SetMarkerSize(1.);
t3->SetLineColor(kGreen+1);
t3->SetLineWidth(2);

t1->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.000008 && r<0.007992", "same");
t2->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.000008 && r<0.007992", "same");
t3->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.000008 && r<0.007992", "same");
t0->Draw("(2*(deltaNLL+nll0+nll)):r","r>-0.000008 && r<0.007992", "same");


char siglegname1[1024];

if(width==0.0043)
{
	sprintf(siglegname1,"M_{S} = %.1f TeV, M_{#chi} = %.2f TeV, #Gamma / M_{S} = %.2f %%",Suu/1000.,Chi/1000., width*100.);
}
else if(width==0.015)
{
	sprintf(siglegname1,"M_{S} = %.1f TeV, M_{#chi} = %.2f TeV, #Gamma / M_{S} = %.1f %%",Suu/1000.,Chi/1000.,width*100.);
}
else
{
	sprintf(siglegname1,"M_{S} = %.1f TeV, M_{#chi} = %.2f TeV, #Gamma / M_{S} = %.0f %%",Suu/1000.,Chi/1000.,width*100.);
}

TPaveText *sigleg = new TPaveText(0.48,0.95,0.78,0.95,"NDC");
sigleg->SetFillColor(0);
sigleg->SetBorderSize(0);
sigleg->AddText(siglegname1);
sigleg->SetTextFont(42);
sigleg->SetTextSize(0.036);
sigleg->Draw();


TLegend *leg = new TLegend(0.4,0.67,0.6,0.87,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->AddEntry(t0,"Envelope","P");
leg->AddEntry(t1,"Dijet-3p","P");
leg->AddEntry(t2,"PowExp-3p","P");
leg->AddEntry(t3,"ModDijet-3p","P");
leg->Draw();


TPaveText *leg2 = new TPaveText(0.61,0.11,0.81,0.21,"NDC");
leg2->SetBorderSize(0);
leg2->SetFillStyle(0);
leg2->SetTextFont(42);
leg2->SetTextSize(0.04);
leg2->AddText("CMS + ATLAS pseudo-dataset");
//leg2->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/highest_signif_mass_points/DNLL_3func_envelope_W-%s_S-%d_chi-%d.png",width_name,Suu,Chi);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/highest_signif_mass_points/DNLL_3func_envelope_W-%s_S-%d_chi-%d.pdf",width_name,Suu,Chi);

c->SaveAs(cname1);
c->SaveAs(cname2);


}
