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

void Plot_RM_vs_data(){

	 double lumi 	     = 136600;    //35900 for 2016, 41850 for 2017, 77750 for 2016+2017
	 double startit	     = 1530;
	 double endit	     = 8152;
	 double startit_RM   = 2438;

	gROOT->LoadMacro("setTDRStyle_teliko.C");
	setTDRStyle_teliko();
	 //gStyle->SetOptFit(1111);
	  
	double qq_6TeV_obs_limit = 0.00064;
	double qg_4TeV_obs_limit = 0.01127;
	double gg_2TeV_obs_limit = 0.17866;
	 
	 //ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 20000);   //set the number of parameter searches for convergence

	char *image_name = "_16_17_18_ticks_added";

//	TFile *f_RM= new TFile("../output_root_files/Double_sideband_Prediction_2016_2017_ax4_middle_no_zeros.root");
	TFile *f_RM= new TFile("/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/output_root_files/Double_sideband_prediction_16_17_18_JECresidual_preliminary_middle_phiHEM_ax3.root");

//	TFile *f_SF= new TFile("../output_root_files/DijetFitResult_deta_1p1.root");
	TFile *f_SF= new TFile("/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/Data2018_results/DijetFitResult_16_17_18_HEMphi.root");

	

	//TFile *f_SF= new TFile("Ratio_Method_Prediction_pol2_2016_2017_mjj2438_MC2017.root");

	double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

	TFile *f_qq= new TFile("/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/output_root_files/ResonanceShapes_qq_13TeV_Spring16.root");
	TH1D *shape_qq_6TeV  = (TH1D*)(f_qq->Get("h_qq_6000"));   //obs limit at 6TeV:   0.00064
	shape_qq_6TeV->Scale(qq_6TeV_obs_limit*lumi);  //scale to events

	TFile *f_qg= new TFile("/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/output_root_files/ResonanceShapes_qg_13TeV_Spring16.root");
	TH1D *shape_qg_4TeV  = (TH1D*)(f_qg->Get("h_qg_4000"));  //obs limit at 4TeV:  0.01127
	shape_qg_4TeV->Scale(qg_4TeV_obs_limit*lumi);

	TFile *f_gg= new TFile("/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/output_root_files/ResonanceShapes_gg_13TeV_Spring16.root");
	TH1D *shape_gg_2TeV  = (TH1D*)(f_gg->Get("h_gg_2000"));   //obs limit at 2TeV: =0.17866
	shape_gg_2TeV->Scale(gg_2TeV_obs_limit*lumi);
	  
	TH1D *Standard_Fit 	          = new TH1D("Standard_Fit","Standard_Fit",103,massBoundaries);  
	TH1D *shape_qq_binned 	      = new TH1D("shape_qq_binned","shape_qq_binned",103,massBoundaries);  
	TH1D *shape_qg_binned 	      = new TH1D("shape_qg_binned","shape_qg_binned",103,massBoundaries);  
	TH1D *shape_gg_binned 	      = new TH1D("shape_gg_binned","shape_gg_binned",103,massBoundaries);  
	TH1D *Standard_fit_pull_1D 	  = new TH1D("Standard_fit_pull_1D","Standard Fit Pulls",12,-4,4);  
	TH1D *Ratio_Method_pull_1D 	  = new TH1D("Ratio_Method_pull_1D","Ratio Method Pulls",9,-3,3);  
	TH1D *signal_data  	     	  = (TH1D*)(f_RM->Get("h_mjj"));
	TH1D *signal_data_1GeVbin     = (TH1D*)(f_RM->Get("h_mjj_1GeVbin"));
	TH1D *h_mjj_high	     	  = (TH1D*)(f_RM->Get("h_mjj_high"));
	TH1D *Ratio_Method  	      = (TH1D*)(f_RM->Get("h_mjj_prediction"));
	TH1D *Prediction_Ratio        = (TH1D*)(Ratio_Method->Clone());
	Prediction_Ratio->SetName("Prediction_Ratio");
	TH1D *Standard_Fit_unbinned   = (TH1D*)(f_SF->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
	//TH1D *Standard_Fit   = (TH1D*)(f_SF->Get("h_mjj_prediction"));  //This was just to compare two different versions of ratio method 
	TH1D *pull_SF        	      = (TH1D*)(signal_data->Clone());
	TH1D *pull_RM  		      	  = (TH1D*)(signal_data->Clone());
	TH1D *pull_qq        	      = (TH1D*)(Standard_Fit->Clone());
	TH1D *pull_qg        	      = (TH1D*)(Standard_Fit->Clone());
	TH1D *pull_gg        	      = (TH1D*)(Standard_Fit->Clone());
	TH1D *Blank       	      	  = (TH1D*)(Ratio_Method ->Clone());

	signal_data->SetMarkerStyle(8);
	signal_data->SetLineColor(1);
	signal_data->SetMarkerColor(1);
	signal_data->GetXaxis()->SetRangeUser(startit,endit);
	Blank->SetMarkerColor(0); 		 //use this white-empty histogram to add blank entries on legend.
	Blank->SetLineColor(0);

	//rebinning 1GeV Standard Fit to standard binning
	for(int i=0; i<Standard_Fit_unbinned->GetNbinsX(); i++)
	 {
		double val  = Standard_Fit_unbinned->GetBinContent(i);
		double xval  = Standard_Fit_unbinned->GetBinCenter(i);
		Standard_Fit->Fill(xval,val);

	 }

	//rebinning 1GeV qq shape to standard binning
	for(int i=0; i<shape_qq_6TeV->GetNbinsX(); i++)
	 {
		double val  = shape_qq_6TeV->GetBinContent(i);
		double xval  = shape_qq_6TeV->GetBinCenter(i);
		shape_qq_binned->Fill(xval,val);		
	 }

	//rebinning 1GeV qg shape to standard binning
	for(int i=0; i<shape_qg_4TeV->GetNbinsX(); i++)
	 {
		double val  = shape_qg_4TeV->GetBinContent(i);
		double xval  = shape_qg_4TeV->GetBinCenter(i);
		shape_qg_binned->Fill(xval,val);
	 }

	//rebinning 1GeV gg shape to standard binning
	for(int i=0; i<shape_gg_2TeV->GetNbinsX(); i++)
	 {
		double val  = shape_gg_2TeV->GetBinContent(i);
		double xval  = shape_gg_2TeV->GetBinCenter(i);
		shape_gg_binned->Fill(xval,val);
     }



	//rescaling prediction, standard fit and data to the differential cross section
	for(int i=0; i<Standard_Fit->GetNbinsX(); i++)
	 {
		//cout <<" mass = " << Standard_Fit->GetBinCenter(i) << " Fit = " << Standard_Fit->GetBinContent(i)<< "  Data = "<< signal_data->GetBinContent(i) <<endl;
		Standard_Fit->SetBinContent(i,1000*Standard_Fit->GetBinContent(i)/((Standard_Fit->GetBinLowEdge(i+1)-Standard_Fit->GetBinLowEdge(i))*lumi));
		Standard_Fit->SetBinError(i,1000*Standard_Fit->GetBinError(i)/((Standard_Fit->GetBinLowEdge(i+1)-Standard_Fit->GetBinLowEdge(i))*lumi));
		Ratio_Method->SetBinContent(i,1000*Ratio_Method->GetBinContent(i)/((Ratio_Method->GetBinLowEdge(i+1)-Ratio_Method->GetBinLowEdge(i))*lumi));
		Ratio_Method->SetBinError(i,1000*Ratio_Method->GetBinError(i)/((Ratio_Method->GetBinLowEdge(i+1)-Ratio_Method->GetBinLowEdge(i))*lumi));
		if (signal_data->GetBinContent(i) < 20) signal_data->SetBinError(i, 0.5 + sqrt( signal_data->GetBinContent(i) + 0.25 ) ); 
	//	if (signal_data->GetBinContent(i)==0) signal_data->SetBinError(i,1.);
		signal_data->SetBinContent(i,1000*signal_data->GetBinContent(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));
		signal_data->SetBinError(i,1000*signal_data->GetBinError(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));
		shape_gg_binned->SetBinContent(i,1000*shape_gg_binned->GetBinContent(i)/((shape_gg_binned->GetBinLowEdge(i+1)-shape_gg_binned->GetBinLowEdge(i))*lumi));
		shape_qg_binned->SetBinContent(i,1000*shape_qg_binned->GetBinContent(i)/((shape_qg_binned->GetBinLowEdge(i+1)-shape_qg_binned->GetBinLowEdge(i))*lumi));
		shape_qq_binned->SetBinContent(i,1000*shape_qq_binned->GetBinContent(i)/((shape_qq_binned->GetBinLowEdge(i+1)-shape_qq_binned->GetBinLowEdge(i))*lumi));
		//cout << " RM : " << Ratio_Method->Interpolate(2900) << " data : " << signal_data->Interpolate(2900) << endl; 
	 }

	//creating Prediction ratio with correct errors
	for (int i=0; i<Ratio_Method->GetNbinsX(); i++)
	 { 		
		if(Ratio_Method->GetBinContent(i)>0)
		 {
			double mjj = Ratio_Method->GetBinCenter(i);
			double sr  = Ratio_Method->GetBinContent(i);
			double esr = Ratio_Method->GetBinError(i);
			double cr  = Standard_Fit->GetBinContent(i);
			double ecr = 0;
			if(cr>0)
			 {
				Prediction_Ratio->SetBinContent(i,sr/cr);
				Prediction_Ratio->SetBinError(i, sqrt( pow(esr/cr,2) + pow(sr*ecr/(cr*cr),2) ) );
			 }
		 }
	 }
	
		//creating pulls and calculate chi square for the two methods: 
	 double chi_square_SF = 0;
	 int    NDF_SF        =-4;  // four parameter function is used for Standard Fit	  
	 double chi_square_RM = 0;
	 int	NDF_RM 	      = 0;  //  linear Fit parametrization for Ratio Method   
		
	for(Int_t i=1;i<=signal_data->GetNbinsX();i++)
	 {
		double edata_signal   = signal_data->GetBinError(i); 
  		double eRM 			  = Ratio_Method->GetBinError(i);
		double data_signal    = signal_data->GetBinContent(i);
		double mjj   	      = signal_data->GetBinCenter(i);
		double SF             = Standard_Fit->GetBinContent(i);
		double RM             = Ratio_Method->GetBinContent(i);
		double RM_tot_error   = sqrt(edata_signal*edata_signal + eRM*eRM);
		double gg		 	  = shape_gg_binned->GetBinContent(i);
		double qg			  = shape_qg_binned->GetBinContent(i);
		double qq		 	  = shape_qq_binned->GetBinContent(i);
		if(edata_signal>0)
		 { 
			pull_SF->SetBinContent(i,0);
			pull_SF->SetBinContent(i,(-SF+data_signal)/edata_signal);
			if (mjj> startit_RM) pull_RM->SetBinContent(i,(-RM+data_signal)/RM_tot_error);
			else pull_RM->SetBinContent(i,0);
			pull_qg->SetBinContent(i,qg/RM_tot_error);
			pull_gg->SetBinContent(i,gg/edata_signal); // at 2 TeV the error on the pulls come from the Standard fit
			pull_qq->SetBinContent(i,qq/RM_tot_error);
			//pull_qg->SetBinContent(i,qg/edata_signal);
			//pull_gg->SetBinContent(i,gg/edata_signal);
			//pull_qq->SetBinContent(i,qq/edata_signal);
			if(mjj>=startit && mjj<= endit )
			 {	
				Standard_fit_pull_1D->Fill(pull_SF->GetBinContent(i));
				chi_square_SF = chi_square_SF + pull_SF->GetBinContent(i)*pull_SF->GetBinContent(i);
				NDF_SF        = NDF_SF + 1 ;
			 }
			if(mjj>=startit_RM && mjj<= endit)
			 {	
				Ratio_Method_pull_1D->Fill(pull_RM->GetBinContent(i));
				chi_square_RM = chi_square_RM + pull_RM->GetBinContent(i)*pull_RM->GetBinContent(i);
				NDF_RM        = NDF_RM + 1 ;
			 }
		 }
		else pull_RM->SetBinContent(i,0);
	
		cout << "Bin = " << i << ",   Mjj " << mjj << "  pred  " << RM <<",   pull = "  << pull_RM->GetBinContent(i) << ",  pull^2 ="  << pull_RM->GetBinContent(i)*pull_RM->GetBinContent(i) <<",   Total x^2 = " << chi_square_RM << endl;

	 } 


	//rescaling CR data to the differential cross section
	for(int i=0; i<h_mjj_high->GetNbinsX(); i++)
	 {
		h_mjj_high->SetBinContent(i,1000*h_mjj_high->GetBinContent(i)/((h_mjj_high->GetBinLowEdge(i+1)-h_mjj_high->GetBinLowEdge(i))*lumi));
		h_mjj_high->SetBinError(i,1000*h_mjj_high->GetBinError(i)/((h_mjj_high->GetBinLowEdge(i+1)-h_mjj_high->GetBinLowEdge(i))*lumi));
	 }

		//rescale signal shapes to xsec / TeV 

	shape_qq_6TeV->Scale(1000/lumi);
	shape_qg_4TeV->Scale(1000/lumi);
	shape_gg_2TeV->Scale(1000/lumi);

	TPaveText *paveCMS = new TPaveText(0.16,0.96,0.96,0.99,"NDC");
	paveCMS->AddText("CMS Preliminary    #sqrt{s} = 13 TeV       L = 136.6 fb^{-1}");
	paveCMS->SetFillColor(0);
	paveCMS->SetBorderSize(0);
	paveCMS->SetTextSize(0.04);

	TPaveText *paveCMS2 = new TPaveText(0.2,0.03,0.5,0.28,"NDC");
	paveCMS2->SetFillColor(0);
	paveCMS2->SetBorderSize(0);
	paveCMS2->SetFillStyle(0);
	paveCMS2->SetTextFont(42);
	paveCMS2->SetTextSize(0.045);
	paveCMS2->SetTextAlign(11);
//	Char_t pave1[1024];
//	sprintf(pave1,"#chi^{2}/ndf = %3.2f / %3.2i ",chi_square,NDF-1);   
//	paveCMS2->AddText(pave1);
	paveCMS2->AddText("Wide PF-jets"); 
	Char_t pave[1024];
	sprintf(pave,"m_{jj} > %3.2f TeV",startit/1000.);   
	paveCMS2->AddText(pave);
	paveCMS2->AddText("|#eta| < 2.5, |#Delta#eta| < 1.1");
	Char_t chi_sq_SF[1024];
	sprintf(chi_sq_SF,"#chi^{2}/NDF = %3.2f / %3.2i ",chi_square_SF, NDF_SF);   
	Char_t chi_sq_RM[1024];
	sprintf(chi_sq_RM,"#chi^{2}/NDF = %3.2f / %3.2i ",chi_square_RM, NDF_RM); 
	shape_gg_2TeV->SetLineColor(4);
	shape_gg_2TeV->GetXaxis()->SetRangeUser(1600,2500);
	shape_gg_2TeV->SetLineStyle(7);
	pull_gg->GetXaxis()->SetRangeUser(1600,2500);
	pull_gg->SetLineStyle(7);
	pull_gg->SetLineColor(4);	
	shape_qg_4TeV->SetLineColor(7);
	shape_qg_4TeV->GetXaxis()->SetRangeUser(3000,5000);
	shape_qg_4TeV->SetLineStyle(7);
	pull_qg->GetXaxis()->SetRangeUser(3000,5000);
	pull_qg->SetLineStyle(7);
	pull_qg->SetLineColor(7);	
	shape_qq_6TeV->SetLineColor(6);
	shape_qq_6TeV->GetXaxis()->SetRangeUser(4500,7000);
 	shape_qq_6TeV->SetLineStyle(7);
	pull_qq->GetXaxis()->SetRangeUser(4500,7000);
	pull_qq->SetLineStyle(7);
	pull_qq->SetLineColor(6);

	TLegend *leg = new TLegend(0.6,0.5,0.8,0.9);
	leg->AddEntry(signal_data,   "Data ","p");
	leg->AddEntry(Standard_Fit,  "Standard Fit","l");
	leg->AddEntry(Blank,  chi_sq_SF,"p");
	leg->AddEntry(Ratio_Method,  "Background from ratio","p");	
	leg->AddEntry(Blank,  chi_sq_RM,"p"); 
	leg->AddEntry(shape_gg_2TeV,"gg (2.0 TeV)","l");
	leg->AddEntry(shape_qg_4TeV,"qg (4.0 TeV)","l");
	leg->AddEntry(shape_qq_6TeV,"qq (6.0 TeV)","l");
	leg->SetTextSize(0.04);

	Standard_Fit->SetLineColor(2);
	Standard_Fit->SetMarkerColor(2);
	Standard_Fit->GetXaxis()->SetRangeUser(startit,endit);
	Standard_Fit->GetYaxis()->SetRangeUser(0.000015,5000.);

	Ratio_Method->SetLineColor(8);
	Ratio_Method->SetMarkerStyle(25);	//square frame
	Ratio_Method->SetMarkerColor(8);
	Ratio_Method->GetXaxis()->SetRangeUser(startit_RM,endit);
//	Ratio_Method->GetYaxis()->SetRangeUser(0.000015,5000.);

	pull_SF->SetLineColor(2);
	pull_SF->SetMarkerColor(2);
	pull_SF->GetXaxis()->SetRangeUser(startit,endit);
	pull_SF->GetYaxis()->SetRangeUser(-4.5,4.5);

	pull_RM->SetLineColor(8);
	pull_RM->SetMarkerColor(8);
	pull_RM->GetXaxis()->SetRangeUser(startit,endit);
	pull_RM->GetYaxis()->SetRangeUser(-4.5,4.5);
	      


	TF1 *f_h2_log10_x_axis = new TF1("f_h2_log10_x_axis", "log10(x)", startit, endit);

	TGaxis *b =new TGaxis(startit, 0.000015,endit, 0.000015, "f_h2_log10_x_axis", 509, "BS", 0.0);
	b->SetTickSize(0.04);
	b->SetMoreLogLabels();
	b->SetLabelOffset(1000);

	TGaxis *b_up =new TGaxis(startit, 5000.,endit, 5000., "f_h2_log10_x_axis", 509, "-", 0.0);
	b_up->SetTickSize(0.04);
	b_up->SetMoreLogLabels();
	b_up->SetLabelOffset(1000);


	TGaxis *b_pull =new TGaxis(startit, -4.5,endit, -4.5, "f_h2_log10_x_axis", 509, "BS", 0.0);
	b_pull->SetTickSize(0.04);
	b_pull->SetMoreLogLabels();
	b_pull->SetLabelOffset(1000);

	TGaxis *b_pull_up =new TGaxis(startit, 4.45,endit, 4.45, "f_h2_log10_x_axis", 509, "-", 0.0);
	b_pull_up->SetTickSize(0.05);
	b_pull_up->SetMoreLogLabels();
	b_pull_up->SetLabelOffset(1000);


	TCanvas *c1 = new TCanvas("c1","Signal region Data & Prediction",600,700);
	 //TCanvas *c1 = new TCanvas("c1","Signal region Data & Prediction",600,945);
	c1->Divide(1,2,0,0,0);

	
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
	pad1r->Draw();
	pad1r->cd();
	pad1r->cd()->SetLogy(1);
	pad1r->cd()->SetLogx(1);
	Standard_Fit->SetYTitle("d#sigma/dm_{jj} [pb/TeV]");
	Standard_Fit->GetYaxis()->SetTitleSize(0.07);
	Standard_Fit->GetYaxis()->SetLabelSize(0.06);
 	Standard_Fit->GetYaxis()->SetTitleOffset(0.9);
	Standard_Fit->SetFillColor(0); 
	Standard_Fit->SetLineWidth(2);
	Standard_Fit->SetLineColor(2);
	Standard_Fit->Draw("l hist");
	b->Draw("same");
	b_up->Draw("same");
	signal_data->Draw("same e");
	Ratio_Method->Draw("same");
	leg->Draw("same"); 
	paveCMS->Draw("same");
	paveCMS2->Draw("same");
	shape_qq_6TeV->Draw("same hist ][");
	shape_qg_4TeV->Draw("same hist ][");
	shape_gg_2TeV->Draw("same hist ][");
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

	pull_SF->GetXaxis()->SetTitle("Dijet mass [TeV]");
	pull_SF->GetXaxis()->SetNoExponent();
	pull_SF->GetXaxis()->SetMoreLogLabels();
	pull_SF->GetXaxis()->SetTitleSize(2*0.06);
	pull_SF->GetYaxis()->SetTitleSize(2*0.06);
	pull_SF->GetXaxis()->SetLabelSize(2*0.07);
	pull_SF->GetYaxis()->SetLabelSize(0.09);
	pull_SF->GetXaxis()->SetLabelOffset(1000);
//	pull_SF->GetXaxis()->SetTickSize(100);
//	pull_SF->GetXaxis()->SetTickLength(100./(endit-startit));
	//pull->GetYaxis()->SetLabelOffset(1000);
	pull_SF->GetXaxis()->SetTitleOffset(1.2);
	pull_SF->GetYaxis()->SetTitleOffset(0.6);
	pull_SF->GetYaxis()->SetNdivisions(210);
	pull_SF->SetLineWidth(1);


	







	TLine *sk = new TLine(startit,0.,endit,0.);

	pull_SF->SetYTitle("#frac{(Data-Prediction)}{Uncertainty}"); 
	pull_SF->SetFillColor(2);
	pull_SF->Draw("HIST");
	b_pull->Draw("same");
	b_pull_up->Draw("same");
	sk->Draw("same"); 
	pull_RM->SetFillStyle(3244);
	pull_RM->SetFillColor(8);
	//pull_RM->SetFillColorAlpha(8, 0.85);
	pull_RM->SetLineWidth(1);
	pull_RM->Draw("same hist");
	pull_qq->Draw("cxsame");
	pull_gg->Draw("cxsame");
	pull_qg->Draw("cxsame");

	TLatex *xLab = new TLatex();
	xLab->SetTextAlign(22);
	xLab->SetTextFont(42);
	xLab->SetTextSize(2*0.05);         
	xLab->DrawLatex(2000, -5.15, "2");
	xLab->DrawLatex(3000, -5.15, "3");
	xLab->DrawLatex(4000, -5.15, "4");
	xLab->DrawLatex(5000, -5.15, "5");
	xLab->DrawLatex(6000, -5.15, "6");
	xLab->DrawLatex(7000, -5.15, "7");
	xLab->DrawLatex(8000, -5.15, "8");

	char Pred_pdf[300];
	strcpy(Pred_pdf,"/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/pdf/Combined_Background");
	strcat(Pred_pdf,image_name);
	strcat(Pred_pdf,".pdf");

	char Pred_png[300];
	strcpy(Pred_png,"/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/png/Combined_Background");
	strcat(Pred_png,image_name);
	strcat(Pred_png,".png");
  
//	c1->SaveAs(Pred_pdf);
//	c1->SaveAs(Pred_png);

/*

	TCanvas *c2 = new TCanvas("c2","Signal region Data & Prediction",600,700);
	c2->cd();
	TLine *sk3 = new TLine(startit_RM,1.,endit,1.);
	Prediction_Ratio->GetXaxis()->SetRangeUser(startit_RM,endit);
	Prediction_Ratio->GetYaxis()->SetRangeUser(0.8,1.2);
	Prediction_Ratio->GetYaxis()->SetTitle("Ratio Method / Standard Fit");
	Prediction_Ratio->GetXaxis()->SetTitle("M_{jj} [GeV]");
 	Prediction_Ratio->GetYaxis()->SetTitleOffset(1.3);
	Prediction_Ratio->SetMarkerStyle(8);
	Prediction_Ratio->SetMarkerColor(1);
	Prediction_Ratio->SetLineColor(1);
	Prediction_Ratio->Draw("p");
	paveCMS->Draw("same");
	sk3->Draw("same");


	char Pred_ratio_pdf[300];
	strcpy(Pred_ratio_pdf,"/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/pdf/Prediction_Ratio");
	strcat(Pred_ratio_pdf,image_name);
	strcat(Pred_ratio_pdf,".pdf");

	char Pred_ratio_png[300];
	strcpy(Pred_ratio_png,"/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/png/Prediction_Ratio");
	strcat(Pred_ratio_png,image_name);
	strcat(Pred_ratio_png,".png");
  
	//c2->SaveAs(Pred_ratio_pdf);
	//c2->SaveAs(Pred_ratio_png);

	TCanvas *c3 = new TCanvas("c3","Standard Fit Pull 1D",600,700);
	c3->cd();
	Standard_fit_pull_1D->GetXaxis()->SetRangeUser(-4,4);
	Standard_fit_pull_1D->SetMarkerStyle(8);
	Standard_fit_pull_1D->SetMarkerColor(1);
	Standard_fit_pull_1D->SetLineColor(1);
	Standard_fit_pull_1D->GetXaxis()->SetTitle("#frac{(Data-Prediction)}{Uncertainty}");
	Standard_fit_pull_1D->GetYaxis()->SetTitle("Entries");
	Standard_fit_pull_1D->GetXaxis()->SetTitleSize(2*0.03);
	Standard_fit_pull_1D->GetYaxis()->SetTitleSize(2*0.03);
	Standard_fit_pull_1D->GetXaxis()->SetLabelSize(2*0.03);
	Standard_fit_pull_1D->GetYaxis()->SetLabelSize(0.06);
	Standard_fit_pull_1D->GetXaxis()->SetTitleOffset(0.9);
	Standard_fit_pull_1D->GetYaxis()->SetTitleOffset(0.6);
	Standard_fit_pull_1D->Draw("e");
	Standard_fit_pull_1D->Fit("gaus");

	char SF_pull_histo_pdf[300];
	strcpy(SF_pull_histo_pdf,"/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/pdf/Standard_Fit_1Dpulls");
	strcat(SF_pull_histo_pdf,image_name);
	strcat(SF_pull_histo_pdf,".pdf");

	char SF_pull_histo_png[300];
	strcpy(SF_pull_histo_png,"/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/png/Standard_Fit_1Dpulls");
	strcat(SF_pull_histo_png,image_name);
	strcat(SF_pull_histo_png,".png");
  
	//c3->SaveAs(SF_pull_histo_pdf);
	//c3->SaveAs(SF_pull_histo_png);

	TCanvas *c4 = new TCanvas("c4","Ratio Method Pull 1D",600,700);
	c4->cd();
	Ratio_Method_pull_1D->GetXaxis()->SetRangeUser(-4,4);
	Ratio_Method_pull_1D->SetMarkerStyle(8);
	Ratio_Method_pull_1D->SetMarkerColor(1);
	Ratio_Method_pull_1D->SetLineColor(1);
	Ratio_Method_pull_1D->GetXaxis()->SetTitle("#frac{(Data-Prediction)}{Uncertainty}");
	Ratio_Method_pull_1D->GetYaxis()->SetTitle("Entries");
	Ratio_Method_pull_1D->GetXaxis()->SetTitleSize(0.03);
	Ratio_Method_pull_1D->GetYaxis()->SetTitleSize(2*0.03);
	Ratio_Method_pull_1D->GetXaxis()->SetLabelSize(2*0.03);
	Ratio_Method_pull_1D->GetYaxis()->SetLabelSize(0.06);
	Ratio_Method_pull_1D->GetXaxis()->SetTitleOffset(1.0);
	Ratio_Method_pull_1D->GetYaxis()->SetTitleOffset(0.8);
	Ratio_Method_pull_1D->Draw("e");
	Ratio_Method_pull_1D->Fit("gaus");

	char RM_pull_histo_pdf[300];
	strcpy(RM_pull_histo_pdf,"/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/pdf/Ratio_Method_1Dpulls");
	strcat(RM_pull_histo_pdf,image_name);
	strcat(RM_pull_histo_pdf,".pdf");

	char RM_pull_histo_png[300];
	strcpy(RM_pull_histo_png,"/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/Plots/png/Ratio_Method_1Dpulls");
	strcat(RM_pull_histo_png,image_name);
	strcat(RM_pull_histo_png,".png");
  
	//c4->SaveAs(RM_pull_histo_pdf);
	//c4->SaveAs(RM_pull_histo_png);
*/
}
