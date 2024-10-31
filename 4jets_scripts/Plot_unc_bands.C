#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TH1.h"

void Plot_unc_bands(){


TFile *f1 = new TFile("output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/limits/xsecUL_HybridNew_qq_alpha0p25_W-0p0043_PFDijetRun2.root","read");
TFile *f2 = new TFile("output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/limits/xsecUL_HybridNew_qq_alpha0p25_W-0p015_PFDijetRun2.root","read");
TFile *f3 = new TFile("output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/limits/xsecUL_HybridNew_qq_alpha0p25_W-0p05_PFDijetRun2.root","read");
TFile *f4 = new TFile("output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/limits/xsecUL_HybridNew_qq_alpha0p25_W-0p1_PFDijetRun2.root","read");

TTree *t1 = (TTree*)f1->Get("xsecTree");
TTree *t2 = (TTree*)f2->Get("xsecTree");
TTree *t3 = (TTree*)f3->Get("xsecTree");
TTree *t4 = (TTree*)f4->Get("xsecTree");

double mass_1, obs_1, exp_plus_2sigma_1, exp_plus_1sigma_1, exp_1, exp_minus_1sigma_1, exp_minus_2sigma_1;
double mass_2, obs_2, exp_plus_2sigma_2, exp_plus_1sigma_2, exp_2, exp_minus_1sigma_2, exp_minus_2sigma_2;
double mass_3, obs_3, exp_plus_2sigma_3, exp_plus_1sigma_3, exp_3, exp_minus_1sigma_3, exp_minus_2sigma_3;
double mass_4, obs_4, exp_plus_2sigma_4, exp_plus_1sigma_4, exp_4, exp_minus_1sigma_4, exp_minus_2sigma_4;

t1->SetBranchAddress("mass",&mass_1);
t1->SetBranchAddress("xsecULObs_PFDijetRun2",&obs_1);
t1->SetBranchAddress("xsecULExpPlus2_PFDijetRun2",&exp_plus_2sigma_1);	
t1->SetBranchAddress("xsecULExpPlus_PFDijetRun2",&exp_plus_1sigma_1);
t1->SetBranchAddress("xsecULExp_PFDijetRun2",&exp_1);
t1->SetBranchAddress("xsecULExpMinus_PFDijetRun2",&exp_minus_1sigma_1);
t1->SetBranchAddress("xsecULExpMinus2_PFDijetRun2",&exp_minus_2sigma_1);

t2->SetBranchAddress("mass",&mass_2);
t2->SetBranchAddress("xsecULObs_PFDijetRun2",&obs_2);
t2->SetBranchAddress("xsecULExpPlus2_PFDijetRun2",&exp_plus_2sigma_2);	
t2->SetBranchAddress("xsecULExpPlus_PFDijetRun2",&exp_plus_1sigma_2);
t2->SetBranchAddress("xsecULExp_PFDijetRun2",&exp_2);
t2->SetBranchAddress("xsecULExpMinus_PFDijetRun2",&exp_minus_1sigma_2);
t2->SetBranchAddress("xsecULExpMinus2_PFDijetRun2",&exp_minus_2sigma_2);

t3->SetBranchAddress("mass",&mass_3);
t3->SetBranchAddress("xsecULObs_PFDijetRun2",&obs_3);
t3->SetBranchAddress("xsecULExpPlus2_PFDijetRun2",&exp_plus_2sigma_3);	
t3->SetBranchAddress("xsecULExpPlus_PFDijetRun2",&exp_plus_1sigma_3);
t3->SetBranchAddress("xsecULExp_PFDijetRun2",&exp_3);
t3->SetBranchAddress("xsecULExpMinus_PFDijetRun2",&exp_minus_1sigma_3);
t3->SetBranchAddress("xsecULExpMinus2_PFDijetRun2",&exp_minus_2sigma_3);

t4->SetBranchAddress("mass",&mass_4);
t4->SetBranchAddress("xsecULObs_PFDijetRun2",&obs_4);
t4->SetBranchAddress("xsecULExpPlus2_PFDijetRun2",&exp_plus_2sigma_4);	
t4->SetBranchAddress("xsecULExpPlus_PFDijetRun2",&exp_plus_1sigma_4);
t4->SetBranchAddress("xsecULExp_PFDijetRun2",&exp_4);
t4->SetBranchAddress("xsecULExpMinus_PFDijetRun2",&exp_minus_1sigma_4);
t4->SetBranchAddress("xsecULExpMinus2_PFDijetRun2",&exp_minus_2sigma_4);

Int_t nentries1 = (Int_t)t1->GetEntries();

TGraph *g1 = new TGraph(nentries1);

for (int i=0; i<nentries1; i++)
{ 
    t1->GetEntry(i);

    g1->SetPoint(i, mass_1/1000., (1.*(exp_plus_1sigma_1-exp_1))/exp_1);  
	
}// end of event loop

Int_t nentries2 = (Int_t)t2->GetEntries();

TGraph *g2 = new TGraph(nentries2);

for (int i=0; i<nentries2; i++)
{ 
    t2->GetEntry(i);

    g2->SetPoint(i, mass_2/1000., (1.*(exp_plus_1sigma_2-exp_2))/exp_2);  
	
}// end of event loop



Int_t nentries3 = (Int_t)t3->GetEntries();

TGraph *g3 = new TGraph(nentries3);

for (int i=0; i<nentries3; i++)
{ 
    t3->GetEntry(i);

    g3->SetPoint(i, mass_3/1000., (1.*(exp_plus_1sigma_3-exp_3))/exp_3);  
	
}// end of event loop


Int_t nentries4 = (Int_t)t4->GetEntries();

TGraph *g4 = new TGraph(nentries4);

for (int i=0; i<nentries4; i++)
{ 
    t4->GetEntry(i);

    g4->SetPoint(i, mass_4/1000., (1.*(exp_plus_1sigma_4-exp_4))/exp_4);  
	
}// end of event loop


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
//c->SetGridy(1);
c->SetRightMargin(0.03);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.14);
c->SetBottomMargin(0.12);

auto frame = c->DrawFrame(1.5,0,10.5,0.89);
frame->GetXaxis()->SetTitleSize(0.07);
frame->GetXaxis()->SetTitleOffset(0.8);
frame->GetXaxis()->SetTitle("Four-jet resonance mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.15);
frame->GetYaxis()->SetTitle("(1#sigma error) / exp. limit");
frame->GetYaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelOffset(0.015);

g1->SetLineColor(kBlack);
g2->SetLineColor(kRed+1);
g3->SetLineColor(kBlue-3);
g4->SetLineColor(kGreen+2);

g1->SetLineWidth(2);
g2->SetLineWidth(2);
g3->SetLineWidth(2);
g4->SetLineWidth(2);

//TLegend *leg = new TLegend(0.2,0.17,0.4,0.47);
TLegend *leg = new TLegend(0.2,0.65,0.4,0.87);
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->SetHeader("Y #rightarrow XX #rightarrow (jj)(jj)");
leg->AddEntry(g1, "#Gamma / M_{Y} = 0.43%", "L");
leg->AddEntry(g2, "#Gamma / M_{Y} = 1.5%", "L");
leg->AddEntry(g3, "#Gamma / M_{Y} = 5%", "L");
leg->AddEntry(g4, "#Gamma / M_{Y} = 10%", "L");
leg->Draw();

g1->Draw("C same");
g2->Draw("C same");
g3->Draw("C same");
g4->Draw("C same");

c->SaveAs("output/Wide_Resonances_Run2_Final/plots/limits/1sigmaErrorOverExpLimit_vsWidth.png");
c->SaveAs("output/Wide_Resonances_Run2_Final/plots/limits/1sigmaErrorOverExpLimit_vsWidth.pdf");

}
