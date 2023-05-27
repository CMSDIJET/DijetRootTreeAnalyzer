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
#include "TGraph.h"

void Plot_Signal_Grid(){

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.05);
c->SetTopMargin(0.07);
c->SetLeftMargin(0.12);

auto frame = c->DrawFrame(1000,0.05,12000,0.52);
//auto frame = c->DrawFrame(1000,150,12000,5000);
frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitleOffset(0.95);
frame->GetXaxis()->SetTitle("Diquark mass [GeV]");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(1.2);
frame->GetYaxis()->SetTitle("#alpha_{true} = #chi mass / Diquark mass");
//frame->GetYaxis()->SetTitle("#chi mass [GeV]");

TGraph *g1 = new TGraph(130);

int p=0;

for(int Suu=2000; Suu<=11000; Suu=Suu+1000)
{
	for(int a=11; a<=35; a=a+2)
	{
		if(a==35) a=42;
		g1->SetPoint(p,Suu,a/100.);
		//g1->SetPoint(p,Suu,(a/100.)*Suu);
		p++;
	}
}

cout<<"p = "<<p<<endl;

TGraph *g2 = new TGraph(23);
g2->SetPoint(0,8600,2150./8600.);
g2->SetPoint(1,8400,1900./8400.);
g2->SetPoint(2,8400,2000./8400.);
g2->SetPoint(3,8400,2100./8400.);
g2->SetPoint(4,8400,2200./8400.);
g2->SetPoint(5,8400,2300./8400.);
g2->SetPoint(6,7800,2100./7800.);
g2->SetPoint(7,8100,2100./8100.);
g2->SetPoint(8,8700,2100./8700.);
g2->SetPoint(9,9000,2100./9000.);
g2->SetPoint(10,8000,3000./8000.);
g2->SetPoint(11,8000,1000./8000.);
g2->SetPoint(12,6000,1000./6000.);
g2->SetPoint(13,6000,2000./6000.);
g2->SetPoint(14,6000,2900./6000.);
g2->SetPoint(15,5000,1000./5000.);
g2->SetPoint(16,5000,2000./5000.);
g2->SetPoint(17,4000,500./4000.);
g2->SetPoint(18,4000,2000./4000.);
g2->SetPoint(19,3000,1000./3000.);
g2->SetPoint(20,3000,500./3000.);
g2->SetPoint(21,2000,1000./2000.);
g2->SetPoint(22,2000,750./2000.);

/*
g2->SetPoint(0,8600,2150.);
g2->SetPoint(1,8400,1900.);
g2->SetPoint(2,8400,2000.);
g2->SetPoint(3,8400,2100.);
g2->SetPoint(4,8400,2200.);
g2->SetPoint(5,8400,2300.);
g2->SetPoint(6,7800,2100.);
g2->SetPoint(7,8100,2100.);
g2->SetPoint(8,8700,2100.);
g2->SetPoint(9,9000,2100.);
g2->SetPoint(10,8000,3000.);
g2->SetPoint(11,8000,1000.);
g2->SetPoint(12,6000,1000.);
g2->SetPoint(13,6000,2000.);
g2->SetPoint(14,6000,2900.);
g2->SetPoint(15,5000,1000.);
g2->SetPoint(16,5000,2000.);
g2->SetPoint(17,4000,500.);
g2->SetPoint(18,4000,2000.);
g2->SetPoint(19,3000,1000.);
g2->SetPoint(20,3000,500.);
g2->SetPoint(21,2000,1000.);
g2->SetPoint(22,2000,750.);
*/
g1->SetMarkerStyle(47);
g1->SetMarkerColor(kBlack);
g1->SetMarkerSize(1.2);

g2->SetMarkerStyle(47);
g2->SetMarkerColor(kBlack);
g2->SetMarkerSize(1.2);

g1->Draw("P same");
g2->Draw("P same");

c->SaveAs("plots/Signal_Grid_SuuMass_vs_alpha.png");
c->SaveAs("plots/Signal_Grid_SuuMass_vs_alpha.pdf");

//c->SaveAs("plots/Signal_Grid_SuuMass_vs_ChiMass.png");
//c->SaveAs("plots/Signal_Grid_SuuMass_vs_ChiMass.pdf");

}
