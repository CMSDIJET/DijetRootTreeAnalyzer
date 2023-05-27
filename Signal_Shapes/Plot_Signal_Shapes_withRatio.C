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

void Plot_Signal_Shapes_withRatio(int Suu, int Chi, char var[1024]){

char xaxistitle[1024];

double xmin, xmax;

if(strcmp(var,"FourjetMass")==0) {sprintf(xaxistitle,"Four-jet mass [GeV]"); xmin = 1; xmax = 2.*Suu;}
if(strcmp(var,"Maverage")==0) {sprintf(xaxistitle,"Average dijet mass [GeV]"); xmin = 1; xmax = 2*Chi;}
if(strcmp(var,"Masymmetry")==0) {sprintf(xaxistitle,"Mass asymmetry"); xmin = 0; xmax = 0.12;}
if(strcmp(var,"DeltaEtaJJAK4")==0) {sprintf(xaxistitle,"|#Delta#eta_{JJ}|"); xmin = 0; xmax = 1.2;}
if(strcmp(var,"DeltaRAK4_First")==0) {sprintf(xaxistitle,"#DeltaR_{1}"); xmin = 0; xmax = 2.5;}
if(strcmp(var,"DeltaRAK4_Second")==0) {sprintf(xaxistitle,"#DeltaR_{2}"); xmin = 0; xmax = 2.5;}
if(strcmp(var,"alpha")==0) {sprintf(xaxistitle,"#alpha = Average dijet mass / Four-jet mass"); xmin = 0; xmax = 0.5;}

TPaveText *cms = new TPaveText(0.2,0.95,0.35,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname1[1024], fname2[1024], fname3[1024];
sprintf(fname1,"rootfiles/ResonanceShapes_EOY2017_Suu_Diquark_S%d_chi%d.root",Suu,Chi);
sprintf(fname2,"rootfiles/ResonanceShapes_Run3Summer22_Suu_Diquark_S%d_chi%d.root",Suu,Chi);
sprintf(fname3,"rootfiles/ResonanceShapes_Run3Summer22EE_Suu_Diquark_S%d_chi%d.root",Suu,Chi);

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");
TFile *f3 = new TFile(fname3,"READ");

TH1D *h1, *h2, *h3;

char hname[1024];
sprintf(hname,"h_%s",var);

h1 = (TH1D*)f1->Get(hname);
h2 = (TH1D*)f2->Get(hname);
h3 = (TH1D*)f3->Get(hname);

/*for(int i=1; i<=h1->GetNbinsX(); i++)
{
	if(h1->GetBinContent(i)==0) h1->SetBinContent(i,0.00001);
	if(h2->GetBinContent(i)==0) h2->SetBinContent(i,0.00001);
	if(h3->GetBinContent(i)==0) h3->SetBinContent(i,0.00001);	
}
*/

TCanvas *c = new TCanvas("c","",600,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);

TPad *pad1r = new TPad("pad1", "pad1", 0, 0.38, 1, 1);
pad1r->SetRightMargin(0.05);
pad1r->SetTopMargin(0.07);
pad1r->SetLeftMargin(0.13);
pad1r->SetBottomMargin(0.01);
pad1r->SetFillColor(0);
pad1r->SetBorderMode(0);
pad1r->SetFrameFillStyle(0);
pad1r->SetFrameBorderMode(0);
pad1r->Draw();
pad1r->cd();
pad1r->cd()->SetLogy(1);
//pad1r->cd()->SetLogx(1);
pad1r->SetTickx(1);
pad1r->SetTicky(1);

h1->SetTitle("");
h1->SetStats(0);
h1->GetXaxis()->SetRangeUser(xmin, xmax);
h2->GetXaxis()->SetRangeUser(xmin, xmax);
h1->GetYaxis()->SetTitle("Normalized entries");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetLineColor(kBlack);
h1->SetLineWidth(3);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
h1->SetMinimum(0.5);

h2->SetLineColor(kBlue);
h2->SetLineWidth(3);

h3->SetLineColor(kRed);
h3->SetLineWidth(3);

h2->Scale(h1->Integral()/h2->Integral());
h3->Scale(h1->Integral()/h3->Integral());

h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");

char legname[1024];
sprintf(legname,"#splitline{M_{S} = %d GeV}{M_{#chi} = %d GeV}",Suu,Chi);

TLegend *leg = new TLegend(0.62,0.5,0.8,0.9,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->SetHeader(legname);
leg->AddEntry(h1,"EOY2017","L");
leg->AddEntry(h2,"Run3Summer22","L");
leg->AddEntry(h3,"Run3Summer22EE","L");
leg->Draw();


cms->Draw();

TPaveText *lumileg = new TPaveText(0.71,0.95,0.90,0.99,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05); 
lumileg->AddText("13 TeV vs 13.6 TeV");
lumileg->Draw();

c->cd();
TPad *pad2r = new TPad("pad2r", "pad2r", 0, 0., 1, 0.35);
pad2r->SetLeftMargin(0.13);
pad2r->SetBottomMargin(0.25);
pad2r->SetRightMargin(0.05);
pad2r->SetTopMargin(0.01);
pad2r->Draw();
pad2r->cd(); 
pad2r->SetTickx(1);
pad2r->SetTicky(1);
//pad2r->cd()->SetLogx(1);

TH1D *h_ratio_Summer22_vs_EOY17 = (TH1D*)h2->Clone();
h_ratio_Summer22_vs_EOY17->Divide(h1);

TH1D *h_ratio_Summer22EE_vs_EOY17 = (TH1D*)h3->Clone();
h_ratio_Summer22EE_vs_EOY17->Divide(h1);

TH1D *h_ratio_Summer22_vs_Summer22EE = (TH1D*)h2->Clone();
h_ratio_Summer22_vs_Summer22EE->Divide(h3);

h_ratio_Summer22_vs_EOY17->SetStats(0);
h_ratio_Summer22_vs_EOY17->SetMarkerStyle(8);
h_ratio_Summer22_vs_EOY17->SetMarkerColor(kBlue);
h_ratio_Summer22_vs_EOY17->SetLineColor(kBlue);
h_ratio_Summer22_vs_EOY17->GetXaxis()->SetRangeUser(xmin, xmax);
h_ratio_Summer22_vs_EOY17->GetYaxis()->SetRangeUser(0.901, 1.099);
h_ratio_Summer22_vs_EOY17->GetYaxis()->SetLabelSize(0.08);
h_ratio_Summer22_vs_EOY17->GetXaxis()->SetLabelSize(0.08);
h_ratio_Summer22_vs_EOY17->GetXaxis()->SetLabelOffset(0.03);
h_ratio_Summer22_vs_EOY17->GetXaxis()->SetTitle(xaxistitle);
h_ratio_Summer22_vs_EOY17->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio_Summer22_vs_EOY17->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio_Summer22_vs_EOY17->GetYaxis()->SetTitle("Ratio");
h_ratio_Summer22_vs_EOY17->GetYaxis()->CenterTitle(1);
h_ratio_Summer22_vs_EOY17->GetYaxis()->SetTitleSize(0.1);
h_ratio_Summer22_vs_EOY17->GetYaxis()->SetTitleOffset(0.55);
h_ratio_Summer22_vs_EOY17->GetYaxis()->SetNdivisions(210);
h_ratio_Summer22_vs_EOY17->SetLineWidth(3);
//h_ratio_Summer22_vs_EOY17->SetLineStyle(kDashed);
h_ratio_Summer22_vs_EOY17->Draw("hist");

h_ratio_Summer22EE_vs_EOY17->SetMarkerStyle(8);
h_ratio_Summer22EE_vs_EOY17->SetMarkerColor(kRed);
h_ratio_Summer22EE_vs_EOY17->SetLineColor(kRed);
h_ratio_Summer22EE_vs_EOY17->SetLineWidth(3);

h_ratio_Summer22_vs_Summer22EE->SetMarkerStyle(8);
h_ratio_Summer22_vs_Summer22EE->SetMarkerColor(kMagenta+1);
h_ratio_Summer22_vs_Summer22EE->SetLineColor(kMagenta+1);
h_ratio_Summer22_vs_Summer22EE->SetLineWidth(3);

h_ratio_Summer22EE_vs_EOY17->Draw("hist same");
h_ratio_Summer22_vs_Summer22EE->Draw("hist same");

TLine *line = new TLine(xmin,1,xmax,1);
line->SetLineWidth(2);
line->SetLineColor(kBlack);
//line->SetLineStyle(kDashed);
line->Draw("same");

TLegend *leg2 = new TLegend(0.65,0.5,0.8,0.9,"");
leg2->SetBorderSize(0);
leg2->SetTextSize(0.05);
leg2->AddEntry(h_ratio_Summer22_vs_EOY17,"Run3Summer22 / EOY2017","PE");
leg2->AddEntry(h_ratio_Summer22EE_vs_EOY17,"Run3Summer22EE / EOY2017","PE");
leg2->AddEntry(h_ratio_Summer22_vs_Summer22EE,"Run3Summer22 / Run3Summer22EE","PE");
leg2->Draw();

char cname_1[1024], cname_2[1024];
sprintf(cname_1,"plots/%s_Summer22_VS_Summer22EE_VS_EOY2017_S%d_chi%d.png",var,Suu,Chi);
sprintf(cname_2,"plots/%s_Summer22_VS_Summer22EE_VS_EOY2017_S%d_chi%d.pdf",var,Suu,Chi);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
