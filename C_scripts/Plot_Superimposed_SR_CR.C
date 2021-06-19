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
#include "setTDRStyle_teliko.C"

void Plot_Superimposed_SR_CR(){

	double startit_SR = 1.530;
	double startit_CR = 2.438;
        double endit = 8.752;

	gROOT->LoadMacro("setTDRStyle_teliko.C");
	setTDRStyle_teliko();

	TFile *fdata= new TFile("../inputs/Double_sideband_inputs_16AugV11_17v6_18v10_SR_Scale.root");

	TH1D *signal_data  = (TH1D*)(fdata->Get("h_mjj"));
	TH1D *control_data = (TH1D*)(fdata->Get("h_mjj_high"));
	TH1D *control_middle_data = (TH1D*)(fdata->Get("h_mjj_middle"));
	TH1D *signal_MC    = (TH1D*)(fdata->Get("h_mjj_MC"));
	TH1D *control_MC   = (TH1D*)(fdata->Get("h_mjj_high_MC"));
	TH1D *control_middle_MC   = (TH1D*)(fdata->Get("h_mjj_middle_MC"));

  const int nMassBins = 102;
  double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
     4686,  4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};
     
  for(Int_t i=0;i<=(nMassBins+1);i++){
     massBoundaries[i]=massBoundaries[i]*0.001;
   }

       TH1D *signal_MCt           = new TH1D("signal_MCt","signal_MCt",nMassBins,massBoundaries);
       TH1D *signal_datat 	  = new TH1D("signal_datat","signal_datat",nMassBins,massBoundaries);
       TH1D *control_middle_datat = new TH1D("control_middle_datat","control_middle_datat",nMassBins,massBoundaries);
       TH1D *control_datat        = new TH1D("control_datat","control_datat",nMassBins,massBoundaries);
       TH1D *control_MCt          = new TH1D("control_MCt","control_MCt",nMassBins,massBoundaries);
       TH1D *control_middle_MCt   = new TH1D("control_middle_MCt","control_middle_MCt",nMassBins,massBoundaries);

	signal_datat->SetMarkerStyle(8);
	signal_datat->SetLineColor(1);
	signal_datat->SetMarkerColor(1);

	control_datat->SetMarkerStyle(25); // 2
	control_datat->SetLineColor(1);
	control_datat->SetMarkerColor(1);

	control_middle_datat->SetMarkerStyle(26);
	control_middle_datat->SetLineColor(1);
	control_middle_datat->SetMarkerColor(1);
//
	signal_MCt->SetLineWidth(2);
	signal_MCt->SetLineColor(2);
	signal_MCt->SetFillColor(0);

	control_MCt->SetLineWidth(2);
	control_MCt->SetLineColor(6);
	control_MCt->SetFillColor(0);

	control_middle_MCt->SetLineWidth(2);
	control_middle_MCt->SetLineColor(4);
	control_middle_MCt->SetFillColor(0);

        for(Int_t ibin=1;ibin<=signal_MC->GetNbinsX();ibin++){
          double cont = signal_MC->GetBinContent(ibin);
          signal_MCt->SetBinContent(ibin,cont);
          cont = signal_data->GetBinContent(ibin);
	  signal_datat->SetBinContent(ibin,cont);          
          cont = control_middle_data->GetBinContent(ibin);
          control_middle_datat->SetBinContent(ibin,cont);
          cont = control_data->GetBinContent(ibin);
          control_datat->SetBinContent(ibin,cont);
          cont = control_MC->GetBinContent(ibin);
          control_MCt->SetBinContent(ibin,cont);
          cont = control_middle_MC->GetBinContent(ibin);
          control_middle_MCt->SetBinContent(ibin,cont);
        }

       TH1D * signal_datap           = (TH1D*)(signal_datat->Clone());
        signal_datap->Sumw2(kFALSE);
        signal_datap->SetBinErrorOption(TH1::kPoisson);

        TH1D * control_datap           = (TH1D*)(control_datat->Clone());
        control_datap->Sumw2(kFALSE);
        control_datap->SetBinErrorOption(TH1::kPoisson);

        TH1D * control_middle_datap           = (TH1D*)(control_middle_datat->Clone());
        control_middle_datap->Sumw2(kFALSE);
        control_middle_datap->SetBinErrorOption(TH1::kPoisson);

        for(Int_t i=1;i<=signal_datat->GetNbinsX();i++){
           double cont = signal_datat->GetBinContent(i);
           signal_datap->SetBinContent(i,cont);
           signal_datap->SetBinErrorOption(TH1::kPoisson);
//
           cont = control_datat->GetBinContent(i);
           control_datap->SetBinContent(i,cont);
           control_datap->SetBinErrorOption(TH1::kPoisson);
//
           cont = control_middle_datat->GetBinContent(i);
           control_middle_datap->SetBinContent(i,cont);
           control_middle_datap->SetBinErrorOption(TH1::kPoisson);
        }

        signal_datap->SetMarkerStyle(8);     
        signal_datap->SetLineColor(1);
        signal_datap->SetMarkerColor(1);
           
        control_datap->SetMarkerStyle(25); // 2
        control_datap->SetLineColor(1);      
        control_datap->SetMarkerColor(1);
           
        control_middle_datap->SetMarkerStyle(26);
        control_middle_datap->SetLineColor(1);
        control_middle_datap->SetMarkerColor(1);

		                             //0.14
	 TPaveText *paveCMS = new TPaveText(0.16,0.96,0.96,0.99,"NDC");
	 paveCMS->AddText("CMS Preliminary    #sqrt{s} = 13 TeV       L = 137 fb^{-1}");
	 paveCMS->SetFillColor(0);
	 paveCMS->SetBorderSize(0);
	 paveCMS->SetTextSize(0.04);

 	 TLegend *leg = new TLegend(0.6,0.6,0.8,0.9);
	 leg->AddEntry(signal_datat,   "Data  SR","p");
	 leg->AddEntry(signal_MCt,   "PYTHIA  SR","l");
	 leg->AddEntry(control_middle_datat,   "Data  CR_{middle}","p");
	 leg->AddEntry(control_middle_MCt,   "PYTHIA  CR_{middle}","l");
	 leg->AddEntry(control_datat,   "Data  CR_{high}","p");
	 leg->AddEntry(control_MCt,   "PYTHIA  CR_{high}","l");
	 leg->SetTextSize(0.03);

	 TPaveText *paveCMS2 = new TPaveText(0.25,0.35,0.45,0.5,"NDC");
	 paveCMS2->AddText("|#eta| < 2.5" );
// 	 paveCMS2->AddText("m_{jj} > 1.5 TeV (SR) ");
//       paveCMS2->AddText("m_{jj} > 2.4 TeV (CRs)");
         paveCMS2->SetFillColor(0);
         paveCMS2->SetBorderSize(0);
         paveCMS2->SetFillStyle(0);
         paveCMS2->SetTextFont(42);
         paveCMS2->SetTextSize(0.04);

	TCanvas *c1 = new TCanvas("c1","Control Region Data",600,600);
	 c1->cd();
	 
	 signal_datat->GetXaxis()->SetRangeUser(startit_SR,endit);
	 signal_MCt->GetXaxis()->SetRangeUser(startit_SR,endit);
	 control_datat->GetXaxis()->SetRangeUser(startit_CR,endit);
	 control_MCt->GetXaxis()->SetRangeUser(startit_CR,endit);
	 signal_MCt->GetYaxis()->SetRangeUser(0.9,6000000);
	 signal_MCt->SetXTitle("Dijet mass [TeV]");
	 signal_MCt->SetYTitle("Events/bin");
	 signal_MCt->GetYaxis()->SetTitleOffset(1.6);
	 c1->SetLogy(1);
         signal_MCt->GetXaxis()->SetLabelSize(0.05);
         signal_MCt->GetYaxis()->SetLabelSize(0.05); 
         signal_MCt->GetXaxis()->SetTitleSize(0.05);
         signal_MCt->GetYaxis()->SetTitleSize(0.05);       
         signal_MCt->GetXaxis()->SetTitleFont(42);
         signal_MCt->GetYaxis()->SetTitleFont(42);        
	 signal_MCt->GetXaxis()->SetTitleOffset(1.2); 
         signal_MCt->GetYaxis()->SetTitleOffset(1.3);

/*
	 signal_MCt->SetMinimum(0.05); 
	 signal_MCt->Draw("hist ][");
         signal_datat->SetMarkerSize(0.7); 
	 signal_datat->Draw("e same"); // e0
 	 control_datat->Draw("e same");
	 control_middle_datat->Draw("e same");
	 control_MCt->Draw("hist ][ same");
	 control_middle_MCt->Draw("hist ][ same");
*/

         signal_MCt->SetMinimum(0.05);
         signal_MCt->Draw("hist ][");
         signal_datap->SetMarkerSize(0.7);
         signal_datap->Draw("e0 same");
         control_datap->Draw("e same");
         control_middle_datap->Draw("e same");
         control_MCt->Draw("hist ][ same");
         control_middle_MCt->Draw("hist ][ same");
         leg->Draw("same");

         TLatex *l = new TLatex();
         l->SetTextAlign(11);
   	 l->SetTextSize(0.045);
     	 l->SetNDC();
    	 l->SetTextFont(62);
         l->DrawLatex(0.19,0.88,"CMS");
//       l->DrawLatex(0.16,0.96,"CMS #it{Preliminary}");
         l->SetTextFont(52);
         l->SetTextFont(42);
         l->DrawLatex(0.66,0.96,"137 fb^{-1} (13 TeV)");

         l->SetTextSize(0.035);
         l->SetTextFont(42);
         l->DrawLatex(0.21,0.18,"SR: |#Delta#eta| < 1.1");
         l->SetTextFont(42);
         l->DrawLatex(0.21,0.24,"CR_{middle}: 1.1 <  |#Delta#eta| < 1.5");
         l->SetTextFont(42);
         l->DrawLatex(0.21,0.30,"CR_{high}: 1.5 < |#Delta#eta| < 2.6");
         paveCMS2->Draw("same"); 

        c1->SaveAs("Superimposed_SR_CRmiddle_CRhigh_16v11_17v6_18v10_merged.png");
        c1->SaveAs("Superimposed_SR_CRmiddle_CRhigh_16v11_17v6_18v10_merged.pdf");


}
