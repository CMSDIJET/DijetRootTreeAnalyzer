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

void Plot_Bkg_Fits(int nPars, int alphabin){

double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

double lumi 	     = 137600;    
double startit	     = 1607;
double endit	     = 9067;
	  

char fname_data[1024], fname_FitDijet[1024], fname_FitAtlas[1024], fname_FitModDijet[1024], fname_QCD[1024];

if(alphabin!=0)
{
    sprintf(fname_data, "Fitting/%dParFits/HISTOS_4J_AlldataRun2_SR_alphabin%d.root", nPars, alphabin);
    sprintf(fname_FitDijet, "Fitting/%dParFits/DijetFitResult_PFDijetRun2_4J_alphabin%d_Dijet.root", nPars, alphabin);
    sprintf(fname_FitAtlas, "Fitting/%dParFits/DijetFitResult_PFDijetRun2_4J_alphabin%d_PowExp.root", nPars, alphabin);
    sprintf(fname_FitModDijet, "Fitting/%dParFits/DijetFitResult_PFDijetRun2_4J_alphabin%d_ModDijet.root", nPars, alphabin);
    sprintf(fname_QCD, "Fitting/%dParFits/QCD2017_Standardcuts_M4Jgt1p6_nobreak_alpha%d.root", nPars, alphabin);
}
else
{
    sprintf(fname_data, "Fitting/%dParFits/HISTOS_4J_AlldataRun2_SR_alphagt0p1.root", nPars);
    sprintf(fname_FitDijet, "Fitting/%dParFits/DijetFitResult_PFDijet2017_4J_alphagt0p1_Dijet.root", nPars);
    sprintf(fname_FitAtlas, "Fitting/%dParFits/DijetFitResult_PFDijetRun2_4J_alphagt0p1_PowExp.root", nPars);
    sprintf(fname_FitModDijet, "Fitting/%dParFits/DijetFitResult_PFDijet2017_4J_alphagt0p1_ModDijet.root", nPars);
    sprintf(fname_QCD, "Fitting/%dParFits/QCD2017_Standardcuts_M4Jgt1p5_nobreak_alphagt0p1.root", nPars);    
}


//Fetch data, MC and fits		
TFile *f_data = new TFile(fname_data, "read");
TFile *f_Fit_dijet = new TFile(fname_FitDijet, "read");
TFile *f_Fit_atlas = new TFile(fname_FitAtlas, "read");
TFile *f_Fit_moddijet = new TFile(fname_FitModDijet, "read");
TFile *f_MC = new TFile(fname_QCD, "read");

TH1D *Standard_Fit_unbinned_dijet = (TH1D*)(f_Fit_dijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *Standard_Fit_unbinned_atlas = (TH1D*)(f_Fit_atlas->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *Standard_Fit_unbinned_moddijet = (TH1D*)(f_Fit_moddijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *h_data = (TH1D*)(f_data->Get("h_FourjetMass"));
TH1D *h_MC = (TH1D*)(f_MC->Get("h_FourjetMass"));

   
TH1D *Standard_Fit_dijet = new TH1D("Standard_Fit_dijet","",103,massBoundaries);
TH1D *Standard_Fit_atlas = new TH1D("Standard_Fit_atlas","",103,massBoundaries);  
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
TH1D *pull_Fit_dijet = (TH1D*)(h_data->Clone());
TH1D *pull_Fit_atlas = (TH1D*)(h_data->Clone()); 
TH1D *pull_Fit_moddijet = (TH1D*)(h_data->Clone()); 
TH1D *pull_MC = (TH1D*)(h_data->Clone());

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

}

//creating pulls and calculate chi square for the two methods: 
double  chi_square_Fit_atlas = 0;
int     NDF_Fit_atlas = -nPars;    
double  chi_square_Fit_dijet = 0;
int	NDF_Fit_dijet = -nPars;       
double  chi_square_Fit_moddijet = 0;
int	NDF_Fit_moddijet = -nPars;   

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

        /*if(cont >= 20)
        {
                errl = sqrt(cont); 
        	errh = sqrt(cont);
        }*/

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
	
	if(edata>0)
	{ 
 		if(data_cont>Fit_atlas_cont) pull_Fit_atlas->SetBinContent(i,(-Fit_atlas_cont+data_cont)/errl);
                if(data_cont<Fit_atlas_cont) pull_Fit_atlas->SetBinContent(i,(-Fit_atlas_cont+data_cont)/errh); 
		
		if(data_cont>Fit_dijet_cont) pull_Fit_dijet->SetBinContent(i,(-Fit_dijet_cont+data_cont)/errl);
                if(data_cont<Fit_dijet_cont) pull_Fit_dijet->SetBinContent(i,(-Fit_dijet_cont+data_cont)/errh); 	
			
                if(data_cont>Fit_moddijet_cont) pull_Fit_moddijet->SetBinContent(i,(-Fit_moddijet_cont+data_cont)/errl);
                if(data_cont<Fit_moddijet_cont) pull_Fit_moddijet->SetBinContent(i,(-Fit_moddijet_cont+data_cont)/errh); 
                
                pull_MC->SetBinContent(i,(-MC_cont+data_cont)/edata);
                
		
		
		if(m4j>=startit && m4j<= endit)
		{	
			
			if(data_cont!=0) chi_square_Fit_atlas = chi_square_Fit_atlas + pull_Fit_atlas->GetBinContent(i)*pull_Fit_atlas->GetBinContent(i);
			if(data_cont!=0) NDF_Fit_atlas        = NDF_Fit_atlas + 1 ;

                        if(data_cont!=0) chi_square_Fit_dijet = chi_square_Fit_dijet + pull_Fit_dijet->GetBinContent(i)*pull_Fit_dijet->GetBinContent(i);
                        if(data_cont!=0) NDF_Fit_dijet        = NDF_Fit_dijet + 1 ;

                        if(data_cont!=0) chi_square_Fit_moddijet = chi_square_Fit_moddijet + pull_Fit_moddijet->GetBinContent(i)*pull_Fit_moddijet->GetBinContent(i);
                        if(data_cont!=0) NDF_Fit_moddijet        = NDF_Fit_moddijet + 1 ;                          
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


Standard_Fit_atlas->SetLineColor(kRed+1);
Standard_Fit_atlas->SetMarkerColor(kRed+1);
Standard_Fit_atlas->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_atlas->GetYaxis()->SetRangeUser(0.00000000015,10000.);

Standard_Fit_dijet->SetLineColor(kBlue-3);
Standard_Fit_dijet->SetMarkerColor(kBlue-3);
Standard_Fit_dijet->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_dijet->GetYaxis()->SetRangeUser(0.00000000015,10000.);
        
Standard_Fit_moddijet->SetLineColor(kGreen+2);
Standard_Fit_moddijet->SetMarkerColor(kGreen+2);
Standard_Fit_moddijet->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_moddijet->GetYaxis()->SetRangeUser(0.00000000015,10000.);

h_MC->SetLineColor(kViolet);
h_MC->SetMarkerColor(kViolet);
h_MC->GetXaxis()->SetRangeUser(startit,endit);
h_MC->GetYaxis()->SetRangeUser(0.00000000015,10000.);

pull_Fit_atlas->SetLineColor(kRed+1);
pull_Fit_atlas->SetMarkerColor(kRed+1);
pull_Fit_atlas->GetXaxis()->SetRangeUser(startit,endit);
pull_Fit_atlas->GetYaxis()->SetRangeUser(-3.3,3.3);

pull_Fit_dijet->SetLineColor(kBlue-3);  
pull_Fit_dijet->SetMarkerColor(kBlue-3);
pull_Fit_dijet->GetXaxis()->SetRangeUser(startit,endit);
pull_Fit_dijet->GetYaxis()->SetRangeUser(-3.3,3.3);

pull_Fit_moddijet->SetLineColor(kGreen+2);  
pull_Fit_moddijet->SetMarkerColor(kGreen+2);
pull_Fit_moddijet->GetXaxis()->SetRangeUser(startit,endit);
pull_Fit_moddijet->GetYaxis()->SetRangeUser(-3.3,3.3);
       
Standard_Fit_atlas->SetTitle("");
Standard_Fit_dijet->SetTitle("");
Standard_Fit_moddijet->SetTitle("");


Standard_Fit_atlas->SetStats(0);
Standard_Fit_dijet->SetStats(0);
Standard_Fit_moddijet->SetStats(0);
pull_Fit_atlas->SetStats(0);
pull_Fit_dijet->SetStats(0);
pull_Fit_moddijet->SetStats(0);

			


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
pad1r->cd()->SetTickx(1);
pad1r->cd()->SetTicky(1);

Standard_Fit_atlas->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_atlas->GetYaxis()->SetTitleSize(0.07); //0.07
Standard_Fit_atlas->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_atlas->GetYaxis()->SetTitleOffset(1.1);
Standard_Fit_atlas->SetFillColor(0); 
Standard_Fit_atlas->SetLineWidth(2);
Standard_Fit_atlas->SetLineStyle(1);
Standard_Fit_atlas->Draw("l hist");

Standard_Fit_dijet->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_dijet->GetYaxis()->SetTitleSize(0.07); //0.07
Standard_Fit_dijet->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_dijet->GetYaxis()->SetTitleOffset(0.9);
Standard_Fit_dijet->SetFillColor(0);
Standard_Fit_dijet->SetLineWidth(2); 
Standard_Fit_dijet->SetLineStyle(1);
Standard_Fit_dijet->Draw("l hist same");

Standard_Fit_moddijet->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_moddijet->GetYaxis()->SetTitleSize(0.07); //0.07
Standard_Fit_moddijet->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_moddijet->GetYaxis()->SetTitleOffset(0.9);
Standard_Fit_moddijet->SetFillColor(0);
Standard_Fit_moddijet->SetLineWidth(2);
Standard_Fit_moddijet->SetLineStyle(1);
Standard_Fit_moddijet->Draw("l hist same");

h_MC->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
h_MC->GetYaxis()->SetTitleSize(0.07); //0.07
h_MC->GetYaxis()->SetLabelSize(0.06);
h_MC->GetYaxis()->SetTitleOffset(0.9);
h_MC->SetFillColor(0);
h_MC->SetLineWidth(2);
h_MC->Scale(h_data->Integral()/h_MC->Integral());
h_MC->Draw("hist same ][");

h_datag->Draw("same ep");



char alphaname[1024];
if(alphabin==1) sprintf(alphaname, "0.10 < #alpha < 0.12");
if(alphabin==2) sprintf(alphaname, "0.12 < #alpha < 0.14");
if(alphabin==3) sprintf(alphaname, "0.14 < #alpha < 0.16");
if(alphabin==4) sprintf(alphaname, "0.16 < #alpha < 0.18");
if(alphabin==5) sprintf(alphaname, "0.18 < #alpha < 0.20");
if(alphabin==6) sprintf(alphaname, "0.20 < #alpha < 0.22");
if(alphabin==7) sprintf(alphaname, "0.22 < #alpha < 0.24");
if(alphabin==8) sprintf(alphaname, "0.24 < #alpha < 0.26");
if(alphabin==9) sprintf(alphaname, "0.26 < #alpha < 0.28");
if(alphabin==10) sprintf(alphaname, "0.28 < #alpha < 0.30");
if(alphabin==11) sprintf(alphaname, "0.30 < #alpha < 0.32");
if(alphabin==12) sprintf(alphaname, "0.32 < #alpha < 0.34");
if(alphabin==13) sprintf(alphaname, "#alpha > 0.34");
if(alphabin==0) sprintf(alphaname, "#alpha > 0.10");

TPaveText *pave3 = new TPaveText(0.3,0.68,0.4,0.71,"NDC");
//TPaveText *pave3 = new TPaveText(0.3,0.54,0.4,0.57,"NDC");
pave3->AddText(alphaname);
pave3->SetFillColor(0);
pave3->SetBorderSize(0);
pave3->SetTextFont(42);
pave3->SetTextSize(0.06);
pave3->Draw("same");


char leg_dijet[1024], leg_atlas[1024], leg_moddijet[1024];
sprintf(leg_dijet, "Dijet-%dp fit", nPars);
sprintf(leg_atlas, "PowExp-%dp fit", nPars);
sprintf(leg_moddijet, "ModDijet-%dp fit", nPars);

TLegend *leg = new TLegend(0.59,0.55,0.89,0.9);
leg->AddEntry(h_datag, "Data","pe");
leg->AddEntry(h_MC, "LO QCD MC","l");
leg->AddEntry(Standard_Fit_dijet, leg_dijet,"l");
leg->AddEntry(Standard_Fit_atlas, leg_atlas,"l");
leg->AddEntry(Standard_Fit_moddijet, leg_moddijet,"l");
leg->SetTextSize(0.06);
leg->SetBorderSize(0);
leg->Draw("same");


char chi2name_atlas[1024], chi2name_moddijet[1024], chi2name_dijet[1024];
sprintf(chi2name_dijet, "#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", chi_square_Fit_dijet, NDF_Fit_dijet, TMath::Prob(chi_square_Fit_dijet, NDF_Fit_dijet));
sprintf(chi2name_atlas, "#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", chi_square_Fit_atlas, NDF_Fit_atlas, TMath::Prob(chi_square_Fit_atlas, NDF_Fit_atlas));
sprintf(chi2name_moddijet, "#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", chi_square_Fit_moddijet, NDF_Fit_moddijet, TMath::Prob(chi_square_Fit_moddijet, NDF_Fit_moddijet));

TLegend *leg2 = new TLegend(0.22,0.05,0.42,0.3);
leg2->AddEntry(Standard_Fit_dijet,  chi2name_dijet,"l");
leg2->AddEntry(Standard_Fit_atlas,  chi2name_atlas,"l");
leg2->AddEntry(Standard_Fit_moddijet,  chi2name_moddijet,"l");
leg2->SetTextSize(0.05);
leg2->SetTextFont(42);
leg2->SetBorderSize(0);
leg2->Draw("same");

  
TLatex *l = new TLatex();     
l->SetTextAlign(11);
l->SetTextSize(0.055);
l->SetNDC();
l->SetTextFont(42);
l->DrawLatex(0.685,0.953,"138 fb^{-1} (13 TeV)");
l->SetTextSize(0.08);	
l->DrawLatex(0.23,0.80,"#splitline{#bf{CMS}}{#scale[0.7]{#it{Preliminary}}}");	
		
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
pad2r->cd()->SetTickx(1);
pad2r->cd()->SetTicky(1);

pull_Fit_atlas->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_Fit_atlas->GetXaxis()->SetNoExponent();
pull_Fit_atlas->GetXaxis()->SetMoreLogLabels();
pull_Fit_atlas->GetXaxis()->SetTitleSize(2*0.06); //2*0.06
pull_Fit_atlas->GetYaxis()->SetTitleSize(2*0.06); //2*0.06
pull_Fit_atlas->GetXaxis()->SetLabelSize(2*0.07);
pull_Fit_atlas->GetYaxis()->SetLabelSize(0.09);
pull_Fit_atlas->GetXaxis()->SetLabelOffset(1000);
pull_Fit_atlas->GetYaxis()->SetLabelOffset(0.02);
pull_Fit_atlas->GetXaxis()->SetTitleOffset(1.2);
pull_Fit_atlas->GetYaxis()->SetTitleOffset(0.6);
pull_Fit_atlas->GetYaxis()->SetNdivisions(210);
pull_Fit_atlas->GetXaxis()->SetTickSize(0.06);
pull_Fit_atlas->SetLineWidth(1);

pull_Fit_dijet->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_Fit_dijet->GetXaxis()->SetNoExponent();
pull_Fit_dijet->GetXaxis()->SetMoreLogLabels();
pull_Fit_dijet->GetXaxis()->SetTitleSize(2*0.06); //2*0.06
pull_Fit_dijet->GetYaxis()->SetTitleSize(2*0.06); //2*0.06
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
pull_Fit_moddijet->GetXaxis()->SetTitleSize(2*0.06); //2*0.06
pull_Fit_moddijet->GetYaxis()->SetTitleSize(2*0.06); //2*0.06
pull_Fit_moddijet->GetXaxis()->SetLabelSize(2*0.07);
pull_Fit_moddijet->GetYaxis()->SetLabelSize(0.09);
pull_Fit_moddijet->GetYaxis()->SetLabelOffset(0.02);
pull_Fit_moddijet->GetXaxis()->SetLabelOffset(1000);
pull_Fit_moddijet->GetXaxis()->SetTitleOffset(1.2);
pull_Fit_moddijet->GetYaxis()->SetTitleOffset(0.6);
pull_Fit_moddijet->GetYaxis()->SetNdivisions(210); 
pull_Fit_moddijet->SetLineWidth(1);

pull_MC->GetXaxis()->SetTitle("Fourjet mass [TeV]");
pull_MC->GetXaxis()->SetNoExponent();
pull_MC->GetXaxis()->SetMoreLogLabels();
pull_MC->GetXaxis()->SetTitleSize(2*0.06); //2*0.06
pull_MC->GetYaxis()->SetTitleSize(2*0.06); //2*0.06
pull_MC->GetXaxis()->SetLabelSize(2*0.07);
pull_MC->GetYaxis()->SetLabelSize(0.09);
pull_MC->GetYaxis()->SetLabelOffset(0.02);
pull_MC->GetXaxis()->SetLabelOffset(1000);
pull_MC->GetXaxis()->SetTitleOffset(1.2);
pull_MC->GetYaxis()->SetTitleOffset(0.6);
pull_MC->GetYaxis()->SetNdivisions(210); 
pull_MC->SetLineWidth(1);

	

pull_Fit_atlas->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_Fit_atlas->SetFillColor(kRed+1);
pull_Fit_atlas->GetYaxis()->CenterTitle(1);
pull_Fit_atlas->Draw("HIST");

pull_Fit_moddijet->SetYTitle("#frac{(Data-Fit)}{Uncertainty}");
pull_Fit_moddijet->SetFillColor(kGreen+2);
pull_Fit_moddijet->Draw("HIST same");

pull_Fit_dijet->SetYTitle("#frac{(Data-Fit)}{Uncertainty}");
pull_Fit_dijet->SetFillColor(kBlue-3);
pull_Fit_dijet->Draw("HIST same");
   
/*pull_Fit_atlas->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_Fit_atlas->SetFillColor(kRed+1);
pull_Fit_atlas->GetYaxis()->CenterTitle(1);
pull_Fit_atlas->Draw("HIST same");   
  */ 
TLine *sk = new TLine(startit,0.,endit,0.);
sk->Draw("same"); 

TLatex *xLab = new TLatex();
xLab->SetTextAlign(22);
xLab->SetTextFont(42);
xLab->SetTextSize(2*0.055);         
xLab->DrawLatex(2000, -3.8, "2");
xLab->DrawLatex(3000, -3.8, "3");
xLab->DrawLatex(4000, -3.8, "4");
xLab->DrawLatex(5000, -3.8, "5");
xLab->DrawLatex(6000, -3.8, "6");
xLab->DrawLatex(7000, -3.8, "7");
xLab->DrawLatex(8000, -3.8, "8");
xLab->DrawLatex(9000, -3.8, "9");

char cname1[1024], cname2[1024];
if(alphabin!=0)
{
    sprintf(cname1, "output/Wide_Resonances_Run2_Final/plots/bkg_fits/BkgFits%dPars_alphabin%d.png", nPars, alphabin);
    sprintf(cname2, "output/Wide_Resonances_Run2_Final/plots/bkg_fits/BkgFits%dPars_alphabin%d.pdf", nPars, alphabin);
}
else
{
    sprintf(cname1, "output/Wide_Resonances_Run2_Final/plots/bkg_fits/BkgFits%dPars_alphagt0p1.png", nPars);
    sprintf(cname2, "output/Wide_Resonances_Run2_Final/plots/bkg_fits/BkgFits%dPars_alphagt0p1.pdf", nPars);
}

c1->SaveAs(cname1);
c1->SaveAs(cname2);

}
