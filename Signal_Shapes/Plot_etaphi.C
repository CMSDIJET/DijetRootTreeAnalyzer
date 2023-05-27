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

void Plot_etaphi(){

char xaxistitle[1024], yaxistitle[1024];

sprintf(xaxistitle,"#eta of the 4 leading jets");
sprintf(yaxistitle,"#phi of the 4 leading jets");
double xmin = 1.;
double xmax = 3.;
double ymin = -3.2;
double ymax = 3.2;

TPaveText *cms = new TPaveText(0.18,0.95,0.33,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.045);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname1[1024], fname2[1024], fname3[1024];
sprintf(fname1,"rootfiles/etaphi_EOY2017_allsignals.root");
sprintf(fname2,"rootfiles/etaphi_Run3Summer22_allsignals.root");
sprintf(fname3,"rootfiles/etaphi_Run3Summer22EE_allsignals.root");

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");
TFile *f3 = new TFile(fname3,"READ");

TH2D *h1 = (TH2D*)f1->Get("h_etaphi");
TH2D *h2 = (TH2D*)f2->Get("h_etaphi");
TH2D *h3 = (TH2D*)f3->Get("h_etaphi");

h2->Scale(h1->Integral()/h2->Integral());
h3->Scale(h1->Integral()/h3->Integral());

TCanvas *c1 = new TCanvas("c1","",700,700);
c1->cd();
c1->SetTickx(1);
c1->SetTicky(1);
c1->SetRightMargin(0.15);
c1->SetTopMargin(0.06);
c1->SetLeftMargin(0.1);
c1->SetBottomMargin(0.1);
c1->SetFillColor(0);
c1->SetBorderMode(0);
c1->SetFrameFillStyle(0);
c1->SetFrameBorderMode(0);
//c->SetLogz(1);

h1->SetTitle("");
h1->SetStats(0);
h1->GetXaxis()->SetRangeUser(xmin, xmax);
h1->GetYaxis()->SetRangeUser(ymin, ymax);
h1->GetZaxis()->SetTitle("Entries");
h1->GetXaxis()->SetTitle(xaxistitle);
h1->GetYaxis()->SetTitle(yaxistitle);
h1->GetXaxis()->SetTitleSize(0.05);
h1->GetYaxis()->SetTitleSize(0.05);
h1->GetZaxis()->SetTitleSize(0.05);
h1->GetXaxis()->SetTitleOffset(0.85);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->GetZaxis()->SetTitleOffset(0.85);
h1->GetZaxis()->SetRangeUser(0,300);
h1->Draw("COLZ");


TPaveText *mc1 = new TPaveText(0.75,0.95,0.85,0.99,"NDC");
mc1->AddText("EOY 2017");
mc1->SetTextFont(42);
mc1->SetTextSize(0.045);
mc1->SetBorderSize(0);
mc1->SetFillColor(0);
mc1->Draw();

cms->Draw();

char cname_1[1024], cname_2[1024];

sprintf(cname_1,"plots/etaphi_EOY2017_allsignals.png");
sprintf(cname_2,"plots/etaphi_EOY2017_allsignals.pdf");

//c1->SaveAs(cname_1);
//c1->SaveAs(cname_2);




TCanvas *c2 = new TCanvas("c2","",700,700);
c2->cd();
c2->SetTickx(1);
c2->SetTicky(1);
c2->SetRightMargin(0.15);
c2->SetTopMargin(0.06);
c2->SetLeftMargin(0.1);
c2->SetBottomMargin(0.1);
c2->SetFillColor(0);
c2->SetBorderMode(0);
c2->SetFrameFillStyle(0);
c2->SetFrameBorderMode(0);
//c->SetLogz(1);

h2->SetTitle("");
h2->SetStats(0);
h2->GetXaxis()->SetRangeUser(xmin, xmax);
h2->GetYaxis()->SetRangeUser(ymin, ymax);
h2->GetZaxis()->SetTitle("Entries");
h2->GetXaxis()->SetTitle(xaxistitle);
h2->GetYaxis()->SetTitle(yaxistitle);
h2->GetXaxis()->SetTitleSize(0.05);
h2->GetYaxis()->SetTitleSize(0.05);
h2->GetZaxis()->SetTitleSize(0.05);
h2->GetXaxis()->SetTitleOffset(0.85);
h2->GetYaxis()->SetTitleOffset(0.9);
h2->GetZaxis()->SetTitleOffset(0.85);
h2->GetZaxis()->SetRangeUser(0,300);
h2->Draw("COLZ");


TPaveText *mc2 = new TPaveText(0.7,0.95,0.8,0.99,"NDC");
mc2->AddText("Run3Summer22");
mc2->SetTextFont(42);
mc2->SetTextSize(0.045);
mc2->SetBorderSize(0);
mc2->SetFillColor(0);
mc2->Draw();

cms->Draw();

char cname_3[1024], cname_4[1024];

sprintf(cname_3,"plots/etaphi_Run3Summer22_allsignals.png");
sprintf(cname_4,"plots/etaphi_Run3Summer22_allsignals.pdf");

//c2->SaveAs(cname_3);
//c2->SaveAs(cname_4);


TCanvas *c3 = new TCanvas("c3","",700,700);
c3->cd();
c3->SetTickx(1);
c3->SetTicky(1);
c3->SetRightMargin(0.15);
c3->SetTopMargin(0.06);
c3->SetLeftMargin(0.1);
c3->SetBottomMargin(0.1);
c3->SetFillColor(0);
c3->SetBorderMode(0);
c3->SetFrameFillStyle(0);
c3->SetFrameBorderMode(0);
//c->SetLogz(1);

h3->SetTitle("");
h3->SetStats(0);
h3->GetXaxis()->SetRangeUser(xmin, xmax);
h3->GetYaxis()->SetRangeUser(ymin, ymax);
h3->GetZaxis()->SetTitle("Entries");
h3->GetXaxis()->SetTitle(xaxistitle);
h3->GetYaxis()->SetTitle(yaxistitle);
h3->GetXaxis()->SetTitleSize(0.05);
h3->GetYaxis()->SetTitleSize(0.05);
h3->GetZaxis()->SetTitleSize(0.05);
h3->GetXaxis()->SetTitleOffset(0.85);
h3->GetYaxis()->SetTitleOffset(0.9);
h3->GetZaxis()->SetTitleOffset(0.85);
h3->GetZaxis()->SetRangeUser(0,300);
h3->Draw("COLZ");

TPaveText *mc3 = new TPaveText(0.65,0.95,0.75,0.99,"NDC");
mc3->AddText("Run3Summer22EE");
mc3->SetTextFont(42);
mc3->SetTextSize(0.045);
mc3->SetBorderSize(0);
mc3->SetFillColor(0);
mc3->Draw();

cms->Draw();

char cname_5[1024], cname_6[1024];

sprintf(cname_5,"plots/etaphi_Run3Summer22EE_allsignals.png");
sprintf(cname_6,"plots/etaphi_Run3Summer22EE_allsignals.pdf");

//c3->SaveAs(cname_5);
//c3->SaveAs(cname_6);


}
