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
#include "TLegendEntry.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include "TLatex.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TGraph.h"
#include "setTDRStyle_teliko.C"
#include <algorithm>
#include <string>

//This script plots superimposed the significances of 2 different procedures (from combine).


//flag is to determine whether an input file is from ratio method --> means it has "mc" in the end of its name
//flag = 0 -> no file has "MC"
//flag = 1 -> First file has "MC"
//flag = 2 -> Second file has "MC" 
//flag = 3 -> Both files have "MC" 

void Superimposed_Significances(int flag) {

	gROOT->LoadMacro("setTDRStyle_teliko.C");
	 setTDRStyle_teliko();

	int Superimposing_Xstart = 1800 ,Superimposing_Xend = 8700;
	double Superimposing_Ystart = 0.0 ,Superimposing_Yend = 4. ;

	char *signif1_directory = "/Final_Results_EXO-19-012/Standard_Fit/Narrow_resonances/significances/";
//	char *signif2_directory = "/Final_Results_EXO-19-012/Ratio_Method/Narrow_resonances/Test_studies/SR_scaled_MC/";
	char *signif2_directory = "/Final_Results_EXO-19-012/Ratio_Method/Narrow_resonances/significances/Narrow_qq_significance/";
	char *output_directory  = "Final_Results_EXO-19-012/Stiched_limits/Narrow_resonances/significances/";
	char *resonance = "qq";          // give the resonance type 
	char *image_name = "paper" ;     // give the end of the name of output pictures (.png and .pdf) --- giving "-" will not put an end to the name

	char *lumi                 = "137" ;   //give lumi in fb^-1  -----  if the two compared methods have different luminocities set: lumi = "-" 
	char *superimposed_legend1 = "Fit method" ;
	char *superimposed_legend2 = "Ratio method" ;

	//year1, year2 are : 2016 or 2017 for file 1 and file 2 respectively
	int year1 = 2017;
 	int year2 = 2017;
	//box string is defined for each input file
 	char box1[300], box2[300];
	//box 1 definition
	if (flag == 1 || flag == 3 )
	{
		if ( year1 == 2016) strcpy(box1,"_PFDijet2016MC"); 
		else if ( year1 == 2017) strcpy(box1,"_PFDijet2017MC"); 
	}
    else
	{
		if ( year1 == 2016) strcpy(box1,"_PFDijet2016");
		else if ( year1 == 2017) strcpy(box1,"_PFDijet2017");
	}
	//box2 definition
	if (flag == 2 || flag == 3 )
	{
		if ( year2 == 2016) strcpy(box2,"_PFDijet2016MC"); 
		else if ( year2 == 2017) strcpy(box2,"_PFDijet2017MC"); 
	}
    else
	{
		if ( year2 == 2016) strcpy(box2,"_PFDijet2016");
		else if ( year2 == 2017) strcpy(box2,"_PFDijet2017");
	}
	

	//full path until the 1st limit file
	char input1_directory[300];

	strcpy(input1_directory,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
	strcat(input1_directory,signif1_directory);
	strcat(input1_directory,"xsecUL_ProfileLikelihood_");
	strcat(input1_directory,resonance);
	strcat(input1_directory,box1);				
	strcat(input1_directory,".root");

	//full path until the 2nd limit file
	char input2_directory[300];
	strcpy(input2_directory,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
	strcat(input2_directory,signif2_directory);
	strcat(input2_directory,"xsecUL_ProfileLikelihood_");
	strcat(input2_directory,resonance);
	strcat(input2_directory,box2);	
	strcat(input2_directory,".root");

	TFile *f1=new TFile(input1_directory);
	TFile *f2=new TFile(input2_directory);

	double mass_SF, signif_SF;
	double mass_RM, signif_RM;

	char signif_name_SF[100];           //This is the variable's name in the input1
	strcpy(signif_name_SF,"xsecULObs");
	strcat(signif_name_SF,box1);

	char signif_name_RM[100];			//This is the variable's name in the input2
	strcpy(signif_name_RM,"xsecULObs");
	strcat(signif_name_RM,box2);	

	TTree * tree1 = (TTree*) f1->Get("xsecTree");
	tree1->SetBranchAddress("mass",&mass_SF);
	tree1->SetBranchAddress(signif_name_SF,&signif_SF);

	TTree * tree2 = (TTree*) f2->Get("xsecTree");
	tree2->SetBranchAddress("mass",&mass_RM);
	tree2->SetBranchAddress(signif_name_RM,&signif_RM);

	int nentries1=(Int_t)tree1->GetEntries(); 
	int nentries2=(Int_t)tree2->GetEntries(); 
	
	double mass_RM_ar[nentries2];
	double mass_SF_ar[nentries1];
	double Signif_SF[nentries1];
	double Signif_RM[nentries2];
	
	for (int i=0; i<nentries1; i++)   //event loop for 1st input to fill arrays
	{   
		tree1->GetEntry(i);
		mass_SF_ar[i] = mass_SF;
		Signif_SF[i] = signif_SF;		
	}// end of event loop

	for (int i=0; i<nentries2; i++)   //event loop for 2nd input to fill arrays
	{   
		tree2->GetEntry(i);
		mass_RM_ar[i] = mass_RM;
		Signif_RM[i] = signif_RM;		
	}// end of event loop

	TGraph *gr_signif_SF=new TGraph(nentries1,mass_SF_ar,Signif_SF);
	TGraph *gr_signif_RM=new TGraph(nentries2,mass_RM_ar,Signif_RM);

	//plotting staff

	char CMS_pave[200];
//	strcpy(CMS_pave,"CMS Preliminary    #sqrt{s} = 13 TeV       L = ");
//	strcpy(CMS_pave,"CMS #it{Preliminary}                                ");
	strcpy(CMS_pave,"                                                  ");
	strcat(CMS_pave,lumi);
	strcat(CMS_pave," fb^{-1} (13 TeV)");

//	TPaveText *paveCMS = new TPaveText(0.16,0.96,0.96,0.99,"NDC");
	TPaveText *paveCMS = new TPaveText(0.19,0.96,0.95,0.99,"NDC");
	 if (lumi == "-")    paveCMS->AddText("CMS Preliminary    #sqrt{s} = 13 TeV    ");
	 else 		     paveCMS->AddText(CMS_pave);
	 paveCMS->SetFillColor(0);
	 paveCMS->SetBorderSize(0);
	 paveCMS->SetTextSize(0.04);
	 paveCMS->SetTextFont(42);



	TPaveText *paveCMS3 = new TPaveText(0.20,0.87,0.30,0.9,"NDC");
//	TPaveText *paveCMS3 = new TPaveText(0.19,0.955,0.42,0.985,"NDC");
	paveCMS3->AddText("CMS");
//	paveCMS3->AddText("CMS #it{Preliminary}");
	paveCMS3->SetFillColor(0);
	paveCMS3->SetBorderSize(0);
	paveCMS3->SetTextSize(0.04);

	TPaveText *paveCMS2 = new TPaveText(0.2,0.65,0.40,0.88,"NDC");
	// paveCMS2->AddText("|#eta|<2.5" );
	// paveCMS2->AddText("M_{jj} > 1.6 TeV");
	 paveCMS2->SetFillColor(0);
	 paveCMS2->SetTextFont(42);
	 paveCMS2->SetBorderSize(0);   
	 paveCMS2->SetTextSize(0.04);
	 if 	 ( resonance == "gg") paveCMS2->AddText("gluon-gluon");
	 else if ( resonance == "qg") paveCMS2->AddText("quark-gluon");
	 else if ( resonance == "qq") paveCMS2->AddText("quark-quark");

	TLegend *leg1 = new TLegend(0.56,0.7,0.93,0.9);
	leg1->AddEntry(gr_signif_RM,superimposed_legend2,"l");
	leg1->AddEntry(gr_signif_SF,superimposed_legend1,"l");
	leg1->SetTextSize(0.04);

	TCanvas *c1 = new TCanvas("c1","Significance Comparison",600,600);
	gr_signif_SF->SetTitle(" ");
	gr_signif_SF->GetXaxis()->SetRangeUser(Superimposing_Xstart,Superimposing_Xend);
	gr_signif_SF->GetYaxis()->SetRangeUser(Superimposing_Ystart,Superimposing_Yend);
	gr_signif_SF->SetFillColor(2);
	gr_signif_SF->SetLineColor(2); 
	gr_signif_SF->SetLineWidth(3); 
	gr_signif_SF->SetLineStyle(2); 
	gr_signif_SF->GetXaxis()->SetTitle("Resonance mass [TeV]");
	gr_signif_SF->GetXaxis()->SetTitleSize(0.05);
	gr_signif_SF->GetXaxis()->SetLabelSize(0.045);
	gr_signif_SF->GetXaxis()->SetLabelOffset(1000);
	gr_signif_SF->GetYaxis()->SetTitle("Local significance [std. deviation]");
	gr_signif_SF->Draw("AC");
	gr_signif_RM->SetFillColor(4);
	gr_signif_RM->SetFillColor(4);
	gr_signif_RM->SetLineColor(4); 
	gr_signif_RM->SetLineWidth(3); 
	gr_signif_RM->Draw("same");
	leg1->Draw("same"); 
	paveCMS->Draw("same");
	paveCMS2->Draw("same");
	paveCMS3->Draw("same");

	TLatex *xLab = new TLatex();
	xLab->SetTextAlign(22);
	xLab->SetTextFont(42);
	xLab->SetTextSize(0.05);         
	xLab->DrawLatex(2000, -0.12, "2");
	xLab->DrawLatex(3000, -0.12, "3");
	xLab->DrawLatex(4000, -0.12, "4");
	xLab->DrawLatex(5000, -0.12, "5");
	xLab->DrawLatex(6000, -0.12, "6");
	xLab->DrawLatex(7000, -0.12, "7");
	xLab->DrawLatex(8000, -0.12, "8");


	char signif_plot_pdf[300];
	strcpy(signif_plot_pdf,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
	strcat(signif_plot_pdf,output_directory);
	strcat(signif_plot_pdf,"Superimposed_");
	strcat(signif_plot_pdf,resonance);
	if ( image_name == "-") strcat(signif_plot_pdf,"_significances.pdf");
	else 
	{	
		strcat(signif_plot_pdf,"_significances_");
		strcat(signif_plot_pdf,image_name);
		strcat(signif_plot_pdf,".pdf");
	}

	char signif_plot_png[300];
	strcpy(signif_plot_png,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
	strcat(signif_plot_png,output_directory);
	strcat(signif_plot_png,"Superimposed_");
	strcat(signif_plot_png,resonance);
	if ( image_name == "-") strcat(signif_plot_png,"_significances.png");
	else
	{	
		strcat(signif_plot_png,"_significances_");
		strcat(signif_plot_png,image_name);
		strcat(signif_plot_png,".png");
	}

	c1->SaveAs(signif_plot_pdf);
	c1->SaveAs(signif_plot_png);

	

}
