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
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "setTDRStyle.C"

void plot_individual_canvases(){

gROOT->LoadMacro("setTDRStyle.C");
setTDRStyle();

TFile *f_alpha= new TFile("test_pulls_alpha13.root");
TH1D *pull_SF_moddijet_alpha = (TH1D*)(f_alpha->Get("h_FourjetMass"));


TCanvas *c1 = new TCanvas("c1","Signal region Data & Prediction",1800,800);
/*
//alpha: 0.10-0.12

c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.217,0.9,0.527,0.95,"NDC"); //0.23,0.9,0.52,0.95,"NDC"
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.10 < #alpha < 0.12");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.76,0.05,0.97,0.39,"NDC"); //0.85,0.12,0.9,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{21.8 / 29}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.12-0.14
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.217,0.9,0.527,0.95,"NDC"); //0.23,0.9,0.52,0.95,"NDC"
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.12 < #alpha < 0.14");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.76,0.05,0.97,0.39,"NDC"); //0.85,0.12,0.9,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{20.5 / 28}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.14-0.16
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.217,0.9,0.527,0.95,"NDC"); //0.23,0.9,0.52,0.95,"NDC"
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.14 < #alpha < 0.16");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.76,0.05,0.97,0.39,"NDC"); //0.85,0.12,0.9,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{20.3 / 30}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");


sk->Draw("same");
*/
//alpha: 0.16-0.18
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.217,0.9,0.527,0.95,"NDC"); //0.23,0.9,0.52,0.95,"NDC"
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.16 < #alpha < 0.18");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.76,0.05,0.97,0.39,"NDC"); //0.85,0.12,0.9,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{21.8 / 27}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.18-0.20
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.217,0.9,0.527,0.95,"NDC"); //0.23,0.9,0.52,0.95,"NDC"
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.18 < #alpha < 0.20");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.76,0.05,0.97,0.39,"NDC"); //0.85,0.12,0.9,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{22.3 / 29}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.20-0.22

/*
c1->cd();

c1->cd();
c1->SetTopMargin(0);
c1->SetBottomMargin(0.13);
c1->SetLeftMargin(0.1);
c1->SetRightMargin(0);

	
c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);

        //
       // pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.05);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        //pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");




	
TPaveText *pave14 = new TPaveText(0.217,0.9,0.527,0.95,"NDC");
 pave14->SetFillColor(0);
//pave->SetLineColor(0);
pave14->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave14->SetTextFont(42);
  pave14->SetTextSize(0.105);
  pave14->AddText("0.20 < #alpha < 0.22");
pave14->Draw("same");


TPaveText *pavechi7 = new TPaveText(0.76,0.15,0.97,0.49,"NDC");
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.1);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{24.6 / 28}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

////paveL1->Draw("same");

TLatex *xLab1 = new TLatex();
	xLab1->SetTextAlign(22);
	xLab1->SetTextFont(42);
	xLab1->SetTextSize(2*0.06);         
	xLab1->DrawLatex(2000, -4.2, "2");
	xLab1->DrawLatex(3000, -4.2, "3");
	xLab1->DrawLatex(4000, -4.2, "4");
	xLab1->DrawLatex(5000, -4.2, "5");
	xLab1->DrawLatex(6000, -4.2, "6");
	xLab1->DrawLatex(7000, -4.2, "7");
	xLab1->DrawLatex(8000, -4.2, "8");

sk->Draw("same");

*/
//alpha: 0.22-0.24
/*
c1->cd();


c1->SetTopMargin(0.);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.135,0.86,0.475,0.95,"NDC"); //0.14,0.88,0.47,0.93,"NDC"
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.22 < #alpha < 0.24");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.75,0.05,0.96,0.39,"NDC"); //0.83,0.12,0.88,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{27.1 / 27}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.24-0.26
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.135,0.9,0.475,0.95,"NDC");
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.24 < #alpha < 0.26");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.75,0.05,0.96,0.39,"NDC"); //0.83,0.12,0.88,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{28.7 / 25}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.26-0.28
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.135,0.9,0.475,0.95,"NDC");
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.26 < #alpha < 0.28");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.75,0.05,0.96,0.39,"NDC"); //0.83,0.12,0.88,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{27.1 / 26}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.28-0.30
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.135,0.9,0.475,0.95,"NDC");
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.28 < #alpha < 0.30");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.75,0.05,0.96,0.39,"NDC"); //0.83,0.12,0.88,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{30.2 / 23}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.30-0.32
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.135,0.9,0.475,0.95,"NDC");
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.30 < #alpha < 0.32");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.75,0.05,0.96,0.39,"NDC"); //0.83,0.12,0.88,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{23.0 / 25}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.32-0.34
/*
c1->cd();


c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);
	
	c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);


        //
        //pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.0);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.1);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");

	
TPaveText *pave6 = new TPaveText(0.135,0.9,0.475,0.95,"NDC");
 pave6->SetFillColor(0);
//pave->SetLineColor(0);
pave6->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave6->SetTextFont(42);
  pave6->SetTextSize(0.12);
  pave6->AddText("0.32 < #alpha < 0.34");
pave6->Draw("same");

TPaveText *pavechi7 = new TPaveText(0.75,0.05,0.96,0.39,"NDC"); //0.83,0.12,0.88,0.32,"NDC"
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.12);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{26.0 / 25}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

sk->Draw("same");
*/
//alpha: 0.34-inf


c1->cd();

c1->cd();
c1->SetTopMargin(0);
c1->SetBottomMargin(0.13);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);

	
c1->cd()->SetLogx(1);
	//c1->SetGridx();
	//c1->SetGridy();

	TLine *sk = new TLine(1607.,0.,9067,0.);

        //
       // pull_SF_moddijet_alpha->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_moddijet_alpha->GetXaxis()->SetNoExponent();
        pull_SF_moddijet_alpha->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleSize(2*0.);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet_alpha->GetXaxis()->SetLabelSize(2*0.05);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet_alpha->GetYaxis()->SetLabelOffset(0.02);
        //pull_SF_moddijet_alpha->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet_alpha->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet_alpha->GetYaxis()->SetRangeUser(-3.49,3.49);
        pull_SF_moddijet_alpha->GetYaxis()->SetTitleOffset(0.4);

        pull_SF_moddijet_alpha->GetYaxis()->SetNdivisions(210); 
        pull_SF_moddijet_alpha->SetLineWidth(1);


        



        pull_SF_moddijet_alpha->SetYTitle("");
        pull_SF_moddijet_alpha->SetFillColor(2);
        pull_SF_moddijet_alpha->Draw("same HIST");




	
TPaveText *pave14 = new TPaveText(0.27,0.9,0.48,0.95,"NDC");
 pave14->SetFillColor(0);
//pave->SetLineColor(0);
pave14->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pave14->SetTextFont(42);
  pave14->SetTextSize(0.105);
  pave14->AddText("#alpha > 0.34");
pave14->Draw("same");


TPaveText *pavechi7 = new TPaveText(0.75,0.15,0.96,0.49,"NDC");
 pavechi7->SetFillColor(0);
//pave->SetLineColor(0);
pavechi7->SetBorderSize(0);
  //pave->SetFillStyle(4100);
  pavechi7->SetTextFont(42);
 pavechi7->SetTextSize(0.1);
  pavechi7->AddText("#splitline{#chi^{2} / NDF =}{14.4 / 21}");
 // pavechi->AddText("21.8/29");
pavechi7->Draw("same");

////paveL1->Draw("same");

TLatex *xLab1 = new TLatex();
	xLab1->SetTextAlign(22);
	xLab1->SetTextFont(42);
	xLab1->SetTextSize(2*0.06);         
	xLab1->DrawLatex(2000, -4.2, "2");
	xLab1->DrawLatex(3000, -4.2, "3");
	xLab1->DrawLatex(4000, -4.2, "4");
	xLab1->DrawLatex(5000, -4.2, "5");
	xLab1->DrawLatex(6000, -4.2, "6");
	xLab1->DrawLatex(7000, -4.2, "7");
	xLab1->DrawLatex(8000, -4.2, "8");

sk->Draw("same");

TFile *fout;

 fout = new TFile("new_pad14_margin_V3_FR.root","RECREATE");


fout->cd();
c1->Write();
fout->Close();

}
