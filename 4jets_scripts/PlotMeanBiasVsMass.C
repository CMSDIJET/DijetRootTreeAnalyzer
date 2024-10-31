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
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TH1.h"

void PlotMeanBiasVsMass(double alpha_true, int function, int signal){

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

char function_name[1024];
if (function==0) sprintf(function_name,"Dijet");
if (function==1) sprintf(function_name,"Atlas");
if (function==2) sprintf(function_name,"ModDijet");

char function_name_forleg[1024];
if (function==0) sprintf(function_name_forleg,"Dijet-3p");
if (function==1) sprintf(function_name_forleg,"PowExp-3p");
if (function==2) sprintf(function_name_forleg,"ModDijet-3p");

char signal_name[1024];
if (signal==0) sprintf(signal_name,"InjSignal0");
if (signal==2) sprintf(signal_name,"InjSignal2sigma");
if (signal==5) sprintf(signal_name,"InjSignal5sigma");

const int n = 11;

char input_txt_name_W0p0043[1024], input_txt_name_W0p015[1024], input_txt_name_W0p05[1024], input_txt_name_W0p1[1024];
sprintf(input_txt_name_W0p0043, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/bias_studies/MeanBiasWithError_alpha%s_Gen%s_%s_W-0p0043.txt", alpha_true_name, alpha_true_name, function_name, signal_name);
sprintf(input_txt_name_W0p015, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/bias_studies/MeanBiasWithError_alpha%s_Gen%s_%s_W-0p015.txt", alpha_true_name, alpha_true_name, function_name, signal_name);
sprintf(input_txt_name_W0p05, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/bias_studies/MeanBiasWithError_alpha%s_Gen%s_%s_W-0p05.txt", alpha_true_name, alpha_true_name, function_name, signal_name);
sprintf(input_txt_name_W0p1, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha%s/bias_studies/MeanBiasWithError_alpha%s_Gen%s_%s_W-0p1.txt", alpha_true_name, alpha_true_name, function_name, signal_name);

std::ifstream infile_W0p0043(input_txt_name_W0p0043);
std::ifstream infile_W0p015(input_txt_name_W0p015);
std::ifstream infile_W0p05(input_txt_name_W0p05);
std::ifstream infile_W0p1(input_txt_name_W0p1);

double mass_W0p0043[n], mean_bias_W0p0043[n], mean_bias_err_W0p0043[n];
double mass_W0p015[n], mean_bias_W0p015[n], mean_bias_err_W0p015[n];
double mass_W0p05[n], mean_bias_W0p05[n], mean_bias_err_W0p05[n];
double mass_W0p1[n], mean_bias_W0p1[n], mean_bias_err_W0p1[n];

for (int i=0; i<n; i++)
{
        infile_W0p0043 >> mass_W0p0043[i] >> mean_bias_W0p0043[i] >> mean_bias_err_W0p0043[i];
        infile_W0p015 >> mass_W0p015[i] >> mean_bias_W0p015[i] >> mean_bias_err_W0p015[i];
        infile_W0p05 >> mass_W0p05[i] >> mean_bias_W0p05[i] >> mean_bias_err_W0p05[i];
        infile_W0p1 >> mass_W0p1[i] >> mean_bias_W0p1[i] >> mean_bias_err_W0p1[i];
}

infile_W0p0043.close();
infile_W0p015.close();
infile_W0p05.close();
infile_W0p1.close();

TGraphErrors *g_W0p0043 = new TGraphErrors(n, mass_W0p0043, mean_bias_W0p0043, nullptr, mean_bias_err_W0p0043);
TGraphErrors *g_W0p015 = new TGraphErrors(n, mass_W0p015, mean_bias_W0p015, nullptr, mean_bias_err_W0p015);
TGraphErrors *g_W0p05 = new TGraphErrors(n, mass_W0p05, mean_bias_W0p05, nullptr, mean_bias_err_W0p05);
TGraphErrors *g_W0p1 = new TGraphErrors(n, mass_W0p1, mean_bias_W0p1, nullptr, mean_bias_err_W0p1);


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
//c->SetLogy(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetGridy(0);
c->SetRightMargin(0.03);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.14);
c->SetBottomMargin(0.12);

double xmin = 1.5;
double xmax = 10.5;

auto frame = c->DrawFrame(xmin,-0.79,xmax,0.79);
frame->GetXaxis()->SetTitleSize(0.065);
frame->GetXaxis()->SetTitleOffset(0.8);
frame->GetXaxis()->SetTitle("Diquark mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.055);
frame->GetYaxis()->SetTitleOffset(1.21);
frame->GetYaxis()->SetTitle("#LTBias#GT");
frame->GetYaxis()->SetLabelSize(0.045);
frame->GetYaxis()->SetLabelOffset(0.012);
frame->GetXaxis()->SetLabelSize(0.045);

g_W0p0043->SetLineColor(kBlack);
g_W0p0043->SetLineWidth(2);  
g_W0p0043->SetMarkerColor(kBlack);
//g_W0p0043->SetMarkerStyle(kFullCross);
g_W0p0043->SetMarkerStyle(21);
g_W0p0043->SetMarkerSize(1.5);

g_W0p015->SetLineColor(kRed+1);
g_W0p015->SetLineWidth(2);  
g_W0p015->SetMarkerColor(kRed+1);
//g_W0p015->SetMarkerStyle(kFullCross);
g_W0p015->SetMarkerStyle(20);
g_W0p015->SetMarkerSize(1.5);

g_W0p05->SetLineColor(kBlue-3);
g_W0p05->SetLineWidth(2);  
g_W0p05->SetMarkerColor(kBlue-3);
//g_W0p05->SetMarkerStyle(kFullCross);
g_W0p05->SetMarkerStyle(22);
g_W0p05->SetMarkerSize(1.5);

g_W0p1->SetLineColor(kGreen+2);
g_W0p1->SetLineWidth(2);  
g_W0p1->SetMarkerColor(kGreen+2);
//g_W0p1->SetMarkerStyle(kFullCross);
g_W0p1->SetMarkerStyle(23);
g_W0p1->SetMarkerSize(1.5);

g_W0p0043->Draw("p same");
g_W0p015->Draw("p same");
g_W0p05->Draw("p same");
g_W0p1->Draw("p same");



TPaveText *cms = new TPaveText(0.29,0.925,0.44,0.955,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);
cms->Draw();

TPaveText *cms2 = new TPaveText(0.855,0.925,0.955,0.955,"NDC"); 
cms2->AddText("13 TeV");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.05);
cms2->SetTextFont(42);
cms2->Draw();

TLine *line1 = new TLine(1.5, 0, 10.5, 0);
line1->SetLineWidth(3);
line1->SetLineStyle(2);
line1->Draw("same");

TLine *line2 = new TLine(1.5, -0.5, 10.5, -0.5);
line2->SetLineWidth(3);
line2->SetLineStyle(9);
line2->Draw("same");

TLine *line3 = new TLine(1.5, 0.5, 10.5, 0.5);
line3->SetLineWidth(3);
line3->SetLineStyle(9);
line3->Draw("same");

char alpha_leg[1024];
sprintf(alpha_leg, "M_{#chi} / M_{S} = %.2f", alpha_true);

TLegend *leg = new TLegend(0.18,0.15,0.53,0.4);
leg->SetFillColor(0);
leg->SetBorderSize(1);
leg->SetTextSize(0.034);
leg->AddEntry((TObject*)0, "S #rightarrow #chi#chi #rightarrow (ug)(ug)", "");
leg->AddEntry((TObject*)0, alpha_leg, "");
leg->AddEntry(g_W0p0043, "#Gamma / M_{S} = 0.43 %", "P");
leg->AddEntry(g_W0p015, "#Gamma / M_{S} = 1.5 %", "P");
leg->AddEntry(g_W0p05, "#Gamma / M_{S} = 5 %", "P");
leg->AddEntry(g_W0p1, "#Gamma / M_{S} = 10 %", "P");
leg->Draw();


char legname1[500], legname2[500], legname3[500];
sprintf(legname1,"Generate with %s", function_name_forleg);
sprintf(legname2,"Fit with Envelope");
if(signal==0) sprintf(legname3,"Injected Signal: 0");
if(signal==2) sprintf(legname3,"Injected Signal: 2#sigma");
if(signal==5) sprintf(legname3,"Injected Signal: 5#sigma");

TPaveText *signal_leg = new TPaveText(0.52,0.70,0.93,0.86,"NDC");
signal_leg->AddText(legname1);
signal_leg->AddText(legname2);
signal_leg->AddText(legname3);
signal_leg->SetFillColor(0);
signal_leg->SetBorderSize(1);
signal_leg->SetTextFont(42);
signal_leg->SetTextSize(0.04);
//signal_leg->SetTextAlign(11);
signal_leg->Draw();


char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/bias_studies/MeanBiasVsWidth_alpha%s_Gen%s_%s_FitEnvelope.png", alpha_true_name, function_name, signal_name);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/bias_studies/MeanBiasVsWidth_alpha%s_Gen%s_%s_FitEnvelope.pdf", alpha_true_name, function_name, signal_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


