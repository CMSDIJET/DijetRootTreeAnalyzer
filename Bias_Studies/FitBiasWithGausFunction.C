#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "Math/MinimizerOptions.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"

void FitBiasWithGausFunction(int Suu, int Chi, double width, int function, int signal){

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char function_name[1024];
if (function==0) sprintf(function_name,"Dijet");
if (function==1) sprintf(function_name,"Atlas");
if (function==2) sprintf(function_name,"ModDijet");

char signal_name[1024];
if (signal==0) sprintf(signal_name,"InjSignal0");
if (signal==2) sprintf(signal_name,"InjSignal2sigma");
if (signal==5) sprintf(signal_name,"InjSignal5sigma");

double r_true;
if(signal==0 && width==0.0043) r_true = 0;
if(signal==2 && width==0.0043) r_true = 0.190423;
if(signal==5 && width==0.0043) r_true = 2*0.190423;

if(signal==0 && width==0.015) r_true = 0;
if(signal==2 && width==0.015) r_true = 0.209863;
if(signal==5 && width==0.015) r_true = 2*0.209863;

if(signal==0 && width==0.05) r_true = 0;
if(signal==2 && width==0.05) r_true = 0.284180;
if(signal==5 && width==0.05) r_true = 2*0.284180;

if(signal==0 && width==0.1) r_true = 0;
if(signal==2 && width==0.1) r_true = 0.325195;
if(signal==5 && width==0.1) r_true = 2*0.325195;

gStyle->SetOptStat(0);

int nbins = 19;
if(signal==0) nbins = 71;

TH1D *h_bias = new TH1D("h_bias","", nbins,-5,5); //25  

TH1D *h_r = new TH1D("h_r","", 500,0,5);
TH1D *h_rHiErr = new TH1D("h_rHiErr","", 500,0,5);
TH1D *h_rLoErr = new TH1D("h_rLoErr","", 500,0,5);


char fname[500];
sprintf(fname,"rootfiles_NoToysFrequentist/fitDiagnostics_W-%s_%d_%d_Gen%s_FitEnvelope_%s.root", width_name, Suu, Chi, function_name, signal_name);


TFile *f = TFile::Open(fname,"READ");	
cout << "File used: " << fname << endl;

f->cd();
 
int fit_status;
double r, rErr, rHiErr,rLoErr; 
  
TTree* tree_fit_sb=(TTree*)(f->Get("tree_fit_sb"));
tree_fit_sb->SetBranchAddress("r",&r);
tree_fit_sb->SetBranchAddress("rErr",&rErr);
tree_fit_sb->SetBranchAddress("rHiErr",&rHiErr);
tree_fit_sb->SetBranchAddress("rLoErr",&rLoErr);
tree_fit_sb->SetBranchAddress("fit_status",&fit_status);

Int_t nentries=(Int_t)tree_fit_sb->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	tree_fit_sb->GetEntry(i);

	if(fit_status>-1)
	{
   
   		h_r->Fill(r);
	   	h_rHiErr->Fill(rHiErr);
		h_rLoErr->Fill(rLoErr);

		if(signal==0)
		{
			h_bias->Fill((r-r_true)/rHiErr); //for 0 signal injected
		}
		else
		{
         		if(r > r_true) h_bias->Fill((r-r_true)/rLoErr);
         		if(r < r_true) h_bias->Fill((r-r_true)/rHiErr);  
		}

	}	      
}// end of event loop


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.04);
c->SetTopMargin(0.1);
c->SetBottomMargin(0.12);

if(signal==0) c->SetLogy(1);

h_bias->GetYaxis()->SetTitle("Toy datasets");
h_bias->GetXaxis()->SetTitle("(#mu - #mu_{true} ) / #sigma_{#mu}");

h_bias->GetYaxis()->SetTitleSize(0.05);
h_bias->GetXaxis()->SetTitleSize(0.05);
h_bias->GetYaxis()->SetTitleOffset(0.9);
h_bias->GetXaxis()->SetTitleOffset(0.95);

if(signal==0) h_bias->GetXaxis()->SetRangeUser(-2,2);

if(signal==0) h_bias->GetYaxis()->SetRangeUser(0.5,1500);
if(signal!=0) h_bias->GetYaxis()->SetRangeUser(0,300);

h_bias->SetMarkerStyle(24);
h_bias->SetLineWidth(2);
h_bias->SetMarkerColor(kBlue-2);
h_bias->SetLineColor(kBlue-2);

h_bias->Draw("PE1");


double mean, sigma, meanerr, sigmaerr;
TF1* func;

if(signal!=0)
{
	func = new TF1("func", "gaus", -5,5);

	h_bias->Fit("gaus","","", -2.5, 3);


	TF1 *gaus = h_bias->GetFunction("gaus");
	mean = gaus->GetParameter(1); 
	sigma = gaus->GetParameter(2);
	meanerr = gaus->GetParError(1); 
	sigmaerr = gaus->GetParError(2);
}

char legname1[500], legname2[500], legname3[500];
sprintf(legname1,"#splitline{#Gamma / M_{S} = %.0f %%}{#splitline{M_{S} = %d GeV}{M_{#chi} = %d GeV}}", width*100., Suu, Chi);

if(signal!=0)
{
	sprintf(legname2,"Mean = %.2f #pm %.2f", mean, meanerr);
	sprintf(legname3,"Sigma = %.2f #pm %.2f", sigma, sigmaerr);
}

double xmin = 0.65;
double xmax = 0.9;
double ymin = 0.59;
double ymax = 0.84;
/*double xmin = 0.12;
double xmax = 0.45;
double ymin = 0.34;
double ymax = 0.59;*/
if(signal==0) ymin = 0.69;

TLegend *leg = new TLegend(xmin,ymin,xmax,ymax); 
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.03);
leg->AddEntry(h_bias, legname1, "LPE");
leg->AddEntry((TObject*)0, "", "");
leg->AddEntry((TObject*)0, "", "");
if(signal!=0) leg->AddEntry(func,"Gaussian fit","L");
if(signal!=0) leg->AddEntry((TObject*)0, legname2, "");
if(signal!=0) leg->AddEntry((TObject*)0, legname3, "");
leg->Draw();


TPaveText *cms = new TPaveText(0.17,0.92,0.32,0.95,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);
cms->Draw();


TPaveText *lumileg = new TPaveText(0.84,0.92,0.94,0.95,"NDC");
lumileg->AddText("13 TeV");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);
lumileg->Draw();


char legname4[500], legname5[500], legname6[500];
sprintf(legname4,"Generate with %s", function_name);
sprintf(legname5,"Fit with Envelope");
if(signal==0) sprintf(legname6,"Injected Signal: 0");
if(signal==2) sprintf(legname6,"Injected Signal: 2#sigma");
if(signal==5) sprintf(legname6,"Injected Signal: 5#sigma");

TPaveText *signal_leg = new TPaveText(0.18,0.72,0.38,0.87,"NDC");
signal_leg->AddText(legname4);
signal_leg->AddText(legname5);
signal_leg->AddText(legname6);
signal_leg->SetFillColor(0);
signal_leg->SetBorderSize(0);
signal_leg->SetTextFont(42);
signal_leg->SetTextSize(0.04);
signal_leg->Draw();


char nameplot1[500], nameplot2[500];

sprintf(nameplot1,"plots/NoToysFrequentist/Gen%s_FitEnvelope_W-%s_Suu%d_Chi%d_%s.png", function_name, width_name, Suu, Chi, signal_name);
sprintf(nameplot2,"plots/NoToysFrequentist/Gen%s_FitEnvelope_W-%s_Suu%d_Chi%d_%s.pdf", function_name, width_name, Suu, Chi, signal_name);

c->SaveAs(nameplot1); 
c->SaveAs(nameplot2);



}











