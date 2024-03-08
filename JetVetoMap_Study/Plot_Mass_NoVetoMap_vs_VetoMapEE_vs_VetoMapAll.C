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

void Plot_Mass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll(){

char fname1[1024], fname2[1024], fname3[1024];
//sprintf(fname1,"histos/Histos_AK4PUPPI_2022EFG_NoVetoMap.root");
//sprintf(fname2,"histos/Histos_AK4PUPPI_2022EFG_VetoMapEE.root");
//sprintf(fname3,"histos/Histos_AK4PUPPI_2022EFG_VetoMapAll.root");

//sprintf(fname1,"histos/Histos_AK4PUPPI_Run3Summer22EE_Stitched_QCD_PT-120to3200_NoVetoMap.root");
//sprintf(fname2,"histos/Histos_AK4PUPPI_Run3Summer22EE_Stitched_QCD_PT-120to3200_VetoMapEE.root");
//sprintf(fname3,"histos/Histos_AK4PUPPI_Run3Summer22EE_Stitched_QCD_PT-120to3200_VetoMapAll.root");

//sprintf(fname1,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S2000_chi500_NoVetoMap.root");
//sprintf(fname2,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S2000_chi500_VetoMapEE.root");
//sprintf(fname3,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S2000_chi500_VetoMapAll.root");

//sprintf(fname1,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S5000_chi1250_NoVetoMap.root");
//sprintf(fname2,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S5000_chi1250_VetoMapEE.root");
//sprintf(fname3,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S5000_chi1250_VetoMapAll.root");

sprintf(fname1,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S8000_chi2000_NoVetoMap.root");
sprintf(fname2,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S8000_chi2000_VetoMapEE.root");
sprintf(fname3,"histos/Histos_AK4PUPPI_Run3Summer22EE_Suu_Diquark_S8000_chi2000_VetoMapAll.root");

char xaxistitle[1024];
//double xmin = 1607;
//double xmin = 944;
//double xmin = 3279;
double xmin = 5253;
//double xmax = 9067;
//double xmax = 10798;
//double xmax = 5058;
//double xmax = 8752;
double xmax = 13272;
sprintf(xaxistitle,"Four-jet mass [GeV]");  


//TPaveText *cms = new TPaveText(0.17,0.95,0.32,0.99,"NDC");
//cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
TPaveText *cms = new TPaveText(0.225,0.95,0.375,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");
TFile *f3 = new TFile(fname3,"READ");

cout << "File 1 used: " << fname1 << endl;
cout << "File 2 used: " << fname2 << endl;
cout << "File 3 used: " << fname3 << endl;

//TH1D *h1 = (TH1D*)f1->Get("h_FourjetMass_data");
//TH1D *h2 = (TH1D*)f2->Get("h_FourjetMass_data");
//TH1D *h3 = (TH1D*)f3->Get("h_FourjetMass_data");

TH1D *h1 = (TH1D*)f1->Get("h_FourjetMass_mc");
TH1D *h2 = (TH1D*)f2->Get("h_FourjetMass_mc");
TH1D *h3 = (TH1D*)f3->Get("h_FourjetMass_mc");

for(int i=1; i<=h1->GetNbinsX(); i++)
{
	if(h1->GetBinContent(i)==0) h1->SetBinContent(i,0.0000000000001);
	if(h2->GetBinContent(i)==0) h2->SetBinContent(i,0.0000000000001);
	if(h3->GetBinContent(i)==0) h3->SetBinContent(i,0.0000000000001);	
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
//pad1r->cd()->SetLogy(1);
pad1r->cd()->SetLogy(0);
pad1r->SetTickx(1);
pad1r->SetTicky(1);

h1->SetTitle("");
h1->SetStats(0);
h1->GetXaxis()->SetRangeUser(xmin, xmax);
h2->GetXaxis()->SetRangeUser(xmin, xmax);
h1->GetYaxis()->SetTitle("Events");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetLineColor(kBlack);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
h1->SetMinimum(0.5);
//h1->SetMinimum(0.00005);

h1->SetLineColor(kBlack);
h1->SetMarkerColor(kBlack);
h1->SetLineWidth(3);
h1->SetMarkerStyle(8);
h1->SetMarkerSize(0.8);

h2->SetLineColor(kBlue-3);
h2->SetMarkerColor(kBlue-3);
h2->SetLineWidth(3);
h2->SetMarkerStyle(8);
h2->SetMarkerSize(0.8);

h3->SetLineColor(kRed-3);
h3->SetMarkerColor(kRed-3);
h3->SetLineWidth(3);
h3->SetMarkerStyle(8);
h3->SetMarkerSize(0.8);

//h1->Draw("PE1");
//h2->Draw("PE1 same");
//h3->Draw("PE1 same");

h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");


char legname1[1024], legname2[1024];
sprintf(legname1,"AK4 PUPPI");
sprintf(legname2,"All analysis cuts");

TLegend *leg = new TLegend(0.56,0.52,0.81,0.88,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->AddEntry((TObject*)0,legname1,"");
leg->AddEntry((TObject*)0,legname2,"");
leg->AddEntry((TObject*)0,"","");
leg->AddEntry(h1,"No Veto Map","L"); //PE
leg->AddEntry(h2,"Veto EE+ only","L"); //PE
leg->AddEntry(h3,"Veto all","L"); //PE
leg->Draw();

cms->Draw();

//TPaveText *lumileg = new TPaveText(0.62,0.95,0.89,0.99,"NDC");
TPaveText *lumileg = new TPaveText(0.765,0.95,0.995,0.99,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
//lumileg->AddText("2022EFG, 27 fb^{-1} (13.6 TeV)");
lumileg->AddText("13.6 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);
lumileg->Draw();


//TPaveText *sample = new TPaveText(0.15,0.1,0.45,0.25,"NDC");
//TPaveText *sample = new TPaveText(0.2,0.1,0.5,0.25,"NDC");
TPaveText *sample = new TPaveText(0.44,0.1,0.89,0.4,"NDC");
sample->SetFillColor(0);
sample->SetBorderSize(0);
//sample->AddText("#bf{Post-EE DATA}");
//sample->AddText("#bf{Run3Summer22EE}");
//sample->AddText("#bf{QCD MC}");
sample->AddText("#bf{Run3Summer22EE}");
sample->AddText("#bf{DIQUARK MC}");
//sample->AddText("#bf{M_{S} = 2 TeV, M_{#chi} = 0.5 TeV}");
//sample->AddText("#bf{M_{S} = 5 TeV, M_{#chi} = 1.25 TeV}");
sample->AddText("#bf{M_{S} = 8 TeV, M_{#chi} = 2 TeV}");
sample->SetTextFont(42);
sample->SetTextSize(0.06);
sample->Draw();

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

TH1D *h_ratio = (TH1D*)h2->Clone();
h_ratio->Divide(h1);

TH1D *h_ratio_2 = (TH1D*)h3->Clone();
h_ratio_2->Divide(h1);

h_ratio->SetStats(0);
h_ratio->SetMarkerStyle(8);
h_ratio->SetMarkerColor(kBlue-3);
h_ratio->SetLineColor(kBlue-3);
h_ratio->SetMarkerSize(0.8);
h_ratio->GetXaxis()->SetRangeUser(xmin, xmax);
h_ratio->GetYaxis()->SetRangeUser(0.91, 1.039);
h_ratio->GetYaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelOffset(0.03);
h_ratio->GetXaxis()->SetTitle(xaxistitle);
h_ratio->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio->GetYaxis()->SetTitle("Ratio");
h_ratio->GetYaxis()->CenterTitle(1);
h_ratio->GetYaxis()->SetTitleSize(0.12);
h_ratio->GetYaxis()->SetTitleOffset(0.5);
h_ratio->GetYaxis()->SetNdivisions(210);
h_ratio->SetLineWidth(3);
h_ratio->Draw("hist");

h_ratio_2->SetStats(0);
h_ratio_2->SetMarkerStyle(8);
h_ratio_2->SetMarkerColor(kRed-3);
h_ratio_2->SetLineColor(kRed-3);
h_ratio_2->SetMarkerSize(0.8);
h_ratio_2->SetLineWidth(3);
h_ratio_2->Draw("hist same");


TLine *line = new TLine(xmin,1,xmax,1);
line->SetLineWidth(2);
line->SetLineStyle(kDashed);
line->Draw("same");

TLegend *leg_ratio = new TLegend(0.57,0.35,0.82,0.6,"");
//TLegend *leg_ratio = new TLegend(0.57,0.78,0.82,0.93,""); 
leg_ratio->SetBorderSize(0);
leg_ratio->SetTextSize(0.085);
leg_ratio->AddEntry(h_ratio,"Veto EE+ / No Veto","L");
leg_ratio->AddEntry(h_ratio_2,"Veto all / No Veto","L");
leg_ratio->Draw();


char cname_1[1024], cname_2[1024];

//sprintf(cname_1,"plots/Data_2022EFG_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.png");
//sprintf(cname_2,"plots/Data_2022EFG_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.pdf");

//sprintf(cname_1,"plots/QCDMC_Run3Summer22EE_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.png");
//sprintf(cname_2,"plots/QCDMC_Run3Summer22EE_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.pdf");

//sprintf(cname_1,"plots/Diquark_S2000_chi500_Run3Summer22EE_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.png");
//sprintf(cname_2,"plots/Diquark_S2000_chi500_Run3Summer22EE_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.pdf");

//sprintf(cname_1,"plots/Diquark_S5000_chi1250_Run3Summer22EE_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.png");
//sprintf(cname_2,"plots/Diquark_S5000_chi1250_Run3Summer22EE_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.pdf");

sprintf(cname_1,"plots/Diquark_S8000_chi2000_Run3Summer22EE_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.png");
sprintf(cname_2,"plots/Diquark_S8000_chi2000_Run3Summer22EE_FourjetMass_NoVetoMap_vs_VetoMapEE_vs_VetoMapAll.pdf");

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
