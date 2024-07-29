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

void Plot_SignalShapes_JER(double width, double alpha_true, double Suu, int alphabin){

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,  //<--48th bin
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, //<--71st bin
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,  //<-94th bin
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

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

double alpha_low, alpha_high;
char alphabin_name[1024], alphaleg[1024];
if (alphabin==1) {alpha_low = 0.10; alpha_high = 0.12; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.10 < #alpha^{rec} < 0.12}");}
if (alphabin==2) {alpha_low = 0.12; alpha_high = 0.14; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.12 < #alpha^{rec} < 0.14}");}
if (alphabin==3) {alpha_low = 0.14; alpha_high = 0.16; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.14 < #alpha^{rec} < 0.16}");}
if (alphabin==4) {alpha_low = 0.16; alpha_high = 0.18; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.16 < #alpha^{rec} < 0.18}");}
if (alphabin==5) {alpha_low = 0.18; alpha_high = 0.20; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.18 < #alpha^{rec} < 0.20}");}
if (alphabin==6) {alpha_low = 0.20; alpha_high = 0.22; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.20 < #alpha^{rec} < 0.22}");}
if (alphabin==7) {alpha_low = 0.22; alpha_high = 0.24; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.22 < #alpha^{rec} < 0.24}");}
if (alphabin==8) {alpha_low = 0.24; alpha_high = 0.26; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.24 < #alpha^{rec} < 0.26}");}
if (alphabin==9) {alpha_low = 0.26; alpha_high = 0.28; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.26 < #alpha^{rec} < 0.28}");}
if (alphabin==10) {alpha_low = 0.28; alpha_high = 0.30; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.28 < #alpha^{rec} < 0.30}");}
if (alphabin==11) {alpha_low = 0.30; alpha_high = 0.32; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.30 < #alpha^{rec} < 0.32}");}
if (alphabin==12) {alpha_low = 0.32; alpha_high = 0.34; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{0.32 < #alpha^{rec} < 0.34}");}
if (alphabin==13) {alpha_low = 0.34; alpha_high = 100.; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#bf{#alpha^{rec} > 0.34}");}
if (alphabin==0) {alpha_low = 0.10; alpha_high = 100.; sprintf(alphabin_name,"alphagt0p1"); sprintf(alphaleg,"#bf{#alpha^{rec} > 0.10}");}


char fname_nominal[1024], fname_jerup[1024];

if(width!=0.0043)
{
    sprintf(fname_nominal, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-%s_S-%.0f_chi-%.0f_%s.root", alpha_true_name, width_name, Suu, Suu*alpha_true, alphabin_name);
    sprintf(fname_jerup, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_JERup_Suu-Diquark_W-%s_S-%.0f_chi-%.0f_%s.root", alpha_true_name, width_name, Suu, Suu*alpha_true, alphabin_name);
}
else
{
    if(alphabin!=0) sprintf(fname_nominal, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/ResonanceShapes_Suu%.0f_Chi%.0f_SR_%s.root", alpha_true_name, Suu, Suu*alpha_true, alphabin_name);
    if(alphabin==0) sprintf(fname_nominal, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/ResonanceShapes_Suu%.0f_Chi%.0f_SR_noslices.root", alpha_true_name, Suu, Suu*alpha_true);
    
    if(alphabin!=0) sprintf(fname_jerup, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/jer_up/ResonanceShapes_Suu%.0f_Chi%.0f_SR_%s.root", alpha_true_name, Suu, Suu*alpha_true, alphabin_name);
    if(alphabin==0) sprintf(fname_jerup, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/jer_up/ResonanceShapes_Suu%.0f_Chi%.0f_SR_noslices.root", alpha_true_name, Suu, Suu*alpha_true);
    
}


cout << "Files used: " << endl;
cout << "NOMINAL: " << fname_nominal << endl;
cout << "JERup: " << fname_jerup << endl;

TFile *f_nominal = new TFile(fname_nominal, "READ");
TFile *f_jerup = new TFile(fname_jerup, "READ");

TH1D *h_nominal; 
TH1D *h_jerup; 

if(width!=0.0043)
{
    h_nominal = (TH1D*)f_nominal->Get("h_FourjetMass100GeV");
    h_jerup = (TH1D*)f_jerup->Get("h_FourjetMass100GeV");
}
else
{
    //h_nominal = new TH1D("h_nominal","",nMassBins,massBoundaries);
    //h_jerup = new TH1D("h_jerup","",nMassBins,massBoundaries);
    
    h_nominal = new TH1D("h_nominal","",140,0,14000);
    h_jerup = new TH1D("h_jerup","",140,0,14000);
    
    TH1D *h_nominal_1GeV = (TH1D*)f_nominal->Get("h_FourjetMass1GeV");
    TH1D *h_jerup_1GeV = (TH1D*)f_jerup->Get("h_FourjetMass1GeV");
        
    double val, xval;

    for(unsigned int j=1; j<=h_nominal_1GeV->GetNbinsX(); j++)
    {
        val  = h_nominal_1GeV->GetBinContent(j);
	xval = h_nominal_1GeV->GetBinCenter(j);
	h_nominal->Fill(xval,val);		
    }
    
    for(unsigned int j=1; j<=h_jerup_1GeV->GetNbinsX(); j++)
    {
        val  = h_jerup_1GeV->GetBinContent(j);
	xval = h_jerup_1GeV->GetBinCenter(j);
	h_jerup->Fill(xval,val);		
    }
    
}

TPaveText *cms1 = new TPaveText(0.21,0.91,0.46,0.96,"NDC"); 
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.06); 

TPaveText *cms2 = new TPaveText(0.825,0.91,0.975,0.96,"NDC"); 
cms2->AddText("13 TeV");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.06);
cms2->SetTextFont(42);


char legentry[1024], legtitle[1024];

TCanvas *c = new TCanvas("c","",800,700);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.03);
c->SetLogy(0);
c->cd();


h_nominal->SetStats(0);
h_jerup->SetStats(0);

h_nominal->SetLineColor(kBlack);
h_jerup->SetLineColor(kViolet);

h_nominal->SetLineWidth(3);
h_jerup->SetLineWidth(3);

h_nominal->SetMarkerColor(kBlack);
h_jerup->SetMarkerColor(kViolet);

h_nominal->SetMarkerStyle(8);
h_jerup->SetMarkerStyle(8);

h_nominal->SetTitle("");
h_nominal->GetXaxis()->SetRangeUser(1,9999.);
//h_nominal->GetYaxis()->SetRangeUser(0.0001,9.9);
h_nominal->GetYaxis()->SetRangeUser(0.,0.14);
h_nominal->GetXaxis()->SetTitle("Four-jet mass [GeV]");
h_nominal->GetXaxis()->SetTitleSize(0.055);
h_nominal->GetXaxis()->SetTitleOffset(0.82);
h_nominal->GetYaxis()->SetTitle("Probability");
h_nominal->GetYaxis()->SetTitleSize(0.055);
h_nominal->GetYaxis()->SetTitleOffset(0.85);
h_nominal->GetXaxis()->SetNdivisions(512,"kTRUE");
h_nominal->Draw("hist");
h_jerup->Draw("hist same");


cms1->Draw();
cms2->Draw();


Int_t maxBin_nominal = h_nominal->GetMaximumBin();
Double_t peakXValue_nominal = h_nominal->GetBinCenter(maxBin_nominal);
//TF1 *gausFunc_nominal = new TF1("gausFunc_nominal", "gaus", peakXValue_nominal*0.9, peakXValue_nominal*1.12);
TF1 *gausFunc_nominal = new TF1("gausFunc_nominal", "gaus", 7300, 8500);
gausFunc_nominal->SetLineColor(kBlack);
Double_t initialValues_nominal[3] = {1.0, Suu, Suu*0.1};
gausFunc_nominal->SetParameters(initialValues_nominal);    
h_nominal->Fit("gausFunc_nominal", "R");
cout << "Chi2 / NDF = " << gausFunc_nominal->GetChisquare() << " / " << gausFunc_nominal->GetNDF() << " = " << gausFunc_nominal->GetChisquare()/gausFunc_nominal->GetNDF() << endl;
cout << "Prob = " << gausFunc_nominal->GetProb() << endl;


Int_t maxBin_jerup = h_jerup->GetMaximumBin();
Double_t peakXValue_jerup = h_jerup->GetBinCenter(maxBin_jerup);
//TF1 *gausFunc_jerup = new TF1("gausFunc_jerup", "gaus", peakXValue_jerup*0.9, peakXValue_jerup*1.12);
TF1 *gausFunc_jerup = new TF1("gausFunc_jerup", "gaus", 7400, 8300);
gausFunc_jerup->SetLineColor(kViolet);
Double_t initialValues_jerup[3] = {1.0, Suu, Suu*0.1};
gausFunc_jerup->SetParameters(initialValues_jerup);    
h_jerup->Fit("gausFunc_jerup", "R");
cout << "Chi2 / NDF = " << gausFunc_jerup->GetChisquare() << " / " << gausFunc_jerup->GetNDF() << " = " << gausFunc_jerup->GetChisquare()/gausFunc_jerup->GetNDF() << endl;
cout << "Prob = " << gausFunc_jerup->GetProb() << endl;


gausFunc_nominal->Draw("same");
gausFunc_jerup->Draw("same");


char text_metric_nominal_1[1024], text_metric_nominal_2[1024], text_metric_nominal_3[1024], text_metric_jerup_1[1024], text_metric_jerup_2[1024], text_metric_jerup_3[1024];

sprintf(text_metric_nominal_1,"Hist Mean = (%.0f #pm %.0f) GeV", h_nominal->GetMean(), h_nominal->GetMeanError());
sprintf(text_metric_nominal_2,"Peak = (%.0f #pm %.0f) GeV", gausFunc_nominal->GetParameter(1), gausFunc_nominal->GetParError(1));
sprintf(text_metric_nominal_3,"Sigma = (%.0f #pm %.0f) GeV", gausFunc_nominal->GetParameter(2), gausFunc_nominal->GetParError(2));
//sprintf(text_metric_nominal_3,"Sigma = (%.0f #pm %.0f) GeV", h_nominal->GetRMS(), h_nominal->GetRMSError());
    
sprintf(text_metric_jerup_1,"Hist Mean = (%.0f #pm %.0f) GeV", h_jerup->GetMean(), h_jerup->GetMeanError());
sprintf(text_metric_jerup_2,"Peak = (%.0f #pm %.0f) GeV", gausFunc_jerup->GetParameter(1), gausFunc_jerup->GetParError(1)); 
sprintf(text_metric_jerup_3,"Sigma = (%.0f #pm %.0f) GeV", gausFunc_jerup->GetParameter(2), gausFunc_jerup->GetParError(2)); 
//sprintf(text_metric_jerup_3,"Sigma = (%.0f #pm %.0f) GeV", h_jerup->GetRMS(), h_jerup->GetRMSError());

char legname1[1024], legname2[1024], legname3[1024];
sprintf(legname1,"#bf{M_{S} = %.0f GeV}", Suu);
sprintf(legname2,"#bf{#alpha_{true} = %.2f}", alpha_true);
if(width==0.0043) sprintf(legname3,"#bf{#Gamma / M_{S} = %.2f %%}", width*100.);
if(width==0.015) sprintf(legname3,"#bf{#Gamma / M_{S} = %.1f %%}", width*100.);
if(width!=0.0043 && width!=0.015) sprintf(legname3,"#bf{#Gamma / M_{S} = %.0f %%}", width*100.);


TLegend *l = new TLegend(0.15,0.57,0.35,0.87,"");
l->SetBorderSize(0);
l->SetTextSize(0.035);
l->SetTextFont(42);
l->AddEntry((TObject*)0, legname1,"");
l->AddEntry((TObject*)0, legname2,"");
l->AddEntry((TObject*)0, legname3,"");
l->AddEntry((TObject*)0, alphaleg,"");
l->AddEntry(h_nominal,"Nominal","L");
l->AddEntry(h_jerup, "JER up","L");
l->Draw();

TLegend *leg_nominal = new TLegend(0.48, 0.75, 0.89, 0.87,"");
leg_nominal->SetBorderSize(0);
leg_nominal->SetTextSize(0.035);
leg_nominal->SetTextColor(kBlack);
leg_nominal->AddEntry((TObject*)0,text_metric_nominal_1,"");
//leg_nominal->AddEntry((TObject*)0,text_metric_nominal_2,""); 
leg_nominal->AddEntry((TObject*)0,text_metric_nominal_3,"");
leg_nominal->Draw(); 

TLegend *leg_jesup = new TLegend(0.48, 0.62, 0.89, 0.74,"");
leg_jesup->SetBorderSize(0);
leg_jesup->SetTextSize(0.035);
leg_jesup->SetTextColor(kViolet);
leg_jesup->AddEntry((TObject*)0,text_metric_jerup_1,"");
//leg_jesup->AddEntry((TObject*)0,text_metric_jerup_2,""); 
leg_jesup->AddEntry((TObject*)0,text_metric_jerup_3,"");
leg_jesup->Draw();


char cname1[1024], cname2[1024];
sprintf(cname1,"plots/SignalShapes_JER/SignalShapes_100GeVBinning_Nominal_vs_JERup_W-%s_Suu%.0f_alpha%s_%s.png", width_name, Suu, alpha_true_name, alphabin_name);
sprintf(cname2,"plots/SignalShapes_JER/SignalShapes_100GeVBinning_Nominal_vs_JERup_W-%s_Suu%.0f_alpha%s_%s.pdf", width_name, Suu, alpha_true_name, alphabin_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


