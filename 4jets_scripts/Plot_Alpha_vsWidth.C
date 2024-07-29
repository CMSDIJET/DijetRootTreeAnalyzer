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

void Plot_Alpha_vsWidth(double alpha_true, double Suu){

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



char fname1[1024], fname2[1024], fname3[1024], fname4[1024];

sprintf(fname1, "signal_histos_Alpha/AlphaShapes_Suu-Diquark_W-0p0043_S-%.0f_chi-%.0f.root", Suu, Suu*alpha_true);
sprintf(fname2, "signal_histos_Alpha/AlphaShapes_Suu-Diquark_W-0p015_S-%.0f_chi-%.0f.root", Suu, Suu*alpha_true);
sprintf(fname3, "signal_histos_Alpha/AlphaShapes_Suu-Diquark_W-0p05_S-%.0f_chi-%.0f.root", Suu, Suu*alpha_true);
sprintf(fname4, "signal_histos_Alpha/AlphaShapes_Suu-Diquark_W-0p1_S-%.0f_chi-%.0f.root", Suu, Suu*alpha_true);


TFile *f1 = new TFile(fname1,"read");
TFile *f2 = new TFile(fname2,"read");
TFile *f3 = new TFile(fname3,"read");
TFile *f4 = new TFile(fname4,"read");

cout << "File 1: " << fname1 << endl;
cout << "File 2: " << fname2 << endl;
cout << "File 3: " << fname3 << endl;
cout << "File 4: " << fname4 << endl;


TH1D *h1 = (TH1D*)f1->Get("h_alpha");
TH1D *h2 = (TH1D*)f2->Get("h_alpha");
TH1D *h3 = (TH1D*)f3->Get("h_alpha");
TH1D *h4 = (TH1D*)f4->Get("h_alpha");



TCanvas *c = new TCanvas("c","",800,700);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.03);
c->SetLogy(0);
c->cd();


h1->SetStats(0);

h1->SetLineWidth(3);
h2->SetLineWidth(3);
h3->SetLineWidth(3);
h4->SetLineWidth(3);

h1->SetLineColor(kBlack);
h2->SetLineColor(kRed+1);
h3->SetLineColor(kBlue-3);
h4->SetLineColor(kGreen+2);

	
h1->GetXaxis()->SetRangeUser(0.10,0.50);
h1->GetYaxis()->SetRangeUser(0,0.7);
h1->GetXaxis()->SetTitle("#alpha");
h1->GetXaxis()->SetTitleSize(0.055);
h1->GetXaxis()->SetTitleOffset(0.82);
h1->GetYaxis()->SetTitle("Percentage of events/bin");
h1->GetYaxis()->SetTitleSize(0.055);
h1->GetYaxis()->SetTitleOffset(0.85);
h1->GetXaxis()->SetNdivisions(512,"kTRUE");

h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");
h4->Draw("hist same");



TPaveText *cms1 = new TPaveText(0.18,0.91,0.43,0.96,"NDC"); 
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.055);
cms1->Draw();

TPaveText *cms2 = new TPaveText(0.825,0.91,0.975,0.96,"NDC"); 
cms2->AddText("13 TeV");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.055);
cms2->SetTextFont(42);
cms2->Draw();


TLegend *leg = new TLegend(0.65,0.6,0.89,0.87); 
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->AddEntry(h1, "#Gamma / M_{S} = 0.43 %", "L");
leg->AddEntry(h2, "#Gamma / M_{S} = 1.5 %", "L");
leg->AddEntry(h3, "#Gamma / M_{S} = 5 %", "L");
leg->AddEntry(h4, "#Gamma / M_{S} = 10 %", "L");
leg->Draw();

char legname1[1024];

sprintf(legname1, "M_{S} = %.1f TeV", Suu/1000.);

TPaveText *sig = new TPaveText(0.13,0.66,0.33,0.87,"NDC"); 
sig->AddText("Diquark: S #rightarrow #chi#chi #rightarrow (ug)(ug)"); 
sig->AddText("M_{#chi} / M_{S} = 0.25");
sig->AddText(legname1);
sig->SetBorderSize(0);
sig->SetTextFont(42);
sig->SetFillColor(0);
sig->SetTextSize(0.04);
sig->SetTextAlign(12);
sig->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/AlphaShapes_alpha%s_Suu%.0f_vsWidth.png",alpha_true_name,Suu);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/AlphaShapes_alpha%s_Suu%.0f_vsWidth.pdf",alpha_true_name,Suu);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


