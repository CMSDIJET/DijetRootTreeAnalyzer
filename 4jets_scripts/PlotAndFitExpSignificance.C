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


void PlotAndFitExpSignificance(double alpha_true, double Suu, double width){

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

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");


char fname[1024];
sprintf(fname, "output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/diquark_cross_section/higgsCombine_W-%s_%.0f_%.0f.Significance.mH120.root", width_name, Suu, Suu*alpha_true);

TFile *f = new TFile(fname, "READ");

TTree *t = (TTree*)f->Get("limit");

double signif;

TH1D *h_signif = new TH1D("h_signif","",200,0,10);

t->SetBranchAddress("limit",&signif);

int nentries=(Int_t)t->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{
	t->GetEntry(i);

	h_signif->Fill(signif);	      
}


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.04);
c->SetTopMargin(0.1);
c->SetBottomMargin(0.12);
c->SetLogy(1);

h_signif->GetXaxis()->SetTitleSize(0.05);
h_signif->GetXaxis()->SetTitleOffset(0.95);
h_signif->GetXaxis()->SetTitle("Expected significance");
h_signif->GetXaxis()->SetRangeUser(0,7.9);
h_signif->GetYaxis()->SetTitleSize(0.05);
h_signif->GetYaxis()->SetTitleOffset(0.97);
h_signif->GetYaxis()->SetTitle("Toy datasets");
h_signif->GetYaxis()->SetRangeUser(0.5,99999);

h_signif->SetLineWidth(3);
h_signif->SetStats(1);

h_signif->Draw("hist");

TF1 *func;
func = new TF1("func", "gaus", 0.5,6);
func->SetLineColor(kRed);
h_signif->Fit("gaus","","", 0.5, 6);

TF1 *gaus = h_signif->GetFunction("gaus");
gaus->SetLineColor(kRed);
gaus->Draw("same");

char legname1[500], legname2[500], legname3[500];
sprintf(legname1,"M_{#chi} / M_{S} = %.2f", alpha_true);
sprintf(legname2,"M_{S} = %.0f GeV", Suu);
if(width==0.0043)
{
    sprintf(legname3, "#Gamma / M_{S} = %.2f %%",width*100.);
}
else if(width==0.015)
{
    sprintf(legname3, "#Gamma / M_{S} = %.1f %%",width*100.);
}
else
{
    sprintf(legname3, "#Gamma / M_{S} = %.0f %%",width*100.);
}

TPaveText *signal_leg = new TPaveText(0.22,0.70,0.42,0.86,"NDC");
signal_leg->AddText(legname1);
signal_leg->AddText(legname2);
signal_leg->AddText(legname3);
signal_leg->SetFillColor(0);
signal_leg->SetBorderSize(0);
signal_leg->SetTextFont(42);
signal_leg->SetTextSize(0.04);
signal_leg->SetTextAlign(11);
signal_leg->Draw();

gPad->Update();
gStyle->SetOptFit(1111);

gPad->Update(); // Ensure everything is drawn before modifying

TPaveStats *stats = (TPaveStats*)h_signif->GetListOfFunctions()->FindObject("stats");
if (stats) {
    // Resize the stats box
    stats->SetX1NDC(0.5);  // Make the box wider
    stats->SetX2NDC(0.98);   // Right boundary of the box
    stats->SetY1NDC(0.65);  // Adjust the height as well to avoid crowding 
    stats->SetY2NDC(0.95);

    // Increase the text size in the stats box
    stats->SetTextSize(0.03);  // Adjust the size of the text

    // Optionally, change the font (default is 42; you can try different values)
    stats->SetTextFont(42);    // Set the font of the text
}

c->Modified(); // Apply the changes to the canvas
c->Update();   // Redraw the canvas to reflect the changes

char cname1[1024], cname2[1024];
sprintf(cname1, "output/Wide_Resonances_Run2_Final/plots/diquark_cross_section/ExpSignifDistr_alpha%s_Suu%.0f_W-%s_logy.png", alpha_true_name, Suu, width_name);
sprintf(cname2, "output/Wide_Resonances_Run2_Final/plots/diquark_cross_section/ExpSignifDistr_alpha%s_Suu%.0f_W-%s_logy.pdf", alpha_true_name, Suu, width_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}
