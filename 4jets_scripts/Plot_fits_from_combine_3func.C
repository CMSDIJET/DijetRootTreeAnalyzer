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

void Plot_fits_from_combine_3func(int alphabin){

double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

double lumi 	     = 275200;
double lumi2	     = 137600;    
double startit	     = 1607;
double endit	     = 10072;
gROOT->LoadMacro("setTDRStyle.C");
setTDRStyle();

char fname_data[1024], fname_dijet[1024], fname_atlas[1024], fname_moddijet[1024], fname_MC[1024];
sprintf(fname_data,"inputs/run2/pseudodata_CMSRunIIPlusBkgToyPlusATLASEvent/HISTOS_4J_CMSRunIIPlusBkgToyPlusATLASEvent_SR_alphabin%d.root",alphabin);
sprintf(fname_dijet,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/BkgOnlyFits/Dijet-3p/FitResults_dijet_PFDijetRun2_4J_alphabin%d.root",alphabin);
sprintf(fname_atlas,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/BkgOnlyFits/Atlas-3p/FitResults_atlas_PFDijetRun2_4J_alphabin%d.root",alphabin);
sprintf(fname_moddijet,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/BkgOnlyFits/Moddijet-3p/FitResults_moddijet_PFDijetRun2_4J_alphabin%d.root",alphabin);
sprintf(fname_MC,"inputs/run2/data/HISTOS_4J_Alldata_SR_alphabin%d.root",alphabin);

TFile *f_data     = new TFile(fname_data,"READ");
TFile *f_dijet    = new TFile(fname_dijet,"READ");
TFile *f_atlas    = new TFile(fname_atlas,"READ");
TFile *f_moddijet = new TFile(fname_moddijet,"READ");
TFile *f_MC       = new TFile(fname_MC,"READ");

TH1D *Standard_Fit_dijet     = new TH1D("Standard_Fit_dijet","Standard_Fit_dijet",103,massBoundaries);  
TH1D *Standard_Fit_atlas     = new TH1D("Standard_Fit_atlas","Standard_Fit_atlas",103,massBoundaries);  
TH1D *Standard_Fit_moddijet  = new TH1D("Standard_Fit_moddijet","Standard_Fit_moddijet",103,massBoundaries);

TH1D *Standard_fit_pull_1D_dijet         = new TH1D("Standard_fit_pull_1D_dijet","Standard Fit Pulls",12,-4,4); 
TH1D *Standard_fit_pull_1D_atlas 	 = new TH1D("Standard_fit_pull_1D_atlas","Standard Fit Pulls",12,-4,4);
TH1D *Standard_fit_pull_1D_moddijet      = new TH1D("Standard_fit_pull_1D_moddijet","Standard Fit Pulls",12,-4,4);
        
TH1D *h_MC = (TH1D*)(f_MC->Get("h_FourjetMass"));
TH1D *h_pull_MC = new TH1D("h_pull_MC","MC Pulls",12,-4,4);

TH1D *signal_data  	      = (TH1D*)(f_data->Get("h_FourjetMass"));
TH1D *Standard_Fit_unbinned_dijet     = (TH1D*)(f_dijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *Standard_Fit_unbinned_atlas     = (TH1D*)(f_atlas->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *Standard_Fit_unbinned_moddijet  = (TH1D*)(f_moddijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
       
TH1D *pull_SF_atlas       = (TH1D*)(signal_data->Clone());
TH1D *pull_SF_dijet       = (TH1D*)(signal_data->Clone()); 
TH1D *pull_SF_moddijet    = (TH1D*)(signal_data->Clone()); 
TH1D *pull_MC             = (TH1D*)(signal_data->Clone());

signal_data->SetMarkerStyle(8);
signal_data->SetLineColor(1);
signal_data->SetMarkerColor(1);
signal_data->GetXaxis()->SetRangeUser(startit,endit);
	

//rebinning 1GeV Standard Fit to standard binning
for(int i=0; i<Standard_Fit_unbinned_atlas->GetNbinsX(); i++)
{
        double val   = Standard_Fit_unbinned_dijet->GetBinContent(i);
        double xval  = Standard_Fit_unbinned_dijet->GetBinCenter(i);
        Standard_Fit_dijet->Fill(xval,val);

	val   = Standard_Fit_unbinned_atlas->GetBinContent(i);
	xval  = Standard_Fit_unbinned_atlas->GetBinCenter(i);
	Standard_Fit_atlas->Fill(xval,val);

        val   = Standard_Fit_unbinned_moddijet->GetBinContent(i);
        xval  = Standard_Fit_unbinned_moddijet->GetBinCenter(i);
        Standard_Fit_moddijet->Fill(xval,val);
}


//rescaling prediction, standard fit and data to the differential cross section
for(int i=0; i<Standard_Fit_atlas->GetNbinsX(); i++)
{
	if (signal_data->GetBinContent(i) < 30) signal_data->SetBinError(i, 0.5 + sqrt( signal_data->GetBinContent(i) + 0.25 ) ); 
	if (signal_data->GetBinContent(i)==0) signal_data->SetBinError(i,1.);
	signal_data->SetBinContent(i,1000*signal_data->GetBinContent(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));
	signal_data->SetBinError(i,1000*signal_data->GetBinError(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));

	if (Standard_Fit_dijet->GetBinContent(i) < 30) Standard_Fit_dijet->SetBinError(i, 0.5 + sqrt( Standard_Fit_dijet->GetBinContent(i) + 0.25 ) ); 
	Standard_Fit_dijet->SetBinContent(i,1000*Standard_Fit_dijet->GetBinContent(i)/((Standard_Fit_dijet->GetBinLowEdge(i+1)-Standard_Fit_dijet->GetBinLowEdge(i))*lumi));
	Standard_Fit_dijet->SetBinError(i,1000*Standard_Fit_dijet->GetBinError(i)/((Standard_Fit_dijet->GetBinLowEdge(i+1)-Standard_Fit_dijet->GetBinLowEdge(i))*lumi));

	if (Standard_Fit_atlas->GetBinContent(i) < 30) Standard_Fit_atlas->SetBinError(i, 0.5 + sqrt( Standard_Fit_atlas->GetBinContent(i) + 0.25 ) ); 
	Standard_Fit_atlas->SetBinContent(i,1000*Standard_Fit_atlas->GetBinContent(i)/((Standard_Fit_atlas->GetBinLowEdge(i+1)-Standard_Fit_atlas->GetBinLowEdge(i))*lumi));
	Standard_Fit_atlas->SetBinError(i,1000*Standard_Fit_atlas->GetBinError(i)/((Standard_Fit_atlas->GetBinLowEdge(i+1)-Standard_Fit_atlas->GetBinLowEdge(i))*lumi));
 
	if (Standard_Fit_moddijet->GetBinContent(i) < 30) Standard_Fit_moddijet->SetBinError(i, 0.5 + sqrt( Standard_Fit_moddijet->GetBinContent(i) + 0.25 ) ); 
	Standard_Fit_moddijet->SetBinContent(i,1000*Standard_Fit_moddijet->GetBinContent(i)/((Standard_Fit_moddijet->GetBinLowEdge(i+1)-Standard_Fit_moddijet->GetBinLowEdge(i))*lumi));
	Standard_Fit_moddijet->SetBinError(i,1000*Standard_Fit_moddijet->GetBinError(i)/((Standard_Fit_moddijet->GetBinLowEdge(i+1)-Standard_Fit_moddijet->GetBinLowEdge(i))*lumi)); 

	h_MC->SetBinContent(i,1000*h_MC->GetBinContent(i)/((h_MC->GetBinLowEdge(i+1)-h_MC->GetBinLowEdge(i))*lumi2)); //lumi
	h_MC->SetBinError(i,1000*h_MC->GetBinError(i)/((h_MC->GetBinLowEdge(i+1)-h_MC->GetBinLowEdge(i))*lumi2)); //lumi          
}



//creating pulls and calculate chi square for the two methods: 
double chi_square_SF_atlas    =  0;
int    NDF_SF_atlas           = -3;	  
double chi_square_SF_dijet    =  0;
int    NDF_SF_dijet	      = -3;       
double chi_square_SF_moddijet =  0;
int    NDF_SF_moddijet	      = -3;  

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

        if(cont>0)
	{
		errl = cont - ROOT::Math::gamma_quantile(alpha/2,cont,1.);
		errh = ROOT::Math::gamma_quantile_c(alpha/2,cont+1,1.)-cont;
        }

        errl = errl*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
        errh = errh*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
                

	signal_datag->SetPointEYlow(i-1, errl); 
        signal_datag->SetPointEYhigh(i-1, errh);

	double data_signal    = signal_data->GetBinContent(i);
	double mjj   	      = signal_data->GetBinCenter(i);
        double SF_dijet       = Standard_Fit_dijet->GetBinContent(i);
	double SF_atlas       = Standard_Fit_atlas->GetBinContent(i);
        double SF_moddijet    = Standard_Fit_moddijet->GetBinContent(i);
        double MC    	      = h_MC->GetBinContent(i);

	if(edata_signal>0)
	{ 
                if(data_signal>SF_dijet) pull_SF_dijet->SetBinContent(i,(-SF_dijet+data_signal)/errl);
                if(data_signal<SF_dijet) pull_SF_dijet->SetBinContent(i,(-SF_dijet+data_signal)/errh);

 		if(data_signal>SF_atlas) pull_SF_atlas->SetBinContent(i,(-SF_atlas+data_signal)/errl);
                if(data_signal<SF_atlas) pull_SF_atlas->SetBinContent(i,(-SF_atlas+data_signal)/errh); 

                if(data_signal>SF_moddijet) pull_SF_moddijet->SetBinContent(i,(-SF_moddijet+data_signal)/errl);
                if(data_signal<SF_moddijet) pull_SF_moddijet->SetBinContent(i,(-SF_moddijet+data_signal)/errh); 

                if(data_signal>MC) pull_MC->SetBinContent(i,(-MC+data_signal)/errl);
                if(data_signal<MC) pull_MC->SetBinContent(i,(-MC+data_signal)/errh);

			
		if(mjj>=startit && mjj<= endit )
		{	
                	Standard_fit_pull_1D_dijet->Fill(pull_SF_dijet->GetBinContent(i));
			Standard_fit_pull_1D_atlas->Fill(pull_SF_atlas->GetBinContent(i));
                	Standard_fit_pull_1D_moddijet->Fill(pull_SF_dijet->GetBinContent(i));
                	pull_MC->Fill(pull_MC->GetBinContent(i));

			if(cont!=0)
			{
				chi_square_SF_dijet = chi_square_SF_dijet + pull_SF_dijet->GetBinContent(i)*pull_SF_dijet->GetBinContent(i);
                        	NDF_SF_dijet        = NDF_SF_dijet + 1 ;

				chi_square_SF_atlas = chi_square_SF_atlas + pull_SF_atlas->GetBinContent(i)*pull_SF_atlas->GetBinContent(i);
				NDF_SF_atlas        = NDF_SF_atlas + 1 ;

                        	chi_square_SF_moddijet = chi_square_SF_moddijet + pull_SF_moddijet->GetBinContent(i)*pull_SF_moddijet->GetBinContent(i);
                        	NDF_SF_moddijet        = NDF_SF_moddijet + 1 ;
                        } 
		}
	}

	if(cont==0)
	{
		signal_datag->SetPointY(i-1,0.0000000000001);
		signal_datag->SetPointEYlow(i-1, 0); 
		signal_datag->SetPointEYhigh(i-1, 0);
	}

	signal_datag->SetPointEXlow(i-1,0);
	signal_datag->SetPointEXhigh(i-1,0);

} 

     
// DRAW

  
TLegend *leg = new TLegend(0.6,0.52,0.8,0.88); 
leg->AddEntry(signal_datag, "#splitline{CMS+ATLAS}{pseudo-dataset}","pe");
leg->AddEntry((TObject*)0,"","");
leg->AddEntry(Standard_Fit_dijet, "Dijet-3p fit","l");
leg->AddEntry(Standard_Fit_atlas, "PowExp-3p fit","l");
leg->AddEntry(Standard_Fit_moddijet, "ModDijet-3p fit","l");
//leg->AddEntry(h_MC, "CMS data","l");
leg->SetTextSize(0.05);
leg->SetTextFont(42);

char chi2leg_dijet[1024], chi2leg_atlas[1024], chi2leg_moddijet[1024];
sprintf(chi2leg_dijet,   "#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", chi_square_SF_dijet,    NDF_SF_dijet,    TMath::Prob(chi_square_SF_dijet,NDF_SF_dijet));
sprintf(chi2leg_atlas,   "#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", chi_square_SF_atlas,    NDF_SF_atlas,    TMath::Prob(chi_square_SF_atlas,NDF_SF_atlas));
sprintf(chi2leg_moddijet,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", chi_square_SF_moddijet, NDF_SF_moddijet, TMath::Prob(chi_square_SF_moddijet,NDF_SF_moddijet));

TLegend *leg2 = new TLegend(0.22,0.03,0.42,0.23);
leg2->AddEntry(Standard_Fit_dijet, chi2leg_dijet,"l");
leg2->AddEntry(Standard_Fit_atlas, chi2leg_atlas,"l");
leg2->AddEntry(Standard_Fit_moddijet, chi2leg_moddijet,"l");
leg2->SetTextSize(0.05);
leg2->SetTextFont(42);


TLegend *leg3 = new TLegend(0.5,0.4,0.9,0.45);
leg3->AddEntry((TObject*)0,  "Pulls of ModDijet-3p fit","");
leg3->SetTextSize(0.08);
leg3->SetTextFont(42);
	


char alpha_name[1024];
if(alphabin==1) sprintf(alpha_name,"0.10 < #alpha < 0.12");
if(alphabin==2) sprintf(alpha_name,"0.12 < #alpha < 0.14");
if(alphabin==3) sprintf(alpha_name,"0.14 < #alpha < 0.16");
if(alphabin==4) sprintf(alpha_name,"0.16 < #alpha < 0.18");
if(alphabin==5) sprintf(alpha_name,"0.18 < #alpha < 0.20");
if(alphabin==6) sprintf(alpha_name,"0.20 < #alpha < 0.22");
if(alphabin==7) sprintf(alpha_name,"0.22 < #alpha < 0.24");
if(alphabin==8) sprintf(alpha_name,"0.24 < #alpha < 0.26");
if(alphabin==9) sprintf(alpha_name,"0.26 < #alpha < 0.28");
if(alphabin==10) sprintf(alpha_name,"0.28 < #alpha < 0.30");
if(alphabin==11) sprintf(alpha_name,"0.30 < #alpha < 0.32");
if(alphabin==12) sprintf(alpha_name,"0.32 < #alpha < 0.34");
if(alphabin==13) sprintf(alpha_name,"#alpha > 0.34");

TPaveText *pave = new TPaveText(0.2,0.65,0.5,0.75,"NDC");
pave->AddText(alpha_name);
pave->SetFillColor(0);
pave->SetBorderSize(0);
pave->SetTextFont(42);
pave->SetTextSize(0.06);




       
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


Standard_Fit_dijet->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_dijet->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_dijet->GetYaxis()->SetRangeUser(0.0000000015,10000.);
Standard_Fit_dijet->GetYaxis()->SetTitleSize(0.07);
Standard_Fit_dijet->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_dijet->GetYaxis()->SetTitleOffset(1.1);
Standard_Fit_dijet->SetFillColor(0);
Standard_Fit_dijet->SetLineWidth(2);
Standard_Fit_dijet->SetLineColor(kBlue-4); 
//Standard_Fit_dijet->SetLineStyle(2);
Standard_Fit_dijet->Draw("l hist same");

Standard_Fit_atlas->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_atlas->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_atlas->GetYaxis()->SetRangeUser(0.0000000015,10000.);
Standard_Fit_atlas->GetYaxis()->SetTitleSize(0.07);
Standard_Fit_atlas->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_atlas->GetYaxis()->SetTitleOffset(1.1);
Standard_Fit_atlas->SetFillColor(0); 
Standard_Fit_atlas->SetLineWidth(2);
Standard_Fit_atlas->SetLineColor(kRed-4);
//Standard_Fit_atlas->SetLineStyle(3);
Standard_Fit_atlas->Draw("l hist same");

Standard_Fit_moddijet->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_moddijet->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_moddijet->GetYaxis()->SetRangeUser(0.00000000015,10000.);
Standard_Fit_moddijet->GetYaxis()->SetTitleSize(0.07);
Standard_Fit_moddijet->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_moddijet->GetYaxis()->SetTitleOffset(1.1);
Standard_Fit_moddijet->SetFillColor(0);
Standard_Fit_moddijet->SetLineWidth(2);
Standard_Fit_moddijet->SetLineColor(kGreen+1); 
//Standard_Fit_moddijet->SetLineStyle(1);
Standard_Fit_moddijet->Draw("l hist same");

h_MC->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
h_MC->GetXaxis()->SetRangeUser(startit,endit);
h_MC->GetYaxis()->SetRangeUser(0.000000000015,10000.);
h_MC->GetYaxis()->SetTitleSize(0.07);
h_MC->GetYaxis()->SetLabelSize(0.06);
h_MC->GetYaxis()->SetTitleOffset(0.9);
h_MC->SetFillColor(0);
h_MC->SetLineWidth(2);
h_MC->SetLineColor(3);
//h_MC->Scale(signal_data->Integral()/h_MC->Integral());
//h_MC->Draw("hist same ][");

signal_datag->SetMarkerSize(1.);
signal_datag->Draw("same ep");
leg->Draw("same");
leg2->Draw("same");

TLatex *l = new TLatex();     
l->SetTextAlign(11);
l->SetTextSize(0.085);
l->SetNDC();
l->SetTextFont(62);
l->SetTextFont(42);
l->DrawLatex(0.23,0.8,"#splitline{#bf{CMS}}{#scale[0.7]{#it{Preliminary}}}");
l->SetTextSize(0.055);
l->DrawLatex(0.69,0.953,"275 fb^{-1} (13 TeV)");
	
pave->Draw("same");



c1->cd();

TVirtualPad *pad2r ;
pad2r = c1->GetPad(2);
pad2r->SetLeftMargin(0.175);
pad2r->SetPad(0.01,0.02,0.99,0.37);
pad2r->SetBottomMargin(0.35); //0.35
pad2r->SetRightMargin(0.05);
pad2r->Draw();
pad2r->cd(); 
pad2r->cd()->SetLogx(1);
//pad2r->SetGridx();
//pad2r->SetGridy();

pull_SF_dijet->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_SF_dijet->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_SF_dijet->GetXaxis()->SetRangeUser(startit,endit);
pull_SF_dijet->GetYaxis()->SetRangeUser(-3.49,3.49);
pull_SF_dijet->GetXaxis()->SetNoExponent();
pull_SF_dijet->GetXaxis()->SetMoreLogLabels();
pull_SF_dijet->GetXaxis()->SetTitleSize(2*0.06);
pull_SF_dijet->GetYaxis()->SetTitleSize(2*0.06); //2*0.06
pull_SF_dijet->GetXaxis()->SetLabelSize(2*0.07);
pull_SF_dijet->GetYaxis()->SetLabelSize(0.09);
pull_SF_dijet->GetXaxis()->SetLabelOffset(1000);
pull_SF_dijet->GetXaxis()->SetTitleOffset(1.2);
pull_SF_dijet->GetYaxis()->SetTitleOffset(0.6);
pull_SF_dijet->GetYaxis()->SetNdivisions(210);
pull_SF_dijet->GetYaxis()->CenterTitle(1); 
pull_SF_dijet->SetLineWidth(2);
pull_SF_dijet->SetFillColor(kBlue-4);
//pull_SF_dijet->SetFillStyle(3305);
pull_SF_dijet->Draw("hist same");

pull_SF_atlas->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_SF_atlas->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_SF_atlas->GetXaxis()->SetRangeUser(startit,endit);
pull_SF_atlas->GetYaxis()->SetRangeUser(-3.49,3.49);
pull_SF_atlas->GetXaxis()->SetNoExponent();
pull_SF_atlas->GetXaxis()->SetMoreLogLabels();
pull_SF_atlas->GetXaxis()->SetTitleSize(2*0.06);
pull_SF_atlas->GetYaxis()->SetTitleSize(2*0.06); //2*0.06
pull_SF_atlas->GetXaxis()->SetLabelSize(2*0.07);
pull_SF_atlas->GetYaxis()->SetLabelSize(0.09);
pull_SF_atlas->GetXaxis()->SetLabelOffset(1000);
pull_SF_atlas->GetXaxis()->SetTitleOffset(1.2);
pull_SF_atlas->GetYaxis()->SetTitleOffset(0.6);
pull_SF_atlas->GetYaxis()->SetNdivisions(210);
pull_SF_atlas->GetYaxis()->CenterTitle(1);
pull_SF_atlas->SetLineWidth(2);
pull_SF_atlas->SetFillColor(kRed-4);
//pull_SF_dijet->SetFillStyle(3395);
pull_SF_atlas->Draw("hist same");

pull_SF_moddijet->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_SF_moddijet->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_SF_moddijet->GetXaxis()->SetRangeUser(startit,endit);
pull_SF_moddijet->GetYaxis()->SetRangeUser(-3.49,3.49);
pull_SF_moddijet->GetXaxis()->SetNoExponent();
pull_SF_moddijet->GetXaxis()->SetMoreLogLabels();
pull_SF_moddijet->GetXaxis()->SetTitleSize(2*0.06);
pull_SF_moddijet->GetYaxis()->SetTitleSize(2*0.06); //2*0.06
pull_SF_moddijet->GetXaxis()->SetLabelSize(2*0.07);
pull_SF_moddijet->GetYaxis()->SetLabelSize(0.09);
pull_SF_moddijet->GetXaxis()->SetLabelOffset(1000);
pull_SF_moddijet->GetXaxis()->SetTitleOffset(1.2);
pull_SF_moddijet->GetYaxis()->SetTitleOffset(0.6);
pull_SF_moddijet->GetYaxis()->SetNdivisions(210); 
pull_SF_moddijet->GetYaxis()->CenterTitle(1);
pull_SF_moddijet->SetLineWidth(2);
pull_SF_moddijet->SetFillColor(kGreen+1);
//pull_SF_moddijet->SetFillStyle(3409);
pull_SF_moddijet->Draw("hist same");

pull_MC->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_MC->GetXaxis()->SetNoExponent();
pull_MC->GetXaxis()->SetMoreLogLabels();
pull_MC->GetXaxis()->SetTitleSize(2*0.06);
pull_MC->GetYaxis()->SetTitleSize(2*0.06); //2*0.06
pull_MC->GetXaxis()->SetLabelSize(2*0.07);
pull_MC->GetYaxis()->SetLabelSize(0.09);
pull_MC->GetXaxis()->SetLabelOffset(1000);
pull_MC->GetXaxis()->SetTitleOffset(1.2);
pull_MC->GetYaxis()->SetTitleOffset(0.6);
pull_MC->GetYaxis()->SetNdivisions(210); 
pull_MC->GetYaxis()->CenterTitle(1);
pull_MC->SetLineWidth(1);

	
TLine *sk = new TLine(startit,0.,endit,0.);
sk->Draw("same"); 

TLatex *xLab = new TLatex();
xLab->SetTextAlign(22);
xLab->SetTextFont(42);
xLab->SetTextSize(2*0.05);         
xLab->DrawLatex(2000, -4.15, "2");
xLab->DrawLatex(3000, -4.15, "3");
xLab->DrawLatex(4000, -4.15, "4");
xLab->DrawLatex(5000, -4.15, "5");
xLab->DrawLatex(6000, -4.15, "6");
xLab->DrawLatex(7000, -4.15, "7");
xLab->DrawLatex(8000, -4.15, "8");
xLab->DrawLatex(9000, -4.15, "9");

//leg3->Draw("same");

char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/plots/Bkg_fits_3p_CMSRunIIPlusBkgToyPlusATLASEvent_alphabin%d.png",alphabin);
sprintf(cname2,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/plots/Bkg_fits_3p_CMSRunIIPlusBkgToyPlusATLASEvent_alphabin%d.pdf",alphabin);

c1->SaveAs(cname1);
c1->SaveAs(cname2);

}
