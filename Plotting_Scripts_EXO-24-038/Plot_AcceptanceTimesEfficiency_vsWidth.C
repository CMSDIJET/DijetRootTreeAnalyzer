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

void Plot_AcceptanceTimesEfficiency_vsWidth(){

double mass_W0p0043[10]={2, 3, 4, 5, 6, 7, 8, 8.4, 9, 10};
double acc_W0p0043[10]={0.16034, 0.17764, 0.18121, 0.18676, 0.188747, 0.18957, 0.187456, 0.1819, 0.17098, 0.14751}; //acceptance
double accEff_W0p0043[10]={0.14061, 0.17698, 0.18099, 0.18673, 0.188747, 0.18957, 0.187456, 0.1819 ,0.17098, 0.14751};  //acceptance x efficiency  

double mass[11]={2, 3, 4, 5, 6, 7, 8, 8.4, 8.6, 9, 10};

double acc_W0p015[11]={0.16579, 0.18209091, 0.18722, 0.19119, 0.18888, 0.1884, 0.1777, 0.16881, 0.16262, 0.15148, 0.11812}; //acceptance
double accEff_W0p015[11]={0.14648, 0.18132323, 0.18709, 0.19115, 0.18887, 0.18839, 0.1777, 0.1688, 0.16262, 0.15148, 0.11812};  //acceptance x efficiency 
double accEff_W0p015_error[11]={0.001118, 0.001225, 0.001233, 0.001243, 0.001238, 0.001237, 0.001209, 0.001185, 0.001167, 0.001134, 0.001021};

double acc_W0p05[11]={0.1666, 0.18126531, 0.18287, 0.18430303, 0.17789, 0.16761, 0.15112, 0.14023469, 0.13484, 0.12313, 0.10356}; //acceptance
double accEff_W0p05[11]={0.14237, 0.17985714, 0.18256, 0.18418182, 0.17785, 0.16759, 0.15111, 0.14023469, 0.13484, 0.12313, 0.10356};  //acceptance x efficiency 
double accEff_W0p05_error[11]={0.001105, 0.001227, 0.001222, 0.001232, 0.001209, 0.001181, 0.001133, 0.001109, 0.00108, 0.001039, 0.000964}; 

double acc_W0p1[11]={0.16834, 0.18286, 0.18479798, 0.18349, 0.17387, 0.1589, 0.13957143, 0.12922, 0.12315, 0.11349, 0.097}; //acceptance
double accEff_W0p1[11]={0.15048, 0.18145, 0.18438384, 0.18327, 0.17382, 0.15885, 0.13957143, 0.12921, 0.12314, 0.11349, 0.097};  //acceptance x efficiency 
double accEff_W0p1_error[11]={0.001131, 0.001219, 0.001232, 0.001223, 0.001198, 0.001156, 0.001107, 0.001061, 0.001039, 0.001003, 0.000936};

Double_t zero_errors[11] = {0};

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetLogy(0);
c->SetTickx(1);
c->SetTicky(1);
c->SetGridy(0);
c->SetRightMargin(0.03);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.14);
c->SetBottomMargin(0.12);

auto frame = c->DrawFrame(1.5,0.,10.5,0.25);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.85);
frame->GetXaxis()->SetTitle("Diquark mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.06);
frame->GetYaxis()->SetTitleOffset(1.15);
frame->GetYaxis()->SetTitle("#it{A}#varepsilon");
frame->GetXaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelSize(0.045);
frame->GetYaxis()->SetLabelOffset(0.012);


TGraph *gr_acc_W0p0043 = new TGraphAsymmErrors(10, mass_W0p0043, acc_W0p0043);
TGraphErrors *gr_accEff_W0p0043 = new TGraphErrors(10, mass_W0p0043, accEff_W0p0043);

TGraph *gr_acc_W0p015 = new TGraphAsymmErrors(11, mass, acc_W0p015);
TGraphErrors *gr_accEff_W0p015 = new TGraphErrors(11, mass, accEff_W0p015, zero_errors, accEff_W0p015_error);

TGraph *gr_acc_W0p05 = new TGraphAsymmErrors(11, mass, acc_W0p05);
TGraphErrors *gr_accEff_W0p05 = new TGraphErrors(11, mass, accEff_W0p05, zero_errors, accEff_W0p05_error);

TGraph *gr_acc_W0p1 = new TGraphAsymmErrors(11, mass, acc_W0p1);
TGraphErrors *gr_accEff_W0p1 = new TGraphErrors(11, mass, accEff_W0p1, zero_errors, accEff_W0p1_error);


gr_accEff_W0p0043->SetMarkerColor(kBlack);
gr_accEff_W0p0043->SetMarkerStyle(kFullSquare);
gr_accEff_W0p0043->SetMarkerSize(1.2);

gr_accEff_W0p015->SetMarkerColor(kRed+1);
gr_accEff_W0p015->SetMarkerStyle(kFullSquare);
gr_accEff_W0p015->SetMarkerSize(1.2);

gr_accEff_W0p05->SetMarkerColor(kBlue-3);
gr_accEff_W0p05->SetMarkerStyle(kFullSquare);
gr_accEff_W0p05->SetMarkerSize(1.2);

gr_accEff_W0p1->SetMarkerColor(kGreen+2);
gr_accEff_W0p1->SetMarkerStyle(kFullSquare);
gr_accEff_W0p1->SetMarkerSize(1.2);


gr_accEff_W0p015->Draw("pe same");
gr_accEff_W0p05->Draw("pe same");
gr_accEff_W0p1->Draw("pe same");



gr_acc_W0p0043->SetLineColor(kGray+3);
gr_acc_W0p0043->SetLineStyle(kFullSquare);
gr_acc_W0p0043->SetLineWidth(2);
gr_acc_W0p0043->SetMarkerStyle(kDot);
gr_acc_W0p0043->SetMarkerSize(0);

gr_acc_W0p015->SetLineColor(kRed-3);
gr_acc_W0p015->SetLineStyle(kFullSquare);
gr_acc_W0p015->SetLineWidth(2);
gr_acc_W0p015->SetMarkerStyle(kDot);
gr_acc_W0p015->SetMarkerSize(0);

gr_acc_W0p05->SetLineColor(kBlue-6);
gr_acc_W0p05->SetLineStyle(kFullSquare);
gr_acc_W0p05->SetLineWidth(2);
gr_acc_W0p05->SetMarkerStyle(kDot);
gr_acc_W0p05->SetMarkerSize(0);

gr_acc_W0p1->SetLineColor(kGreen-2);
gr_acc_W0p1->SetLineStyle(kFullSquare);
gr_acc_W0p1->SetLineWidth(2);
gr_acc_W0p1->SetMarkerStyle(kDot);
gr_acc_W0p1->SetMarkerSize(0);

gr_acc_W0p015->Draw("l same");
gr_acc_W0p05->Draw("l same");
gr_acc_W0p1->Draw("l same");

TPaveText *cms1 = new TPaveText(0.16,0.81,0.36,0.84,"NDC");
cms1->AddText("#splitline{#bf{CMS}}{#scale[0.7]{#it{Simulation}}}");
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.07); 
cms1->Draw();

TPaveText *cms2 = new TPaveText(0.842,0.925,0.952,0.955,"NDC"); 
cms2->AddText("(13 TeV)");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.05);
cms2->SetTextFont(42);
cms2->Draw();


TPaveText *pave = new TPaveText(0.62, 0.75, 0.94, 0.86,"NDC");
pave->SetTextAlign(31); 
pave->AddText("uu #rightarrow S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)" );
pave->AddText("M_{#chi} / M_{S} = 0.25");
pave->SetFillColor(0);
pave->SetBorderSize(0);
pave->SetTextSize(0.04);
pave->SetTextFont(42);
pave->Draw();


TPaveText *pave2 = new TPaveText(0.20, 0.24, 0.49, 0.34,"NDC");
pave2->SetTextAlign(11); 
pave2->AddText("All #alpha bins");
pave2->AddText("(#alpha > 0.1)");
pave2->SetFillColor(0);
pave2->SetBorderSize(0);
pave2->SetTextSize(0.04);
pave2->SetTextFont(42);
pave2->Draw();



TLegend *leg = new TLegend(0.46,0.18,0.80,0.38);
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->SetMargin(0.3);
leg->AddEntry(gr_acc_W0p015, " ", "L");
leg->AddEntry(gr_acc_W0p05, " ", "L");
leg->AddEntry(gr_acc_W0p1, " ", "L");
leg->Draw();

TLegend *leg2 = new TLegend(0.57,0.18,0.93,0.38);
leg2->SetFillColor(0);
leg2->SetBorderSize(0);
leg2->SetTextSize(0.04);
leg2->AddEntry(gr_accEff_W0p015, "#Gamma / M_{S} = 1.5%", "P");
leg2->AddEntry(gr_accEff_W0p05, "#Gamma / M_{S} = 5%", "P");
leg2->AddEntry(gr_accEff_W0p1, "#Gamma / M_{S} = 10%", "P");
leg2->Draw();

TLatex *lat = new TLatex();
lat->SetTextAlign(22);
lat->SetTextFont(42);
lat->SetTextSize(0.045);
lat->DrawLatex(5.5, 0.09,"#it{A}");
lat->DrawLatex(6.6, 0.09,"#it{A}#varepsilon");

char cname[1024];
sprintf(cname, "plots/Figure_004.pdf");

c->SaveAs(cname);

}



