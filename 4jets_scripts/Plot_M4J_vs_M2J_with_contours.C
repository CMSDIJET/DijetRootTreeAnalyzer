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

void Plot_M4J_vs_M2J_with_contours(){

/*TPaveText *paveCMS = new TPaveText(0.2,0.93,0.3,0.96,"NDC");
paveCMS->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
paveCMS->SetTextFont(42); 
paveCMS->SetFillColor(0);
paveCMS->SetBorderSize(0);
paveCMS->SetTextSize(0.06);*/

TPaveText *paveCMS = new TPaveText(0.2,0.77,0.3,0.85,"NDC");
paveCMS->AddText("#splitline{#bf{CMS}}{#scale[0.7]{#it{Preliminary}}}");
paveCMS->SetTextFont(42); 
paveCMS->SetFillColor(0);
paveCMS->SetBorderSize(0);
paveCMS->SetTextSize(0.06);

TPaveText *paveCMS2 = new TPaveText(0.625,0.93,0.755,0.96,"NDC");
paveCMS2->SetTextFont(42);
paveCMS2->AddText("138 fb^{-1} (13 TeV)");
paveCMS2->SetFillColor(0);
paveCMS2->SetBorderSize(0);
paveCMS2->SetTextSize(0.05);


char f_name[1024], fcont68Narrow_name[1024], fcont90Narrow_name[1024], fcont68Wide_name[1024], fcont90Wide_name[1024];
sprintf(f_name, "/afs/cern.ch/user/i/izisopou/public/EXO-21-010/EXO-21-010-Plotting-Scripts/Figure_002/HISTOS_2016_2017_2018_Robert.root");
sprintf(fcont68Narrow_name, "signal_histos_contours/contour68_Suu-Diquark_W-0p0043_S-8400_chi-2100.root");
sprintf(fcont90Narrow_name, "signal_histos_contours/contour90_Suu-Diquark_W-0p0043_S-8400_chi-2100.root");
sprintf(fcont68Wide_name, "signal_histos_contours/contour68_Suu-Diquark_W-0p1_S-8400_chi-2100.root");
sprintf(fcont90Wide_name, "signal_histos_contours/contour90_Suu-Diquark_W-0p1_S-8400_chi-2100.root");

TFile *f = new TFile(f_name,"READ");
TFile *fcont68Narrow = new TFile(fcont68Narrow_name,"READ");
TFile *fcont90Narrow = new TFile(fcont90Narrow_name,"READ");
TFile *fcont68Wide = new TFile(fcont68Wide_name,"READ");
TFile *fcont90Wide = new TFile(fcont90Wide_name,"READ");

TH2D *h_data = (TH2D*)(f->Get("h_M4J_vs_M2J"));
TH2D *h_cont68Narrow = (TH2D*)(fcont68Narrow->Get("h_M4J_vs_M2J"));
TH2D *h_cont90Narrow = (TH2D*)(fcont90Narrow->Get("h_M4J_vs_M2J"));
TH2D *h_cont68Wide = (TH2D*)(fcont68Wide->Get("h_M4J_vs_M2J"));
TH2D *h_cont90Wide = (TH2D*)(fcont90Wide->Get("h_M4J_vs_M2J"));

h_data->SetStats(0);
h_cont68Narrow->SetStats(0);
h_cont90Narrow->SetStats(0);
h_cont68Wide->SetStats(0);
h_cont90Wide->SetStats(0);



TPaveText *paveCMS3 = new TPaveText(0.555,0.15,0.79,0.49,"NDC");
paveCMS3->SetTextFont(42);
paveCMS3->AddText("Diquark");
paveCMS3->AddText("S #rightarrow #chi#chi #rightarrow (ug)(ug)");
paveCMS3->AddText("M_{#chi} / M_{S} = 0.25");
paveCMS3->AddText("M_{S} = 8.4 TeV");
paveCMS3->AddText("68% and 90%");
paveCMS3->AddText("contours");
paveCMS3->AddText("#Gamma / M_{S} = 0.43%");
paveCMS3->AddText("#Gamma / M_{S} = 10%");
paveCMS3->SetFillColor(0);
paveCMS3->SetBorderSize(1);
paveCMS3->SetTextSize(0.035);
paveCMS3->SetTextAlign(12);
((TText*)paveCMS3->GetListOfLines()->At(6))->SetTextColor(kViolet);
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
h_data->GetZaxis()->SetRangeUser(1.,200000);  
h_data->GetZaxis()->SetTitleOffset(1.);
h_data->GetZaxis()->SetLabelSize(0.05);

h_data->Draw("colz same");

h_cont68Narrow->SetLineColor(kViolet);
h_cont90Narrow->SetLineColor(kViolet);
h_cont68Narrow->SetLineWidth(2);
h_cont90Narrow->SetLineWidth(2);
h_cont68Narrow->SetLineStyle(3);
h_cont90Narrow->SetLineStyle(7);

h_cont68Wide->SetLineColor(kGreen+2);
h_cont90Wide->SetLineColor(kGreen+2);
h_cont68Wide->SetLineWidth(2);
h_cont90Wide->SetLineWidth(2);
h_cont68Wide->SetLineStyle(3);
h_cont90Wide->SetLineStyle(7);

h_cont68Narrow->Draw("CONT3 same");
h_cont90Narrow->Draw("CONT3 same");
h_cont68Wide->Draw("CONT3 same");
h_cont90Wide->Draw("CONT3 same");

frame->Draw("AXIS same");

paveCMS->Draw("same");
paveCMS2->Draw("same");
paveCMS3->Draw("same");

char cname[1024];
sprintf(cname, "output/Wide_Resonances_Run2_Final/plots/M4JvsM2J_Data_And_SignalContours.pdf");

//c->SaveAs(cname);

}
