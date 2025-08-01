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

void Plot_and_debug_diquark_cross_section(){

double mass[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

//W-0p1, alpha0p11
double sigmaB[9] = {41.33, 7.408, 1.605, 0.374, 0.09557, 0.0283, 0.009989, 0.004352, 0.002099}; 
double A[9] = {0.173657, 0.22244, 0.247192, 0.26198, 0.25668, 0.23442, 0.20824, 0.18054, 0.1619};
double e[9] = {0.861622, 0.82148, 0.759194, 0.691694, 0.540206, 0.398985, 0.270889, 0.230586, 0.220939};

//W-0p1, alpha0p33
//double sigmaB[9] = {42.89, 7.404, 1.482, 0.2988, 0.05865, 0.01089, 0.0019, 0.0003217, 5.335e-05}; 
//double A[9] = {0.118747, 0.12003, 0.11617, 0.11313, 0.10753, 0.10199, 0.09425, 0.08882, 0.08603};
//double e[9] = {0.800102, 0.774223, 0.804597, 0.74737, 0.735888, 0.665555, 0.583448, 0.561135, 0.520516};

double sigmaBA[9], sigmaBAe[9];

for(int i=0; i<9; i++)
{
    sigmaBA[i] = sigmaB[i]*A[i];
    sigmaBAe[i] = sigmaB[i]*A[i]*e[i];    
}

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetLogy(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetGridy(0);
c->SetRightMargin(0.03);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.14);
c->SetBottomMargin(0.12);

auto frame = c->DrawFrame(2,1.01e-06,10,0.2e+00);
frame->GetXaxis()->SetTitleSize(0.07);
frame->GetXaxis()->SetTitleOffset(0.8);
frame->GetXaxis()->SetTitle("Four-jet resonance mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.15);
frame->GetYaxis()->SetTitle("Cross section [pb]");
frame->GetXaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelSize(0.045);
frame->GetYaxis()->SetLabelOffset(0.012);


TGraph *gr_sigmaB = new TGraph(9, mass, sigmaB);
TGraph *gr_sigmaBA = new TGraph(9, mass, sigmaBA);
TGraph *gr_sigmaBAe = new TGraph(9, mass, sigmaBAe);


gr_sigmaB->SetLineColor(kBlack);
gr_sigmaBA->SetLineColor(kRed+1);
gr_sigmaBAe->SetLineColor(kBlue-3);
gr_sigmaB->SetLineWidth(3);
gr_sigmaBA->SetLineWidth(3);
gr_sigmaBAe->SetLineWidth(3);


gr_sigmaB->SetMarkerStyle(20);
gr_sigmaBA->SetMarkerStyle(20);
gr_sigmaBAe->SetMarkerStyle(20);

gr_sigmaB->Draw("c same");
gr_sigmaBA->Draw("c same");
gr_sigmaBAe->Draw("c same");




TPaveText *cms1 = new TPaveText(0.196,0.925,0.496,0.955,"NDC"); 
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.055);
cms1->Draw();

TPaveText *cms2 = new TPaveText(0.84,0.925,0.95,0.955,"NDC"); 
cms2->AddText("(13 TeV)");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.05);
cms2->SetTextFont(42);
cms2->Draw();


//TPaveText *pave = new TPaveText(0.52, 0.70, 0.84, 0.86,"NDC");
TPaveText *pave = new TPaveText(0.40, 0.16, 0.45, 0.32,"NDC");
pave->SetTextAlign(11);
pave->AddText("uu #rightarrow S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)" );
pave->AddText("#bf{#alpha_{true} = M_{#chi} / M_{S} = 0.11}");
pave->AddText("#bf{#Gamma / M_{S} = 10%}");
pave->SetFillColor(0);
pave->SetBorderSize(0);
pave->SetTextSize(0.04);
pave->SetTextFont(42);
pave->Draw();


TLegend *leg = new TLegend(0.17,0.18,0.32,0.35);
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.035);
leg->AddEntry(gr_sigmaB, "#sigma#it{#Beta}", "L");
leg->AddEntry(gr_sigmaBA, "#sigma#it{#Beta}#it{A}", "L");
leg->AddEntry(gr_sigmaBAe, "#sigma#it{#Beta}#it{A}#varepsilon", "L");
leg->Draw();


c->SaveAs("plots/CrossSection_alpha0p11_W-0p1.png");
c->SaveAs("plots/CrossSection_alpha0p11_W-0p1.pdf");

}



