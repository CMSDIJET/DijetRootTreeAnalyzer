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

void Plot_GOFpvalue_vsMassWidth(double alpha_true){

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

double mass[11] = {2, 2.2, 3, 4, 5, 6, 7, 8, 8.6, 9, 10};
double pvalue_W0p0043[11] = {0.19587, 0.2318, 0.17613, 0.20928, 0.18027, 0.17671, 0.17796, 0.27018, 0.33027, 0.31749, 0.2481};
double pvalue_W0p015[11] = {0.19923, 0.23774, 0.17634, 0.21252, 0.18102, 0.17668, 0.17784, 0.27071, 0.32963, 0.31548, 0.24645};
double pvalue_W0p05[11] = {0.20315, 0.26917, 0.17629, 0.22876, 0.18077, 0.17657, 0.17725, 0.26318, 0.31817, 0.30836, 0.24554};
double pvalue_W0p1[11] = {0.21574, 0.28728, 0.1762, 0.2276, 0.18159, 0.17654, 0.1772, 0.25607, 0.30395, 0.29705, 0.23633};

TGraph *g_W0p0043 = new TGraph(11, mass, pvalue_W0p0043);
TGraph *g_W0p015 = new TGraph(11, mass, pvalue_W0p015);
TGraph *g_W0p05 = new TGraph(11, mass, pvalue_W0p05);
TGraph *g_W0p1 = new TGraph(11, mass, pvalue_W0p1);

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
//c->SetLogy(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetGridy(0);
c->SetRightMargin(0.03);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.14);
c->SetBottomMargin(0.12);

double xmin = 1.6;
double xmax = 10.4;

auto frame = c->DrawFrame(xmin,0,xmax,0.4);
frame->GetXaxis()->SetTitleSize(0.065);
frame->GetXaxis()->SetTitleOffset(0.8);
frame->GetXaxis()->SetTitle("Diquark resonance mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.055);
frame->GetYaxis()->SetTitleOffset(1.21);
frame->GetYaxis()->SetTitle("Signal plus background fit #it{p}-value");
frame->GetYaxis()->SetLabelSize(0.045);
frame->GetYaxis()->SetLabelOffset(0.012);
frame->GetXaxis()->SetLabelSize(0.045);

g_W0p0043->SetLineColor(kBlack);
g_W0p0043->SetLineWidth(2);  
g_W0p0043->SetMarkerColor(kBlack);
//g_W0p0043->SetMarkerStyle(kFullCross);
g_W0p0043->SetMarkerStyle(21);
g_W0p0043->SetMarkerSize(1.5);

g_W0p015->SetLineColor(kRed+1);
g_W0p015->SetLineWidth(2);  
g_W0p015->SetMarkerColor(kRed+1);
//g_W0p015->SetMarkerStyle(kFullCross);
g_W0p015->SetMarkerStyle(20);
g_W0p015->SetMarkerSize(1.5);

g_W0p05->SetLineColor(kBlue-3);
g_W0p05->SetLineWidth(2);  
g_W0p05->SetMarkerColor(kBlue-3);
//g_W0p05->SetMarkerStyle(kFullCross);
g_W0p05->SetMarkerStyle(22);
g_W0p05->SetMarkerSize(1.5);

g_W0p1->SetLineColor(kGreen+2);
g_W0p1->SetLineWidth(2);  
g_W0p1->SetMarkerColor(kGreen+2);
//g_W0p1->SetMarkerStyle(kFullCross);
g_W0p1->SetMarkerStyle(23);
g_W0p1->SetMarkerSize(1.5);

g_W0p0043->Draw("p same");
g_W0p015->Draw("p same");
g_W0p05->Draw("p same");
g_W0p1->Draw("p same");



TPaveText *cms1 = new TPaveText(0.16,0.81,0.33,0.84,"NDC"); 
cms1->AddText("#splitline{#bf{CMS}}{#scale[0.7]{#it{Preliminary}}}"); 
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
sprintf(alpha_leg, "M_{#chi} / M_{S} = %.2f", alpha_true);

TLegend *leg = new TLegend(0.16,0.15,0.51,0.4);
leg->SetFillColor(0);
leg->SetBorderSize(1);
leg->SetTextSize(0.034);
leg->AddEntry((TObject*)0, "S #rightarrow #chi#chi #rightarrow (ug)(ug)", "");
leg->AddEntry((TObject*)0, alpha_leg, "");
leg->AddEntry(g_W0p0043, "#Gamma / M_{S} = 0.43 %", "P");
leg->AddEntry(g_W0p015, "#Gamma / M_{S} = 1.5 %", "P");
leg->AddEntry(g_W0p05, "#Gamma / M_{S} = 5 %", "P");
leg->AddEntry(g_W0p1, "#Gamma / M_{S} = 10 %", "P");
leg->Draw();



TPaveText *leg_bkgonly = new TPaveText(0.69,0.425,0.92,0.525,"NDC"); 
leg_bkgonly->AddText("Background-only fit");
leg_bkgonly->AddText("#it{p}-value = 0.18");
leg_bkgonly->SetBorderSize(0);
leg_bkgonly->SetFillColor(0);
leg_bkgonly->SetTextSize(0.039);
leg_bkgonly->SetTextFont(42);
leg_bkgonly->SetTextAlign(22);
leg_bkgonly->SetTextColor(kViolet);
leg_bkgonly->Draw();

TLine *line_bkgonly = new TLine(xmin, 0.18091, xmax, 0.18091);
line_bkgonly->SetLineColor(kViolet); 
line_bkgonly->SetLineWidth(3);    
line_bkgonly->SetLineStyle(2);      
line_bkgonly->Draw("same");


TPaveText *leg_gof = new TPaveText(0.57,0.18,0.9,0.32,"NDC"); 
leg_gof->AddText("Goodness of fit");
leg_gof->AddText("Likelihood ratio test with respect");
leg_gof->AddText("to the saturated model");
leg_gof->SetBorderSize(0);
leg_gof->SetFillColor(0);
leg_gof->SetTextSize(0.038);
leg_gof->SetTextFont(42);
leg_gof->SetTextAlign(22);
leg_gof->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/GOFPValueVsMassVsWidth_alpha%s.png",alpha_true_name);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/GOFPValueVsMassVsWidth_alpha%s.pdf",alpha_true_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


