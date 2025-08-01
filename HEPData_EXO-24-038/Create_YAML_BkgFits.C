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

void Create_YAML_BkgFits(int alphabin){

double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

double lumi 	     = 137600;
double startit	     = 1607;
double endit	     = 9067;

double sig_perc_narrow_8p6[13] = {0.00319764, 0.0053499, 0.0079326, 0.0097159, 0.0175255, 0.0282868, 0.111487, 0.43986, 0.156438, 0.0774812, 0.0555897, 0.0448899, 0.0422457};
double sig_perc_wide_8p6[13] = {0.00535932, 0.00876979, 0.0107998, 0.0157531, 0.020138, 0.0315063, 0.0777101, 0.184978, 0.177426, 0.148437, 0.127, 0.0969549, 0.0951685};

double sig_perc_narrow_3p6[13] = {0.0028686, 0.00525447, 0.00717159, 0.00920572, 0.0111821, 0.0189228, 0.0282422, 0.0533884, 0.180514, 0.489127, 0.133848, 0.0394531, 0.0208225};
double sig_perc_wide_3p6[13] = {0.00265078, 0.00547306, 0.00742521, 0.0102742, 0.0162088, 0.0249265, 0.042666, 0.0856481, 0.202656, 0.307657, 0.176142, 0.0771381, 0.0411337};

double sig_narrow_norm_8p6 = 0.000047642*sig_perc_narrow_8p6[alphabin-1];
double sig_wide_norm_8p6 = 0.000063891*sig_perc_wide_8p6[alphabin-1];

double sig_narrow_norm_3p6 = 0.001337810*sig_perc_narrow_3p6[alphabin-1];
double sig_wide_norm_3p6 = 0.002232955*sig_perc_wide_3p6[alphabin-1];


//Fetch data, MC and fits

char fname_data[1024], fname_Fit_atlas[1024], fname_Fit_dijet[1024], fname_Fit_moddijet[1024];

sprintf(fname_data, "inputs/HISTOS_4J_AlldataRun2_SR_alphabin%d.root", alphabin);
sprintf(fname_Fit_atlas, "inputs/DijetFitResult_PFDijetRun2_4J_alphabin%d_PowExp.root", alphabin);
sprintf(fname_Fit_dijet, "inputs/DijetFitResult_PFDijetRun2_4J_alphabin%d_Dijet.root", alphabin);
sprintf(fname_Fit_moddijet, "inputs/DijetFitResult_PFDijetRun2_4J_alphabin%d_ModDijet.root", alphabin);

TFile *f_data = new TFile(fname_data);
TFile *f_Fit_atlas = new TFile(fname_Fit_atlas);
TFile *f_Fit_dijet = new TFile(fname_Fit_dijet);
TFile *f_Fit_moddijet = new TFile(fname_Fit_moddijet);

TH1D *Standard_Fit_unbinned_atlas = (TH1D*)(f_Fit_atlas->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *Standard_Fit_unbinned_dijet = (TH1D*)(f_Fit_dijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *Standard_Fit_unbinned_moddijet = (TH1D*)(f_Fit_moddijet->Get("Bkg_fit_unbinned"));  //1GeV histogram of Standard Fit
TH1D *h_data = (TH1D*)(f_data->Get("h_FourjetMass"));

//Fetch narrow signal histos for 8.6 TeV

char fname_sig_narrow_8p6[1024];
sprintf(fname_sig_narrow_8p6, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p25/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p015_S-8600_chi-2150_alphabin%d.root", alphabin);
TFile *f_sig_narrow_8p6 = new TFile(fname_sig_narrow_8p6);
TH1D *h_sig_narrow_8p6  = (TH1D*)(f_sig_narrow_8p6->Get("h_FourjetMass"));
h_sig_narrow_8p6->Scale(sig_narrow_norm_8p6*lumi);

//Fetch wide signal histos for 8.6 TeV

char fname_sig_wide_8p6[1024];
sprintf(fname_sig_wide_8p6, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p25/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p1_S-8600_chi-2150_alphabin%d.root", alphabin);
TFile *f_sig_wide_8p6 = new TFile(fname_sig_wide_8p6);
TH1D *h_sig_wide_8p6  = (TH1D*)(f_sig_wide_8p6->Get("h_FourjetMass"));
h_sig_wide_8p6->Scale(sig_wide_norm_8p6*lumi);




//Fetch narrow signal histos for 3.6 TeV

char fname_sig_narrow_3p6[1024];
sprintf(fname_sig_narrow_3p6, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p29/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p015_S-3600_chi-1044_alphabin%d.root", alphabin);
TFile *f_sig_narrow_3p6 = new TFile(fname_sig_narrow_3p6);
TH1D *h_sig_narrow_3p6 = (TH1D*)(f_sig_narrow_3p6->Get("h_FourjetMass"));
h_sig_narrow_3p6->Scale(sig_narrow_norm_3p6*lumi);


//Fetch wide signal histos for 3.6 TeV

char fname_sig_wide_3p6[1024];
sprintf(fname_sig_wide_3p6, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha0p29/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p1_S-3600_chi-1044_alphabin%d.root", alphabin);
TFile *f_sig_wide_3p6 = new TFile(fname_sig_wide_3p6);
TH1D *h_sig_wide_3p6 = (TH1D*)(f_sig_wide_3p6->Get("h_FourjetMass"));
h_sig_wide_3p6->Scale(sig_wide_norm_3p6*lumi);



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

        if (h_data->GetBinContent(i) < 30) h_data->SetBinError(i, 0.5 + sqrt( h_data->GetBinContent(i) + 0.25 ) );
	if (h_data->GetBinContent(i)==0) h_data->SetBinError(i,1.);
	h_data->SetBinContent(i,1000*h_data->GetBinContent(i)/((h_data->GetBinLowEdge(i+1)-h_data->GetBinLowEdge(i))*lumi));
	h_data->SetBinError(i,1000*h_data->GetBinError(i)/((h_data->GetBinLowEdge(i+1)-h_data->GetBinLowEdge(i))*lumi));

        h_sig_narrow_8p6->SetBinContent(i,1000*h_sig_narrow_8p6->GetBinContent(i)/((h_sig_narrow_8p6->GetBinLowEdge(i+1)-h_sig_narrow_8p6->GetBinLowEdge(i))*lumi));
        h_sig_wide_8p6->SetBinContent(i,1000*h_sig_wide_8p6->GetBinContent(i)/((h_sig_wide_8p6->GetBinLowEdge(i+1)-h_sig_wide_8p6->GetBinLowEdge(i))*lumi));

        h_sig_narrow_3p6->SetBinContent(i,1000*h_sig_narrow_3p6->GetBinContent(i)/((h_sig_narrow_3p6->GetBinLowEdge(i+1)-h_sig_narrow_3p6->GetBinLowEdge(i))*lumi));
        h_sig_wide_3p6->SetBinContent(i,1000*h_sig_wide_3p6->GetBinContent(i)/((h_sig_wide_3p6->GetBinLowEdge(i+1)-h_sig_wide_3p6->GetBinLowEdge(i))*lumi));

}

//creating pulls and calculate chi square:
double  chi_square_Fit_atlas = 0;
int     NDF_Fit_atlas = -3;  // 3 parameter function is used for Standard Fit
double  chi_square_Fit_dijet = 0;
int	NDF_Fit_dijet = -3;
double  chi_square_Fit_moddijet = 0;
int	NDF_Fit_moddijet = -3;

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
        double sig_narrow_cont_8p6 = h_sig_narrow_8p6->GetBinContent(i);
	double sig_wide_cont_8p6 = h_sig_wide_8p6->GetBinContent(i);
        double sig_narrow_cont_3p6 = h_sig_narrow_3p6->GetBinContent(i);
        double sig_wide_cont_3p6 = h_sig_wide_3p6->GetBinContent(i);

	if(edata>0)
	{
 		if(data_cont>Fit_atlas_cont) pull_Fit_atlas->SetBinContent(i,(-Fit_atlas_cont+data_cont)/errl);
                if(data_cont<Fit_atlas_cont) pull_Fit_atlas->SetBinContent(i,(-Fit_atlas_cont+data_cont)/errh);

		if(data_cont>Fit_dijet_cont) pull_Fit_dijet->SetBinContent(i,(-Fit_dijet_cont+data_cont)/errl);
                if(data_cont<Fit_dijet_cont) pull_Fit_dijet->SetBinContent(i,(-Fit_dijet_cont+data_cont)/errh);

                if(data_cont>Fit_moddijet_cont) pull_Fit_moddijet->SetBinContent(i,(-Fit_moddijet_cont+data_cont)/errl);
                if(data_cont<Fit_moddijet_cont) pull_Fit_moddijet->SetBinContent(i,(-Fit_moddijet_cont+data_cont)/errh); 

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

	

}

//h_sig_narrow_8p6->GetXaxis()->SetRangeUser(3147,9067);
h_sig_narrow_8p6->SetLineColor(kOrange+1);
h_sig_narrow_8p6->SetLineStyle(1);
h_sig_narrow_8p6->SetLineWidth(2);
//h_sig_wide_8p6->GetXaxis()->SetRangeUser(3147,9067);
h_sig_wide_8p6->SetLineColor(kYellow-6);
h_sig_wide_8p6->SetLineStyle(1);
h_sig_wide_8p6->SetLineWidth(2);

//h_sig_narrow_3p6->GetXaxis()->SetRangeUser(1770,4509);
h_sig_narrow_3p6->SetLineColor(kBlue);
h_sig_narrow_3p6->SetLineStyle(1);
h_sig_narrow_3p6->SetLineWidth(2);
//h_sig_wide_3p6->GetXaxis()->SetRangeUser(1770,4509);
h_sig_wide_3p6->SetLineColor(kCyan-3);
h_sig_wide_3p6->SetLineStyle(1);
h_sig_wide_3p6->SetLineWidth(2);

Standard_Fit_atlas->SetLineColor(2);
Standard_Fit_atlas->SetMarkerColor(2);
Standard_Fit_atlas->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_atlas->GetYaxis()->SetRangeUser(0.00000000015,9.);

Standard_Fit_dijet->SetLineColor(4);
Standard_Fit_dijet->SetMarkerColor(4);
Standard_Fit_dijet->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_dijet->GetYaxis()->SetRangeUser(0.00000000015,9.);

Standard_Fit_moddijet->SetLineColor(2);
Standard_Fit_moddijet->SetMarkerColor(2);
Standard_Fit_moddijet->GetXaxis()->SetRangeUser(startit,endit);
Standard_Fit_moddijet->GetYaxis()->SetRangeUser(0.00000000015,9.);

pull_Fit_atlas->SetLineColor(2);
pull_Fit_atlas->SetMarkerColor(2);
pull_Fit_atlas->GetXaxis()->SetRangeUser(startit,endit);
pull_Fit_atlas->GetYaxis()->SetRangeUser(-3.3,3.3);

pull_Fit_dijet->SetLineColor(4);
pull_Fit_dijet->SetMarkerColor(4);
pull_Fit_dijet->GetXaxis()->SetRangeUser(startit,endit);
pull_Fit_dijet->GetYaxis()->SetRangeUser(-3.3,3.3);

pull_Fit_moddijet->SetLineColor(2);
pull_Fit_moddijet->SetMarkerColor(2);
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
pad1r->SetPad(0.,0.38,1.,1.); //0.,0.37,1.,1.
pad1r->SetRightMargin(0.05); //0.05
pad1r->SetTopMargin(0.01); //0.05
pad1r->SetLeftMargin(0.1); //0.1
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
Standard_Fit_atlas->GetYaxis()->SetTitleSize(0.); //0.07
Standard_Fit_atlas->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_atlas->GetYaxis()->SetTitleOffset(0.97);
Standard_Fit_atlas->SetFillColor(0);
Standard_Fit_atlas->SetLineWidth(2);
Standard_Fit_atlas->SetLineColor(2);
Standard_Fit_atlas->SetLineStyle(3);
Standard_Fit_atlas->Draw("l hist");

Standard_Fit_dijet->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_dijet->GetYaxis()->SetTitleSize(0.); //0.07
Standard_Fit_dijet->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_dijet->GetYaxis()->SetTitleOffset(0.9);
Standard_Fit_dijet->SetFillColor(0);
Standard_Fit_dijet->SetLineWidth(2);
Standard_Fit_dijet->SetLineColor(2);
Standard_Fit_dijet->SetLineStyle(2);
Standard_Fit_dijet->Draw("l hist same");

Standard_Fit_moddijet->SetYTitle("d#sigma/dm_{4j} [pb/TeV]");
Standard_Fit_moddijet->GetYaxis()->SetTitleSize(0.); //0.07
Standard_Fit_moddijet->GetYaxis()->SetLabelSize(0.06);
Standard_Fit_moddijet->GetYaxis()->SetTitleOffset(0.9);
Standard_Fit_moddijet->SetFillColor(0);
Standard_Fit_moddijet->SetLineWidth(2);
Standard_Fit_moddijet->SetLineColor(2);
Standard_Fit_moddijet->SetLineStyle(1);
Standard_Fit_moddijet->Draw("l hist same");

h_datag->SetMarkerSize(1);
h_datag->Draw("same ep");

h_sig_narrow_8p6->Draw("hist same ][");
h_sig_wide_8p6->Draw("hist same ][");

h_sig_narrow_3p6->Draw("hist same ][");
h_sig_wide_3p6->Draw("hist same ][");


// Create and write YAML file

char outF_name[1024];
sprintf(outF_name, "outputs/Figures_005_006_BkgFitsWithSignals_alphabin%d.yaml", alphabin);

std::ofstream outF(outF_name);

outF << "independent_variables:" << endl;
outF << "- header:" << endl;
outF << "    name: Four-jet mass" << endl;
outF << "    units: TeV" << endl;
outF << "  values:" << endl;

for (int i=0; i<h_datag->GetN(); i++)
{
    double x, y;
    h_datag->GetPoint(i, x, y);

    if (x<1607 || x>9067 ) continue;

    double m4j_low = x - h_datag->GetErrorXlow(i);
    double m4j_high = x + h_datag->GetErrorXhigh(i);

    double errYlow = h_datag->GetErrorYlow(i);
    double errYhigh = h_datag->GetErrorYhigh(i);

    outF << "  - low: " << std::fixed << std::setprecision(3) << m4j_low/1000. << endl;
    outF << "    high: " << std::fixed << std::setprecision(3) << m4j_high/1000. << endl;    
}

outF << "dependent_variables:" << endl;
outF << "- header:" << endl;
outF << "    name: Cross-section of data" << endl;
outF << "    units: pb/TeV" << endl;
outF << "  values:" << endl;

for (int i=0; i<h_datag->GetN(); i++)
{
    double x, y;
    h_datag->GetPoint(i, x, y);

    if (x<1607 || x>9067 ) continue;

    double m4j_low = x - h_datag->GetErrorXlow(i);
    double m4j_high = x + h_datag->GetErrorXhigh(i);

    double errYlow = h_datag->GetErrorYlow(i);
    double errYhigh = h_datag->GetErrorYhigh(i);

    outF << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
    outF << "    errors:" << endl;
    outF << "      - asymerror:" << endl;
    outF << "          plus: " << std::fixed << std::setprecision(10) << errYhigh << endl;
    outF << "          minus: -" << std::fixed << std::setprecision(10) << errYlow << endl;
}

outF << "- header:" << endl;
outF << "    name: Cross-section of Dijet-3p fit" << endl;
outF << "    units: pb/TeV" << endl;
outF << "  values:" << endl;

for (int i=1; i<=Standard_Fit_dijet->GetNbinsX(); i++)
{
    double x = Standard_Fit_dijet->GetBinCenter(i);
    double y = Standard_Fit_dijet->GetBinContent(i);

    if (x<1607 || x>9067 ) continue;

    outF << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

outF << "- header:" << endl;
outF << "    name: Cross-section of PowExp-3p fit" << endl;
outF << "    units: pb/TeV" << endl;
outF << "  values:" << endl;

for (int i=1; i<=Standard_Fit_atlas->GetNbinsX(); i++)
{
    double x = Standard_Fit_atlas->GetBinCenter(i);
    double y = Standard_Fit_atlas->GetBinContent(i);

    if (x<1607 || x>9067 ) continue;

    outF << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

outF << "- header:" << endl;
outF << "    name: Cross-section of ModDijet-3p fit" << endl;
outF << "    units: pb/TeV" << endl;
outF << "  values:" << endl;

for (int i=1; i<=Standard_Fit_moddijet->GetNbinsX(); i++)
{
    double x = Standard_Fit_moddijet->GetBinCenter(i);
    double y = Standard_Fit_moddijet->GetBinContent(i);

    if (x<1607 || x>9067 ) continue;

    outF << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

outF << "- header:" << endl;
outF << "    name: Cross-section of signal with $M_{\\mathrm{S}}$ = 8.6 TeV, $M_{\\mathrm{\\chi}}$ = 2.15 TeV, $\\Gamma/M_{\\mathrm{S}}$ = 1.5%" << endl;
outF << "    units: pb/TeV" << endl;
outF << "  values:" << endl;

for (int i=1; i<=h_sig_narrow_8p6->GetNbinsX(); i++)
{
    double x = h_sig_narrow_8p6->GetBinCenter(i);
    double y = h_sig_narrow_8p6->GetBinContent(i);

    if (x<1607 || x>9067 ) continue;

    outF << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

outF << "- header:" << endl;
outF << "    name: Cross-section of signal with $M_{\\mathrm{S}}$ = 8.6 TeV, $M_{\\mathrm{\\chi}}$ = 2.15 TeV, $\\Gamma/M_{\\mathrm{S}}$ = 10%" << endl;
outF << "    units: pb/TeV" << endl;
outF << "  values:" << endl;

for (int i=1; i<=h_sig_wide_8p6->GetNbinsX(); i++)
{
    double x = h_sig_wide_8p6->GetBinCenter(i);
    double y = h_sig_wide_8p6->GetBinContent(i);

    if (x<1607 || x>9067 ) continue;

    outF << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}


if(alphabin==9 || alphabin==10 || alphabin==11)
{
    outF << "- header:" << endl;
    outF << "    name: Cross-section of signal with $M_{\\mathrm{S}}$ = 3.6 TeV, $M_{\\mathrm{\\chi}}$ = 1.0 TeV, $\\Gamma/M_{\\mathrm{S}}$ = 1.5%" << endl;
    outF << "    units: pb/TeV" << endl;
    outF << "  values:" << endl;

    for (int i=1; i<=h_sig_narrow_3p6->GetNbinsX(); i++)
    {
        double x = h_sig_narrow_3p6->GetBinCenter(i);
        double y = h_sig_narrow_3p6->GetBinContent(i);

        if (x<1607 || x>9067 ) continue;

        outF << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
    }

    outF << "- header:" << endl;
    outF << "    name: Cross-section of signal with $M_{\\mathrm{S}}$ = 3.6 TeV, $M_{\\mathrm{\\chi}}$ = 1.0 TeV, $\\Gamma/M_{\\mathrm{S}}$ = 10%" << endl;
    outF << "    units: pb/TeV" << endl;
    outF << "  values:" << endl;

    for (int i=1; i<=h_sig_wide_3p6->GetNbinsX(); i++)
    {
        double x = h_sig_wide_3p6->GetBinCenter(i);
        double y = h_sig_wide_3p6->GetBinContent(i);

        if (x<1607 || x>9067 ) continue;

        outF << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
    }


}



c1->cd();

TVirtualPad *pad2r ;
pad2r = c1->GetPad(2);
pad2r->SetLeftMargin(0.1); //0.1
pad2r->SetPad(0.,0.0,1,0.36); //0.,0.02,1,0.37
pad2r->SetBottomMargin(0.15); //0.15
pad2r->SetRightMargin(0.05); //0.05
pad2r->Draw();
pad2r->cd();
pad2r->cd()->SetLogx(1);
pad2r->cd()->SetTickx(1);
pad2r->cd()->SetTicky(1);

pull_Fit_atlas->GetXaxis()->SetTitle("Four-jet mass [TeV]");
pull_Fit_atlas->GetXaxis()->SetNoExponent();
pull_Fit_atlas->GetXaxis()->SetMoreLogLabels();
pull_Fit_atlas->GetXaxis()->SetTitleSize(2*0.); //2*0.06
pull_Fit_atlas->GetYaxis()->SetTitleSize(2*0.); //2*0.06
pull_Fit_atlas->GetXaxis()->SetLabelSize(2*0.07);
pull_Fit_atlas->GetYaxis()->SetLabelSize(0.09);
pull_Fit_atlas->GetXaxis()->SetLabelOffset(1000);
pull_Fit_atlas->GetYaxis()->SetLabelOffset(0.02);
pull_Fit_atlas->GetXaxis()->SetTitleOffset(1.2);
pull_Fit_atlas->GetYaxis()->SetTitleOffset(0.6);
pull_Fit_atlas->GetYaxis()->SetNdivisions(210);
pull_Fit_atlas->SetLineWidth(1);

pull_Fit_dijet->GetXaxis()->SetTitle("Fourjet mass [TeV]");
pull_Fit_dijet->GetXaxis()->SetNoExponent();
pull_Fit_dijet->GetXaxis()->SetMoreLogLabels();
pull_Fit_dijet->GetXaxis()->SetTitleSize(2*0.); //2*0.06
pull_Fit_dijet->GetYaxis()->SetTitleSize(2*0.); //2*0.06
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
pull_Fit_moddijet->GetXaxis()->SetTitleSize(2*0.); //2*0.06
pull_Fit_moddijet->GetYaxis()->SetTitleSize(2*0.); //2*0.06
pull_Fit_moddijet->GetXaxis()->SetLabelSize(2*0.07);
pull_Fit_moddijet->GetYaxis()->SetLabelSize(0.09);
pull_Fit_moddijet->GetYaxis()->SetLabelOffset(0.02);
pull_Fit_moddijet->GetXaxis()->SetLabelOffset(1000);
pull_Fit_moddijet->GetXaxis()->SetTitleOffset(1.2);
pull_Fit_moddijet->GetYaxis()->SetTitleOffset(0.6);
pull_Fit_moddijet->GetYaxis()->SetNdivisions(210);
pull_Fit_moddijet->SetLineWidth(1);

pull_Fit_atlas->GetXaxis()->SetTickSize(0.08);
pull_Fit_dijet->GetXaxis()->SetTickSize(0.08);
pull_Fit_moddijet->GetXaxis()->SetTickSize(0.08);

pull_Fit_atlas->GetYaxis()->SetTickSize(0.03);
pull_Fit_dijet->GetYaxis()->SetTickSize(0.03);
pull_Fit_moddijet->GetYaxis()->SetTickSize(0.03);

pull_Fit_atlas->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_Fit_atlas->SetFillColor(2);

pull_Fit_dijet->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_Fit_dijet->SetFillColor(4);

pull_Fit_moddijet->SetYTitle("#frac{Data #minus Fit}{Uncertainty}");
pull_Fit_moddijet->SetFillColor(2);
pull_Fit_moddijet->GetYaxis()->CenterTitle(1);
pull_Fit_moddijet->Draw("HIST");

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

}
