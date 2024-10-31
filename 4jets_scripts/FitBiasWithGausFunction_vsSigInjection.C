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


void FitBiasWithGausFunction_vsSigInjection(double width, double alpha_true, double Suu, int gen_function, int fit_function){

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char alpha_true_name[1024];
if (alpha_true==0.11) sprintf(alpha_true_name,"0p11");
if (alpha_true==0.13) sprintf(alpha_true_name,"0p13");
if (alpha_true==0.15) sprintf(alpha_true_name,"0p15");
if (alpha_true==0.17) sprintf(alpha_true_name,"0p17");
if (alpha_true==0.19) sprintf(alpha_true_name,"0p19");
if (alpha_true==0.21) sprintf(alpha_true_name,"0p21");
if (alpha_true==0.23) sprintf(alpha_true_name,"0p23");
if (alpha_true==0.25) sprintf(alpha_true_name,"0p25");
if (alpha_true==0.27) sprintf(alpha_true_name,"0p27");
if (alpha_true==0.29) sprintf(alpha_true_name,"0p29");
if (alpha_true==0.31) sprintf(alpha_true_name,"0p31");
if (alpha_true==0.33) sprintf(alpha_true_name,"0p33");
if (alpha_true==0.42) sprintf(alpha_true_name,"0p42");

char gen_function_name[1024], fit_function_name[1024];
if (gen_function==0) sprintf(gen_function_name,"Dijet");
if (gen_function==1) sprintf(gen_function_name,"Atlas");
if (gen_function==2) sprintf(gen_function_name,"ModDijet");
if (fit_function==0) sprintf(fit_function_name,"Dijet");
if (fit_function==1) sprintf(fit_function_name,"Atlas");
if (fit_function==2) sprintf(fit_function_name,"ModDijet");
if (fit_function==012) sprintf(fit_function_name,"Envelope");

char gen_function_name_forleg[1024], fit_function_name_forleg[1024];
if (gen_function==0) sprintf(gen_function_name_forleg,"Dijet-3p");
if (gen_function==1) sprintf(gen_function_name_forleg,"PowExp-3p");
if (gen_function==2) sprintf(gen_function_name_forleg,"ModDijet-3p");
if (fit_function==0) sprintf(fit_function_name_forleg,"Dijet-3p");
if (fit_function==1) sprintf(fit_function_name_forleg,"PowExp-3p");
if (fit_function==2) sprintf(fit_function_name_forleg,"ModDijet-3p");
if (fit_function==012) sprintf(fit_function_name_forleg,"Envelope");


//Fetch expected limit
double limit = 0;

char name[1024];

if(Suu<4500)
{
    sprintf(name,"/eos/user/i/izisopou/4jets_Run2/CMSSW_14_1_0_pre4/src/CMSDIJET/DijetRootTreeAnalyzer/output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/limits/higgsCombine_alpha%s_W-%s_%.0f_%.0f.AsymptoticLimits.mH120.root", alpha_true_name, alpha_true_name, width_name, Suu, Suu*alpha_true);
}
else
{
    sprintf(name,"/eos/user/i/izisopou/4jets_Run2/CMSSW_14_1_0_pre4/src/CMSDIJET/DijetRootTreeAnalyzer/output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/limits/higgsCombine_alpha%s_W-%s_%.0f_%.0f.HybridNew.mH120.root", alpha_true_name, alpha_true_name, width_name, Suu, Suu*alpha_true);
}

cout << "name = " << name << endl;

TFile *f = new TFile(name, "read");
TTree *t = (TTree*)f->Get("limit");
t->SetBranchAddress("limit", &limit);
t->GetEntry(2);
double exp_limit = limit;
f->Close();


cout << "exp_limit = " << exp_limit << endl;


double r_true_0 = 0;
double r_true_2sigma = exp_limit; 
double r_true_5sigma = 2.*exp_limit; 

    
cout << "Suu mass = " << Suu << " GeV" << endl;
cout << "Chi mass = " << Suu*alpha_true << " GeV" << endl;
cout << "Width = " << width << endl;
cout << "Gen from " << gen_function_name << endl;    
cout << "Fit with " << fit_function_name << endl; 

cout << "" << endl;

cout << "Inj. signals = " << r_true_0 << " , " << r_true_2sigma << " , " << r_true_5sigma << endl;
    
cout << "" << endl;

gStyle->SetOptStat(0);


int nbins = 39;

TH1D *h_bias_r0 = new TH1D("h_bias_r0","", nbins,-10,10);
TH1D *h_bias_r2sigma = new TH1D("h_bias_r2sigma","", nbins,-10,10);
TH1D *h_bias_r5sigma = new TH1D("h_bias_r5sigma","", nbins,-10,10);



char fname_r0[500], fname_r2sigma[500], fname_r5sigma[500];

sprintf(fname_r0,"output/Wide_Resonances_Run2_Final/bias_studies_highest_signif_mass_points/fitDiagnostics_W-%s_%.0f_%.0f_Gen%s_InjSignal0_Fit%s.root", width_name, Suu, Suu*alpha_true, gen_function_name, fit_function_name);
sprintf(fname_r2sigma,"output/Wide_Resonances_Run2_Final/bias_studies_highest_signif_mass_points/fitDiagnostics_W-%s_%.0f_%.0f_Gen%s_InjSignal2sigma_Fit%s.root", width_name, Suu, Suu*alpha_true, gen_function_name, fit_function_name);
sprintf(fname_r5sigma,"output/Wide_Resonances_Run2_Final/bias_studies_highest_signif_mass_points/fitDiagnostics_W-%s_%.0f_%.0f_Gen%s_InjSignal5sigma_Fit%s.root", width_name, Suu, Suu*alpha_true, gen_function_name, fit_function_name);

TFile *f_fitDiagn_r0 = TFile::Open(fname_r0,"READ");
TFile *f_fitDiagn_r2sigma = TFile::Open(fname_r2sigma,"READ");
TFile *f_fitDiagn_r5sigma = TFile::Open(fname_r5sigma,"READ");
	
cout << "Files used: " << endl;
cout << fname_r0 << endl;
cout << fname_r2sigma << endl;
cout << fname_r5sigma << endl;

int fit_status, nentries;
double r, rErr, rHiErr,rLoErr; 
  
  
TTree* tree_fit_sb_r0 = (TTree*)(f_fitDiagn_r0->Get("tree_fit_sb"));
tree_fit_sb_r0->SetBranchAddress("r",&r);
tree_fit_sb_r0->SetBranchAddress("rErr",&rErr);
tree_fit_sb_r0->SetBranchAddress("rHiErr",&rHiErr);
tree_fit_sb_r0->SetBranchAddress("rLoErr",&rLoErr);
tree_fit_sb_r0->SetBranchAddress("fit_status",&fit_status);

nentries=(Int_t)tree_fit_sb_r0->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	tree_fit_sb_r0->GetEntry(i);

	if(fit_status>-1)
	{

         	if(r > r_true_0) h_bias_r0->Fill((r-r_true_0)/rLoErr);
         	if(r < r_true_0) h_bias_r0->Fill((r-r_true_0)/rHiErr);  
		

	}	      
}// end of event loop



TTree* tree_fit_sb_r2sigma = (TTree*)(f_fitDiagn_r2sigma->Get("tree_fit_sb"));
tree_fit_sb_r2sigma->SetBranchAddress("r",&r);
tree_fit_sb_r2sigma->SetBranchAddress("rErr",&rErr);
tree_fit_sb_r2sigma->SetBranchAddress("rHiErr",&rHiErr);
tree_fit_sb_r2sigma->SetBranchAddress("rLoErr",&rLoErr);
tree_fit_sb_r2sigma->SetBranchAddress("fit_status",&fit_status);

nentries=(Int_t)tree_fit_sb_r2sigma->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	tree_fit_sb_r2sigma->GetEntry(i);

	if(fit_status>-1)
	{

         	if(r > r_true_2sigma) h_bias_r2sigma->Fill((r-r_true_2sigma)/rLoErr);
         	if(r < r_true_2sigma) h_bias_r2sigma->Fill((r-r_true_2sigma)/rHiErr);  
		

	}	      
}// end of event loop


TTree* tree_fit_sb_r5sigma = (TTree*)(f_fitDiagn_r5sigma->Get("tree_fit_sb"));
tree_fit_sb_r5sigma->SetBranchAddress("r",&r);
tree_fit_sb_r5sigma->SetBranchAddress("rErr",&rErr);
tree_fit_sb_r5sigma->SetBranchAddress("rHiErr",&rHiErr);
tree_fit_sb_r5sigma->SetBranchAddress("rLoErr",&rLoErr);
tree_fit_sb_r5sigma->SetBranchAddress("fit_status",&fit_status);

nentries=(Int_t)tree_fit_sb_r5sigma->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	tree_fit_sb_r5sigma->GetEntry(i);

	if(fit_status>-1)
	{

         	if(r > r_true_5sigma) h_bias_r5sigma->Fill((r-r_true_5sigma)/rLoErr);
         	if(r < r_true_5sigma) h_bias_r5sigma->Fill((r-r_true_5sigma)/rHiErr);  
		

	}	      
}// end of event loop




//__________edw______________


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.04);
c->SetTopMargin(0.1);
c->SetBottomMargin(0.12);

double frxmin, frxmax, frymin, frymax;

frxmin = -6; 
frxmax = 12; 
frymin = 0; 
frymax = 600;

auto frame = c->DrawFrame(frxmin,frymin,frxmax,frymax);

frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitleOffset(0.95);
frame->GetXaxis()->SetTitle("(r - r_{true} ) / #sigma_{r}");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(0.97);
frame->GetYaxis()->SetTitle("Toy datasets");


h_bias_r0->SetMarkerStyle(8); 
h_bias_r0->SetLineWidth(0);
h_bias_r0->SetMarkerColor(kRed+1);
h_bias_r0->SetLineColor(kRed+1);
h_bias_r0->SetMarkerSize(0);

h_bias_r2sigma->SetMarkerStyle(8); 
h_bias_r2sigma->SetLineWidth(2);
h_bias_r2sigma->SetMarkerColor(kBlue-3);
h_bias_r2sigma->SetLineColor(kBlue-3);
h_bias_r2sigma->SetMarkerSize(1.2);

h_bias_r5sigma->SetMarkerStyle(8); 
h_bias_r5sigma->SetLineWidth(2);
h_bias_r5sigma->SetMarkerColor(kGreen+2);
h_bias_r5sigma->SetLineColor(kGreen+2);
h_bias_r5sigma->SetMarkerSize(1.2);

h_bias_r0->Draw("PE1 same");
h_bias_r2sigma->Draw("PE1 same");
h_bias_r5sigma->Draw("PE1 same");

double mean_r0, sigma_r0, meanerr_r0, sigmaerr_r0;
double mean_r2sigma, sigma_r2sigma, meanerr_r2sigma, sigmaerr_r2sigma;
double mean_r5sigma, sigma_r5sigma, meanerr_r5sigma, sigmaerr_r5sigma;

TF1* func_r0;
TF1* func_r2sigma;
TF1* func_r5sigma;


func_r0 = new TF1("func_r0", "gaus", -5,5);
func_r0->SetLineColor(kRed+1);

h_bias_r0->Fit("gaus","","", -1, 1);

TF1 *gaus_r0 = h_bias_r0->GetFunction("gaus");
mean_r0 = gaus_r0->GetParameter(1); 
sigma_r0 = gaus_r0->GetParameter(2);
meanerr_r0 = gaus_r0->GetParError(1); 
sigmaerr_r0 = gaus_r0->GetParError(2);

gaus_r0->SetLineColor(kRed+1);
gaus_r0->SetLineWidth(0);
gaus_r0->Draw("same");



func_r2sigma = new TF1("func_r2sigma", "gaus", -5,5);
func_r2sigma->SetLineColor(kBlue-3);

h_bias_r2sigma->Fit("gaus","","", -3, 2.5);

TF1 *gaus_r2sigma = h_bias_r2sigma->GetFunction("gaus");
mean_r2sigma = gaus_r2sigma->GetParameter(1); 
sigma_r2sigma = gaus_r2sigma->GetParameter(2);
meanerr_r2sigma = gaus_r2sigma->GetParError(1); 
sigmaerr_r2sigma = gaus_r2sigma->GetParError(2);

gaus_r2sigma->SetLineColor(kBlue-3);
gaus_r2sigma->Draw("same");



func_r5sigma = new TF1("func_r5sigma", "gaus", -5,5);
func_r5sigma->SetLineColor(kGreen+2);

h_bias_r5sigma->Fit("gaus","","", -3, 2.5);

TF1 *gaus_r5sigma = h_bias_r5sigma->GetFunction("gaus");
mean_r5sigma = gaus_r5sigma->GetParameter(1); 
sigma_r5sigma = gaus_r5sigma->GetParameter(2);
meanerr_r5sigma = gaus_r5sigma->GetParError(1); 
sigmaerr_r5sigma = gaus_r5sigma->GetParError(2);

gaus_r5sigma->SetLineColor(kGreen+2);
gaus_r5sigma->Draw("same");


char legname1_v1[500], legname1_v2[500], legname1_v3[500], legname1_v4[500], legname2_r0[500], legname3_r0[500], legname2_r2sigma[500], legname3_r2sigma[500], legname2_r5sigma[500], legname3_r5sigma[500];

sprintf(legname1_v1,"#bf{M_{S} = %.0f GeV}", Suu);
sprintf(legname1_v2,"#bf{M_{#chi} = %.0f GeV}", Suu*alpha_true);
sprintf(legname1_v3,"#bf{M_{#chi} / M_{S} = %.2f}", alpha_true);
if(width==0.0043) sprintf(legname1_v4,"#bf{#Gamma / M_{S} = %.2f%%}", width*100.);
if(width==0.015) sprintf(legname1_v4,"#bf{#Gamma / M_{S} = %.1f%%}", width*100.);
if(width==0.05) sprintf(legname1_v4,"#bf{#Gamma / M_{S} = %.0f%%}", width*100.);
if(width==0.1) sprintf(legname1_v4,"#bf{#Gamma / M_{S} = %.0f%%}", width*100.);

sprintf(legname2_r0,"#bf{Mean = %.2f #pm %.2f}", mean_r0, meanerr_r0);
sprintf(legname3_r0,"Sigma = %.2f #pm %.2f", sigma_r0, sigmaerr_r0);

sprintf(legname2_r2sigma,"#bf{Mean = %.2f #pm %.2f}", mean_r2sigma, meanerr_r2sigma);
sprintf(legname3_r2sigma,"Sigma = %.2f #pm %.2f", sigma_r2sigma, sigmaerr_r2sigma);

sprintf(legname2_r5sigma,"#bf{Mean = %.2f #pm %.2f}", mean_r5sigma, meanerr_r5sigma);
sprintf(legname3_r5sigma,"Sigma = %.2f #pm %.2f", sigma_r5sigma, sigmaerr_r5sigma);

double xmin = 0.63;
double xmax = 0.88;
double ymin = 0.15;
double ymax = 0.87;

TLegend *leg = new TLegend(xmin,ymin,xmax,ymax); 
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.035);
leg->AddEntry((TObject*)0, legname1_v1, "");
leg->AddEntry((TObject*)0, legname1_v2, "");
leg->AddEntry((TObject*)0, legname1_v3, "");
leg->AddEntry((TObject*)0, legname1_v4, "");
//leg->AddEntry(h_bias_r0, "Injected signal: 0", "PE");
leg->AddEntry(h_bias_r2sigma, "Injected Signal: 2#sigma", "PE");
leg->AddEntry(h_bias_r5sigma, "Injected Signal: 5#sigma", "PE");
leg->AddEntry((TObject*)0, "", "");

/*TLegendEntry *entry1_r0 = leg->AddEntry(func_r0,"Gaussian fit","L");
TLegendEntry *entry2_r0 = leg->AddEntry((TObject*)0, legname2_r0, "");
TLegendEntry *entry3_r0 = leg->AddEntry((TObject*)0, legname3_r0, "");
entry1_r0->SetTextColor(kRed+1);
entry2_r0->SetTextColor(kRed+1);
entry3_r0->SetTextColor(kRed+1);
entry1_r0->SetTextSize(0.03);
entry2_r0->SetTextSize(0.03);
entry3_r0->SetTextSize(0.03);
*/
TLegendEntry *entry1_r2sigma = leg->AddEntry(func_r2sigma,"Gaussian fit","L");
TLegendEntry *entry2_r2sigma = leg->AddEntry((TObject*)0, legname2_r2sigma, "");
TLegendEntry *entry3_r2sigma = leg->AddEntry((TObject*)0, legname3_r2sigma, "");
entry1_r2sigma->SetTextColor(kBlue-3);
entry2_r2sigma->SetTextColor(kBlue-3);
entry3_r2sigma->SetTextColor(kBlue-3);
entry1_r2sigma->SetTextSize(0.03);
entry2_r2sigma->SetTextSize(0.03);
entry3_r2sigma->SetTextSize(0.03);

TLegendEntry *entry1_r5sigma = leg->AddEntry(func_r5sigma,"Gaussian fit","L");
TLegendEntry *entry2_r5sigma = leg->AddEntry((TObject*)0, legname2_r5sigma, "");
TLegendEntry *entry3_r5sigma = leg->AddEntry((TObject*)0, legname3_r5sigma, "");
entry1_r5sigma->SetTextColor(kGreen+2);
entry2_r5sigma->SetTextColor(kGreen+2);
entry3_r5sigma->SetTextColor(kGreen+2);
entry1_r5sigma->SetTextSize(0.03);
entry2_r5sigma->SetTextSize(0.03);
entry3_r5sigma->SetTextSize(0.03);

leg->Draw();


TPaveText *cms = new TPaveText(0.25,0.92,0.40,0.95,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);
cms->Draw();


TPaveText *lumileg = new TPaveText(0.845,0.92,0.945,0.95,"NDC");
lumileg->AddText("13 TeV");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);
lumileg->Draw();


char legname4[500], legname5[500], legname6[500];
sprintf(legname4,"#bf{Generate from %s}", gen_function_name_forleg);
sprintf(legname5,"#bf{Fit with %s}", fit_function_name_forleg);

TPaveText *func_leg = new TPaveText(0.14,0.75,0.34,0.86,"NDC");
func_leg->AddText(legname4);
func_leg->AddText(legname5);
func_leg->SetFillColor(0);
func_leg->SetBorderSize(0);
func_leg->SetTextFont(42);
func_leg->SetTextSize(0.04);
func_leg->SetTextAlign(11);
func_leg->Draw();


char nameplot1[500], nameplot2[500];

sprintf(nameplot1,"output/Wide_Resonances_Run2_Final/plots/highest_signif_mass_points/BiasVsSignalInjection_W-%s_Suu%.0f_alpha%s_Gen%s_Fit%s.png", width_name, Suu, alpha_true_name, gen_function_name, fit_function_name);
sprintf(nameplot2,"output/Wide_Resonances_Run2_Final/plots/highest_signif_mass_points/BiasVsSignalInjection_W-%s_Suu%.0f_alpha%s_Gen%s_Fit%s.pdf", width_name, Suu, alpha_true_name, gen_function_name, fit_function_name);

c->SaveAs(nameplot1); 
c->SaveAs(nameplot2);


}











