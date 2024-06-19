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

void Plot_MC_CHS_vs_PUPPI(){

char xaxistitle[1024];
char run[1024];

sprintf(xaxistitle,"MET / H_{T}");
sprintf(run,"BC");
double xmin = 0;
double xmax = 1;

TPaveText *cms = new TPaveText(0.17,0.95,0.32,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TPaveText *lumileg = new TPaveText(0.81,0.95,0.96,0.99,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("13.6 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);

char fname1[1024], fname2[1024];
sprintf(fname1,"Histos_DataRun2022%s_VS_QCDFlatMC_AllSelCrit_AK4PUPPI.root",run);
sprintf(fname2,"Histos_DataRun2022%s_VS_QCDFlatMC_AllSelCrit_AK4CHS.root",run);

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");

cout << "File used for PUPPI: " << fname1 << endl;
cout << "File used for CHS: " << fname2 << endl;

TH1D *h1 = (TH1D*)f1->Get("h_METoverHT_mc");
TH1D *h2 = (TH1D*)f2->Get("h_METoverHT_mc");

for(int i=1; i<=h1->GetNbinsX(); i++)
{
	if(h1->GetBinContent(i)==0) h1->SetBinContent(i,0.0000000000001);
	if(h2->GetBinContent(i)==0) h2->SetBinContent(i,0.0000000000001);	
}


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
h1->GetYaxis()->SetTitle("Entries");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetMarkerColor(kRed);
h1->SetMarkerStyle(8);
h1->SetMarkerSize(0.8);
h1->SetLineColor(kRed);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
//h1->SetMinimum(0.0000000005);
h1->SetMinimum(0.00000000005);
//h1->SetMaximum(100);

h2->SetLineColor(kBlue);
h2->SetLineWidth(3);

h1->Draw("PE1");
h2->Draw("hist same");
h1->Draw("PE1 same");

char legname[1024];
sprintf(legname,"#splitline{QCD MC}{All analysis cuts applied}");

char integCHS[1024], integPUPPI[1024];
sprintf(integPUPPI,"Integral PUPPI = %.6f",h1->Integral());
sprintf(integCHS,"Integral CHS = %.6f",h2->Integral());

TLegend *leg = new TLegend(0.45,0.5,0.75,0.9,""); //top right
//TLegend *leg = new TLegend(0.5,0.05,0.7,0.45,""); //bottom right
//TLegend *leg = new TLegend(0.17,0.05,0.47,0.45,""); //bottom left
//TLegend *leg = new TLegend(0.36,0.05,0.56,0.45,""); //bottom middle
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->SetHeader(legname);
leg->AddEntry(h1,"AK4 PUPPI","PE");
leg->AddEntry(h2,"AK4 CHS","L");
leg->AddEntry((TObject*)0,integPUPPI,"");
leg->AddEntry((TObject*)0,integCHS,"");
leg->Draw();

cms->Draw();
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

TH1D *h_ratio = (TH1D*)h1->Clone();
h_ratio->Divide(h2);

//h_ratio->SetBinContent(4,1);

h_ratio->SetStats(0);
h_ratio->SetMarkerStyle(8);
h_ratio->SetMarkerColor(kBlack);
h_ratio->SetLineColor(kBlack);
h_ratio->SetMarkerSize(0.8);
h_ratio->GetXaxis()->SetRangeUser(xmin, xmax);
h_ratio->GetYaxis()->SetRangeUser(0.41, 1.59);
h_ratio->GetYaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelOffset(0.03);
h_ratio->GetXaxis()->SetTitle(xaxistitle);
h_ratio->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio->GetYaxis()->SetTitle("PUPPI / CHS");
h_ratio->GetYaxis()->CenterTitle(1);
h_ratio->GetYaxis()->SetTitleSize(0.12);
h_ratio->GetYaxis()->SetTitleOffset(0.5);
h_ratio->GetYaxis()->SetNdivisions(210);
h_ratio->SetLineWidth(4);
h_ratio->SetLineStyle(kDashed);
h_ratio->Draw("hist");

TLine *line = new TLine(xmin,1,xmax,1);
line->SetLineWidth(2);
line->SetLineColor(kRed);
//line->SetLineStyle(kDashed);
line->Draw("same");

char cname_1[1024], cname_2[1024];
sprintf(cname_1,"plots/CHS_VS_PUPPI_MC/AllCuts_QCDMC_CHS_VS_PUPPI_METoverHT.png");
sprintf(cname_2,"plots/CHS_VS_PUPPI_MC/AllCuts_QCDMC_CHS_VS_PUPPI_METoverHT.pdf");

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
