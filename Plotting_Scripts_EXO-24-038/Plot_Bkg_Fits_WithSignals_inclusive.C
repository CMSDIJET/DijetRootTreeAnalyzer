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

void Plot_Bkg_Fits_WithSignals_inclusive(){

double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

double lumi 	     = 137600;    
double startit	     = 1530;
double endit	     = 9067;


double sig_low_narrow_obs_limit = 0.001337810*1.; 
double sig_high_narrow_obs_limit = 0.000047642*1.; 

double sig_low_wide_obs_limit = 0.002232955*1.; 
double sig_high_wide_obs_limit = 0.000063891*1.; 
	
//Fetch data, MC and fits		
TFile *f_data = new TFile("files/HISTOS_4J_AlldataRun2_SR_alphagt0p1.root");
TFile *f_Fit_atlas = new TFile("files/DijetFitResult_PFDijetRun2_4J_alphagt0p1_PowExp.root");
TFile *f_Fit_dijet = new TFile("files/DijetFitResult_PFDijetRun2_4J_alphagt0p1_Dijet.root");
TFile *f_Fit_moddijet = new TFile("files/DijetFitResult_PFDijetRun2_4J_alphagt0p1_ModDijet.root");
TFile *f_MC = new TFile("files/QCD2017_Standardcuts_M4Jgt1p5_nobreak_alphagt0p1.root");

TH1D *Standard_Fit_unbinned_atlas = (TH1D*)(f_Fit_atlas->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *Standard_Fit_unbinned_dijet = (TH1D*)(f_Fit_dijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *Standard_Fit_unbinned_moddijet = (TH1D*)(f_Fit_moddijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *h_data = (TH1D*)(f_data->Get("h_FourjetMass"));
TH1D *h_MC = (TH1D*)(f_MC->Get("h_FourjetMass"));



/*//Fetch narrow signal histos
TFile *f_sig_low_narrow = new TFile("files/ResonanceShapes_Suu3600_Chi1044_SR_noslices.root");
TH1D *h_sig_low_narrow_1GeV = (TH1D*)(f_sig_low_narrow->Get("h_FourjetMass1GeV"));   
h_sig_low_narrow_1GeV->Scale(sig_low_narrow_obs_limit*lumi);  


TFile *f_sig_high_narrow = new TFile("files/ResonanceShapes_Suu8600_Chi2150_SR_noslices.root");
TH1D *h_sig_high_narrow_1GeV = (TH1D*)(f_sig_high_narrow->Get("h_FourjetMass1GeV"));   
h_sig_high_narrow_1GeV->Scale(sig_high_narrow_obs_limit*lumi);


TH1D *h_sig_low_narrow = new TH1D("h_sig_low_narrow","",103,massBoundaries); 
TH1D *h_sig_high_narrow = new TH1D("h_sig_high_narrow","",103,massBoundaries); 

//rebinning 1GeV shapes to standard binning
for(int i=0; i<h_sig_low_narrow_1GeV->GetNbinsX(); i++)
{
	double val   = h_sig_low_narrow_1GeV->GetBinContent(i);
	double xval  = h_sig_low_narrow_1GeV->GetBinCenter(i);
	h_sig_low_narrow->Fill(xval,val);
	
	
	val   = h_sig_high_narrow_1GeV->GetBinContent(i);
	xval  = h_sig_high_narrow_1GeV->GetBinCenter(i);
	h_sig_high_narrow->Fill(xval,val);
}
*/

//Fetch narrow signal histos
TFile *f_sig_low_narrow = new TFile("files/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p015_S-3600_chi-1044_alphagt0p1.root");
TH1D *h_sig_low_narrow  = (TH1D*)(f_sig_low_narrow->Get("h_FourjetMass"));   
h_sig_low_narrow->Scale(sig_low_narrow_obs_limit*lumi);  


TFile *f_sig_high_narrow = new TFile("files/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p015_S-8600_chi-2150_alphagt0p1.root");
TH1D *h_sig_high_narrow  = (TH1D*)(f_sig_high_narrow->Get("h_FourjetMass"));   
h_sig_high_narrow->Scale(sig_high_narrow_obs_limit*lumi);



//Fetch wide signal histos
TFile *f_sig_low_wide = new TFile("files/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p1_S-3600_chi-1044_alphagt0p1.root");
TH1D *h_sig_low_wide  = (TH1D*)(f_sig_low_wide->Get("h_FourjetMass"));   
h_sig_low_wide->Scale(sig_low_wide_obs_limit*lumi);  


TFile *f_sig_high_wide = new TFile("files/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p1_S-8600_chi-2150_alphagt0p1.root");
TH1D *h_sig_high_wide  = (TH1D*)(f_sig_high_wide->Get("h_FourjetMass"));   
h_sig_high_wide->Scale(sig_high_wide_obs_limit*lumi);


	    
TH1D *Standard_Fit_atlas = new TH1D("Standard_Fit_atlas","",103,massBoundaries);  
TH1D *Standard_Fit_dijet = new TH1D("Standard_Fit_dijet","",103,massBoundaries);
TH1D *Standard_Fit_moddijet = new TH1D("Standard_Fit_moddijet","",103,massBoundaries); 

//rebinning 1GeV Standard Fit to standard binning
for(int i=0; i<Standard_Fit_unbinned_atlas->GetNbinsX(); i++)
{
	double val  = Standard_Fit_unbinned_atlas->GetBinContent(i);
	double xval  = Standard_Fit_unbinned_atlas->GetBinCenter(i);
	Standard_Fit_atlas->Fill(xval,val);
        val  = Standard_Fit_unbinned_dijet->GetBinContent(i);
        xval  = Standard_Fit_unbinned_dijet->GetBinCenter(i);
        Standard_Fit_dijet->Fill(xval,val);
        val  = Standard_Fit_unbinned_moddijet->GetBinContent(i);
        xval  = Standard_Fit_unbinned_moddijet->GetBinCenter(i);
        Standard_Fit_moddijet->Fill(xval,val);
}



//Define pull histos		        
TH1D *pull_Fit_atlas = (TH1D*)(h_data->Clone());
TH1D *pull_Fit_dijet = (TH1D*)(h_data->Clone()); 
TH1D *pull_Fit_moddijet = (TH1D*)(h_data->Clone()); 
TH1D *pull_MC = (TH1D*)(h_data->Clone());

TH1D *pull_sig_low_narrow = (TH1D*)(Standard_Fit_atlas->Clone());
TH1D *pull_sig_high_narrow = (TH1D*)(Standard_Fit_atlas->Clone());

TH1D *pull_sig_low_wide = (TH1D*)(Standard_Fit_atlas->Clone());
TH1D *pull_sig_high_wide = (TH1D*)(Standard_Fit_atlas->Clone());


h_data->SetMarkerStyle(8);
h_data->SetLineColor(1);
h_data->SetMarkerColor(1);
h_data->GetXaxis()->SetRangeUser(startit,endit);
	
		

//rescaling prediction, standard fit and data to the differential cross section
for(int i=0; i<Standard_Fit_atlas->GetNbinsX(); i++)
{

        if (Standard_Fit_atlas->GetBinContent(i) < 30) Standard_Fit_atlas->SetBinError(i, 0.5 + sqrt( Standard_Fit_atlas->GetBinContent(i) + 0.25 ) );  
	Standard_Fit_atlas->SetBinContent(i,1000*Standard_Fit_atlas->GetBinContent(i)/((Standard_Fit_atlas->GetBinLowEdge(i+1)-Standard_Fit_atlas->GetBinLowEdge(i))*lumi));
	Standard_Fit_atlas->SetBinError(i,1000*Standard_Fit_atlas->GetBinError(i)/((Standard_Fit_atlas->GetBinLowEdge(i+1)-Standard_Fit_atlas->GetBinLowEdge(i))*lumi));
        

        if (Standard_Fit_dijet->GetBinContent(i) < 30) Standard_Fit_dijet->SetBinError(i, 0.5 + sqrt( Standard_Fit_dijet->GetBinContent(i) + 0.25 ) ); 
        Standard_Fit_dijet->SetBinContent(i,1000*Standard_Fit_dijet->GetBinContent(i)/((Standard_Fit_dijet->GetBinLowEdge(i+1)-Standard_Fit_dijet->GetBinLowEdge(i))*lumi));
        Standard_Fit_dijet->SetBinError(i,1000*Standard_Fit_dijet->GetBinError(i)/((Standard_Fit_dijet->GetBinLowEdge(i+1)-Standard_Fit_dijet->GetBinLowEdge(i))*lumi)); 

        if (Standard_Fit_moddijet->GetBinContent(i) < 30) Standard_Fit_moddijet->SetBinError(i, 0.5 + sqrt( Standard_Fit_moddijet->GetBinContent(i) + 0.25 ) ); 
        Standard_Fit_moddijet->SetBinContent(i,1000*Standard_Fit_moddijet->GetBinContent(i)/((Standard_Fit_moddijet->GetBinLowEdge(i+1)-Standard_Fit_moddijet->GetBinLowEdge(i))*lumi));
        Standard_Fit_moddijet->SetBinError(i,1000*Standard_Fit_moddijet->GetBinError(i)/((Standard_Fit_moddijet->GetBinLowEdge(i+1)-Standard_Fit_moddijet->GetBinLowEdge(i))*lumi)); 

        h_MC->SetBinContent(i,1000*h_MC->GetBinContent(i)/((h_MC->GetBinLowEdge(i+1)-h_MC->GetBinLowEdge(i))*lumi));
        h_MC->SetBinError(i,1000*h_MC->GetBinError(i)/((h_MC->GetBinLowEdge(i+1)-h_MC->GetBinLowEdge(i))*lumi));           
              
        if (h_data->GetBinContent(i) < 30) h_data->SetBinError(i, 0.5 + sqrt( h_data->GetBinContent(i) + 0.25 ) ); 
	if (h_data->GetBinContent(i)==0) h_data->SetBinError(i,1.);
	h_data->SetBinContent(i,1000*h_data->GetBinContent(i)/((h_data->GetBinLowEdge(i+1)-h_data->GetBinLowEdge(i))*lumi));
	h_data->SetBinError(i,1000*h_data->GetBinError(i)/((h_data->GetBinLowEdge(i+1)-h_data->GetBinLowEdge(i))*lumi));

	h_sig_low_narrow->SetBinContent(i,1000*h_sig_low_narrow->GetBinContent(i)/((h_sig_low_narrow->GetBinLowEdge(i+1)-h_sig_low_narrow->GetBinLowEdge(i))*lumi));
        h_sig_high_narrow->SetBinContent(i,1000*h_sig_high_narrow->GetBinContent(i)/((h_sig_high_narrow->GetBinLowEdge(i+1)-h_sig_high_narrow->GetBinLowEdge(i))*lumi));
        
        h_sig_low_wide->SetBinContent(i,1000*h_sig_low_wide->GetBinContent(i)/((h_sig_low_wide->GetBinLowEdge(i+1)-h_sig_low_wide->GetBinLowEdge(i))*lumi));
        h_sig_high_wide->SetBinContent(i,1000*h_sig_high_wide->GetBinContent(i)/((h_sig_high_wide->GetBinLowEdge(i+1)-h_sig_high_wide->GetBinLowEdge(i))*lumi));
}

//creating pulls and calculate chi square for the two methods: 
double  chi_square_Fit_atlas = 0;
int     NDF_Fit_atlas = -5;  // 5 parameter function is used for Standard Fit	  
double  chi_square_Fit_dijet = 0;
int	NDF_Fit_dijet = -5;  //     
double  chi_square_Fit_moddijet = 0;
int	NDF_Fit_moddijet = -5;  // 

TGraphAsymmErrors *h_datag = new TGraphAsymmErrors(h_data);
	
for(Int_t i=1;i<=h_data->GetNbinsX();i++)
{

	double edata = h_data->GetBinError(i); 
	double alpha = 1-0.6827;
	double cont = h_data->GetBinContent(i)*((h_data->GetBinLowEdge(i+1)-h_data->GetBinLowEdge(i))*lumi)/1000.;
        double errl,errh;

        cout << " in the loop " << i << " cont " << cont << endl;

        if(cont<=0) errl = 0;
        if(cont<=0) errh = 1.8;

        if(cont>0)
        {
		errl = cont - ROOT::Math::gamma_quantile(alpha/2,cont,1.);
		errh = ROOT::Math::gamma_quantile_c(alpha/2,cont+1,1.)-cont;
        }


        errl = errl*1000./((h_data->GetBinLowEdge(i+1)-h_data->GetBinLowEdge(i))*lumi);
        errh = errh*1000./((h_data->GetBinLowEdge(i+1)-h_data->GetBinLowEdge(i))*lumi);
                
                
	h_datag->SetPointEYlow(i-1, errl); 
        h_datag->SetPointEYhigh(i-1, errh);
        
	double data_cont    = h_data->GetBinContent(i);
	double m4j   	      = h_data->GetBinCenter(i);
	double Fit_atlas_cont       = Standard_Fit_atlas->GetBinContent(i);
        double Fit_dijet_cont       = Standard_Fit_dijet->GetBinContent(i);
        double Fit_moddijet_cont    = Standard_Fit_moddijet->GetBinContent(i);
        double MC_cont    = h_MC->GetBinContent(i);
	double sig_low_narrow_cont = h_sig_low_narrow->GetBinContent(i);
	double sig_high_narrow_cont = h_sig_high_narrow->GetBinContent(i);
	double sig_low_wide_cont = h_sig_low_wide->GetBinContent(i);
	double sig_high_wide_cont = h_sig_high_wide->GetBinContent(i);
	
	if(edata>0)
	{ 
 		if(data_cont>Fit_atlas_cont) pull_Fit_atlas->SetBinContent(i,(-Fit_atlas_cont+data_cont)/errl);
                if(data_cont<Fit_atlas_cont) pull_Fit_atlas->SetBinContent(i,(-Fit_atlas_cont+data_cont)/errh); 
		
		if(data_cont>Fit_dijet_cont) pull_Fit_dijet->SetBinContent(i,(-Fit_dijet_cont+data_cont)/errl);
                if(data_cont<Fit_dijet_cont) pull_Fit_dijet->SetBinContent(i,(-Fit_dijet_cont+data_cont)/errh); 	
			
                if(data_cont>Fit_moddijet_cont) pull_Fit_moddijet->SetBinContent(i,(-Fit_moddijet_cont+data_cont)/errl);
                if(data_cont<Fit_moddijet_cont) pull_Fit_moddijet->SetBinContent(i,(-Fit_moddijet_cont+data_cont)/errh); 
                
                pull_MC->SetBinContent(i,(-MC_cont+data_cont)/edata);
                
		pull_sig_low_narrow->SetBinContent(i,sig_low_narrow_cont/edata);
		pull_sig_high_narrow->SetBinContent(i,sig_high_narrow_cont/edata);
		
		pull_sig_low_wide->SetBinContent(i,sig_low_wide_cont/edata);
		pull_sig_high_wide->SetBinContent(i,sig_high_wide_cont/edata);
		
		
		if(m4j>=startit && m4j<= endit)
		{	
			
			chi_square_Fit_atlas = chi_square_Fit_atlas + pull_Fit_atlas->GetBinContent(i)*pull_Fit_atlas->GetBinContent(i);
			NDF_Fit_atlas        = NDF_Fit_atlas + 1 ;

                        chi_square_Fit_dijet = chi_square_Fit_dijet + pull_Fit_dijet->GetBinContent(i)*pull_Fit_dijet->GetBinContent(i);
                        NDF_Fit_dijet        = NDF_Fit_dijet + 1 ;

                        chi_square_Fit_moddijet = chi_square_Fit_moddijet + pull_Fit_moddijet->GetBinContent(i)*pull_Fit_moddijet->GetBinContent(i);
                        NDF_Fit_moddijet        = NDF_Fit_moddijet + 1 ;                          
		}
	}

	if(cont==0)
	{
		h_datag->SetPointY(i-1,0.0000000000001);
		h_datag->SetPointEYlow(i-1, 0); 
		h_datag->SetPointEYhigh(i-1, 0);
	}

	h_datag->SetPointEXlow(i-1,0);
	h_datag->SetPointEXhigh(i-1,0);

}


h_sig_low_narrow->GetXaxis()->SetRangeUser(1530,5058);
h_sig_low_narrow->SetLineStyle(1);
h_sig_low_narrow->SetLineColor(kBlue);
h_sig_low_narrow->SetLineWidth(2);		
pull_sig_low_narrow->GetXaxis()->SetRangeUser(1530,5058);
pull_sig_low_narrow->SetLineStyle(1);
pull_sig_low_narrow->SetLineColor(kBlue);
pull_sig_low_narrow->SetLineWidth(3);
	
	
h_sig_high_narrow->GetXaxis()->SetRangeUser(2132,9067);
h_sig_high_narrow->SetLineColor(kGreen+3); //kOrange+1
h_sig_high_narrow->SetLineStyle(1);
h_sig_high_narrow->SetLineWidth(2);	
pull_sig_high_narrow->GetXaxis()->SetRangeUser(2132,9067);
pull_sig_high_narrow->SetLineStyle(1);
pull_sig_high_narrow->SetLineColor(kGreen+3); //kOrange+1
pull_sig_high_narrow->SetLineWidth(3);        
	



h_sig_low_wide->GetXaxis()->SetRangeUser(1530,5058);
h_sig_low_wide->SetLineStyle(1);
h_sig_low_wide->SetLineColor(kCyan-3);
h_sig_low_wide->SetLineWidth(2);		
pull_sig_low_wide->GetXaxis()->SetRangeUser(1530,5058);
pull_sig_low_wide->SetLineStyle(1);
pull_sig_low_wide->SetLineColor(kCyan-3);
pull_sig_low_wide->SetLineWidth(3);

	
h_sig_high_wide->GetXaxis()->SetRangeUser(2132,9067);
h_sig_high_wide->SetLineColor(kGreen); //kYellow-6
h_sig_high_wide->SetLineStyle(1);
h_sig_high_wide->SetLineWidth(2);	
pull_sig_high_wide->GetXaxis()->SetRangeUser(2132,9067);
pull_sig_high_wide->SetLineStyle(1);
pull_sig_high_wide->SetLineColor(kGreen); //kYellow-6
pull_sig_high_wide->SetLineWidth(3); 


Standard_Fit_atlas->SetLineColor(2);
Standard_Fit_atlas->SetMarkerColor(2);
Standard_Fit_atlas->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_atlas->GetYaxis()->SetRangeUser(0.00000005,200000.);

Standard_Fit_dijet->SetLineColor(4);
Standard_Fit_dijet->SetMarkerColor(4);
Standard_Fit_dijet->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_dijet->GetYaxis()->SetRangeUser(0.00000005,200000.);
        
Standard_Fit_moddijet->SetLineColor(2);
Standard_Fit_moddijet->SetMarkerColor(2);
Standard_Fit_moddijet->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_moddijet->GetYaxis()->SetRangeUser(0.00000005,200000.);

h_MC->SetLineColor(5);
h_MC->SetMarkerColor(5);
h_MC->GetXaxis()->SetRangeUser(startit,endit);
h_MC->GetYaxis()->SetRangeUser(0.00000005,400000.);

pull_Fit_atlas->SetLineColor(2);
pull_Fit_atlas->SetMarkerColor(2);
pull_Fit_atlas->GetXaxis()->SetRangeUser(startit,endit);
pull_Fit_atlas->GetYaxis()->SetRangeUser(-3.4,3.4);

pull_Fit_dijet->SetLineColor(4);  
pull_Fit_dijet->SetMarkerColor(4);
pull_Fit_dijet->GetXaxis()->SetRangeUser(startit,endit);
pull_Fit_dijet->GetYaxis()->SetRangeUser(-3.4,3.4);

pull_Fit_moddijet->SetLineColor(2);  
pull_Fit_moddijet->SetMarkerColor(2);
pull_Fit_moddijet->GetXaxis()->SetRangeUser(startit,endit);
pull_Fit_moddijet->GetYaxis()->SetRangeUser(-3.4,3.4);
       
Standard_Fit_atlas->SetTitle("");
Standard_Fit_dijet->SetTitle("");
Standard_Fit_moddijet->SetTitle("");


Standard_Fit_atlas->SetStats(0);
Standard_Fit_dijet->SetStats(0);
Standard_Fit_moddijet->SetStats(0);
pull_Fit_atlas->SetStats(0);
pull_Fit_dijet->SetStats(0);
pull_Fit_moddijet->SetStats(0);

			


TCanvas *c1 = new TCanvas("c1","Signal region Data & Prediction",900,900);
c1->Divide(1,2,0,0,0);
	 
	 
TVirtualPad *pad1r; 
pad1r = c1->GetPad(1);
pad1r->SetPad(0.01,0.29,0.99,1.);
pad1r->SetRightMargin(0.05);
pad1r->SetTopMargin(0.08); 
pad1r->SetLeftMargin(0.175);
pad1r->SetBottomMargin(0.01);
pad1r->SetFillColor(0);
pad1r->SetBorderMode(0);
pad1r->SetFrameFillStyle(0);
pad1r->SetFrameBorderMode(0);
pad1r->Draw();
pad1r->cd();
pad1r->cd()->SetLogy(1);
pad1r->cd()->SetLogx(1);
pad1r->cd()->SetTickx(1);
pad1r->cd()->SetTicky(1);

Standard_Fit_atlas->GetXaxis()->SetTickSize(0.04);

Standard_Fit_atlas->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_atlas->GetYaxis()->SetTitleSize(0.065); 
Standard_Fit_atlas->GetYaxis()->SetLabelSize(0.040);
Standard_Fit_atlas->GetYaxis()->SetTitleOffset(1.15);
Standard_Fit_atlas->SetFillColor(0); 
Standard_Fit_atlas->SetLineWidth(2);
Standard_Fit_atlas->SetLineColor(2);
Standard_Fit_atlas->SetLineStyle(3);
Standard_Fit_atlas->Draw("l hist");

Standard_Fit_dijet->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_dijet->GetYaxis()->SetTitleSize(0.07); 
Standard_Fit_dijet->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_dijet->GetYaxis()->SetTitleOffset(0.9);
Standard_Fit_dijet->SetFillColor(0);
Standard_Fit_dijet->SetLineWidth(2);
Standard_Fit_dijet->SetLineColor(2); 
Standard_Fit_dijet->SetLineStyle(2);
Standard_Fit_dijet->Draw("l hist same");

Standard_Fit_moddijet->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_moddijet->GetYaxis()->SetTitleSize(0.07); 
Standard_Fit_moddijet->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_moddijet->GetYaxis()->SetTitleOffset(0.9);
Standard_Fit_moddijet->SetFillColor(0);
Standard_Fit_moddijet->SetLineWidth(2);
Standard_Fit_moddijet->SetLineColor(2); 
Standard_Fit_moddijet->SetLineStyle(1);
Standard_Fit_moddijet->Draw("l hist same");

h_MC->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
h_MC->GetYaxis()->SetTitleSize(0.07); 
h_MC->GetYaxis()->SetLabelSize(0.06);
h_MC->GetYaxis()->SetTitleOffset(0.9);
h_MC->SetFillColor(0);
h_MC->SetLineWidth(2);
h_MC->SetLineColor(3);
h_MC->Scale(h_data->Integral()/h_MC->Integral());
//h_MC->Draw("hist same ][");

h_datag->Draw("same ep");


h_sig_low_narrow->Draw("same hist ][");
h_sig_high_narrow->Draw("same hist ][");

h_sig_low_wide->Draw("same hist ][");
h_sig_high_wide->Draw("same hist ][");


TPaveText *pave3 = new TPaveText(0.23,0.35,0.34,0.45,"NDC");
pave3->AddText("All #alpha bins");
pave3->AddText("(#alpha > 0.1)");
pave3->SetFillColor(0);
pave3->SetBorderSize(0);
pave3->SetTextFont(42);
pave3->SetTextSize(0.045);
pave3->Draw("same");

TLegend *leg = new TLegend(0.23,0.59,0.44,0.82);
leg->AddEntry(h_datag, "Data ","pe");
//leg->AddEntry(h_MC, "LO QCD MC","l");
leg->AddEntry(Standard_Fit_atlas, "PowExp-5p fit","l");
leg->AddEntry(Standard_Fit_moddijet, "ModDijet-5p fit","l");
leg->AddEntry(Standard_Fit_dijet, "Dijet-5p fit","l");
leg->SetTextSize(0.042);
leg->SetBorderSize(0);
leg->Draw("same");


TLegend *leg2 = new TLegend(0.495,0.49,0.725,0.90);
leg2->AddEntry((TObject*)0,"uu #rightarrow S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)","");
leg2->AddEntry((TObject*)0,"M_{S} = 8.6 TeV, #alpha_{true} = 0.25","");
leg2->AddEntry(h_sig_high_narrow,"#Gamma / M_{S} = 1.5%","l");
leg2->AddEntry(h_sig_high_wide,"#Gamma / M_{S} = 10%","l");
leg2->AddEntry((TObject*)0,"M_{S} = 3.6 TeV, #alpha_{true} = 0.29","");
leg2->AddEntry(h_sig_low_narrow,"#Gamma / M_{S} = 1.5%","l");
leg2->AddEntry(h_sig_low_wide,"#Gamma / M_{S} = 10%","l");
leg2->SetTextSize(0.045);
leg2->SetBorderSize(0);	
leg2->Draw("same"); 
  
TLatex *l = new TLatex();     
l->SetTextAlign(11);
l->SetTextSize(0.085); //0.072 PAS
l->SetNDC();
l->SetTextFont(42);
//l->DrawLatex(0.1768,0.935,"#bf{CMS} #scale[0.7]{#it{Preliminary}}");
//l->DrawLatex(0.176,0.935,"#bf{CMS}");
l->DrawLatex(0.208,0.837,"#bf{CMS}");
l->SetTextSize(0.057);
l->DrawLatex(0.675,0.936,"138 fb^{-1} (13 TeV)");
	
		
c1->cd();

TVirtualPad *pad2r ;
pad2r = c1->GetPad(2);
pad2r->SetLeftMargin(0.175);
pad2r->SetPad(0.01,0.,0.99,0.28);
pad2r->SetBottomMargin(0.3); 
pad2r->SetRightMargin(0.05);
pad2r->Draw();
pad2r->cd(); 
pad2r->cd()->SetLogx(1);
pad2r->cd()->SetTickx(1);
pad2r->cd()->SetTicky(1);

pull_Fit_atlas->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_Fit_atlas->GetXaxis()->SetNoExponent();
pull_Fit_atlas->GetXaxis()->SetMoreLogLabels();
pull_Fit_atlas->GetXaxis()->SetTitleSize(2*0.07); 
pull_Fit_atlas->GetYaxis()->SetTitleSize(2*0.07); 
pull_Fit_atlas->GetXaxis()->SetLabelSize(2*0.07);
pull_Fit_atlas->GetYaxis()->SetLabelSize(0.09);
pull_Fit_atlas->GetXaxis()->SetLabelOffset(1000);
pull_Fit_atlas->GetYaxis()->SetLabelOffset(0.02);
pull_Fit_atlas->GetXaxis()->SetTitleOffset(1.1);
pull_Fit_atlas->GetYaxis()->SetTitleOffset(0.55);
pull_Fit_atlas->GetYaxis()->SetNdivisions(210);
pull_Fit_atlas->SetLineWidth(1);

pull_Fit_dijet->GetXaxis()->SetTitle("Fourjet mass [TeV]");
pull_Fit_dijet->GetXaxis()->SetNoExponent();
pull_Fit_dijet->GetXaxis()->SetMoreLogLabels();
pull_Fit_dijet->GetXaxis()->SetTitleSize(2*0.06); 
pull_Fit_dijet->GetYaxis()->SetTitleSize(2*0.06); 
pull_Fit_dijet->GetXaxis()->SetLabelSize(2*0.07);
pull_Fit_dijet->GetYaxis()->SetLabelSize(0.09);
pull_Fit_dijet->GetYaxis()->SetLabelOffset(0.02);
pull_Fit_dijet->GetXaxis()->SetLabelOffset(1000);
pull_Fit_dijet->GetXaxis()->SetTitleOffset(1.2);
pull_Fit_dijet->GetYaxis()->SetTitleOffset(0.6);
pull_Fit_dijet->GetYaxis()->SetNdivisions(210); 
pull_Fit_dijet->SetLineWidth(1);
        
pull_Fit_moddijet->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_Fit_moddijet->GetXaxis()->SetNoExponent();
pull_Fit_moddijet->GetXaxis()->SetMoreLogLabels();
pull_Fit_moddijet->GetXaxis()->SetTitleSize(2*0.085); 
pull_Fit_moddijet->GetYaxis()->SetTitleSize(2*0.07); 
pull_Fit_moddijet->GetXaxis()->SetLabelSize(2*0.07);
pull_Fit_moddijet->GetYaxis()->SetLabelSize(0.11);
pull_Fit_moddijet->GetYaxis()->SetLabelOffset(0.02);
pull_Fit_moddijet->GetXaxis()->SetLabelOffset(1000);
pull_Fit_moddijet->GetXaxis()->SetTitleOffset(0.8);
pull_Fit_moddijet->GetYaxis()->SetTitleOffset(0.57);
pull_Fit_moddijet->GetYaxis()->SetNdivisions(210); 
pull_Fit_moddijet->SetLineWidth(1);

pull_MC->GetXaxis()->SetTitle("Fourjet mass [TeV]");
pull_MC->GetXaxis()->SetNoExponent();
pull_MC->GetXaxis()->SetMoreLogLabels();
pull_MC->GetXaxis()->SetTitleSize(2*0.06); 
pull_MC->GetYaxis()->SetTitleSize(2*0.06); 
pull_MC->GetXaxis()->SetLabelSize(2*0.07);
pull_MC->GetYaxis()->SetLabelSize(0.09);
pull_MC->GetYaxis()->SetLabelOffset(0.02);
pull_MC->GetXaxis()->SetLabelOffset(1000);
pull_MC->GetXaxis()->SetTitleOffset(1.2);
pull_MC->GetYaxis()->SetTitleOffset(0.6);
pull_MC->GetYaxis()->SetNdivisions(210); 
pull_MC->SetLineWidth(1);

pull_Fit_atlas->GetXaxis()->SetTickSize(0.08);
pull_Fit_dijet->GetXaxis()->SetTickSize(0.08);
pull_Fit_moddijet->GetXaxis()->SetTickSize(0.08);
pull_MC->GetXaxis()->SetTickSize(0.08);
pull_sig_low_narrow->GetXaxis()->SetTickSize(0.08);
pull_sig_low_wide->GetXaxis()->SetTickSize(0.08);
pull_sig_high_narrow->GetXaxis()->SetTickSize(0.08);
pull_sig_high_wide->GetXaxis()->SetTickSize(0.08);


pull_Fit_atlas->GetYaxis()->SetTickSize(0.03);
pull_Fit_dijet->GetYaxis()->SetTickSize(0.03);
pull_Fit_moddijet->GetYaxis()->SetTickSize(0.03);
pull_MC->GetYaxis()->SetTickSize(0.03);
pull_sig_low_narrow->GetYaxis()->SetTickSize(0.03);
pull_sig_low_wide->GetYaxis()->SetTickSize(0.03);
pull_sig_high_narrow->GetYaxis()->SetTickSize(0.03);
pull_sig_high_wide->GetYaxis()->SetTickSize(0.03);	

pull_Fit_atlas->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_Fit_atlas->SetFillColor(2);

pull_Fit_dijet->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_Fit_dijet->SetFillColor(4);

pull_Fit_moddijet->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_Fit_moddijet->SetFillColor(2);
pull_Fit_moddijet->GetYaxis()->CenterTitle(1);
pull_Fit_moddijet->Draw("HIST");

pull_sig_low_narrow->Draw("HIST same");  
pull_sig_high_narrow->Draw("HIST same");

pull_sig_low_wide->Draw("HIST same");  
pull_sig_high_wide->Draw("HIST same");
   
TLine *sk = new TLine(startit,0.,endit,0.);
sk->Draw("same"); 


TLatex *xLab = new TLatex();
xLab->SetTextAlign(22);
xLab->SetTextFont(42);
xLab->SetTextSize(2*0.055);         
xLab->DrawLatex(2000, -3.95, "2");
xLab->DrawLatex(3000, -3.95, "3");
xLab->DrawLatex(4000, -3.95, "4");
xLab->DrawLatex(5000, -3.95, "5");
xLab->DrawLatex(6000, -3.95, "6");
xLab->DrawLatex(7000, -3.95, "7");
xLab->DrawLatex(8000, -3.95, "8");

c1->SaveAs("plots/Figure_007.pdf");

}
