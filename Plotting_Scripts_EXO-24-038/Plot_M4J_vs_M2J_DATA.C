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

void Plot_M4J_vs_M2J_DATA(){

TPaveText *paveCMS = new TPaveText(0.17,0.79,0.27,0.87,"NDC");
paveCMS->AddText("#bf{CMS}");
paveCMS->SetTextFont(42); 
paveCMS->SetFillColor(0);
paveCMS->SetBorderSize(0);
paveCMS->SetTextSize(0.08);

TPaveText *paveCMS2 = new TPaveText(0.625,0.93,0.755,0.96,"NDC");
paveCMS2->SetTextFont(42);
paveCMS2->AddText("138 fb^{-1} (13 TeV)");
paveCMS2->SetFillColor(0);
paveCMS2->SetBorderSize(0);
paveCMS2->SetTextSize(0.05);


char f_name[1024], fcont68Narrow_name[1024], fcont68Wide1_name[1024], fcont68Wide2_name[1024], fcont68Wide3_name[1024];
sprintf(f_name, "files/HISTOS_2016_2017_2018.root");
sprintf(fcont68Narrow_name, "files/contour68_M4JvsM2J_Suu-Diquark_W-0p0043_S-8400_chi-2100.root");
sprintf(fcont68Wide1_name, "files/contour68_M4JvsM2J_Suu-Diquark_W-0p015_S-8400_chi-2100.root");
sprintf(fcont68Wide2_name, "files/contour68_M4JvsM2J_Suu-Diquark_W-0p05_S-8400_chi-2100.root");
sprintf(fcont68Wide3_name, "files/contour68_M4JvsM2J_Suu-Diquark_W-0p1_S-8400_chi-2100.root");

TFile *f = new TFile(f_name,"READ");
TFile *fcont68Narrow = new TFile(fcont68Narrow_name,"READ");
TFile *fcont68Wide1 = new TFile(fcont68Wide1_name,"READ");
TFile *fcont68Wide2 = new TFile(fcont68Wide2_name,"READ");
TFile *fcont68Wide3 = new TFile(fcont68Wide3_name,"READ");

TH2D *h_data = (TH2D*)(f->Get("h_M4J_vs_M2J"));
TH2D *h_cont68Narrow = (TH2D*)(fcont68Narrow->Get("h_M4J_vs_M2J"));
TH2D *h_cont68Wide1 = (TH2D*)(fcont68Wide1->Get("h_M4J_vs_M2J"));
TH2D *h_cont68Wide2 = (TH2D*)(fcont68Wide2->Get("h_M4J_vs_M2J"));
TH2D *h_cont68Wide3 = (TH2D*)(fcont68Wide3->Get("h_M4J_vs_M2J"));

h_data->SetStats(0);
h_cont68Narrow->SetStats(0);
h_cont68Wide1->SetStats(0);
h_cont68Wide2->SetStats(0);
h_cont68Wide3->SetStats(0);



TPaveText *paveCMS3 = new TPaveText(0.54,0.15,0.7775,0.53,"NDC");
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

auto frame = c->DrawFrame(1.6,0.15,10.4,2.6);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.9);
frame->GetXaxis()->SetTitle("Four-jet mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.02);
frame->GetYaxis()->SetTitle("Average dijet mass [TeV]");
frame->GetYaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelOffset(0.015);
frame->GetXaxis()->SetLabelSize(0.05);

h_data->SetZTitle("Events/bin");
h_data->GetZaxis()->SetTitleSize(0.065);  
h_data->GetZaxis()->SetRangeUser(0.1,10000);
h_data->GetZaxis()->SetTitleOffset(1.);
h_data->GetZaxis()->SetLabelSize(0.05);

h_data->Draw("colz same");

TPaveText *paveWhiteBox = new TPaveText(0.88, 0.08, 0.96, 0.17, "NDC");
paveWhiteBox->SetTextFont(42);
paveWhiteBox->SetFillColor(0);  
paveWhiteBox->SetBorderSize(0); 
paveWhiteBox->SetTextSize(0.1); 
paveWhiteBox->AddText(""); 
paveWhiteBox->Draw(); 


h_cont68Narrow->SetLineColor(kViolet);
h_cont68Narrow->SetLineWidth(2);
h_cont68Narrow->SetLineStyle(1);

h_cont68Wide1->SetLineColor(kRed-3);
h_cont68Wide1->SetLineWidth(2);
h_cont68Wide1->SetLineStyle(1);

h_cont68Wide2->SetLineColor(kBlue-3);
h_cont68Wide2->SetLineWidth(2);
h_cont68Wide2->SetLineStyle(1);

h_cont68Wide3->SetLineColor(kGreen+2);
h_cont68Wide3->SetLineWidth(2);
h_cont68Wide3->SetLineStyle(1);


h_cont68Wide1->Draw("CONT3 same");
h_cont68Wide2->Draw("CONT3 same");
h_cont68Wide3->Draw("CONT3 same");

frame->Draw("AXIS same");

paveCMS->Draw("same");
paveCMS2->Draw("same");
paveCMS3->Draw("same");

char cname[1024];
sprintf(cname, "plots/Figure_002-a.pdf");

c->SaveAs(cname);

}
