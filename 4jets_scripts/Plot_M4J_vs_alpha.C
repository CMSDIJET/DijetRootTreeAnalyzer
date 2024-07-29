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

void Plot_M4J_vs_alpha(double width, double alpha_true, double Suu){

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


TPaveText *paveCMS3 = new TPaveText(0.15,0.7,0.30,0.89,"NDC");
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
sprintf(f_name, "signal_histos_Alpha/M4JvsAlpha_Suu-Diquark_W-%s_S-%.0f_chi-%.0f.root", width_name, Suu, Suu*alpha_true);

TFile *f = new TFile(f_name,"READ");
TH2D *h_M4J_vs_M2J = (TH2D*)(f->Get("h_M4J_vs_alpha"));



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

double xmin=0.2;
double xmax=10.4;
double ymin=0.08;
double ymax=0.52;

auto frame = c->DrawFrame(xmin,ymin,xmax,ymax);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.9);
frame->GetXaxis()->SetTitle("Four-jet mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(1.15);
frame->GetYaxis()->SetTitle("#alpha = Average dijet mass / Four-jet mass");
frame->GetYaxis()->SetLabelSize(0.047);
frame->GetYaxis()->SetLabelOffset(0.012);
frame->GetXaxis()->SetLabelSize(0.05);

h_M4J_vs_M2J->SetZTitle("Events/bin");
h_M4J_vs_M2J->GetZaxis()->SetTitleSize(0.065);
h_M4J_vs_M2J->GetZaxis()->SetRangeUser(0.00001,1.);  
h_M4J_vs_M2J->GetZaxis()->SetTitleOffset(1.);
h_M4J_vs_M2J->GetZaxis()->SetLabelSize(0.05);

h_M4J_vs_M2J->Draw("colz same");

frame->Draw("AXIS same");

paveCMS->Draw("same");
paveCMS2->Draw("same");
paveCMS3->Draw("same");

TLine *lvert = new TLine(1.607,ymin,1.607,0.4);
lvert->SetLineStyle(kDashed);
lvert->SetLineWidth(3);
lvert->Draw("same");

TLine *l1 = new TLine(xmin,0.10,xmax,0.10);
l1->SetLineWidth(3);
l1->SetLineColor(1);
l1->SetLineStyle(2);
l1->Draw("same");

TLine *l2 = new TLine(xmin,0.12,xmax,0.12);
l2->SetLineWidth(3);
l2->SetLineColor(1);
l2->SetLineStyle(2);
l2->Draw("same");

TLine *l3 = new TLine(xmin,0.14,xmax,0.14);
l3->SetLineWidth(3);
l3->SetLineColor(1);
l3->SetLineStyle(2);
l3->Draw("same");

TLine *l4 = new TLine(xmin,0.16,xmax,0.16);
l4->SetLineWidth(3);
l4->SetLineColor(1);
l4->SetLineStyle(2);
l4->Draw("same");

TLine *l5 = new TLine(xmin,0.18,xmax,0.18);
l5->SetLineWidth(3);
l5->SetLineColor(1);
l5->SetLineStyle(2);
l5->Draw("same");

TLine *l6 = new TLine(xmin,0.2,xmax,0.2);
l6->SetLineWidth(3);
l6->SetLineColor(1);
l6->SetLineStyle(2);
l6->Draw("same");

TLine *l7 = new TLine(xmin,0.22,xmax,0.22);
l7->SetLineWidth(3);
l7->SetLineColor(1);
l7->SetLineStyle(2);
l7->Draw("same");

TLine *l8 = new TLine(xmin,0.24,xmax,0.24);
l8->SetLineWidth(3);
l8->SetLineColor(1);
l8->SetLineStyle(2);
l8->Draw("same");

TLine *l9 = new TLine(xmin,0.26,xmax,0.26);
l9->SetLineWidth(3);
l9->SetLineColor(1);
l9->SetLineStyle(2);
l9->Draw("same");

TLine *l10 = new TLine(xmin,0.28,xmax,0.28);
l10->SetLineWidth(3);
l10->SetLineColor(1);
l10->SetLineStyle(2);
l10->Draw("same");

TLine *l11 = new TLine(xmin,0.3,xmax,0.3);
l11->SetLineWidth(3);
l11->SetLineColor(1);
l11->SetLineStyle(2);
l11->Draw("same");

TLine *l12 = new TLine(xmin,0.32,xmax,0.32);
l12->SetLineWidth(3);
l12->SetLineColor(1);
l12->SetLineStyle(2);
l12->Draw("same");

TLine *l13 = new TLine(xmin,0.34,xmax,0.34);
l13->SetLineWidth(3);
l13->SetLineColor(1);
l13->SetLineStyle(2);
l13->Draw("same");

char cname1[1024], cname2[1024];
sprintf(cname1, "output/Wide_Resonances_Run2_Final/plots/M4JvsAlpha_Suu-%.0f_chi-%.0f_W-%s.png", Suu, Suu*alpha_true, width_name);
sprintf(cname2, "output/Wide_Resonances_Run2_Final/plots/M4JvsAlpha_Suu-%.0f_chi-%.0f_W-%s.pdf", Suu, Suu*alpha_true, width_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}
