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

void Plot_Data_vs_MC_2D(char jetAlgo[1024]){

char xaxistitle[1024], yaxistitle[1024];
char run[1024];

sprintf(xaxistitle,"#phi of the 4 leading jets");
sprintf(yaxistitle,"#eta of the 4 leading jets");
sprintf(run,"BC");
double xmin = -3.2;
double xmax = 3.2;
double ymin = -3;
double ymax = 3;

TPaveText *cms = new TPaveText(0.155,0.95,0.305,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.045);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname[1024];
sprintf(fname,"Histos_DataRun2022%s_VS_QCDFlatMC_AllSelCrit_PUReweight_AK4%s.root",run,jetAlgo);
TFile *f = new TFile(fname,"READ");

cout << "File used: " << fname << endl;

TH2D *h1 = (TH2D*)f->Get("h_etaphi_data");
TH2D *h2 = (TH2D*)f->Get("h_etaphi_mc");

h2->Scale(h1->Integral()/h2->Integral());

//TH2D *h = (TH2D*)h1->Clone();
//TH2D *h = (TH2D*)h2->Clone();

TH2D *h = (TH2D*)h1->Clone();
h->Divide(h2);

gStyle->SetPalette(53);
gStyle->SetPaintTextFormat(".1f");

TCanvas *c = new TCanvas("c","",600,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.15);
c->SetTopMargin(0.06);
c->SetLeftMargin(0.1);
c->SetBottomMargin(0.1);
c->SetFillColor(0);
c->SetBorderMode(0);
c->SetFrameFillStyle(0);
c->SetFrameBorderMode(0);
//c->SetLogz(1);

h->SetTitle("");
h->SetStats(0);
h->GetXaxis()->SetRangeUser(xmin, xmax);
h->GetYaxis()->SetRangeUser(ymin, ymax);
h->GetZaxis()->SetTitle("Data / MC");
h->GetXaxis()->SetTitle(xaxistitle);
h->GetYaxis()->SetTitle(yaxistitle);
h->GetXaxis()->SetTitleSize(0.05);
h->GetYaxis()->SetTitleSize(0.05);
h->GetZaxis()->SetTitleSize(0.05);
h->GetXaxis()->SetTitleOffset(0.85);
h->GetYaxis()->SetTitleOffset(0.9);
h->GetZaxis()->SetTitleOffset(0.85);
h->SetMinimum(0);
h->SetMaximum(2);
h->Draw("COLZ");

char legname[1024];
//sprintf(legname,"Data: AK4 %s, All analysis cuts applied",jetAlgo);
//sprintf(legname,"QCD MC: AK4 %s, All analysis cuts applied",jetAlgo);
sprintf(legname,"Data/MC: AK4 %s, All analysis cuts applied",jetAlgo);

TLegend *leg = new TLegend(0.17,0.88,0.77,0.93,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.03);
leg->SetHeader(legname);
//leg->AddEntry(h,"Data","");
leg->Draw();

cms->Draw();

if(strcmp(run,"B")==0 || strcmp(run,"C")==0)
{
	TPaveText *lumileg = new TPaveText(0.62,0.95,0.95,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	if(strcmp(run,"B")==0) lumileg->AddText("Run 2022 B (13.6 TeV)");
	if(strcmp(run,"C")==0) lumileg->AddText("Run 2022 C (13.6 TeV)");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.035);
	lumileg->Draw();
}
else if(strcmp(run,"BC")==0)
{
	TPaveText *lumileg = new TPaveText(0.49,0.95,0.82,0.99,"NDC");
	//TPaveText *lumileg = new TPaveText(0.66,0.95,0.97,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	lumileg->AddText("Runs 2022 B & C (13.6 TeV)");
	//lumileg->AddText("13.6 TeV");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.035);
	lumileg->Draw();
}


char cname_1[1024], cname_2[1024];
//sprintf(cname_1,"plots/Data_VS_MC/AllCuts_DataRun2022%s_%s_eta_vs_phi.png",run,jetAlgo);
//sprintf(cname_2,"plots/Data_VS_MC/AllCuts_DataRun2022%s_%s_eta_vs_phi.pdf",run,jetAlgo);

sprintf(cname_1,"plots/Data_VS_MC/AllCuts_DataRun2022%s_VS_MC_Ratio_%s_eta_vs_phi.png",run,jetAlgo);
sprintf(cname_2,"plots/Data_VS_MC/AllCuts_DataRun2022%s_VS_MC_Ratio_%s_eta_vs_phi.pdf",run,jetAlgo);

//sprintf(cname_1,"plots/Data_VS_MC/AllCuts_MC_%s_eta_vs_phi.png",jetAlgo);
//sprintf(cname_2,"plots/Data_VS_MC/AllCuts_MC_%s_eta_vs_phi.pdf",jetAlgo);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
