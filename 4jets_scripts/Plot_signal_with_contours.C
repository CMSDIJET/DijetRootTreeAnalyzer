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

void Plot_signal_with_contours(double width, double alpha_true, double Suu){

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


TPaveText *paveCMS = new TPaveText(0.28,0.93,0.38,0.96,"NDC");
paveCMS->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
paveCMS->SetTextFont(42); 
paveCMS->SetFillColor(0);
paveCMS->SetBorderSize(0);
paveCMS->SetTextSize(0.06);

TPaveText *paveCMS2 = new TPaveText(0.7,0.93,0.83,0.96,"NDC");
paveCMS2->SetTextFont(42);
paveCMS2->AddText("13 TeV");
paveCMS2->SetFillColor(0);
paveCMS2->SetBorderSize(0);
paveCMS2->SetTextSize(0.05);

char leg_alpha[1024], leg_Suu[1024], leg_width[1024];
sprintf(leg_alpha, "M_{#chi} / M_{S} = %.2f", alpha_true);
sprintf(leg_Suu, "M_{S} = %.1f TeV", Suu/1000.);
if(width==0.0043) sprintf(leg_width, "#Gamma / M_{S} = %.2f %%", width*100.);
if(width==0.015) sprintf(leg_width, "#Gamma / M_{S} = %.1f %%", width*100.);
if(width==0.05 || width==0.1) sprintf(leg_width, "#Gamma / M_{S} = %.0f %%", width*100.);


TPaveText *paveCMS3 = new TPaveText(0.15,0.65,0.30,0.89,"NDC");
paveCMS3->AddText("Diquark: S #rightarrow #chi#chi #rightarrow (ug)(ug)");
paveCMS3->AddText(leg_alpha);
paveCMS3->AddText(leg_Suu);
paveCMS3->AddText(leg_width);
paveCMS3->SetTextFont(42); 
paveCMS3->SetFillColor(0);
paveCMS3->SetBorderSize(0);
paveCMS3->SetTextSize(0.04);
paveCMS3->SetTextAlign(12);

char f_name[1024], fcont68_name[1024], fcont90_name[1024];
sprintf(f_name, "signal_histos_contours/M4JvsM2J_Suu-Diquark_W-%s_S-%.0f_chi-%.0f.root", width_name, Suu, Suu*alpha_true);
sprintf(fcont68_name, "signal_histos_contours/contour68_Suu-Diquark_W-%s_S-%.0f_chi-%.0f.root", width_name, Suu, Suu*alpha_true);
sprintf(fcont90_name, "signal_histos_contours/contour90_Suu-Diquark_W-%s_S-%.0f_chi-%.0f.root", width_name, Suu, Suu*alpha_true);

TFile *f = new TFile(f_name,"READ");
TH2D *h_M4J_vs_M2J = (TH2D*)(f->Get("h_M4J_vs_M2J"));

TFile *fcont68 = new TFile(fcont68_name,"READ");
TH2D *h_cont68 = (TH2D*)(fcont68->Get("h_M4J_vs_M2J"));
h_cont68->SetStats(0);

TFile *fcont90 = new TFile(fcont90_name,"READ");
TH2D *h_cont90 = (TH2D*)(fcont90->Get("h_M4J_vs_M2J"));
h_cont90->SetStats(0);


TLegend *legend = new TLegend(0.56,0.16,0.73,0.27); //0.63,0.3,0.73,0.5,"NDC"
legend->SetTextFont(42);
legend->AddEntry(h_cont68,"68% contour","L");
legend->AddEntry(h_cont90,"90% contour","L");
legend->SetFillColor(0);
legend->SetBorderSize(0);
legend->SetTextSize(0.045);


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

auto frame = c->DrawFrame(1.2,0.15,10.4,2.8);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.9);
frame->GetXaxis()->SetTitle("Four-jet mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.02);
frame->GetYaxis()->SetTitle("Average dijet mass [TeV]");
frame->GetYaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelOffset(0.015);
frame->GetXaxis()->SetLabelSize(0.05);

h_M4J_vs_M2J->SetZTitle("Events/bin");
h_M4J_vs_M2J->GetZaxis()->SetTitleSize(0.065);
h_M4J_vs_M2J->GetZaxis()->SetRangeUser(0.00001,1.);  
h_M4J_vs_M2J->GetZaxis()->SetTitleOffset(1.);
h_M4J_vs_M2J->GetZaxis()->SetLabelSize(0.05);

h_M4J_vs_M2J->Draw("colz same");

h_cont68->SetLineColor(kViolet);
h_cont68->SetLineWidth(3);
h_cont90->SetLineColor(kGreen-7);
h_cont90->SetLineWidth(3);

h_cont68->Draw("CONT3 same");
h_cont90->Draw("CONT3 same");

paveCMS->Draw("same");
paveCMS2->Draw("same");
paveCMS3->Draw("same");
legend->Draw("same");

char cname[1024];
sprintf(cname, "output/Wide_Resonances_Run2_Final/plots/2DSignalWithContours_Suu-%.0f_chi-%.0f_W-%s.pdf", Suu, Suu*alpha_true, width_name);

c->SaveAs(cname);

}
