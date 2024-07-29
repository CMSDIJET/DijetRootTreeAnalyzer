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

void Plot_Limits_vsWidth(double alpha_true){

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
//sprintf(fname_W0p0043, "/afs/cern.ch/user/i/izisopou/public/EXO-21-010/EXO-21-010-Plotting-Scripts/Figure_011/Limits_alpha%s/limits_freq_gg_pfdijet2017_alpha%s.root", alpha_true_name, alpha_true_name);
sprintf(fname_W0p0043, "output/Narrow_Resonances_Run2/combine_rootfiles_alpha%s/limits/limits_freq_qq_pfdijetrun2_alpha%s_W-0p0043.root", alpha_true_name, alpha_true_name);
sprintf(fname_W0p015, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/limits/limits_freq_qq_pfdijetrun2_alpha%s_W-0p015.root", alpha_true_name, alpha_true_name);
sprintf(fname_W0p05, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/limits/limits_freq_qq_pfdijetrun2_alpha%s_W-0p05.root", alpha_true_name, alpha_true_name);
sprintf(fname_W0p1, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/limits/limits_freq_qq_pfdijetrun2_alpha%s_W-0p1.root", alpha_true_name, alpha_true_name);


TFile *f_W0p0043 = new TFile(fname_W0p0043,"read");
TFile *f_W0p015 = new TFile(fname_W0p015,"read");
TFile *f_W0p05 = new TFile(fname_W0p05,"read");
TFile *f_W0p1 = new TFile(fname_W0p1,"read");

//TGraph *gExp_W0p0043 = (TGraph*)f_W0p0043->Get("exp_gg_pfdijet2017");
TGraph *gExp_W0p0043 = (TGraph*)f_W0p0043->Get("exp_qq_pfdijetrun2");
TGraph *gExp_W0p015 = (TGraph*)f_W0p015->Get("exp_qq_pfdijetrun2");
TGraph *gExp_W0p05 = (TGraph*)f_W0p05->Get("exp_qq_pfdijetrun2");
TGraph *gExp_W0p1 = (TGraph*)f_W0p1->Get("exp_qq_pfdijetrun2");

//TGraph *gObs_W0p0043 = (TGraph*)f_W0p0043->Get("obs_gg_pfdijet2017");
TGraph *gObs_W0p0043 = (TGraph*)f_W0p0043->Get("obs_qq_pfdijetrun2");
TGraph *gObs_W0p015 = (TGraph*)f_W0p015->Get("obs_qq_pfdijetrun2");
TGraph *gObs_W0p05 = (TGraph*)f_W0p05->Get("obs_qq_pfdijetrun2");
TGraph *gObs_W0p1 = (TGraph*)f_W0p1->Get("obs_qq_pfdijetrun2");

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetLogy(1);
c->SetTickx(1);
c->SetTicky(1);
//c->SetGridy(1);
c->SetRightMargin(0.03);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.14);
c->SetBottomMargin(0.12);

auto frame = c->DrawFrame(2000,5e-6,9000,0.5);
frame->GetXaxis()->SetTitleSize(0.07);
frame->GetXaxis()->SetTitleOffset(0.8);
frame->GetXaxis()->SetTitle("Four-jet resonance mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.15);
frame->GetYaxis()->SetTitle("#sigma #times #it{B} #times #it{A} [pb]");
frame->GetXaxis()->SetLabelOffset(1000);
frame->GetYaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelOffset(0.015);

gObs_W0p0043->SetLineColor(kBlack);
gObs_W0p0043->SetLineWidth(2);  
gObs_W0p0043->SetMarkerColor(kBlack);
gObs_W0p0043->SetMarkerStyle(kFullCircle);
gObs_W0p0043->SetMarkerSize(1.);

gObs_W0p015->SetLineColor(kRed+1);
gObs_W0p015->SetLineWidth(2);  
gObs_W0p015->SetMarkerColor(kRed+1);
gObs_W0p015->SetMarkerStyle(kFullCircle);
gObs_W0p015->SetMarkerSize(1.);

gObs_W0p05->SetLineColor(kBlue-3);
gObs_W0p05->SetLineWidth(2);  
gObs_W0p05->SetMarkerColor(kBlue-3);
gObs_W0p05->SetMarkerStyle(kFullCircle);
gObs_W0p05->SetMarkerSize(1.);

gObs_W0p1->SetLineColor(kGreen+2);
gObs_W0p1->SetLineWidth(2);  
gObs_W0p1->SetMarkerColor(kGreen+2);
gObs_W0p1->SetMarkerStyle(kFullCircle);
gObs_W0p1->SetMarkerSize(1.);



gExp_W0p0043->SetLineColor(kBlack);
gExp_W0p0043->SetLineWidth(3); 
gExp_W0p0043->SetLineStyle(7); 
gExp_W0p0043->SetMarkerColor(kBlack);
gExp_W0p0043->SetMarkerStyle(kFullCircle);
gExp_W0p0043->SetMarkerSize(1.2);

gExp_W0p015->SetLineColor(kRed+1);
gExp_W0p015->SetLineWidth(3); 
gExp_W0p015->SetLineStyle(7); 
gExp_W0p015->SetMarkerColor(kRed+1);
gExp_W0p015->SetMarkerStyle(kFullCircle);
gExp_W0p015->SetMarkerSize(1.2);

gExp_W0p05->SetLineColor(kBlue-3);
gExp_W0p05->SetLineWidth(3);  
gExp_W0p05->SetLineStyle(7);
gExp_W0p05->SetMarkerColor(kBlue-3);
gExp_W0p05->SetMarkerStyle(kFullCircle);
gExp_W0p05->SetMarkerSize(1.2);

gExp_W0p1->SetLineColor(kGreen+2);
gExp_W0p1->SetLineWidth(3);  
gExp_W0p1->SetLineStyle(7);
gExp_W0p1->SetMarkerColor(kGreen+2);
gExp_W0p1->SetMarkerStyle(kFullCircle);
gExp_W0p1->SetMarkerSize(1.2);

gObs_W0p0043->Draw("lp same");
gObs_W0p015->Draw("lp same");
gObs_W0p05->Draw("lp same");
gObs_W0p1->Draw("lp same");
gExp_W0p0043->Draw("c same");
gExp_W0p015->Draw("c same");
gExp_W0p05->Draw("c same");
gExp_W0p1->Draw("c same");

char xLab_leg[1024];
TLatex *xLab = new TLatex();
xLab->SetTextAlign(22);
xLab->SetTextSize(0.05);
xLab->SetTextFont(42);
xLab->SetTextSize(0.05);
for(int mass=2000; mass<=10000; mass=mass+1000)
{
    sprintf(xLab_leg,"%.0f",mass/1000.);
    //xLab->DrawLatex(mass, 6.5e-7, xLab_leg);
    xLab->DrawLatex(mass, 3.5e-6, xLab_leg);
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


TLegend *leg = new TLegend(0.15,0.72,0.25,0.87);
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->AddEntry((TObject*)0, "Y #rightarrow XX #rightarrow (jj)(jj)", "");
leg->AddEntry((TObject*)0, alpha_leg, "");
leg->Draw();


TLegend *leg2 = new TLegend(0.49,0.62,0.80,0.82);
leg2->SetFillColor(0);
leg2->SetBorderSize(0);
leg2->SetTextSize(0.04);
leg2->SetMargin(0.3);
leg2->AddEntry(gExp_W0p0043, " ", "L");
leg2->AddEntry(gExp_W0p015, " ", "L");
leg2->AddEntry(gExp_W0p05, " ", "L");
leg2->AddEntry(gExp_W0p1, " ", "L");
leg2->Draw();

TLegend *leg3 = new TLegend(0.57,0.62,0.93,0.82);
leg3->SetFillColor(0);
leg3->SetBorderSize(0);
leg3->SetTextSize(0.04);
leg3->SetMargin(0.4);
leg3->AddEntry(gObs_W0p0043, "#Gamma / M_{Y} = 0.43 %", "LP");
leg3->AddEntry(gObs_W0p015, "#Gamma / M_{Y} = 1.5 %", "LP");
leg3->AddEntry(gObs_W0p05, "#Gamma / M_{Y} = 5 %", "LP");
leg3->AddEntry(gObs_W0p1, "#Gamma / M_{Y} = 10 %", "LP");
leg3->Draw();

/*
TLegend *leg3 = new TLegend(0.57,0.62,0.93,0.87);
leg3->SetFillColor(0);
leg3->SetBorderSize(0);
leg3->SetTextSize(0.04);
//leg3->SetHeader("Observed 95% CL limits");
//leg3->AddEntry(gObs_W0p0043, "#Gamma / M_{Y} = 0.43 %", "LP");
//leg3->AddEntry(gObs_W0p015, "#Gamma / M_{Y} = 1.5 %", "LP");
//leg3->AddEntry(gObs_W0p05, "#Gamma / M_{Y} = 5 %", "LP");
//leg3->AddEntry(gObs_W0p1, "#Gamma / M_{Y} = 10 %", "LP");
leg3->SetHeader("Expected 95% CL limits");
leg3->AddEntry(gExp_W0p0043, "#Gamma / M_{Y} = 0.43 %", "L");
leg3->AddEntry(gExp_W0p015, "#Gamma / M_{Y} = 1.5 %", "L");
leg3->AddEntry(gExp_W0p05, "#Gamma / M_{Y} = 5 %", "L");
leg3->AddEntry(gExp_W0p1, "#Gamma / M_{Y} = 10 %", "L");
leg3->Draw();
*/

TLatex *lat = new TLatex();
lat->SetTextAlign(22);
lat->SetTextFont(42);
lat->SetTextSize(0.045);
//lat->DrawLatex(5800, 3.5e-1,"Exp.   Obs.");
//lat->DrawLatex(7650, 3.8e-1,"95% CL limits");
lat->DrawLatex(5800, 2e-1,"Exp.   Obs.");
lat->DrawLatex(7650, 2.1e-1,"95% CL limits");


char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/LimitVsMassVsWidth_alpha%s.png",alpha_true_name);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/LimitVsMassVsWidth_alpha%s.pdf",alpha_true_name);

//sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/ObsLimitVsMassVsWidth_alpha%s.png",alpha_true_name);
//sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/ObsLimitVsMassVsWidth_alpha%s.pdf",alpha_true_name);

//sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/ExpLimitVsMassVsWidth_alpha%s.png",alpha_true_name);
//sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/ExpLimitVsMassVsWidth_alpha%s.pdf",alpha_true_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


