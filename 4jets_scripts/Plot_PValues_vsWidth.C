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

void Plot_PValues_vsWidth(double alpha_true){

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

char fname_W0p015[1024], fname_W0p05[1024], fname_W0p1[1024], fname_W0p0043[1024];
sprintf(fname_W0p0043, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/pvalues/pvalue_qq_pfdijetrun2_alpha%s_W-0p0043_AsymptPlusHN.root", alpha_true_name, alpha_true_name);
sprintf(fname_W0p015, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/pvalues/pvalue_qq_pfdijetrun2_alpha%s_W-0p015_AsymptPlusHN.root", alpha_true_name, alpha_true_name);
sprintf(fname_W0p05, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/pvalues/pvalue_qq_pfdijetrun2_alpha%s_W-0p05_AsymptPlusHN.root", alpha_true_name, alpha_true_name);
sprintf(fname_W0p1, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/pvalues/pvalue_qq_pfdijetrun2_alpha%s_W-0p1_AsymptPlusHN.root", alpha_true_name, alpha_true_name);


TFile *f_W0p0043 = new TFile(fname_W0p0043,"read");
TFile *f_W0p015 = new TFile(fname_W0p015,"read");
TFile *f_W0p05 = new TFile(fname_W0p05,"read");
TFile *f_W0p1 = new TFile(fname_W0p1,"read");

TGraph *g_W0p0043 = (TGraph*)f_W0p0043->Get("Graph");
TGraph *g_W0p015 = (TGraph*)f_W0p015->Get("Graph");
TGraph *g_W0p05 = (TGraph*)f_W0p05->Get("Graph");
TGraph *g_W0p1 = (TGraph*)f_W0p1->Get("Graph");

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetLogy(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetGridy(0);
c->SetRightMargin(0.03);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.14);
c->SetBottomMargin(0.12);

auto frame = c->DrawFrame(2000,5e-06,10000,2.);
frame->GetXaxis()->SetTitleSize(0.07);
frame->GetXaxis()->SetTitleOffset(0.8);
frame->GetXaxis()->SetTitle("Four-jet resonance mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.19);
frame->GetYaxis()->SetTitle("Local #it{p}-value");
frame->GetXaxis()->SetLabelOffset(1000);
frame->GetYaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelOffset(0.015);

g_W0p0043->SetLineColor(kBlack);
g_W0p0043->SetLineWidth(2);  
g_W0p0043->SetMarkerColor(kBlack);
g_W0p0043->SetMarkerStyle(kFullCircle);
g_W0p0043->SetMarkerSize(1.);

g_W0p015->SetLineColor(kRed+1);
g_W0p015->SetLineWidth(2);  
g_W0p015->SetMarkerColor(kRed+1);
g_W0p015->SetMarkerStyle(kFullCircle);
g_W0p015->SetMarkerSize(1.);

g_W0p05->SetLineColor(kBlue-3);
g_W0p05->SetLineWidth(2);  
g_W0p05->SetMarkerColor(kBlue-3);
g_W0p05->SetMarkerStyle(kFullCircle);
g_W0p05->SetMarkerSize(1.);

g_W0p1->SetLineColor(kGreen+2);
g_W0p1->SetLineWidth(2);  
g_W0p1->SetMarkerColor(kGreen+2);
g_W0p1->SetMarkerStyle(kFullCircle);
g_W0p1->SetMarkerSize(1.);

g_W0p0043->Draw("lp same");
g_W0p015->Draw("lp same");
g_W0p05->Draw("lp same");
g_W0p1->Draw("lp same");


char xLab_leg[1024];
TLatex *xLab = new TLatex();
xLab->SetTextAlign(22);
xLab->SetTextSize(0.05);
xLab->SetTextFont(42);
xLab->SetTextSize(0.05);
for(int mass=2000; mass<=10000; mass=mass+1000)
{
    sprintf(xLab_leg,"%.0f",mass/1000.);
    xLab->DrawLatex(mass, 3.e-6, xLab_leg);
}


TPaveText *cms1 = new TPaveText(0.12,0.925,0.42,0.955,"NDC"); 
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.055);
cms1->Draw();

TPaveText *cms2 = new TPaveText(0.755,0.925,0.895,0.955,"NDC"); 
cms2->AddText("138 fb^{-1} (13 TeV)");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.05);
cms2->SetTextFont(42);
cms2->Draw();

char alpha_leg[1024];
sprintf(alpha_leg, "M_{X} / M_{Y} = %.2f", alpha_true);

TLegend *leg = new TLegend(0.20,0.242,0.50,0.454);
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.034);
leg->AddEntry((TObject*)0, "Y #rightarrow XX #rightarrow (jj)(jj)", "");
leg->AddEntry((TObject*)0, alpha_leg, "");
leg->AddEntry(g_W0p0043, "#Gamma / M_{Y} = 0.43 %", "LP");
leg->AddEntry(g_W0p015, "#Gamma / M_{Y} = 1.5 %", "LP");
leg->AddEntry(g_W0p05, "#Gamma / M_{Y} = 5 %", "LP");
leg->AddEntry(g_W0p1, "#Gamma / M_{Y} = 10 %", "LP");
leg->Draw();

/*TPaveText *sig = new TPaveText(0.6,0.8,0.89,0.88,"NDC"); 
sig->AddText("Y #rightarrow XX #rightarrow (jj)(jj)");
sig->AddText(alpha_leg);
sig->SetBorderSize(0);
sig->SetFillColor(0);
sig->SetTextSize(0.035);
sig->SetTextFont(42);
sig->SetTextAlign(12);
sig->Draw();*/

TLine *l0sigma = new TLine(2000, 0.5, 6100, 0.5);
TLine *l1sigma = new TLine(2000, 0.15865525, 6100, 0.15865525);
TLine *l2sigma = new TLine(2000, 0.022750132, 6100, 0.022750132);
TLine *l3sigma = new TLine(2000, 0.0013498980, 6100, 0.0013498980);
TLine *l4sigma = new TLine(2000, 3.1671242e-05, 6100, 3.1671242e-05);   
l0sigma->SetLineColor(kViolet);
l1sigma->SetLineColor(kViolet);
l2sigma->SetLineColor(kViolet);
l3sigma->SetLineColor(kViolet);
l4sigma->SetLineColor(kViolet);      
l0sigma->SetLineStyle(2);
l1sigma->SetLineStyle(2);
l2sigma->SetLineStyle(2);
l3sigma->SetLineStyle(2);
l4sigma->SetLineStyle(2);
l0sigma->SetLineWidth(2);
l1sigma->SetLineWidth(2);
l2sigma->SetLineWidth(2);
l3sigma->SetLineWidth(2);
l4sigma->SetLineWidth(2);       
l0sigma->Draw("same");
l1sigma->Draw("same");
l2sigma->Draw("same");
l3sigma->Draw("same");
l4sigma->Draw("same");

TLine *l0sigma_v2 = new TLine(6500, 0.5, 10000, 0.5);
TLine *l1sigma_v2 = new TLine(6500, 0.15865525, 10000, 0.15865525);
TLine *l2sigma_v2 = new TLine(6500, 0.022750132, 10000, 0.022750132);
TLine *l3sigma_v2 = new TLine(6500, 0.0013498980, 10000, 0.0013498980);
TLine *l4sigma_v2 = new TLine(6500, 3.1671242e-05, 10000, 3.1671242e-05);   
l0sigma_v2->SetLineColor(kViolet);
l1sigma_v2->SetLineColor(kViolet);
l2sigma_v2->SetLineColor(kViolet);
l3sigma_v2->SetLineColor(kViolet);
l4sigma_v2->SetLineColor(kViolet);      
l0sigma_v2->SetLineStyle(2);
l1sigma_v2->SetLineStyle(2);
l2sigma_v2->SetLineStyle(2);
l3sigma_v2->SetLineStyle(2);
l4sigma_v2->SetLineStyle(2);
l0sigma_v2->SetLineWidth(2);
l1sigma_v2->SetLineWidth(2);
l2sigma_v2->SetLineWidth(2);
l3sigma_v2->SetLineWidth(2);
l4sigma_v2->SetLineWidth(2);       
l0sigma_v2->Draw("same");
l1sigma_v2->Draw("same");
l2sigma_v2->Draw("same");
l3sigma_v2->Draw("same");
l4sigma_v2->Draw("same");

TLatex *lsigma_leg = new TLatex();
lsigma_leg->SetTextAlign(22);
lsigma_leg->SetTextSize(0.035);
lsigma_leg->SetTextFont(42);
lsigma_leg->SetTextColor(kViolet);
 
lsigma_leg->DrawLatex(6300, 0.15865525, "1#sigma");
lsigma_leg->DrawLatex(6300, 0.022750132, "2#sigma");
lsigma_leg->DrawLatex(6300, 0.0013498980, "3#sigma");
lsigma_leg->DrawLatex(6300, 3.1671242e-05, "4#sigma");


char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/significances/AsymptPlusHNPValueVsMassVsWidth_alpha%s.png",alpha_true_name);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/significances/AsymptPlusHNPValueVsMassVsWidth_alpha%s.pdf",alpha_true_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


