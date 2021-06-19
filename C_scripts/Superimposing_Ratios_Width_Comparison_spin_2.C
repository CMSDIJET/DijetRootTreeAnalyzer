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
#include "TLegendEntry.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TGraph.h"
#include "setTDRStyle_teliko.C"
#include <algorithm>
#include <string>


//This script plots superimposes the expected and observed limits of 2 different procedures (from the limit code) and also plots their ratio.


void Superimposing_Ratios_Width_Comparison_spin_2() {

	gROOT->LoadMacro("setTDRStyle_teliko.C");
	 setTDRStyle_teliko();

	int Superimposing_Xstart = 2700 ,Superimposing_Xend = 8700;
	double Superimposing_Ystart = 0.001 ,Superimposing_Yend = 10. ;
	int Ratio_Xstart = 2700 ,Ratio_Xend = 8700;
	double Ratio_Ystart = 0. ,Ratio_Yend = 2.0, Ratio_Yend_obs = 2.0 ;

	bool PlotForPass = true;
	bool SavePlots = true;

	//directories with the limit file inputs

	char *output_directory = "../Final_Results_EXO-19-012/Ratio_Method/Wide_resonances/limits/Spin_2/Correct_shapes/";  

	char *limits_directory = "Final_Results_EXO-19-012/Standard_Fit/Wide_resonances/limits/Spin_2/Correct_shapes/qq/";  
	//char *limits_directory = "double_sideband_no_zeros/Wide_limits/";   
//	char *limits_directory_mc = "Final_Results_EXO-19-012/Ratio_Method/Wide_resonances/limits/Spin_2/";
	char *limits_directory_mc = "Final_Results_EXO-19-012/Ratio_Method/Wide_resonances/limits/Spin_2/Correct_shapes/";

	char *resonance = "qq";          // give the resonance type 

	char box[300];
	strcpy(box,"_pfdijet2017"); 

	char box_mc[300];
	strcpy(box_mc,"_pfdijet2017mc"); 

	char obs_gr[300];
	strcpy(obs_gr,"obs_");
    strcat(obs_gr,resonance);
	strcat(obs_gr,box);


	char exp_gr[300];
	strcpy(exp_gr,"exp_");
    strcat(exp_gr,resonance);
	strcat(exp_gr,box);


	char obs_gr_MC[300];
	strcpy(obs_gr_MC,"obs_");
    strcat(obs_gr_MC,resonance);
	strcat(obs_gr_MC,box_mc);


	char exp_gr_MC[300];
	strcpy(exp_gr_MC,"exp_");
    strcat(exp_gr_MC,resonance);
	strcat(exp_gr_MC,box_mc);


	TFile *f;
	TFile *fmc;

	//char resonance_width[10];

	//char resonance_width[] = { '01', '05', '1', '15', '2', '25' , '3' ,'\0'};
	char resonance_width[12][3] = { "01", "05", "1", "15", "2", "25" , "3", "35", "4", "45", "5", "55" }; // array with words: 7 words, 3 is the number of memory needed (one for each letter) +1 for each word -- 2+1=3
	//string resonance_width[7] = { "01", "05", "1", "15", "2", "25" , "3" };

	TGraph *expected_ratio01, *expected_ratio05, *expected_ratio10, *expected_ratio15, *expected_ratio20, *expected_ratio25, *expected_ratio30, *expected_ratio35, *expected_ratio40, *expected_ratio45, *expected_ratio50, *expected_ratio55;
	TGraph *observed_ratio01, *observed_ratio05, *observed_ratio10, *observed_ratio15, *observed_ratio20, *observed_ratio25, *observed_ratio30, *observed_ratio35, *observed_ratio40, *observed_ratio45, *observed_ratio50, *observed_ratio55 ;




	char *width0 = "01"; 
	char *width1 = "05";
	char *width2 = "1";
	char *width3 = "15";
	char *width4 = "2";
	char *width5 = "25";
	char *width6 = "3";
	char *width7 = "35";
	char *width8 = "4";
	char *width9 = "45";
	char *width10 = "5";
	char *width11 = "55";



	TPaveText *paveCMS;

//paveCMS = new TPaveText(0.16,0.955,0.96,0.99,"NDC");
	if (PlotForPass )
	{
		paveCMS = new TPaveText(0.25,0.955,0.45,0.99,"NDC");
//		paveCMS->AddText("CMS #it{Supplementary}                   137 fb^{-1} (13 TeV)");
		paveCMS->AddText("CMS #it{Supplementary}");
	}
	
	// paveCMS->AddText("CMS                                 L = 137.5 fb^{-1}  (13 TeV)");

	 paveCMS->SetFillColor(0);
	 paveCMS->SetBorderSize(0);
	 paveCMS->SetTextSize(0.04);

	TPaveText *lumi_txt = new TPaveText(0.78,0.955,0.85,0.99,"NDC");
	lumi_txt->SetTextFont(42);
	lumi_txt->SetFillColor(0);
	 lumi_txt->SetBorderSize(0);
	 lumi_txt->SetTextSize(0.04);
	lumi_txt->AddText("137 fb^{-1} (13 TeV)");

	TPaveText *paveCMS3;
	paveCMS3 = new TPaveText(0.3,0.88,0.35,0.91,"NDC");
	paveCMS3->AddText("CMS");
	paveCMS3->SetFillColor(0);
	paveCMS3->SetBorderSize(0);
	paveCMS3->SetTextSize(0.045);

	 //TPaveText *paveCMS2 = new TPaveText(0.35,0.75,0.55,0.9,"NDC");
//	 TPaveText *paveCMS2 = new TPaveText(3500,0.6,4500,0.8); //spin 2
	 TPaveText *paveCMS2 = new TPaveText(3500,0.3,4500,0.5); //spin 2
//	 TPaveText *paveCMS2 = new TPaveText(3000,0.3,3600,0.5); //spin 1
	 paveCMS2->SetTextFont(42);
	 paveCMS2->AddText("Spin 2");
//	 paveCMS2->AddText("gluon-gluon" );
	 paveCMS2->AddText("quark-quark" );

	 paveCMS2->SetFillColor(0);
	 paveCMS2->SetBorderSize(0);   
	 paveCMS2->SetTextSize(0.034);

	for (int k =0; k<7;  k++) {
		

		//const char *width = resonance_width[k].c_str();  // if 'resonance_width' is s string, it converts its k element to const *char


		char input_directory[400];
		strcpy(input_directory,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
		//strcpy(input_directory,"/afs/cern.ch/work/d/dkarasav/public/limit_code_new/CMSSW_7_4_14/src/CMSDIJET/DijetRootTreeAnalyzer/");
		strcat(input_directory,limits_directory);
//	    strcat(input_directory,resonance);
//		strcat(input_directory,"_wide_0p");
		strcat(input_directory,"0p");
//		strcat(input_directory,"New_JER_implementation_0p");
		strcat(input_directory,resonance_width[k]);
		//strcat(input_directory,width);
		strcat(input_directory,"/limits_freq_");
//	    	strcat(input_directory,"gg");
	    strcat(input_directory,resonance);
		strcat(input_directory,box);				
		strcat(input_directory,".root");

	cout << input_directory << endl;

	
		f=new TFile(input_directory);


		TGraph *obs_graph  = (TGraph*)(f->Get(obs_gr));
		TGraph *exp_graph  = (TGraph*)(f->Get(exp_gr));

		char input_directoryMC[400];
		//strcpy(input_directoryMC,"/afs/cern.ch/work/d/dkarasav/public/limit_code_new/CMSSW_7_4_14/src/CMSDIJET/DijetRootTreeAnalyzer/");
		strcpy(input_directoryMC,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
		strcat(input_directoryMC,limits_directory_mc);
	    strcat(input_directoryMC,resonance);
		strcat(input_directoryMC,"_wide_0p");
//		strcat(input_directoryMC,"0p");
		strcat(input_directoryMC,resonance_width[k]);
		strcat(input_directoryMC,"/limits_freq_");
	    strcat(input_directoryMC,resonance);
		strcat(input_directoryMC,box_mc);	
		strcat(input_directoryMC,".root");

		
		fmc=new TFile(input_directoryMC);

		TGraph *obs_graphMC  = (TGraph*)(fmc->Get(obs_gr_MC));
		TGraph *exp_graphMC  = (TGraph*)(fmc->Get(exp_gr_MC));

		  int n = obs_graph->GetN();  //grabbing the graphs points to create the ratios///////////////////////////////////
		  int nmc = obs_graphMC->GetN();
		  int n_min = min(n,nmc);
		 

///////////////////////////////////defining the arrays needed/////////////////////////

 		 double obs[n] ,exp[n] ,x[n] ,obs_mc[nmc] ,exp_mc[nmc] ,xmc[nmc] ,exp_ratio[nmc] ,obs_ratio[nmc],xArray_min[n_min] ;
 

////////////////////////////saving the graph points into arrays/////////////////////////

		 for (int i=0; i<max(n,nmc); i++) {

			 if(i<n) {
			      obs_graph->GetPoint(i,x[i],obs[i]);
			      exp_graph->GetPoint(i,x[i],exp[i]);
				       }     

			 if(i<nmc) {
			     obs_graphMC->GetPoint(i,xmc[i],obs_mc[i]);
			     exp_graphMC->GetPoint(i,xmc[i],exp_mc[i]);
			     //if(i==10) cout << "mjj = "<<x1[i+n1-n2]<< " exp_standard = " << exp_1[i+n1-n2] << " mjj pred = "<< x2[i] <<" exp_pred = " << exp_2[i] <<"\n";
					 }

////////////////////////////Find which of the two graphs has the smaller range in x axis and use it to define the ratio /////////////////////////
			 if(i<n_min) {
				if (n>=nmc) xArray_min[i] = xmc[i];
			 	else	    xArray_min[i] = x[i];
						}
				                         }

//////////////////////////////////////////////creating the ratio ////////////////////////////////////

		for (int i=0; i<n_min; i++)
		 {
			exp_ratio[i]=exp_graph->Eval(xArray_min[i])/exp_graphMC->Eval(xArray_min[i]);    	    
			obs_ratio[i]=obs_graph->Eval(xArray_min[i])/obs_graphMC->Eval(xArray_min[i]);     
		 }	
  

		if(k==0)
		 {
			expected_ratio01=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio01=new TGraph(n_min,xArray_min,obs_ratio);
		 }

		if(k==1)
		 {
			expected_ratio05=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio05=new TGraph(n_min,xArray_min,obs_ratio);
		 }

		if(k==2)
		 {
			expected_ratio10=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio10=new TGraph(n_min,xArray_min,obs_ratio);
	 	 }
		if(k==3)
		 {
			expected_ratio15=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio15=new TGraph(n_min,xArray_min,obs_ratio);
		 }
		if(k==4)
		 {
			expected_ratio20=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio20=new TGraph(n_min,xArray_min,obs_ratio);
		 }
		if(k==5)
		 {
			expected_ratio25=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio25=new TGraph(n_min,xArray_min,obs_ratio);
		 }
		if(k==6)
		 {
			expected_ratio30=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio30=new TGraph(n_min,xArray_min,obs_ratio);
		 }
		if(k==7)
		 {
			expected_ratio35=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio35=new TGraph(n_min,xArray_min,obs_ratio);
		 }
		if(k==8)
		 {
			expected_ratio40=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio40=new TGraph(n_min,xArray_min,obs_ratio);
		 }
		if(k==9)
		 {
			expected_ratio45=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio45=new TGraph(n_min,xArray_min,obs_ratio);
		 }
		if(k==10)
		 {
			expected_ratio50=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio50=new TGraph(n_min,xArray_min,obs_ratio);
		 }
        if(k==11)
		 {
			expected_ratio55=new TGraph(n_min,xArray_min,exp_ratio);
			observed_ratio55=new TGraph(n_min,xArray_min,obs_ratio);
		 }

	//f->Close();
	//fmc->Close();
		}              //end of loop in files

	
	TLine *sk = new TLine(Ratio_Xstart,1.,Ratio_Xend,1.);
	sk->SetLineStyle(9);

 	TCanvas *c3 = new TCanvas("c3","Observed Limits Ratio Comparison",600,600);

	 observed_ratio01->SetTitle(" ");
	 observed_ratio01->GetXaxis()->SetRangeUser(Ratio_Xstart,Ratio_Xend);
	 observed_ratio01->GetXaxis()->SetLabelOffset(1000);
	 observed_ratio01->GetYaxis()->SetTitleSize(0.04);
	 observed_ratio01->GetYaxis()->SetRangeUser(Ratio_Ystart,Ratio_Yend_obs);
	 observed_ratio01->SetFillColor(1);
	 observed_ratio01->SetLineColor(1); 
     observed_ratio01->SetLineWidth(2);
	 observed_ratio01->SetMarkerStyle(26);
	 observed_ratio01->SetMarkerColor(1);
     observed_ratio01->GetXaxis()->SetTitle("Resonance mass [TeV]");
//	 observed_ratio01->GetYaxis()->SetTitle("Ratio of observed limits from Fit Method / Ratio Method");
	 observed_ratio01->GetYaxis()->SetTitle("Shapes: New / Old");
	 observed_ratio01->Draw("AC");


	 observed_ratio30->SetTitle(" ");
	 observed_ratio30->GetXaxis()->SetRangeUser(Ratio_Xstart,Ratio_Xend);
	 observed_ratio30->GetYaxis()->SetRangeUser(Ratio_Ystart,Ratio_Yend);
	 observed_ratio30->GetYaxis()->SetTitleSize(0.04);
	 observed_ratio30->SetFillColor(1);
	 observed_ratio30->SetLineColor(7); 
	 observed_ratio30->GetXaxis()->SetLabelOffset(1000);
     observed_ratio30->SetLineWidth(2);
	 observed_ratio30->SetMarkerStyle(26);
	 observed_ratio30->SetMarkerColor(7);
     observed_ratio30->GetXaxis()->SetTitle("Resonance Mass [TeV]");
//	 observed_ratio30->GetYaxis()->SetTitle("Ratio of observed limits from Fit Method / Ratio Method");
	 observed_ratio30->GetYaxis()->SetTitle("Shapes: New / Old");
//	 observed_ratio30->Draw("AC");
	 observed_ratio30->Draw("same");


	 observed_ratio05->SetLineColor(2); 
	 observed_ratio05->SetMarkerStyle(30);
	 observed_ratio05->SetMarkerColor(2);
     observed_ratio05->SetLineWidth(2);
	 observed_ratio05->SetFillColor(2);
	 observed_ratio05->Draw("same");


	 observed_ratio10->SetFillColor(3);
	 observed_ratio10->SetLineColor(3); 
     observed_ratio10->SetLineWidth(2);
	 observed_ratio10->SetMarkerStyle(4);
	 observed_ratio10->SetMarkerColor(3);
	 observed_ratio10->Draw("same");

	 observed_ratio15->SetFillColor(4);
	 observed_ratio15->SetLineColor(4); 
     observed_ratio15->SetLineWidth(2);
	 observed_ratio15->SetMarkerStyle(4);
	 observed_ratio15->SetMarkerColor(4);
	 observed_ratio15->Draw("same");

	 observed_ratio20->SetFillColor(kRed);
//	 observed_ratio20->SetLineColor(5); 
     observed_ratio20->SetLineWidth(2);
	 observed_ratio20->SetMarkerStyle(5);
//	 observed_ratio20->SetMarkerColor(5);
	 observed_ratio20->SetLineColor(kRed);
	 observed_ratio20->Draw("same");

	 observed_ratio25->SetFillColor(6);
	 observed_ratio25->SetLineColor(6); 
     observed_ratio25->SetLineWidth(2);
	 observed_ratio25->SetMarkerStyle(25);
	 observed_ratio25->SetMarkerColor(6);
	 observed_ratio25->Draw("same");

/*
	 observed_ratio35->SetFillColor(kYellow-2);
	 observed_ratio35->SetLineColor(kYellow-2); 
     observed_ratio35->SetLineWidth(2);
	 observed_ratio35->SetMarkerStyle(27);
	 observed_ratio35->SetMarkerColor(kYellow-2);
	 observed_ratio35->Draw("same");
*/

/*	
	 observed_ratio40->SetFillColor(kBlack);
	 observed_ratio40->SetLineColor(kBlack); 
     observed_ratio40->SetLineWidth(2);
	 observed_ratio40->SetMarkerStyle(27);
	 observed_ratio40->SetMarkerColor(kBlack);
	 observed_ratio40->Draw("same");	
*/
/*		
	 observed_ratio45->SetFillColor(kCyan+2);
	 observed_ratio45->SetLineColor(kCyan+2); 
     observed_ratio45->SetLineWidth(2);
	 observed_ratio45->SetMarkerStyle(27);
	 observed_ratio45->SetMarkerColor(kCyan+2);
	 observed_ratio45->Draw("same");

	
	 observed_ratio50->SetFillColor(kGray+2);
	 observed_ratio50->SetLineColor(kGray+2); 
     observed_ratio50->SetLineWidth(2);
	 observed_ratio50->SetMarkerStyle(27);
	 observed_ratio50->SetMarkerColor(kGray+2);
	 observed_ratio50->Draw("same");
*/

/*	
	 observed_ratio55->SetFillColor(kGreen+2);
	 observed_ratio55->SetLineColor(kGreen+2); 
     observed_ratio55->SetLineWidth(2);
	 observed_ratio55->SetMarkerStyle(27);
	 observed_ratio55->SetMarkerColor(kGreen+2);
	 observed_ratio55->Draw("same");
*/
	 TLegend *leg3 = new TLegend(0.7,0.18,0.9,0.45);
	 leg3->AddEntry(observed_ratio01,   "#Gamma/#Mu 1% ","l");
	 leg3->AddEntry(observed_ratio05,   "#Gamma/#Mu 5% ","l");
	 leg3->AddEntry(observed_ratio10,   "#Gamma/#Mu 10%","l");
	 leg3->AddEntry(observed_ratio15,   "#Gamma/#Mu 15%","l");
	 leg3->AddEntry(observed_ratio20,   "#Gamma/#Mu 20%","l");
	 leg3->AddEntry(observed_ratio25,   "#Gamma/#Mu 25%","l");
	 leg3->AddEntry(observed_ratio30,   "#Gamma/#Mu 30%","l");

//	 leg3->AddEntry(observed_ratio35,   "#Gamma/#Mu 35%","l");
//	 leg3->AddEntry(observed_ratio40,   "#Gamma/#Mu 40%","l");
//	 leg3->AddEntry(observed_ratio45,   "#Gamma/#Mu 45%","l");
//	 leg3->AddEntry(observed_ratio50,   "#Gamma/#Mu 50%","l");

//	 leg3->AddEntry(observed_ratio55,   "#Gamma/#Mu 55%","l");

	 leg3->SetTextSize(0.03);
	 leg3->Draw("same"); 

	 sk->Draw("same");
	 paveCMS->Draw("same");
	 paveCMS2->Draw("same");
	 if (!PlotForPass )	 paveCMS3->Draw("same"); 


	 TLatex *xLab = new TLatex();
	xLab->SetTextAlign(22);
	xLab->SetTextFont(42);
	xLab->SetTextSize(0.05);         
//	xLab->DrawLatex(2000, 6.25e-6, "2");
/*
	xLab->DrawLatex(3000, 0.07, "3");
	xLab->DrawLatex(4000, 0.07, "4");
	xLab->DrawLatex(5000, 0.07, "5");
	xLab->DrawLatex(6000, 0.07, "6");
	xLab->DrawLatex(7000, 0.07, "7");
	xLab->DrawLatex(8000, 0.07, "8");
*/

	xLab->DrawLatex(3000, Ratio_Ystart-0.04, "3");
	xLab->DrawLatex(4000, Ratio_Ystart-0.04, "4");
	xLab->DrawLatex(5000, Ratio_Ystart-0.04, "5");
	xLab->DrawLatex(6000, Ratio_Ystart-0.04, "6");
	xLab->DrawLatex(7000, Ratio_Ystart-0.04, "7");
	xLab->DrawLatex(8000, Ratio_Ystart-0.04, "8");


	 //paveCMS2->Draw("same");

	char Obs_pdf_plot[350];
	strcpy(Obs_pdf_plot,output_directory);
	strcat(Obs_pdf_plot,"/Observed_Wide_Resonance_limits_ratio_superimposed_gg_highW_v2.pdf");

	char Obs_png_plot[350];
	strcpy(Obs_png_plot,output_directory);
	strcat(Obs_png_plot,"/Observed_Wide_Resonance_limits_ratio_superimposed_gg_highW_v2.png");

//	if(SavePlots) c3->SaveAs(Obs_png_plot);
//	if(SavePlots) c3->SaveAs(Obs_pdf_plot);


 	TCanvas *c4 = new TCanvas("c4","Expected Limits Ratio Comparison",600,600);


	 expected_ratio01->SetTitle(" ");
	 expected_ratio01->GetXaxis()->SetRangeUser(Ratio_Xstart,Ratio_Xend);
	 expected_ratio01->GetYaxis()->SetRangeUser(Ratio_Ystart,Ratio_Yend);
	 expected_ratio01->GetYaxis()->SetTitleSize(0.04);
	 expected_ratio01->SetFillColor(1);
	 expected_ratio01->SetLineColor(1); 
	 expected_ratio01->GetXaxis()->SetLabelOffset(1000);
     expected_ratio01->SetLineWidth(2);
	 expected_ratio01->SetMarkerStyle(26);
	 expected_ratio01->SetMarkerColor(1);
     expected_ratio01->GetXaxis()->SetTitle("Resonance mass [TeV]");
	 expected_ratio01->GetYaxis()->SetTitle("Ratio of expected limits between the fit and the ratio methods");
//	 expected_ratio01->GetYaxis()->SetTitle("Shapes: New / Old");
//	 expected_ratio01->Draw("AC");


	 expected_ratio30->SetTitle(" ");
	 expected_ratio30->GetXaxis()->SetRangeUser(Ratio_Xstart,Ratio_Xend);
	 expected_ratio30->GetYaxis()->SetRangeUser(Ratio_Ystart,Ratio_Yend);
	 expected_ratio30->GetYaxis()->SetTitleSize(0.045);
	 expected_ratio30->GetYaxis()->SetTitleOffset(1.4);
	 expected_ratio30->SetFillColor(1);
	 expected_ratio30->SetLineColor(7); 
	 expected_ratio30->GetXaxis()->SetLabelOffset(1000);
     expected_ratio30->SetLineWidth(2);
	 expected_ratio30->SetMarkerStyle(26);
	 expected_ratio30->SetMarkerColor(7);
     expected_ratio30->GetXaxis()->SetTitle("Resonance mass [TeV]");
	 expected_ratio30->GetYaxis()->SetTitle("Ratio of expected limits: fit / ratio methods");
//	 expected_ratio30->GetYaxis()->SetTitle("Shapes: New / Old");
	 expected_ratio30->Draw("AC");
//	 expected_ratio30->Draw("same");


	 expected_ratio05->SetLineColor(2); 
	 expected_ratio05->SetMarkerStyle(30);
	 expected_ratio05->SetMarkerColor(2);
     expected_ratio05->SetLineWidth(2);
	 expected_ratio05->SetFillColor(2);
//	 expected_ratio05->Draw("same");



	 expected_ratio10->SetFillColor(3);
	 expected_ratio10->SetLineColor(3);
     expected_ratio10->SetLineWidth(2); 
	 expected_ratio10->SetMarkerStyle(4);
	 expected_ratio10->SetMarkerColor(3);
	 expected_ratio10->Draw("same");

	 expected_ratio15->SetFillColor(4);
	 expected_ratio15->SetLineColor(4); 
     expected_ratio15->SetLineWidth(2);
	 expected_ratio15->SetMarkerStyle(4);
	 expected_ratio15->SetMarkerColor(4);
	 expected_ratio15->Draw("same");

	 expected_ratio20->SetFillColor(kRed);
//	 expected_ratio20->SetLineColor(5); 
     expected_ratio20->SetLineWidth(2);
	 expected_ratio20->SetMarkerStyle(5);
//	 expected_ratio20->SetMarkerColor(5);
	 expected_ratio20->SetLineColor(kRed);
	 expected_ratio20->Draw("same");

	 expected_ratio25->SetFillColor(6);
	 expected_ratio25->SetLineColor(6); 
     expected_ratio25->SetLineWidth(2);
	 expected_ratio25->SetMarkerStyle(25);
	 expected_ratio25->SetMarkerColor(6);
	 expected_ratio25->Draw("same");
/*
	 expected_ratio35->SetFillColor(kYellow-2);
	 expected_ratio35->SetLineColor(kYellow-2); 
     expected_ratio35->SetLineWidth(2);
	 expected_ratio35->SetMarkerStyle(27);
	 expected_ratio35->SetMarkerColor(kYellow-2);
	 expected_ratio35->Draw("same");
*/

/*	
	 expected_ratio40->SetFillColor(kBlue-1);
	 expected_ratio40->SetLineColor(kBlue-1); 
     expected_ratio40->SetLineWidth(2);
	 expected_ratio40->SetMarkerStyle(27);
	 expected_ratio40->SetMarkerColor(kBlue-1);
	 expected_ratio40->Draw("same");	
*/
	/*	
	 expected_ratio45->SetFillColor(kCyan+2);
	 expected_ratio45->SetLineColor(kCyan+2); 
     expected_ratio45->SetLineWidth(2);
	 expected_ratio45->SetMarkerStyle(27);
	 expected_ratio45->SetMarkerColor(kCyan+2);
	 expected_ratio45->Draw("same");

	
	 expected_ratio50->SetFillColor(kGray+2);
	 expected_ratio50->SetLineColor(kGray+2); 
     expected_ratio50->SetLineWidth(2);
	 expected_ratio50->SetMarkerStyle(27);
	 expected_ratio50->SetMarkerColor(kGray+2);
	 expected_ratio50->Draw("same");
*/

/*
	 expected_ratio55->SetFillColor(kGreen+2);
	 expected_ratio55->SetLineColor(kGreen+2); 
     expected_ratio55->SetLineWidth(2);
	 expected_ratio55->SetMarkerStyle(27);
	 expected_ratio55->SetMarkerColor(kGreen+2);
	 expected_ratio55->Draw("same");
*/
/*
	 expected_ratio30->SetFillColor(7);
	 expected_ratio30->SetLineColor(7); 
     expected_ratio30->SetLineWidth(2);
	 expected_ratio30->SetMarkerStyle(27);
	 expected_ratio30->SetMarkerColor(7);
	 expected_ratio30->Draw("same");
*/
	 TLegend *leg4 = new TLegend(0.7,0.18,0.9,0.45);
//	 leg4->AddEntry(expected_ratio01,   "#Gamma/#Mu 1% ","l");
//	 leg4->AddEntry(expected_ratio05,   "#Gamma/#Mu 5% ","l");
	 leg4->AddEntry(expected_ratio10,   "#Gamma/#Mu 10%","l");
	 leg4->AddEntry(expected_ratio15,   "#Gamma/#Mu 15%","l");
	 leg4->AddEntry(expected_ratio20,   "#Gamma/#Mu 20%","l");
	 leg4->AddEntry(expected_ratio25,   "#Gamma/#Mu 25%","l");
	 leg4->AddEntry(expected_ratio30,   "#Gamma/#Mu 30%","l");

//	 leg4->AddEntry(expected_ratio35,   "#Gamma/#Mu 35%","l");
//	 leg4->AddEntry(expected_ratio40,   "#Gamma/#Mu 40%","l");
//	 leg4->AddEntry(expected_ratio45,   "#Gamma/#Mu 45%","l");
//	 leg4->AddEntry(expected_ratio50,   "#Gamma/#Mu 50%","l");
//	 leg4->AddEntry(expected_ratio55,   "#Gamma/#Mu 55%","l");

	 leg4->SetTextSize(0.03);
	 leg4->Draw("same"); 
	 sk->Draw("same");
	 paveCMS->Draw("same");
	 paveCMS2->Draw("same");
	 if (!PlotForPass )	 paveCMS3->Draw("same"); 
	 lumi_txt->Draw("same");


	xLab->DrawLatex(3000, -0.065, "3");
	xLab->DrawLatex(4000, -0.065, "4");
	xLab->DrawLatex(5000, -0.065, "5");
	xLab->DrawLatex(6000, -0.065, "6");
	xLab->DrawLatex(7000, -0.065, "7");
	xLab->DrawLatex(8000, -0.065, "8");


/*	
	xLab->DrawLatex(3000, Ratio_Ystart-0.048, "3");
	xLab->DrawLatex(4000, Ratio_Ystart-0.048, "4");
	xLab->DrawLatex(5000, Ratio_Ystart-0.048, "5");
	xLab->DrawLatex(6000, Ratio_Ystart-0.048, "6");
//	xLab->DrawLatex(7000, Ratio_Ystart-0.048, "7");
//	xLab->DrawLatex(8000, Ratio_Ystart-0.048, "8");
*/
	// paveCMS2->Draw("same");
	char pdf_plot[350];
	strcpy(pdf_plot,output_directory);
	strcat(pdf_plot,"/Expected_Wide_Resonance_limits_ratio_superimposed_qq_highW_v2.pdf");

	char png_plot[350];
	strcpy(png_plot,output_directory);
	strcat(png_plot,"/Expected_Wide_Resonance_limits_ratio_superimposed_qq_highW_v2.png");

	if(SavePlots) c4->SaveAs(png_plot);
	if(SavePlots) c4->SaveAs(pdf_plot);




}
