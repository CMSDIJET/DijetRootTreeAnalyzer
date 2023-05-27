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

void Plot_Combined_v6_alpha8_forindividual_yaml(){

	 double lumi 	     = 137000;    //35900 for 2016, 41850 for 2017, 77750 for 2016+2017
	 double startit	     = 1607;
	 double endit	     = 9067;
	 double startit_RM   = 1607;
	gROOT->LoadMacro("setTDRStyle.C");
	setTDRStyle();
	 //gStyle->SetOptFit(1111);
	  
	/*double gg_8TeV_obs_limit = 0.0000024;
        double qq_4TeV_obs_limit = 0.0000045;
        double qq_2TeV_obs_limit = 0.00038;*/
        double gg_8TeV_obs_limit = 0.000009;
        double qq_2TeV_obs_limit = 0.002;
        double qq_4TeV_obs_limit = 0.000017;
/*double gg_8TeV_obs_limit = 0.0000024;
        double qq_4TeV_obs_limit = 0.0000045;
        double qq_2TeV_obs_limit = 0.00038;*/
	 
	 
	 //ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 20000);   //set the number of parameter searches for convergence

	char *image_name = "_2016_2017_Shapes_tot_err_alpha8_proper";

	TFile *f_RM= new TFile("HISTOS_4J_Alldata_SR_alphabin8.root");
	TFile *f_SF_atlas= new TFile("DijetFitResult_PFDijet2017_4J_alphabin8_atlas_test.root");
        TFile *f_SF_dijet= new TFile("DijetFitResult_PFDijet2017_4J_alphabin8_dijet_test.root");
        TFile *f_SF_moddijet= new TFile("DijetFitResult_PFDijet2017_4J_alphabin8_moddijet_test.root");
        TFile *f_MC= new TFile("QCD2017_Standardcuts_M4Jgt1p6_nobreak_alpha8.root");
// Initial roofit /afs/cern.ch/work/m/mdiamant/public/forNiki/alphagt0p1/atlas/DijetFitResults_PFDijet2017_4J_alphabin8.root");

	double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

	TFile *f_gg= new TFile("ResonanceShapes_Suu8600_Chi2150_SR_alphabin8.root");
	TH1D *shape_gg_8TeV  = (TH1D*)(f_gg->Get("h_FourjetMass1GeV"));   //obs limit at 6TeV:   0.00064
	shape_gg_8TeV->Scale(gg_8TeV_obs_limit*lumi);  //scale to events

TFile *f_qq= new TFile("ResonanceShapes_Suu2000_Chi500_SR_alphabin8.root");
	TH1D *shape_qq_2TeV  = (TH1D*)(f_qq->Get("h_FourjetMass1GeV"));   //obs limit at 6TeV:   0.00064
	shape_qq_2TeV->Scale(qq_2TeV_obs_limit*lumi);  //scale to events



TFile *f_qg= new TFile("ResonanceShapes_Suu5000_Chi1250_SR_alphabin8.root");
	TH1D *shape_qq_4TeV  = (TH1D*)(f_qg->Get("h_FourjetMass1GeV"));   //obs limit at 6TeV:   0.00064
	shape_qq_4TeV->Scale(qq_4TeV_obs_limit*lumi);  //scale to events
	  
	  
	  
	TH1D *Standard_Fit_atlas      = new TH1D("Standard_Fit_atlas","Standard_Fit_atlas",103,massBoundaries);  
        TH1D *Standard_Fit_dijet      = new TH1D("Standard_Fit_dijet","Standard_Fit_dijet",103,massBoundaries);
        TH1D *Standard_Fit_moddijet      = new TH1D("Standard_Fit_moddijet","Standard_Fit_moddijet",103,massBoundaries);
        TH1D *h_MC	      = (TH1D*)(f_MC->Get("h_FourjetMass"));

	TH1D *shape_gg_binned 	      = new TH1D("shape_gg_binned","shape_gg_binned",103,massBoundaries); 
TH1D *shape_qq_binned 	      = new TH1D("shape_qq_binned","shape_qq_binned",103,massBoundaries); 
TH1D *shape_qg_binned 	      = new TH1D("shape_qg_binned","shape_qg_binned",103,massBoundaries);   
	TH1D *Standard_fit_pull_1D_atlas 	    = new TH1D("Standard_fit_pull_1D_atlas","Standard Fit Pulls",12,-4,4);
        TH1D *Standard_fit_pull_1D_dijet            = new TH1D("Standard_fit_pull_1D_dijet","Standard Fit Pulls",12,-4,4);
        TH1D *Standard_fit_pull_1D_moddijet            = new TH1D("Standard_fit_pull_1D_moddijet","Standard Fit Pulls",12,-4,4);
        TH1D *h_pull_MC            = new TH1D("h_pull_MC","MC Pulls",12,-4,4);
	TH1D *signal_data  	      = (TH1D*)(f_RM->Get("h_FourjetMass"));
	TH1D *Standard_Fit_unbinned_atlas   = (TH1D*)(f_SF_atlas->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
        TH1D *Standard_Fit_unbinned_dijet   = (TH1D*)(f_SF_dijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
        TH1D *Standard_Fit_unbinned_moddijet   = (TH1D*)(f_SF_moddijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
        TH1D *Blank                   = (TH1D*)(signal_data->Clone());
	TH1D *pull_SF_atlas        	    = (TH1D*)(signal_data->Clone());
        TH1D *pull_SF_dijet                 = (TH1D*)(signal_data->Clone()); 
        TH1D *pull_SF_moddijet                 = (TH1D*)(signal_data->Clone()); 
        TH1D *pull_MC                 = (TH1D*)(signal_data->Clone());
	TH1D *pull_qq        	      = (TH1D*)(Standard_Fit_atlas->Clone());
	TH1D *pull_qg        	      = (TH1D*)(Standard_Fit_atlas->Clone());
	TH1D *pull_gg        	      = (TH1D*)(Standard_Fit_atlas->Clone());

	signal_data->SetMarkerStyle(8);
	signal_data->SetLineColor(1);
	signal_data->SetMarkerColor(1);
	signal_data->GetXaxis()->SetRangeUser(startit,endit);
	Blank->SetMarkerColor(0); 		 //use this white-empty histogram to add blank entries on legend.
	Blank->SetLineColor(0);

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

	//rebinning 1GeV gg shape to standard binning
	for(int i=0; i<shape_gg_8TeV->GetNbinsX(); i++)
	 {
		double val   = shape_gg_8TeV->GetBinContent(i);
		double xval  = shape_gg_8TeV->GetBinCenter(i);
		shape_gg_binned->Fill(xval,val);
         }

for(int i=0; i<shape_qq_2TeV->GetNbinsX(); i++)
	 {
		double val   = shape_qq_2TeV->GetBinContent(i);
		double xval  = shape_qq_2TeV->GetBinCenter(i);
		shape_qq_binned->Fill(xval,val);
         }



for(int i=0; i<shape_qq_4TeV->GetNbinsX(); i++)
	 {
		double val   = shape_qq_4TeV->GetBinContent(i);
		double xval  = shape_qq_4TeV->GetBinCenter(i);
		shape_qg_binned->Fill(xval,val);
         }


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
              
                if (signal_data->GetBinContent(i) < 30) signal_data->SetBinError(i, 0.5 + sqrt( signal_data->GetBinContent(i) + 0.25 ) ); 
		if (signal_data->GetBinContent(i)==0) signal_data->SetBinError(i,1.);
		signal_data->SetBinContent(i,1000*signal_data->GetBinContent(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));
		signal_data->SetBinError(i,1000*signal_data->GetBinError(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));

		shape_gg_binned->SetBinContent(i,1000*shape_gg_binned->GetBinContent(i)/((shape_gg_binned->GetBinLowEdge(i+1)-shape_gg_binned->GetBinLowEdge(i))*lumi));
shape_qq_binned->SetBinContent(i,1000*shape_qq_binned->GetBinContent(i)/((shape_qq_binned->GetBinLowEdge(i+1)-shape_qq_binned->GetBinLowEdge(i))*lumi));
shape_qg_binned->SetBinContent(i,1000*shape_qg_binned->GetBinContent(i)/((shape_qg_binned->GetBinLowEdge(i+1)-shape_qg_binned->GetBinLowEdge(i))*lumi));
	 }

		//creating pulls and calculate chi square for the two methods: 
	 double chi_square_SF_atlas = 0;
	 int    NDF_SF_atlas        =-3;  // 3 parameter function is used for Standard Fit	  
	 double chi_square_SF_dijet = 0;
	 int	NDF_SF_dijet	    =-3;  //     
         double chi_square_SF_moddijet = 0;
	 int	NDF_SF_moddijet	    =-3;  // 

TGraphAsymmErrors * signal_datag = new TGraphAsymmErrors(signal_data);
	for(Int_t i=1;i<=signal_data->GetNbinsX();i++)

	 {


double edata_signal   = signal_data->GetBinError(i); 
		 double alpha = 1-0.6827;
		 double cont = signal_data->GetBinContent(i)*((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi)/1000.;
                 double errl,errh;

                 cout << " in the loop " << i << " cont " << cont << endl;

                 if(cont<=0) errl = 0;
                 if(cont<=0) errh = 1.8;

                 //if(cont>0 && cont < 20){
                 if(cont>0){
		   errl = cont - ROOT::Math::gamma_quantile(alpha/2,cont,1.);
		   errh = ROOT::Math::gamma_quantile_c(alpha/2,cont+1,1.)-cont;
                 }

                 //if(cont>0 && cont >= 20){
                   //errl = sqrt(cont); 
                   //errh = sqrt(cont);
                 //}

                errl = errl*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
                errh = errh*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
                double edata_signal2 = ( errl + errh )/2.;
                


//signal_data->SetPoint(i-1,signal_data
	        signal_datag->SetPointEYlow(i-1, errl); 
                signal_datag->SetPointEYhigh(i-1, errh);
		//double edata_signal   = signal_data->GetBinError(i); 
		double data_signal    = signal_data->GetBinContent(i);
		double mjj   	      = signal_data->GetBinCenter(i);
		double SF_atlas       = Standard_Fit_atlas->GetBinContent(i);
                double SF_dijet       = Standard_Fit_dijet->GetBinContent(i);
                double SF_moddijet    = Standard_Fit_moddijet->GetBinContent(i);
                double MC    = h_MC->GetBinContent(i);
		double gg	      = shape_gg_binned->GetBinContent(i);
double qq	      = shape_qq_binned->GetBinContent(i);
double qg	      = shape_qg_binned->GetBinContent(i);
		if(edata_signal>0)
		 { 
			pull_SF_atlas->SetBinContent(i,0);
 if(data_signal>SF_atlas) pull_SF_atlas->SetBinContent(i,(-SF_atlas+data_signal)/errl);
              if(data_signal<SF_atlas) pull_SF_atlas->SetBinContent(i,(-SF_atlas+data_signal)/errh); 
			
                        pull_SF_dijet->SetBinContent(i,0);
                        pull_SF_dijet->SetBinContent(i,(-SF_dijet+data_signal)/edata_signal);
                        if(data_signal>SF_moddijet) pull_SF_moddijet->SetBinContent(i,(-SF_moddijet+data_signal)/errl);
              if(data_signal<SF_moddijet) pull_SF_moddijet->SetBinContent(i,(-SF_moddijet+data_signal)/errh); 
                        pull_MC->SetBinContent(i,0);
                        pull_MC->SetBinContent(i,(-MC+data_signal)/edata_signal);
			pull_gg->SetBinContent(i,gg/edata_signal);
//if (data_signal==0)pull_gg->SetBinContent(i,gg/errh);
pull_qq->SetBinContent(i,qq/edata_signal);
pull_qg->SetBinContent(i,qg/edata_signal);

cout << "mjj " << mjj << " gg " << gg  << " error " << edata_signal2 << gg/edata_signal2 << " error low " << errl << " error high " << errh << endl;

			if(mjj>=startit && mjj<= endit )
			 {	
				Standard_fit_pull_1D_atlas->Fill(pull_SF_atlas->GetBinContent(i));
                                Standard_fit_pull_1D_dijet->Fill(pull_SF_dijet->GetBinContent(i));
                                Standard_fit_pull_1D_moddijet->Fill(pull_SF_dijet->GetBinContent(i));
                                pull_MC->Fill(pull_MC->GetBinContent(i));

				chi_square_SF_atlas = chi_square_SF_atlas + pull_SF_atlas->GetBinContent(i)*pull_SF_atlas->GetBinContent(i);
				NDF_SF_atlas        = NDF_SF_atlas + 1 ;

                                chi_square_SF_dijet = chi_square_SF_dijet + pull_SF_dijet->GetBinContent(i)*pull_SF_dijet->GetBinContent(i);
                                NDF_SF_dijet        = NDF_SF_dijet + 1 ;


                                chi_square_SF_moddijet = chi_square_SF_moddijet + pull_SF_moddijet->GetBinContent(i)*pull_SF_moddijet->GetBinContent(i);
                                NDF_SF_moddijet        = NDF_SF_moddijet + 1 ;
                          


			 }
		 }

//if(cont==0) {
//signal_datag->SetPointY(i-1,0.0000000000001);
//signal_datag->SetPointEYlow(i-1, 0); 
//signal_datag->SetPointEYhigh(i-1, 0);
//}

	 } 

	shape_gg_8TeV->Scale(1000/lumi);
shape_qq_2TeV->Scale(1000/lumi);
shape_qq_4TeV->Scale(1000/lumi);

	TPaveText *paveCMS = new TPaveText(0.16,0.03,0.93,0.27,"NDC");
	paveCMS->AddText("CMS Preliminary    #sqrt{s} = 13 TeV       L = 137 fb^{-1}");
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
	paveCMS2->AddText("AK4CHS PF-jets"); 
	Char_t pave[1024];
	sprintf(pave,"m_{jjjj} > %3.2f TeV",startit/1000.);   
	paveCMS2->AddText(pave);
	paveCMS2->AddText("|#eta| < 2.5, |#Delta#eta| < 1.1");
	Char_t chi_sq_SF_atlas[1024];
        double prob=TMath::Prob(chi_square_SF_atlas,NDF_SF_atlas);
	/*sprintf(chi_sq_SF_atlas,"#chi^{2}/NDF = 19.9 / 26. 0.8");    
	Char_t chi_sq_SF_dijet[1024];
        prob=TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet);
	sprintf(chi_sq_SF_dijet,"#chi^{2}/NDF = 20.9 / 26. 0.8");     
        Char_t chi_sq_SF_moddijet[1024];
        prob=TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet);
	sprintf(chi_sq_SF_moddijet,"#chi^{2}/NDF = 20.7 / 26. 0.8");*/ 
TPaveText *paveCMS3 = new TPaveText(0.16,0.03,0.93,0.27,"NDC");
	paveCMS3->AddText("CMS Preliminary");
	paveCMS3->SetFillColor(0);
	paveCMS3->SetBorderSize(0);
	paveCMS3->SetTextSize(0.04);






sprintf(chi_sq_SF_atlas,"#chi^{2}/NDF = 24.2 / 27. 0.6");    
	Char_t chi_sq_SF_dijet[1024];
        prob=TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet);
	sprintf(chi_sq_SF_dijet,"#chi^{2}/NDF = 27.1 / 27. 0.5");     
        Char_t chi_sq_SF_moddijet[1024];
        prob=TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet);
	sprintf(chi_sq_SF_moddijet,"#chi^{2}/NDF = 25.7 / 27. 0.5"); 

//alpha 8

/*sprintf(chi_sq_SF_atlas,"#chi^{2}/NDF = 26.1 / 25. 0.4");    
	Char_t chi_sq_SF_dijet[1024];
        prob=TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet);
	sprintf(chi_sq_SF_dijet,"#chi^{2}/NDF = 29.7 / 25. 0.2");     
        Char_t chi_sq_SF_moddijet[1024];
        prob=TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet);
	sprintf(chi_sq_SF_moddijet,"#chi^{2}/NDF = 27.9 / 25. 0.3"); */

//alpha 9

/*sprintf(chi_sq_SF_atlas,"#chi^{2}/NDF = 19.9 / 26. 0.8");    
	Char_t chi_sq_SF_dijet[1024];
        prob=TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet);
	sprintf(chi_sq_SF_dijet,"#chi^{2}/NDF = 21.7 / 26. 0.7");     
        Char_t chi_sq_SF_moddijet[1024];
        prob=TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet);
	sprintf(chi_sq_SF_moddijet,"#chi^{2}/NDF = 20.7 / 26. 0.8");*/

//alpha 10


/*sprintf(chi_sq_SF_atlas,"#chi^{2}/NDF = 29.6 / 23. 0.2");    
	Char_t chi_sq_SF_dijet[1024];
        prob=TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet);
	sprintf(chi_sq_SF_dijet,"#chi^{2}/NDF = 30.2 / 23. 0.2");     
        Char_t chi_sq_SF_moddijet[1024];
        prob=TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet);
	sprintf(chi_sq_SF_moddijet,"#chi^{2}/NDF = 29.7/ 23. 0.2"); */


//alpha 11
/*sprintf(chi_sq_SF_atlas,"#chi^{2}/NDF = 22.3 / 25. 0.6");    
	Char_t chi_sq_SF_dijet[1024];
        prob=TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet);
	sprintf(chi_sq_SF_dijet,"#chi^{2}/NDF = 23.1 / 25. 0.6");     
        Char_t chi_sq_SF_moddijet[1024];
        prob=TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet);
	sprintf(chi_sq_SF_moddijet,"#chi^{2}/NDF = 22.6 / 25. 0.6"); */


//alpha 12

/*sprintf(chi_sq_SF_atlas,"#chi^{2}/NDF = 25.4 / 25. 0.4");    
	Char_t chi_sq_SF_dijet[1024];
        prob=TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet);
	sprintf(chi_sq_SF_dijet,"#chi^{2}/NDF = 26. / 25. 0.4");     
        Char_t chi_sq_SF_moddijet[1024];
        prob=TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet);
	sprintf(chi_sq_SF_moddijet,"#chi^{2}/NDF = 25.7 / 25. 0.4"); */


//alpha 13 
/*sprintf(chi_sq_SF_atlas,"#chi^{2}/NDF = 14.5 / 21. 0.7");    
	Char_t chi_sq_SF_dijet[1024];
        prob=TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet);
	sprintf(chi_sq_SF_dijet,"#chi^{2}/NDF = 14.4/ 21. 0.9");     
        Char_t chi_sq_SF_moddijet[1024];
        prob=TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet);
	sprintf(chi_sq_SF_moddijet,"#chi^{2}/NDF = 14.4 / 21. 0.8"); */







	shape_gg_binned->SetLineColor(4);
	shape_gg_binned->GetXaxis()->SetRangeUser(7000,9000);
	shape_gg_binned->SetLineStyle(1);
	pull_gg->GetXaxis()->SetRangeUser(7000,9000);
	pull_gg->SetLineStyle(1);
	pull_gg->SetLineColor(4);
shape_qq_binned->SetLineColor(4);
	shape_qq_binned->GetXaxis()->SetRangeUser(1600,2300);
	shape_qq_binned->SetLineStyle(3);
	pull_qq->GetXaxis()->SetRangeUser(1600,2700);
	pull_qq->SetLineStyle(3);
	pull_qq->SetLineColor(4);



shape_qg_binned->SetLineColor(4);
	shape_qg_binned->GetXaxis()->SetRangeUser(4000,6000);
	shape_qg_binned->SetLineStyle(2);
	pull_qg->GetXaxis()->SetRangeUser(4000,6000);
	pull_qg->SetLineStyle(2);
	pull_qg->SetLineColor(4);


shape_gg_binned->SetLineWidth(2);
shape_qq_binned->SetLineWidth(2);
shape_qg_binned->SetLineWidth(2);
pull_qq->SetLineWidth(2);
pull_qg->SetLineWidth(2);
pull_gg->SetLineWidth(2);			

        TLegend *leg = new TLegend(0.65,0.5,0.85,0.9); //0.6,0.5,0.8,0.9
        leg->AddEntry(signal_datag,   "Data ","pe");
        leg->AddEntry(h_MC,  "LO QCD MC","l");
        leg->AddEntry(Standard_Fit_atlas,  "PowExp-3p fit","l");
        leg->AddEntry(Standard_Fit_moddijet,  "ModDijet-3p fit","l");
         leg->AddEntry(Standard_Fit_dijet,  "Dijet-3p fit","l");
/*leg->AddEntry(Blank,"Diquark: S_{uu}#rightarrow#chi#chi#rightarrow(ug)(ug)","l");
        //leg2->AddEntry(Blank,"m_{#chi}/M_{S}=0.25, y_{uu}=0.4,y_{x}=0.6","l");
        leg->AddEntry(shape_gg_binned,"M(S_{uu})=8600 GeV","l");
        leg->AddEntry(shape_qg_binned,"M(S_{uu})=5000 GeV","l");
        leg->AddEntry(shape_qq_binned,"M(S_{uu})=2000 GeV","l");
        leg->AddEntry(Blank,"M(#chi)/M(S_{uu})=0.25");
        //leg->AddEntry(Blank,  chi_sq_SF_dijet,"p");*/
        leg->SetTextSize(0.04);

TLegend *leg2 = new TLegend(0.2,0.03,0.5,0.39);
leg2->AddEntry(Blank,"Diquark: S #rightarrow #chi#chi #rightarrow (ug) (ug)","l");
        //leg2->AddEntry(Blank,"m_{#chi}/M_{S}=0.25, y_{uu}=0.4,y_{x}=0.6","l");
        leg2->AddEntry(shape_gg_binned,"M(S) = 8.6 TeV","l");
        leg2->AddEntry(shape_qg_binned,"M(S) = 5.0 TeV","l");
        leg2->AddEntry(shape_qq_binned,"M(S) = 2.0 TeV","l");
        leg2->AddEntry(Blank,"M(#chi)/M(S) = 0.25");
leg2->SetTextSize(0.04);

	Standard_Fit_atlas->SetLineColor(2);
	Standard_Fit_atlas->SetMarkerColor(2);
	Standard_Fit_atlas->GetXaxis()->SetRangeUser(startit,endit);
	Standard_Fit_atlas->GetYaxis()->SetRangeUser(0.00000000015,1000.);

        Standard_Fit_dijet->SetLineColor(4);
        Standard_Fit_dijet->SetMarkerColor(4);
        Standard_Fit_dijet->GetXaxis()->SetRangeUser(startit,endit);
        Standard_Fit_dijet->GetYaxis()->SetRangeUser(0.00000000015,1000.);

        
        Standard_Fit_moddijet->SetLineColor(2);
        Standard_Fit_moddijet->SetMarkerColor(2);
        Standard_Fit_moddijet->GetXaxis()->SetRangeUser(startit,endit);
        Standard_Fit_moddijet->GetYaxis()->SetRangeUser(0.000000000015,1000.);



        
        h_MC->SetLineColor(5);
        h_MC->SetMarkerColor(5);
        h_MC->GetXaxis()->SetRangeUser(startit,endit);
        h_MC->GetYaxis()->SetRangeUser(0.000000000015,1000.);



	pull_SF_atlas->SetLineColor(2);
	pull_SF_atlas->SetMarkerColor(2);
       // oull_SF_atlas->SetM
	pull_SF_atlas->GetXaxis()->SetRangeUser(startit,endit);
	pull_SF_atlas->GetYaxis()->SetRangeUser(-2.99,2.99);

        pull_SF_dijet->SetLineColor(4);  
        pull_SF_dijet->SetMarkerColor(4);
        pull_SF_dijet->GetXaxis()->SetRangeUser(startit,endit);
        pull_SF_dijet->GetYaxis()->SetRangeUser(-2.99,2.99);


        pull_SF_moddijet->SetLineColor(2);  
        pull_SF_moddijet->SetMarkerColor(2);
        pull_SF_moddijet->GetXaxis()->SetRangeUser(startit,endit);
        pull_SF_moddijet->GetYaxis()->SetRangeUser(-2.99,2.99);
       
       
	TCanvas *c1 = new TCanvas("c1","Signal region Data & Prediction",600,700);
	c1->Divide(1,2,0,0,0);
	
	TVirtualPad *pad1r; 
	pad1r = c1->GetPad(1);
	pad1r->SetPad(0.01,0.37,0.99,0.98);
	pad1r->SetRightMargin(0.05);
	pad1r->SetTopMargin(0.07); //0.05
	pad1r->SetLeftMargin(0.175);
	pad1r->SetFillColor(0);
	pad1r->SetBorderMode(0);
	pad1r->SetFrameFillStyle(0);
	pad1r->SetFrameBorderMode(0);
	pad1r->Draw();
	pad1r->cd();
	pad1r->cd()->SetLogy(1);
	pad1r->cd()->SetLogx(1);
	Standard_Fit_atlas->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
	Standard_Fit_atlas->GetYaxis()->SetTitleSize(0.07);
	Standard_Fit_atlas->GetYaxis()->SetLabelSize(0.06);
 	Standard_Fit_atlas->GetYaxis()->SetTitleOffset(0.97);
	Standard_Fit_atlas->SetFillColor(0); 
	Standard_Fit_atlas->SetLineWidth(2);
	Standard_Fit_atlas->SetLineColor(2);
        Standard_Fit_atlas->SetLineStyle(3);
	Standard_Fit_atlas->Draw("l hist");
//
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
 h_MC->Scale(signal_data->Integral()/h_MC->Integral());
        h_MC->Draw("hist same ][");

TPaveText *pave3 = new TPaveText(0.2,0.7,0.5,0.8,"NDC");
 pave3->AddText("0.24 < #alpha < 0.26");
  pave3->SetFillColor(0);
  pave3->SetBorderSize(0);
  //pave3->SetTextFont(42);
  pave3->SetTextSize(0.06);
  pave3->Draw("same");




	signal_datag->Draw("same ep");
	leg->Draw("same");
       leg2->Draw("same"); 
    TLatex *l = new TLatex();     
    l->SetTextAlign(11);
    l->SetTextSize(0.055);
    l->SetNDC();
    //l->SetTextFont(62);
  //  l->DrawLatex(0.2,0.88,"CMS Preliminary");
l->SetTextFont(42); // or 43  (the last digit refers to how you express the size if infraction or points○
l->DrawLatex(0.23,0.84,"#bf{CMS} #scale[0.7]{#it{Preliminary}}"); //for PAS - ilias
//l->DrawLatex(0.23,0.84,"#bf{CMS}"); //for PAPER - ilias
    //l->SetTextFont(52);
    l->SetTextFont(42);
    l->DrawLatex(0.690,0.953,"138 fb^{-1} (13 TeV)"); //0.68,0.953
	//paveCMS2->Draw("same");
	shape_gg_binned->Draw("same hist ][");
        shape_qq_binned->Draw("same hist ][");
       
        shape_qg_binned->Draw("same hist ][");
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

	pull_SF_atlas->GetXaxis()->SetTitle("Four-jet mass [TeV]");
	pull_SF_atlas->GetXaxis()->SetNoExponent();
	pull_SF_atlas->GetXaxis()->SetMoreLogLabels();
	pull_SF_atlas->GetXaxis()->SetTitleSize(2*0.06);
	pull_SF_atlas->GetYaxis()->SetTitleSize(2*0.06);
	pull_SF_atlas->GetXaxis()->SetLabelSize(2*0.07);
	pull_SF_atlas->GetYaxis()->SetLabelSize(0.09);
	pull_SF_atlas->GetXaxis()->SetLabelOffset(1000);
	pull_SF_atlas->GetXaxis()->SetTitleOffset(1.2);
	pull_SF_atlas->GetYaxis()->SetTitleOffset(0.6);
	pull_SF_atlas->GetYaxis()->SetNdivisions(210);
	pull_SF_atlas->GetYaxis()->CenterTitle(1);
	pull_SF_atlas->SetLineWidth(1);
//
        pull_SF_dijet->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_SF_dijet->GetXaxis()->SetNoExponent();
        pull_SF_dijet->GetXaxis()->SetMoreLogLabels();
        pull_SF_dijet->GetXaxis()->SetTitleSize(2*0.06);
        pull_SF_dijet->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_dijet->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_dijet->GetYaxis()->SetLabelSize(0.09);
        pull_SF_dijet->GetXaxis()->SetLabelOffset(1000);
        pull_SF_dijet->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_dijet->GetYaxis()->SetTitleOffset(0.6);
        pull_SF_dijet->GetYaxis()->SetNdivisions(210);
	pull_SF_dijet->GetYaxis()->CenterTitle(1); 
        pull_SF_dijet->SetLineWidth(1);


        //
        pull_SF_moddijet->GetXaxis()->SetTitle("Four-jet mass [TeV]");
        pull_SF_moddijet->GetXaxis()->SetNoExponent();
        pull_SF_moddijet->GetXaxis()->SetMoreLogLabels();
        pull_SF_moddijet->GetXaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet->GetYaxis()->SetTitleSize(2*0.06);
        pull_SF_moddijet->GetXaxis()->SetLabelSize(2*0.07);
        pull_SF_moddijet->GetYaxis()->SetLabelSize(0.09);
        pull_SF_moddijet->GetXaxis()->SetLabelOffset(1000);
        pull_SF_moddijet->GetXaxis()->SetTitleOffset(1.2);
        pull_SF_moddijet->GetYaxis()->SetTitleOffset(0.6);
        pull_SF_moddijet->GetYaxis()->SetNdivisions(210); 
	pull_SF_moddijet->GetYaxis()->CenterTitle(1);
        pull_SF_moddijet->SetLineWidth(1);


         pull_MC->GetXaxis()->SetTitle("Fourjet mass [TeV]");
        pull_MC->GetXaxis()->SetNoExponent();
        pull_MC->GetXaxis()->SetMoreLogLabels();
        pull_MC->GetXaxis()->SetTitleSize(2*0.06);
        pull_MC->GetYaxis()->SetTitleSize(2*0.06);
        pull_MC->GetXaxis()->SetLabelSize(2*0.07);
        pull_MC->GetYaxis()->SetLabelSize(0.09);
        pull_MC->GetXaxis()->SetLabelOffset(1000);
        pull_MC->GetXaxis()->SetTitleOffset(1.2);
        pull_MC->GetYaxis()->SetTitleOffset(0.6);
        pull_MC->GetYaxis()->SetNdivisions(210); 
	pull_MC->GetYaxis()->CenterTitle(1);
        pull_MC->SetLineWidth(1);

	TLine *sk = new TLine(startit,0.,endit,0.);

	pull_SF_atlas->SetYTitle("#frac{(Data-Fit)}{Uncertainty}"); 
	pull_SF_atlas->SetFillColor(2);
        //pull_SF_atlas->SetFillStyle(1);
	//pull_SF_atlas->Draw("HIST");
//
        pull_SF_dijet->SetYTitle("#frac{(Data-Fit)}{Uncertainty}");
        pull_SF_dijet->SetFillColor(4);
        //->Draw("l same");


        pull_SF_moddijet->SetYTitle("#frac{(Data-Fit)}{Uncertainty}");
         pull_SF_moddijet->SetFillColor(2);
        pull_SF_moddijet->Draw(" HIST");

      
	pull_gg->Draw("l same");

	pull_qq->Draw("l same");



	pull_qg->Draw("l same");

	sk->Draw("same"); 

	TLatex *xLab = new TLatex();
	xLab->SetTextAlign(22);
	xLab->SetTextFont(42);
	xLab->SetTextSize(2*0.05);         
	xLab->DrawLatex(2000, -3.65, "2");
	xLab->DrawLatex(3000, -3.65, "3");
	xLab->DrawLatex(4000, -3.65, "4");
	xLab->DrawLatex(5000, -3.65, "5");
	xLab->DrawLatex(6000, -3.65, "6");
	xLab->DrawLatex(7000, -3.65, "7");
	xLab->DrawLatex(8000, -3.65, "8");

	char Pred_pdf[300];
	strcpy(Pred_pdf,"Combined_Background");
	strcat(Pred_pdf,image_name);
	strcat(Pred_pdf,"_dijet.pdf");

	char Pred_png[300];
	strcpy(Pred_png,"Combined_Background");
	strcat(Pred_png,image_name);
	strcat(Pred_png,"_dijet.png");
  
	//c1->SaveAs(Pred_pdf);
	//c1->SaveAs(Pred_png);
/*TFile *fout;

 fout = new TFile("test_pulls_legend.root","RECREATE");


fout->cd();
pull_SF_moddijet->Write();
fout->Close();
*/

TFile *fout;

 fout = new TFile("/eos/user/i/izisopou/4jets/CMSSW_10_2_13/src/CMSDIJET/DijetRootTreeAnalyzer/Fig6_forHEPData_alpha8.root","RECREATE");


fout->cd();
signal_datag->Write();
fout->Close();
}
