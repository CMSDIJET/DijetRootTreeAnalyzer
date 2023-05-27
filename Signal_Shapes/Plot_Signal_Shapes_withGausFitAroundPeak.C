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

void Plot_Signal_Shapes_withGausFitAroundPeak(int Suu, int Chi, char var[1024]){

char xaxistitle[1024];

double xmin, xmax;

if(strcmp(var,"FourjetMass")==0) {sprintf(xaxistitle,"Four-jet mass [GeV]"); xmin = Suu-0.6*Suu; xmax = Suu+0.8*Suu;}
if(strcmp(var,"Maverage")==0) {sprintf(xaxistitle,"Average dijet mass [GeV]"); xmin = Chi-0.6*Chi; xmax = Chi+0.8*Chi;}

TPaveText *cms = new TPaveText(0.2,0.94,0.35,0.98,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.05);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char fname1[1024], fname2[1024], fname3[1024];
sprintf(fname1,"rootfiles/etalt1p5_ResonanceShapes_EOY2017_Suu_Diquark_S%d_chi%d.root",Suu,Chi);
sprintf(fname2,"rootfiles/etalt1p5_ResonanceShapes_Run3Summer22_Suu_Diquark_S%d_chi%d.root",Suu,Chi);
sprintf(fname3,"rootfiles/etalt1p5_ResonanceShapes_Run3Summer22EE_Suu_Diquark_S%d_chi%d.root",Suu,Chi);

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
h1->GetYaxis()->SetTitle("Normalized entries");
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
h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");

char legname[1024];
sprintf(legname,"#splitline{M_{S} = %d GeV}{M_{#chi} = %d GeV}",Suu,Chi);


double x1,x2,y1,y2;
if(strcmp(var,"FourjetMass")==0 || strcmp(var,"Maverage")==0) {x1=0.62; x2=0.8; y1=0.55; y2=0.85;}

TLegend *leg = new TLegend(x1,y1,x2,y2,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->SetHeader(legname);
leg->AddEntry((TObject*)0,"","");
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


TF1 *g1 = new TF1("g1","gaus",1,1400);
g1->SetRange(6328.,7060.);
h1->Fit(g1,"R");
g1->SetLineStyle(kDashed);
g1->SetLineColor(kBlack);
g1->SetLineWidth(3);
g1->Draw("same");

TF1 *g2 = new TF1("g2","gaus",1,1400);
g2->SetRange(6328.,7060.);
h2->Fit(g2,"R");
g2->SetLineStyle(kDashed);
g2->SetLineColor(kBlue);
g1->SetLineWidth(3);
g2->Draw("same");

TF1 *g3 = new TF1("g3","gaus",1,1400);
g3->SetRange(6328.,7060.);
h3->Fit(g3,"R");
g3->SetLineStyle(kDashed);
g3->SetLineColor(kRed);
g1->SetLineWidth(3);
g3->Draw("same");

cout<<"chi2 / ndf 1 = "<<g1->GetChisquare()<<"/"<<g1->GetNDF()<<endl;
cout<<"Prob 1 = " <<g1->GetProb()<<endl;
cout<<"chi2 / ndf 2 = "<<g2->GetChisquare()<<"/"<<g2->GetNDF()<<endl;
cout<<"Prob 2 = " <<g2->GetProb()<<endl;
cout<<"chi2 / ndf 3 = "<<g3->GetChisquare()<<"/"<<g3->GetNDF()<<endl;
cout<<"Prob 3 = " <<g3->GetProb()<<endl;

char legentry1[1024], legentry2[1024], legentry3[1024];
sprintf(legentry1,"Peak = #splitline{%.0f}{#pm %.0f} GeV",g1->GetParameter(1),g1->GetParError(1));
sprintf(legentry2,"Peak = #splitline{%.0f}{#pm %.0f} GeV",g2->GetParameter(1),g2->GetParError(1));
sprintf(legentry3,"Peak = #splitline{%.0f}{#pm %.0f} GeV",g3->GetParameter(1),g3->GetParError(1));

TLegend *leg2 = new TLegend(0.62,0.15,0.8,0.5,"");
leg2->SetBorderSize(0);
leg2->SetTextSize(0.04);
leg2->AddEntry(h1,legentry1,"L");
leg2->AddEntry(h2,legentry2,"L");
leg2->AddEntry(h3,legentry3,"L");
leg2->Draw();


char cname_1[1024], cname_2[1024];
sprintf(cname_1,"plots/etalt1p5_%s_Summer22_VS_Summer22EE_VS_EOY2017_S%d_chi%d_GausFit.png",var,Suu,Chi);
sprintf(cname_2,"plots/etalt1p5_%s_Summer22_VS_Summer22EE_VS_EOY2017_S%d_chi%d_GausFit.pdf",var,Suu,Chi);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
