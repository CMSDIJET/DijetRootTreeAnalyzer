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

void Plot_Signal_Shapes_phi_allsignals(char var[1024]){

char xaxistitle[1024];

double xmin, xmax;
if(strcmp(var,"phi_eta1p5to2")==0) {sprintf(xaxistitle,"#phi of 4 leading jets"); xmin = -3.2; xmax = 3.2;}
if(strcmp(var,"phi_NOTeta1p5to2")==0) {sprintf(xaxistitle,"#phi of 4 leading jets"); xmin = -3.2; xmax = 3.2;}

TPaveText *cms = new TPaveText(0.2,0.94,0.35,0.98,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.05);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname1[1024], fname2[1024], fname3[1024];
sprintf(fname1,"rootfiles/etaphi_EOY2017_allsignals.root");
sprintf(fname2,"rootfiles/etaphi_Run3Summer22_allsignals.root");
sprintf(fname3,"rootfiles/etaphi_Run3Summer22EE_allsignals.root");

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");
TFile *f3 = new TFile(fname3,"READ");

TH1D *h1, *h2, *h3;

char hname[1024];
sprintf(hname,"h_%s",var);

h1 = (TH1D*)f1->Get(hname);
h2 = (TH1D*)f2->Get(hname);
h3 = (TH1D*)f3->Get(hname);


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.05);
c->SetTopMargin(0.07);
c->SetLeftMargin(0.1);
//c->SetLogy(1);

h1->SetTitle("");
h1->SetStats(0);
h1->GetXaxis()->SetRangeUser(xmin, xmax);
h2->GetXaxis()->SetRangeUser(xmin, xmax);
h3->GetXaxis()->SetRangeUser(xmin, xmax);
//h1->GetYaxis()->SetTitle("Normalized entries");
h1->GetXaxis()->SetTitle(xaxistitle);
h1->GetYaxis()->SetTitleSize(0.05);
h1->GetYaxis()->SetTitleOffset(1.1);
h1->GetXaxis()->SetTitleSize(0.05);
h1->GetXaxis()->SetTitleOffset(0.9);
h1->SetLineColor(kBlack);
h1->SetLineWidth(3);
h1->SetMinimum(0.5);

h2->SetLineColor(kBlue);
h2->SetLineWidth(3);

h3->SetLineColor(kRed);
h3->SetLineWidth(3);

h2->Scale(h1->Integral()/h2->Integral());
h3->Scale(h1->Integral()/h3->Integral());

double max = h1->GetMaximum(); 
if(h2->GetMaximum() > max) max = h2->GetMaximum();
if(h3->GetMaximum() > max) max = h3->GetMaximum();

h1->SetMaximum(max*1.1);
h1->SetMaximum(500);
h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");


double x1,x2,y1,y2;
if(strcmp(var,"phi_NOTeta1p5to2")==0 || strcmp(var,"phi_eta1p5to2")==0) {x1=0.15; x2=0.33; y1=0.15; y2=0.45;}
//if(strcmp(var,"phi_eta1p5to2")==0) {x1=0.15; x2=0.33; y1=0.6; y2=0.9;}

TLegend *leg = new TLegend(x1,y1,x2,y2,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->AddEntry((TObject*)0,"","");
if(strcmp(var,"phi_eta1p5to2")==0) leg->AddEntry((TObject*)0,"1.5 < #eta < 2","");
if(strcmp(var,"phi_NOTeta1p5to2")==0) leg->AddEntry((TObject*)0,"-2.5 < #eta < 1.5 or 2 < #eta < 2.5","");
leg->AddEntry(h1,"EOY2017","L");
leg->AddEntry(h2,"Run3Summer22","L");
leg->AddEntry(h3,"Run3Summer22EE","L");
leg->Draw();


cms->Draw();

TPaveText *lumileg = new TPaveText(0.72,0.94,0.91,0.98,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.04); 
lumileg->AddText("13 TeV vs 13.6 TeV");
lumileg->Draw();

char cname_1[1024], cname_2[1024];
sprintf(cname_1,"plots/%s_Summer22_VS_Summer22EE_VS_EOY2017_allsignals.png",var);
sprintf(cname_2,"plots/%s_Summer22_VS_Summer22EE_VS_EOY2017_allsignals.pdf",var);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
