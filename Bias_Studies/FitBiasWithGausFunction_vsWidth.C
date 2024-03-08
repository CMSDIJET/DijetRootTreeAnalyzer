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

void FitBiasWithGausFunction_vsWidth(int Suu, int Chi, int function, int signal){

char function_name[1024];
if (function==0) sprintf(function_name,"Dijet");
if (function==1) sprintf(function_name,"Atlas");
if (function==2) sprintf(function_name,"ModDijet");

char signal_name[1024];
if (signal==0) sprintf(signal_name,"InjSignal0");
if (signal==2) sprintf(signal_name,"InjSignal2sigma");
if (signal==5) sprintf(signal_name,"InjSignal5sigma");

double r_true_W0p0043, r_true_W0p015, r_true_W0p05, r_true_W0p1;

if(signal==0) r_true_W0p0043 = 0;
if(signal==2) r_true_W0p0043 = 0.190423;
if(signal==5) r_true_W0p0043 = 2*0.190423;

if(signal==0) r_true_W0p015 = 0;
if(signal==2) r_true_W0p015 = 0.209863;
if(signal==5) r_true_W0p015 = 2*0.209863;

if(signal==0) r_true_W0p05 = 0;
if(signal==2) r_true_W0p05 = 0.284180;
if(signal==5) r_true_W0p05 = 2*0.284180;

if(signal==0) r_true_W0p1 = 0;
if(signal==2) r_true_W0p1 = 0.325195;
if(signal==5) r_true_W0p1 = 2*0.325195;

gStyle->SetOptStat(0);

int nbins = 19;
if(signal==0) nbins = 71;

TH1D *h_bias_W0p0043 = new TH1D("h_bias_W0p0043","", nbins,-5,5);
TH1D *h_bias_W0p015 = new TH1D("h_bias_W0p015","", nbins,-5,5);
TH1D *h_bias_W0p05 = new TH1D("h_bias_W0p05","", nbins,-5,5);
TH1D *h_bias_W0p1 = new TH1D("h_bias_W0p1","", nbins,-5,5);  

TH1D *h_r_W0p0043 = new TH1D("h_r_W0p0043","", 500,0,5);
TH1D *h_r_W0p015 = new TH1D("h_r_W0p015","", 500,0,5);
TH1D *h_r_W0p05 = new TH1D("h_r_W0p05","", 500,0,5);
TH1D *h_r_W0p1 = new TH1D("h_r_W0p1","", 500,0,5);

TH1D *h_rHiErr_W0p0043 = new TH1D("h_rHiErr_W0p0043","", 500,0,5);
TH1D *h_rHiErr_W0p015 = new TH1D("h_rHiErr_W0p015","", 500,0,5);
TH1D *h_rHiErr_W0p05 = new TH1D("h_rHiErr_W0p05","", 500,0,5);
TH1D *h_rHiErr_W0p1 = new TH1D("h_rHiErr_W0p1","", 500,0,5);

TH1D *h_rLoErr_W0p0043 = new TH1D("h_rLoErr_W0p0043","", 500,0,5);
TH1D *h_rLoErr_W0p015 = new TH1D("h_rLoErr_W0p015","", 500,0,5);
TH1D *h_rLoErr_W0p05 = new TH1D("h_rLoErr_W0p05","", 500,0,5);
TH1D *h_rLoErr_W0p1 = new TH1D("h_rLoErr_W0p1","", 500,0,5);

char fname_W0p0043[500], fname_W0p015[500], fname_W0p05[500], fname_W0p1[500];

sprintf(fname_W0p0043,"rootfiles_NoToysFrequentist/fitDiagnostics_W-0p0043_%d_%d_Gen%s_FitEnvelope_%s.root", Suu, Chi, function_name, signal_name);
sprintf(fname_W0p015,"rootfiles_NoToysFrequentist/fitDiagnostics_W-0p015_%d_%d_Gen%s_FitEnvelope_%s.root", Suu, Chi, function_name, signal_name);
sprintf(fname_W0p05,"rootfiles_NoToysFrequentist/fitDiagnostics_W-0p05_%d_%d_Gen%s_FitEnvelope_%s.root", Suu, Chi, function_name, signal_name);
sprintf(fname_W0p1,"rootfiles_NoToysFrequentist/fitDiagnostics_W-0p1_%d_%d_Gen%s_FitEnvelope_%s.root", Suu, Chi, function_name, signal_name);

TFile *f_W0p0043 = TFile::Open(fname_W0p0043,"READ");
TFile *f_W0p015 = TFile::Open(fname_W0p015,"READ");
TFile *f_W0p05 = TFile::Open(fname_W0p05,"READ");
TFile *f_W0p1 = TFile::Open(fname_W0p1,"READ");
	
cout << "Files used: " << endl;
cout << fname_W0p0043 << endl;
cout << fname_W0p015 << endl;
cout << fname_W0p05 << endl;
cout << fname_W0p1 << endl;

int fit_status, nentries;
double r, rErr, rHiErr,rLoErr; 

  
TTree* tree_fit_sb_W0p0043 = (TTree*)(f_W0p0043->Get("tree_fit_sb"));
tree_fit_sb_W0p0043->SetBranchAddress("r",&r);
tree_fit_sb_W0p0043->SetBranchAddress("rErr",&rErr);
tree_fit_sb_W0p0043->SetBranchAddress("rHiErr",&rHiErr);
tree_fit_sb_W0p0043->SetBranchAddress("rLoErr",&rLoErr);
tree_fit_sb_W0p0043->SetBranchAddress("fit_status",&fit_status);

nentries=(Int_t)tree_fit_sb_W0p0043->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	tree_fit_sb_W0p0043->GetEntry(i);

	if(fit_status>-1)
	{
   
   		h_r_W0p0043->Fill(r);
	   	h_rHiErr_W0p0043->Fill(rHiErr);
		h_rLoErr_W0p0043->Fill(rLoErr);

		if(signal==0)
		{
			h_bias_W0p0043->Fill((r-r_true_W0p0043)/rHiErr); //for 0 signal injected
		}
		else
		{
         		if(r > r_true_W0p0043) h_bias_W0p0043->Fill((r-r_true_W0p0043)/rLoErr);
         		if(r < r_true_W0p0043) h_bias_W0p0043->Fill((r-r_true_W0p0043)/rHiErr);  
		}

	}	      
}// end of event loop



TTree* tree_fit_sb_W0p015 = (TTree*)(f_W0p015->Get("tree_fit_sb"));
tree_fit_sb_W0p015->SetBranchAddress("r",&r);
tree_fit_sb_W0p015->SetBranchAddress("rErr",&rErr);
tree_fit_sb_W0p015->SetBranchAddress("rHiErr",&rHiErr);
tree_fit_sb_W0p015->SetBranchAddress("rLoErr",&rLoErr);
tree_fit_sb_W0p015->SetBranchAddress("fit_status",&fit_status);

nentries=(Int_t)tree_fit_sb_W0p015->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	tree_fit_sb_W0p015->GetEntry(i);

	if(fit_status>-1)
	{
   
   		h_r_W0p015->Fill(r);
	   	h_rHiErr_W0p015->Fill(rHiErr);
		h_rLoErr_W0p015->Fill(rLoErr);

		if(signal==0)
		{
			h_bias_W0p015->Fill((r-r_true_W0p015)/rHiErr); //for 0 signal injected
		}
		else
		{
         		if(r > r_true_W0p015) h_bias_W0p015->Fill((r-r_true_W0p015)/rLoErr);
         		if(r < r_true_W0p015) h_bias_W0p015->Fill((r-r_true_W0p015)/rHiErr);  
		}

	}	      
}// end of event loop



TTree* tree_fit_sb_W0p05 = (TTree*)(f_W0p05->Get("tree_fit_sb"));
tree_fit_sb_W0p05->SetBranchAddress("r",&r);
tree_fit_sb_W0p05->SetBranchAddress("rErr",&rErr);
tree_fit_sb_W0p05->SetBranchAddress("rHiErr",&rHiErr);
tree_fit_sb_W0p05->SetBranchAddress("rLoErr",&rLoErr);
tree_fit_sb_W0p05->SetBranchAddress("fit_status",&fit_status);

nentries=(Int_t)tree_fit_sb_W0p05->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	tree_fit_sb_W0p05->GetEntry(i);

	if(fit_status>-1)
	{
   
   		h_r_W0p05->Fill(r);
	   	h_rHiErr_W0p05->Fill(rHiErr);
		h_rLoErr_W0p05->Fill(rLoErr);

		if(signal==0)
		{
			h_bias_W0p05->Fill((r-r_true_W0p05)/rHiErr); //for 0 signal injected
		}
		else
		{
         		if(r > r_true_W0p05) h_bias_W0p05->Fill((r-r_true_W0p05)/rLoErr);
         		if(r < r_true_W0p05) h_bias_W0p05->Fill((r-r_true_W0p05)/rHiErr);  
		}

	}	      
}// end of event loop



TTree* tree_fit_sb_W0p1 = (TTree*)(f_W0p1->Get("tree_fit_sb"));
tree_fit_sb_W0p1->SetBranchAddress("r",&r);
tree_fit_sb_W0p1->SetBranchAddress("rErr",&rErr);
tree_fit_sb_W0p1->SetBranchAddress("rHiErr",&rHiErr);
tree_fit_sb_W0p1->SetBranchAddress("rLoErr",&rLoErr);
tree_fit_sb_W0p1->SetBranchAddress("fit_status",&fit_status);

nentries=(Int_t)tree_fit_sb_W0p1->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	tree_fit_sb_W0p1->GetEntry(i);

	if(fit_status>-1)
	{
   
   		h_r_W0p1->Fill(r);
	   	h_rHiErr_W0p1->Fill(rHiErr);
		h_rLoErr_W0p1->Fill(rLoErr);

		if(signal==0)
		{
			h_bias_W0p1->Fill((r-r_true_W0p1)/rHiErr); //for 0 signal injected
		}
		else
		{
         		if(r > r_true_W0p1) h_bias_W0p1->Fill((r-r_true_W0p1)/rLoErr);
         		if(r < r_true_W0p1) h_bias_W0p1->Fill((r-r_true_W0p1)/rHiErr);  
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

double frxmin, frxmax, frymin, frymax;

if(signal==0) {frxmin = -3; frxmax = 3; frymin = 0.5; frymax = 1500;}
if(signal!=0) {frxmin = -5; frxmax = 7; frymin = 0; frymax = 300;}

auto frame = c->DrawFrame(frxmin,frymin,frxmax,frymax);

frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitleOffset(0.95);
frame->GetXaxis()->SetTitle("(#mu - #mu_{true} ) / #sigma_{#mu}");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(0.97);
frame->GetYaxis()->SetTitle("Toy datasets");


//h_bias_W0p0043->GetYaxis()->SetTitle("Toy datasets");
//h_bias_W0p0043->GetXaxis()->SetTitle("(#mu - #mu_{true} ) / #sigma_{#mu}");

//h_bias_W0p0043->GetYaxis()->SetTitleSize(0.05);
//h_bias_W0p0043->GetXaxis()->SetTitleSize(0.05);
//h_bias_W0p0043->GetYaxis()->SetTitleOffset(0.9);
//h_bias_W0p0043->GetXaxis()->SetTitleOffset(0.95);

//if(signal==0) h_bias_W0p0043->GetXaxis()->SetRangeUser(-2,3);
//if(signal!=0) h_bias_W0p0043->GetXaxis()->SetRangeUser(-5,7);

h_bias_W0p0043->SetMarkerStyle(21); //24
h_bias_W0p0043->SetLineWidth(2);
h_bias_W0p0043->SetMarkerColor(kBlack);
h_bias_W0p0043->SetLineColor(kBlack);
h_bias_W0p0043->SetMarkerSize(1.2);

h_bias_W0p015->SetMarkerStyle(22); //26
h_bias_W0p015->SetLineWidth(2);
h_bias_W0p015->SetMarkerColor(kRed+1);
h_bias_W0p015->SetLineColor(kRed+1);
h_bias_W0p0043->SetMarkerSize(1.3);

h_bias_W0p05->SetMarkerStyle(23); //32
h_bias_W0p05->SetLineWidth(2);
h_bias_W0p05->SetMarkerColor(kBlue-3);
h_bias_W0p05->SetLineColor(kBlue-3);
h_bias_W0p0043->SetMarkerSize(1.3);

h_bias_W0p1->SetMarkerStyle(20); //25
h_bias_W0p1->SetLineWidth(2);
h_bias_W0p1->SetMarkerColor(kViolet);
h_bias_W0p1->SetLineColor(kViolet);
h_bias_W0p0043->SetMarkerSize(1.3);

h_bias_W0p0043->Draw("PE1 same");
h_bias_W0p015->Draw("PE1 same");
h_bias_W0p05->Draw("PE1 same");
h_bias_W0p1->Draw("PE1 same");

double mean_W0p0043, sigma_W0p0043, meanerr_W0p0043, sigmaerr_W0p0043;
double mean_W0p015, sigma_W0p015, meanerr_W0p015, sigmaerr_W0p015;
double mean_W0p05, sigma_W0p05, meanerr_W0p05, sigmaerr_W0p05;
double mean_W0p1, sigma_W0p1, meanerr_W0p1, sigmaerr_W0p1;

TF1* func_W0p0043;
TF1* func_W0p015;
TF1* func_W0p05;
TF1* func_W0p1;

if(signal!=0)
{
	func_W0p0043 = new TF1("func_W0p0043", "gaus", -5,5);
	func_W0p0043->SetLineColor(kBlack);

	h_bias_W0p0043->Fit("gaus","","", -2.5, 3);

	TF1 *gaus_W0p0043 = h_bias_W0p0043->GetFunction("gaus");
	mean_W0p0043 = gaus_W0p0043->GetParameter(1); 
	sigma_W0p0043 = gaus_W0p0043->GetParameter(2);
	meanerr_W0p0043 = gaus_W0p0043->GetParError(1); 
	sigmaerr_W0p0043 = gaus_W0p0043->GetParError(2);

	gaus_W0p0043->SetLineColor(kBlack);
	gaus_W0p0043->Draw("same");


	func_W0p015 = new TF1("func_W0p015", "gaus", -5,5);
	func_W0p015->SetLineColor(kRed+1);

	h_bias_W0p015->Fit("gaus","","", -2.5, 3);

	TF1 *gaus_W0p015 = h_bias_W0p015->GetFunction("gaus");
	mean_W0p015 = gaus_W0p015->GetParameter(1); 
	sigma_W0p015 = gaus_W0p015->GetParameter(2);
	meanerr_W0p015 = gaus_W0p015->GetParError(1); 
	sigmaerr_W0p015 = gaus_W0p015->GetParError(2);

	gaus_W0p015->SetLineColor(kRed+1);
	gaus_W0p015->Draw("same");


	func_W0p05 = new TF1("func_W0p05", "gaus", -5,5);
	func_W0p05->SetLineColor(kBlue-3);

	h_bias_W0p05->Fit("gaus","","", -2.5, 3);

	TF1 *gaus_W0p05 = h_bias_W0p05->GetFunction("gaus");
	mean_W0p05 = gaus_W0p05->GetParameter(1); 
	sigma_W0p05 = gaus_W0p05->GetParameter(2);
	meanerr_W0p05 = gaus_W0p05->GetParError(1); 
	sigmaerr_W0p05 = gaus_W0p05->GetParError(2);

	gaus_W0p05->SetLineColor(kBlue-3);
	gaus_W0p05->Draw("same");


	func_W0p1 = new TF1("func_W0p1", "gaus", -5,5);
	func_W0p1->SetLineColor(kViolet);

	h_bias_W0p1->Fit("gaus","","", -2.5, 3);

	TF1 *gaus_W0p1 = h_bias_W0p1->GetFunction("gaus");
	mean_W0p1 = gaus_W0p1->GetParameter(1); 
	sigma_W0p1 = gaus_W0p1->GetParameter(2);
	meanerr_W0p1 = gaus_W0p1->GetParError(1); 
	sigmaerr_W0p1 = gaus_W0p1->GetParError(2);

	gaus_W0p1->SetLineColor(kViolet);
	gaus_W0p1->Draw("same");
}

char legname1_v1[500], legname1_v2[500], legname2_W0p0043[500], legname3_W0p0043[500], legname2_W0p015[500], legname3_W0p015[500], legname2_W0p05[500], legname3_W0p05[500], legname2_W0p1[500], legname3_W0p1[500];

sprintf(legname1_v1,"M_{S} = %d GeV", Suu);
sprintf(legname1_v2,"M_{#chi} = %d GeV", Chi);

if(signal!=0)
{
	sprintf(legname2_W0p0043,"Mean = %.2f #pm %.2f", mean_W0p0043, meanerr_W0p0043);
	sprintf(legname3_W0p0043,"Sigma = %.2f #pm %.2f", sigma_W0p0043, sigmaerr_W0p0043);

	sprintf(legname2_W0p015,"Mean = %.2f #pm %.2f", mean_W0p015, meanerr_W0p015);
	sprintf(legname3_W0p015,"Sigma = %.2f #pm %.2f", sigma_W0p015, sigmaerr_W0p015);

	sprintf(legname2_W0p05,"Mean = %.2f #pm %.2f", mean_W0p05, meanerr_W0p05);
	sprintf(legname3_W0p05,"Sigma = %.2f #pm %.2f", sigma_W0p05, sigmaerr_W0p05);

	sprintf(legname2_W0p1,"Mean = %.2f #pm %.2f", mean_W0p1, meanerr_W0p1);
	sprintf(legname3_W0p1,"Sigma = %.2f #pm %.2f", sigma_W0p1, sigmaerr_W0p1);
}

double xmin = 0.65;
double xmax = 0.9;
double ymin = 0.19;
double ymax = 0.84;
if(signal==0) {ymin = 0.15; ymax=0.55; xmin=0.15; xmax=0.4;}

TLegend *leg = new TLegend(xmin,ymin,xmax,ymax); 
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.03);
leg->AddEntry((TObject*)0, legname1_v1, "");
leg->AddEntry((TObject*)0, legname1_v2, "");
leg->AddEntry(h_bias_W0p0043, "#Gamma / M_{S} = 0.43 %", "PE");
leg->AddEntry(h_bias_W0p015, "#Gamma / M_{S} = 1.5 %", "PE");
leg->AddEntry(h_bias_W0p05, "#Gamma / M_{S} = 5 %", "PE");
leg->AddEntry(h_bias_W0p1, "#Gamma / M_{S} = 10 %", "PE");
leg->AddEntry((TObject*)0, "", "");
if(signal!=0)
{
	TLegendEntry *entry1_W0p0043 = leg->AddEntry(func_W0p0043,"Gaussian fit","L");
	TLegendEntry *entry2_W0p0043 = leg->AddEntry((TObject*)0, legname2_W0p0043, "");
	TLegendEntry *entry3_W0p0043 = leg->AddEntry((TObject*)0, legname3_W0p0043, "");
	entry1_W0p0043->SetTextColor(kBlack);
	entry2_W0p0043->SetTextColor(kBlack);
	entry3_W0p0043->SetTextColor(kBlack);

	TLegendEntry *entry1_W0p015 = leg->AddEntry(func_W0p015,"Gaussian fit","L");
	TLegendEntry *entry2_W0p015 = leg->AddEntry((TObject*)0, legname2_W0p015, "");
	TLegendEntry *entry3_W0p015 = leg->AddEntry((TObject*)0, legname3_W0p015, "");
	entry1_W0p015->SetTextColor(kRed+1);
	entry2_W0p015->SetTextColor(kRed+1);
	entry3_W0p015->SetTextColor(kRed+1);

	TLegendEntry *entry1_W0p05 = leg->AddEntry(func_W0p05,"Gaussian fit","L");
	TLegendEntry *entry2_W0p05 = leg->AddEntry((TObject*)0, legname2_W0p05, "");
	TLegendEntry *entry3_W0p05 = leg->AddEntry((TObject*)0, legname3_W0p05, "");
	entry1_W0p05->SetTextColor(kBlue-3);
	entry2_W0p05->SetTextColor(kBlue-3);
	entry3_W0p05->SetTextColor(kBlue-3);

	TLegendEntry *entry1_W0p1 = leg->AddEntry(func_W0p1,"Gaussian fit","L");
	TLegendEntry *entry2_W0p1 = leg->AddEntry((TObject*)0, legname2_W0p1, "");
	TLegendEntry *entry3_W0p1 = leg->AddEntry((TObject*)0, legname3_W0p1, "");
	entry1_W0p1->SetTextColor(kViolet);
	entry2_W0p1->SetTextColor(kViolet);
	entry3_W0p1->SetTextColor(kViolet);
}
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

sprintf(nameplot1,"plots/NoToysFrequentist/Gen%s_FitEnvelope_Suu%d_Chi%d_%s_vsWidth.png", function_name, Suu, Chi, signal_name);
sprintf(nameplot2,"plots/NoToysFrequentist/Gen%s_FitEnvelope_Suu%d_Chi%d_%s_vsWidth.pdf", function_name, Suu, Chi, signal_name);

c->SaveAs(nameplot1); 
c->SaveAs(nameplot2);



}











