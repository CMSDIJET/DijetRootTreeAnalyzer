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
#include "setTDRStyle_2DLimits.C"
#include "TGraph.h"
#include "TGraph2D.h"

void Plot_2D_Limits_M4J_vs_alpha(){

setTDRStyle_2DLimits();

TGraph2D *g_lim_M4J_vs_alpha = new TGraph2D();

int count=0;
char filename[1024];

for(int alphap=11; alphap<=35; alphap=alphap+2)
{
	if(alphap==35) alphap=42;

	sprintf(filename,"limits_freq_gg_pfdijet2017_alpha0p%d.root",alphap);
	TFile *f = new TFile(filename,"READ");

	//TGraph *g_lim = (TGraph*)f->Get("obs_gg_pfdijet2017");
	TGraph *g_lim = (TGraph*)f->Get("exp_gg_pfdijet2017"); 

	for(int i=0; i<=70; i++) 
	{
		double Suu_mass, limit;
		g_lim->GetPoint(i,Suu_mass,limit);
		
		g_lim_M4J_vs_alpha->SetPoint(count*71+i,Suu_mass,alphap/100.,limit);
	}

	count++;

	g_lim->Clear();
}

//cout<<"Points of tgraph = " << g_lim_M4J_vs_alpha->GetN() << endl;

TCanvas *c = new TCanvas("c","c",1200,1200);
c->cd();
c->SetLogz(1);
c->SetTopMargin(0.05);
c->SetRightMargin(0.16);
c->SetLeftMargin(0.12);
gStyle->SetPalette(53); // 56
//TColor::InvertPalette();

TH2D *h_lim_M4J_vs_alpha = (TH2D*)g_lim_M4J_vs_alpha->GetHistogram();
auto frame = c->DrawFrame(1800,0.1,9200,0.46);
frame->GetXaxis()->SetLabelSize(0);
frame->GetXaxis()->SetTitleOffset(1.);
frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitle("Four-jet resonance mass [TeV]");
frame->GetYaxis()->SetTitleOffset(1.1);
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitle("#alpha_{true} = M(X)/M(Y)");

h_lim_M4J_vs_alpha->Draw("col same z");
//h_lim_M4J_vs_alpha->SetTitle(" ; Four-jet resonance mass [TeV]; #alpha_{true} = M(X)/M(Y); Observed #kern[0.1]{#sigma #times #bf{#it{#Beta}} #times #bf{#it{#Alpha}} [pb]}");
h_lim_M4J_vs_alpha->SetTitle(" ; Four-jet resonance mass [TeV]; #alpha_{true} = M(X)/M(Y); Expected #kern[0.1]{#sigma #times #bf{#it{#Beta}} #times #bf{#it{#Alpha}} [pb]}");
gPad->Update();
h_lim_M4J_vs_alpha->GetZaxis()->SetRangeUser(0.0000005,0.05); //0.0000005,0.05
h_lim_M4J_vs_alpha->GetZaxis()->SetTitleOffset(1.);
h_lim_M4J_vs_alpha->GetZaxis()->SetTitleSize(0.05);


//observed
TGraph *g_excl_obs = new TGraph();
g_excl_obs->SetPoint(0,7900,0.11);
g_excl_obs->SetPoint(1,7950,0.13);
g_excl_obs->SetPoint(2,7950,0.15);
g_excl_obs->SetPoint(3,7900,0.17);
g_excl_obs->SetPoint(4,7900,0.19);
g_excl_obs->SetPoint(5,7800,0.21);
g_excl_obs->SetPoint(6,7650,0.23);
g_excl_obs->SetPoint(7,7600,0.25);
g_excl_obs->SetPoint(8,7550,0.27);
g_excl_obs->SetPoint(9,7550,0.29);
g_excl_obs->SetPoint(10,7550,0.31);
g_excl_obs->SetPoint(11,7450,0.33);
g_excl_obs->SetPoint(12,6650,0.42);
g_excl_obs->SetLineWidth(3);
g_excl_obs->SetLineColor(15); //15
g_excl_obs->SetLineStyle(5);
g_excl_obs->Draw("L same");

//expected
TGraph *g_excl_exp = new TGraph();
g_excl_exp->SetPoint(0,7900,0.11);
g_excl_exp->SetPoint(1,7950,0.13);
g_excl_exp->SetPoint(2,7900,0.15);
g_excl_exp->SetPoint(3,7900,0.17);
g_excl_exp->SetPoint(4,7850,0.19);
g_excl_exp->SetPoint(5,7850,0.21);
g_excl_exp->SetPoint(6,7800,0.23);
g_excl_exp->SetPoint(7,7800,0.25);
g_excl_exp->SetPoint(8,7750,0.27);
g_excl_exp->SetPoint(9,7700,0.29);
g_excl_exp->SetPoint(10,7600,0.31);
g_excl_exp->SetPoint(11,7500,0.33);
g_excl_exp->SetPoint(12,6450,0.42);
g_excl_exp->SetLineColor(kBlack);
g_excl_exp->SetLineWidth(3);
g_excl_exp->SetLineStyle(5);
g_excl_exp->Draw("L same");

TLatex *xLab = new TLatex();
xLab->SetTextAlign(22);
xLab->SetTextSize(0.05);
xLab->SetTextFont(42);
xLab->SetTextSize(0.04);

char xlabel[1024];

for(int i=2; i<=9; i++)
{
	sprintf(xlabel, "%d", i);
	xLab->DrawLatex(i*1000, 0.09, xlabel);
}

TLatex *lumi = new TLatex();
lumi->SetTextAlign(11);
lumi->SetTextSize(0.035);
lumi->SetTextFont(62);
lumi->DrawLatex(7700, 0.465, "#bf{138 fb^{-1} (13 TeV)}");

TLatex *cms = new TLatex();
cms->SetTextAlign(11);
cms->SetTextSize(0.035);
cms->SetTextFont(62);
cms->DrawLatex(2400, 0.43, "CMS #scale[0.7]{#it{#bf{Preliminary}}}");
//cms->DrawLatex(2400, 0.43, "CMS #scale[0.7]{#it{#bf{Supplementary}}}");

TLegend *l = new TLegend(0.55,0.87,0.8,0.92,"");
l->SetBorderSize(0);
l->SetTextSize(0.02);
l->AddEntry(g_excl_obs,"#bf{Observed mass limit}","L");
l->AddEntry(g_excl_exp,"#bf{Expected mass limit}","L");
l->Draw();

//c->SaveAs("2D_obs_limits.C");
//c->SaveAs("2D_obs_limits.png");
//c->SaveAs("2D_obs_limits.pdf");

c->SaveAs("2D_exp_limits.C");
c->SaveAs("2D_exp_limits.png");
c->SaveAs("2D_exp_limits.pdf");

}
