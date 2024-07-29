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

void Plot_SignalShapes_vsWidth(double alpha_true, double Suu, int alphabin){

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

char alphabin_name[1024], alphaleg[1024];
if (alphabin==1) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.10 < #alpha < 0.12");}
if (alphabin==2) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.12 < #alpha < 0.14");}
if (alphabin==3) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.14 < #alpha < 0.16");}
if (alphabin==4) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.16 < #alpha < 0.18");}
if (alphabin==5) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.18 < #alpha < 0.20");}
if (alphabin==6) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.20 < #alpha < 0.22");}
if (alphabin==7) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.22 < #alpha < 0.24");}
if (alphabin==8) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.24 < #alpha < 0.26");}
if (alphabin==9) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.26 < #alpha < 0.28");}
if (alphabin==10) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.28 < #alpha < 0.30");}
if (alphabin==11) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.30 < #alpha < 0.32");}
if (alphabin==12) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.32 < #alpha < 0.34");}
if (alphabin==13) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#alpha > 0.34");}
if (alphabin==0) {sprintf(alphabin_name,"alphagt0p1"); sprintf(alphaleg,"#alpha > 0.10");}


char fname1[1024], fname2[1024], fname3[1024], fname4[1024];

if(Suu!=10000 && Suu!=11000)
{
	if(alphabin==0)
	{
		sprintf(fname1, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/ResonanceShapes_Suu%.0f_Chi%.0f_SR_noslices.root", alpha_true_name, Suu, Suu*alpha_true);
	}
	else
	{
		sprintf(fname1, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/ResonanceShapes_Suu%.0f_Chi%.0f_SR_%s.root", alpha_true_name, Suu, Suu*alpha_true, alphabin_name);
	}
}
else
{
	sprintf(fname1, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/ResonanceShapes_Summer20UL18_Suu-Diquark_S-%.0f_chi-%.0f_%s.root", alpha_true_name, Suu, Suu*alpha_true, alphabin_name);
}

sprintf(fname2, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p015_S-%.0f_chi-%.0f_%s.root", alpha_true_name, Suu, Suu*alpha_true, alphabin_name);
sprintf(fname3, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p05_S-%.0f_chi-%.0f_%s.root", alpha_true_name, Suu, Suu*alpha_true, alphabin_name);
sprintf(fname4, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p1_S-%.0f_chi-%.0f_%s.root", alpha_true_name, Suu, Suu*alpha_true, alphabin_name);


TFile *f1 = new TFile(fname1,"read");
TFile *f2 = new TFile(fname2,"read");
TFile *f3 = new TFile(fname3,"read");
TFile *f4 = new TFile(fname4,"read");

cout << "File 1: " << fname1 << endl;
cout << "File 2: " << fname2 << endl;
cout << "File 3: " << fname3 << endl;
cout << "File 4: " << fname4 << endl;


const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,  //<--48th bin
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, //<--71st bin
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,  //<-94th bin
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

TH1D *h1;

if(Suu!=10000 && Suu!=11000)
{
	TH1D *h1_1GeV = (TH1D*)f1->Get("h_FourjetMass1GeV");

	h1 = new TH1D("h1","",nMassBins,massBoundaries);

	double val, xval;

	for(unsigned int i=1; i<=h1_1GeV->GetNbinsX(); i++)
	{
	 	val  = h1_1GeV->GetBinContent(i);
	 	xval = h1_1GeV->GetBinCenter(i);
	 	h1->Fill(xval,val);		
	}
}
else
{
	h1 = (TH1D*)f1->Get("h_FourjetMass");
}

TH1D *h2 = (TH1D*)f2->Get("h_FourjetMass");
TH1D *h3 = (TH1D*)f3->Get("h_FourjetMass");
TH1D *h4 = (TH1D*)f4->Get("h_FourjetMass");



TCanvas *c = new TCanvas("c","",800,700);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.03);
c->SetLogy(1);
c->cd();


h1->SetStats(0);

h1->SetLineWidth(3);
h2->SetLineWidth(3);
h3->SetLineWidth(3);
h4->SetLineWidth(3);

h1->SetLineColor(kBlack);
h2->SetLineColor(kRed+1);
h3->SetLineColor(kBlue-3);
h4->SetLineColor(kGreen+2);

h1->Scale(1./h1->Integral());
h2->Scale(1./h2->Integral());
h3->Scale(1./h3->Integral());
h4->Scale(1./h4->Integral());
	
h1->GetXaxis()->SetRangeUser(Suu*0.,4686);
h1->GetYaxis()->SetRangeUser(0.00005,5.);
h1->GetXaxis()->SetTitle("Four-jet mass [GeV]");
h1->GetXaxis()->SetTitleSize(0.055);
h1->GetXaxis()->SetTitleOffset(0.82);
h1->GetYaxis()->SetTitle("Normalized entries to unity");
h1->GetYaxis()->SetTitleSize(0.055);
h1->GetYaxis()->SetTitleOffset(0.85);
h1->GetXaxis()->SetNdivisions(512,"kTRUE");

h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");
h4->Draw("hist same");



TPaveText *cms1 = new TPaveText(0.18,0.91,0.43,0.96,"NDC"); 
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.055);
cms1->Draw();

TPaveText *cms2 = new TPaveText(0.825,0.91,0.975,0.96,"NDC"); 
cms2->AddText("13 TeV");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.055);
cms2->SetTextFont(42);
cms2->Draw();

char legname1[1024], legname2[1024];

sprintf(legname1,"M_{S} = %.0f GeV, M_{#chi} = %.0f GeV", Suu, Suu*alpha_true);
sprintf(legname2,"#alpha_{true} = %.2f", alpha_true);

TLegend *leg = new TLegend(0.13,0.5,0.33,0.87); 
//TLegend *leg = new TLegend(0.53,0.5,0.73,0.87);
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.035);
leg->AddEntry((TObject*)0, legname1, "");
leg->AddEntry((TObject*)0, legname2, "");
leg->AddEntry(h1, "#Gamma / M_{S} = 0.43 %", "L");
leg->AddEntry(h2, "#Gamma / M_{S} = 1.5 %", "L");
leg->AddEntry(h3, "#Gamma / M_{S} = 5 %", "L");
leg->AddEntry(h4, "#Gamma / M_{S} = 10 %", "L");
leg->AddEntry((TObject*)0, alphaleg, "");
leg->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/signal_shapes/SignalShapes_alpha%s_Suu%.0f_vsWidth_%s.png",alpha_true_name,Suu,alphabin_name);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/signal_shapes/SignalShapes_alpha%s_Suu%.0f_vsWidth_%s.pdf",alpha_true_name,Suu,alphabin_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


