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

 #include "TGraphErrors.h"
 #include "TGraph2DErrors.h"
 #include "TCanvas.h"
 #include "TF2.h"
 #include "TH1.h"
 #include "TVirtualFitter.h"


#include "setTDRStyle_teliko.C"

void Plot_Ratio_Method_Prediction_new_version(){

         double lumi = 137500;
         double startit = 2438; // 2.438
         double endit = 8752; // 8.752
         double Fit_startit = 2438; // 2.428
         double Fit_endit = 8752;  //8.752
         gROOT->LoadMacro("setTDRStyle_teliko.C");
         setTDRStyle_teliko();
	  
         TPaveText *paveCMS = new TPaveText(0.16,0.96,0.96,0.99,"NDC");
         paveCMS->AddText("CMS Preliminary    #sqrt{s} = 13 TeV       L = 77.75 fb^{-1}");
         paveCMS->SetFillColor(0);
         paveCMS->SetBorderSize(0);
         paveCMS->SetTextSize(0.06);


     double massBoundaries[103] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};


//	char *image_name = "_2016_2017_ax3_no_zeros_new_version3";
        char *image_name = "_2016_2017_ax3_no_zeros_new_version4";

    TFile *f= new TFile("../inputs/Double_sideband_prediction_16AugV11_17v6_18v10_SR_Scale.root");
    TFile *f2 = new TFile("../inputs/double_sideband_Powheg_16_17_18_merged.root");

	TH1D *h_ratio_MC_Powheg = (TH1D*)(f2->Get("h_ratio_MC"));
    h_ratio_MC_Powheg->SetName("h_ratio_MC_Powheg");

	TH1D *h_ratio_MC = (TH1D*)(f->Get("h_ratio_MC"));
	//TH1D *h_ratio_MC = (TH1D*)(f->Get("h_ratio_MC_middle"));
	TH1D *h_ratio_Data = (TH1D*)(f->Get("h_ratio_Data"));
	TH1D *h_Double_ratio = (TH1D*)(h_ratio_MC->Clone());
	
	TH1D *signal_data  = (TH1D*)(f->Get("h_mjj"));
	TH1D *h_mjj_middle  = (TH1D*)(f->Get("h_mjj_middle"));

	TH1D *h_mjj_high = (TH1D*)(f->Get("h_mjj_high"));
	TH1D *prediction   = (TH1D*)(f->Get("h_mjj_prediction"));
	TH1D *pull = (TH1D*)(signal_data->Clone());

	h_ratio_Data->Divide(signal_data,h_mjj_high);
	//h_ratio_Data->Divide(h_mjj_middle,h_mjj_high);
	h_Double_ratio->Divide(h_ratio_Data,h_ratio_MC);

	signal_data->SetMarkerStyle(8);
	signal_data->SetLineColor(1);
	signal_data->SetMarkerColor(1);
	signal_data->GetXaxis()->SetRangeUser(startit,endit);

	//rescaling prediction and data to the differential cross section
	for(int i=0; i<prediction->GetNbinsX(); i++)
	 {
	// h_mjj->SetBinContent(i,1000*h_mjj->GetBinContent(i)/((h_mjj->GetBinLowEdge(i+1)-h_mjj->GetBinLowEdge(i))*lumi));
		prediction->SetBinContent(i,1000*prediction->GetBinContent(i)/((prediction->GetBinLowEdge(i+1)-prediction->GetBinLowEdge(i))*lumi));
		prediction->SetBinError(i,1000*prediction->GetBinError(i)/((prediction->GetBinLowEdge(i+1)-prediction->GetBinLowEdge(i))*lumi));
		if (signal_data->GetBinContent(i)==0) signal_data->SetBinError(i,1.); //poissonian error of zero content
		signal_data->SetBinContent(i,1000*signal_data->GetBinContent(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));
		signal_data->SetBinError(i,1000*signal_data->GetBinError(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));
	//cout << h_mjj_2016->GetBinLowEdge(i+1)-h_mjj_2016->GetBinLowEdge(i) << endl;
	 }
	
		//creating wpulls and calculate chi square: 
	 double chi_square = 0;
	 int NDF =0;	  
		
	for(Int_t i=0;i<signal_data->GetNbinsX();i++)
	 {

		double edata_signal   = signal_data->GetBinError(i); 
	   //if (edata_signal==0) edata_signal = 1000*1.7/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
		double edata_control  = h_mjj_high->GetBinError(i);
		double data_signal    = signal_data->GetBinContent(i);
		double mjj   	 = signal_data->GetBinCenter(i);
		double pred   = prediction->GetBinContent(i);
		double eRM     	 = prediction->GetBinError(i);
		double RM_tot_error   = sqrt(edata_signal*edata_signal + eRM*eRM);
	    if(edata_signal>0)
		 {
			pull->SetBinContent(i,(-pred+data_signal)/RM_tot_error);
			if(mjj>startit && mjj< endit )
			 {
				chi_square = chi_square + pull->GetBinContent(i)*pull->GetBinContent(i);
				NDF= NDF +1 ;
				//cout << " pred = "<<pred <<"  data = "<< data_signal<<" chi_square = " << chi_square << endl;
			 }
		 }
	 } 

	//rescaling CR data to the differential cross section
	for(int i=0; i<h_mjj_high->GetNbinsX(); i++)
	{
	// h_mjj->SetBinContent(i,1000*h_mjj->GetBinContent(i)/((h_mjj->GetBinLowEdge(i+1)-h_mjj->GetBinLowEdge(i))*lumi));
		h_mjj_high->SetBinContent(i,1000*h_mjj_high->GetBinContent(i)/((h_mjj_high->GetBinLowEdge(i+1)-h_mjj_high->GetBinLowEdge(i))*lumi));
		h_mjj_high->SetBinError(i,1000*h_mjj_high->GetBinError(i)/((h_mjj_high->GetBinLowEdge(i+1)-h_mjj_high->GetBinLowEdge(i))*lumi));		
	//cout << h_mjj_2016->GetBinLowEdge(i+1)-h_mjj_2016->GetBinLowEdge(i) << endl;
	}


	TPaveText *paveCMS2 = new TPaveText(0.2,0.03,0.5,0.28,"NDC");
        paveCMS2->SetFillColor(0);
	paveCMS2->SetBorderSize(0);
	paveCMS2->SetFillStyle(0);
	paveCMS2->SetTextFont(42);
	paveCMS2->SetTextSize(0.045);
	paveCMS2->SetTextAlign(11);
	Char_t pave1[1024];
	sprintf(pave1,"#chi^{2}/ndf = %3.2f / %3.2i ",chi_square,NDF);   
	paveCMS2->AddText(pave1);
	paveCMS2->AddText("Wide PF-jets"); 
	Char_t pave[1024];
	sprintf(pave,"m_{jj} > %3.2f TeV",startit/1000.);   
	paveCMS2->AddText(pave);
	paveCMS2->AddText("|#eta| < 2.5, |#Delta#eta| < 1.1");

	TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
	leg->AddEntry(signal_data,   "Data ","p");
	leg->AddEntry(prediction,  "Background ","l");
	leg->SetTextSize(0.05);

	prediction->SetLineColor(2);
	prediction->SetMarkerColor(2);
	prediction->GetXaxis()->SetRangeUser(startit,endit);
	prediction->GetYaxis()->SetRangeUser(0.000015,50.);

	pull->SetLineColor(2);
	pull->SetMarkerColor(2);
	pull->GetXaxis()->SetRangeUser(startit,endit);
	pull->GetYaxis()->SetRangeUser(-4.5,4.5);
	 
	TCanvas *c1 = new TCanvas("c1","Signal region Data &Prediction",600,700);
	c1->Divide(1,2,0,0,0);
	//TPad *pad1r = new TPad("pad1r","pad1r",0,0.4,1,1); 
	TVirtualPad *pad1r; 
	pad1r = c1->GetPad(1);
	pad1r->SetPad(0.01,0.37,0.99,0.98);
	pad1r->SetRightMargin(0.05);
	pad1r->SetTopMargin(0.05);
	pad1r->SetLeftMargin(0.175);
	pad1r->SetFillColor(0);
	pad1r->SetBorderMode(0);
	pad1r->SetFrameFillStyle(0);
	pad1r->SetFrameBorderMode(0);
	//pad1r->SetBottomMargin(0);
	pad1r->Draw();
	pad1r->cd();
	pad1r->cd()->SetLogy(1);
	pad1r->cd()->SetLogx(1);
	prediction->SetYTitle("d#sigma/dm_{jj} [pb/TeV]");
	//prediction->SetXTitle("M_{jj} (GeV)");
	prediction->GetYaxis()->SetTitleSize(0.07);
	prediction->GetYaxis()->SetLabelSize(0.05);
	//c1->SetLogy(1);
	prediction->SetFillColor(0); 
	prediction->SetLineWidth(2);
	prediction->SetLineColor(2);
	prediction->Draw("l hist");
        leg->Draw("same");
	signal_data->Draw("same e");
        //leg->Draw("same"); 
	paveCMS->Draw("same");
	//paveCMS2->Draw("same");
	c1->cd();

	TVirtualPad *pad2r ;
	pad2r = c1->GetPad(2);
	pad2r->SetLeftMargin(0.175);
	pad2r->SetPad(0.01,0.02,0.99,0.37);
	pad2r->SetBottomMargin(0.35);
	pad2r->SetRightMargin(0.05);
	pad2r->Draw();
	pad2r->cd(); 
	pad2r->cd()->SetLogx(1);
	pad2r->SetGridx();
	pad2r->SetGridy();

	pull->GetXaxis()->SetTitle("Dijet mass [TeV]");
	pull->GetXaxis()->SetNoExponent();
	pull->GetXaxis()->SetMoreLogLabels();
	pull->GetXaxis()->SetTitleSize(2*0.06);
	pull->GetYaxis()->SetTitleSize(2*0.06);
	pull->GetXaxis()->SetLabelSize(2*0.07);
	pull->GetYaxis()->SetLabelSize(0.09);
	pull->GetXaxis()->SetLabelOffset(1000);
	//pull->GetYaxis()->SetLabelOffset(1000);
	pull->GetXaxis()->SetTitleOffset(1.2);
	pull->GetYaxis()->SetTitleOffset(0.6);
	pull->GetYaxis()->SetNdivisions(210);
	pull->SetLineWidth(1);

	TLine *sk = new TLine(startit,0.,endit,0.);
	pull->SetYTitle("#frac{(Data-Prediction)}{Uncertainty}"); 
	pull->SetFillColor(2);
	pull->Draw("HIST");


	TLatex *xLab = new TLatex();
	xLab->SetTextAlign(22);
	xLab->SetTextFont(42);
	xLab->SetTextSize(2*0.05);
	xLab->DrawLatex(3000, -5.1, "3");
	xLab->DrawLatex(4000, -5.1, "4");
	xLab->DrawLatex(5000, -5.1, "5");
	xLab->DrawLatex(6000, -5.1, "6");
	xLab->DrawLatex(7000, -5.1, "7");
	xLab->DrawLatex(8000, -5.1, "8");
	sk->Draw("same");

	char Pred_pdf[300];
        strcpy(Pred_pdf,"Double_sideband_Prediction");
///afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/pdf/Double_sideband_Prediction");
        strcat(Pred_pdf,image_name);
//        strcat(Pred_pdf,"_pas.pdf");
	strcat(Pred_pdf,".pdf");

        char Pred_png[300];
        strcpy(Pred_png,"Double_sideband_Prediction");
///afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/png/Double_sideband_Prediction");
        strcat(Pred_png,image_name);
//        strcat(Pred_png,"_pas.png");
        strcat(Pred_png,".png");
      
        //c1->SaveAs(Pred_pdf);
        //c1->SaveAs(Pred_png);


	//creating and plotting Double Ratio
 
	TF1 *pol = new TF1("pol","[0] + [1]*pow(x/13000,3)",startit,endit);
	pol->SetLineColor(4);
	TCanvas *c7 = new TCanvas("c7","  ",600,700);
	h_Double_ratio->Fit("pol","","",Fit_startit,Fit_endit);
	pol->SetLineWidth(2);
	c7->Close();
	cout << " x^2 / NDF = " << pol->GetChisquare() << " / " << pol->GetNDF() << endl;
	double p0 = pol->GetParameter(0);
	double ep0 = pol->GetParError(0);
	double p1 = pol->GetParameter(1);
	double ep1 = pol->GetParError(1);
		//calculate chi square for Double Ratio Fit
	chi_square = 0;
	NDF=-2;

	for(Int_t i=1;i<=signal_data->GetNbinsX();i++)
	 {
		double edata_signal   = h_Double_ratio->GetBinError(i); 
		double data_signal    = h_Double_ratio->GetBinContent(i);
		double mjj  		  = h_Double_ratio->GetBinCenter(i);
		double pred   = pol->Eval(mjj);
	    if(edata_signal>0)
		{
			pull->SetBinContent(i,(-pred+data_signal)/edata_signal);
			if(mjj>Fit_startit && mjj< Fit_endit )
			{
				chi_square = chi_square + pow((-pred+data_signal)/edata_signal,2);
				NDF= NDF +1 ;
				//cout << " mjj = " << mjj <<" pred = "<<pred <<"  data = "<< data_signal<<" chi_square = " << chi_square << " ndf = "<<NDF << endl;
			}
		}
	 }

    TH1D *hint            = new TH1D("hint","Fit with .68 conf.band",102,massBoundaries);
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint,0.95);
    //Now the "hint" histogram has the fitted function values as the
    //bin contents and the confidence intervals as bin errors
    hint->Print();
    hint->SetStats(kFALSE);
    hint->SetFillColor(kBlue-10);
    hint->SetMarkerColor(kBlue-10);
    hint->SetMarkerSize(0.001);

	TH1D *h_ratio_MC_Pythia_corrected = (TH1D*)(h_ratio_MC->Clone());

	TF1 *pol_mid = new TF1("pol_mid","[0] + [1]*pow(x/13000,3)",startit,endit); //defining the correction from CR-middle
//	pol_mid->SetParameter(0,0.987);
//	pol_mid->SetParameter(1,4.63);

        pol_mid->SetParameter(0,0.977);
        pol_mid->SetParameter(1,2.07);

        TF1 *EW_mid = new TF1("pol_EW","[0] + [1]*pow(x/13000,3)",startit,endit); //defining the correction          
//        pol_EW->SetParameter(0,0.977);
//        pol_EW->SetParameter(1,0.9);

         pol_EW->SetParameter(0,0.97);
         pol_EW->SetParameter(1,2.0);

		//creating corrected Pythia from CR-middle
	for (int i =52; i<h_ratio_MC->GetNbinsX(); i++)
	 {
		double mjj = h_ratio_MC->GetBinCenter(i);
		double r   = h_ratio_MC->GetBinContent(i);
		double er  = h_ratio_MC->GetBinError(i);
		h_ratio_MC_Pythia_corrected->SetBinContent(i,r*pol_mid->Eval(mjj));	
		h_ratio_MC_Pythia_corrected->SetBinError(i,er*pol_mid->Eval(mjj));
	 }

	//creating and fitting double ratios of Powheg and Pythia-corrected


	TH1D *h_Double_ratio_Powheg = (TH1D*)(h_ratio_MC->Clone());
	TH1D *h_Double_ratio_Pythia_corrected = (TH1D*)(h_ratio_MC->Clone());

	h_Double_ratio_Powheg->Divide(h_ratio_MC_Powheg,h_ratio_MC);
	h_Double_ratio_Pythia_corrected->Divide(h_ratio_MC_Pythia_corrected,h_ratio_MC);

	TF1 *Dratio_powheg = new TF1("Dratio_powheg","[0]+[1]*pow(x/13000,3)",startit,endit);
	TF1 *Dratio_pythia_cor = new TF1("Dratio_pythia_cor","[0]+[1]*pow(x/13000,3)",startit,endit);

	TCanvas *c2 = new TCanvas("c5","Superimposed Ratios",600,600);
	c2->cd();
	h_Double_ratio_Powheg->Fit("Dratio_powheg");
        cout << " This is the POWHEG FIT " << endl;
	h_Double_ratio_Pythia_corrected->Fit("Dratio_pythia_cor");
        cout << " This is the PYTHIA FIT " << endl;

	c2->Close();

	TH1D *h_ratio_MC_Pythia_corrected_from_Powheg = (TH1D*)(h_ratio_MC->Clone());
        h_ratio_MC_Pythia_corrected_from_Powheg->SetName("h_ratio_MC_Pythia_corrected_from_Powheg");
        TH1D *h_ratio_MC_EW = (TH1D*)(h_ratio_MC->Clone());
        h_ratio_MC_EW->SetName("h_ratio_MC_EW");


		//creating corrected Pythia from Powheg ( this is similar to a smoothed Powheg ratio )
	for (int i =52; i<h_ratio_MC->GetNbinsX(); i++)
	 {
		double mjj = h_ratio_MC->GetBinCenter(i);
		double r   = h_ratio_MC->GetBinContent(i);
		double er  = h_ratio_MC->GetBinError(i);
		h_ratio_MC_Pythia_corrected_from_Powheg->SetBinContent(i,r*Dratio_powheg->Eval(mjj));	
		h_ratio_MC_Pythia_corrected_from_Powheg->SetBinError(i,er*Dratio_powheg->Eval(mjj));
                h_ratio_MC_EW->SetBinContent(i,r*pol_EW->Eval(mjj));
                h_ratio_MC_EW->SetBinError(i,er*pol_EW->Eval(mjj));
	 }


        TPaveText *paveCMS3 = new TPaveText(0.2,0.35,0.5,0.6,"NDC");
        paveCMS3->SetFillColor(0);
        paveCMS3->SetBorderSize(0);
        paveCMS3->SetFillStyle(0);
        paveCMS3->SetTextFont(42);
        paveCMS3->SetTextSize(0.07);
        paveCMS3->SetTextAlign(11);
        paveCMS3->AddText("Wide PF-jets");
        sprintf(pave,"m_{jj} > %3.2f TeV",startit/1000.);
        paveCMS3->AddText(pave);
        paveCMS3->AddText("|#eta| < 2.5");

        TPaveText *paveCMS5 = new TPaveText(2600,0.08,7600,0.4); // 2600 3600 0.2, 0.5
        paveCMS5->SetFillColor(0);
        paveCMS5->SetBorderSize(0);
        paveCMS5->SetFillStyle(0);
        paveCMS5->SetTextFont(42);
        paveCMS5->SetTextSize(0.06);
        paveCMS5->SetTextAlign(11);
        Char_t dratio_pave[1024];
        sprintf(dratio_pave,"Fit: y =(%3.3f #pm %3.3f)+(%3.2f #pm %3.2f) (m_{jj}/13000)^{3}",p0,ep0,p1,ep1);
        paveCMS5->AddText(dratio_pave);
        Char_t pave2[1024];
        sprintf(pave2,"#chi^{2}/ndf = %3.2f / %3.2i ",chi_square,NDF);
        paveCMS5->AddText(pave2);
	
	h_ratio_MC_Powheg->SetLineColor(2);
        h_ratio_MC_EW->SetLineColor(kRed+2);    
        h_ratio_MC_EW->SetLineStyle(kDashed);

	TLegend *leg5 = new TLegend(0.20,0.55,0.9,0.8); // 0.20,0.6,0.68,0.8
	leg5->AddEntry(h_ratio_Data,   "Data ","p");
	leg5->AddEntry(h_ratio_MC,  "QCD PYTHIA","l");
        leg5->AddEntry(h_ratio_MC_EW,  "QCD POWHEG+EW cor.","l");
	leg5->AddEntry(h_ratio_MC_Pythia_corrected,  "QCD PYTHIA corrected","l");
	leg5->SetTextSize(0.055);

        pol_EW->SetLineColor(kRed+2); // EDW EW corrections
        pol_EW->SetLineStyle(kDashed);
        pol_EW->SetLineWidth(0.8);  

	TLegend *leg6 = new TLegend(0.20,0.65,0.9,0.9); // 0.20,0.77,0.68,0.97
	leg6->AddEntry(h_Double_ratio,   "Data ","p");
	leg6->AddEntry(pol,   "Fit (Data) ","l");
        leg6->AddEntry(pol_EW,  "QCD POWHEG+EW cor.","l");
	leg6->AddEntry(Dratio_pythia_cor,  "QCD PYTHIA corrected","l");
	leg6->SetTextSize(0.055);

        TCanvas *c5 = new TCanvas("c5","Signal/Control Ratio",600,700);
        c5->Divide(1,2,0,0,0);
        TVirtualPad *pad3r;
        pad3r = c5->GetPad(1);
        pad3r->SetPad(0.0,0.52,0.99,0.98); // 0.0,05
        TLine *fix = new TLine(2438,0.0151,8752,0.0151);
        pad3r->SetRightMargin(0.05);
        pad3r->SetTopMargin(0.09); // 0.08
        pad3r->SetLeftMargin(0.175);
        pad3r->SetFillColor(0);
        pad3r->SetBorderMode(0);
        pad3r->SetFrameFillStyle(0);
        pad3r->SetFrameBorderMode(0);
        pad3r->Draw();
        pad3r->cd();
        pad3r->SetLogy(1);
	h_ratio_MC->SetLineColor(3); // eDW 
	h_ratio_MC->SetYTitle("SR / CR_{high}");
	h_ratio_MC->GetYaxis()->SetRangeUser(0.015,4.0); // !!! 0.01 1.6 EDW!!!
	h_ratio_MC->GetXaxis()->SetRangeUser(startit,endit);

        h_ratio_MC->GetXaxis()->SetLabelSize(0.09);
        h_ratio_MC->GetYaxis()->SetLabelSize(0.09);
        h_ratio_MC->GetXaxis()->SetTitleSize(0.09); 
        h_ratio_MC->GetYaxis()->SetTitleSize(0.09);
        h_ratio_MC->GetXaxis()->SetTitleFont(42);
        h_ratio_MC->GetYaxis()->SetTitleFont(42);
        h_ratio_MC->GetXaxis()->SetTitleOffset(1.);
        h_ratio_MC->GetYaxis()->SetTitleOffset(1.);

	h_ratio_MC->Draw("hist");
	h_ratio_Data->SetMarkerStyle(8);
	h_ratio_Data->SetLineColor(1);
	h_ratio_Data->SetMarkerColor(1);
        leg5->Draw("same");
	h_ratio_Data->Draw("same p");
	h_ratio_MC_Pythia_corrected->SetLineColor(2); // edw 6
	h_ratio_MC_Pythia_corrected->SetLineStyle(1);
	h_ratio_MC_Pythia_corrected->Draw("same hist");
//	h_ratio_MC_Pythia_corrected_from_Powheg->SetLineColor(2);
//	h_ratio_MC_Pythia_corrected_from_Powheg->SetLineStyle(1);
//	h_ratio_MC_Pythia_corrected_from_Powheg->Draw("same hist");
        h_ratio_MC_EW->Draw("same hist");
	fix->Draw("same");
	//leg5->Draw("same"); 
       
    TLatex *l = new TLatex();
    l->SetTextAlign(11);
    l->SetTextSize(0.08);
    l->SetNDC();
    l->SetTextFont(62);
    l->DrawLatex(0.20,0.82,"CMS");
    l->SetTextFont(52);
    l->SetTextFont(42);
    l->DrawLatex(0.66,0.93,"137 fb^{-1} (13 TeV)");
//      paveCMS->Draw("same");
//      paveCMS3->Draw("same");
        c5->cd();
       TVirtualPad *pad4r ;
        pad4r = c5->GetPad(2);
        pad4r->SetLeftMargin(0.175);
        pad4r->SetPad(0.0,0.02,0.99,0.50);
        pad4r->SetBottomMargin(0.19); // 0.35 // 0.2
        pad4r->SetRightMargin(0.05);
        pad4r->Draw();
        pad4r->cd();
        pad4r->SetLogy(1); // here!!

	h_Double_ratio->SetMarkerStyle(8);
	h_Double_ratio->SetLineColor(1);
	h_Double_ratio->SetMarkerColor(1);
	h_Double_ratio->GetXaxis()->SetRangeUser(startit,endit);
	h_Double_ratio->GetYaxis()->SetRangeUser(0.01,1.99);

        h_Double_ratio->GetXaxis()->SetLabelSize(0.09);
        h_Double_ratio->GetYaxis()->SetLabelSize(0.09);
        h_Double_ratio->GetXaxis()->SetTitleSize(0.09);
        h_Double_ratio->GetYaxis()->SetTitleSize(0.09);
        h_Double_ratio->GetXaxis()->SetTitleFont(42);
        h_Double_ratio->GetYaxis()->SetTitleFont(42);
        h_Double_ratio->GetXaxis()->SetTitleOffset(1.);
        h_Double_ratio->GetYaxis()->SetTitleOffset(1.);
        h_Double_ratio->GetYaxis()->SetRangeUser(0.5,22.5); // EDW !!! 0.5,9.5
	h_Double_ratio->Draw("p");

        hint->Draw("E3 same");
        leg6->Draw("same");
        h_Double_ratio->Draw("p same");

        cout << " First bin low edgw " << h_Double_ratio->GetBinLowEdge(57) << endl;
        cout << " Double Ratio First Bin is " << h_Double_ratio->GetBinContent(57) << endl;
	h_Double_ratio->GetXaxis()->SetTitle("Dijet mass [TeV]");
	h_Double_ratio->GetYaxis()->SetTitle("Ratio to PYTHIA");
	h_Double_ratio->GetXaxis()->SetNoExponent();   
	h_Double_ratio->GetXaxis()->SetMoreLogLabels();
	h_Double_ratio->GetXaxis()->SetLabelOffset(1000);
        TLatex *xLab = new TLatex();
        xLab->SetTextAlign(22);
        xLab->SetTextFont(42);
        xLab->SetTextSize(0.09);
        xLab->DrawLatex(3000, 0.4, "3"); // -0.073
        xLab->DrawLatex(4000, 0.4, "4"); 
        xLab->DrawLatex(5000, 0.4, "5"); 
        xLab->DrawLatex(6000, 0.4, "6"); 
        xLab->DrawLatex(7000, 0.4, "7");
        xLab->DrawLatex(8000, 0.4, "8");     

//	Dratio_powheg->SetLineColor(2);
//	Dratio_powheg->SetLineStyle(1);
//	Dratio_powheg->SetMarkerColor(2);
//	Dratio_powheg->SetMarkerStyle(22);
//	Dratio_powheg->Draw("same l");
	Dratio_pythia_cor->SetLineColor(2); // edw 6
	Dratio_pythia_cor->SetLineStyle(1);
	Dratio_pythia_cor->SetMarkerColor(1); // edw 6
	Dratio_pythia_cor->SetMarkerStyle(33);
	Dratio_pythia_cor->Draw("same l");
        pol_EW->Draw("same l");
	//paveCMS5->Draw("same");
	//leg6->Draw("same");

                char Double_ratio_pdf[300];
        strcpy(Double_ratio_pdf,"Double_ratio");
///afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/pdf/Double_ratio");
        strcat(Double_ratio_pdf,image_name);
//        strcat(Double_ratio_pdf,"_pas.pdf");
        strcat(Double_ratio_pdf,".pdf");
    
        char Double_ratio_png[300];
        strcpy(Double_ratio_png,"Double_ratio");
///afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/png/Double_ratio");
        strcat(Double_ratio_png,image_name);
//        strcat(Double_ratio_png,"_pas.png");
        strcat(Double_ratio_png,".png");

 	 c5->SaveAs(Double_ratio_pdf);
         c5->SaveAs(Double_ratio_png);


}
