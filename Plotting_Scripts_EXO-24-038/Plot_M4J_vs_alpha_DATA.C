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
#include "TEllipse.h"

void Plot_M4J_vs_alpha_DATA(){

TPaveText *paveCMS = new TPaveText(0.17,0.79,0.27,0.87,"NDC");
paveCMS->AddText("#bf{CMS}");
paveCMS->SetTextFont(42); 
paveCMS->SetFillColor(0);
paveCMS->SetBorderSize(0);
paveCMS->SetTextSize(0.08); 

TPaveText *paveCMS2 = new TPaveText(0.627,0.93,0.757,0.96,"NDC");
paveCMS2->SetTextFont(42);
paveCMS2->AddText("138 fb^{-1} (13 TeV)");
paveCMS2->SetFillColor(0);
paveCMS2->SetBorderSize(0);
paveCMS2->SetTextSize(0.05);


char f_name[1024], f_name_contour_1[1024], f_name_contour_2[1024], f_name_contour_3[1024], f_name_contour_4[1024];
sprintf(f_name, "files/HISTOS_2016_2017_2018.root");
sprintf(f_name_contour_1, "files/contour68_M4JvsAlpha_Suu-Diquark_W-0p0043_S-8400_chi-2100.root");
sprintf(f_name_contour_2, "files/contour68_M4JvsAlpha_Suu-Diquark_W-0p015_S-8400_chi-2100.root");
sprintf(f_name_contour_3, "files/contour68_M4JvsAlpha_Suu-Diquark_W-0p05_S-8400_chi-2100.root");
sprintf(f_name_contour_4, "files/contour68_M4JvsAlpha_Suu-Diquark_W-0p1_S-8400_chi-2100.root");

TFile *f = new TFile(f_name,"READ");
TFile *f_contour1 = new TFile(f_name_contour_1,"READ");
TFile *f_contour2 = new TFile(f_name_contour_2,"READ");
TFile *f_contour3 = new TFile(f_name_contour_3,"READ");
TFile *f_contour4 = new TFile(f_name_contour_4,"READ");

TH2D *h_M4J_vs_alpha = (TH2D*)(f->Get("h_alpha_vs_M2J"));
TH2D *h_M4J_vs_alpha_contour1 = (TH2D*)(f_contour1->Get("h_M4J_vs_alpha"));
TH2D *h_M4J_vs_alpha_contour2 = (TH2D*)(f_contour2->Get("h_M4J_vs_alpha"));
TH2D *h_M4J_vs_alpha_contour3 = (TH2D*)(f_contour3->Get("h_M4J_vs_alpha"));
TH2D *h_M4J_vs_alpha_contour4 = (TH2D*)(f_contour4->Get("h_M4J_vs_alpha"));

h_M4J_vs_alpha_contour1->SetStats(0);
h_M4J_vs_alpha_contour2->SetStats(0);
h_M4J_vs_alpha_contour3->SetStats(0);
h_M4J_vs_alpha_contour4->SetStats(0);

gStyle->SetPalette(53);

TCanvas *c = new TCanvas("c","",800,650);
c->cd();
c->SetLogz(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.18);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.12);
c->SetBottomMargin(0.12);

double xmin=1.5;
double xmax=10.4; 
double ymin=0.08;
double ymax=0.62;

auto frame = c->DrawFrame(xmin,ymin,xmax,ymax);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.9);
frame->GetXaxis()->SetTitle("Four-jet mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(1.17);
frame->GetYaxis()->SetTitle("#alpha = Average dijet mass / Four-jet mass");
frame->GetYaxis()->SetLabelSize(0.047);
frame->GetYaxis()->SetLabelOffset(0.011);
frame->GetXaxis()->SetLabelSize(0.05); 

h_M4J_vs_alpha->SetZTitle("Events/bin");
h_M4J_vs_alpha->GetZaxis()->SetTitleSize(0.065);   
h_M4J_vs_alpha->GetZaxis()->SetRangeUser(0.1,10000);
h_M4J_vs_alpha->GetZaxis()->SetTitleOffset(1.);
h_M4J_vs_alpha->GetZaxis()->SetLabelSize(0.05);

h_M4J_vs_alpha->Draw("colz same");


TPaveText *paveWhiteBox = new TPaveText(0.88, 0.08, 0.96, 0.17, "NDC");
paveWhiteBox->SetTextFont(42);
paveWhiteBox->SetFillColor(0);  
paveWhiteBox->SetBorderSize(0); 
paveWhiteBox->SetTextSize(0.1); 
paveWhiteBox->AddText(""); 
paveWhiteBox->Draw(); 



h_M4J_vs_alpha_contour1->SetLineColor(kViolet);
h_M4J_vs_alpha_contour1->SetLineWidth(2);
h_M4J_vs_alpha_contour1->SetLineStyle(1);

h_M4J_vs_alpha_contour2->SetLineColor(kRed-3);
h_M4J_vs_alpha_contour2->SetLineWidth(2);
h_M4J_vs_alpha_contour2->SetLineStyle(1);

h_M4J_vs_alpha_contour3->SetLineColor(kBlue-3);
h_M4J_vs_alpha_contour3->SetLineWidth(2);
h_M4J_vs_alpha_contour3->SetLineStyle(1);

h_M4J_vs_alpha_contour4->SetLineColor(kGreen+2);
h_M4J_vs_alpha_contour4->SetLineWidth(2);
h_M4J_vs_alpha_contour4->SetLineStyle(1);



TLine *l1 = new TLine(xmin,0.10,xmax,0.10);
l1->SetLineWidth(2);
l1->SetLineColor(1);
l1->SetLineStyle(2);
l1->Draw("same");

TLine *l2 = new TLine(xmin,0.12,xmax,0.12);
l2->SetLineWidth(2);
l2->SetLineColor(1);
l2->SetLineStyle(2);
l2->Draw("same");

TLine *l3 = new TLine(xmin,0.14,xmax,0.14);
l3->SetLineWidth(2);
l3->SetLineColor(1);
l3->SetLineStyle(2);
l3->Draw("same");

TLine *l4 = new TLine(xmin,0.16,xmax,0.16);
l4->SetLineWidth(2);
l4->SetLineColor(1);
l4->SetLineStyle(2);
l4->Draw("same");

TLine *l5 = new TLine(xmin,0.18,xmax,0.18);
l5->SetLineWidth(2);
l5->SetLineColor(1);
l5->SetLineStyle(2);
l5->Draw("same");

TLine *l6 = new TLine(xmin,0.2,xmax,0.2);
l6->SetLineWidth(2);
l6->SetLineColor(1);
l6->SetLineStyle(2);
l6->Draw("same");

TLine *l7 = new TLine(xmin,0.22,xmax,0.22);
l7->SetLineWidth(2);
l7->SetLineColor(1);
l7->SetLineStyle(2);
l7->Draw("same");

TLine *l8 = new TLine(xmin,0.24,xmax,0.24);
l8->SetLineWidth(2);
l8->SetLineColor(1);
l8->SetLineStyle(2);
l8->Draw("same");

TLine *l9 = new TLine(xmin,0.26,xmax,0.26);
l9->SetLineWidth(2);
l9->SetLineColor(1);
l9->SetLineStyle(2);
l9->Draw("same");

TLine *l10 = new TLine(xmin,0.28,xmax,0.28);
l10->SetLineWidth(2);
l10->SetLineColor(1);
l10->SetLineStyle(2);
l10->Draw("same");

TLine *l11 = new TLine(xmin,0.3,xmax,0.3);
l11->SetLineWidth(2);
l11->SetLineColor(1);
l11->SetLineStyle(2);
l11->Draw("same");

TLine *l12 = new TLine(xmin,0.32,xmax,0.32);
l12->SetLineWidth(2);
l12->SetLineColor(1);
l12->SetLineStyle(2);
l12->Draw("same");

TLine *l13 = new TLine(xmin,0.34,xmax,0.34);
l13->SetLineWidth(2);
l13->SetLineColor(1);
l13->SetLineStyle(2);
l13->Draw("same");


h_M4J_vs_alpha_contour2->Draw("CONT3 same");
h_M4J_vs_alpha_contour3->Draw("CONT3 same");
h_M4J_vs_alpha_contour4->Draw("CONT3 same");

frame->Draw("AXIS same");

paveCMS->Draw("same");
paveCMS2->Draw("same");


TPaveText *paveCMS3 = new TPaveText(0.535,0.52,0.77,0.88,"NDC");
paveCMS3->SetTextFont(42);
paveCMS3->AddText("Diquark");
paveCMS3->AddText("S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)");
paveCMS3->AddText("M_{#chi} / M_{S} = 0.25");
paveCMS3->AddText("M_{S} = 8.4 TeV");
paveCMS3->AddText("68% contours");
paveCMS3->AddText("#Gamma / M_{S} = 1.5%");
paveCMS3->AddText("#Gamma / M_{S} = 5%");
paveCMS3->AddText("#Gamma / M_{S} = 10%");
paveCMS3->SetFillColor(0);
paveCMS3->SetBorderSize(0);
paveCMS3->SetTextSize(0.036);
paveCMS3->SetTextAlign(12);
((TText*)paveCMS3->GetListOfLines()->At(5))->SetTextColor(kRed-3);
((TText*)paveCMS3->GetListOfLines()->At(6))->SetTextColor(kBlue-3);
((TText*)paveCMS3->GetListOfLines()->At(7))->SetTextColor(kGreen+2);
paveCMS3->Draw();


char cname[1024];
sprintf(cname, "plots/Figure_002-b.pdf");

c->SaveAs(cname);

}
